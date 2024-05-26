/*
EQUIPOS E INSTRUMENTACIÓN ELECTRÓNICA
Nombre del grupo:
- Juan José
- Carlon
- Tico
*/

#include <LiquidCrystal_I2C.h> // Biblioteca de pantalla LCD con I2C
LiquidCrystal_I2C lcd(0x27,16,2);  // Iniciar pantalla LCD, 16 caractares por línea y 2 líneas.

//EXTERNO
#define LDR_PIN_EXT A1 // Pin analógico A0 para LDR
const float GAMMA = 0.7; // Valor de la constante gamma para el cálculo de iluminación
const float RL10 = 50; // Valor de resistencia de referencia
int ledPin_ext = 13;


// Simbolo LCD Temperatura
byte temp[8] = { 
  B00100, B01010, B01010, B01110, B01110, B11111, B11111, B01110 
};

// Simbolo LCD Estrella
byte lum[8] = {  
  B00000, B00100, B01110, B11111, B01110, B00100, B00000, B00000 
};

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 lcd.init();
 lcd.backlight();

 // Externo
 pinMode(LDR_PIN_EXT,INPUT);
 pinMode(ledPin_ext,OUTPUT);
 lcd.createChar(1,temp);
 lcd.createChar(2,lum);
}

void loop() {
  // EXTERNO
  lcd.clear();
  int value = analogRead(A0);
  float volts = (value*5)/1023.0;
  float T_ext = volts * 100;
   // calculo de iluminación
  int lux_ext = analogRead(A1);
  // float voltage = (lux_ext* 5)/10233;
  // float resistance = 2000 * voltage / (1 - voltage / 5);
  // float alux_ext = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA)); //Cálculo de iluminación
  exterior(lux_ext);
  pantalla_exterior(lux_ext,T_ext);

if (T_obj = T_int){
  // perfe
}
if (T_obj < T_int && T_obj < T_ext){
  // 
}
if (T_obj < T_int && T_obj > T_ext){
  // perfe
}
if (T_obj < T_int && T_obj < T_ext){
  // perfe
}





  
}
void exterior(int lux_ext){
  if(lux_ext > 650){
    analogWrite(ledPin_ext, 0);
  }
    if(lux_ext < 650){
    analogWrite(ledPin_ext, 255);
  }


}
void pantalla_exterior(int lux_ext, int celsius){
  lcd.setCursor(0,0);

  lcd.print("Exterior");
  lcd.setCursor(0,1);
  lcd.write(1); // 
  lcd.print(" ");
  lcd.print(celsius);
  lcd.print(" C ");
  lcd.write(2);
  lcd.print(" ");
  lcd.print(lux_ext,1);
  lcd.print(" lx");
  delay(1000);  
}