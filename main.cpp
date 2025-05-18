#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

void ubicarBarcos(char matriz[][10], const char color[]);
int posicionamientoBarcos(char matriz[][10], int tam, char nombre, int x, int y, int v, const char color[]);
int atacar(char matriz1[][10], char matriz2[][10], char matriz1_ofensiva[][10], char matriz2_ofensiva[][10], int &turno);
void imprimirMatriz(char matriz[][10], const char color[]);
void guardarPartida(const char nombreJugador1[], const char nombreJugador2[], char matriz1[][10], char matriz2[][10], char matriz1_ofensiva[][10], char matriz2_ofensiva[][10], int turno);
bool cargarPartida(char nombreJugador1[], char nombreJugador2[], char matriz1[][10], char matriz2[][10], char matriz1_ofensiva[][10], char matriz2_ofensiva[][10], int &turno);
void guardarMovimiento(const char nombreJugador1[], const char nombreJugador2[], char matriz1[][10], char matriz2[][10], int turno);

struct Jugador
{
    char nombre[30];
} player1, player2;

const char RED[] = "\033[1;31m";
const char BLUE[] = "\033[1;34m";
const char RESET[] = "\033[0m";

int main()
{
    setlocale(LC_ALL, "spanish");

    // Declaración de matrices defensivas y ofensivas para ambos jugadores
    char matriz[10][10], matriz2[10][10];
    char matriz1_ofensiva[10][10], matriz2_ofensiva[10][10];
    
    // Inicializar todas las posiciones de las matrices
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            matriz[i][j] = 'O';
            matriz2[i][j] = 'O';
            matriz1_ofensiva[i][j] = '*';
            matriz2_ofensiva[i][j] = '*';
        }
    }

    int ganador = 0;
    int turno = 1;
    int opcion;

    cout << "¡Batalla Naval!" << endl;
    cout << "1. Iniciar juego nuevo" << endl;
    cout << "2. Cargar partida guardada" << endl;
    cout << "3. Guardar partida actual" << endl;
    cout << "4. Salir" << endl;
    cout << "Ingrese su opción: ";
    cin >> opcion;

    switch (opcion)
    {
    case 1:
        cout << "Ingrese el nombre del primer jugador: ";
        cin >> player1.nombre;
        cout << "Ingrese el nombre del segundo jugador: ";
        cin >> player2.nombre;

        cout << "Ubicación barcos " << BLUE << player1.nombre << RESET << endl;
        ubicarBarcos(matriz, BLUE);
        cout << "Ubicación barcos " << RED << player2.nombre << RESET << endl;
        ubicarBarcos(matriz2, RED);

        cout << "¡Hora de atacar!" << endl;
        ganador = atacar(matriz, matriz2, matriz1_ofensiva, matriz2_ofensiva, turno);

        if (ganador == 1)
        {
            cout << BLUE << "¡¡Felicidades " << player1.nombre << "!!" << RESET << endl;
            cout << "¡¡Has ganado la partida!!" << endl;
        }
        else
        {
            cout << RED << "¡¡Felicidades " << player2.nombre << "!!" << RESET << endl;
            cout << "¡¡Has ganado la partida!!" << endl;
        }
        break;

    case 2:
        if (cargarPartida(player1.nombre, player2.nombre, matriz, matriz2, matriz1_ofensiva, matriz2_ofensiva, turno))
        {
            cout << "Partida cargada exitosamente." << endl;
            ganador = atacar(matriz, matriz2, matriz1_ofensiva, matriz2_ofensiva, turno);
            if (ganador == 1)
            {
                cout << BLUE << "¡¡Felicidades " << player1.nombre << "!!" << RESET << endl;
                cout << "¡¡Has ganado la partida!!" << endl;
            }
            else
            {
                cout << RED << "¡¡Felicidades " << player2.nombre << "!!" << RESET << endl;
                cout << "¡¡Has ganado la partida!!" << endl;
            }
        }
        else
        {
            cout << "No se pudo cargar la partida." << endl;
        }
        break;

    case 3:
        guardarPartida(player1.nombre, player2.nombre, matriz, matriz2, matriz1_ofensiva, matriz2_ofensiva, turno);
        break;

    case 4:
        cout << "Saliendo del juego. ¡Hasta la próxima!" << endl;
        break;

    default:
        cout << "Opción no válida." << endl;
    }
    return 0;
}

// Función para guardar partida
void guardarPartida(const char nombreJugador1[], const char nombreJugador2[], char matriz1[][10], char matriz2[][10], char matriz1_ofensiva[][10], char matriz2_ofensiva[][10], int turno)
{
    char nombrePartida[30];
    cout << "Ingrese un nombre para esta partida guardada: ";
    cin >> nombrePartida;

    ofstream archivo("partidas_guardadas.txt", ios::app);
    if (!archivo.is_open())
    {
        cerr << "Error: No se pudo abrir el archivo para guardar la partida." << endl;
        return;
    }

    archivo << "Partida: " << nombrePartida << endl;
    archivo << nombreJugador1 << endl;
    archivo << nombreJugador2 << endl;
    archivo << turno << endl;

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            archivo << matriz1[i][j];
        }
        archivo << endl;
    }

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            archivo << matriz1_ofensiva[i][j];
        }
        archivo << endl;
    }

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            archivo << matriz2[i][j];
        }
        archivo << endl;
    }

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            archivo << matriz2_ofensiva[i][j];
        }
        archivo << endl;
    }

    archivo.close();
    cout << "Partida guardada exitosamente como: " << nombrePartida << endl;
}

// Función para cargar partida
bool cargarPartida(char nombreJugador1[], char nombreJugador2[], char matriz1[][10], char matriz2[][10], char matriz1_ofensiva[][10], char matriz2_ofensiva[][10], int &turno)
{
    char nombrePartida[30];
    cout << "Ingrese el nombre de la partida que desea cargar: ";
    cin >> nombrePartida;

    ifstream archivo("partidas_guardadas.txt");
    if (!archivo.is_open())
    {
        cerr << "Error: No se pudo abrir el archivo de partidas guardadas." << endl;
        return false;
    }

    string linea;
    bool partidaEncontrada = false;

    while (getline(archivo, linea))
    {
        if (linea == string("Partida: ") + nombrePartida)
        {
            partidaEncontrada = true;
            break;
        }
    }

    if (!partidaEncontrada)
    {
        cout << "No se encontró la partida " << nombrePartida << " en el archivo." << endl;
        return false;
    }

    archivo.getline(nombreJugador1, 30);
    archivo.getline(nombreJugador2, 30);
    archivo >> turno;
    archivo.ignore();

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            archivo >> matriz1[i][j];
        }
    }
    archivo.ignore();

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            archivo >> matriz1_ofensiva[i][j];
        }
    }
    archivo.ignore();

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            archivo >> matriz2[i][j];
        }
    }
    archivo.ignore();

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            archivo >> matriz2_ofensiva[i][j];
        }
    }

    archivo.close();
    cout << "Partida " << nombrePartida << " cargada exitosamente." << endl;
    return true;
}

// Función para ubicar los barcos
void ubicarBarcos(char matriz[][10], const char color[])
{
    int x = 0;
    int y = 0;
    int v = 0;
    int tam;
    char nombre;
    bool elegidos[5] = {false};

    for (int q = 0; q < 5; q++)
    {
        int p = -1;
        bool barcoElegido = false;

        while (!barcoElegido)
        {
            cout << "Ingrese qué tipo de barco desea poner: " << endl;
            cout << "0. Portaviones (5)" << endl;
            cout << "1. Fragata (4)" << endl;
            cout << "2. Crucero (3)" << endl;
            cout << "3. Submarino (3)" << endl;
            cout << "4. Destructor (2)" << endl;
            cout << "  > ";
            cin >> p;

            if (p >= 0 && p <= 4 && !elegidos[p])
            {
                switch (p)
                {
                case 0:
                    tam = 5;
                    nombre = 'P';
                    barcoElegido = true;
                    break;
                case 1:
                    tam = 4;
                    nombre = 'F';
                    barcoElegido = true;
                    break;
                case 2:
                    tam = 3;
                    nombre = 'C';
                    barcoElegido = true;
                    break;
                case 3:
                    tam = 3;
                    nombre = 'S';
                    barcoElegido = true;
                    break;
                case 4:
                    tam = 2;
                    nombre = 'D';
                    barcoElegido = true;
                    break;
                }
            }
            else
            {
                cout << "¡¡Valor inválido o barco ya elegido!!" << endl;
            }
        }

        if (posicionamientoBarcos(matriz, tam, nombre, x, y, v, color))
        {
            elegidos[p] = true;
        }
        else
        {
            q--;
        }
    }
}

// Función para posicionar los barcos en la matriz
int posicionamientoBarcos(char matriz[][10], int tam, char nombre, int x, int y, int v, const char color[])
{
    cout << "¿En qué posición desea poner su barco?" << endl;
    cout << " Posición en filas: ";
    cin >> x;
    cout << " Posición en columnas: ";
    cin >> y;

    cout << "¿Desea posicionarlo en horizontal? (0. Sí, 1. No): ";
    cin >> v;

    if (v == 0)
    {
        if ((y + tam - 1) >= 10)
        {
            cout << "¡¡Posición inválida!!" << endl;
            return false;
        }

        for (int i = 0; i < tam; i++)
        {
            if (matriz[x][y + i] != 'O')
            {
                cout << "¡¡Posición ocupada!!" << endl;
                return false;
            }
        }

        for (int i = 0; i < tam; i++)
        {
            matriz[x][y + i] = nombre;
        }
    }
    else
    {
        if ((x + tam - 1) >= 10)
        {
            cout << "¡¡Posición inválida!!" << endl;
            return false;
        }

        for (int i = 0; i < tam; i++)
        {
            if (matriz[x + i][y] != 'O')
            {
                cout << "¡¡Posición ocupada!!" << endl;
                return false;
            }
        }

        for (int i = 0; i < tam; i++)
        {
            matriz[x + i][y] = nombre;
        }
    }

    imprimirMatriz(matriz, color);
    return true;
}
int atacar(char matriz1[][10], char matriz2[][10], char matriz1_ofensiva[][10], char matriz2_ofensiva[][10], int &turno) {
    int contador1 = 0;
    int contador2 = 0;
    int x = 0;
    int y = 0;
    int opcionGuardar;

    while (true) {
        while (true) {
            cout << BLUE << "Turno " << player1.nombre << RESET << endl;
            cout << "Ingrese las coordenadas para atacar" << endl;
            cout << "Fila: ";
            cin >> x;
            cout << "Columna: ";
            cin >> y;

            if (x >= 10 || y >= 10 || matriz1_ofensiva[x][y] != '*') {
                cout << "¡¡Coordenada inválida!!" << endl;
                continue;
            }

            if (matriz2[x][y] == 'O') {
                matriz1_ofensiva[x][y] = 'O';
                cout << "¡Has fallado el tiro!" << endl;
                imprimirMatriz(matriz1_ofensiva, BLUE);
                break;
            } else {
                matriz1_ofensiva[x][y] = 'X';
                cout << "¡Le atinaste!" << endl;
                contador1++;
                imprimirMatriz(matriz1_ofensiva, BLUE);
                if (contador1 == 17) // Este valor asume que los barcos ocupan 17 espacios en total
                    return 1;
            }
        }

        turno++; // Cambiar turno al jugador 2

        while (true) {
            cout << RED << "Turno " << player2.nombre << RESET << endl;
            cout << "Ingrese las coordenadas para atacar" << endl;
            cout << "Fila: ";
            cin >> x;
            cout << "Columna: ";
            cin >> y;

            if (x >= 10 || y >= 10 || matriz2_ofensiva[x][y] != '*') {
                cout << "¡¡Coordenada inválida!!" << endl;
                continue;
            }

            if (matriz1[x][y] == 'O') {
                matriz2_ofensiva[x][y] = 'O';
                cout << "¡Has fallado el tiro!" << endl;
                imprimirMatriz(matriz2_ofensiva, RED);
                break;
            } else {
                matriz2_ofensiva[x][y] = 'X';
                cout << "¡Le atinaste!" << endl;
                contador2++;
                imprimirMatriz(matriz2_ofensiva, RED);
                if (contador2 == 17) // Mismo valor de espacios ocupados por los barcos
                    return 2;
            }
        }

        turno++; // Cambiar turno al jugador 1
    }
}


// Función para imprimir la matriz de cada jugador
void imprimirMatriz(char matriz[][10], const char color[])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (matriz[i][j] != 'O')
            {
                cout << color << matriz[i][j] << RESET << " ";
            }
            else
            {
                cout << matriz[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

