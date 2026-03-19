#include <NimBLEDevice.h>
#include <BleGamepad.h>

HardwareSerial hidSerial(2);

BleGamepad *bleGamepad;

uint8_t profile = 0;
bool bluetoothEnabled = true;

uint16_t lastState = 0;

void startBLE() {

  if (profile == 0)
    bleGamepad = new BleGamepad("Hydra TwinStick A", "Hydra", 100);
  else
    bleGamepad = new BleGamepad("Hydra TwinStick B", "Hydra", 100);

  BleGamepadConfiguration config;
  config.setAutoReport(false);
  config.setControllerType(CONTROLLER_TYPE_GAMEPAD);

  bleGamepad->begin(&config);

  Serial.print("BLE iniciado com perfil ");
  Serial.println(profile);
}

void stopBLE() {

  Serial.println("Bluetooth desligado");

  if (bleGamepad != nullptr) {
    delete bleGamepad;
    bleGamepad = nullptr;
  }

  NimBLEDevice::deinit(true);
}

void toggleBluetooth() {

  bluetoothEnabled = !bluetoothEnabled;

  if (bluetoothEnabled) {

    Serial.println("Ligando Bluetooth");
    startBLE();

  } else {

    stopBLE();
  }
}

void nextProfile() {

  profile++;

  if (profile > 1)
    profile = 0;

  Serial.print("Mudando para perfil ");
  Serial.println(profile);

  stopBLE();
  delay(500);
  startBLE();
}

bool readPacket(uint16_t &state) {

  if (hidSerial.available() < 4)
    return false;

  if (hidSerial.read() != 0xAA)
    return false;

  uint8_t lo = hidSerial.read();
  uint8_t hi = hidSerial.read();
  uint8_t crc = hidSerial.read();

  if (((lo + hi) & 0xFF) != crc) {

    Serial.println("CRC FAIL");
    return false;
  }

  state = lo | (hi << 8);

  return true;
}

void sendHID(uint16_t state) {

  bool up = state & (1 << 0);
  bool down = state & (1 << 1);
  bool left = state & (1 << 2);
  bool right = state & (1 << 3);

  int hat = HAT_CENTERED;

  if (up && right) hat = HAT_UP_RIGHT;
  else if (up && left) hat = HAT_UP_LEFT;
  else if (down && right) hat = HAT_DOWN_RIGHT;
  else if (down && left) hat = HAT_DOWN_LEFT;
  else if (up) hat = HAT_UP;
  else if (down) hat = HAT_DOWN;
  else if (left) hat = HAT_LEFT;
  else if (right) hat = HAT_RIGHT;

  bleGamepad->setHat1(hat);

  for (int i = 4; i < 12; i++) {

    if (state & (1 << i)) {

      bleGamepad->press(i - 3);
      Serial.print("BTN ");
      Serial.print(i);
      Serial.println(" PRESS");

    } else {

      bleGamepad->release(i - 3);
    }
  }

  bleGamepad->sendReport();

  Serial.print("HAT: ");
  Serial.println(hat);
}

void handleSystemButtons(uint16_t state) {

  bool bt = state & (1 << 12);
  bool profileBtn = state & (1 << 13);

  static bool lastBT = false;
  static bool lastProfile = false;

  if (bt && !lastBT) {

    Serial.println("BT BUTTON");
    toggleBluetooth();
  }

  if (profileBtn && !lastProfile) {

    Serial.println("PROFILE BUTTON");
    nextProfile();
  }

  lastBT = bt;
  lastProfile = profileBtn;
}

void setup() {

  Serial.begin(115200);

  hidSerial.begin(
    115200,
    SERIAL_8N1,
    16,
    17);

  Serial.println("Hydra Core Boot");

  startBLE();
}

void loop() {

  uint16_t state;

  if (readPacket(state)) {

    if (state != lastState) {

      Serial.print("STATE: ");
      Serial.println(state, BIN);

      handleSystemButtons(state);

      if (bluetoothEnabled && bleGamepad->isConnected())
        sendHID(state);

      lastState = state;
    }
  }
}