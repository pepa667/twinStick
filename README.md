
# TwinStick

Universal **Arcade Controller Platform** with **USB + Bluetooth** support and multiple HID profiles.

## Architecture

TwinStick is divided into three major components:

```
TwinStick
 ├── HydraCore   (ESP32 Bluetooth stack / HID profiles)
 ├── NexusUI     (RP2040 inputs + LCD + system interface)
 └── ArcadeLink  (UART protocol between RP2040 and ESP32)
```

### HydraCore (ESP32)
Responsible for wireless connectivity.

Features:
- Bluetooth pairing
- HID profile emulation
- XInput
- DInput
- Nintendo Switch HID
- Communication with RP2040

### NexusUI (RP2040)
Responsible for the user interface and input scanning.

Features:
- Button scanning
- Shift register support
- LCD menu system
- Profile selection
- Bluetooth control
- USB HID mode
- Communication with ESP32

### ArcadeLink Protocol
UART communication protocol connecting NexusUI and HydraCore.

Responsibilities:
- Button state transmission
- Profile change commands
- Bluetooth management commands
- System status exchange

## Connection Modes

### USB Mode

Buttons → RP2040 → USB HID → Host

Advantages:
- ~1ms latency
- maximum compatibility

### Bluetooth Mode

Buttons → RP2040 → UART → ESP32 → Bluetooth HID → Host

Advantages:
- wireless support
- multi-profile compatibility

## HID Profiles

Supported modes:

- XInput (Xbox compatible)
- DInput (generic PC controller)
- Nintendo Switch Pro Controller

Selectable through NexusUI menu.

## Repository Layout

```
firmware/
    hydra-core-esp32/
    nexus-ui-rp2040/

protocol/
    arcade-link/

hardware/
    schematics/
    pcb/

docs/

tools/
```

## License

Open hardware / open firmware project.
