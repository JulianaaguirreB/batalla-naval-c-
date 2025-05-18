#include <iostream>
#include <fstream>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#define CLEAR "cls"
#else
#include <unistd.h>
#define CLEAR "clear"
#endif
using namespace std;

void ubicarBarcos (char matriz[][10], const string& color);
int posicionamientoBarcos (char matriz[][10], int tam, char nombre, int q, int x, int y, int v, bool h, const string& color);
int atacar (char matriz1[][10], char matriz2[][10], char matriz1_ofeniva[][10], char matriz2_ofensiva[][10]);
void imprimirMatriz (char matriz[][10], const string& color);

struct jugadores {
	string nombre;
} player1, player2;

const string RED = "\033[1;31m";
const string BLUE = "\033[1;34m";
const string RESET = "\033[0m";

int main () {
	
	setlocale(LC_ALL, "spanish");
	char matriz[10][10] = {{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' }, {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' }, {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' },{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' },{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' },{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' },{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' },{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' },{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' },{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' }};
	char matriz2[10][10] = {{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' }, {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' }, {'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' },{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' },{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' },{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' },{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' },{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' },{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' },{'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O' }};
	char matriz1_ofensiva[10][10] = {{'*','*','*','*','*','*','*','*','*','*'},{'*','*','*','*','*','*','*','*','*','*'},{'*','*','*','*','*','*','*','*','*','*'},{'*','*','*','*','*','*','*','*','*','*'},{'*','*','*','*','*','*','*','*','*','*'},{'*','*','*','*','*','*','*','*','*','*'},{'*','*','*','*','*','*','*','*','*','*'},{'*','*','*','*','*','*','*','*','*','*'},{'*','*','*','*','*','*','*','*','*','*'},{'*','*','*','*','*','*','*','*','*','*'}};
	char matriz2_ofensiva[10][10] = {{'*','*','*','*','*','*','*','*','*','*'},{'*','*','*','*','*','*','*','*','*','*'},{'*','*','*','*','*','*','*','*','*','*'},{'*','*','*','*','*','*','*','*','*','*'},{'*','*','*','*','*','*','*','*','*','*'},{'*','*','*','*','*','*','*','*','*','*'},{'*','*','*','*','*','*','*','*','*','*'},{'*','*','*','*','*','*','*','*','*','*'},{'*','*','*','*','*','*','*','*','*','*'},{'*','*','*','*','*','*','*','*','*','*'}};
	int ganador = 0;
	
	cout << "¡Batalla Naval!" << endl;
	cout << endl;
	cout << " Ingrese el nombre del primer jugador" << endl;
	cout << "  > ";
	cin >> player1.nombre;
	cout << endl;
	cout << " Ingrese el nombre del segundo jugador" << endl;
	cout << "  > ";
	cin >> player2.nombre;
	cout << endl; cout << endl;
	
	int i = 1;
	int k = 0;
	
	while (i != 0) { //MENÚ
		
		cout << "Menú" << endl;
		cout << endl;
		cout << " 0. Salir del juego" << endl;
		cout << " 1. Iniciar juego" << endl;
		cout << " 2. Cambiar nombre de jugadores" << endl;
		cout << " 3. Mostrar registro de resultados" << endl;
		cout << endl;		
		cout << "  > ";
		cin >> i;
		cout << endl;
		system(CLEAR);
		
		if (i == 0) {
			cout << "¡Gracias por jugar!" << endl;
			cout << "¡Hasta la próxima!" << endl;
			cout << ":)" << endl;
			cout << endl;
			break;
		}
		
		switch (i) {
			
			case 1:
				cout << "'Debe ingresar una coordenada'" << endl;
				cout << "'El barco se ubicará hacia abajo y hacia la derecha'" << endl;
				cout << endl;
				cout << "Ubicación barcos " << BLUE << player1.nombre << RESET << endl;
				cout << endl;
				ubicarBarcos(matriz, BLUE);
				cout << endl;
				cout << "Ingrese '0' para continuar" << endl;
				cout << " > ";
				cin >> k;
				system(CLEAR);
				
				cout << "Ubicación barcos " << RED << player2.nombre << RESET << endl;
				cout << endl;
				ubicarBarcos(matriz2, RED);
				cout << endl;
				cout << "Ingrese '0' para continuar" << endl;
				cout << " > ";
				cin >> k;
				system(CLEAR);
				
				cout << endl;
				cout << "¡Hora de atacar!" << endl;
				cout << endl;
				ganador = atacar(matriz, matriz2, matriz1_ofensiva, matriz2_ofensiva);
				system(CLEAR);
				
				if (ganador == 1) {
					cout << BLUE << "¡¡Felicidades " << player1.nombre << "!!" << RESET << endl;
					cout << "¡¡Has ganado la partida!!" << endl;
					cout << endl;
				} else {
					cout << RED << "¡¡Felicidades " << player2.nombre << "!!" << RESET << endl;
					cout << "¡¡Has ganado la partida!!" << endl;
					cout << endl;
				}				
				break;
				
			case 2:
				cout << " Ingrese el nombre del primer jugador" << endl;
            	cout << "  > ";
            	cin >> player1.nombre;
	            cout << endl;
	            cout << " Ingrese el nombre del segundo jugador" << endl;
	            cout << "  > ";
				cin >> player2.nombre;
				cout << endl;
				system(CLEAR);
				continue;
				
			case 3:
				// registros
				break;
				
			default:
				cout << "Valor inválido" << endl;
				system(CLEAR);
				break;						
			
		}		
	}
}

void ubicarBarcos (char matriz[][10], const string& color) {
	
	int x = 0;
	int y = 0;
	int v = 0;
	bool h = true;
	int vector[20];
	int tam;
	char nombre;
	bool elegidos [5] = {false};
	
	for (int q = 0; q < 5; q++) {
		
		bool repetidos = true;
		
		cout << "Ingrese que tipo de barco desea poner: " << endl;
		cout << endl;
		cout << " 0. Portaviones (5)" << endl;
		cout << " 1. Fragata (4)" << endl;
		cout << " 2. Crucero (3)" << endl;
		cout << " 3. Submarino (3)" << endl;
		cout << " 4. Destructor (2)" << endl;
		int p = 0;
		cout << endl;
		cout << "  > ";
		cin >> p;
		cout << endl;
		
		switch (p) {
			case 0:
				if(!elegidos[0]){
					tam = 5;
					nombre = 'P';			
					q = posicionamientoBarcos(matriz, tam, nombre, q, x, y, v, h, color);
					elegidos [0] = true;
					repetidos = false;
				} else {
					cout << "Ese barco ya está elegido " << endl;
					cout << "Seleccione otro" << endl;
					cout << endl;
					q--;
				}
				break;
				
			case 1:
				if(!elegidos[1]){
					tam = 4;
					nombre = 'F';
					q = posicionamientoBarcos(matriz, tam, nombre, q, x, y, v, h, color);
					elegidos [1]=true;
					repetidos= false;
				} else {
					cout << "Ese barco ya está elegido " << endl;
					cout << "Seleccione otro" << endl;
					cout << endl;
					q--;
				}
				
				break;
				
			case 2:	
				if(!elegidos[2]){			
					tam = 3;
					nombre = 'C';
					q = posicionamientoBarcos(matriz, tam, nombre, q, x, y, v, h, color);
					elegidos [2]=true;
					repetidos= false;
				} else {
					cout << "Ese barco ya está elegido " << endl;
					cout << "Seleccione otro" << endl;
					cout << endl;
					q--;
				}
				
				break;
				
			case 3:
				if(!elegidos[3]){
					tam = 3;
					nombre = 'S';
					q = posicionamientoBarcos(matriz, tam, nombre, q, x, y, v, h, color);
					elegidos [3] = true;
					repetidos = false;
				} else {
					cout << "Ese barco ya está elegido " << endl;
					cout << "Seleccione otro" << endl;
					cout << endl;
					q--;
				}				
				break;
				
			case 4:
				if(!elegidos[4]){	
					tam = 2;
					nombre = 'D';
					q = posicionamientoBarcos(matriz, tam, nombre, q, x, y, v, h, color);
					repetidos= false;
				} else {
					cout << "Ese barco ya está elegido " << endl;
					cout << "Seleccione otro" << endl;
					cout << endl;
					q--;
				}	
				break;	
					
			default:
				cout << "¡¡Valor inválido!!" << endl;
				cout << endl;
				q--;
				break;
		}			
	}	
}

int posicionamientoBarcos (char matriz[][10], int tam, char nombre, int q, int x, int y, int v, bool h, const string& color) {
	
	cout << "¿En qué posición desea poner su barco?" << endl;
	cout << endl;
	cout << " Posición en filas: " << endl;
	cout << "  > ";
	cin >> x;
	cout << endl;
	cout << " Posición en columnas: " << endl;
	cout << "  > ";
	cin >> y;
	cout << endl;
	
	cout << "¿Desea posicionarlo en horizontal?" << endl;
	cout << " 0. Sí" << endl;
	cout << " 1. No" << endl;
	cout << "  > ";
	cin >> v;
	cout << endl;
	

	if (v == 0) {
		
		if (v== 0 && (y + tam-1) >= 10 || matriz[x][y + (tam-1)] != 'O') {
			cout << "  " << endl;
			cout << " ¡¡Posición ocupada o inválida - Elija otra opción!! " << endl;
			cout << "  " << endl;
			q--;
			return q;
			
		} else {
							
			for (int i = 0; i < tam; i++) {
				if (matriz[x][y+i] != 'O') {
					h = false;
					break;
				}
				h = true;
			}
			
			if (h == true) {
				for (int i = 0; i < tam; i++) {
				matriz [x][y] = nombre;
				y++;
				}
			} else {
				cout << "¡¡Posición inválida!!" << endl;
				cout << endl;
				q--;
				return q;
			}		
		} 

	} else if (v != 0) {
		
		if (v!= 0 && (x + (tam-1) >= 10 || matriz[x + (tam-1)][y] != 'O')) {
		  	cout << "  " << endl;
		   	cout << " ¡¡Posición ocupada o inválida - Elija otra opción!! " << endl;
		  	cout << "  " << endl;
			q--;
			return q;
					 
		} else {
			
			for (int i = 0; i < tam; i++) {
				if (matriz[x+i][y] != 'O') {
					h = false;
					break;
				} else {
					h = true;
				}
			}

			if (h == true) {
				for (int i = 0; i < tam; i++) {
				matriz [x][y] = nombre;
				x++;
				}
			} else {
			cout << "¡¡Posición inválida!!" << endl;
			cout << endl;
			q--;
			return q;	
			}
		}
	}
	imprimirMatriz(matriz, color);						
	return q; 	
}

int atacar (char matriz1[][10], char matriz2[][10], char matriz1_ofensiva[][10], char matriz2_ofensiva[][10]) {
	
	int contador1 = 0;
	int contador2 = 0;
	int x = 0;
	int y = 0;
	int k = 0;
	
	while (true) {
		
		while (true) {
			
			cout << BLUE << "Turno " << player1.nombre << RESET << endl;
			cout << endl;
			cout << "Ingrese las coordenadas para atacar" << endl;
			cout << endl;
			cout << " Fila" << endl;
			cout << "  > ";
			cin >> x;
			cout << "Columna" << endl;
			cout << "  > ";
			cin >> y;
			cout << endl;
			
			if (matriz1_ofensiva[x][y] != '*' || x >= 10 || y >= 10) {
				cout << "¡¡Coordenada inválida!!" << endl;
				continue;
			}
	
			if (matriz1[x][y] == 'O') {
				matriz1_ofensiva[x][y] = 'O';
				cout << "¡Has fallado el tiro!" << endl;
				cout << endl;
				imprimirMatriz(matriz1_ofensiva, BLUE);
				cout << endl;
				break;
			} else {
				matriz1_ofensiva[x][y] = 'X';
				cout << "¡Le atinaste!" << endl;
				contador1++;
				cout << endl;
				imprimirMatriz(matriz1_ofensiva, BLUE);
				cout << endl;
			}
			if (contador1 == 17) {
				return 1;
			}
		}
		cout << "Ingrese '0' para continuar" << endl;
		cout << " > ";
		cin >> k;	
		system(CLEAR);
		
		while (true) {
			
			cout << RED << "Turno " << player2.nombre << RESET << endl;
			cout << endl;
			cout << "Ingrese las coordenadas para atacar" << endl;
			cout << endl;
			cout << " Fila" << endl;
			cout << "  > ";
			cin >> x;
			cout << "Columna" << endl;
			cout << "  > ";
			cin >> y;
			cout << endl;
			
			if (matriz2_ofensiva[x][y] != '*' || x >= 10 || y >= 10) { // condicion fuera
				cout << "¡¡Coordenada inválida!!" << endl;
				cout << endl;
				continue;
			}
	
			if (matriz2[x][y] == 'O') {
				matriz2_ofensiva[x][y] = 'O';
				cout << "¡Has fallado el tiro!" << endl;
				cout << endl;
				imprimirMatriz(matriz2_ofensiva, RED);
				cout << endl;
				break;
				
			} else {
				matriz2_ofensiva[x][y] = 'X';
				cout << "¡Le atinaste!" << endl;
				contador2++;
				cout << endl;
				imprimirMatriz(matriz2_ofensiva, RED);
				cout << endl;
				
			}
			if (contador2 == 17) {
				return 2;
			}
			
		}
		cout << "Ingrese '0' para continuar" << endl;
		cout << " > ";
		cin >> k;
		system(CLEAR);
	}	
}

void imprimirMatriz (char matriz[][10], const string& color) {
	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (matriz[i][j] != 'O') {
				cout << color << matriz[i][j] << RESET << " ";  // Color a los barcos
			} else {
				cout << matriz[i][j] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;	
}

