#include <iostream>
#include <memory>
#include "Guerreros.hpp"
#include "Magos.hpp"
#include "ArmasCombate.hpp"
#include "ArmasMagicas.hpp"

using namespace std;

int main() {
    // Crear guerreros
    Barbaro barbaro(100, 50, 30, "Ragnar");
    Paladin paladin(120, 40, 20, 10, "Arthur", 50, 30);

    // Crear magos
    Hechicero hechicero(100, 80, 10, 50, 20, "Merlin", 40, 5);
    Nigromante nigromante(90, 70, 15, 40, 25, "Necro", 50, 3);

    // Crear armas de combate
    unique_ptr<InterfazArma> espada = make_unique<Espada>(30, 10, 1, "Acero", "Excalibur", 15, 0.2);
    unique_ptr<InterfazArma> hacha = make_unique<HachaSimple>(25, 8, 1, "Hierro", "Hacha de Guerra", 12);

    // Crear armas mágicas
    unique_ptr<InterfazArma> baston = make_unique<Baston>(40, 15, "Madera", "Bastón Arcano", 100, 1, true, 50, "Fuego", 1.5);
    unique_ptr<InterfazArma> libro = make_unique<Libro>(35, 12, "Papel", "Necronomicon", 50, true, 20, "Latín");

    // Equipar armas a los personajes
    barbaro.equiparArma(std::move(espada), true);
    paladin.equiparArma(std::move(hacha), true);
    hechicero.equiparArma(std::move(baston), true);
    nigromante.equiparArma(std::move(libro), true);

    // Realizar ataques
    cout << "\n--- Ataques de los personajes ---\n";
    barbaro.atacar();
    paladin.atacar();
    hechicero.atacar();
    nigromante.atacar();

    // Mostrar estadísticas
    cout << "\n--- Estadísticas de los personajes ---\n";
    cout << barbaro.obtenerEstadisticas() << endl;
    cout << paladin.obtenerEstadisticas() << endl;
    cout << hechicero.obtenerEstadisticas() << endl;
    cout << nigromante.obtenerEstadisticas() << endl;

    // Realizar acciones adicionales
    cout << "\n--- Acciones adicionales ---\n";
    paladin.invocarLuzSagrada();
    nigromante.invocarMuertos();
    hechicero.lanzarHechizo("Bola de Fuego");
    barbaro.invocarDiosNordico("Thor");

    return 0;
}