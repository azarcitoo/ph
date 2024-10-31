#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PH_PIN A0  // Pin analógico donde está conectado el sensor pH
LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección del LCD I2C, 16 columnas y 2 filas

void setup() {
  lcd.begin(16,2);
  lcd.backlight();  // Activa la luz de fondo del LCD
  Serial.begin(9600); // Inicia la comunicación serial
}

void loop() {
  float phValue = readPH();
  
  // Muestra el valor en el LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("pH Value:");
  lcd.setCursor(0, 1);
  lcd.print(phValue, 2); // Muestra el pH con 2 decimales
  
  // Enviar el valor por el puerto serie
  Serial.print("pH Value: ");
  Serial.println(phValue);
  
  delay(2000); // Espera 2 segundos antes de la siguiente lectura
}

float readPH() {
  int sensorValue = analogRead(PH_PIN);
  
  // Convierte el valor analógico a voltaje
  float voltage = sensorValue * (5.0 / 1023.0);
  
  // Convertir voltaje a pH (ajusta estos valores según tu sensor)
  float ph = 7 + ((2.5 - voltage)/0.18); // Fórmula de calibración (ajusta según sea necesario)
  
  return ph;
}
