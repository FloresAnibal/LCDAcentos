/*
 * Herramientas UTF-8 para LCDAcentos
 * 
 * Este sketch proporciona herramientas útiles para:
 * - Analizar bytes UTF-8 de cadenas de texto
 * - Generar código para nuevos caracteres
 * - Verificar compatibilidad de caracteres
 * 
 * Usar este sketch para desarrollar nuevos caracteres especiales
 * antes de agregarlos a la librería LCDAcentos
 * 
 * Autor: [Tu nombre]
 * Fecha: 2024
 */

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(10);
  }
  
  Serial.println("=== HERRAMIENTAS UTF-8 para LCDAcentos ===");
  Serial.println("Selecciona una opción:");
  Serial.println("1. Analizar texto (envía texto por Serial)");
  Serial.println("2. Ejemplos de caracteres comunes");
  Serial.println("3. Generar código para carácter");
  Serial.println("==========================================");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readString();
    input.trim();
    
    if (input == "1") {
      Serial.println("Envía el texto a analizar:");
    } else if (input == "2") {
      mostrarEjemplosComunes();
    } else if (input == "3") {
      Serial.println("Función generar código - implementar según necesidad");
    } else if (input.length() > 0) {
      analizarTexto(input);
    }
  }
}

void analizarTexto(String texto) {
  Serial.println("\n=== ANÁLISIS UTF-8 ===");
  Serial.println("Texto: " + texto);
  Serial.println("Longitud: " + String(texto.length()) + " bytes");
  Serial.println("\nBytes individuales:");
  
  for (int i = 0; i < texto.length(); i++) {
    byte b = texto.charAt(i);
    Serial.print("Pos " + String(i) + ": ");
    Serial.print("0x");
    if (b < 16) Serial.print("0");
    Serial.print(b, HEX);
    Serial.print(" (");
    Serial.print(b, DEC);
    Serial.print(") ");
    
    if (b >= 32 && b <= 126) {
      Serial.print("'" + String((char)b) + "'");
    } else {
      Serial.print("(especial)");
    }
    Serial.println();
  }
  
  Serial.println("\nCaracteres UTF-8 de 2 bytes detectados:");
  for (int i = 0; i < texto.length() - 1; i++) {
    byte b1 = texto.charAt(i);
    byte b2 = texto.charAt(i + 1);
    
    if ((b1 == 0xC2 || b1 == 0xC3) && (b2 & 0x80) == 0x80) {
      Serial.print("Posición " + String(i) + "-" + String(i+1) + ": ");
      Serial.print("0x");
      if (b1 < 16) Serial.print("0");
      Serial.print(b1, HEX);
      Serial.print(", 0x");
      if (b2 < 16) Serial.print("0");
      Serial.print(b2, HEX);
      
      // Intentar mostrar el carácter
      String caracter = String((char)b1) + String((char)b2);
      Serial.println(" → '" + caracter + "'");
      
      // Generar línea de código
      Serial.println("  Código: {0x" + String(b1, HEX) + ", 0x" + String(b2, HEX) + 
                    ", {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000}}, // " + caracter);
    }
  }
  Serial.println("====================\n");
}

void mostrarEjemplosComunes() {
  Serial.println("\n=== CARACTERES COMUNES Y SUS BYTES UTF-8 ===");
  
  // Caracteres básicos españoles
  Serial.println("\n--- Minúsculas con acento ---");
  mostrarCaracter("á", 0xC3, 0xA1);
  mostrarCaracter("é", 0xC3, 0xA9);
  mostrarCaracter("í", 0xC3, 0xAD);
  mostrarCaracter("ó", 0xC3, 0xB3);
  mostrarCaracter("ú", 0xC3, 0xBA);
  mostrarCaracter("ñ", 0xC3, 0xB1);
  
  Serial.println("\n--- Mayúsculas con acento ---");
  mostrarCaracter("Á", 0xC3, 0x81);
  mostrarCaracter("É", 0xC3, 0x89);
  mostrarCaracter("Í", 0xC3, 0x8D);
  mostrarCaracter("Ó", 0xC3, 0x93);
  mostrarCaracter("Ú", 0xC3, 0x9A);
  mostrarCaracter("Ñ", 0xC3, 0x91);
  
  Serial.println("\n--- Símbolos especiales ---");
  mostrarCaracter("°", 0xC2, 0xB0);
  mostrarCaracter("¡", 0xC2, 0xA1);
  mostrarCaracter("¿", 0xC2, 0xBF);
  
  Serial.println("\n--- Otros símbolos útiles ---");
  mostrarCaracter("ü", 0xC3, 0xBC);
  mostrarCaracter("Ü", 0xC3, 0x9C);
  mostrarCaracter("ç", 0xC3, 0xA7);
  mostrarCaracter("Ç", 0xC3, 0x87);
  
  Serial.println("============================================\n");
}

void mostrarCaracter(String caracter, byte b1, byte b2) {
  Serial.print("'" + caracter + "' → 0x");
  if (b1 < 16) Serial.print("0");
  Serial.print(b1, HEX);
  Serial.print(", 0x");
  if (b2 < 16) Serial.print("0");
  Serial.print(b2, HEX);
  
  Serial.println("  {0x" + String(b1, HEX) + ", 0x" + String(b2, HEX) + 
                ", {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000}}, // " + caracter);
}

void generarPlantillaCaracter(String nombre, byte b1, byte b2) {
  Serial.println("\n=== PLANTILLA PARA CARÁCTER '" + nombre + "' ===");
  Serial.println("// Agregar esta línea al array CARACTERES_ESPECIALES:");
  Serial.print("{0x");
  if (b1 < 16) Serial.print("0");
  Serial.print(b1, HEX);
  Serial.print(", 0x");
  if (b2 < 16) Serial.print("0");
  Serial.print(b2, HEX);
  Serial.println(", {");
  Serial.println("  B00000,  // Fila 1 - Diseña tu carácter aquí");
  Serial.println("  B00000,  // Fila 2 - Usa 1s para píxeles encendidos");
  Serial.println("  B00000,  // Fila 3 - Usa 0s para píxeles apagados");
  Serial.println("  B00000,  // Fila 4");
  Serial.println("  B00000,  // Fila 5");
  Serial.println("  B00000,  // Fila 6");
  Serial.println("  B00000,  // Fila 7");
  Serial.println("  B00000   // Fila 8");
  Serial.println("}}, // " + nombre);
  Serial.println("================================================\n");
}

/*
 * INSTRUCCIONES DE USO:
 * 
 * 1. Carga este sketch en tu Arduino
 * 2. Abre el Monitor Serie (115200 baudios)
 * 3. Envía texto para analizarlo
 * 4. Usa los códigos generados en LCDAcentos.cpp
 * 
 * EJEMPLO DE FLUJO:
 * 1. Envía "Educación" → obtienes los bytes UTF-8
 * 2. Diseña los caracteres en LCD Character Creator
 * 3. Agrega las líneas generadas al array CARACTERES_ESPECIALES
 * 4. Actualiza MAX_CARACTERES_ESPECIALES
 * 5. ¡Listo para usar!
 */