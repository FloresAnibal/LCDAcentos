/*
 * Ejemplo Caracteres Extendidos - LCDAcentos
 * 
 * Este ejemplo demuestra el uso de caracteres extendidos incluyendo
 * mayúsculas con acento y símbolos especiales adicionales
 * 
 * Requiere: LCDAcentos v1.1.0 o superior
 * 
 * Caracteres demostrados:
 * - Mayúsculas con acento: Á, É, Í, Ó, Ú, Ñ
 * - Minúsculas básicas: á, é, í, ó, ú, ñ
 * - Símbolos especiales: °, ¡, ¿
 * 
 * Autor: [Tu nombre]
 * Fecha: 2024
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LCDAcentos.h>

// Configuración del LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
LCDAcentos lcdAcentos(&lcd);

void setup() {
  Serial.begin(9600);
  Serial.println("=== Demo Caracteres Extendidos ===");
  
  // Inicializar LCD
  lcd.init();
  lcd.backlight();
  
  // Demostrar diferentes conjuntos de caracteres
  demoMinusculas();
  delay(3000);
  
  demoMayusculas(); 
  delay(3000);
  
  demoSimbolos();
  delay(3000);
  
  demoTextoMixto();
  delay(3000);
  
  Serial.println("Demo completada. Iniciando loop...");
}

void loop() {
  // Ciclo de ejemplos dinámicos
  ejemploDinamico1();
  delay(2000);
  
  ejemploDinamico2();
  delay(2000);
  
  ejemploDinamico3();
  delay(2000);
}

void demoMinusculas() {
  lcdAcentos.clear();
  Serial.println("Demostrando minúsculas...");
  
  lcdAcentos.setCursor(0, 0);
  lcdAcentos.print("educación técnica");
  lcdAcentos.setCursor(0, 1);
  lcdAcentos.print("programación 2024");
  
  Serial.println("Minúsculas: educación, técnica, programación");
}

void demoMayusculas() {
  lcdAcentos.clear();
  Serial.println("Demostrando mayúsculas...");
  
  lcdAcentos.setCursor(0, 0);
  lcdAcentos.print("EDUCACIÓN");
  lcdAcentos.setCursor(0, 1);
  lcdAcentos.print("PROGRAMACIÓN");
  
  Serial.println("Mayúsculas: EDUCACIÓN, PROGRAMACIÓN");
}

void demoSimbolos() {
  lcdAcentos.clear();
  Serial.println("Demostrando símbolos...");
  
  lcdAcentos.setCursor(0, 0);
  lcdAcentos.print("Temp: 25°C");
  lcdAcentos.setCursor(0, 1);
  lcdAcentos.print("¿Estado? ¡OK!");
  
  Serial.println("Símbolos: °, ¿, ¡");
}

void demoTextoMixto() {
  lcdAcentos.clear();
  Serial.println("Demostrando texto mixto...");
  
  lcdAcentos.setCursor(0, 0);
  lcdAcentos.print("EDUCACIÓN técnica");
  lcdAcentos.setCursor(0, 1);
  lcdAcentos.print("¿TODO bien? ¡Sí!");
  
  Serial.println("Mixto: mayúsculas + minúsculas + símbolos");
}

void ejemploDinamico1() {
  lcdAcentos.clear();
  lcdAcentos.print("Año: 2024");
  lcdAcentos.setCursor(0, 1);
  lcdAcentos.print("Versión: 1.1.0");
}

void ejemploDinamico2() {
  lcdAcentos.clear();
  lcdAcentos.print("PROGRAMACIÓN");
  lcdAcentos.setCursor(0, 1);
  lcdAcentos.print("Español ñ - 25°");
}

void ejemploDinamico3() {
  lcdAcentos.clear();
  lcdAcentos.print("¿Funciona?");
  lcdAcentos.setCursor(0, 1);
  lcdAcentos.print("¡PERFECCIÓN!");
}

void mostrarEstadisticas() {
  // Función para mostrar estadísticas por Serial
  Serial.println("\n=== Estadísticas de Caracteres ===");
  
  String texto = "EDUCACIÓN técnica ñáéíóú¡¿°";
  Serial.println("Texto de prueba: " + texto);
  Serial.println("Longitud: " + String(texto.length()) + " bytes");
  
  // Contar caracteres especiales
  int especiales = 0;
  for (int i = 0; i < texto.length(); i++) {
    byte b = texto.charAt(i);
    if (b == 0xC2 || b == 0xC3) {
      especiales++;
    }
  }
  
  Serial.println("Caracteres especiales detectados: " + String(especiales));
  Serial.println("===================================\n");
}