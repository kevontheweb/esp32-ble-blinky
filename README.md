## INFO
Add this to your `secrets.h` under `lib>secrets>secrets.h`.
You can use [this BLE UUID generator](https://bleid.netlify.app/).

```c++
#ifndef SECRETS_H
#define SECRETS_H

constexpr auto BLE_SERVICE_UUID = "<your_service_uuid_here>";
constexpr auto BLE_CHARACTERISTIC_UUID = "<your_characteristic_uuid_here>";

#endif
```


## How to build PlatformIO based project

1. [Install PlatformIO Core](https://docs.platformio.org/page/core.html)
2. Download [development platform with examples](https://github.com/platformio/platform-espressif32/archive/develop.zip)
3. Extract ZIP archive
4. Run these commands:

```shell
# Change directory to example
$ cd platform-espressif32/examples/arduino-blink

# Build project
$ pio run

# Upload firmware
$ pio run --target upload

# Build specific environment
$ pio run -e esp32dev

# Upload firmware for the specific environment
$ pio run -e esp32dev --target upload

# Clean build files
$ pio run --target clean
```