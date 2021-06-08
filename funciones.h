/********** FUNCIONES **********/

void inicio() {
  
  // DE LA MATRIZ:     
  matriz.shutdown(0, false);  // Enciende la matriz.
  matriz.setIntensity(0, 4);  // Establece brillo (entre 0 y 15).
  matriz.clearDisplay(0);     // Blanquea la matriz.
  // PARA LIBRERÍA DE MENSAJES:
  pantalla.begin(DIN, CLK, CS, MODULOS);
  // POSICIÓN DE LA CABEZA:
  snake.fila = random(8);
  snake.col = random(8);
  
}

void comidaRandom() {
  if (comida.fila == -1 || comida.col == -1) {
    do {
      comida.col = random(8);
      comida.fila = random(8);
      // Mientras haya comida me quedo en el DO:
    } while (tablero[comida.fila][comida.col] > 0);
  }
}

void leerTeclado() {
  int direccionAnterior = direccion; // Dirección anterior.
  long timestamp = millis();
  
  while (millis() < timestamp + velocidad) {

    // Guardo la tecla presionada:
    char tecla_presionada = teclado.getKey();

    // Identificar dirección:
    tecla_presionada == '2' ? direccion = derecha : direccion;
    tecla_presionada == '8' ? direccion = izquierda : direccion;
    tecla_presionada == '4' ? direccion = arriba : direccion;
    tecla_presionada == '6' ? direccion = abajo : direccion;
    
    // Bloquear direcciones en sentido opuesto:
    direccion + 2 == direccionAnterior && direccionAnterior != 0 ? direccion = direccionAnterior : 0;
    direccion - 2 == direccionAnterior && direccionAnterior != 0 ? direccion = direccionAnterior : 0;

    // Identificar cambios de velocidad:
    tecla_presionada == '7' ? accion = bajar : accion;
    tecla_presionada == '9' ? accion = aumentar : accion;

    // Mostrar y hacer parpadear la comida:
    matriz.setLed(0, comida.fila, comida.col, millis() % 100 < 50 ? 1 : 0);
    
  }
}

// Aparecer del otro lado del cuadrante:
void volverTablero() {
  snake.col < 0 ? snake.col += 8 : 0;
  snake.col > 7 ? snake.col -= 8 : 0;
  snake.fila < 0 ? snake.fila += 8 : 0;
  snake.fila > 7 ? snake.fila -= 8 : 0;
}

void moverSnake() {
  switch (direccion) {
    case arriba:
      snake.fila--;
      volverTablero();
      // setLed(nº matriz, fila, columna, valor)
      matriz.setLed(0, snake.fila, snake.col, 1);
      break;

    case derecha:
      snake.col++;
      volverTablero();
      matriz.setLed(0, snake.fila, snake.col, 1);
      break;

    case abajo:
      snake.fila++;
      volverTablero();
      matriz.setLed(0, snake.fila, snake.col, 1);
      break;

    case izquierda:
      snake.col--;
      volverTablero();
      matriz.setLed(0, snake.fila, snake.col, 1);
      break;

    default:
      return;
  }

  // Si se choca con el cuerpo:
  if (tablero[snake.fila][snake.col] > 1 && direccion != 0) {
    perdiste = true;
    return;
  }

  // Si la cabeza de la snake y comida están en las mismas coordenadas (comido):
  if (snake.fila == comida.fila && snake.col == comida.col) {
    // Nuevo random de comida:
    comida.fila = -1;
    comida.col = -1;

    // Aumenta el largo y el puntaje:
    largoSnake++;
    puntaje++;

    // Incrementa los segmentos:
    for (int fila = 0; fila < 8; fila++) {
      for (int col = 0; col < 8; col++) {
        if (tablero[fila][col] > 0 ) {
          tablero[fila][col]++;
        }
      }
    }
  }

  // Crece snake un casillero:
  tablero[snake.fila][snake.col] = largoSnake + 1;

  // Disminuyo los segmentos de la cola a medida que avanzo:
  for (int fila = 0; fila < 8; fila++) {
    
    for (int col = 0; col < 8; col++) {
      if (tablero[fila][col] > 0 ) {
        tablero[fila][col]--;
      }
      
      matriz.setLed(0, fila, col, tablero[fila][col] == 0 ? 0 : 1);
    }
  }
}


void desarmarSnake() {
  matriz.setLed(0, comida.fila, comida.col, 0);

  for (int i = 1; i <= largoSnake; i++) {
    for (int fila = 0; fila < 8; fila++) {
      for (int col = 0; col < 8; col++) {
        if (tablero[fila][col] == i) {
          matriz.setLed(0, fila, col, 0);
          delay(100);
        }
      }
    }
  }
}

void cambiarVelocidad() {
  
  switch (accion) {
    
    case aumentar:
      if (velocidad > 100){
        velocidad = velocidad - 100;
        tecla_presionada = direccion;
        accion = 0;
      }
      break;
      
    case bajar:
      if (velocidad < 1500){
        velocidad = velocidad + 100;
        tecla_presionada = direccion;
        accion = 0;
      }
      break;
      
    default:
      break;
  }
}

void mostrarPuntaje(){ // Pendiente: editar librería para recibir String.

  String puntajeString = String(puntaje);
  char const* valor = puntajeString.c_str(); 
  
  delay(200);
  pantalla.escribirFraseScroll("PUNTAJE", 70);
  delay(100);
  pantalla.escribirFraseScroll(valor,200);
  delay(100);
  
}

void borrarTablero() {
  
  for (int fila = 0; fila < 8; fila++) {
      for (int col = 0; col < 8; col++) {
        if (tablero[fila][col] > 0 ) {
          tablero[fila][col] = 0;
      }
    }
  }
}

void reiniciarVariables() {
  perdiste = false;
  snake.fila = random(8);
  snake.col = random(8);
  comida.fila = -1;
  comida.col = -1;
  largoSnake = 3;
  puntaje = 0;
  direccion = 0;
  accion = 0;
}

void estado() {
  
  if (perdiste) {
    desarmarSnake();
    pantalla.borrar();
    pantalla.escribirFraseScroll("PERDISTE", 70);
    mostrarPuntaje();     
    matriz.clearDisplay(0);
    reiniciarVariables();
    borrarTablero();   
  }
  
}
