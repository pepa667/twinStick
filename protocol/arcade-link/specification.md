
# ArcadeLink Protocol

Communication protocol between RP2040 (NexusUI) and ESP32 (HydraCore).

## Transport

UART

Recommended settings:

115200 baud

## Packet Format

```
[HEADER][TYPE][DATA][CHECKSUM]
```

Example packet:

```
AA 01 34 12 5F
```

Field description:

HEADER   start of packet (0xAA)
TYPE     message type
DATA     payload
CHECKSUM simple checksum

## Message Types

| Code | Description |
|-----|-------------|
01 | Button state |
02 | Change HID profile |
03 | Bluetooth command |
04 | Status request |
05 | Status response |

## Button Bitmask

Buttons are sent as a 16-bit value.

| Bit | Button |
|----|--------|
0 | UP |
1 | DOWN |
2 | LEFT |
3 | RIGHT |
4 | A |
5 | B |
6 | X |
7 | Y |
8 | START |
9 | SELECT |
10 | L1 |
11 | R1 |
12 | L2 |
13 | R2 |
14 | HOME |
15 | Reserved |
