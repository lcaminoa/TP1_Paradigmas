#ifndef MAGOS_HPP
#define MAGOS_HPP

#include "IPersonajes.hpp"
#include "IArmas.hpp"
#include <memory>
#include <vector>

using namespace std;

class Mago : public InterfazPersonaje {
protected:
    int mana;
    int salud;
    int fuerza;
    int inteligencia;
    int experiencia;
    string nombre;
    string tipo;
    vector<unique_ptr<InterfazArma>> armas;

public:
    /**
     * Constructor de Mago.
     * @param m Mana inicial del mago.
     * @param s Salud inicial del mago.
     * @param f Fuerza inicial del mago.
     * @param i Inteligencia inicial del mago.
     * @param e Experiencia inicial del mago.
     * @param nom Nombre del mago.
     * @param tipo Tipo del mago (ej. "Hechicero", "Conjurador", etc.).
     */
    Mago(int m, int s, int f, int i, int e, string nom, string tipo);

    /**
     * Realiza un ataque con las armas equipadas.
     * Si tiene ambas armas, ataca con ambas.
     * Si tiene solo una, ataca con esa.
     * Si no tiene armas, usa una característica del personaje para atacar.
     */
    virtual void atacar() override;

    /**
     * Realiza un ataque especial.
     * Este método puede ser sobrescrito por las clases derivadas.
     */
    virtual void ataqueEspecial() = 0;

    /**
     * Método abstracto para que cada tipo de mago implemente su forma única de recuperar salud.
     */
    virtual void efectoCurativo() = 0;

    /**
     * Equipa un arma primaria o secundaria al mago.
     * @param arma Unique ptr al arma que se desea equipar.
     * @param esPrimaria Indica si el arma es primaria (true) o secundaria (false).
     */
    virtual void equiparArma(unique_ptr<InterfazArma> arma, bool esPrimaria) override;

    /**
     * Desequipa un arma primaria o secundaria del mago.
     * @param esPrimaria Indica si el arma es primaria (true) o secundaria (false).
     */
    void desequiparArma(bool esPrimaria) override;

    /**
     * Obtiene el nombre del mago.
     * @return Nombre del mago como un string.
     */
    virtual string getNombre() const override;

    /**
     * Obtiene el tipo del mago.
     * @return Tipo del mago como un string.
     */
    virtual string getTipo() const override;

    /**
     * Obtiene las armas del mago.
     * @return Vector de unique_ptr a las armas del mago.
     *         Si no tiene armas, devuelve un vector vacío.
     */
    const vector<unique_ptr<InterfazArma>>& getArmas() const override;

    /**
     * Calcula el daño del mago.
     *      Si no tiene arma equipada, el daño es igual a la fuerza.
     *      Si tiene un arma equipada, el daño es igual a la fuerza + poder del arma.
     * @return Daño total del mago.
     */
    virtual int calcularDanio() const override;

    /**
     * Recibe daño y actualiza la salud del mago.
     * Si la salud llega a 0 o menos, el mago muere.
     * @param danio Daño recibido.
     */
    virtual void recibirDanio(int danio) override;

    /**
     * Destructor de Mago.
     * Libera los recursos asociados al mago.
     */
    virtual ~Mago();
};

class Hechicero : public Mago {
private:
    int poderMagico;
    int nivelHechizo;

public:
    /**
     * Constructor de Hechicero.
     * @param m Mana inicial del hechicero.
     * @param s Salud inicial del hechicero.
     * @param f Fuerza inicial del hechicero.
     * @param i Inteligencia inicial del hechicero.
     * @param e Experiencia inicial del hechicero.
     * @param nom Nombre del hechicero.
     * @param poder Poder mágico inicial del hechicero.
     * @param nivelHechizo Nivel inicial de los hechizos del hechicero.
     */
    Hechicero(int m, int s, int f, int i, int e, string nom, int poder, int nivelHechizo);

    /**
     * Realiza un ataque especial con el hechicero.
     * Si no tiene suficiente mana, realiza un ataque normal.
     */
    void ataqueEspecial() override;

    /**
     * Lanza un hechizo específico.
     * @param hechizo Nombre del hechizo que se desea lanzar.
     */
    void lanzarHechizo(string hechizo);

    /**
     * Calcula el daño del hechicero.
     */
    int calcularDanio() const override;

    /**
     * Le da una muerte personalizada al Hechicero.
     */
    void morir() const override;

    /**
     * Obtiene las estadísticas del hechicero.
     * @return Estadísticas del hechicero como un string.
     */
    string obtenerEstadisticas() const override;

    /**
     * Implementación del efecto curativo único del hechicero.
     */
    void efectoCurativo() override;
};

class Conjurador : public Mago {
private:
    int cantidadInvocaciones;
    int poderInvocacion;

public:
    /**
     * Constructor de Conjurador.
     * @param m Mana inicial del conjurador.
     * @param s Salud inicial del conjurador.
     * @param f Fuerza inicial del conjurador.
     * @param i Inteligencia inicial del conjurador.
     * @param e Experiencia inicial del conjurador.
     * @param nom Nombre del conjurador.
     * @param invocaciones Cantidad inicial de invocaciones disponibles.
     * @param poder Poder de invocación inicial del conjurador.
     */
    Conjurador(int m, int s, int f, int i, int e, string nom, int invocaciones, int poder);

    /**
     * Realiza un ataque especial con el conjurador.
     * Si no tiene suficientes invocaciones disponibles, realiza un ataque normal.
     */
    void ataqueEspecial() override;
    
    /**
     * Calcula el daño del conjurador.
     */
    int calcularDanio() const override;

    /**
     * Invoca al demonio Paimon.
     * Consume una invocación y una gran cantidad de mana.
     */
    void invocarPaimon();

    /**
     * Le da una muerte personalizada al Conjurador.
     */
    void morir() const override;

    /**
     * Obtiene las estadísticas del conjurador.
     * @return Estadísticas del conjurador como un string.
     */
    string obtenerEstadisticas() const override;

    /**
     * Implementación del efecto curativo único del conjurador.
     */
    void efectoCurativo() override;
};

class Brujo : public Mago {
private:
    int poderOscuro; // Poder oscuro del brujo
    int nivelMaldicion; // Nivel de las maldiciones que puede lanzar

public:
    /**
     * Constructor de Brujo.
     * @param m Mana inicial del brujo.
     * @param s Salud inicial del brujo.
     * @param f Fuerza inicial del brujo.
     * @param i Inteligencia inicial del brujo.
     * @param e Experiencia inicial del brujo.
     * @param nom Nombre del brujo.
     * @param poder Poder oscuro inicial del brujo.
     * @param nivel Nivel inicial de las maldiciones del brujo.
     */
    Brujo(int m, int s, int f, int i, int e, string nom, int poder, int nivel);

    /**
     * Realiza un ataque especial con el brujo.
     * Si no tiene suficiente mana, realiza un ataque normal.
     */
    void ataqueEspecial() override;

    /**
     * Calcula el daño del brujo.
     */
    int calcularDanio() const override;

    /**
     * Lanza una maldición sobre un objetivo.
     * @param objetivo Nombre del objetivo de la maldición.
     */
    void lanzarMaldicion(string objetivo);

    /**
     * Invoca el espíritu de Merlín.
     * Aumenta el poder oscuro y regenera mana.
     */
    void invocarEspirituDeMerlin();

    /**
     * Le da una muerte personalizada al Brujo.
     */
    void morir() const override;

    /**
     * Obtiene las estadísticas del brujo.
     * @return Estadísticas del brujo como un string.
     */
    string obtenerEstadisticas() const override;

    /**
     * Implementación del efecto curativo único del brujo.
     */
    void efectoCurativo() override;
};

class Nigromante : public Mago {
private:
    int poderNecromancia; // Poder relacionado con las artes satánicas
    int cantidadMuertosInvocados; // Número de muertos que puede invocar

public:
    /**
     * Constructor de Nigromante.
     * @param m Mana inicial del nigromante.
     * @param s Salud inicial del nigromante.
     * @param f Fuerza inicial del nigromante.
     * @param i Inteligencia inicial del nigromante.
     * @param e Experiencia inicial del nigromante.
     * @param nom Nombre del nigromante.
     * @param poder Poder de necromancia inicial del nigromante.
     * @param muertos Cantidad inicial de muertos que puede invocar.
     */
    Nigromante(int m, int s, int f, int i, int e, string nom, int poder, int muertos);

    /**
     * Realiza un ataque especial con el nigromante.
     * Si no tiene suficientes invocaciones de muertos disponibles, realiza un ataque normal.
     */
    void ataqueEspecial() override;

    /**
     * Calcula el daño del nigromante.
     */
    int calcularDanio() const override;

    /**
     * Invoca muertos para luchar junto al nigromante.
     * Consume mana y reduce la cantidad de muertos disponibles.
     */
    void invocarMuertos();

    /**
     * Realiza un sacrificio oscuro.
     * Pierde salud para aumentar su poder de necromancia y regenerar mana.
     */
    void realizarSacrificioOscuro();

    /**
     * Le da una muerte personalizada al Nigromante.
     */
    void morir() const override;

    /**
     * Obtiene las estadísticas del nigromante.
     * @return Estadísticas del nigromante como un string.
     */
    string obtenerEstadisticas() const override;

    /**
     * Implementación del efecto curativo único del nigromante.
     */
    void efectoCurativo() override;
};

#endif // MAGOS_HPP