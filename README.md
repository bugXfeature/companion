# ESP32 Buzzer Project — Arch Linux Setup Guide

---

## PART 1 — Wiring Check

Your wiring based on your description:
- Buzzer **positive (+)** → **D7** on ESP32 (GPIO 13)
- Buzzer **negative (-)** → **GND** on ESP32

> ✅ This is correct for a passive buzzer.  
> If the buzzer is **active** (has a circuit board on it), it will just beep at one tone — that's fine too.

---

## PART 2 — Arch Linux USB Setup

### Step 1 — Install required packages

```bash
sudo pacman -S arduino arduino-avr-core python-pyserial
```

Also install the `udev` rules and add yourself to the `uucp` group (this is the group that owns serial ports on Arch):

```bash
sudo usermod -aG uucp $USER
sudo usermod -aG lock $USER
```

**Log out and log back in** (or reboot) for group changes to take effect.

---

### Step 2 — Install Arduino IDE 2 (recommended)

Arduino IDE 2 handles ESP32 much better than IDE 1.

```bash
# Via AUR (use yay or paru)
yay -S arduino-ide-bin
```

Or download the AppImage from https://www.arduino.cc/en/software and run:
```bash
chmod +x arduino-ide_*.AppImage
./arduino-ide_*.AppImage
```

---

### Step 3 — Check your ESP32 serial port

Plug in your ESP32 via USB. Then run:

```bash
ls /dev/ttyUSB* /dev/ttyACM*
```

You should see something like `/dev/ttyUSB0` or `/dev/ttyACM0`.

If you see **nothing**, install the CH340 driver (many ESP32 boards use this chip):

```bash
sudo modprobe ch341
```

Check again with `ls /dev/ttyUSB*`. Most ESP32 dev boards with a USB-to-serial chip will show up as `/dev/ttyUSB0`.

---

### Step 4 — Add ESP32 board support to Arduino IDE

1. Open Arduino IDE 2
2. Go to **File → Preferences**
3. In the **"Additional boards manager URLs"** field, paste:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Click OK
5. Go to **Tools → Board → Boards Manager**
6. Search for `esp32` and install **"esp32 by Espressif Systems"**

---

### Step 5 — Install the WebSocketsServer library

1. In Arduino IDE go to **Tools → Manage Libraries**
2. Search for `WebSockets`
3. Install **"WebSockets by Markus Sattler"**

---

### Step 6 — Configure the board

1. Go to **Tools → Board → esp32 → ESP32 Dev Module**
   (or pick the specific variant if you know your board — "ESP32-WROOM-32" is the most common)
2. **Tools → Port** → select `/dev/ttyUSB0` (or whichever appeared earlier)
3. **Tools → Upload Speed** → `115200`

---

### Step 7 — Edit and upload the firmware

1. Open `esp32_buzzer.ino` in Arduino IDE
2. Change these two lines at the top:
   ```cpp
   const char* SSID     = "YOUR_WIFI_SSID";
   const char* PASSWORD = "YOUR_WIFI_PASSWORD";
   ```
3. Make sure your laptop and ESP32 will be on the **same WiFi network**
4. Click **Upload** (→ arrow button)
5. While uploading, if you see `Connecting......____` stuck, **hold the BOOT button** on your ESP32 until upload starts

---

### Step 8 — Get the ESP32's IP address

After uploading, open **Tools → Serial Monitor**, set baud rate to `115200`.

You'll see output like:
```
[WIFI] Connecting to MyWiFi...
[WIFI] Connected!
[WIFI] IP Address: 192.168.1.42       ← COPY THIS
[WS] WebSocket server started on port 81
```

---

## PART 3 — Using the Web App

1. Open `index.html` in **Google Chrome** (Chrome has the best Speech Recognition API support)
2. In the **ESP32 IP** box at the bottom, type the IP you got from Serial Monitor (e.g. `192.168.1.42`)
3. Click **CONNECT** — the status should turn green
4. Click the **microphone button** and allow microphone access when Chrome asks
5. Say one of the trigger words: **alarm, buzzer, alert, ring, beep**
6. The transcript appears, it's sent to the ESP32, and the buzzer beeps!
7. Say **"stop"** to silence the buzzer

---

## PART 4 — Troubleshooting

| Problem | Fix |
|---------|-----|
| Port not visible | `sudo modprobe ch341` then replug USB |
| Permission denied on `/dev/ttyUSB0` | `sudo usermod -aG uucp $USER` then relogin |
| Stuck on `Connecting......` | Hold BOOT button on ESP32 during upload |
| WebSocket won't connect | Make sure laptop & ESP32 are on same WiFi network; check IP in Serial Monitor |
| Speech not working | Must use Chrome; must be on HTTPS or `localhost` (or just open the HTML file directly) |
| Buzzer makes no sound | Check wiring — positive to GPIO13, negative to GND; some boards label D7 differently, verify your board's pinout |

---

## PART 5 — Customizing Keywords

In `esp32_buzzer.ino`, edit these arrays to change your trigger/stop words:

```cpp
const String TRIGGER_KEYWORDS[] = {
  "alarm", "buzzer", "alert", "ring", "beep"
  // add whatever you want here
};

const String STOP_KEYWORDS[] = {
  "stop", "silence", "quiet", "off", "mute"
};
```

After editing, re-upload to the ESP32.
