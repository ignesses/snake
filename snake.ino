/********** LIBRERÍAS **********/
#include <LedControl.h> // Matriz Led
#include <Keypad.h>     // Matriz Teclado
#include <MatrizLed.h>  // Mensajes Scroll
#include "config.h"     // Variables y Configuración
#include "funciones.h"  // Funciones

void setup() {
  
  Serial.begin(115200);
  inicio();
  
}

void loop() {
  
  comidaRandom();       // Si no hay comida en el tablero, la creo.
  
  leerTeclado();        // Leo y guardo los valores recibidos por teclado.
  
  moverSnake();         // Definimos cómo se mueve la snake según el case.
  
  cambiarVelocidad();   // Aumentamos o disminuímos la velocidad.
  estado();
  
}
