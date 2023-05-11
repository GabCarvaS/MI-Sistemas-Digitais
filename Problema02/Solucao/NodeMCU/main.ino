#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "INTELBRAS"
#define STAPSK  "Pbl-Sistemas-Digitais"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
const char* host = "ESP-10.0.0.109";

int led_pin = LED_BUILTIN;
#define N_DIMMERS 3
int dimmer_pin[] = {14, 5, 15};

//........Tabela 01 - Comandos........
#define situacaoSensor  0b00000001 // 01
#define entradaAnalogica  0b00010001 //17 -> Potenciometro
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



void setup() {
  
  /* switch on led */
  pinMode(led_pin, OUTPUT);
  pinMode(D0, INPUT);

  pinMode(D1,INPUT); //botão
  
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
}

void loop() { 
  ArduinoOTA.handle();
  digitalWrite(led_pin, HIGH);
  
    /* Via loopback */
  char comando = 0b00100001;
  Serial.write(comando);
  delay(5000);
  if(Serial.available() > 0) { // Verifica se tem algo sendo recebido
      char c = Serial.read();  //Lê o pino RX
      switch(c){
        case acende_led:
         //Serial.write("Chegou");
          digitalWrite(led_pin, LOW);
          delay(2000);
          break;
      } 
  }
}
