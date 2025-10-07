/*
 * LCDAcentos.cpp - Implementación de la librería para mostrar caracteres acentuados
 * 
 * Esta implementación proporciona funcionalidad completa para mostrar texto
 * con acentos españoles en pantallas LCD I2C, manteniendo compatibilidad
 * con las funciones estándar de LiquidCrystal_I2C.
 */

#include "LCDAcentos.h"

// Definición de caracteres especiales con sus diseños
const LCDAcentos::CaracterEspecial LCDAcentos::CARACTERES_ESPECIALES[MAX_CARACTERES_ESPECIALES] = {
  // Caracteres básicos españoles
  {0xC3, 0xA1, {B00001, B00010, B01110, B00001, B01110, B10001, B01110, B00000}}, // á
  {0xC3, 0xA9, {B00001, B00010, B01110, B10001, B11111, B10000, B01110, B00000}}, // é
  {0xC3, 0xAD, {B00010, B00100, B00000, B01100, B00100, B00100, B01110, B00000}}, // í
  {0xC3, 0xB3, {B00001, B00010, B01110, B10001, B10001, B10001, B01110, B00000}}, // ó
  {0xC3, 0xBA, {B00010, B00100, B10001, B10001, B10001, B10011, B01101, B00000}}, // ú
  {0xC3, 0xB1, {B01110, B00000, B10110, B11001, B10001, B10001, B10001, B00000}}, // ñ
  {0xC2, 0xB0, {B01100, B10010, B01100, B00000, B00000, B00000, B00000, B00000}}, // °
  {0xC2, 0xA1, {B00100, B00000, B00000, B00100, B00100, B00100, B00100, B00000}}, // ¡
  {0xC2, 0xBF, {B00100, B00000, B00100, B01000, B10000, B10001, B01110, B00000}}, // ¿
  
  // ¡NUEVOS CARACTERES! - Solo agregar aquí
  {0xC3, 0x81, {B00100, B01010, B01110, B00001, B01111, B10001, B01111, B00000}}, // Á (A mayúscula con acento)
  {0xC3, 0x89, {B00100, B01010, B11111, B10000, B11110, B10000, B11111, B00000}}, // É (E mayúscula con acento)
  {0xC3, 0x8D, {B01000, B10000, B01110, B00100, B00100, B00100, B01110, B00000}}, // Í (I mayúscula con acento)
  {0xC3, 0x93, {B00100, B01010, B01110, B10001, B10001, B10001, B01110, B00000}}, // Ó (O mayúscula con acento)
  {0xC3, 0x9A, {B00100, B01010, B10001, B10001, B10001, B10001, B01110, B00000}}, // Ú (U mayúscula con acento)
  {0xC3, 0x91, {B01110, B00000, B10001, B11001, B10101, B10011, B10001, B00000}}  // Ñ (Ñ mayúscula)
};

// Constructor
LCDAcentos::LCDAcentos(LiquidCrystal_I2C* lcd) {
  _lcd = lcd;
  _cursorCol = 0;
  _cursorRow = 0;
  _maxCols = 16;  // Valor por defecto, se puede ajustar
  _maxRows = 2;   // Valor por defecto, se puede ajustar
  _sistemaInicializado = false;
  _inicializarSistema();
}

// ===== FUNCIONES PÚBLICAS DE IMPRESIÓN =====

void LCDAcentos::print(String texto) {
  if (!_sistemaInicializado) {
    _inicializarSistema();
  }
  _procesarYMostrarTexto(texto);
}

void LCDAcentos::print(const char* texto) {
  print(String(texto));
}

void LCDAcentos::println(String texto) {
  print(texto);
  _manejarFinDeLinea();
}

void LCDAcentos::println(const char* texto) {
  println(String(texto));
}

// ===== FUNCIONES DE CONTROL DE CURSOR =====

void LCDAcentos::setCursor(int col, int row) {
  _cursorCol = constrain(col, 0, _maxCols - 1);
  _cursorRow = constrain(row, 0, _maxRows - 1);
  _lcd->setCursor(_cursorCol, _cursorRow);
}

void LCDAcentos::getCursor(int* col, int* row) {
  if (col) *col = _cursorCol;
  if (row) *row = _cursorRow;
}

// ===== GESTIÓN DE SLOTS =====

void LCDAcentos::reservarSlot(int slot) {
  if (slot >= 0 && slot < TOTAL_SLOTS_LCD) {
    _slotReservado[slot] = true;
    
    // Si el slot estaba siendo usado por un carácter especial, liberarlo
    for (int i = 0; i < MAX_CARACTERES_ESPECIALES; i++) {
      if (_slotsUsados[i] == (uint8_t)slot) {
        _slotsUsados[i] = 255; // Marcar como no asignado
        break;
      }
    }
  }
}

void LCDAcentos::liberarSlot(int slot) {
  if (slot >= 0 && slot < TOTAL_SLOTS_LCD) {
    _slotReservado[slot] = false;
  }
}

void LCDAcentos::liberarTodosLosSlots() {
  for (int i = 0; i < TOTAL_SLOTS_LCD; i++) {
    _slotReservado[i] = false;
  }
}

bool LCDAcentos::isSlotReservado(int slot) {
  if (slot >= 0 && slot < TOTAL_SLOTS_LCD) {
    return _slotReservado[slot];
  }
  return false;
}

int LCDAcentos::slotsDisponibles() {
  int disponibles = 0;
  for (int slot = 0; slot < TOTAL_SLOTS_LCD; slot++) {
    if (!_slotReservado[slot]) {
      // Verificar que no esté siendo usado por otro carácter
      bool slotEnUso = false;
      for (int i = 0; i < MAX_CARACTERES_ESPECIALES; i++) {
        if (_slotsUsados[i] == (uint8_t)slot) {
          slotEnUso = true;
          break;
        }
      }
      if (!slotEnUso) {
        disponibles++;
      }
    }
  }
  return disponibles;
}

int LCDAcentos::slotsUsados() {
  return TOTAL_SLOTS_LCD - slotsDisponibles();
}

// ===== FUNCIONES DE UTILIDAD =====

void LCDAcentos::clear() {
  _lcd->clear();
  _cursorCol = 0;
  _cursorRow = 0;
}

void LCDAcentos::home() {
  _lcd->home();
  _cursorCol = 0;
  _cursorRow = 0;
}

void LCDAcentos::reiniciarSistema() {
  _inicializarSistema();
}

LiquidCrystal_I2C* LCDAcentos::lcd() {
  return _lcd;
}

// ===== FUNCIONES DE SINCRONIZACIÓN =====

void LCDAcentos::sincronizarCursor() {
  // Nota: LiquidCrystal_I2C no proporciona getCursor(),
  // por lo que esta función es limitada
  // Se recomienda usar sincronizarDesde() con valores conocidos
}

void LCDAcentos::sincronizarDesde(int col, int row) {
  _cursorCol = constrain(col, 0, _maxCols - 1);
  _cursorRow = constrain(row, 0, _maxRows - 1);
}

// ===== FUNCIONES PRIVADAS =====

void LCDAcentos::_inicializarSistema() {
  // Inicializar mapeo de slots
  for (int i = 0; i < MAX_CARACTERES_ESPECIALES; i++) {
    _slotsUsados[i] = 255; // Valor que indica "no asignado"
  }
  
  // Por defecto, ningún slot está reservado
  for (int i = 0; i < TOTAL_SLOTS_LCD; i++) {
    _slotReservado[i] = false;
  }
  
  _sistemaInicializado = true;
}

void LCDAcentos::_actualizarCursor() {
  _lcd->setCursor(_cursorCol, _cursorRow);
}

int LCDAcentos::_buscarCaracterEspecial(uint8_t byte1, uint8_t byte2) {
  for (int i = 0; i < MAX_CARACTERES_ESPECIALES; i++) {
    if (CARACTERES_ESPECIALES[i].primerByte == byte1 && 
        CARACTERES_ESPECIALES[i].segundoByte == byte2) {
      return i;
    }
  }
  return -1; // No encontrado
}

bool LCDAcentos::_asignarSlotACaracter(int indiceCaracter) {
  // Buscar slot libre que no esté reservado
  for (int slot = 0; slot < TOTAL_SLOTS_LCD; slot++) {
    if (!_slotReservado[slot]) {
      // Verificar que no esté siendo usado por otro carácter
      bool slotEnUso = false;
      for (int i = 0; i < MAX_CARACTERES_ESPECIALES; i++) {
        if (_slotsUsados[i] == (uint8_t)slot) {
          slotEnUso = true;
          break;
        }
      }
      
      if (!slotEnUso) {
        _slotsUsados[indiceCaracter] = (uint8_t)slot;
        return true;
      }
    }
  }
  return false; // No hay slots disponibles
}

void LCDAcentos::_procesarYMostrarTexto(const String& texto) {
  // Primero, procesar el texto para asignar slots a caracteres especiales
  for (size_t i = 0; i < texto.length(); i++) {
    if (i + 1 < texto.length()) {
      uint8_t primerByte = (uint8_t)texto.charAt(i);
      uint8_t segundoByte = (uint8_t)texto.charAt(i + 1);
      
      int indiceCaracter = _buscarCaracterEspecial(primerByte, segundoByte);
      
      if (indiceCaracter >= 0 && _slotsUsados[indiceCaracter] == 255) {
        if (_asignarSlotACaracter(indiceCaracter)) {
          // Crear el carácter personalizado en el LCD
          // Usamos const_cast porque sabemos que createChar no modifica el array
          _lcd->createChar((uint8_t)_slotsUsados[indiceCaracter], 
                          const_cast<uint8_t*>(CARACTERES_ESPECIALES[indiceCaracter].disenio));
        }
      }
    }
  }
  
  // Ahora mostrar el texto
  for (size_t i = 0; i < texto.length(); i++) {
    if (_cursorCol >= _maxCols) {
      _manejarFinDeLinea();
    }
    
    if (_cursorRow >= _maxRows) {
      break; // No hay más espacio en la pantalla
    }
    
    uint8_t primerByte = (uint8_t)texto.charAt(i);
    
    // Verificar si es un carácter UTF-8 de 2 bytes
    if (i + 1 < texto.length() && _esCaracterUTF8(primerByte)) {
      uint8_t segundoByte = (uint8_t)texto.charAt(i + 1);
      int indiceCaracter = _buscarCaracterEspecial(primerByte, segundoByte);
      
      if (indiceCaracter >= 0 && _slotsUsados[indiceCaracter] != 255) {
        // Mostrar carácter especial
        _actualizarCursor();
        _lcd->write((uint8_t)_slotsUsados[indiceCaracter]);
        i++; // Saltar el segundo byte del carácter UTF-8
        _avanzarCursor();
        continue;
      } else if (indiceCaracter >= 0) {
        // Carácter especial reconocido pero sin slot disponible - usar fallback
        _actualizarCursor();
        char fallback = _obtenerCaracterFallback(primerByte, segundoByte);
        _lcd->print(fallback);
        i++; // Saltar el segundo byte del carácter UTF-8
        _avanzarCursor();
        continue;
      }
    }
    
    // Mostrar carácter normal
    _actualizarCursor();
    _lcd->print((char)primerByte);
    _avanzarCursor();
  }
}

void LCDAcentos::_avanzarCursor() {
  _cursorCol++;
  if (_cursorCol >= _maxCols) {
    _manejarFinDeLinea();
  }
}

bool LCDAcentos::_esCaracterUTF8(uint8_t b) {
  // Verificar si el byte indica el inicio de un carácter UTF-8 de 2 bytes
  return (b == 0xC2 || b == 0xC3);
}

void LCDAcentos::_manejarFinDeLinea() {
  _cursorRow++;
  _cursorCol = 0;
  if (_cursorRow >= _maxRows) {
    _cursorRow = _maxRows - 1; // Quedarse en la última fila
  }
}

char LCDAcentos::_obtenerCaracterFallback(uint8_t byte1, uint8_t byte2) {
  // Sistema de fallback: mostrar caracteres similares sin acento
  if (byte1 == 0xC3) {
    switch (byte2) {
      case 0xA1: case 0x81: return 'a'; // á, Á → a, A
      case 0xA9: case 0x89: return 'e'; // é, É → e, E
      case 0xAD: case 0x8D: return 'i'; // í, Í → i, I
      case 0xB3: case 0x93: return 'o'; // ó, Ó → o, O
      case 0xBA: case 0x9A: return 'u'; // ú, Ú → u, U
      case 0xB1: case 0x91: return 'n'; // ñ, Ñ → n, N
    }
  } else if (byte1 == 0xC2) {
    switch (byte2) {
      case 0xB0: return 'o'; // ° → o
      case 0xA1: return '!'; // ¡ → !
      case 0xBF: return '?'; // ¿ → ?
    }
  }
  return '?'; // Carácter desconocido
}