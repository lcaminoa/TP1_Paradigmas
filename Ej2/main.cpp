#include "PersonajeFactory.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

using namespace std;

// Función para generar un número aleatorio en un rango [min, max]
int numAleatorio(int min, int max) {
    return min + (rand() % (max - min + 1));
}

int main() {
    srand(time(0)); // Inicializar el generador de números aleatorios

    try {
        // Generar número aleatorio entre 3 y 7 para determinar cuántos magos y guerreros se crearán
        int cantidadPersonajes = numAleatorio(3, 7);

        cout << "Se crearán " << cantidadPersonajes << " magos y " << cantidadPersonajes << " guerreros.\n";

        // Crear magos
        for (int i = 0; i < cantidadPersonajes; ++i) {
            // Generar número aleatorio entre 0 y 2 para determinar cuántas armas tendrá el mago
            int cantidadArmas = numAleatorio(0, 2);

            if (cantidadArmas > 0) {
                vector<unique_ptr<InterfazArma>> armas;

                // Generar las armas del mago
                for (int j = 0; j < cantidadArmas; ++j) {
                    armas.push_back(Factory::crearArma(numAleatorio(5, 8))); // Armas mágicas
                }

                // Crear el mago con armas
                auto mago = Factory::crearPersonaje(numAleatorio(5, 8), std::move(armas));
                cout << "Creado mago: " << mago->getNombre() << " con " << cantidadArmas << " armas.\n";
            } else {
                // Crear el mago sin armas
                auto mago = Factory::crearPersonaje(numAleatorio(5, 8));
                cout << "Creado mago: " << mago->getNombre() << " sin armas.\n";
            }
        }

        // Crear guerreros
        for (int i = 0; i < cantidadPersonajes; ++i) {
            // Generar número aleatorio entre 0 y 2 para determinar cuántas armas tendrá el guerrero
            int cantidadArmas = numAleatorio(0, 2);

            if (cantidadArmas > 0) {
                vector<unique_ptr<InterfazArma>> armas;

                // Generar las armas del guerrero
                for (int j = 0; j < cantidadArmas; ++j) {
                    armas.push_back(Factory::crearArma(numAleatorio(0, 4))); // Armas físicas
                }

                // Crear el guerrero con o sin armas
                auto guerrero = Factory::crearPersonaje(numAleatorio(0, 4), std::move(armas));
                cout << "Creado guerrero: " << guerrero->getNombre() << " con " << cantidadArmas << " armas.\n";
            } else {
                // Crear el guerrero sin armas
                auto guerrero = Factory::crearPersonaje(numAleatorio(0, 4));
                cout << "Creado guerrero: " << guerrero->getNombre() << " sin armas.\n";
            }
        }

    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}