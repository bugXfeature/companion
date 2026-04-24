#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// ─── WiFi Credentials ───────────────────────────────────────────────────────
const char* ssid     = "JESUS";
const char* password = "maximum_effort";

// ─── Buzzer Pin Mapping (ESP8266 GPIO numbers) ───────────────────────────────
// D0 = GPIO16, D1 = GPIO5, D2 = GPIO4, D3 = GPIO0,
// D4 = GPIO2,  D5 = GPIO14
#define BUZZER_D0  16   // "wallet"
#define BUZZER_D1   5   // "one"
#define BUZZER_D2   4   // "two"
#define BUZZER_D3   0   // "three"
#define BUZZER_D4   2   // "four"
#define BUZZER_D5  14   // "five"

const int buzzerPins[6] = {
  BUZZER_D0, BUZZER_D1, BUZZER_D2,
  BUZZER_D3, BUZZER_D4, BUZZER_D5
};

// Beep interval (ms) – buzzer toggles every BEEP_INTERVAL ms until /stop
#define BEEP_INTERVAL 300

ESP8266WebServer server(81);

// ─── Continuous-buzz state ────────────────────────────────────────────────────
bool  isBuzzing       = false;
int   activeBuzzerPin = -1;
bool  buzzerState     = false;
unsigned long lastToggle = 0;

// Start continuous beep on a pin (stops any previous buzzer first)
void startBuzzer(int pin) {
  if (activeBuzzerPin >= 0) digitalWrite(activeBuzzerPin, LOW); // stop old
  activeBuzzerPin = pin;
  isBuzzing       = true;
  buzzerState     = true;
  digitalWrite(pin, HIGH);   // fire immediately — no waiting for loop
  lastToggle      = millis();
}

// Stop all buzzers
void stopBuzzer() {
  if (activeBuzzerPin >= 0) digitalWrite(activeBuzzerPin, LOW);
  isBuzzing       = false;
  activeBuzzerPin = -1;
  buzzerState     = false;
}

// ─── CORS helper ─────────────────────────────────────────────────────────────
void addCORSHeaders() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
}

// ─── Route handlers ──────────────────────────────────────────────────────────
void handleBuzzer(int index) {
  addCORSHeaders();
  startBuzzer(buzzerPins[index]);
  server.send(200, "text/plain", "OK");
}

void handleStop() {
  addCORSHeaders();
  stopBuzzer();
  server.send(200, "text/plain", "STOPPED");
}

void handleRoot() {
  // Serve a minimal redirect page; the real UI is the index.html served locally
  addCORSHeaders();
  server.send(200, "text/plain", "ESP8266 6-Buzzer Server Running");
}

// ─── Setup ───────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);

  // Initialise all buzzer pins as OUTPUT and set LOW
  for (int i = 0; i < 6; i++) {
    pinMode(buzzerPins[i], OUTPUT);
    digitalWrite(buzzerPins[i], LOW);
  }

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());

  // ── Register routes ────────────────────────────────────────────────────────
  server.on("/",        HTTP_GET, handleRoot);

  // D0 → "wallet"
  server.on("/buzz/0",  HTTP_GET, []() { handleBuzzer(0); });
  // D1 → "one"
  server.on("/buzz/1",  HTTP_GET, []() { handleBuzzer(1); });
  // D2 → "two"
  server.on("/buzz/2",  HTTP_GET, []() { handleBuzzer(2); });
  // D3 → "three"
  server.on("/buzz/3",  HTTP_GET, []() { handleBuzzer(3); });
  // D4 → "four"
  server.on("/buzz/4",  HTTP_GET, []() { handleBuzzer(4); });
  // D5 → "watch"
  server.on("/buzz/5",  HTTP_GET, []() { handleBuzzer(5); });

  // Stop all buzzers (voice command: "stop")
  server.on("/stop",    HTTP_GET, handleStop);

  // Handle preflight OPTIONS for CORS
  server.onNotFound([]() {
    if (server.method() == HTTP_OPTIONS) {
      addCORSHeaders();
      server.send(204);
    } else {
      server.send(404, "text/plain", "Not Found");
    }
  });

  server.begin();
  Serial.println("HTTP server started");
}

// ─── Loop ────────────────────────────────────────────────────────────────────
void loop() {
  server.handleClient();

  // Non-blocking buzzer toggling
  if (isBuzzing) {
    unsigned long now = millis();
    if (now - lastToggle >= BEEP_INTERVAL) {
      buzzerState = !buzzerState;
      digitalWrite(activeBuzzerPin, buzzerState ? HIGH : LOW);
      lastToggle = now;
    }
  }
}
