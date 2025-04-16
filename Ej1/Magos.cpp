#include "Magos.hpp"
#include <iostream>
#include <utility>

using namespace std;

Mago::Mago(int m, int s, int f, int i, int e, string nom, string tipo)
    : mana(m), salud(s), fuerza(f), inteligencia(i), experiencia(e), nombre(nom), tipo(tipo), armas(2) {}

void Mago::equiparArma(unique_ptr<InterfazArma> arma, bool esPrimaria) {
    if (esPrimaria) {
        armas[0] = std::move(arma); // Equipar el arma primaria
        cout << nombre << " ha equipado el arma primaria: " << armas[0]->getNombre() << ".\n";
    } else {
        armas[1] = std::move(arma); // Equipar el arma secundaria
        cout << nombre << " ha equipado el arma secundaria: " << armas[1]->getNombre() << ".\n";
    }
}

void Mago::desequiparArma(bool esPrimaria) {
    if (esPrimaria && armas[0]) {
        cout << nombre << " ha desequipado el arma primaria: " << armas[0]->getNombre() << ".\n";
        armas[0].reset();
    } else if (!esPrimaria && armas[1]) {
        cout << nombre << " ha desequipado el arma secundaria: " << armas[1]->getNombre() << ".\n";
        armas[1].reset();
    } else {
        cout << "No hay un arma equipada en esa posición para desequipar.\n";
    }
}

const vector<unique_ptr<InterfazArma>>& Mago::getArmas() const {
    return armas;
}

int Mago::calcularDanio() const {
    int danioTotal = inteligencia;
    if (armas[0]) {
        danioTotal += armas[0]->getPoder();
    }
    if (armas[1]) {
        danioTotal += armas[1]->getPoder();
    }
    return danioTotal;
}

void Mago::atacar() {
    if (mana < 10) {
        cout << nombre << " no tiene suficiente mana para atacar.\n";
        return;
    }

    if (armas[0] && armas[1]) {
        int danioPrimaria = armas[0]->getPoder();
        int danioSecundaria = armas[1]->getPoder();
        cout << nombre << " lanza un ataque mágico utilizando " << armas[0]->getNombre() << " y " << armas[1]->getNombre()
             << ", causando un total de " << (inteligencia + danioPrimaria + danioSecundaria) << " de daño.\n";
        armas[0]->usar();
        armas[1]->usar();
    } else if (armas[0]) {
        int danioPrimaria = armas[0]->getPoder();
        cout << nombre << " lanza un ataque mágico con " << armas[0]->getNombre() << ", causando " << (inteligencia + danioPrimaria) << " de daño.\n";
        armas[0]->usar();
    } else if (armas[1]) {
        int danioSecundaria = armas[1]->getPoder();
        cout << nombre << " lanza un ataque mágico con " << armas[1]->getNombre() << ", causando " << (inteligencia + danioSecundaria) << " de daño.\n";
        armas[1]->usar();
    } else {
        cout << nombre << " lanza un hechizo básico, causando " << inteligencia << " de daño.\n";
    }

    mana -= 10; // Reducir mana por el ataque
}

void Mago::recibirDanio(int danio) {
    salud -= danio;
    cout << nombre << " ha recibido " << danio << " puntos de daño. Salud restante: " << salud << ".\n";
    if (salud <= 0) {
        salud = 0;
        morir();
    }
}

string Mago::getNombre() const {
    return nombre; // Devolver el nombre del mago
}

string Mago::getTipo() const {
    return tipo; // Devolver el tipo del mago
}

Mago::~Mago() = default; // unique_ptr libera las armas automáticamente


// Hechicero

Hechicero::Hechicero(int m, int s, int f, int i, int e, string nom, int poder, int nivelHechizo)
    : Mago(m, s, f, i, e, nom, "Hechicero"), poderMagico(poder), nivelHechizo(nivelHechizo) {}

void Hechicero::lanzarHechizo(string hechizo) {
    if (mana >= 20) {
        cout << nombre << " lanza el hechizo '" << hechizo << "' con nivel " << nivelHechizo << ".\n";
        mana -= 20; // Consumir mana por el hechizo
    } else {
        cout << nombre << " no tiene suficiente mana para lanzar el hechizo.\n";
    }
}

int Hechicero::calcularDanio() const {
    int danioBase = Mago::calcularDanio();
    int bonificacionPoderMagico = (poderMagico / 10) * 5; // 5% de bonificación por cada 10 puntos de poder mágico
    return danioBase + bonificacionPoderMagico;
}

void Hechicero::ataqueEspecial() {
    if (mana >= 20) { // Activar ataque especial si tiene suficiente mana
        cout << nombre << " lanza un HECHIZO PODEROSO!\n";
        int danioEspecial = calcularDanio() * 2; // Duplicar el daño
        cout << nombre << " causa un daño mágico de " << danioEspecial << " puntos.\n";
        mana -= 20; // Consumir mana
        return;
    }

    // Si no se cumplen las condiciones, usar el ataque normal
    Mago::atacar();
}

void Hechicero::efectoCurativo() {
    const int manaNecesario = 15; // Mana necesaria para curarse
    const int saludRestaurada = 30; // Salud que se restaura

    if (mana >= manaNecesario) {
        salud += saludRestaurada;
        mana -= manaNecesario; // Consumir solo la cantidad fija de mana
        cout << nombre << " lanza un hechizo de curación, restaurando " << saludRestaurada 
             << " puntos de salud a cambio de " << manaNecesario << " puntos de mana.\n";
    } else {
        cout << nombre << " no tiene suficiente mana para lanzar un hechizo de curación.\n";
    }
}

void Hechicero::morir() const {
    cout << nombre << " ha caído en combate, pero su aura sigue en el aire.\n";
}

string Hechicero::obtenerEstadisticas() const {
    string estadisticas = "Hechicero: " + nombre +
                          "\nMana: " + to_string(mana) +
                          "\nSalud: " + to_string(salud) +
                          "\nFuerza: " + to_string(fuerza) +
                          "\nInteligencia: " + to_string(inteligencia) +
                          "\nExperiencia: " + to_string(experiencia) +
                          "\nPoder Mágico: " + to_string(poderMagico) +
                          "\nNivel de Hechizo: " + to_string(nivelHechizo);
    if (armas[0]) {
        estadisticas += "\nArma primaria: " + armas[0]->getNombre();
    } else {
        estadisticas += "\nArma primaria: Ninguna";
    }
    if (armas[1]) {
        estadisticas += "\nArma secundaria: " + armas[1]->getNombre();
    } else {
        estadisticas += "\nArma secundaria: Ninguna";
    }
    return estadisticas;
    return estadisticas;
}


// Conjurador
Conjurador::Conjurador(int m, int s, int f, int i, int e, string nom, int invocaciones, int poder)
    : Mago(m, s, f, i, e, nom, "Conjurador"), cantidadInvocaciones(invocaciones), poderInvocacion(poder) {}

void Conjurador::invocarPaimon() {
    if (cantidadInvocaciones > 0 && mana >= 50) {
        cout << nombre << " invoca al poderoso demonio Paimon con un poder de " << poderInvocacion * 2 << "!\n";
        cout << "Paimon aparece en una explosión de fuego y caos, listo para destruir a los enemigos.\n";
        cantidadInvocaciones--;
        mana -= 50; // Consumir una gran cantidad de mana por la invocación especial
    } else if (cantidadInvocaciones <= 0) {
        cout << nombre << " no tiene más invocaciones disponibles para invocar a Paimon.\n";
    } else {
        cout << nombre << " no tiene suficiente mana para invocar a Paimon.\n";
    }
}

int Conjurador::calcularDanio() const {
    int danioBase = Mago::calcularDanio();
    int bonificacionPoderInvocacion = (poderInvocacion / 10) * 4; // 4% de bonificación por cada 10 puntos de poder de invocación
    return danioBase + bonificacionPoderInvocacion;
}

void Conjurador::ataqueEspecial() {
    if (cantidadInvocaciones > 0) { // Activar ataque especial si tiene invocaciones disponibles
        cout << nombre << " invoca un espíritu para atacar al enemigo!\n";
        int danioEspecial = calcularDanio() * 2; // Duplicar el daño
        cout << nombre << " causa un daño devastador de " << danioEspecial << " puntos.\n";
        cantidadInvocaciones--; // Consumir una invocación
        return;
    }

    // Si no se cumplen las condiciones, usar el ataque normal
    Mago::atacar();
}

void Conjurador::efectoCurativo() {
    if (cantidadInvocaciones > 0) {
        salud += 25; // Restaura salud
        fuerza += 5; // Aumenta la fuerza
        cantidadInvocaciones--; // Consume una invocación
        cout << nombre << " invoca un espíritu protector, restaurando 25 puntos de salud y aumentando su fuerza en 5 puntos.\n";
    } else {
        cout << nombre << " no tiene suficientes invocaciones para invocar un espíritu protector.\n";
    }
}

void Conjurador::morir() const {
    cout << nombre << " ha caído en combate, pero seguirá invocando sombras en el más allá.\n";
}

string Conjurador::obtenerEstadisticas() const {
    string estadisticas = "Conjurador: " + nombre +
                          "\nMana: " + to_string(mana) +
                          "\nSalud: " + to_string(salud) +
                          "\nFuerza: " + to_string(fuerza) +
                          "\nInteligencia: " + to_string(inteligencia) +
                          "\nExperiencia: " + to_string(experiencia) +
                          "\nCantidad de Invocaciones: " + to_string(cantidadInvocaciones) +
                          "\nPoder de Invocación: " + to_string(poderInvocacion);
    if (armas[0]) {
        estadisticas += "\nArma primaria: " + armas[0]->getNombre();
    } else {
        estadisticas += "\nArma primaria: Ninguna";
    }
    if (armas[1]) {
        estadisticas += "\nArma secundaria: " + armas[1]->getNombre();
    } else {
        estadisticas += "\nArma secundaria: Ninguna";
    }
    return estadisticas;
}


// Brujo

Brujo::Brujo(int m, int s, int f, int i, int e, string nom, int poder, int nivel)
    : Mago(m, s, f, i, e, nom, "Brujo"), poderOscuro(poder), nivelMaldicion(nivel) {}

void Brujo::lanzarMaldicion(string objetivo) {
    if (mana >= 30) {
        cout << nombre << " lanza una maldición oscura sobre " << objetivo << " con nivel " << nivelMaldicion << ".\n";
        mana -= 30; // Consumir mana por la maldición
    } else {
        cout << nombre << " no tiene suficiente mana para lanzar la maldición.\n";
    }
}

int Brujo::calcularDanio() const {
    int danioBase = Mago::calcularDanio();
    int bonificacionPoderOscuro = (poderOscuro / 10) * 6; // 6% de bonificación por cada 10 puntos de poder oscuro
    return danioBase + bonificacionPoderOscuro;
}

void Brujo::ataqueEspecial() {
    if (mana >= 30) { // Activar ataque especial si tiene suficiente mana
        cout << nombre << " lanza una MALDICIÓN OSCURA!\n";
        int danioEspecial = calcularDanio() * 2; // Duplicar el daño
        cout << nombre << " causa un daño oscuro de " << danioEspecial << " puntos.\n";
        mana -= 30; // Consumir mana
        return;
    }

    // Si no se cumplen las condiciones, usar el ataque normal
    Mago::atacar();
}

void Brujo::invocarEspirituDeMerlin() {
    if (mana >= 50) {
        cout << nombre << " invoca el espíritu de Merlín, obteniendo un aumento de poder oscuro y regeneración de mana.\n";
        poderOscuro += 10; // Incrementar el poder oscuro
        mana += 20; // Regenerar mana
    } else {
        cout << nombre << " no tiene suficiente mana para invocar el espíritu de Merlín.\n";
    }
}

void Brujo::efectoCurativo() {
    if (fuerza > 10) {
        int saludRestaurada = fuerza / 2; // Convierte la mitad de su fuerza en salud
        salud += saludRestaurada;
        fuerza -= 10; // Reduce fuerza
        poderOscuro += 15; // Aumenta su poder oscuro
        cout << nombre << " realiza un pacto oscuro, sacrificando fuerza para restaurar " << saludRestaurada 
             << " puntos de salud y aumentando su poder oscuro en 15.\n";
    } else {
        cout << nombre << " no tiene suficiente fuerza para realizar un pacto oscuro.\n";
    }
}

void Brujo::morir() const {
    cout << nombre << " ha caído en combate, su gato negro llora su pérdida.\n";
}

string Brujo::obtenerEstadisticas() const {
    string estadisticas = "Brujo: " + nombre +
                          "\nMana: " + to_string(mana) +
                          "\nSalud: " + to_string(salud) +
                          "\nFuerza: " + to_string(fuerza) +
                          "\nInteligencia: " + to_string(inteligencia) +
                          "\nExperiencia: " + to_string(experiencia) +
                          "\nPoder Oscuro: " + to_string(poderOscuro) +
                          "\nNivel de Maldición: " + to_string(nivelMaldicion);
    if (armas[0]) {
        estadisticas += "\nArma primaria: " + armas[0]->getNombre();
    } else {
        estadisticas += "\nArma primaria: Ninguna";
    }
    if (armas[1]) {
        estadisticas += "\nArma secundaria: " + armas[1]->getNombre();
    } else {
        estadisticas += "\nArma secundaria: Ninguna";
    }
    return estadisticas;
}


// Nigromante

Nigromante::Nigromante(int m, int s, int f, int i, int e, string nom, int poder, int muertos)
    : Mago(m, s, f, i, e, nom, "Nigromante"), poderNecromancia(poder), cantidadMuertosInvocados(muertos) {}

void Nigromante::invocarMuertos() {
    if (cantidadMuertosInvocados > 0 && mana >= 40) {
        cout << nombre << " invoca a " << cantidadMuertosInvocados << " muertos para luchar a su lado.\n";
        cantidadMuertosInvocados--;
        mana -= 40; // Consumir mana por la invocación
    } else if (cantidadMuertosInvocados <= 0) {
        cout << nombre << " no tiene más muertos para invocar.\n";
    } else {
        cout << nombre << " no tiene suficiente mana para invocar muertos.\n";
    }
}

int Nigromante::calcularDanio() const {
    int danioBase = Mago::calcularDanio();
    int bonificacionPoderNecromancia = (poderNecromancia / 10) * 5; // 5% de bonificación por cada 10 puntos de poder de necromancia
    return danioBase + bonificacionPoderNecromancia;
}

void Nigromante::ataqueEspecial() {
    if (cantidadMuertosInvocados > 0) { // Activar ataque especial si tiene muertos disponibles
        cout << nombre << " invoca a los muertos para atacar al enemigo!\n";
        int danioEspecial = calcularDanio() * 2; // Duplicar el daño
        cout << nombre << " causa un daño devastador de " << danioEspecial << " puntos.\n";
        cantidadMuertosInvocados--; // Consumir un muerto invocado
        return;
    }

    // Si no se cumplen las condiciones, usar el ataque normal
    Mago::atacar();
}

void Nigromante::realizarSacrificioOscuro() {
    if (salud > 20) {
        cout << nombre << " realiza un sacrificio oscuro, perdiendo salud pero aumentando su poder de necromancia.\n";
        salud -= 20; // Reducir salud
        poderNecromancia += 15; // Aumentar poder de necromancia
        mana += 30; // Regenerar mana
    } else {
        cout << nombre << " no tiene suficiente salud para realizar un sacrificio oscuro.\n";
    }
}

void Nigromante::efectoCurativo() {
    if (cantidadMuertosInvocados > 0) {
        salud += 30; // Restaura salud
        mana += 20; // Aumenta mana
        poderNecromancia += 10; // Incrementa su poder de necromancia
        cantidadMuertosInvocados--; // Consume un muerto invocado
        cout << nombre << " sacrifica a uno de sus muertos invocados, restaurando 30 puntos de salud, ganando 20 de mana y aumentando su poder de necromancia en 10.\n";
    } else {
        cout << nombre << " no tiene muertos invocados para sacrificar.\n";
    }
}

void Nigromante::morir() const {
    cout << nombre << " ha caído en combate, pero su espíritu sigue buscando almas.\n";
}

string Nigromante::obtenerEstadisticas() const {
    string estadisticas = "Nigromante: " + nombre +
                          "\nMana: " + to_string(mana) +
                          "\nSalud: " + to_string(salud) +
                          "\nFuerza: " + to_string(fuerza) +
                          "\nInteligencia: " + to_string(inteligencia) +
                          "\nExperiencia: " + to_string(experiencia) +
                          "\nPoder de Necromancia: " + to_string(poderNecromancia) +
                          "\nCantidad de Muertos Invocados: " + to_string(cantidadMuertosInvocados);
    if (armas[0]) {
        estadisticas += "\nArma primaria: " + armas[0]->getNombre();
    } else {
        estadisticas += "\nArma primaria: Ninguna";
    }
    if (armas[1]) {
        estadisticas += "\nArma secundaria: " + armas[1]->getNombre();
    } else {
        estadisticas += "\nArma secundaria: Ninguna";
    }
    return estadisticas;
}