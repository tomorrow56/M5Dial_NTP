# M5Dial_NTP

英語版ドキュメントは `README.md` を参照してください。

## 概要

`M5Dial_NTP` は M5Dial 向けの Arduino スケッチ集です。
このリポジトリには、時計・タイマー・簡易ピアノなどのサンプルが含まれます。

## 含まれるスケッチ

- `M5Dial/M5Dial_watch_mod/M5Dial_watch_mod.ino`
  - Wi-Fi で NTP 時刻を取得し、RTC に反映するアナログ時計
- `M5Dial/watchESPI/watchESPI.ino`
  - RTC の時刻を使うアナログ時計（NTP 同期なし）
- `M5Dial/timer/timer.ino`
  - ダイヤル操作とタッチで使うタイマー
- `M5Dial/pianoDial/pianoDial.ino`
  - タッチで音階を鳴らすピアノ風アプリ

## 必要環境

- Arduino IDE 2.x（推奨）
- ESP32 ボードパッケージ（Espressif Systems）
- M5Dial 用ライブラリ（`M5Dial.h` が使える環境）
- `TFT_eSPI`（`watchESPI`, `M5Dial_watch_mod` で使用）
- `Tone32`（`pianoDial` で使用）
  - このリポジトリには `M5Dial/pianoDial/Tone32-master` が同梱されています

## 使い方

1. Arduino IDE で使いたい `.ino` を開く
2. ボードを M5Dial / ESP32S3 系に設定する
3. 必要なライブラリをインストールする
4. M5Dial を接続して書き込む

## NTP 設定（`M5Dial_watch_mod`）

- `ssid`
- `password`
- `ntpServer`

## 注意

- フォントヘッダ（`Noto.h` など）は時計スケッチで使用されています。
