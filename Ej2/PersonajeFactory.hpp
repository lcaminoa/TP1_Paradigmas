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
    /**
     * Crea un personaje basado en el tipo especificado.
     * @param personaje Tipo de personaje a crear (0-8).
     * @param Armas Opcional: vector de armas a equipar al personaje.
     * @return Un unique_ptr al personaje creado.
     * @throws invalid_argument Si el tipo de personaje no es válido.
     */
    static unique_ptr<InterfazPersonaje> crearPersonaje(int personaje, vector<unique_ptr<InterfazArma>> Armas = {});

    /**
     * Crea un arma basada en el tipo especificado.
     * @param tipo Tipo de arma a crear (0-8).
     * @return Un unique_ptr al arma creada.
     * @throws invalid_argument Si el tipo de arma no es válido.
     */
    static unique_ptr<InterfazArma> crearArma(int tipo);
};