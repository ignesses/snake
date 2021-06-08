/********** CONSTANTES & CONFIGURACIONES **********/

// Matriz Led:
const int DIN = D1;
const int CS = D0; // Chip-select
const int CLK = D5; // Clock
const int MODULOS = 1;

LedControl matriz = LedControl(DIN, CLK, CS, MODULOS); // Configuración Matriz Led.
MatrizLed pantalla; // Para el scroll de los mensajes.

// Matriz Teclado:
const byte FILAS = 3; // Filas del teclado (uso menos).
const byte COLUMNAS = 3; // Columnas del teclado (uso menos).
char keys[FILAS][COLUMNAS] = {
  {'3','6','9'},
  {'2','5','8'},
  {'1','4','7'}
};
byte pinesFilas[FILAS] = {D2,D3,D4}; // Pines usados para las filas.
byte pinesColumnas[COLUMNAS] = {D8,D7,D6}; // Pines usados para las columnas.
Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS); // Teclado (objeto).
char tecla_presionada = teclado.getKey(); // Guardo la clave presionada.

// Constantes de dirección:
const int arriba = 1;
const int derecha = 2;
const int abajo = 3;
const int izquierda = 4;

// Constantes de velocidad:
const int aumentar = 1;
const int bajar = 2;

/********** JUEGO **********/

bool perdiste = false;
int puntaje = 0;
int largoSnake = 3;     // Largo inicial.
int velocidad = 700;    // Velocidad inicial (milisegundos).
int tablero[8][8] = {}; // Tamaño matriz del tablero.
int direccion = 0;      // Dirección (para que no comience jugando).
int accion = 0;         // Acción para cambio de volicidad.

/********** COORDENADAS **********/

// Dibuja un punto en las coordenadas dadas (X, Y):
struct Point {
  int fila = 0, col = 0;
  Point(int fila = 0, int col = 0): fila(fila), col(col) {}
};

// Coordenadas random para la cabeza de la snake:
Point snake;

// Comida fuera del tablero:
Point comida(-1, -1);
