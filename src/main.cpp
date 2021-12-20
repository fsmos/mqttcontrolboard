#include "../inc/cfg.h"
#include <WiFi.h>
#include <MQTT.h>

#include <WiFi.h>
#include <MQTT.h>

#include "Nextion.h"
WiFiClient net;
MQTTClient client;

NexPage main = NexPage(0, 0, "main");
NexNumber main_tu = NexNumber(0, 10, "tu");
NexNumber main_th = NexNumber(0, 11, "th");
NexNumber main_hm = NexNumber(0, 12, "hm");
NexNumber main_pr = NexNumber(0, 13, "pr");
NexNumber main_t1 = NexNumber(0, 1, "t1");
NexNumber main_t2 = NexNumber(0, 3, "t2");
NexPage cfg = NexPage(1, 0, "cfg");
NexDSButton cfg_uhf = NexDSButton(1, 2, "uhf");
NexDSButton cfg_hf = NexDSButton(1, 5, "hf");
NexDSButton cfg_lbp10a = NexDSButton(1, 3, "lbp10a");
NexDSButton cfg_tlbp = NexDSButton(1, 7, "tlbp");
NexDSButton cfg_lbp1 = NexDSButton(1, 6, "lbp1");
NexDSButton cfg_lbp2 = NexDSButton(1, 8, "lbp2");
NexDSButton cfg_comp = NexDSButton(1, 9, "comp");
NexDSButton cfg_osl = NexDSButton(1, 4, "osl");
NexDSButton cfg_gen = NexDSButton(1, 10, "gen");

NexTouch *nex_listen_list[] = {
    &cfg_uhf, &cfg_hf, &cfg_lbp10a, &cfg_lbp1, &cfg_lbp2, &cfg_comp, &cfg_osl, &cfg_gen, NULL};
unsigned long lastMillis = 0;

void connect()
{
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("esp32_sergei_controlstol", mqttlogin, mqttpassword))
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  if (client.subscribe("Zigbee0EF8/0x00124B002258EA7E/state_l1"))
  {
    Serial.println("Subscribe L1");
  }
  else
  {
    Serial.println("NoSubscribe L1");
  }
  if (client.subscribe("Zigbee0EF8/0x00124B002258EA7E/state_l2"))
  {
    Serial.println("Subscribe L2");
  }
  else
  {
    Serial.println("NoSubscribe L2");
  }
  if (client.subscribe("Zigbee0EF8/0x00124B002258EA7E/state_l3"))
  {
    Serial.println("Subscribe L3");
  }
  else
  {
    Serial.println("NoSubscribe L3");
  }
  if (client.subscribe("Zigbee0EF8/0x00124B002258EA7E/state_l4"))
  {
    Serial.println("Subscribe L4");
  }
  else
  {
    Serial.println("NoSubscribe L4");
  }
  if (client.subscribe("Zigbee0EF8/0x00124B002258EA7E/state_l5"))
  {
    Serial.println("Subscribe L5");
  }
  else
  {
    Serial.println("NoSubscribe L5");
  }
  if (client.subscribe("Zigbee0EF8/0x00124B002258EA7E/state_l6"))
  {
    Serial.println("Subscribe L6");
  }
  else
  {
    Serial.println("NoSubscribe L6");
  }
  if (client.subscribe("Zigbee0EF8/0x00124B002258EA7E/state_l7"))
  {
    Serial.println("Subscribe L7");
  }
  else
  {
    Serial.println("NoSubscribe L7");
  }
  if (client.subscribe("Zigbee0EF8/0x00124B002258EA7E/state_l8"))
  {
    Serial.println("Subscribe L8");
  }
  else
  {
    Serial.println("NoSubscribe L8");
  }
    if (client.subscribe("Zigbee1030/0x00158D00040D381D/state_l1"))
  {
    Serial.println("Subscribe L9");
  }
  else
  {
    Serial.println("NoSubscribe L9");
  }
  client.subscribe("Zigbee1030/0x00124B0022027AEC/pressure");
  client.subscribe("Zigbee1030/0x00124B0022027AEC/temperature");
  client.subscribe("Zigbee1030/0x00124B0022027AEC/humidity");
  client.subscribe("Zigbee1030/0x00158D0004641AB1/temperature");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload)
{
  Serial.println("incoming: " + topic + " - " + payload);
  if (topic == "Zigbee0EF8/0x00124B002258EA7E/state_l1")
  {
    if (payload == "ON")
    {
      cfg_lbp2.setValue(1);
    }
    else if (payload == "OFF")
    {
      cfg_lbp2.setValue(0);
    }
  }
  if (topic == "Zigbee0EF8/0x00124B002258EA7E/state_l2")
  {
    if (payload == "ON")
    {
      cfg_tlbp.setValue(1);
    }
    else if (payload == "OFF")
    {
      cfg_tlbp.setValue(0);
    }
  }
  if (topic == "Zigbee0EF8/0x00124B002258EA7E/state_l3")
  {
    if (payload == "ON")
    {
      cfg_lbp10a.setValue(1);
    }
    else if (payload == "OFF")
    {
      cfg_lbp10a.setValue(0);
    }
  }
  if (topic == "Zigbee0EF8/0x00124B002258EA7E/state_l4")
  {
    if (payload == "ON")
    {
      cfg_osl.setValue(1);
    }
    else if (payload == "OFF")
    {
      cfg_osl.setValue(0);
    }
  }
  if (topic == "Zigbee0EF8/0x00124B002258EA7E/state_l5")
  {
    if (payload == "ON")
    {
      cfg_lbp1.setValue(1);
    }
    else if (payload == "OFF")
    {
      cfg_lbp1.setValue(0);
    }
  }
  if (topic == "Zigbee0EF8/0x00124B002258EA7E/state_l6")
  {
    if (payload == "ON")
    {
      cfg_gen.setValue(1);
    }
    else if (payload == "OFF")
    {
      cfg_gen.setValue(0);
    }
  }
  if (topic == "Zigbee0EF8/0x00124B002258EA7E/state_l7")
  {
    if (payload == "ON")
    {
      cfg_uhf.setValue(1);
    }
    else if (payload == "OFF")
    {
      cfg_uhf.setValue(0);
    }
  }
  if (topic == "Zigbee0EF8/0x00124B002258EA7E/state_l8")
  {
    if (payload == "ON")
    {
      cfg_hf.setValue(1);
    }
    else if (payload == "OFF")
    {
      cfg_hf.setValue(0);
    }
  }
   if (topic == "Zigbee1030/0x00158D00040D381D/state_l1")
  {
    if (payload == "ON")
    {
      cfg_comp.setValue(1);
    }
    else if (payload == "OFF")
    {
      cfg_comp.setValue(0);
    }
  }
  if (topic == "Zigbee1030/0x00124B0022027AEC/pressure")
  {
     main_pr.setValue((uint32_t)(payload.toFloat()*0.75006156130264));
  }
  if (topic == "Zigbee1030/0x00124B0022027AEC/temperature")
  {
     main_th.setValue((uint32_t)(payload.toFloat()));
  }
  if (topic == "Zigbee1030/0x00124B0022027AEC/humidity")
  {
     main_hm.setValue((uint32_t)(payload.toFloat()));
  }
   if (topic == "Zigbee1030/0x00158D0004641AB1/temperature")
  {
     main_tu.setValue((uint32_t)(payload.toFloat()));
  }
}

void cfg_lbp2_Press(void *ptr)
{
  uint32_t val = 0;
  cfg_lbp2.getValue(&val);
  if (val == 1)
  {
    client.publish("Zigbee0EF8/0x00124B002258EA7E/set/state_l1", "ON");
  }
  else
  {
    client.publish("Zigbee0EF8/0x00124B002258EA7E/set/state_l1", "OFF");
  }
}

void cfg_tlbp_Press(void *ptr)
{
  uint32_t val = 0;
  cfg_tlbp.getValue(&val);
  if (val == 1)
  {
    client.publish("Zigbee0EF8/0x00124B002258EA7E/set/state_l2", "ON");
  }
  else
  {
    client.publish("Zigbee0EF8/0x00124B002258EA7E/set/state_l2", "OFF");
  }
}

void cfg_lbp10a_Press(void *ptr)
{
  uint32_t val = 0;
  cfg_lbp10a.getValue(&val);
  if (val == 1)
  {
    client.publish("Zigbee0EF8/0x00124B002258EA7E/set/state_l3", "ON");
  }
  else
  {
    client.publish("Zigbee0EF8/0x00124B002258EA7E/set/state_l3", "OFF");
  }
}

void cfg_osl_Press(void *ptr)
{
  uint32_t val = 0;
  cfg_osl.getValue(&val);
  if (val == 1)
  {
    client.publish("Zigbee0EF8/0x00124B002258EA7E/set/state_l4", "ON");
  }
  else
  {
    client.publish("Zigbee0EF8/0x00124B002258EA7E/set/state_l4", "OFF");
  }
}

void cfg_lbp1_Press(void *ptr)
{
  uint32_t val = 0;
  cfg_lbp1.getValue(&val);
  if (val == 1)
  {
    client.publish("Zigbee0EF8/0x00124B002258EA7E/set/state_l5", "ON");
  }
  else
  {
    client.publish("Zigbee0EF8/0x00124B002258EA7E/set/state_l5", "OFF");
  }
}

void cfg_gen_Press(void *ptr)
{
  uint32_t val = 0;
  cfg_gen.getValue(&val);
  if (val == 1)
  {
    client.publish("Zigbee0EF8/0x00124B002258EA7E/set/state_l6", "ON");
  }
  else
  {
    client.publish("Zigbee0EF8/0x00124B002258EA7E/set/state_l6", "OFF");
  }
}


void cfg_uhf_Press(void *ptr)
{
  uint32_t val = 0;
  cfg_uhf.getValue(&val);
  if (val == 1)
  {
    client.publish("Zigbee0EF8/0x00124B002258EA7E/set/state_l7", "ON");
  }
  else
  {
    client.publish("Zigbee0EF8/0x00124B002258EA7E/set/state_l7", "OFF");
  }
}

void cfg_hf_Press(void *ptr)
{
  uint32_t val = 0;
  cfg_hf.getValue(&val);
  if (val == 1)
  {
    client.publish("Zigbee0EF8/0x00124B002258EA7E/set/state_l8", "ON");
  }
  else
  {
    client.publish("Zigbee0EF8/0x00124B002258EA7E/set/state_l8", "OFF");
  }
}

void cfg_comp_Press(void *ptr)
{
  uint32_t val = 0;
  cfg_comp.getValue(&val);
  if (val == 1)
  {
    client.publish("Zigbee1030/0x00158D00040D381D/state_l1", "ON");
  }
  else
  {
    client.publish("Zigbee1030/0x00158D00040D381D/state_l1", "OFF");
  }
}


void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
  // by Arduino. You need to set the IP address directly.
  client.begin(mqttserver, net);
  client.onMessage(messageReceived);

  connect();
  cfg_lbp2.attachPop(cfg_lbp2_Press, &cfg_lbp2);
  cfg_tlbp.attachPop(cfg_tlbp_Press, &cfg_tlbp);
  cfg_lbp10a.attachPop(cfg_lbp10a_Press, &cfg_lbp10a);
  cfg_osl.attachPop(cfg_osl_Press, &cfg_osl);
  cfg_lbp1.attachPop(cfg_lbp1_Press, &cfg_lbp1);
  cfg_gen.attachPop(cfg_gen_Press, &cfg_gen);
  cfg_uhf.attachPop(cfg_uhf_Press, &cfg_uhf);
  cfg_hf.attachPop(cfg_hf_Press, &cfg_hf);
  cfg_comp.attachPop(cfg_hf_Press, &cfg_comp);
  //client.publish("Zigbee0EF8/0x00124B002258EA7E/set/state_l1","ON");
}

void loop()
{
  client.loop();
  delay(10); // <- fixes some issues with WiFi stability

  if (!client.connected())
  {
    connect();
  }
  nexLoop(nex_listen_list);
}