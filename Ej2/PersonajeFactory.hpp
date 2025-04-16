#include <memory>
#include <string>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "../Ej1/Guerreros.hpp"
#include "../Ej1/Magos.hpp"
#include "../Ej1/ArmasCombate.hpp"
#include "../Ej1/ArmasMagicas.hpp"

using namespace std;

class Factory {
    public:
    static unique_ptr<InterfazPersonaje> crearPersonaje(int personaje, vector<unique_ptr<InterfazArma>> Armas = {});
    static unique_ptr<InterfazArma> crearArma(int tipo);
};