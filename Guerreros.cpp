#include "Guerreros.hpp"
#include <iostream>
#include <sstream>

using namespace std;

Guerrero::Guerrero(int s, int f, int e, string nom, string tipo)
    : salud(s), fuerza(f), experiencia(e), nombre(nom), tipo(tipo), armas(2) {}

void Guerrero::atacar() {
    // Calcular probabilidad de ataque especial
    bool ataqueEspecial = (rand() % 100) < experiencia;

    int danioTotal = calcularDanio();
    if (ataqueEspecial) {
        cout << nombre << " realiza un ATAQUE ESPECIAL!\n";
        danioTotal *= 2; // Duplicar el daño
    }

    // Usar armas si están disponibles
    bool armaUsada = false;
    for (size_t i = 0; i < armas.size(); ++i) {
        if (armas[i] && armas[i]->puedeUsarse()) {
            cout << nombre << " ataca con " << armas[i]->getNombre()
                 << ", causando " << danioTotal << " de daño.\n";
            armas[i]->usar();
            armaUsada = true;
        }
    }

    // Si no se usaron armas, atacar con fuerza bruta
    if (!armaUsada) {
        cout << nombre << " ataca con su fuerza bruta, causando " << danioTotal << " de daño.\n";
    }
}

void Guerrero::equiparArma(unique_ptr<InterfazArma> arma, bool esPrimaria) {
    if (esPrimaria) {
        armas[0] = std::move(arma); // Equipar el arma primaria
        cout << nombre << " ha equipado el arma primaria: " << armas[0]->getNombre() << ".\n";
    } else {
        armas[1] = std::move(arma); // Equipar el arma secundaria
        cout << nombre << " ha equipado el arma secundaria: " << armas[1]->getNombre() << ".\n";
    }
}

void Guerrero::desequiparArma(bool esPrimaria) {
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

string Guerrero::getNombre() const {
    return nombre;
}

string Guerrero::getTipo() const {
    return tipo;
}

const vector<unique_ptr<InterfazArma>>& Guerrero::getArmas() const {
    return armas;
}

int Guerrero::calcularDanio() const {
    int danioTotal = fuerza + (experiencia / 10); // La experiencia aumenta el daño
    if (!armas.empty() && armas[0]) {
        danioTotal += armas[0]->getPoder();
    }
    if (armas.size() > 1 && armas[1]) {
        danioTotal += armas[1]->getPoder();
    }
    return danioTotal;
}

void Guerrero::recibirDanio(int danio) {
    salud -= danio; // Restar el daño a la salud

    if (salud > 0) {
        // Mostrar mensaje solo si el personaje sigue vivo
        cout << nombre << " ha recibido " << danio << " puntos de daño. Salud restante: " << salud << ".\n";
    } else {
        salud = 0; // Para que la salud no sea negativa
        morir();   // Muerte personalizada
    }
}


// Barbaro

Barbaro::Barbaro(int s, int f, int fur, string nom)
    : Guerrero(s, f, 0, nom, "Barbaro"), furia(fur) {}

void Barbaro::atacar() {
    if (furia >= 50) { // Activar ataque especial si la furia es suficiente
        cout << nombre << " entra en un estado de furia incontrolable y realiza un ATAQUE FURIOSO!\n";
        int danioEspecial = calcularDanio() * 2; // Duplicar el daño
        cout << nombre << " causa un daño devastador de " << danioEspecial << " puntos.\n";
        furia -= 50; // Consumir furia
        return;
    }

    // Si no se cumplen las condiciones, usa el ataque normal
    Guerrero::atacar();
}

void Barbaro::invocarDiosNordico(string dios) {
    cout << nombre << " invoca al dios nórdico " << dios << ".\n";
    if (dios == "Thor") {
        cout << "Thor le da un aumento de fuerza.\n";
        fuerza += 10;
    } else if (dios == "Odin") {
        cout << "Odin le da sabiduría y regenera su salud.\n";
        salud += 20;
    } else if (dios == "Freya") {
        cout << "Freya le da una furia incontrolable.\n";
        furia += 15;
    } else {
        cout << dios << " no responde a la invocación.\n";
    }
}

void Barbaro::morir() const {
    cout << nombre << " ha caído en batalla gloriosa y es llevado al Valhalla por las valquirias.\n";
}

int Barbaro::calcularDanio() const {
    int danioBase = Guerrero::calcularDanio();
    int bonificacionFuria = (furia / 10) * 5; // 5% de bonificación por cada 10 puntos de furia
    return danioBase + bonificacionFuria;
}

string Barbaro::obtenerEstadisticas() const {
    string estadisticas = "Barbaro: " + nombre +
                          "\nSalud: " + to_string(salud) +
                          "\nFuerza: " + to_string(fuerza) +
                          "\nExperiencia: " + to_string(experiencia) +
                          "\nFuria: " + to_string(furia);
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


// Paladin

Paladin::Paladin(int s, int f, int i, int e, string nom, int feInicial, int poderInicial)
    : Guerrero(s, f, e, nom, "Paladin"), fe(feInicial), poderSagrado(poderInicial) {}

void Paladin::atacar() {
    if (fe >= 20) { // Activar ataque especial si la fe es suficiente
        cout << nombre << " invoca el poder sagrado y realiza un ATAQUE DIVINO!\n";
        int danioEspecial = calcularDanio() * 2; // Duplicar el daño
        cout << nombre << " causa un daño divino de " << danioEspecial << " puntos.\n";
        fe -= 20; // Consumir fe
        return;
    }

    // Si no se cumplen las condiciones, usar el ataque normal
    Guerrero::atacar();
}

void Paladin::curar() {
    if (fe >= 10) {
        cout << nombre << " utiliza su fe para curarse, restaurando 30 puntos de salud.\n";
        salud += 30; // Restaurar salud
        fe -= 10; // Consumir fe
    } else {
        cout << nombre << " no tiene suficiente fe para curarse.\n";
    }
}

void Paladin::invocarLuzSagrada() {
    if (fe >= 20) {
        cout << nombre << " invoca la luz sagrada, causando daño a los enemigos y curándose a sí mismo.\n";
        cout << "Inflige " << poderSagrado * 2 << " de daño a los enemigos y restaura 20 puntos de salud.\n";
        salud = min(salud + 20, 100); // Suponiendo que 100 es la salud máxima
        fe -= 20; // Consumir fe
    } else {
        cout << nombre << " no tiene suficiente fe para invocar la luz sagrada.\n";
    }
}

void Paladin::morir() const {
    cout << nombre << " ha caído, pero su espíritu se eleva hacia la luz divina.\n";
}

int Paladin::calcularDanio() const {
    int danioBase = Guerrero::calcularDanio();
    int bonificacionFe = (fe / 10) * 3; // 3% de bonificación por cada 10 de fe
    return danioBase + bonificacionFe;
}

string Paladin::obtenerEstadisticas() const {
    string estadisticas = "Paladin: " + nombre +
                          "\nSalud: " + to_string(salud) +
                          "\nFuerza: " + to_string(fuerza) +
                          "\nExperiencia: " + to_string(experiencia) +
                          "\nFe: " + to_string(fe) +
                          "\nPoder Sagrado: " + to_string(poderSagrado);
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


// Caballero

Caballero::Caballero(int s, int f, int i, int e, string nom, int honorInicial, int devocionInicial)
    : Guerrero(s, f, e, nom, "Caballero"), honor(honorInicial), devocion(devocionInicial) {}

void Caballero::atacar() {
    if (devocion >= 30) { // Activar ataque especial si la devoción es suficiente
        cout << nombre << " invoca su fe y realiza un ATAQUE HONORABLE!\n";
        int danioEspecial = calcularDanio() * 2; // Duplicar el daño
        cout << nombre << " causa un daño honorable de " << danioEspecial << " puntos.\n";
        devocion -= 10; // Consumir algo de devoción
        return;
    }

    // Si no se cumplen las condiciones, usar el ataque normal
    Guerrero::atacar();
}

void Caballero::protegerInocente() {
    cout << nombre << " protege a un inocente, aumentando su honor.\n";
    honor += 10; // Aumentar el honor
}

void Caballero::rezar() {
    if (devocion >= 5) {
        cout << nombre << " reza fervientemente, restaurando 20 puntos de salud y aumentando su devoción.\n";
        salud += 20; // Restaurar salud
        devocion += 5; // Incrementar devoción
    } else {
        cout << nombre << " no tiene suficiente devoción para rezar.\n";
    }
}

void Caballero::morir() const {
    cout << nombre << " ha muerto defendiendo su honor y será recordado como un héroe.\n";
}

int Caballero::calcularDanio() const {
    int danioBase = Guerrero::calcularDanio();
    int bonificacionHonor = (honor / 10) * 3; // 3% de bonificación por cada 10 puntos de honor
    return danioBase + bonificacionHonor;
}

string Caballero::obtenerEstadisticas() const {
    string estadisticas = "Caballero: " + nombre +
                          "\nSalud: " + to_string(salud) +
                          "\nFuerza: " + to_string(fuerza) +
                          "\nExperiencia: " + to_string(experiencia) +
                          "\nHonor: " + to_string(honor) +
                          "\nDevoción: " + to_string(devocion);
    if (armas[0]) {
        estadisticas += "\nArma primaria: " + armas[0]->getNombre();
    } else {
        estadisticas += "\nArma primaria: Ninguna";
    }
    if (armas[0]) {
        estadisticas += "\nArma secundaria: " + armas[0]->getNombre();
    } else {
        estadisticas += "\nArma secundaria: Ninguna";
    }
    return estadisticas;
}


// Mercenario

Mercenario::Mercenario(int s, int f, int i, int e, string nom, int oroInicial, int lealtadInicial)
    : Guerrero(s, f, e, nom, "Mercenario"), oro(oroInicial), lealtad(lealtadInicial) {}

void Mercenario::comprarPocion(int costo, int saludRestaurada) {
    if (oro >= costo) {
        oro -= costo;
        salud += saludRestaurada;
        cout << nombre << " compra una poción por " << costo << " monedas de oro y restaura " << saludRestaurada << " puntos de salud.\n";
    } else {
        cout << nombre << " no tiene suficiente oro para comprar una poción.\n";
    }
}

void Mercenario::atacar() {
    if (lealtad >= 50) { // Activar ataque especial si la lealtad es suficiente
        cout << nombre << " realiza un ATAQUE LEAL, motivado por su compromiso con el empleador!\n";
        int danioEspecial = calcularDanio() * 2; // Duplicar el daño
        cout << nombre << " causa un daño devastador de " << danioEspecial << " puntos.\n";
        lealtad -= 10; // Consumir algo de lealtad
        return;
    }

    // Si no se cumplen las condiciones, usar el ataque normal
    Guerrero::atacar();
}

void Mercenario::cobrarRecompensa(int cantidad) {
    oro += cantidad;
    cout << nombre << " ha cobrado una recompensa de " << cantidad << " monedas de oro. Ahora tiene " << oro << " monedas.\n";
}

void Mercenario::traicionar() {
    if (lealtad > 0) {
        int reduccion = min(lealtad, 10); // Reducir hasta 10, pero no más de lo que tiene
        lealtad -= reduccion;
        oro += 50; // Ganar oro por traición
        cout << nombre << " traicionó a su empleador por un poco de oro. Su lealtad disminuyó a " << lealtad << ".\n";
    } else {
        cout << nombre << " ya no tiene lealtad y actúa solo por dinero.\n";
    }
}

void Mercenario::morir() const {
    cout << nombre << " ha caído en combate, pero su espíritu sigue buscando oro en el más allá.\n";
}

int Mercenario::calcularDanio() const {
    int danioBase = Guerrero::calcularDanio();
    int bonificacionOro = (oro / 50) * 2; // 2% de bonificación por cada 50 monedas de oro
    return danioBase + bonificacionOro;
}

string Mercenario::obtenerEstadisticas() const {
    string estadisticas = "Mercenario: " + nombre +
                          "\nSalud: " + to_string(salud) +
                          "\nFuerza: " + to_string(fuerza) +
                          "\nExperiencia: " + to_string(experiencia) +
                          "\nOro: " + to_string(oro) +
                          "\nLealtad: " + to_string(lealtad);
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


// Gladiador

Gladiador::Gladiador(int s, int f, int i, int e, string nom, int gloriaInicial, int resistenciaInicial)
    : Guerrero(s, f, e, nom, "Gladiador"), gloria(gloriaInicial), resistencia(resistenciaInicial) {}

void Gladiador::entrenar() {
    fuerza += 5;
    resistencia += 10;
    cout << nombre << " acaba de entrenar. Su fuerza aumentó a " << fuerza << " y su resistencia a " << resistencia << ".\n";
}

void Gladiador::recibirOvacion() {
    gloria += 15;
    salud += 10; // Cada ovación restaura 10 de salud
    cout << nombre << " recibe una ovación del público, aumentando su salud a " << salud << " y su gloria a " << gloria << ".\n";
}

int Gladiador::calcularDanio() const {
    int danioBase = Guerrero::calcularDanio();
    int bonificacionGloria = (gloria / 10) * 4; // 4% de bonificación por cada 10 puntos de gloria
    return danioBase + bonificacionGloria;
}

void Gladiador::atacar() {
    if (gloria >= 30) { // Activar ataque especial si la gloria es suficiente
        cout << nombre << " se alimenta de la ovación del público y realiza un ATAQUE GLORIOSO!\n";
        int danioEspecial = calcularDanio() * 2; // Duplicar el daño
        cout << nombre << " causa un daño glorioso de " << danioEspecial << " puntos.\n";
        gloria -= 30; // Consumir gloria
        return;
    }

    // Si no se cumplen las condiciones, usar el ataque normal
    Guerrero::atacar();
}

void Gladiador::morir() const {
    cout << nombre << " ha caído en la arena, pero su espíritu vivirá en la memoria de los espectadores.\n";
}

string Gladiador::obtenerEstadisticas() const {
    string estadisticas = "Gladiador: " + nombre +
                          "\nSalud: " + to_string(salud) +
                          "\nFuerza: " + to_string(fuerza) +
                          "\nExperiencia: " + to_string(experiencia) +
                          "\nGloria: " + to_string(gloria) +
                          "\nResistencia: " + to_string(resistencia);
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