# AGENTS.md

## Project Overview

Embedded firmware for a custom synthesizer UI board. C++ Arduino-style project targeting **Seeed XIAO ESP32-S3** via **PlatformIO**.

All source lives under `Software/XVA1UserInterface/`. All commands below must be run from that directory.

---

## Dev Commands

```bash
platformio run                  # compile only
platformio run -t upload        # compile + flash
platformio run -t monitor       # open serial monitor (115200 baud)
./upload_and_monitor.sh         # upload then open monitor
platformio run -t clean         # clean build artifacts
```

First run after a fresh clone downloads the ESP32 toolchain and libraries — can take several minutes.

---

## Testing

No automated tests exist. `test/` is a PlatformIO placeholder only.

Verification = compile (`platformio run`) + flash + observe serial output at 115200 baud. Serial debug output is extensive throughout the code.

---

## Architecture

- **`src/main.cpp`** — Arduino `setup()`/`loop()` entry point; also contains `rotaryEncoderChanged()` with intentional speed-scaling (fast turn = +20, medium = +10, slow = +2, very slow = +1).
- **`src/Hardware.h`** — defines all hardware globals (MCPs, displays, encoders, `Synthesizer`, `ParameterController`). **Include in `main.cpp` only** — it contains object definitions, not declarations; multiple includes cause linker errors.
- **`src/ParameterController`** — central UI orchestrator; maps encoder changes to synth parameters, manages pages/sections, drives TFT + 4 OLED displays.
- **`src/SectionFactory`** — builds the 12 `Section` objects (synth parameter groups). Sections 9–12 are accessed via SHIFT + buttons 1–4.
- **`src/Synthesizer`** — communicates with the physical XVA1 over a second UART (`SynthSerial`) at **500000 baud** on D6/D7. Protocol: `'r'` = select patch, `'d'` = dump 512-byte patch, `'s'` = set parameter.
- **`include/User_Setup.h`** — TFT_eSPI pin/driver config. Injected via `-include` build flag + `USER_SETUP_LOADED=1`. If this path breaks, the TFT silently uses wrong pin mappings.

---

## Key Quirks

- **`SynthSerial` vs `Serial`:** `SynthSerial` uses **UART1** (explicitly routed to D6=GPIO43/TX and D7=GPIO44/RX via the ESP32-S3 GPIO matrix). `Serial` uses UART0. They are now fully independent — no conflict.
- **Patch indexing:** UI shows 1-indexed patch numbers; wire protocol is 0-indexed (`selectPatch(n)` sends `n - 1`).
- **Parameters > 255:** Use two-byte format — send `255`, then `(param_index - 256)`.
- **Envelope rendering** runs as a separate FreeRTOS task on the second ESP32 core (`displayEnvelopesTaskHandle`).
- **`ParameterType` enum values:** `NUMERIC`, `CENTER_128`, `BITWISE`, `MIDI_NOTE`, `ASCII_CHAR`, `PERFORMANCE_CTRL` — display rendering branches on these.
- **`projectFilesBackup/`** under the PlatformIO project root is a manual backup; not part of the build.
- **`.pio/`** is gitignored (toolchain + fetched libs).
- No linter, formatter, static analysis, or CI is configured.
