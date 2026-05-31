//
// Debug.h — compile-time debug logging
//
// When DEBUG is defined (set via build flag -D DEBUG), LOG/LOGLN forward to
// Serial. On the XIAO ESP32-S3 without ARDUINO_USB_CDC_ON_BOOT, Serial maps
// to the HWCDC (native USB) which works fine for monitoring but requires the
// USB cable to be connected. Do NOT set ARDUINO_USB_CDC_ON_BOOT=1 — it
// conflicts with SPI/TFT initialisation on this board and causes a boot panic.
//

#pragma once

#ifdef DEBUG
    #define LOG_BEGIN()    Serial.begin(115200)
    #define LOG(...)       Serial.print(__VA_ARGS__)
    #define LOGLN(...)     Serial.println(__VA_ARGS__)
#else
    #define LOG_BEGIN()
    #define LOG(...)
    #define LOGLN(...)
#endif
