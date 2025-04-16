#include "ArmasCombate.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// ArmaDeCombate

ArmaDeCombate::ArmaDeCombate(int dano, int dur, int niv, string nom, string tipo)
    : danoFisico(dano), durabilidad(dur), nivel(niv), nombre(nom), tipo(tipo) {}

int ArmaDeCombate::getPoder() const {
    return danoFisico; // Devuelve el daño físico del arma
}

string ArmaDeCombate::getNombre() const {
    return nombre; // Devuelve el nombre del arma
}

string ArmaDeCombate::getTipo() const {
    return tipo; // Devuelve el tipo de arma
}

bool ArmaDeCombate::puedeUsarse() const {
    return durabilidad > 0; // El arma puede usarse si tiene durabilidad
}

string ArmaDeCombate::getInfo() const {
    return "Arma de Combate: " + nombre +
           "\nDaño Físico: " + to_string(danoFisico) +
           "\nDurabilidad: " + to_string(durabilidad) +
           "\nNivel: " + to_string(nivel);
}


// HachaSimple

HachaSimple::HachaSimple(int dano, int dur, int niv, string nom, double filoInicial)
    : ArmaDeCombate(dano, dur, niv, nom, "HachaSimple"), filo(filoInicial) {}

bool HachaSimple::estaAfilado() const {
    return filo > 10; // Está afilado si el filo es mayor a 10
}

void HachaSimple::usar() {
    if (durabilidad > 0) {
        double danoTotal = (danoFisico + (estaAfilado() ? filo * 1.5 : filo)) * (1 + nivel * 0.1);
        cout << "Usando el hacha " << nombre << ". Daño causado: " << danoTotal << ".\n";
        reducirDurabilidad();
        filo -= 1; // Reducir el filo al usar el hacha
        if (filo < 0) filo = 0; // Asegurarse de que el filo no sea negativo
        cout << "El filo del hacha " << nombre << " se ha reducido a " << filo << ".\n";
    } else {
        cout << "El hacha " << nombre << " está rota y no puede ser usada.\n";
    }
}

void HachaSimple::afilar() {
    filo += 5; // Aumentar el filo al afilar
    cout << "El hacha " << nombre << " ha sido afilada. Nuevo filo: " << filo << ".\n";
}

void HachaSimple::reducirDurabilidad() {
    if (durabilidad > 0) {
        durabilidad--;
        cout << "Durabilidad del hacha " << nombre << " reducida a " << durabilidad << ".\n";
        if (durabilidad == 0) {
            cout << "El hacha " << nombre << " se ha roto y ya no puede ser usada.\n";
        }
    }
}

void HachaSimple::mejorar() {
    nivel++;
    danoFisico += 5; // Aumentar el daño físico
    filo += 2; // Aumentar el filo
    cout << "El hacha " << nombre << " ha sido mejorada al nivel " << nivel << ".\n";
}

string HachaSimple::getInfo() const {
    return "Hacha Simple: " + nombre +
           "\nDaño Físico: " + to_string(danoFisico) +
           "\nFilo: " + to_string(filo) +
           "\nDurabilidad: " + to_string(durabilidad) +
           "\nNivel: " + to_string(nivel);
}


// Hacha doble

HachaDoble::HachaDoble(int dano, int dur, int niv, string nom, double filo1, double filo2)
    : ArmaDeCombate(dano, dur, niv, nom, "HachaDoble"), filoPrincipal(filo1), filoSecundario(filo2) {}

bool HachaDoble::estaAfilado() const {
    return filoPrincipal > 10 && filoSecundario > 10; // Ambos filos tienen que estar por encima de 10
}

void HachaDoble::usar() {
    if (durabilidad > 0) {
        double danoTotal = (danoFisico + (estaAfilado() ? filoPrincipal + filoSecundario : (filoPrincipal + filoSecundario) / 2)) * (1 + nivel * 0.1);
        cout << "Usando el hacha doble " << nombre << ". Daño causado: " << danoTotal << ".\n";
        if (estaAfilado()) {
            cout << "¡Ataque doble activado! Ambos filos causan daño adicional.\n";
        }
        reducirDurabilidad();
        filoPrincipal -= 1; // Reducir el filo principal
        filoSecundario -= 1; // Reducir el filo secundario
        if (filoPrincipal < 0) filoPrincipal = 0; // Ver que no sea negativo
        if (filoSecundario < 0) filoSecundario = 0;
        cout << "El filo principal del hacha doble " << nombre << " se ha reducido a " << filoPrincipal << ".\n";
        cout << "El filo secundario del hacha doble " << nombre << " se ha reducido a " << filoSecundario << ".\n";
    } else {
        cout << "El hacha doble " << nombre << " está rota y no puede ser usada.\n";
    }
}

void HachaDoble::afilar() {
    filoPrincipal += 5; // Aumentar el filo principal
    filoSecundario += 5; // Aumentar el filo secundario
    cout << "El hacha doble " << nombre << " ha sido afilada. Nuevos filos: " << filoPrincipal << " y " << filoSecundario << ".\n";
}

void HachaDoble::reducirDurabilidad() {
    if (durabilidad > 0) {
        durabilidad--;
        cout << "Durabilidad del hacha doble " << nombre << " reducida a " << durabilidad << ".\n";
        if (durabilidad == 0) {
            cout << "El hacha doble " << nombre << " se ha roto y ya no puede ser usada.\n";
        }
    }
}

void HachaDoble::mejorar() {
    nivel++;
    danoFisico += 10; // Aumentar el daño físico
    filoPrincipal += 3; // Aumentar el filo principal
    filoSecundario += 3; // Aumentar el filo secundario
    cout << "El hacha doble " << nombre << " ha sido mejorada al nivel " << nivel << ".\n";
}

string HachaDoble::getInfo() const {
    return "Hacha Doble: " + nombre +
           "\nDaño Físico: " + to_string(danoFisico) +
           "\nFilo Principal: " + to_string(filoPrincipal) +
           "\nFilo Secundario: " + to_string(filoSecundario) +
           "\nDurabilidad: " + to_string(durabilidad) +
           "\nNivel: " + to_string(nivel);
}


// Espada

Espada::Espada(int dano, int dur, int niv, string nom, double filoInicial, double probCritico)
    : ArmaDeCombate(dano, dur, niv, nom, "Espada"), filo(filoInicial), probabilidadCritico(probCritico) {
    srand(time(0)); // Inicializar la semilla para números aleatorios
}

bool Espada::estaAfilado() const {
    return filo > 10; // Está afilado si el filo es mayor a 10
}

void Espada::usar() {
    if (durabilidad > 0) {
        double danoTotal = (danoFisico + filo) * (1 + nivel * 0.1);
        bool esCritico = (rand() % 100) < (probabilidadCritico * (estaAfilado() ? 150 : 100)); // Mayor probabilidad si está afilada

        if (esCritico) {
            danoTotal *= 2; // Duplicar el daño si el ataque es crítico
            cout << "¡Ataque crítico! ";
        }

        cout << "Usando la espada " << nombre << ". Daño causado: " << danoTotal << ".\n";
        reducirDurabilidad();
        filo -= 1; // Reducir el filo al usar la espada
        if (filo < 0) filo = 0; // Ver que el filo no sea negativo
        cout << "El filo de la espada " << nombre << " se ha reducido a " << filo << ".\n";
    } else {
        cout << "La espada " << nombre << " está rota y no puede ser usada.\n";
    }
}

void Espada::afilar() {
    filo += 5; // Aumentar el filo al afilar
    cout << "La espada " << nombre << " ha sido afilada. Nuevo filo: " << filo << ".\n";
}

void Espada::reducirDurabilidad() {
    if (durabilidad > 0) {
        durabilidad--;
        cout << "Durabilidad de la espada " << nombre << " reducida a " << durabilidad << ".\n";
        if (durabilidad == 0) {
            cout << "La espada " << nombre << " se ha roto y ya no puede ser usada.\n";
        }
    }
}

void Espada::mejorar() {
    nivel++;
    danoFisico += 5; // Aumentar el daño físico
    filo += 2; // Aumentar el filo
    cout << "La espada " << nombre << " ha sido mejorada al nivel " << nivel << ".\n";
}

string Espada::getInfo() const {
    return "Espada: " + nombre +
           "\nDaño Físico: " + to_string(danoFisico) +
           "\nFilo: " + to_string(filo) +
           "\nProbabilidad de Crítico: " + to_string(probabilidadCritico * 100) + "%" +
           "\nDurabilidad: " + to_string(durabilidad) +
           "\nNivel: " + to_string(nivel);
}


// Lanza

Lanza::Lanza(int dano, int dur, int niv, string nom, double alcanceInicial, double perforacionInicial)
    : ArmaDeCombate(dano, dur, niv, nom, "Lanza"), alcance(alcanceInicial), perforacion(perforacionInicial) {}

bool Lanza::estaAfilado() const {
    return perforacion > 10; // Está afilada si la perforación es mayor a 10
}

void Lanza::usar() {
    if (durabilidad > 0) {
        double danoTotal = (danoFisico + (estaAfilado() ? perforacion * 1.5 : perforacion)) * (1 + nivel * 0.1);
        cout << "Usando la lanza " << nombre << " con alcance " << alcance << ".\n";
        cout << "Daño causado: " << danoTotal << ".\n";
        reducirDurabilidad();
        perforacion -= 1; // Reducir la perforación al usar la lanza
        if (perforacion < 0) perforacion = 0; // Ver que la perforación no sea negativa
        cout << "La perforación de la lanza " << nombre << " se ha reducido a " << perforacion << ".\n";
    } else {
        cout << "La lanza " << nombre << " está rota y no puede ser usada.\n";
    }
}

void Lanza::afilar() {
    perforacion += 5; // Aumentar la perforación al afilar
    cout << "La lanza " << nombre << " ha sido afilada. Nueva perforación: " << perforacion << ".\n";
}

void Lanza::reducirDurabilidad() {
    if (durabilidad > 0) {
        durabilidad--;
        cout << "Durabilidad de la lanza " << nombre << " reducida a " << durabilidad << ".\n";
        if (durabilidad <= 0) {
            cout << "La lanza " << nombre << " se ha roto y ya no puede ser usada.\n";
        }
    }
}

void Lanza::mejorar() {
    nivel++;
    danoFisico += 5; // Aumentar el daño físico
    perforacion += 3; // Aumentar la perforación
    alcance += 1; // Aumentar el alcance
    cout << "La lanza " << nombre << " ha sido mejorada al nivel " << nivel << ".\n";
}

string Lanza::getInfo() const {
    return "Lanza: " + nombre +
           "\nDaño Físico: " + to_string(danoFisico) +
           "\nPerforación: " + to_string(perforacion) +
           "\nAlcance: " + to_string(alcance) +
           "\nDurabilidad: " + to_string(durabilidad) +
           "\nNivel: " + to_string(nivel);
}


// Garrote

Garrote::Garrote(int dano, int dur, int niv, string nom, double pesoCabezaInicial, double probAturdir)
    : ArmaDeCombate(dano, dur, niv, nom, "Garrote"), pesoCabeza(pesoCabezaInicial), probabilidadAturdir(probAturdir), estaEnBuenEstado(true) {
    srand(time(0)); // Inicializar la semilla para números aleatorios
}

void Garrote::usar() {
    if (durabilidad > 0) {
        double danoTotal = (danoFisico + pesoCabeza) * (1 + nivel * 0.1);
        bool aturdir = (rand() % 100) < (probabilidadAturdir * 100); // Determinar si el enemigo es aturdido

        cout << "Usando el garrote " << nombre << ". Daño causado: " << danoTotal << ".\n";
        if (aturdir) {
            cout << "¡El enemigo ha sido aturdido!\n";
        }

        reducirDurabilidad();
        if (durabilidad <= 5) {
            cout << "El garrote " << nombre << " está en mal estado. Considera repararlo.\n";
            estaEnBuenEstado = false; // Cambiar el estado a "mal estado"
        }
        else if (durabilidad <= 0) {
            cout << "El garrote " << nombre << " se ha roto y ya no puede ser usado.\n";
        }
    } else {
        cout << "El garrote " << nombre << " está roto y no puede ser usado.\n";
    }
}

void Garrote::reparar() {
    if (!estaEnBuenEstado) {
        estaEnBuenEstado = true;
        cout << "El garrote " << nombre << " ha sido reparado y ahora está en buen estado.\n";
    }
    else {
        cout << "El garrote " << nombre << " ya está en buen estado.\n";
    }
}

void Garrote::reducirDurabilidad() {
    if (durabilidad > 0) {
        durabilidad--;
        cout << "Durabilidad del garrote " << nombre << " reducida a " << durabilidad << ".\n";
        if (durabilidad == 0) {
            cout << "El garrote " << nombre << " se ha roto y ya no puede ser usado.\n";
            estaEnBuenEstado = false; // Cambiar el estado del garrote a "mal estado"
        }
    }
}

void Garrote::mejorar() {
    nivel++;
    danoFisico += 5; // Aumentar el daño físico
    pesoCabeza += 2; // Aumentar el peso de la cabeza
    cout << "El garrote " << nombre << " ha sido mejorado al nivel " << nivel << ".\n";
}

string Garrote::getInfo() const {
    string info =  "Garrote: " + nombre +
                   "\nPeso de la Cabeza: " + to_string(pesoCabeza) +
                   "\nDaño Físico: " + to_string(danoFisico) +
                   "\nProbabilidad de Aturdir: " + to_string(probabilidadAturdir * 100) + "%" +
                   "\nDurabilidad: " + to_string(durabilidad) +
                   "\nNivel: " + to_string(nivel) +
                   "\nEstado: ";
    if (estaEnBuenEstado) {
        info += "Bueno";
    } else {
        info += "Malo";
    }
    return info;
}