# HydraCore

HydraCore is the **ESP32 firmware** responsible for wireless connectivity in the TwinStick platform.

Each HydraCore instance represents **one player controller**.

The system normally runs **two ESP32 modules simultaneously**.

---

# Responsibilities

HydraCore handles:

- Bluetooth pairing
- Wireless connection management
- HID profile emulation
- Receiving input data from RP2040
- Translating data into HID reports

---

# Library

HydraCore is built using:

**HOJA-LIB-ESP32**

This library provides controller profile emulation including:

- XInput
- DInput
- Nintendo Switch Pro Controller
- BLE HID

---

# Data Source

HydraCore receives input data via **UART ArcadeLink protocol**.

The RP2040 broadcasts controller state packets.

Each ESP32 processes only packets matching its PLAYER_ID.

---

# Architecture

RP2040 → UART → ESP32 → Bluetooth HID → Host
