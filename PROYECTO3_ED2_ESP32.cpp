//**
// UVG Proyecto 3 - ED2
// Campaneros 211054
// ESP32
//**
//**
// Librerías
//**ç
#include <Arduino.h>
#include <Temperature_LM75_Derived.h>
#include <Adafruit_NeoPixel.h>
#ifdef AVR
    #include <avr/power.h>
#endif
//**
// Definición de etiquetas
//**
#define PIN 5 //Pin  para el NeoPixel
//**
// Prototipos de funciones
//**
void colorWipe(uint32_t c, uint8_t wait);

//**
// Variables Globales
//**
Generic_LM75 temperature;
int solicitar;
float temp;
//**
// ISR: Interrupciones
//**
// void IRAM_ATTR ISR(){
//
//}
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);
//**
// Configuración
//**
void setup() {
  Serial.begin(115200); //Inicio Comunicación Serial del ESP32 a la Compu
  Serial2.begin(115200); //Inicio Comunicación Serial del ESP32 <-> TivaC
  Wire.begin(); //Inicio comunicación I2C

  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Inicia el NeoPixel en OFF
  
}
//**
// Loop Principal
//**
void loop() {
  //Parte 1 - ESP32 Y Sensor con I2C  y  Parte 2 - Comunicación UART con ESP32<->TivaC
  //Parte 5 - Indicador visual
  //Recibir datos
  if(Serial2.available()>0){
    solicitar =Serial2.parseInt();
  }
  //Serial.println(solicitar);
  //Transmitir datos
  if(solicitar==1){
    //Envia la medición de la temperatura a la tivaC
    temp = temperature.readTemperatureC();
    Serial2.print(temp); 
    //Envia la medición de la temperatura al monitor serial
    Serial.print("Temperatura = ");
    Serial.print(temp);
    Serial.println("°C");    
    colorWipe(strip.Color(0, 0, 176), 10); //Indica que he realizado la medición
    //delay(100);
  }
  if(solicitar==0){
    colorWipe(strip.Color(128, 0, 128), 0); //Indica que he realizado la medición
  }
  if(solicitar==2){
    colorWipe(strip.Color(0, 135, 0), 10); // indica que se ha almacenado la medición en la SD
  }
}
//**
// Funciones
//**
// Rellena los puntos uno tras otro con un color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}