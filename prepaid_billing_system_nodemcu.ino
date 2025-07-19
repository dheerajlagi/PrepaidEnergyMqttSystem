#include<ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define SDA D5
#define SCL D6

#define light D3
#define motor1 D4

#define buz D2

#define WLAN_SSID    "WIFI_USERNAME"
#define WLAN_PASS    "WIFI_PASSWORD"

#define AIO_SERVER  "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "YOUR_USERNAME"
#define AIO_KEY  "AIOKEY"

WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe amt = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/Amount");

void MQTT_connect();

float amount=0;
bool ck=false;
float per=0;

void setup()
{
  Wire.begin(int(SDA), int(SCL));
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(F(" Prepaid Energy "));
  lcd.setCursor(0,1);
  lcd.print(F("     System     "));
  Serial.begin(9600);
  Serial.println("    ");
  pinMode(motor1,OUTPUT);
  pinMode(light,OUTPUT);
  pinMode(buz,OUTPUT);
  digitalWrite(motor1,HIGH);
  digitalWrite(light,HIGH);
  digitalWrite(buz,LOW);
  WiFi.begin(WLAN_SSID,WLAN_PASS);
  while (WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
  }
  lcd.clear();
  lcd.print(F("Connected WiFi...."));
  mqtt.subscribe(&amt);
  delay(2000);
  lcd.clear();
 }

void loop()
{
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while((subscription = mqtt.readSubscription(1000))) {
    if (subscription == &amt) 
    {
      ck=false;
      per=0;
      int rx_state = atoi((char *)amt.lastread);
      lcd.clear();
      lcd.print(F("Amount Received="));
      lcd.setCursor(0,1);
      amount=rx_state;
      lcd.print(amount);
      delay(1000);
      lcd.clear();
      while(amount>0)
      {
      lcd.setCursor(0,0);
      lcd.print(F("Amount="));
      lcd.print(amount);
      lcd.print(F("       "));
      lcd.setCursor(0,1);
      lcd.print(F("Percentage="));
      lcd.print(per);
      lcd.print(F("%"));
      lcd.print(F("   "));
      digitalWrite(light, LOW);
      digitalWrite(motor1,LOW);
      delay(1000);
      amount=amount-1;
      per=((amount/rx_state)*100);
      if((per<=20) && (ck==false))
      {
        digitalWrite(buz,HIGH);
        lcd.clear();
        lcd.print(per);
        lcd.print(F("%energy consumed"));
        lcd.setCursor(0,1);
        lcd.print(F("sending to BT...."));
        Serial.println(F("80% energy comsumed"));
        ck=true;
        delay(2000);
        digitalWrite(buz,LOW);
        lcd.clear();
      }
      }
      if(amount==0)
      {
        lcd.clear();
        lcd.print(F("No Amount"));
        lcd.setCursor(0,1);
        lcd.print(F("Devices OFF"));
        digitalWrite(light, HIGH);
      digitalWrite(motor1,HIGH);
      delay(2000);
      lcd.clear();
      }
    }
  }
}

void MQTT_connect()
{
  int8_t ret;
  if (mqtt.connected())
  {
    return;
  }
  uint8_t retries = 3;

  while((ret = mqtt.connect())!=0)
  {
    mqtt.disconnect();
    delay(5000);
    retries--;
    if(retries == 0)
    {
      while(1);
    }
  }
}
