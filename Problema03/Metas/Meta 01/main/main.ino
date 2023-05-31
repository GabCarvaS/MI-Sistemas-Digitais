#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>

#ifndef STASSID
#define STASSID "INTELBRAS"
#define STAPSK  "Pbl-Sistemas-Digitais"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
const char* host = "ESP-10.0.0.107";

// MQTT broker credentials (set to NULL if not required)
const char* MQTT_username = "aluno"; 
const char* MQTT_password = "@luno*123"; 

// Change the variable to your Raspberry Pi IP address, so it connects to your MQTT broker
const char* mqtt_server = "10.0.0.101";
//For example
//const char* mqtt_server = "192.168.1.106";

int led_pin = LED_BUILTIN;
#define N_DIMMERS 3
int dimmer_pin[] = {14, 5, 15};

WiFiClient espClient;
PubSubClient client(espClient);

// Timers auxiliar variables
long now = millis();
long lastMeasure = 0;

/* Comandos */
//#define situacaoSensor  0b00000001 // 01
#define todasEntradas  0b00000001 // 01
#define entradaAnalogica  0b00010001 //17
#define entradaDigital0  0b00010010 //18
#define entradaDigital1  0b00010011
#define entradaDigital2  0b00010100
#define entradaDigital3  0b00010101
#define entradaDigital4  0b00010110
#define entradaDigital5  0b00010111
#define entradaDigital6  0b00011000
#define entradaDigital7  0b00011001
#define entradaDigital8  0b00011010
#define entradaDigital9  0b00011011
#define entradaDigital10  0b00011100
#define entradaDigital11  0b00011101
#define entradaDigital12  0b00011110
#define entradaDigital13  0b00011111 //31
#define acenderLed  0b00100001 // 33

/* Respostas */
#define	problemaNode 0b00000001 // 1
#define okNode 0b00000010 // 2
#define estadoSensorDigital 0b00010010 // 18

/* Unidade */
#define Node01 0b00100011 // 35 

void setup() {
  
  /* switch on led */
  pinMode(led_pin, OUTPUT);
  
  Serial.begin(9600); // BaudRate
  
  //Serial.println("Booting");
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    //Serial.println("Tentando nova conexão...");
  }
  /* switch off led */
  digitalWrite(led_pin, HIGH);

  /* configure dimmers, and OTA server events */
  analogWriteRange(1000);
  analogWrite(led_pin, 990);

  for (int i = 0; i < N_DIMMERS; i++) {
    pinMode(dimmer_pin[i], OUTPUT);
    analogWrite(dimmer_pin[i], 50);
  }

  ArduinoOTA.setHostname(host);
  ArduinoOTA.onStart([]() { // switch off all the PWMs during upgrade
    for (int i = 0; i < N_DIMMERS; i++) {
      analogWrite(dimmer_pin[i], 0);
    }
    analogWrite(led_pin, 0);
  });

  ArduinoOTA.onEnd([]() { // do a fancy thing with our board led at end
    for (int i = 0; i < 30; i++) {
      analogWrite(led_pin, (i * 100) % 1001);
      delay(50);
    }
  });

  ArduinoOTA.onError([](ota_error_t error) {
    (void)error;
    ESP.restart();
  });

  /* setup the OTA server */
  ArduinoOTA.begin();
  //Serial.println("Tudo pronto.");
  digitalWrite(led_pin, HIGH);

  client.setServer(mqtt_server, 1883); // 1183 é a porta do servidor?
  client.setCallback(callback);
}

// This function is executed when some device publishes a message to a topic that your ESP8266 is subscribed to
// Change the function below to add logic to your program, so when a device publishes a message to a topic that 
// your ESP8266 is subscribed you can actually do something
void callback(String topic, byte* message, unsigned int length) {
/*
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
*/
  // If a message is received on the topic, you check if the message is either on or off. Turns the led_pin GPIO according to the message
  
  if(topic=="aoba"){
      digitalWrite(led_pin, LOW);
      delay(1000);
      digitalWrite(led_pin, HIGH);
    /*
      if(messageTemp == "on"){
        digitalWrite(led_pin, HIGH);
      }
      else if(messageTemp == "off"){
        digitalWrite(led_pin, LOW);
      }
    */
  }
}

// This functions reconnects your ESP8266 to your MQTT broker
// Change the function below if you want to subscribe to more topics with your ESP8266 
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    // Attempt to connect
    if (client.connect("ESP8266Client", MQTT_username, MQTT_password)) {
      // Subscribe or resubscribe to a topic
      // You can subscribe to more topics (to control more LEDs in this example)
      client.subscribe("aoba");
    } else {
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

/* Variáveis auxiliares*/
unsigned char valorLido;

void loop() { 
  ArduinoOTA.handle();
  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266Client", MQTT_username, MQTT_password);
    now = millis();
  // Publishes new value every 30 seconds
  if (now - lastMeasure > 30000) {
    lastMeasure = now;
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float value = digitalRead(D0);

    // Check if the read failed and exit early (to try again).
    if (isnan(value)) {
      return;
    }

    // Publishes the read value
    client.publish("aoba/digital", String(value).c_str());
  /*
  if(Serial.available() > 0) { // Verifica se recebeu algo da OrangePi
      char c = Serial.read();  // Le o pino RX
      switch(c){
        case Node01:
          // Confirma selecao
          Serial.write(okNode);        
          break;
        case acenderLed: 
          // Alterna o estado do led
          if(digitalRead(led_pin) == HIGH){
            digitalWrite(led_pin, LOW);
          }
          else if(digitalRead(led_pin) == LOW){
            digitalWrite(led_pin, HIGH);
          }
          Serial.write(okNode);        
          break;
        case entradaAnalogica:
          // Falta implementar
          Serial.write(okNode);
          break;
        case todasEntradas:
          // Falta implementar
          Serial.write(okNode);
          break;
        case entradaDigital0:
          valorLido =  digitalRead(D0);
          Serial.write(valorLido);
          break;
        case entradaDigital1:
          valorLido =  digitalRead(D1);
          Serial.write(valorLido);
          break;
        case entradaDigital2:
          valorLido =  digitalRead(D2);
          Serial.write(valorLido);
          break;
        case entradaDigital3:
          valorLido =  digitalRead(D3);
          Serial.write(valorLido);
          break;
        case entradaDigital4:
          valorLido =  digitalRead(D4);
          Serial.write(valorLido);
          break;
        case entradaDigital5:
          valorLido =  digitalRead(D5);
          Serial.write(valorLido);
          break;
        case entradaDigital6:
          valorLido =  digitalRead(D6);
          Serial.write(valorLido);
          break;
        case entradaDigital7:
          valorLido =  digitalRead(D7);
          Serial.write(valorLido);
          break;
        case entradaDigital8:
          valorLido =  digitalRead(D8);
          Serial.write(valorLido);
          break;
        case entradaDigital9:
          valorLido =  digitalRead(D9);
          Serial.write(valorLido);
          break;
      } 
  }
  */
  }
}
