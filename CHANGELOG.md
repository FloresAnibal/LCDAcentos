# Changelog

Todos los cambios notables en este proyecto serán documentados en este archivo.

El formato está basado en [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
y este proyecto adhiere al [Versionado Semántico](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2025-10-06

### Agregado
- Primera versión estable de la librería.
- Soporte para caracteres básicos españoles: á, é, í, ó, ú, ñ.
- Soporte para mayúsculas con acento: Á, É, Í, Ó, Ú, Ñ.
- Inclusión de símbolos especiales: °, ¡, ¿.
- Comportamiento compatible con `print()` de Arduino.
- Sistema de gestión automática de slots para caracteres personalizados.
- Sistema de reserva de slots para caracteres definidos por el usuario.
- Funciones de control de cursor: `setCursor`, `getCursor`.
- Funciones de utilidad: `clear`, `home`, `reiniciarSistema`.
- Función `sincronizarCursor()` para uso mixto con `LiquidCrystal_I2C`.
- Función `sincronizarDesde(int col, int row)` para sincronización manual.
- Ejemplo `CaracteresExtendidos.ino`.
- Ejemplo `EjemploMixto.ino` para uso simultáneo de librerías.
- Herramientas de desarrollo en carpeta `extras/`.
- Documentación completa incluida en `README.md`.
- Ejemplo básico de uso.
- Archivo `keywords.txt` para coloreado de sintaxis.

### Características Técnicas
- Compatible con pantallas LCD I2C 16x2 y otros tamaños.
- Gestión eficiente de memoria para caracteres personalizados.
- Seguimiento automático de posición del cursor.
- Soporte para cadenas UTF-8.
- Arquitectura modular para fácil extensión.

### Licencia
Este proyecto está licenciado bajo los términos de la Licencia MIT.

