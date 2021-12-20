#include "../inc/cfg.h"
#include <WiFi.h>
#include <MQTT.h>

#include <WiFi.h>
#include <MQTT.h>

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("esp32_sergei_controlstol", mqttlogin, mqttpassword)) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  if(client.subscribe("Zigbee0EF8/0x00124B002258EA7E/state_l1")) {
    Serial.println("Subscribe L1");
  } else {
    Serial.println("NoSubscribe L1");
  }
  if(client.subscribe("Zigbee0EF8/0x00124B002258EA7E/state_l2")) {
    Serial.println("Subscribe L2");
  } else {
    Serial.println("NoSubscribe L2");
  }
  if(client.subscribe("Zigbee0EF8/0x00124B002258EA7E/state_l3")) {
    Serial.println("Subscribe L3");
  } else {
    Serial.println("NoSubscribe L3");
  }
  if(client.subscribe("Zigbee0EF8/0x00124B002258EA7E/state_l4")) {
    Serial.println("Subscribe L4");
  } else {
    Serial.println("NoSubscribe L4");
  }
  if(client.subscribe("Zigbee0EF8/0x00124B002258EA7E/state_l5")) {
    Serial.println("Subscribe L5");
  } else {
    Serial.println("NoSubscribe L5");
  }
  if(client.subscribe("Zigbee0EF8/0x00124B002258EA7E/state_l6")) {
    Serial.println("Subscribe L6");
  } else {
    Serial.println("NoSubscribe L6");
  }
  if(client.subscribe("Zigbee0EF8/0x00124B002258EA7E/state_l7")) {
    Serial.println("Subscribe L7");
  } else {
    Serial.println("NoSubscribe L7");
  }
  if(client.subscribe("Zigbee0EF8/0x00124B002258EA7E/state_l8")) {
    Serial.println("Subscribe L8");
  } else {
    Serial.println("NoSubscribe L8");
  }
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
  // by Arduino. You need to set the IP address directly.
  client.begin(mqttserver, net);
  client.onMessage(messageReceived);

  connect();
  //client.publish("Zigbee0EF8/0x00124B002258EA7E/set/state_l1","ON");
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }
}