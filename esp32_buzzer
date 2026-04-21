/*
  ============================================================
  ESP8266 Keyword Buzzer - WiFi WebSocket Server
  ============================================================
  Buzzer positive → D7 (GPIO13)
  Buzzer negative → GND
  
  The ESP8266 hosts a WebSocket server on port 81.
  The web app connects and sends keyword strings.
  If the keyword matches, buzzer beeps.
  If "stop" is received, buzzer stops.
  ============================================================
*/

#include <ESP8266WiFi.h>  // Changed from WiFi.h
#include <WebSocketsServer.h>
#include <Arduino.h>

// ─── CONFIGURE THESE ───────────────────────────────────────
const char* SSID     = "JESUS";
const char* PASSWORD = "maximum_effort";

// Keywords that trigger the buzzer (lowercase for easy matching)
const String TRIGGER_KEYWORDS[] = {
  "alarm",
  "buzzer",
  "alert",
  "ring",
  "find"
};
const int KEYWORD_COUNT = 5;

// Stop keywords
const String STOP_KEYWORDS[] = {
  "stop",
  "silence",
  "quiet",
  "off",
  "mute"
};
const int STOP_COUNT = 5;
// ───────────────────────────────────────────────────────────

const int BUZZER_PIN = 13;  // D7 on most NodeMCU/ESP8266 boards = GPIO13
bool buzzerActive = false;

WebSocketsServer webSocket = WebSocketsServer(81);

// ── Helper: convert string to lowercase ───────────────────
String toLowerCase(String s) {
  s.toLowerCase();
  return s;
}

// ── Helper: check if text contains a keyword ──────────────
bool containsKeyword(String text, const String* keywords, int count) {
  text = toLowerCase(text);
  for (int i = 0; i < count; i++) {
    if (text.indexOf(keywords[i]) != -1) {
      return true;
    }
  }
  return false;
}

// ── Buzzer control ─────────────────────────────────────────
void startBuzzer() {
  buzzerActive = true;
  Serial.println("[BUZZER] ACTIVATED");
}

void stopBuzzer() {
  buzzerActive = false;
  digitalWrite(BUZZER_PIN, LOW);
  noTone(BUZZER_PIN); // Changed from ledcWriteTone(0,0)
  Serial.println("[BUZZER] STOPPED");
}

// ── WebSocket event handler ────────────────────────────────
void onWebSocketEvent(uint8_t clientNum, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED: {
      IPAddress ip = webSocket.remoteIP(clientNum);
      Serial.printf("[WS] Client #%u connected from %s\n", clientNum, ip.toString().c_str());
      webSocket.sendTXT(clientNum, "{\"status\":\"connected\",\"message\":\"ESP8266 Buzzer Ready\"}");
      break;
    }

    case WStype_DISCONNECTED:
      Serial.printf("[WS] Client #%u disconnected\n", clientNum);
      break;

    case WStype_TEXT: {
      String msg = String((char*)payload);
      Serial.printf("[WS] Received: %s\n", msg.c_str());

      if (containsKeyword(msg, STOP_KEYWORDS, STOP_COUNT)) {
        stopBuzzer();
        webSocket.broadcastTXT("{\"status\":\"stopped\",\"message\":\"Buzzer stopped\"}");
      } else if (containsKeyword(msg, TRIGGER_KEYWORDS, KEYWORD_COUNT)) {
        startBuzzer();
        webSocket.broadcastTXT("{\"status\":\"triggered\",\"message\":\"Buzzer activated\"}");
      } else {
        webSocket.sendTXT(clientNum, "{\"status\":\"no_match\",\"message\":\"Keyword not recognized\"}");
        Serial.println("[WS] No keyword match");
      }
      break;
    }

    default:
      break;
  }
}

// ── Setup ──────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  delay(500);

  // Standard pin setup for ESP8266 (removed ledcAttach)
  pinMode(BUZZER_PIN, OUTPUT);

  // Connect to WiFi
  Serial.printf("\n[WIFI] Connecting to %s", SSID);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n[WIFI] Connected!");
  Serial.print("[WIFI] IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("[WIFI] Copy this IP into the web app!");

  // Start WebSocket server
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);
  Serial.println("[WS] WebSocket server started on port 81");
}

// ── Loop ───────────────────────────────────────────────────
void loop() {
  webSocket.loop();

  // Buzzer beeping pattern when active
  if (buzzerActive) {
    tone(BUZZER_PIN, 2000);  // Play 2kHz tone on the buzzer pin
    delay(300);
    noTone(BUZZER_PIN);      // Silence the buzzer
    delay(200);
  }
}
