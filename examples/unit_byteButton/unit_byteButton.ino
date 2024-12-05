#include "unit_byte.hpp"
#include <M5Unified.h>

UnitByte device;
uint8_t buttonId        = 0x47;
const uint32_t colors[] = {
    0xFF0000, 0x0000FF, 0xFFFF00, 0xFF00FF, 0x00FFFF, 0xFFFFFF, 0xFFA500, 0x808080, 0x00FF00,
};
void setup()
{
    M5.begin();
    Serial.begin(115200);
    device.begin(&Wire1, buttonId, 32, 33, 400000);
    Serial.printf("getLEDMode :%d\n", device.getLEDShowMode());
    delay(1000);
    Serial.printf("Switch Status:%d\n", device.getSwitchStatus());
    delay(1000);
    for (uint8_t i = 0; i < 8; i++) {
        uint8_t switchStatus8Bytes = device.getSwitchStatus(i);
        Serial.print("Switch Status Byte ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(switchStatus8Bytes);
    }
    delay(1000);

    device.setLEDShowMode(BYTE_LED_USER_DEFINED);
    Serial.println("Set LED show self define.");
    delay(1000);
    // Set LED brightness (assuming 250)
    for (uint8_t i = 0; i <= 8; i++) {
        device.setLEDBrightness(i, 250);
    }
    delay(1000);
    // Get LED brightness to confirm
    Serial.printf("New LED Brightness:: %02X\n", device.getLEDBrightness());
    delay(1000);
    // RGB
    for (int i = 0; i <= 8; i++) {
        device.setRGB888(i, colors[i]);
        // device.setRGB233(i, colors[8-i]);
        // Output the hexadecimal value of the current color
        Serial.printf("Set RGB to %06X\n", (unsigned int)colors[i]);
    }
    delay(1000);

    for (int i = 0; i < 8; i++) {
        // Serial.printf("Retrieved  RGB: %06X\n",device.getRGB888(i));
        Serial.printf("Retrieved  RGB: %06X\n", device.getRGB233(i));
    }

    delay(1000);
    device.setIRQEnable(false);
    delay(1000);
    Serial.printf("getIRQEnable: %02x\n", device.getIRQEnable());
    delay(1000);
    Serial.printf("Firmware Version: %02x\n", device.getFirmwareVersion());
    delay(1000);

    Serial.printf("read I2C Address:%02X\n", device.getI2CAddress());
    delay(1000);

    device.setI2CAddress(0x12);
    delay(1000);
    Serial.printf("new I2C Address: %02x\n", device.getI2CAddress());
    delay(2000);
    device.setI2CAddress(buttonId);
    delay(1000);

    device.setLEDShowMode(BYTE_LED_MODE_DEFAULT);
    Serial.println("Set LED show sys define.");
    delay(1000);
    device.setRGB233(8, colors[1]);
    delay(1000);
    device.setFlashWriteBack();
    delay(1000);
    for (int i = 0; i < 8; i++) {
        device.setSwitchOffRGB888(i, colors[i]);
        // Output the hexadecimal value of the current color
        Serial.printf("Set Switch Off RGB to %06X\n", (unsigned int)colors[i]);
    }
    delay(1000);
    for (int i = 0; i < 8; i++) {
        device.setSwitchOnRGB888(i, colors[9 - i]);
        // Output the hexadecimal value of the current color
        Serial.printf("Set Switch On RGB to %06X\n", (unsigned int)colors[i]);
    }
    delay(1000);
    device.setFlashWriteBack();
}
void loop()
{
    delay(1000);
}