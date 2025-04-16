#ifndef BATALLA_HPP
#define BATALLA_HPP

#include <iostream>
#include <vector>
#include <memory>
#include "../Ej1/IPersonajes.hpp"
#include "../Ej1/IArmas.hpp"
#include "../Ej2/PersonajeFactory.hpp"

// Opciones de ataque
enum Ataque { GOLPE_FUERTE = 1, GOLPE_RAPIDO, DEFENSA_Y_GOLPE };

/**
 * Muestra el menú de personajes disponibles para elegir.
 */
void mostrarMenuPersonajes();

/**
 * Muestra el menú de armas disponibles para elegir.
 */
void mostrarMenuArmas();

/**
 * Determina el resultado de una ronda.
 * @param ataque1 Ataque del jugador 1.
 * @param ataque2 Ataque del jugador 2.
 * @return 1 si el jugador 1 es dañado, 2 si el jugador 2 es dañado, 0 si es un empate.
 */
int calcularDanio(Ataque ataque1, Ataque ataque2);

/**
 * Ejecuta la batalla entre dos personajes.
 * Permite a los jugadores elegir sus ataques y calcula el daño.
 * La batalla continúa hasta que uno de los personajes se queda sin HP.
 */
void ejecutarBatalla();

#endif // BATALLA_HPP