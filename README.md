# テレメトリシステム / Telemetry System

---

## 📖 概要 / Overview

本リポジトリは、**気球搭載機器からのテレメトリデータを地上局を通じてサーバーに収集・可視化するシステム**のソースコードを管理しています。  
This repository manages the source code for a **telemetry system that collects and visualizes telemetry data from a balloon via ground stations to a server**.

構成要素 / Components:

- STM32メイン基板 (STM32 main board): LoRaパケット送信 / コマンド受信
- ESP32地上局 (ESP32 ground stations): LoRaパケット受信 / サーバー送信 / コマンド送信
- サーバー (Server): FastAPI + SQLite3 + WebSocket
- フロントエンド (Frontend): CesiumJS + HTML/JS/CSS

---

## 🗂️ ディレクトリ構成 / Directory Structure

```plaintext
telemetry-system-repo/
├── stm32-firmware/         # STM32ファームウェア / STM32 Firmware
├── esp32-firmware/         # ESP32ファームウェア / ESP32 Firmware
├── server/                 # サーバー (FastAPI + SQLite) / Server (FastAPI + SQLite)
├── frontend/               # フロントエンド (CesiumJS) / Frontend (CesiumJS)
└── docs/                   # ドキュメント / Documentation
```

---

## 🚀 セットアップ手順 / Setup Instructions

### サーバー / Server

```bash
cd server
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
uvicorn app.main:app --reload
```

### フロントエンド / Frontend

```bash
cd frontend
npm install
npm run dev
```

### ESP32 / STM32

PlatformIO または Arduino IDE を使用してそれぞれの `firmware` ディレクトリからビルドしてください。  
Use PlatformIO or Arduino IDE to build firmware from the respective `firmware` directories.

---

## 📡 システム構成図 / System Architecture

```
[STM32] → LoRa → [ESP32 Ground Stations] → Wi-Fi → [FastAPI Server] → WebSocket → [Frontend / CesiumJS]
                                     ↑             ↓
                                HTTP API / Uplink Command
```

---

## 📝 ライセンス / License

このリポジトリは MIT ライセンスの下で公開されています。  
This repository is licensed under the MIT License.

---

## 📧 問い合わせ / Contact

プロジェクトに関する問い合わせは GitHub Issues または開発チームまでご連絡ください。  
For inquiries about the project, please contact us via GitHub Issues or reach out to the development team.

---