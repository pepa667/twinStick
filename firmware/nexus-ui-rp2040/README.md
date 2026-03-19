# NexusUI

NexusUI is the **main firmware** running on the RP2040.

It acts as the central controller of the TwinStick platform.

---

# Responsibilities

NexusUI manages:

- Arcade input scanning
- Shift-register expansion hardware
- LCD configuration interface
- Profile switching
- Communication with HydraCore modules

---

# Input System

Inputs can be read through:

- Direct GPIO
- Shift registers
- Button matrices

---

# LCD Interface

The LCD allows configuration of:

- Controller profiles
- Bluetooth pairing
- System status
- Player connection state

Example:

TwinStick v0.1
Profile: XINPUT
P1 Connected
P2 Connected

---

# Communication

The RP2040 broadcasts input states using the **ArcadeLink UART protocol** to both ESP32 modules.
