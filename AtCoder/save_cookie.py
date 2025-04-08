#!/usr/bin/env python3
import os
import requests
from http.cookiejar import LWPCookieJar, Cookie
import time
from datetime import datetime
from atcodertools.fileutils.artifacts_cache import get_cache_file_path

# クッキー情報を標準入力から受け取る
print("AtCoderクッキー文字列を入力してください（REVEL_SESSION=...で始まる文字列）:")
cookie_str = input().strip()

# クッキーパスの設定
cookie_path = get_cache_file_path('cookie.txt')
os.makedirs(os.path.dirname(cookie_path), exist_ok=True)

# クッキーJarの作成
cookie_jar = LWPCookieJar(cookie_path)

# クッキー文字列を解析
cookie_parts = cookie_str.split(';')
main_part = cookie_parts[0].strip()
name_value = main_part.split('=', 1)
name = name_value[0]
value = name_value[1]

# 有効期限の設定 (Sun, 05 Oct 2025 16:04:07 GMT)
expires = int(time.mktime(datetime(2025, 10, 5, 16, 4, 7).timetuple()))

# ドメインとパスの設定
domain = "atcoder.jp"
path = "/"

# Cookieオブジェクトを作成
cookie = Cookie(
    version=0,
    name=name,
    value=value,
    port=None,
    port_specified=False,
    domain=domain,
    domain_specified=True,
    domain_initial_dot=False,
    path=path,
    path_specified=True,
    secure=True,
    expires=expires,
    discard=False,
    comment=None,
    comment_url=None,
    rest={'HttpOnly': None},
    rfc2109=False
)

# CookieをCookieJarに追加
cookie_jar.set_cookie(cookie)

# ファイルに保存
cookie_jar.save()

print(f"クッキーが {cookie_path} に保存されました")
print(f"ファイルのパーミッションを設定中...")
os.chmod(cookie_path, 0o600)
print("完了")