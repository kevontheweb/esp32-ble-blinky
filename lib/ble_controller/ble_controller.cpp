#include "ble_controller.h"
#include "secrets.h"

BLEController::BLEController() : animation_pause_state(false) {}

void BLEController::setup() {
    BLEDevice::init("LED Controller");
    BLEServer* server_ptr = BLEDevice::createServer();
    BLEService* service_ptr = server_ptr->createService(service_uuid);
    characteristic_ptr = service_ptr->createCharacteristic(
        characteristic_uuid,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_WRITE
    );
    characteristic_ptr->setCallbacks(new CustomCallback(this));
    characteristic_ptr->setValue("start");
    service_ptr->start();
    BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(service_uuid);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    pAdvertising->start();
}

bool BLEController::is_animation_paused() {
    return animation_pause_state;
}

BLEController::CustomCallback::CustomCallback(BLEController* controller) : controller(controller) {}

void BLEController::CustomCallback::on_write(BLECharacteristic* characteristic_ptr) {
    std::string value = characteristic_ptr->getValue();
    if (value == "pause") {
        controller->animation_pause_state = true;
    } else if (value == "start") {
        controller->animation_pause_state = false;
    }
}