# 📡 COMPANION — Voice-Controlled Buzzer Finder

A voice-activated item finder system built on an **ESP8266** + **web app**. Say the name of an item out loud, and the buzzer attached to it beeps — helping you locate your wallet, keys, glasses, and more without touching a thing.

---

## 🧠 How It Works

```
Your Voice → Browser (Speech Recognition) → HTTP Request → ESP8266 → GPIO Pin → Buzzer 🔔
```

1. Open the web app on your phone or PC (connected to the same WiFi)
2. Tap the mic button and speak a keyword (e.g. *"wallet"*, *"keys"*)
3. The browser recognises the word and sends an HTTP GET request to the ESP8266
4. The ESP8266 fires the corresponding GPIO pin → the buzzer beeps
5. Say *"stop"* to silence it

---

## 🛠️ Hardware

| Component | Quantity |
|-----------|----------|
| ESP8266 NodeMCU | 1 |
| 5V Active Buzzers | 6 |
| Jumper wires | as needed |

### Pin Mapping

| D-Pin | GPIO | Item |
|-------|------|------|
| D1 | 5 | Wallet |
| D2 | 4 | Keys |
| D5 | 14 | Medicine |
| D6 | 12 | Spectacles |
| D7 | 13 | Stick |
| D8 | 15 | Watch |

> ⚠️ **Do NOT use D0 (GPIO16), D3 (GPIO0), or D4 (GPIO2)** — these are boot-strapping pins. The ESP8266 hardware drives them HIGH before your code runs, causing buzzers to fire on every power-up.

### Wiring Each Buzzer

```
Buzzer (+) ──→ GPIO Pin (D1–D8)
Buzzer (–) ──→ GND
```

All 6 buzzers share the ESP8266's GND rail.

---

## 💻 Software

### ESP8266 Firmware (`esp32_buzzer_fixed.ino`)

- Built with **Arduino IDE** + ESP8266 core
- Runs a lightweight HTTP server on **port 81**
- Non-blocking buzzer toggling via `millis()` (no `delay()` calls)
- WiFi modem sleep **disabled** for minimum latency (~30ms response)

**Required Libraries** (install via Arduino Library Manager):
- `ESP8266WiFi`
- `ESP8266WebServer`

### Web App (`index.html`)

- Pure HTML/CSS/JS — no framework, no server needed
- **Three.js** animated 3D orb visualiser reacts to your voice
- **Web Speech API** (Chrome) for continuous voice recognition
- O(1) keyword matching via a pre-built `Map` — zero loop overhead
- Saves ESP IP address to `localStorage`

---

## 🚀 Setup

### 1. Flash the ESP8266

1. Open `esp32_buzzer_fixed.ino` in Arduino IDE
2. Set your WiFi credentials at the top of the file:
   ```cpp
   const char* ssid     = "YOUR_WIFI_NAME";
   const char* password = "YOUR_WIFI_PASSWORD";
   ```
3. Select board: **NodeMCU 1.0 (ESP-12E Module)**
4. Flash the firmware
5. Open Serial Monitor (115200 baud) and note the IP address printed after connecting

### 2. Open the Web App

- Open `index.html` directly in **Google Chrome** (Speech API requires Chrome)
- Must be on the **same WiFi network** as the ESP8266
- Enter the ESP's IP address in the box at the bottom and click **Connect**

### 3. Test It

- Click the mic button — it should glow gold and show "Listening…"
- Say one of the keywords out loud
- The corresponding buzzer should beep within ~30ms

---

## 🎙️ Voice Keywords

| Say this... | Fires buzzer for... |
|-------------|---------------------|
| wallet, valet, ballet | Wallet |
| keys, key, cheese | Keys |
| medicine, medic, medical | Medicine |
| spectacles, specs, glasses | Spectacles |
| stick, sticks | Stick |
| watch, watches | Watch |
| **stop, silence, quiet, off** | **Stops all buzzers** |

Aliases handle common speech-recognition mishears (e.g. Chrome often hears *"cheese"* for *"keys"*).

---

## 🌐 API Endpoints

The ESP8266 exposes a simple REST API on `http://<ESP_IP>:81`:

| Endpoint | Action |
|----------|--------|
| `GET /buzz/0` | Beep wallet buzzer (D1) |
| `GET /buzz/1` | Beep keys buzzer (D2) |
| `GET /buzz/2` | Beep medicine buzzer (D5) |
| `GET /buzz/3` | Beep spectacles buzzer (D6) |
| `GET /buzz/4` | Beep stick buzzer (D7) |
| `GET /buzz/5` | Beep watch buzzer (D8) |
| `GET /stop` | Stop all buzzers |

You can trigger any buzzer manually in a browser or with `curl`:
```bash
curl http://192.168.1.XXX:81/buzz/0
curl http://192.168.1.XXX:81/stop
```

---

## ⚡ Latency Optimisations

The firmware includes several tweaks to minimise the delay between saying a word and hearing the beep:

| Optimisation | Effect |
|---|---|
| `WiFi.setSleepMode(WIFI_NONE_SLEEP)` | Eliminates 100–300ms modem wake-up delay |
| `WiFi.setOutputPower(20.5)` | Max TX power → fewer retransmits → lower jitter |
| `WiFi.persistent(false)` | Skips flash writes on boot, faster startup |
| GPIO fires **before** HTTP response | Buzzer triggers at earliest possible moment |
| `Connection: close` header | Browser doesn't wait for keep-alive timeout |

**Typical end-to-end latency:** ~30ms from HTTP request to buzzer beep.

> Note: The largest remaining delay is the Speech Recognition engine itself — Chrome takes 200–500ms to finalise a spoken word. This is a browser/Google limitation and cannot be reduced on the ESP side.

---

## 🐛 Known Issues & FAQ

**Q: All buzzers beep the moment I plug in the ESP.**
A: You're using D0, D3, or D4 — boot-strapping pins that go HIGH before `setup()` runs. Move to D1, D2, D5, D6, D7, or D8.

**Q: The blue LED on the ESP is always on.**
A: Normal behaviour. The blue LED is tied to GPIO2 (D4) / the TX line and reflects WiFi/serial activity. It is not a fault.

**Q: Voice commands work but there's a big delay.**
A: Make sure the ESP and your device are on the same WiFi band (2.4GHz). Also confirm the firmware has `WiFi.setSleepMode(WIFI_NONE_SLEEP)` — older versions of the code did not include this.

**Q: Speech recognition doesn't work.**
A: The Web Speech API only works in **Google Chrome** and requires microphone permission. It also needs an internet connection (Google's servers process the audio).

**Q: Can I add more items?**
A: The ESP8266 has more usable GPIOs (A0 in digital mode, etc.), but 6 is the practical limit with D-pins. To add more, you could use a GPIO expander (e.g. MCP23017 over I2C).

---

## 📁 File Structure

```
companion/
├── index.html              # Web app (open in Chrome)
└── esp32_buzzer_fixed.ino  # ESP8266 Arduino firmware
```

---

## 🔧 Built With

- [ESP8266 Arduino Core](https://github.com/esp8266/Arduino)
- [Three.js](https://threejs.org/) — 3D visualiser
- [Web Speech API](https://developer.mozilla.org/en-US/docs/Web/API/Web_Speech_API) — voice recognition
- Orbitron & Rajdhani fonts via Google Fonts

---

## 📜 License

Personal / hobby project. Free to use and modify.
