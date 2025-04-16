#ifndef GUERRERO_HPP
#define GUERRERO_HPP

#include "IPersonajes.hpp"
#include <memory>
#include <vector>

using namespace std;

class Guerrero : public InterfazPersonaje {
protected:
    int salud;
    int fuerza;
    int experiencia; // De 0 a 100
    string nombre;
    string tipo;
    vector<unique_ptr<InterfazArma>> armas;

public:
    /**
     * Constructor de Guerrero.
     * @param s Salud inicial del guerrero.
     * @param f Fuerza inicial del guerrero.
     * @param e Experiencia inicial del guerrero.
     * @param nom Nombre del guerrero.
     * @param tipo Tipo del guerrero (ej. "Caballero", "Barbaro", etc.).
     */
    Guerrero(int s, int f, int e, string nom, string tipo);

    /**
     * Realiza un ataque con las armas equipadas.
     * Si tiene ambas armas, ataca con ambas.
     * Si tiene solo una, ataca con esa.
     * Si no tiene armas, usa una característica del personaje para atacar.
     */
    virtual void atacar() override;

    /**
     * Equipa un arma primaria o secundaria al guerrero.
     * @param arma Unique ptr al arma que se desea equipar.
     * @param esPrimaria Indica si el arma es primaria (true) o secundaria (false).
     */
    virtual void equiparArma(unique_ptr<InterfazArma> arma, bool esPrimaria) override;

    /**
     * Desequipa un arma primaria o secundaria del guerrero.
     * @param esPrimaria Indica si el arma es primaria (true) o secundaria (false).
     */
    void desequiparArma(bool esPrimaria) override;

    /**
     * Obtiene el nombre del guerrero.
     * @return Nombre del guerrero como un string.
     */
    virtual string getNombre() const override;
    
    /**
     * Obtiene el tipo del guerrero.
     * @return Tipo del guerrero como un string.
     */
    virtual string getTipo() const override;

    /**
     * Obtiene las armas del guerrero.
     * @return Vector de unique_ptr a las armas del guerrero.
     *         Si no tiene armas, devuelve un vector vacío.
     */
    virtual const vector<unique_ptr<InterfazArma>>& getArmas() const override;

    /**
     * Calcula el daño del guerrero.
     *      Si no tiene arma equipada, el daño es igual a la fuerza.
     *      Si tiene un arma equipada, el daño es igual a la fuerza + poder del arma.
     * @return Daño total del guerrero.
     */
    virtual int calcularDanio() const override;

    /**
     * Recibe daño y actualiza la salud del guerrero.
     * Si la salud llega a 0 o menos, el guerrero muere.
     * @param danio Daño recibido.
     */
    virtual void recibirDanio(int danio) override;

    /**
     * Destructor de Guerrero.
     * Libera la memoria de las armas equipadas.
     */
    virtual ~Guerrero() = default;
};

class Barbaro : public Guerrero {
private:
    int furia; // Nivel de furia (afecta el daño)

public:
    /**
     * Constructor de Barbaro.
     * @param s Salud inicial del bárbaro.
     * @param f Fuerza inicial del bárbaro.
     * @param fur Furia inicial del bárbaro.
     * @param nom Nombre del bárbaro.
     */
    Barbaro(int s, int f, int fur, string nom);

    /**
     * Realiza un ataque con el bárbaro.
     * Si tiene un arma equipada, la usa; de lo contrario, ataca con sus puños.
     */
    void atacar() override;

    /**
     * Invoca a un dios nórdico para obtener un beneficio.
     * @param dios Nombre del dios nórdico (ej. "Thor", "Odin", "Freya").
     */
    void invocarDiosNordico(string dios);

    /**
     * Le da una muerte personalizada al bárbaro.
     */
    virtual void morir() const override;

    /**
     * Calcula el daño del bárbaro.
     */
    virtual int calcularDanio() const override;

    /**
     * Obtiene las estadísticas del bárbaro.
     * @return Estadísticas del bárbaro como un string.
     */
    string obtenerEstadisticas() const override;
};

class Paladin : public Guerrero {
private:
    int fe; // Nivel de fe del paladín (afecta sus habilidades sagradas)
    int poderSagrado; // Poder relacionado con la luz sagrada

public:
    /**
     * Constructor de Paladin.
     * @param s Salud inicial del paladín.
     * @param f Fuerza inicial del paladín.
     * @param e Experiencia inicial del paladín.
     * @param nom Nombre del paladín.
     * @param feInicial Fe inicial del paladín.
     * @param poderInicial Poder sagrado inicial del paladín.
     */
    Paladin(int s, int f, int e, string nom, int feInicial, int poderInicial);

    /**
     * Realiza un ataque con el paladín.
     * Si tiene un arma equipada, la usa; de lo contrario, ataca con su fuerza sagrada.
     */
    void atacar() override;

    /**
     * Cura al paladín utilizando su fe.
     * Restaura salud si tiene suficiente fe.
     */
    void curar();

    /**
     * Invoca la luz sagrada para causar daño a los enemigos y curarse a sí mismo.
     * Consume fe para realizar esta acción.
     */
    void invocarLuzSagrada();

    /**
     * Le da una muerte personalizada al paladín.
     */
    virtual void morir() const override;

    /**
     * Calcula el daño del paladín.
     */
    virtual int calcularDanio() const override;

    /**
     * Obtiene las estadísticas del paladín.
     * @return Estadísticas del paladín como un string.
     */
    string obtenerEstadisticas() const override;
};

class Caballero : public Guerrero {
private:
    int honor; // Nivel de honor del caballero (afecta sus habilidades)
    int devocion; // Nivel de devoción religiosa del caballero

public:
    /**
     * Constructor de Caballero.
     * @param s Salud inicial del caballero.
     * @param f Fuerza inicial del caballero.
     * @param e Experiencia inicial del caballero.
     * @param nom Nombre del caballero.
     * @param honorInicial Honor inicial del caballero.
     * @param devocionInicial Devoción inicial del caballero.
     */
    Caballero(int s, int f, int e, string nom, int honorInicial, int devocionInicial);

    /**
     * Realiza un ataque con el caballero.
     * Si tiene un arma equipada, la usa; de lo contrario, ataca con su fuerza y honor.
     */
    void atacar() override;

    /**
     * Protege a un inocente, aumentando el honor del caballero.
     */
    void protegerInocente();

    /**
     * Reza para restaurar salud y aumentar su devoción.
     * Solo puede realizar esta acción si tiene suficiente devoción (>=5).
     * Ya que de lo contrario, significaría que no tiene la suficiente
     * conexión con Dios como para rezar efectivamente.
     */
    void rezar();

    /**
     * Le da una muerte personalizada al caballero.
     */
    virtual void morir() const override;

    /**
     * Calcula el daño del caballero.
     */
    virtual int calcularDanio() const override;

    /**
     * Obtiene las estadísticas del caballero.
     * @return Estadísticas del caballero como un string.
     */
    string obtenerEstadisticas() const override;
};

class Mercenario : public Guerrero {
private:
    int oro; // Cantidad de oro que posee el mercenario
    int lealtad; // Nivel de lealtad del mercenario (afecta su desempeño)

public:
    /**
     * Constructor de Mercenario.
     * @param s Salud inicial del mercenario.
     * @param f Fuerza inicial del mercenario.
     * @param e Experiencia inicial del mercenario.
     * @param nom Nombre del mercenario.
     * @param oroInicial Oro inicial del mercenario.
     * @param lealtadInicial Lealtad inicial del mercenario.
     */
    Mercenario(int s, int f, int e, string nom, int oroInicial, int lealtadInicial);

    /**
     * Compra una poción para restaurar salud.
     * @param costo Costo de la poción.
     * @param saludRestaurada Cantidad de salud que restaurará la poción.
     */
    void comprarPocion(int costo, int saludRestaurada);

    /**
     * Realiza un ataque con el mercenario.
     * Si tiene un arma equipada, la usa; de lo contrario, ataca con su fuerza.
     */
    void atacar() override;

    /**
     * Cobra una recompensa, aumentando la cantidad de oro del mercenario.
     * @param cantidad Cantidad de oro a cobrar.
     */
    void cobrarRecompensa(int cantidad);

    /**
     * Traiciona a su empleador, reduciendo su lealtad.
     */
    void traicionar();

    /**
     * Le da una muerte personalizada al Mercenario.
     */
    virtual void morir() const override;

    /**
     * Calcula el daño del mercenario.
     */
    virtual int calcularDanio() const override;

    /**
     * Obtiene las estadísticas del mercenario.
     * @return Estadísticas del mercenario como un string.
     */
    string obtenerEstadisticas() const override;
};

class Gladiador : public Guerrero {
private:
    int gloria; // Nivel de gloria del gladiador (afecta su moral y desempeño)
    int resistencia; // Nivel de resistencia física del gladiador

public:
    /**
     * Constructor de Gladiador.
     * @param s Salud inicial del gladiador.
     * @param f Fuerza inicial del gladiador.
     * @param e Experiencia inicial del gladiador.
     * @param nom Nombre del gladiador.
     * @param gloriaInicial Gloria inicial del gladiador.
     * @param resistenciaInicial Resistencia inicial del gladiador.
     */
    Gladiador(int s, int f, int e, string nom, int gloriaInicial, int resistenciaInicial);

    /**
     * Realiza un ataque con el gladiador.
     * Si tiene un arma equipada, la usa; de lo contrario, ataca con su fuerza y resistencia.
     */
    void atacar() override;

    /**
     * Entrena para aumentar su fuerza y resistencia.
     */
    void entrenar();

    /**
     * Recibe una ovación del público, aumentando su gloria.
     */
    void recibirOvacion();

    /**
     * Le da una muerte personalizada al Gladiador.
     */
    virtual void morir() const override;

    /**
     * Calcula el daño del gladiador.
     */
    virtual int calcularDanio() const override;

    /**
     * Obtiene las estadísticas del gladiador.
     * @return Estadísticas del gladiador como un string.
     */
    string obtenerEstadisticas() const override;
};

#endif // GUERRERO_HPP