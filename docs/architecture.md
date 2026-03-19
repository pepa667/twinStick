
# System Architecture

TwinStick uses a dual‑microcontroller design.

## RP2040 (NexusUI)

Handles:

- button scanning
- LCD UI
- configuration menu
- USB HID interface
- sending input state to ESP32

## ESP32 (HydraCore)

Handles:

- Bluetooth stack
- HID emulation
- pairing management

## Data Flow

USB:

Buttons → RP2040 → USB HID → Host

Bluetooth:

Buttons → RP2040 → ArcadeLink → ESP32 → Bluetooth HID → Host
