coding arduino ide kontrol ui
#include <WiFi.h>
#include <WebSocketsServer.h>

// === Pin definisi ===
#define BUTTON1_PIN  4     // Push Button 1 (Relay1)
#define BUTTON2_PIN  15    // Push Button 2 (Relay2)
#define RELAY1_PIN   5     // Relay 1 (SSR channel 1)
#define RELAY2_PIN   18    // Relay 2 (SSR channel 2)
#define LED_PIN      2     // LED internal ESP32

// === WiFi ===
const char* ssid     = "NOC";        // ganti dengan SSID WiFi kamu
const char* password = "noc2023!";   // ganti dengan password WiFi kamu

// === WebSocket ===
WebSocketsServer webSocket = WebSocketsServer(81);

// === Status relay ===
bool relay1State = false;
bool relay2State = false;

// === Variabel untuk debounce tombol ===
bool lastButton1 = HIGH;
bool lastButton2 = HIGH;
unsigned long lastDebounce1 = 0;
unsigned long lastDebounce2 = 0;
const unsigned long debounceDelay = 200; // ms

// === Update fisik relay sesuai variabel ===
void updateRelay() {
  digitalWrite(RELAY1_PIN, relay1State ? HIGH : LOW);
  digitalWrite(RELAY2_PIN, relay2State ? HIGH : LOW);

  // LED internal ikut ON jika salah satu relay aktif
  digitalWrite(LED_PIN, (relay1State || relay2State) ? HIGH : LOW);
}

// === Kirim status ke Node-RED ===
void notifyClients() {
  String msg;
  msg += (relay1State ? "ON1" : "OFF1");
  msg += ",";
  msg += (relay2State ? "ON2" : "OFF2");

  Serial.println("Kirim status ke client: " + msg);
  webSocket.broadcastTXT(msg);
}

// === Event WebSocket ===
void onEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.printf("Client %u connected\n", num);
      notifyClients(); // kirim status awal ke dashboard
      break;

    case WStype_DISCONNECTED:
      Serial.printf("Client %u disconnected\n", num);
      break;

    case WStype_TEXT: {
      String cmd = String((char*)payload);
      cmd.trim();
      Serial.println("Pesan dari client: [" + cmd + "]");

      if (cmd == "ON1") relay1State = true;
      else if (cmd == "OFF1") relay1State = false;
      else if (cmd == "ON2") relay2State = true;
      else if (cmd == "OFF2") relay2State = false;

      updateRelay();
      notifyClients();
      break;
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);

  // Awal semua relay OFF
  relay1State = false;
  relay2State = false;
  updateRelay();

  // === WiFi connect ===
  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi connected. IP: ");
  Serial.println(WiFi.localIP());  // <-- catat IP ini untuk Node-RED

  // === WebSocket start ===
  webSocket.begin();
  webSocket.onEvent(onEvent);
}

void loop() {
  webSocket.loop();

  unsigned long now = millis();

  // === Push Button 1 (Relay1) ===
  int btn1 = digitalRead(BUTTON1_PIN);
  if (btn1 == LOW && lastButton1 == HIGH && (now - lastDebounce1 > debounceDelay)) {
    relay1State = !relay1State;   // toggle
    updateRelay();
    notifyClients();
    lastDebounce1 = now;
  }
  lastButton1 = btn1;

  // === Push Button 2 (Relay2) ===
  int btn2 = digitalRead(BUTTON2_PIN);
  if (btn2 == LOW && lastButton2 == HIGH && (now - lastDebounce2 > debounceDelay)) {
    relay2State = !relay2State;   // toggle
    updateRelay();
    notifyClients();
    lastDebounce2 = now;
  }
  lastButton2 = btn2;
}