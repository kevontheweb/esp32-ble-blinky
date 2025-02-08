#ifndef BLECONTROLLER_H
#define BLECONTROLLER_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "secrets.h"

class BLEController {
public:
  BLEController();
  void setup();
  bool is_animation_paused();

private:
  bool animation_pause_state;
  BLECharacteristic* characteristic_ptr;
  const char* service_uuid = BLE_SERVICE_UUID;
  const char* characteristic_uuid = BLE_CHARACTERISTIC_UUID;

  class CustomCallback : public BLECharacteristicCallbacks {
  public:
    CustomCallback(BLEController* controller);
    void on_write(BLECharacteristic* characteristic_ptr);
  private:
    BLEController* controller;
  };
};

#endif // BLECONTROLLER_H