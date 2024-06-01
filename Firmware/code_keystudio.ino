/*
EQUIPOS E INSTRUMENTACIÓN ELECTRÓNICA
Actividad 2
Nombre del grupo:
 - Juan José Martínez Cámara
 - Carlos Morón Barrios
 - Escolastico Muñoz Pardo
*/

// #include <DHT.h>
#include <dht11.h>
#include <LiquidCrystal_I2C.h>
#include <LowPower.h>
#include <Servo.h>
#include <Stepper.h>

// Declaracion de tipos
// Estructura para guardar las constantes de PID
typedef struct
{
    // Constantes del PID
    float Kp;
    float Ki;
    float Kd;
    float Ts;
} s_pid_constants;

// Estructurta para guardar todo lo necesario sobre el PID
typedef struct
{
    s_pid_constants pid_constants;
    // Variables PID
    float cv, cv1;
    float err, err1, err2;
} s_pid;

// Definiciónd e los pines para los diferentes sensores

// Sensores de temperatura y humedad
#define DHTPIN_INT 13 // Sensor Humedad y Temperaura Interior
dht11 DHT11;
#define LM35_ext A0 // Temperaura Exterior LM35

// Sensores LDR

// Constantes de los LDR
const long A = 1000; // Resistencia en oscuridad en KΩ
const int B = 15;    // Resistencia a la luz (10 Lux) en KΩ
const int Rc = 10;   // Resistencia calibracion en KΩ

// Definicion Pines LDR
#define LDR_INT A2 // Sensor LDR Interior
#define LDR_EXT A1 // Sensor LDR Exterior

// Led gradual para el control de iluminacion
#define LED 6

#define PIR 2 // Sensor PIR

// Pantalla LCD
// Definición de Columnas y filas del LCD
#define COLS 16 // Columnas del LCD
#define ROWS 2  // Filas del LCD

// Inicializacion de pantalla LCD
LiquidCrystal_I2C lcd(0x27, COLS, ROWS);

// Se crea el servo para controlar la apertura y cierre de ventana
Servo ventilacion;
#define PIN_SERVO_VENTILACION 7 // Servo

// Se crea el stepper para controlar las persianas

const int stepsPerRevolution = 2048; // Pasos por revolucion
// Initializacion del stepper motor
Stepper persianas(stepsPerRevolution, 8, 10, 9, 11); // Pines stepper 8,9,10,11

// Ventilador
#define PIN_VENTILADOR_INT 3 // DC motor

// PID variables
float temperature_setpoint = 20;
float light_setpoint = 600;
s_pid pid_temperature = {
    .pid_constants = {.Kp = 10, .Ki = 0.1, .Kd = 0, .Ts = 0.1},
    .cv = 0,
    .cv1 = 0,
    .err = 0,
    .err1 = 0,
    .err2 = 0};

s_pid pid_light = {
    .pid_constants = {.Kp = 0.6, .Ki = 0.005, .Kd = 0, .Ts = 0.1},
    .cv = 0,
    .cv1 = 0,
    .err = 0,
    .err1 = 0,
    .err2 = 0};

// Declaracion de variables globales

// Variables para el timer de deteccion de presencia y para poner en modo bajo consumo

int sleep = 1;
unsigned long start_time_pir = 0, timer_time_pir = 60000;

// Variable para cambiar el estado de la pantalla y para su timer

int state_LCD = 0;
unsigned long start_time_lcd = 0, timer_time_lcd = 3000;

// Declaración de simbolos para LCD

byte tem_icon[8] = {
    B00100, B01010, B01010, B01010, B01010, B10001, B10001, B01110}; // Icono de Temperatura
byte house_icon[8] = {
    B00000, B00100, B01110, B11111, B10001, B10101, B10101, B11111}; // Icono casa para interior
byte sun_icon[8] = {
    B00000, B00000, B10101, B01110, B11111, B01110, B10101, B00000}; // Icono sol para exterior
byte lux_icon[8] = {
    B00000, B01110, B10001, B10001, B10101, B01110, B01110, B00100}; // Icono Iluminación

// Predeclaración de las funciones
void show_temperature(float t_int, float t_ext);
void show_light(float light_int, float light_ext);
void show_pid_setpoint(float temp_setpoint, float light_setpoint);
void go_to_sleep();
void wake_up();
float compute_pid(float input, float setpoint, s_pid *pid);
void control_temperature(float t_int, float t_ext, float setpoint, s_pid *pid);
void control_light(float light_int, float light_ext, float setpoint, s_pid *pid);
void control_lcd_screen(int *state_lcd, unsigned long *start_time, unsigned long timer_time);
void detect_presence(int pir_value, unsigned long *start_time, unsigned long timer_time);
float illumination(float value_read);
float readLM35();

void setup()
{

    // Inicialización de los pines
    Serial.begin(9600);

    pinMode(PIR, INPUT);

    // Inicializacion de los leds de iluminacion
    pinMode(LED, OUTPUT);

    // Apagamos inicialmente
    digitalWrite(LED, LOW);

    // Inicializacion de los servos en posicion cerrada (90º)
    ventilacion.attach(PIN_SERVO_VENTILACION);
    ventilacion.write(90);

    // Ventilador interior
    pinMode(PIN_VENTILADOR_INT, OUTPUT);

    // Inicializar el LCD
    lcd.init();
}

void loop()
{

    // Obtenemos valor de temperatura e iluminacion interior y exterior
    int chk = DHT11.read(DHTPIN_INT); // Temperatura Exterior
    float t_int = (float)DHT11.temperature;

    float t_ext = readLM35(); // Temperatura Exterior
    float light_int = illumination(analogRead(LDR_INT));
    float light_ext = illumination(analogRead(LDR_EXT));

    int pir_value = digitalRead(PIR); // Valor del sensor de presencia

    detect_presence(pir_value, &start_time_pir, timer_time_pir);

    // Modo bajo consumo
    if (sleep)
    {

        lcd.noBacklight(); // Apagamos la Pantalla

        // Ponemos en modo reposo al arduino hasta que se detecte presencia o se pulse el boon
        go_to_sleep();

        sleep = 0;
        lcd.backlight(); // Encendemos la pantalla
    }

    control_lcd_screen(&state_LCD, &start_time_lcd, timer_time_lcd);

    // Maquina de estados para mostrar las diferentes pantallas
    if (state_LCD == 0)
        show_temperature(t_int, t_ext);
    else if (state_LCD == 1)
        show_light(light_int, light_ext);
    else if (state_LCD == 2)
        show_pid_setpoint(temperature_setpoint, light_setpoint);

    // Control de temperatura e iluminación
    control_temperature(t_int, t_ext, temperature_setpoint, &pid_temperature);
    control_light(light_int, light_ext, light_setpoint, &pid_light);

    delay(100);
}

// Funcion para leer temperatura de LM35

float readLM35()
{
    long value = analogRead(LM35_ext);
    float temperatureC = (5.0 * value * 100.0) / 1024.0;
    return temperatureC;
}

// Funcion para mostrar en LCD los valores de temperatura interior y exterior
// @Param
// t_int - Valor de temperatura interior
// t_ext - Valor de temperatura exterior

void show_temperature(float t_int, float t_ext)
{
    lcd.createChar(1, tem_icon);
    lcd.createChar(2, house_icon);
    lcd.createChar(3, sun_icon);
    lcd.setCursor(0, 0);
    lcd.write(1);
    lcd.setCursor(2, 0);
    lcd.write(2);
    lcd.setCursor(4, 0);
    lcd.print(t_int);
    lcd.setCursor(COLS - 1, 0);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.write(1);
    lcd.setCursor(2, 1);
    lcd.write(3);
    lcd.setCursor(4, 1);
    lcd.print(t_ext);
    lcd.setCursor(COLS - 1, 1);
    lcd.print("C");
}

// Funcion para mostrar en LCD los valores de iluminacion interior y exterior
// @Param
// light_int - Valor de iluminacion interior
// light_ext - Valor de iluminacion exterio

void show_light(float light_int, float light_ext)
{
    lcd.createChar(1, lux_icon);
    lcd.createChar(2, house_icon);
    lcd.createChar(3, sun_icon);
    lcd.setCursor(0, 0);
    lcd.write(1);
    lcd.setCursor(2, 0);
    lcd.write(2);
    lcd.setCursor(4, 0);
    lcd.print(light_int);
    lcd.setCursor(COLS - 3, 0);
    lcd.print("Lux");
    lcd.setCursor(0, 1);
    lcd.write(1);
    lcd.setCursor(2, 1);
    lcd.write(3);
    lcd.setCursor(4, 1);
    lcd.print(light_ext);
    lcd.setCursor(COLS - 3, 1);
    lcd.print("Lux");
}

// Funcion para mostrar en LCD los setpoints puestos para el control PID
// @Param
// temp_setpoint - Valor de setpoint de temperatura
// light_setpoint - Valor de setpoint de iluminacion

void show_pid_setpoint(float temp_setpoint, float light_setpoint)
{
    lcd.createChar(1, tem_icon);
    lcd.createChar(2, lux_icon);
    lcd.setCursor(0, 0);
    lcd.write(1);
    lcd.setCursor(2, 0);
    lcd.print("S: ");
    lcd.print(temp_setpoint);
    lcd.setCursor(COLS - 1, 0);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.write(2);
    lcd.setCursor(2, 1);
    lcd.print("S: ");
    lcd.print(light_setpoint);
    lcd.setCursor(COLS - 3, 1);
    lcd.print("Lux");
}

// Funcion para poner arduino en modo bajo consumo

void go_to_sleep()
{

    Serial.println("Sleep!");

    lcd.noBacklight(); // Apagamos la Pantalla
    attachInterrupt(0, wake_up, HIGH);

    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    detachInterrupt(0);

    sleep = 0;
    lcd.backlight(); // Encendemos la pantalla
}

void wake_up()
{
    // Para tener el callback para levantar el arduino
}

// Funcion para calcular el valor del PID
// @Param
// Input - Valor de entrada al PID
// Setpoint - Valor deseado del input
// pid - Structura con las variables y constantes del PID
// @return cv el valor de salida del PID

float compute_pid(float input, float setpoint, s_pid *pid)
{
    float Kp = pid->pid_constants.Kp;
    float Ki = pid->pid_constants.Ki;
    float Kd = pid->pid_constants.Kd;
    float Ts = pid->pid_constants.Ts;
    pid->err = abs(setpoint - input);
    pid->cv = pid->cv1 + (Kp + Kd / Ts) * pid->err + (-Kp + Ki * Ts - 2 * Kd / Ts) * pid->err1 + pid->err2 * (Kd / Ts);
    pid->cv1 = pid->cv;
    pid->err2 = pid->err1;
    pid->err1 = pid->err;
    return pid->cv;
}

// Funcion para realizar el control de la temperatura mediante el valor del PID
// @Param
// t_int - Valor de temperatura interior
// t_ext - Valor de temperatura exterior
// setpoint - Valor de temperatura deseado
// pid - Structura con las variables y constantes del PID

void control_temperature(float t_int, float t_ext, float setpoint, s_pid *pid)
{
    float Output = compute_pid(t_int, setpoint, pid);
    if ((t_int > t_ext && t_int > setpoint) || (t_ext > t_int && t_int < setpoint))
    {
        if (Output > 180)
            Output = 180;
        if (Output < 90)
            Output = 90;
        ventilacion.write(Output);
    }
    else if (t_int > setpoint)
    {
        if (Output > 255)
            Output = 255;
        if (Output < 0)
            Output = 0;
        ventilacion.write(90);
        analogWrite(PIN_VENTILADOR_INT, Output);
    }
}

// Funcion para realizar el control de la iluminación mediante el valor del PID
// @Param
// light_int - Valor de iluminación interior
// light_ext - Valor de iluminación exterior
// setpoint - Valor de iluminación deseado
// pid - Structura con las variables y constantes del PID

void control_light(float light_int, float light_ext, float setpoint, s_pid *pid)
{
    float Output = compute_pid(light_int, setpoint, pid);
    if ((light_int < light_ext && light_int < setpoint))
    {
        if (Output > 400)
            Output = 400;
        if (Output < 0)
            Output = 0;
        persianas.setSpeed(Output / 10);
        persianas.step(stepsPerRevolution);
    }
    else if (light_int < setpoint)
    {
        if (Output > 255)
            Output = 255;
        if (Output < 0)
            Output = 0;
        persianas.setSpeed(Output);
        persianas.step(stepsPerRevolution);
        analogWrite(LED, Output);
    }
}

// Funcion para realizar el cambio de pantallas del LCD cada un tiempo determinado
// @Param
// state_lcd - Valor del estado en el que se encuentra la pantalla
// start_time - Valor del tiempo en el que salto la ultima vez el timer
// timer_time - Valor del tiempo máximo de cada pantalla

void control_lcd_screen(int *state_lcd, unsigned long *start_time, unsigned long timer_time)
{
    unsigned long current_time = millis();

    if (abs(current_time - *start_time) >= timer_time)
    {
        *start_time = millis();
        *state_lcd = (*state_lcd + 1) % 3;
        lcd.clear();
    }
}

// Funcion para pasar al modo de bajo consumo si no se detecta presencia dado un determinado tiempo
// @Param
// pir_value - Valor del detector de presencia
// start_time - Valor del tiempo en el que salto la ultima vez el timer
// timer_time - Valor del tiempo maximo sin presencia para pasar al modo bajo consumo

void detect_presence(int pir_value, unsigned long *start_time, unsigned long timer_time)
{
    unsigned long current_time = millis();
    if (pir_value)
        *start_time = millis();
    else if (abs(current_time - *start_time) >= timer_time)
    {
        *start_time = millis();
        sleep = 1;
    }
}

// Funcion para calcular los luxes dado el valor leido del LDR
// @Param
// value_read - Valor leido del LDR
// @return - Valor medido en luxes

float illumination(float value_read)
{

    int LDR_Value = (int)value_read;
    float lux = ((long)LDR_Value * A * 10) / ((long)B * Rc * (1024 - LDR_Value));
    return lux;
}
