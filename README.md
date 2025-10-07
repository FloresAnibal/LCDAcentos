# LCDAcentos

Una librería para Arduino que permite mostrar caracteres acentuados españoles en pantallas LCD I2C, manteniendo compatibilidad total con las funciones estándar de LiquidCrystal_I2C.

## 🚀 Características

- ✅ Soporte completo para caracteres acentuados españoles: **á, é, í, ó, ú, ñ**
- ✅ Símbolos especiales: **°, ¡, ¿**
- ✅ Comportamiento idéntico a `print()` de Arduino
- ✅ Gestión automática de slots para caracteres personalizados
- ✅ Sistema de reserva de slots para otros usos
- ✅ Seguimiento automático de posición del cursor
- ✅ Compatible con LCD I2C de 16x2 y otros tamaños

## 📦 Instalación

### Método 1: Instalación desde ZIP (Recomendado)
1. Descarga el archivo `LCDAcentos.zip`
2. En el IDE de Arduino: **Sketch > Incluir Librería > Añadir librería .ZIP**
3. Selecciona el archivo descargado
4. ¡Listo! La librería aparecerá en **Sketch > Incluir Librería > LCDAcentos**

### Método 2: Instalación Manual
1. Descarga todos los archivos de la librería
2. Crea una carpeta llamada `LCDAcentos` en tu directorio `libraries` de Arduino
3. Coloca todos los archivos dentro de esa carpeta
4. Reinicia el IDE de Arduino

## 🔌 Conexiones

```
LCD I2C  ->  Arduino UNO  ->  Arduino MEGA
VCC      ->  5V           ->  5V
GND      ->  GND          ->  GND
SDA      ->  A4           ->  Pin 21
SCL      ->  A5           ->  Pin 20
```

## 💡 Uso Básico

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LCDAcentos.h>

// Crear objetos LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Ajusta la dirección I2C
LCDAcentos lcdAcentos(&lcd);

void setup() {
  // Inicializar LCD
  lcd.init();
  lcd.backlight();
  
  // ¡Usar como print() normal!
  lcdAcentos.print("¡Educación técnica!");
  lcdAcentos.setCursor(0, 1);
  lcdAcentos.print("Año 2024 - 25°C");
}

void loop() {
  // Tu código aquí
}
```

## 📚 Funciones Disponibles

### Impresión de Texto
```cpp
lcdAcentos.print("Educación");        // Imprime texto con acentos
lcdAcentos.println("¿Está bien?");    // Imprime y salta línea
```

### Control de Cursor
```cpp
lcdAcentos.setCursor(0, 1);           // Posicionar cursor
int col, row;
lcdAcentos.getCursor(&col, &row);     // Obtener posición actual
```

### Gestión de Slots
```cpp
lcdAcentos.reservarSlot(0);           // Reservar slot para otros usos
lcdAcentos.liberarSlot(0);            // Liberar slot
lcdAcentos.liberarTodosLosSlots();    // Liberar todos los slots
bool reservado = lcdAcentos.isSlotReservado(0);  // Verificar estado
```

### Utilidades
```cpp
lcdAcentos.clear();                   // Limpiar pantalla
lcdAcentos.home();                    // Cursor al inicio
lcdAcentos.reiniciarSistema();        // Reiniciar sistema de slots
```

### Acceso al LCD Original
```cpp
LiquidCrystal_I2C* lcd_ptr = lcdAcentos.lcd();  // Obtener puntero al LCD
```

## 🎯 Ejemplos Avanzados

### Usando Slots Reservados
```cpp
// Reservar slots para caracteres personalizados
lcdAcentos.reservarSlot(0);
lcdAcentos.reservarSlot(1);

// Crear caracteres personalizados
byte corazon[8] = {0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00};
lcd.createChar(0, corazon);

// Mostrar texto con acentos (usará otros slots automáticamente)
lcdAcentos.print("Educación ");
lcd.write(0);  // Mostrar corazón
lcdAcentos.print(" técnica");
```

### Texto Largo con Manejo Automático
```cpp
String texto = "Programación en español: ñáéíóú¡¿°";
lcdAcentos.print(texto);  // Se maneja automáticamente el overflow
```

## 🔧 Configuración

### Direcciones I2C Comunes
- `0x27` - La más común
- `0x3F` - Alternativa frecuente  
- `0x38` - Algunos módulos chinos
- `0x26` - Menos común

Para encontrar tu dirección I2C, usa un scanner I2C.

### Caracteres Soportados
| Carácter | Descripción | UTF-8 |
|----------|-------------|-------|
| á | a con acento | C3 A1 |
| é | e con acento | C3 A9 |
| í | i con acento | C3 AD |
| ó | o con acento | C3 B3 |
| ú | u con acento | C3 BA |
| ñ | eñe | C3 B1 |
| ° | símbolo grado | C2 B0 |
| ¡ | admiración invertida | C2 A1 |
| ¿ | interrogación invertida | C2 BF |

## 🐛 Solución de Problemas

### El LCD no muestra nada
- Verifica las conexiones
- Prueba diferentes direcciones I2C (0x27, 0x3F)
- Asegúrate de llamar `lcd.init()` y `lcd.backlight()`

### Los acentos no se ven correctamente
- Verifica que estés usando cadenas UTF-8
- El IDE de Arduino debe estar configurado en UTF-8
- Algunos editores pueden cambiar la codificación

### No hay suficientes slots
- La librería gestiona automáticamente los slots disponibles
- Puedes reservar slots específicos para otros caracteres personalizados
- Máximo 8 slots totales en LCD estándar

## 📄 Licencia

Este proyecto está bajo la Licencia MIT. Consulta el archivo `LICENSE` para más detalles.

## 👨‍💻 Autor

**Aníbal Flores**

## 📝 Changelog

### v1.0.0
- Primera versión estable
- Soporte completo para acentos españoles
- Gestión automática de slots
- Sistema de reserva de slots
- Comportamiento compatible con print()