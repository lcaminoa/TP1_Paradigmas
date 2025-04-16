#include "PersonajeFactory.hpp"

unique_ptr<InterfazArma> Factory::crearArma(int tipo) {
    try {
        switch (tipo) {
            case 0:
                return make_unique<HachaSimple>(25, 8, 1, "Hacha Simple", 12);
            case 1:
                return make_unique<HachaDoble>(35, 12, 1, "Hacha Doble", 20, 15);
            case 2:
                return make_unique<Espada>(30, 10, 1, "Espada", 15, 0.2);
            case 3:
                return make_unique<Lanza>(20, 15, 2, "Lanza", 10, 5);
            case 4:
                return make_unique<Garrote>(15, 5, 1, "Garrote", 5, 3);
            case 5:
                return make_unique<Baston>(40, 15, "Bastón", 8, true, 50, "Fuego");
            case 6:
                return make_unique<Libro>(35, 12, "Libro de Hechizos", 50, true, 20, "Latín");
            case 7:
                return make_unique<Pocion>(10, 5, "Poción", 20, "Curativa", 3, 10);
            case 8:
                return make_unique<Amuleto>(15, 10, "Amuleto", 30, "Protección");
            default:
                return nullptr;
        }
    } catch (const bad_alloc& e) {
        cout << "Error al crear el arma." << endl;
        return nullptr;
    }
}

unique_ptr<InterfazPersonaje> Factory::crearPersonaje(int personaje, vector<unique_ptr<InterfazArma>> Armas) {
    try {
        unique_ptr<InterfazPersonaje> nuevoPersonaje;

        // Crear el personaje según el tipo
        switch (personaje) {
            case 0:
                nuevoPersonaje = make_unique<Barbaro>(100, 50, 30, "Barbaro");
                break;
            case 1:
                nuevoPersonaje = make_unique<Paladin>(100, 40, 20, "Paladin", 50, 30);
                break;
            case 2:
                nuevoPersonaje = make_unique<Caballero>(100, 45, 15, "Caballero", 40, 20);
                break;
            case 3:
                nuevoPersonaje = make_unique<Mercenario>(100, 55, 10, "Mercenario", 100, 80);
                break;
            case 4:
                nuevoPersonaje = make_unique<Gladiador>(100, 60, 15, "Gladiador", 50, 30);
                break;
            case 5:
                nuevoPersonaje = make_unique<Hechicero>(80, 100, 10, 50, 5, "Hechicero", 40, 5);
                break;
            case 6:
                nuevoPersonaje = make_unique<Conjurador>(90, 100, 15, 40, 10, "Conjurador", 10, 4);
                break;
            case 7:
                nuevoPersonaje = make_unique<Brujo>(85, 100, 20, 45, 8, "Brujo", 35, 6);
                break;
            case 8:
                nuevoPersonaje = make_unique<Nigromante>(95, 100, 25, 35, 12, "Nigromante", 50, 3);
                break;
            default:
                throw invalid_argument("Tipo de personaje no válido");
        }

        // Asignar las armas al personaje
        bool esPrimaria = true; // La primera arma será primaria
        for (auto& arma : Armas) {
            nuevoPersonaje->equiparArma(std::move(arma), esPrimaria);
            esPrimaria = false; // Las siguientes armas serán secundarias
        }

        return nuevoPersonaje;

    } catch (const bad_alloc& e) {
        cout << "Error al crear el personaje" << endl;
        return nullptr;
    }
}