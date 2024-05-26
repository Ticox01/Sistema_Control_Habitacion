/*
EQUIPOS E INSTRUMENTACIÓN ELECTRÓNICA
Nombre del grupo:
- Juan José
- Carlon
- Tico
*/

#include <LiquidCrystal_I2C.h>      // Biblioteca de pantalla LCD con I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // Iniciar pantalla LCD, 16 caractares por línea y 2 líneas.
#include <dht11.h>                  // Biblioteca Sensor de Temperatura + Humedad

#define BUTTON_B A3 // A3 como boton

// INTERIOR
#define LDR_PIN_EXT A1   // Pin analógico A0 para LDR
const float GAMMA = 0.7; // Valor de la constante gamma para el cálculo de iluminación
const float RL10 = 50;   // Valor de resistencia de referencia
int ledPin_ext = 13;

// INTERIOR
dht11 DHT11;           // Crear Objeto para sensor DHT 11
#define LDR_PIN_INT A2 // Definir pin digital para alarma de sensor LDR
#define DHT11PIN 12    // Definir pin digital para DHT11

// TEMPERATURA OBJETIVO
int T_obj = 20;

// Simbolo LCD Temperatura y Estrella
byte temp[8] = {
    B00100, B01010, B01010, B01110, B01110, B11111, B11111, B01110};
byte lum[8] = {
    B00000, B00100, B01110, B11111, B01110, B00100, B00000, B00000};

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();

    // Externo
    pinMode(LDR_PIN_EXT, INPUT);
    pinMode(ledPin_ext, OUTPUT);

    // Interior
    pinMode(LDR_PIN_INT, INPUT);

    pinMode(BUTTON_B, INPUT_PULLUP); // Boton de 4 modos con resistencia pull-up

    lcd.createChar(1, temp);
    lcd.createChar(2, lum);
}

void loop()
{
    // lee el estado del boton  ///////////////////////////////
    bool btnState = !digitalRead(BUTTON_B);

    // verifica si esta presionado
    if (btnState && !flag && millis() - btnTimer > 100)
    {
        flag = true;
        btnTimer = millis();
        Serial.println("press");
        count += 1;
        mode = count % 4;
        Serial.println(count);
    }

    // Reinicia el estado del boton
    if (!btnState && flag && millis() - btnTimer > 100)
    {
        flag = false;
        btnTimer = millis();
    }

    Serial.print(mode);
    //////////////////////////////////////
    // EXTERNO
    lcd.clear();
    int value = analogRead(A0);
    float volts = (value * 5) / 1023.0;
    float T_ext = volts * 100;
    int lux_ext = analogRead(A1);

    // Interior
    int DTH_int = DHT11.read(DHT11PIN);
    int lux_int = analogRead(A2);

    exterior(lux_ext);

    if (mode == 0)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PRACTICA 2");
    }
    if (mode == 0)
    {
        pantalla_exterior(lux_ext, T_ext);
    }
    if (mode == 1)
    {
        pantalla_interior(lux_int, DTH_int);
    }

    // if (T_obj = T_int){
    // // perfe
    // }
    // if (T_obj < T_int && T_obj < T_ext){
    // //
    // }
    // if (T_obj < T_int && T_obj > T_ext){
    // // perfe
    // }
    // if (T_obj > T_int && T_obj < T_ext){
    // // perfe
    // }
    // if (T_obj > T_int && T_obj > T_ext){
    // // perfe
    // }
}
void exterior(int lux_ext)
{
    if (lux_ext > 650)
    {
        analogWrite(ledPin_ext, 0);
    }
    if (lux_ext < 650)
    {
        analogWrite(ledPin_ext, 255);
    }

    void interior()
    {
        // if (T_obj = T_int){
        // // perfe
        // }
        // if (T_obj < T_int && T_obj < T_ext){
        // //
        // }
        // if (T_obj < T_int && T_obj > T_ext){
        // // perfe
        // }
        // if (T_obj > T_int && T_obj < T_ext){
        // // perfe
        // }
        // if (T_obj > T_int && T_obj > T_ext){
        // // perfe
        // }
    }
}
void pantalla_interior(int lux_int, int T_int, int H_int)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Interior");
    lcd.print(" ");
    lcd.print((float)DHT11.humidity, 2);
    lcd.setCursor(0, 1);
    lcd.write(1); //
    lcd.print(" ");
    lcd.print((float)DHT11.temperature, 2);
    lcd.print(" C ");
    lcd.write(2);
    lcd.print(" ");
    lcd.print(lux_int, 1);
    lcd.print(" lx");
    delay(1000);
}
void pantalla_exterior(int lux_ext, int celsius)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Exterior");
    lcd.setCursor(0, 1);
    lcd.write(1); //
    lcd.print(" ");
    lcd.print(celsius);
    lcd.print(" C ");
    lcd.write(2);
    lcd.print(" ");
    lcd.print(lux_ext, 1);
    lcd.print(" lx");
    delay(1000);
}
