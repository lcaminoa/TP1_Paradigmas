#include "ArmasMagicas.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// ArmaMagica

ArmaMagica::ArmaMagica(int poder, int dur, string nom, int niv, string tipoArma)
    : poderMagico(poder), durabilidad(dur), nombre(nom), nivel(niv), tipo(tipoArma) {}

int ArmaMagica::getPoder() const {
    return poderMagico; // Devuelve el poder mágico del arma
}

string ArmaMagica::getNombre() const {
    return nombre; // Devuelve el nombre del arma
}

string ArmaMagica::getTipo() const {
    return tipo; // Devuelve el tipo de arma
}

bool ArmaMagica::puedeUsarse() const {
    return durabilidad > 0; // El arma puede usarse si tiene durabilidad
}

string ArmaMagica::getInfo() const {
    return "Arma Mágica: " + nombre +
           "\nPoder: " + to_string(poderMagico) +
           "\nDurabilidad: " + to_string(durabilidad) +
           "\nNivel: " + to_string(nivel);
}


// Baston

Baston::Baston(int poder, int dur, string nom, int niv, bool encantado, int energia, string tipoHechizo)
    : ArmaMagica(poder, dur, nom, niv, "Baston"), estaEncantado(encantado),
      energiaRestante(energia), tipoHechizo(tipoHechizo), esFerulaPapal(false), esBastonSatanas(false) {}

void Baston::usar() {
    if (energiaRestante > 0 && durabilidad > 0) {
        cout << "Usando " << nombre << " para lanzar un hechizo mágico.\n";
        reducirDurabilidad();
        int costoEnergia = estaEncantado ? 1 : 2; // Si está encantado gasta menos energía
        energiaRestante -= costoEnergia;
        cout << "Energía restante: " << energiaRestante << ".\n";

        // Efecto especial del bastón: regenera mana al usarlo
        cout << "El bastón regenera 5 puntos de mana al jugador.\n";
    } else if (energiaRestante <= 0) {
        cout << "No hay suficiente energía para usar el bastón.\n";
    } else {
        cout << nombre << " está roto y no puede ser usado.\n";
    }
}

void Baston::lanzarHechizoEspecial() {
    if (energiaRestante >= 5 && durabilidad > 0) {
        int costoEnergia = estaEncantado ? 3 : 5; // Si está encantado gasta menos energía
        cout << "Lanzando hechizo de " << tipoHechizo << " con " << nombre
             << " (Poder: " << poderMagico << ").\n";
        energiaRestante -= costoEnergia;
        cout << "Energía restante: " << energiaRestante << ".\n";
        reducirDurabilidad();
    } else if (energiaRestante < 5) {
        cout << "No hay suficiente energía para lanzar el hechizo especial.\n";
    } else {
        cout << nombre << " está roto y no puede ser usado.\n";
    }
}

void Baston::recargarEnergia() {
    energiaRestante += 10; // Recargar energía
    if (energiaRestante > 100) { // Limitar la energía máxima
        energiaRestante = 100;
    }
    cout << "Recargando energía mágica del " << nombre << ". Energía actual: " << energiaRestante << ".\n";
}

void Baston::mejorar() {
    if (energiaRestante >= 20) { // Ver si hay suficiente energía para mejorar
        nivel++;
        poderMagico += 10;
        energiaRestante -= 20; // Costo de mejorar
        cout << nombre << " mejorado al nivel " << nivel << " (Poder: " << poderMagico << ").\n";
    } else {
        cout << "No hay suficiente energía para mejorar " << nombre << ".\n";
    }
}

void Baston::reducirDurabilidad() {
    int desgaste = estaEncantado ? 3 : 5; // Reducir el desgaste si está encantado
    if (durabilidad > desgaste) {
        durabilidad -= desgaste;
        cout << "Durabilidad del " << nombre << " reducida a " << durabilidad << ".\n";
    } else {
        durabilidad = 0; // No permitir que la durabilidad sea negativa
        cout << nombre << " se ha roto.\n";
    }
}

void Baston::encantar() {
    if (esFerulaPapal) {
        cout << nombre << " no puede ser encantado, pues ya cuenta con el poder de Dios todopoderoso.\n";
    } else if (esBastonSatanas) {
        cout << nombre << " no puede ser encantado, pues ya cuenta con el poder del infierno.\n";
    } else if (!estaEncantado) {
        estaEncantado = true;
        poderMagico += 20; // Aumentar el poder mágico
        cout << nombre << " ha sido encantado! Poder aumentado a " << poderMagico << ".\n";
    } else {
        cout << nombre << " ya está encantado.\n";
    }
}

void Baston::convertirEnFerulaPapal() {
    if (esBastonSatanas) {
        cout << "El bastón " << nombre << " dejará de ser el Bastón de Satanás para convertirse en la Férula Papal.\n";
        esBastonSatanas = false; // Dejar de ser Bastón de Satanás
    }

    if (!esFerulaPapal) {
        esFerulaPapal = true;
        tipoHechizo = "Luz Divina"; // Cambiar el tipo de hechizo
        poderMagico += 30; // Aumentar el poder mágico
        energiaRestante += 20; // Restaurar algo de energía
        estaEncantado = false; // El modo Férula Papal no se puede encantar

        cout << nombre << " ha sido convertido en la Férula Papal. Que la luz divina te guíe.\n";
    } else {
        cout << nombre << " ya es la Férula Papal.\n";
    }
}

void Baston::convertirEnBastonSatanas() {
    if (esFerulaPapal) {
        cout << "El bastón " << nombre << " dejará de ser la Férula Papal para convertirse en el Bastón de Satanás.\n";
        esFerulaPapal = false; // Dejar de ser Férula Papal
    }

    if (!esBastonSatanas) {
        esBastonSatanas = true;
        tipoHechizo = "Fuego Infernal"; // Cambiar el tipo de hechizo
        poderMagico += 50; // Aumentar significativamente el poder mágico
        energiaRestante += 10; // Restaurar algo de energía
        estaEncantado = true; // El modo Bastón de Satanás está encantado por defecto

        cout << nombre << " ha sido convertido en el Bastón de Satanás. Que el fuego infernal consuma a tus enemigos.\n";
    } else {
        cout << nombre << " ya es el Bastón de Satanás.\n";
    }
}

string Baston::getInfo() const {
    string info = "Bastón: " + nombre +
                  "\nPoder: " + to_string(poderMagico) +
                  "\nDurabilidad: " + to_string(durabilidad) +
                  "\nNivel: " + to_string(nivel) +
                  "\nEnergía Restante: " + to_string(energiaRestante) +
                  "\nTipo de Hechizo: " + tipoHechizo +
                  "\nModo Actual: ";
    if (esFerulaPapal) {
        info += "Férula Papal";
    } else if (esBastonSatanas) {
        info += "Bastón de Satanás";
    } else {
        info += "Normal";
    }
    return info;
}

// Libro
Libro::Libro(int poder, int dur, string nom, int pag, bool sellado, int conjuro, string idi)
    : ArmaMagica(poder, dur, nom, 1, "Libro"), paginas(pag), estaSellado(sellado),
      poderConjuro(conjuro), idioma(idi), esBiblia(false), esNecronomicon(false) {
    listaVersiculos();
    listaFrasesOscuras();
}

void Libro::listaVersiculos() {
    versiculos = {
        "Proverbios 21:31 - El caballo se alista para el día de la batalla, pero la victoria es del Señor.",
        "Salmos 144:1 - Bendito sea el Señor, mi roca, quien adiestra mis manos para la batalla, mis dedos para la guerra.",
        "Eclesiastés 3:8 - Tiempo de amar y tiempo de odiar; tiempo de guerra y tiempo de paz.",
        "Deuteronomio 20:4 - Porque el Señor tu Dios va contigo, para pelear por ti contra tus enemigos y darte la victoria.",
        "Josué 1:9 - Sé fuerte y valiente. No temas ni te desanimes, porque el Señor tu Dios estará contigo dondequiera que vayas.",
        "2 Crónicas 20:15 - No teman ni se desalienten ante esta gran multitud, porque la batalla no es de ustedes, sino de Dios.",
        "Salmos 18:39 - Tú me armaste de fuerza para la batalla; sometiste a mis adversarios debajo de mí.",
        "Isaías 54:17 - Ningún arma forjada contra ti prosperará, y condenarás toda lengua que se levante contra ti en juicio.",
        "Éxodo 15:3 - El Señor es un guerrero; el Señor es su nombre.",
        "1 Samuel 17:47 - Toda esta asamblea sabrá que el Señor no salva con espada ni con lanza, porque la batalla es del Señor."
    };
}

void Libro::listaFrasesOscuras() {
    frasesOscuras = {
        "Ph'nglui mglw'nafh Cthulhu R'lyeh wgah'nagl fhtagn.",
        "El conocimiento prohibido consume el alma de quien lo busca.",
        "Los antiguos observan desde las sombras, esperando el momento de regresar.",
        "El caos es el verdadero orden del universo.",
        "La sangre es la llave que abre las puertas del abismo.",
        "El Necronomicón no es un libro, es un portal hacia la locura.",
        "Aquellos que leen estas palabras sellan su destino en la oscuridad.",
        "El tiempo y el espacio son ilusiones; todo converge en el vacío eterno.",
        "El poder absoluto requiere un precio absoluto.",
        "El abismo no solo te observa, sino que te llama por tu nombre."
    };
}

void Libro::usar() {
    if (durabilidad > 0) {
        if (!estaSellado) { // Ver si no está sellado
            cout << "Usando " << nombre << " para invocar un conjuro poderoso.\n";
            cout << "Daño causado: " << poderConjuro * 1.5 << ".\n"; // Si está abierto hace mas daño
        } else {
            cout << "Usando " << nombre << " mientras está cerrado.\n";
            cout << "Daño causado: " << poderConjuro * 0.5 << ".\n"; // Si está cerrado hace menos daño
        }
        reducirDurabilidad();
    } else {
        cout << nombre << " está roto y no puede ser usado.\n";
    }
}

void Libro::invocarConjuro() {
    cout << "Invocando conjuro desde " << nombre << " (Poder: " << poderConjuro << ").\n";
}

void Libro::abrirLibro() {
    if (estaSellado) {
        estaSellado = false;
        cout << nombre << " ha sido abierto.\n";
    } else {
        cout << nombre << " ya esta abierto.\n";
    }
}

void Libro::mejorar() {
    nivel++;
    poderMagico += 12;
    cout << nombre << " mejorado al nivel " << nivel << " (Poder: " << poderMagico << ").\n";
}

void Libro::reducirDurabilidad() {
    durabilidad -= 4;
    cout << "Durabilidad del " << nombre << " reducida a " << durabilidad << ".\n";
}

void Libro::convertirEnBiblia() {
    if (esNecronomicon) {
        cout << "El libro " << nombre << " dejará de ser un Necronomicón para convertirse en una Biblia.\nBienvenido a la luz.\n";
        esNecronomicon = false; // Dejar de ser un Necronomicón
    }

    if (!esBiblia) {
        esBiblia = true;
        idioma = "Hebreo";
        paginas += 200; // Aumentar el número de páginas
        estaSellado = false; // Las biblias no están selladas
        poderConjuro += 50; // Aumentar el poder del conjuro al convertirlo en Biblia

        cout << nombre << " ha sido convertido en una Biblia. Que Dios guíe tu camino.\n";
    } else {
        cout << nombre << " ya es una Biblia.\n";
    }
}

void Libro::convertirEnNecronomicon() {
    if (esBiblia) {
        cout << "El libro " << nombre << " dejará de ser una Biblia para convertirse en el Necronomicón.\nBienvenido a la oscuridad.\n";
        esBiblia = false; // Dejar de ser una Biblia
    }

    esNecronomicon = true;
    idioma = "Lengua Oscura"; // Cambiar el idioma
    poderConjuro += 50; // Aumentar el poder del conjuro
    paginas += 100; // Agregar más páginas oscuras
    estaSellado = true; // El Necronomicón empieza sellado

    cout << "El libro " << nombre << " se ha convertido en el Necronomicón, un tomo oscuro de gran poder.\n";
}

void Libro::arrancarPaginas(int cantidad) {
    if (cantidad > 0 && cantidad <= paginas) {
        paginas -= cantidad;
        poderMagico -= 2 * cantidad; // Reducir el poder por cada página arrancada

        // Beneficio: liberar un conjuro especial
        int danoEspecial = cantidad * 10; // Daño especial basado en la cantidad de páginas arrancadas
        cout << "Has arrancado " << cantidad << " páginas de " << nombre << ".\n";
        cout << "Liberando un conjuro especial que inflige " << danoEspecial << " puntos de daño.\n";

        cout << "Páginas restantes: " << paginas << ", Poder actual: " << poderMagico << ".\n";
    } else {
        cout << "No puedes arrancar esa cantidad de páginas. Verifica el número de páginas disponibles.\n";
    }
}

void Libro::agregarPaginas(int cantidad) {
    if (cantidad > 0) {
        int costoPoder = cantidad * 5; // Costo de poder por página agregada
        int desgasteDurabilidad = cantidad / 10; // Desgaste de durabilidad por cada 10 páginas

        // Ver si hay suficiente energía mágica y durabilidad
        if (poderMagico >= costoPoder && durabilidad > desgasteDurabilidad) {
            paginas += cantidad;
            poderMagico -= costoPoder; // Reducir poder mágico
            durabilidad -= desgasteDurabilidad; // Reducir durabilidad

            cout << "Has agregado " << cantidad << " páginas a " << nombre << ".\n";
            cout << "Costo: " << costoPoder << " puntos de poder mágico y " << desgasteDurabilidad << " puntos de durabilidad.\n";
            cout << "Páginas totales: " << paginas << ", Poder actual: " << poderMagico << ", Durabilidad actual: " << durabilidad << ".\n";
        } else {
            if (poderMagico < costoPoder) {
                cout << "No tienes suficiente poder mágico para agregar " << cantidad << " páginas.\n";
            }
            if (durabilidad <= desgasteDurabilidad) {
                cout << "No tienes suficiente durabilidad para agregar " << cantidad << " páginas.\n";
            }
        }
    } else {
        cout << "La cantidad de páginas a agregar debe ser positiva.\n";
    }
}

string Libro::leerBiblia() {
    if (!esBiblia) {
        return "Este libro no es una biblia. No puedes leer versículos hasta que aceptes al señor en tu corazón.";
    }

    srand(time(0)); // Inicializar la semilla para números aleatorios
    int indice = rand() % versiculos.size(); // Seleccionar un índice aleatorio
    return versiculos[indice];
}

string Libro::leerNecronomicon() {
    if (!esNecronomicon) {
        return "Este libro no es el Necronomicón. No puedes leer frases oscuras hasta que abraces la oscuridad.";
    }

    srand(time(0)); // Inicializar la semilla para números aleatorios
    int indice = rand() % frasesOscuras.size(); // Seleccionar un índice aleatorio
    return frasesOscuras[indice];
}

string Libro::getInfo() const {
    string info = "Libro: " + nombre +
                  "\nPoder: " + to_string(poderMagico) +
                  "\nDurabilidad: " + to_string(durabilidad) +
                  "\nPáginas: " + to_string(paginas) +
                  "\nIdioma: " + idioma +
                  "\nTipo de Libro: ";
    if (esBiblia) {
        info += "Biblia";
    } else if (esNecronomicon) {
        info += "Necronomicón: ";
    } else {
        info += "Normal";
    }
    return info;
}


// Pocion

Pocion::Pocion(int poder, int dur, string nom, int niv, string tipo, int cantidad, int efecto, bool esAguaBendita)
    : ArmaMagica(poder, dur, nom, niv, "Pocion"), tipo(tipo), cantidad(cantidad), efecto(efecto), esAguaBendita(esAguaBendita) {}

void Pocion::usar() {
    if (cantidad > 0 && durabilidad > 0) {
        if (esAguaBendita) {
            cout << "Usando la poción " << nombre << " (Agua Bendita).\n";
            cout << "Efecto: Cura completamente la vida y aumenta la energía en " << efecto << " puntos.\n";
        } else {
            cout << "Usando la poción " << nombre << " (" << tipo << ").\n";
            cout << "Efecto: " << efecto << " puntos restaurados.\n";
        }

        cantidad--;
        reducirDurabilidad();
    } else if (cantidad <= 0) {
        cout << "La poción " << nombre << " ya no tiene usos disponibles.\n";
    } else {
        cout << "La poción " << nombre << " está rota y no puede ser usada.\n";
    }
}

void Pocion::reducirDurabilidad() {
    if (durabilidad > 0) {
        durabilidad--;
        cout << "Durabilidad de la poción " << nombre << " reducida a " << durabilidad << ".\n";
    } else {
        cout << "La poción " << nombre << " se ha roto.\n";
    }
}

void Pocion::mejorar() {
    nivel++;
    efecto += 10; // Incrementa el efecto de la poción.
    cantidad += 1; // Agrega un uso adicional.
    cout << "La poción " << nombre << " ha sido mejorada al nivel " << nivel << ". Efecto: " << efecto << ", Usos: " << cantidad << ".\n";
}

void Pocion::convertirEnAguaBendita() {
    if (!esAguaBendita) {
        esAguaBendita = true;
        tipo = "bendita";
        cantidad = 1; // Solo un uso disponible para el agua bendita.
        efecto = 100; // Efecto máximo de curación y energía.
        durabilidad = 5; // Durabilidad fija para el agua bendita.
        nombre = "Agua Bendita"; // Cambiar el nombre.
        cout << "La poción ha sido convertida en Agua Bendita. Ahora tiene un efecto sagrado.\n";
    } else {
        cout << "La poción ya es Agua Bendita.\n";
    }
}

string Pocion::getInfo() const {
    return "Poción: " + nombre +
           "\nTipo: " + tipo +
           "\nEfecto: " + to_string(efecto) +
           "\nCantidad de usos: " + to_string(cantidad) +
           "\nDurabilidad: " + to_string(durabilidad) +
           "\nNivel: " + to_string(nivel);
}


// Amuleto

Amuleto::Amuleto(int poder, int dur, string nom, int niv, string efectoEsp)
    : ArmaMagica(poder, dur, nom, niv, "Amuleto"), efectoEspecial(efectoEsp), estaActivado(false), esCrucifijo(false) {}

void Amuleto::usar() {
    if (estaActivado && durabilidad > 0) {
        cout << "Usando el amuleto " << nombre << ".\n";
        cout << "Efecto: Activa un escudo mágico que reduce el daño recibido en un 50 porciento durante 3 turnos.\n";
        reducirDurabilidad();
    } else if (!estaActivado) {
        cout << "El amuleto " << nombre << " no está activado. Actívalo antes de usarlo.\n";
    } else {
        cout << "El amuleto " << nombre << " está roto y no puede ser usado.\n";
    }
}

void Amuleto::reducirDurabilidad() {
    if (durabilidad > 0) {
        durabilidad--;
        cout << "Durabilidad del amuleto " << nombre << " reducida a " << durabilidad << ".\n";
        if (durabilidad == 0) {
            cout << "El amuleto " << nombre << " se ha roto y ya no puede ser usado.\n";
            desactivar();
        }
    }
}

void Amuleto::mejorar() {
    nivel++;
    poderMagico += 5; // Incrementa el poder mágico del amuleto.
    cout << "El amuleto " << nombre << " ha sido mejorado al nivel " << nivel << ". El efecto especial ahora es más potente.\n";
}

void Amuleto::activar() {
    if (!estaActivado) {
        estaActivado = true;
        cout << "El amuleto " << nombre << " ha sido activado. Ahora puedes usarlo.\n";
    } else {
        cout << "El amuleto " << nombre << " ya está activado.\n";
    }
}

void Amuleto::desactivar() {
    if (estaActivado) {
        estaActivado = false;
        cout << "El amuleto " << nombre << " ha sido desactivado. No puedes usarlo hasta que lo actives nuevamente.\n";
    } else {
        cout << "El amuleto " << nombre << " ya está desactivado.\n";
    }
}

void Amuleto::convertirEnCrucifijo() {
    if (!esCrucifijo) {
        esCrucifijo = true;
        efectoEspecial = "Defensa aumentada y regeneración de energía";
        cout << "El amuleto " << nombre << " se ha convertido en un crucifijo. Ahora tiene un efecto combinado de defensa y regeneración de energía.\n";
    } else {
        cout << "El amuleto " << nombre << " ya es un crucifijo.\n";
    }
}

void Amuleto::usarCrucifijo() {
    if (esCrucifijo) {
        cout << "Usando el crucifijo " << nombre << ".\n";
        cout << "Efecto: Aumenta la defensa y regenera energía.\n";
        cout << "El amuleto vuelve a su estado normal.\n";
        reducirDurabilidad();
        esCrucifijo = false; // Deja de ser un crucifijo después de usarlo
    } else {
        cout << "El amuleto " << nombre << " no es un crucifijo.\n";
    }
}

string Amuleto::getInfo() const {
    string info = "Amuleto: " + nombre +
                  "\nEfecto Especial: " + efectoEspecial +
                  "\nDurabilidad: " + to_string(durabilidad) +
                  "\nNivel: " + to_string(nivel) +
                   "\nEs Crucifijo: ";
    if (esCrucifijo) {
        info += "Sí";
    } else {
        info += "No";
    }
    return info;
}