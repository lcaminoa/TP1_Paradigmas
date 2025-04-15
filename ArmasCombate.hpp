#ifndef ARMASCOMBATE_HPP
#define ARMASCOMBATE_HPP

#include "IArmas.hpp"

using namespace std;

/**
 * Clase base para armas de combate cuerpo a cuerpo.
 */
class ArmaDeCombate : public InterfazArma {
protected:
    int danoFisico; // Daño físico que causa el arma.
    int durabilidad; // Cantidad de usos restantes.
    int nivel; // Nivel del arma.
    string nombre; // Nombre del arma.
    string tipo; // Tipo de arma (ej. "Espada", "Hacha", etc.).

public:
    /**
     * Constructor de ArmaDeCombate.
     * @param dano Daño físico del arma.
     * @param dur Durabilidad inicial del arma.
     * @param niv Nivel del arma.
     * @param mat Material del arma.
     * @param nom Nombre del arma.
     * @param tipo Tipo del arma (ej. "Espada", "Hacha", etc.).
     */
    ArmaDeCombate(int dano, int dur, int niv, string mat, string nom, string tipo);

    /**
     * Método abstracto para usar el arma.
     */
    virtual void usar() override = 0;

    /**
     * Obtiene el poder del arma.
     * @return Poder del arma como un int.
     */
    virtual int getPoder() const override;

    /**
     * Obtiene el nombre del arma.
     * @return Nombre del arma como un string.
     */
    virtual string getNombre() const override;

    /**
     * Obtiene el tipo del arma de combate.
     * @return Tipo del arma de combate como un string.
     */
    virtual string getTipo() const override;

    /**
     * Obtiene información detallada del arma.
     * @return Información del arma como un string.
     */
    string getInfo() const override;

    /**
     * Verifica si el arma puede ser usada.
     * @return true si el arma puede ser usada, false en caso contrario.
     */
    bool puedeUsarse() const override;

    /**
     * Destructor virtual de ArmaDeCombate.
     */
    virtual ~ArmaDeCombate() = default;
};

/**
 * Clase para un hacha simple.
 */
class HachaSimple : public ArmaDeCombate {
private:
    double filo; // Filo del hacha (afecta el daño).

public:
    /**
     * Constructor de HachaSimple.
     * @param dano Daño físico del hacha.
     * @param dur Durabilidad inicial del hacha.
     * @param niv Nivel del hacha.
     * @param mat Material del hacha.
     * @param nom Nombre del hacha.
     * @param filoInicial Filo inicial del hacha.
     */
    HachaSimple(int dano, int dur, int niv, string mat, string nom, double filoInicial);

    /**
     * Verifica si el hacha está afilada (filo > 10).
     * @return true si el hacha está afilada, false en caso contrario.
     */
    bool estaAfilado() const;

    /**
     * Usa el hacha para atacar
     */
    void usar() override;

    /**
     * Afila el hacha para aumentar su filo.
     */
    void afilar();

    /**
     * Reduce la durabilidad del hacha.
     */
    void reducirDurabilidad() override;

    /**
     * Mejora el hacha, aumentando su nivel y filo.
     */
    void mejorar() override;

    /**
     * Obtiene información detallada del hacha.
     * @return Información del hacha como un string.
     */
    string getInfo() const override;
};

/**
 * Clase para un hacha doble.
 */
class HachaDoble : public ArmaDeCombate {
private:
    double filoPrincipal; // Filo principal del hacha.
    double filoSecundario; // Filo secundario del hacha.

public:
    /**
     * Constructor de HachaDoble.
     * @param dano Daño físico del hacha.
     * @param dur Durabilidad inicial del hacha.
     * @param niv Nivel del hacha.
     * @param mat Material del hacha.
     * @param nom Nombre del hacha.
     * @param filo1 Filo principal del hacha.
     * @param filo2 Filo secundario del hacha.
     */
    HachaDoble(int dano, int dur, int niv, string mat, string nom, double filo1, double filo2);

    /**
     * Verifica si ambos filos están afilados.
     * @return true si ambos filos están afilados, false en caso contrario.
     */
    bool estaAfilado() const;

    /**
     * Usa el hacha doble para atacar.
     */
    void usar() override;

    /**
     * Afila ambos filos del hacha.
     */
    void afilar();

    /**
     * Reduce la durabilidad del hacha doble.
     */
    void reducirDurabilidad() override;

    /**
     * Mejora el hacha doble, aumentando su nivel y filo.
     */
    void mejorar() override;

    /**
     * Obtiene información detallada del hacha doble.
     * @return Información del hacha doble como un string.
     */
    string getInfo() const override;
};

/**
 * Clase para una espada.
 */
class Espada : public ArmaDeCombate {
private:
    double filo; // Filo de la espada (afecta el daño).
    double probabilidadCritico; // Probabilidad de realizar un ataque crítico.

public:
    /**
     * Constructor de Espada.
     * @param dano Daño físico de la espada.
     * @param dur Durabilidad inicial de la espada.
     * @param niv Nivel de la espada.
     * @param mat Material de la espada.
     * @param nom Nombre de la espada.
     * @param filoInicial Filo inicial de la espada.
     * @param probCritico Probabilidad de realizar un ataque crítico.
     */
    Espada(int dano, int dur, int niv, string mat, string nom, double filoInicial, double probCritico);

    /**
     * Verifica si el filo está afilado.
     * @return true si el filo está afilado, false en caso contrario.
     */
    bool estaAfilado() const;

    /**
     * Usa la espada para atacar.
     */
    void usar() override;

    /**
     * Afila la espada para aumentar su filo.
     */
    void afilar();

    /**
     * Reduce la durabilidad de la espada.
     */
    void reducirDurabilidad() override;

    /**
     * Mejora la espada, aumentando su nivel y filo.
     */
    void mejorar() override;

    /**
     * Obtiene información detallada de la espada.
     * @return Información de la espada como un string.
     */
    string getInfo() const override;
};

/**
 * Clase para una lanza.
 */
class Lanza : public ArmaDeCombate {
private:
    double alcance; // Alcance de la lanza (afecta la distancia del ataque).
    double perforacion; // Capacidad de perforación (afecta el daño).

public:
    /**
     * Constructor de Lanza.
     * @param dano Daño físico de la lanza.
     * @param dur Durabilidad inicial de la lanza.
     * @param niv Nivel de la lanza.
     * @param mat Material de la lanza.
     * @param nom Nombre de la lanza.
     * @param alcanceInicial Alcance inicial de la lanza.
     * @param perforacionInicial Capacidad inicial de perforación de la lanza.
     */
    Lanza(int dano, int dur, int niv, string mat, string nom, double alcanceInicial, double perforacionInicial);

    /**
     * Verifica si la lanza está afilada (perforación > 10).
     * @return true si la lanza está afilada, false en caso contrario.
     */
    bool estaAfilado() const;

    /**
     * Usa la lanza para atacar.
     */
    void usar() override;

    /**
     * Afila la lanza para aumentar su perforación.
     */
    void afilar();

    /**
     * Reduce la durabilidad de la lanza.
     */
    void reducirDurabilidad() override;

    /**
     * Mejora la lanza, aumentando su nivel y perforación.
     */
    void mejorar() override;

    /**
     * Obtiene información detallada de la lanza.
     * @return Información de la lanza como un string.
     */
    string getInfo() const override;
};

/**
 * Clase para un garrote.
 */
class Garrote : public ArmaDeCombate {
private:
    double pesoCabeza; // Peso de la cabeza del garrote (afecta el daño).
    double probabilidadAturdir; // Probabilidad de aturdir al enemigo.
    bool estaEnBuenEstado; // Indica si el garrote está en buen estado.

public:
    /**
     * Constructor de Garrote.
     * @param dano Daño físico del garrote.
     * @param dur Durabilidad inicial del garrote.
     * @param niv Nivel del garrote.
     * @param mat Material del garrote.
     * @param p Peso del garrote.
     * @param nom Nombre del garrote.
     * @param pesoCabezaInicial Peso inicial de la cabeza del garrote.
     * @param probAturdir Probabilidad inicial de aturdir al enemigo.
     */
    Garrote(int dano, int dur, int niv, string mat, double p, string nom, double pesoCabezaInicial, double probAturdir);

    /**
     * Usa el garrote para atacar.
     */
    void usar() override;

    /**
     * Repara el garrote para restaurar su estado.
     */
    void reparar();

    /**
     * Reduce la durabilidad del garrote.
     */
    void reducirDurabilidad() override;

    /**
     * Mejora el garrote, aumentando su nivel y peso de la cabeza.
     */
    void mejorar() override;

    /**
     * Obtiene información detallada del garrote.
     * @return Información del garrote como un string.
     */
    string getInfo() const override;
};

#endif // ARMASCOMBATE_HPP