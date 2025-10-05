# AtCoder cookie 自動更新スクリプト

`tools/update_atcoder_cookie.py` は `REVEL_SESSION` (AtCoder ログインセッション) を期限前に自動更新する補助ツールです。

## 目的

- ローカルの `~/.local/share/atcoder-tools/cookie.txt` を手動で貼り替える手間を減らす
- 期限切れ直前で `atcoder-tools gen / test` が失敗するのを防ぐ

## 前提

- Python 3.9+
- `requirements.txt` に含まれる `requests`, `atcoder-tools` がインストール済み
- 2要素認証(2FA) 未対応 (有効化している場合は別途調整が必要)

## 環境変数

| 変数 | 内容 |
|------|------|
| `ATCODER_USERNAME` | AtCoder ユーザ名 (スクリーンネームではなくログイン用) |
| `ATCODER_PASSWORD` | パスワード |

シェル例:

```bash
export ATCODER_USERNAME=your_id
export ATCODER_PASSWORD='your_password'
```

## 使い方

```bash
python tools/update_atcoder_cookie.py \
  --cookie-path ~/.local/share/atcoder-tools/cookie.txt \
  --threshold-days 14
```

### 主なオプション

- `-t / --threshold-days <N>`: 有効期限残り日数が N 日未満なら更新 (既定 14)
- `-f / --force`: 閾値に関係なく常に更新
- `--print-only`: ファイルを書かずに LWP 形式を標準出力へ (Cron + 差分監視などに)

## Exit Code (抜粋)

| コード | 意味 |
|--------|------|
| 0 | 正常終了 |
| 1-3 | CSRF 取得/ログイン/セッション取得失敗 |
| 10 | 環境変数未設定 |
| 130 | Ctrl-C 中断 |

## Cron 運用例

週1で強制更新 (失敗時ログを残す):

```cron
0 3 * * 1 ATCODER_USERNAME=foo ATCODER_PASSWORD=bar /usr/bin/python3 /path/to/repo/tools/update_atcoder_cookie.py -f >> /var/log/atcoder_cookie.log 2>&1
```

## セキュリティ注意

- このリポジトリに `cookie.txt` をコミットしない (`.gitignore` 推奨)
- パスワードを平文で他ファイルに書かない
- 共有マシンでは `print-only` で内容が出力されるログの取り扱いに注意

## 改善余地

- 2FA 対応 (TOTP 入力)
- 失効前自動通知 (Slack/Webhook)
- `atcoder-tools login` の内部再利用

