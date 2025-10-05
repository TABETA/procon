#!/usr/bin/env python3
"""AtCoder cookie 自動更新スクリプト

機能:
 1. 既存 cookie.txt (LWP-Cookies-2.0) を読み REVEL_SESSION の期限を取得
 2. 残り日数が閾値(デフォルト 14 日)未満、または --force 指定時に再ログイン
 3. ログインは username/password を環境変数 ATCODER_USERNAME, ATCODER_PASSWORD から取得
 4. 新しい Set-Cookie (REVEL_SESSION) を取得し LWP 形式で上書き
 5. --print-only なら標準出力に出すだけ

使い方例:
  python tools/update_atcoder_cookie.py --cookie-path ~/.local/share/atcoder-tools/cookie.txt
  python tools/update_atcoder_cookie.py -f -t 30
  ATCODER_USERNAME=foo ATCODER_PASSWORD=bar python tools/update_atcoder_cookie.py

注意: パスワードは環境変数でのみ扱い、引数やファイルに残さないこと。

制限: 2FA 有効アカウント未対応 (必要なら改修)。
"""
from __future__ import annotations
import argparse
import datetime as dt
import os
import re
import sys
from typing import Optional
import requests

LOGIN_URL = "https://atcoder.jp/login"
TOP_URL = "https://atcoder.jp/"
DEFAULT_COOKIE_PATH = os.path.expanduser("~/.local/share/atcoder-tools/cookie.txt")
LWP_HEADER = "#LWP-Cookies-2.0"
SESSION_COOKIE_NAME = "REVEL_SESSION"


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Update AtCoder REVEL_SESSION cookie if near expiry")
    p.add_argument("--cookie-path", default=DEFAULT_COOKIE_PATH, help="cookie.txt (LWP) のパス")
    p.add_argument("-t", "--threshold-days", type=int, default=14, help="更新する残り日数閾値")
    p.add_argument("-f", "--force", action="store_true", help="残り日数に関係なく更新")
    p.add_argument("--print-only", action="store_true", help="ファイルは書き換えず新しい LWP 行を出力")
    return p.parse_args()


def load_current_cookie_line(path: str) -> Optional[str]:
    try:
        with open(path, "r", encoding="utf-8") as f:
            for line in f:
                if line.startswith("Set-Cookie3:") and SESSION_COOKIE_NAME in line:
                    return line.strip()
    except FileNotFoundError:
        return None
    return None


def extract_expiry(line: str) -> Optional[dt.datetime]:
    m = re.search(r'expires="([0-9T:\-]+Z)"', line)
    if not m:
        return None
    try:
        return dt.datetime.strptime(m.group(1), "%Y-%m-%d %H:%M:%SZ").replace(tzinfo=dt.timezone.utc)
    except ValueError:
        return None


def need_update(expiry: Optional[dt.datetime], threshold_days: int, force: bool) -> bool:
    if force:
        return True
    if expiry is None:
        return True
    now = dt.datetime.now(dt.timezone.utc)
    remain = expiry - now
    return remain <= dt.timedelta(days=threshold_days)


def get_csrf_and_session(session: requests.Session) -> str:
    r = session.get(LOGIN_URL, timeout=20)
    r.raise_for_status()
    # CSRF token は hidden input name="csrf_token"
    m = re.search(r'name="csrf_token" value="([^"]+)"', r.text)
    if not m:
        print("[ERROR] csrf_token が取得できません", file=sys.stderr)
        sys.exit(1)
    return m.group(1)


def login_and_get_session_cookie(username: str, password: str) -> str:
    with requests.Session() as sess:
        csrf = get_csrf_and_session(sess)
        payload = {"username": username, "password": password, "csrf_token": csrf}
        r = sess.post(LOGIN_URL, data=payload, timeout=20, allow_redirects=False)
        # 成功すると 302 で / へリダイレクト
        if r.status_code not in (302, 303):
            print(f"[ERROR] ログイン失敗 status={r.status_code}", file=sys.stderr)
            if r.text:
                snippet = r.text[:400].replace("\n", " ")
                print(f"[DEBUG] resp snippet: {snippet}", file=sys.stderr)
            sys.exit(2)
        # Cookie の中に REVEL_SESSION
        for c in sess.cookies:
            if c.name == SESSION_COOKIE_NAME:
                # Expires は epoch 秒 (ない場合はセッション) => RFC日付は不要、LWPで独自指定
                # 追加で TOP にアクセスして長期クッキー化（AtCoder は最初から Max-Age 指定されることが多い）
                return c.value
        print("[ERROR] REVEL_SESSION が取得できません", file=sys.stderr)
        sys.exit(3)


def fetch_server_cookie_attributes() -> Optional[dt.datetime]:
    """TOP にアクセスして Set-Cookie ヘッダから Expires を抽出 (あれば)。"""
    r = requests.get(TOP_URL, timeout=20)
    # 直接ログイン前は匿名セッションになるので expiry は意味薄いが参考。
    sc = r.headers.get('Set-Cookie', '')
    m = re.search(r'REVEL_SESSION=[^;]+;[^E]*Expires=([^;]+);', sc, re.IGNORECASE)
    if not m:
        return None
    # 形式: Fri, 03 Apr 2026 14:21:21 GMT
    try:
        dt_obj = dt.datetime.strptime(m.group(1).strip(), "%a, %d %b %Y %H:%M:%S GMT")
        return dt_obj.replace(tzinfo=dt.timezone.utc)
    except ValueError:
        return None


def build_lwp_line(session_value: str, expiry: Optional[dt.datetime]) -> str:
    # 既存観察: expires="YYYY-MM-DD HH:MM:SSZ"
    if expiry is None:
        # デフォルト 180 日後
        expiry = dt.datetime.now(dt.timezone.utc) + dt.timedelta(days=180)
    exp_str = expiry.strftime("%Y-%m-%d %H:%M:%SZ")
    # セッション値は URL エンコード不要 (atcoder-tools もそのまま入れている)
    return (f'Set-Cookie3: {SESSION_COOKIE_NAME}="{session_value}"; path="/"; domain="atcoder.jp"; '
            f'path_spec; secure; expires="{exp_str}"; HttpOnly=None; version=0')


def write_cookie(path: str, lwp_line: str):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", encoding="utf-8") as f:
        f.write(LWP_HEADER + "\n")
        f.write(lwp_line + "\n")
    print(f"[INFO] cookie updated: {path}")


def main():
    ns = parse_args()
    current_line = load_current_cookie_line(ns.cookie_path)
    expiry = extract_expiry(current_line) if current_line else None

    force = ns.force
    username = os.getenv("ATCODER_USERNAME")
    password = os.getenv("ATCODER_PASSWORD")

    if not username or not password:
        print("[ERROR] ATCODER_USERNAME / ATCODER_PASSWORD 環境変数が未設定", file=sys.stderr)
        sys.exit(10)

    if current_line:
        print(f"[INFO] 現在の cookie 行: {current_line[:120]}...")
        if expiry:
            remain = expiry - dt.datetime.now(dt.timezone.utc)
            print(f"[INFO] 現在期限: {expiry.isoformat()} 残り {remain.days} 日")
        else:
            print("[WARN] expires が解析できませんでした -> 更新判定は閾値により True")

    if not need_update(expiry, ns.threshold_days, force):
        print("[INFO] 閾値に達していないので更新しません (--force で上書き可能)")
        return

    print("[INFO] ログインして新しいセッションを取得します...")
    session_value = login_and_get_session_cookie(username, password)

    server_expiry = fetch_server_cookie_attributes()
    lwp_line = build_lwp_line(session_value, server_expiry)

    if ns.print_only:
        print(LWP_HEADER)
        print(lwp_line)
        return

    write_cookie(ns.cookie_path, lwp_line)


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("[INFO] aborted", file=sys.stderr)
        sys.exit(130)
