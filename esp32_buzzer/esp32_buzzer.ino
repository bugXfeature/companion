// ════════════════════════════════════════════════════════════════
//  ESP8266 6-Buzzer Server  —  Low-latency build
//  Pins: D1 D2 D5 D6 D7 D8  (all boot-safe)
// ════════════════════════════════════════════════════════════════

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid     = "JESUS";
const char* password = "maximum_effort";

// ─── Pin mapping ─────────────────────────────────────────────────────────────
#define BUZZER_D1   5   // wallet
#define BUZZER_D2   4   // keys
#define BUZZER_D5  14   // medicine
#define BUZZER_D6  12   // spectacles
#define BUZZER_D7  13   // stick
#define BUZZER_D8  15   // watch

const int buzzerPins[6] = {
  BUZZER_D1, BUZZER_D2, BUZZER_D5,
  BUZZER_D6, BUZZER_D7, BUZZER_D8
};

#define BUZZER_ON  HIGH
#define BUZZER_OFF LOW
#define BEEP_INTERVAL 300

ESP8266WebServer server(81);

bool  isBuzzing       = false;
int   activeBuzzerPin = -1;
bool  buzzerState     = false;
unsigned long lastToggle = 0;

// ─── Buzzer control ───────────────────────────────────────────────────────────
void startBuzzer(int pin) {
  if (activeBuzzerPin >= 0) digitalWrite(activeBuzzerPin, BUZZER_OFF);
  activeBuzzerPin = pin;
  isBuzzing       = true;
  buzzerState     = true;
  digitalWrite(pin, BUZZER_ON);   // fire IMMEDIATELY
  lastToggle = millis();
}

void stopBuzzer() {
  if (activeBuzzerPin >= 0) digitalWrite(activeBuzzerPin, BUZZER_OFF);
  isBuzzing       = false;
  activeBuzzerPin = -1;
  buzzerState     = false;
}

// ─── CORS ─────────────────────────────────────────────────────────────────────
void addCORSHeaders() {
  server.sendHeader("Access-Control-Allow-Origin",  "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  // Tell browser not to wait — close connection immediately after response
  server.sendHeader("Connection", "close");
}

// ─── Handlers — fire buzzer FIRST, then send HTTP response ───────────────────
// Reason: the browser is blocked waiting for the response. If we send the
// response first and THEN fire, the browser unblocks and the UI updates,
// but the actual GPIO write happens after network I/O — adding ~10-30ms lag.
// Firing first means the buzzer triggers at the earliest possible moment.
void handleBuzzer(int index) {
  startBuzzer(buzzerPins[index]);   // GPIO fires HERE — before any network I/O
  addCORSHeaders();
  server.send(200, "text/plain", "OK");
}

void handleStop() {
  stopBuzzer();                     // GPIO off HERE — before any network I/O
  addCORSHeaders();
  server.send(200, "text/plain", "STOPPED");
}

void handleRoot() {
  addCORSHeaders();
  server.send(200, "text/plain", "ESP8266 6-Buzzer Server Running");
}

// ─── Setup ───────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  Serial.println("\n[BOOT] Initialising...");

  for (int i = 0; i < 6; i++) {
    pinMode(buzzerPins[i], OUTPUT);
    digitalWrite(buzzerPins[i], BUZZER_OFF);
  }

  // ── FIX 1: Disable WiFi modem sleep ──────────────────────────────────────
  // Default modem-sleep wakes the radio only every 100ms (DTIM interval).
  // Any request arriving during sleep has to wait for the next wake window.
  // Disabling sleep keeps the radio always-on → consistent <5ms response.
  WiFi.setSleepMode(WIFI_NONE_SLEEP);

  // ── FIX 2: Maximum TX power ───────────────────────────────────────────────
  // Lower TX power = more retransmits = higher jitter. Max power gives the
  // cleanest signal and fewest retransmits, especially across walls.
  WiFi.setOutputPower(20.5);  // max is 20.5 dBm

  // ── FIX 3: Persistent connection mode ────────────────────────────────────
  WiFi.persistent(false);     // don't write credentials to flash every boot
  WiFi.mode(WIFI_STA);        // station only, no AP overhead

  WiFi.begin(ssid, password);
  Serial.print("[WiFi] Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("[WiFi] Connected! IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("[WiFi] Signal strength: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");

  server.on("/",       HTTP_GET, handleRoot);
  server.on("/buzz/0", HTTP_GET, []() { handleBuzzer(0); });  // wallet
  server.on("/buzz/1", HTTP_GET, []() { handleBuzzer(1); });  // keys
  server.on("/buzz/2", HTTP_GET, []() { handleBuzzer(2); });  // medicine
  server.on("/buzz/3", HTTP_GET, []() { handleBuzzer(3); });  // spectacles
  server.on("/buzz/4", HTTP_GET, []() { handleBuzzer(4); });  // stick
  server.on("/buzz/5", HTTP_GET, []() { handleBuzzer(5); });  // watch
  server.on("/stop",   HTTP_GET, handleStop);

  server.onNotFound([]() {
    if (server.method() == HTTP_OPTIONS) {
      addCORSHeaders();
      server.send(204);
    } else {
      server.send(404, "text/plain", "Not Found");
    }
  });

  server.begin();
  Serial.println("[HTTP] Server started on port 81");
}

// ─── Loop ────────────────────────────────────────────────────────────────────
void loop() {
  server.handleClient();

  if (isBuzzing) {
    unsigned long now = millis();
    if (now - lastToggle >= BEEP_INTERVAL) {
      buzzerState = !buzzerState;
      digitalWrite(activeBuzzerPin, buzzerState ? BUZZER_ON : BUZZER_OFF);
      lastToggle = now;
    }
  }
}
