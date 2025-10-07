/*
 * LCDAcentos.h - Librería para mostrar caracteres acentuados en LCD I2C
 * 
 * Esta librería permite mostrar texto con acentos españoles en pantallas LCD I2C
 * manteniendo compatibilidad con las funciones estándar de LiquidCrystal_I2C
 * 
 * Autor: [Tu nombre]
 * Versión: 1.0.0
 * 
 * Características:
 * - Soporte para caracteres acentuados españoles (á, é, í, ó, ú, ñ, °, ¡, ¿)
 * - Gestión automática de slots para caracteres personalizados
 * - Slots reservables para otros usos
 * - Comportamiento similar a print() de LiquidCrystal_I2C
 * - Seguimiento automático de posición del cursor
 */

#ifndef LCDAcentos_h
#define LCDAcentos_h

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// Configuración de la librería
#define MAX_CARACTERES_ESPECIALES 15  // Aumentamos para más caracteres
#define TOTAL_SLOTS_LCD 8

class LCDAcentos {
  public:
    // Constructor
    LCDAcentos(LiquidCrystal_I2C* lcd);
    
    // Funciones principales de impresión
    void print(String texto);
    void print(const char* texto);
    void println(String texto);
    void println(const char* texto);
    
    // Funciones de control de cursor
    void setCursor(int col, int row);
    void getCursor(int* col, int* row);
    
    // Gestión de slots
    void reservarSlot(int slot);
    void liberarSlot(int slot);
    void liberarTodosLosSlots();
    bool isSlotReservado(int slot);
    int slotsDisponibles();
    int slotsUsados();
    
    // Funciones de utilidad
    void clear();
    void home();
    void reiniciarSistema();
    
    // Acceso al LCD original
    LiquidCrystal_I2C* lcd();
    
    // Sincronización con LCD original
    void sincronizarCursor();
    void sincronizarDesde(int col, int row);
    
  private:
    struct CaracterEspecial {
      uint8_t primerByte;
      uint8_t segundoByte;
      uint8_t disenio[8];
    };
    
    // Variables de instancia
    LiquidCrystal_I2C* _lcd;
    int _cursorCol;
    int _cursorRow;
    int _maxCols;
    int _maxRows;
    
    // Estado de slots
    uint8_t _slotsUsados[MAX_CARACTERES_ESPECIALES];
    bool _slotReservado[TOTAL_SLOTS_LCD];
    bool _sistemaInicializado;
    
    // Definición de caracteres especiales
    static const CaracterEspecial CARACTERES_ESPECIALES[MAX_CARACTERES_ESPECIALES];
    
    // Funciones privadas
    void _inicializarSistema();
    void _actualizarCursor();
    int _buscarCaracterEspecial(uint8_t byte1, uint8_t byte2);
    bool _asignarSlotACaracter(int indiceCaracter);
    void _procesarYMostrarTexto(const String& texto);
    void _avanzarCursor();
    bool _esCaracterUTF8(uint8_t b);
    void _manejarFinDeLinea();
    char _obtenerCaracterFallback(uint8_t byte1, uint8_t byte2);
};

#endif