#include "main.hpp"
#include <cstdlib>
#include <ctime>
#include <utility>

using namespace std;

void mostrarMenuPersonajes() {
    cout << "Elija su personaje:\n";
    cout << "0. Barbaro\n";
    cout << "1. Paladin\n";
    cout << "2. Caballero\n";
    cout << "3. Mercenario\n";
    cout << "4. Gladiador\n";
    cout << "5. Hechicero\n";
    cout << "6. Conjurador\n";
    cout << "7. Brujo\n";
    cout << "8. Nigromante\n";
}

void mostrarMenuArmas() {
    cout << "Elija su arma:\n";
    cout << "0. Hacha Simple\n";
    cout << "1. Hacha Doble\n";
    cout << "2. Espada\n";
    cout << "3. Lanza\n";
    cout << "4. Garrote\n";
    cout << "5. Baston\n";
    cout << "6. Libro de Hechizos\n";
    cout << "7. Pocion\n";
    cout << "8. Amuleto\n";
}

int calcularDanio(Ataque ataque1, Ataque ataque2) {
    if (ataque1 == GOLPE_FUERTE && ataque2 == GOLPE_RAPIDO) return 2; // Jugador 2 recibe daño
    if (ataque1 == GOLPE_RAPIDO && ataque2 == DEFENSA_Y_GOLPE) return 2; // Jugador 2 recibe daño
    if (ataque1 == DEFENSA_Y_GOLPE && ataque2 == GOLPE_FUERTE) return 2; // Jugador 2 recibe daño
    if (ataque1 == ataque2) {
        return 0; // Empate, nadie recibe daño
    }
    return 1; // Daña al Jugador 1
}

void ejecutarBatalla() {
    srand(time(0)); // Inicializar generador de números aleatorios

    // Menú para elegir personaje y arma del jugador 1
    mostrarMenuPersonajes();
    cout << "Elija su personaje (0-8): ";
    int tipoJugador1;
    cin >> tipoJugador1;

    mostrarMenuArmas();
    cout << "Elija su arma (0-8): ";
    int armaJugador1;
    cin >> armaJugador1;

    // Crear personaje y arma del jugador 1
    vector<unique_ptr<InterfazArma>> armasJugador1;
    armasJugador1.push_back(Factory::crearArma(armaJugador1));
    auto jugador1 = Factory::crearPersonaje(tipoJugador1, std::move(armasJugador1));

    // Crear personaje y arma del jugador 2 (aleatorio)
    int tipoJugador2 = rand() % 9; // Elegir aleatoriamente un personaje
    int armaJugador2 = rand() % 9; // Elegir aleatoriamente un arma
    vector<unique_ptr<InterfazArma>> armasJugador2;
    armasJugador2.push_back(Factory::crearArma(armaJugador2));
    auto jugador2 = Factory::crearPersonaje(tipoJugador2, std::move(armasJugador2));

    int hpJugador1 = 100;
    int hpJugador2 = 100;

    // Mostrar información inicial
    cout << "Jugador 1 (" << jugador1->getNombre() << ") con " << jugador1->getArmas()[0]->getNombre() << " tiene " << hpJugador1 << " HP.\n";
    cout << "Jugador 2 (" << jugador2->getNombre() << ") con " << jugador2->getArmas()[0]->getNombre() << " tiene " << hpJugador2 << " HP.\n";
    cout << "¡Que comience la batalla!\n";

    // Batalla
    while (hpJugador1 > 0 && hpJugador2 > 0) {
        cout << "----------------------------------------\n";
        cout << "Jugador 1 (" << jugador1->getNombre() << ") tiene " << hpJugador1 << " HP.\n";
        cout << "Jugador 2 (" << jugador2->getNombre() << ") tiene " << hpJugador2 << " HP.\n";

        // Jugador 1 elige su ataque
        cout << "Su opción: (1) Golpe Fuerte, (2) Golpe Rápido, (3) Defensa y Golpe: ";
        int opcionJugador1;
        cin >> opcionJugador1;

        // Validar entrada del jugador 1
        while (opcionJugador1 < 1 || opcionJugador1 > 3) {
            cout << "Opción inválida. Intente de nuevo: ";
            cin >> opcionJugador1;
        }
        cout << "Jugador 1 eligió: " << opcionJugador1 << "\n";

        // Jugador 2 elige su ataque aleatoriamente
        int opcionJugador2 = rand() % 3 + 1;
        cout << "Jugador 2 eligió: " << opcionJugador2 << "\n";

        // Calcular daño
        int danio = calcularDanio(static_cast<Ataque>(opcionJugador1), static_cast<Ataque>(opcionJugador2)); // Daño que recibe el jugador 2

        if (danio == 1) {
            hpJugador1 -= 10;
            cout << jugador2->getNombre() << " ataca con " << jugador2->getArmas()[0]->getNombre()
                 << " y hace 10 puntos de daño.\n";
        } else if (danio == 2) {
            hpJugador2 -= 10;
            cout << jugador1->getNombre() << " ataca con " << jugador1->getArmas()[0]->getNombre()
                 << " y hace 10 puntos de daño.\n";
        } else {
            cout << "Ambos jugadores eligieron la misma acción. No hay daño.\n";
        }
    }

    // Resultado final
    if (hpJugador1 > 0) {
        cout << "¡Jugador 1 (" << jugador1->getNombre() << ") gana la batalla!\n";
    } else {
        cout << "¡Jugador 2 (" << jugador2->getNombre() << ") gana la batalla!\n";
    }
}

int main() {
    ejecutarBatalla();
    return 0;
}