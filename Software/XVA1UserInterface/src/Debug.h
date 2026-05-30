//
// Debug.h — compile-time debug logging
//
// When DEBUG is defined (set via build flag -D DEBUG), LOG/LOGLN forward to
// Serial (USB CDC on XIAO ESP32-S3 with ARDUINO_USB_CDC_ON_BOOT=1).
// When DEBUG is not defined all macros expand to nothing — zero overhead.
//
// Usage:
//   LOG("value: ");   LOGLN(x);   LOG(x, DEC);
//
// To enable:  add -D DEBUG to build_flags in platformio.ini
// To disable: remove -D DEBUG for production builds
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
