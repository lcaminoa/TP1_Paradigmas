#ifndef ARMASMAGICAS_HPP
#define ARMASMAGICAS_HPP

#include <string>
#include <vector>
#include "IArmas.hpp"
using namespace std;

/**
 * Clase base para armas mágicas.
 */
class ArmaMagica : public InterfazArma {
protected:
    int poderMagico; // Poder mágico del arma.
    int durabilidad; // Cantidad de usos restantes.
    string nombre; // Nombre del arma.
    int nivel; // Nivel del arma.
    string tipo; // Tipo de arma (ej. "Bastón", "Libro", etc.).

public:
    /**
     * Constructor de ArmaMagica.
     * @param poder Poder mágico del arma.
     * @param dur Durabilidad inicial del arma.
     * @param nom Nombre del arma.
     * @param niv Nivel del arma.
     * @param tipo Tipo del arma.
     */
    ArmaMagica(int poder, int dur, string nom, int niv, string tipo);

    /**
     * Usa el arma para lanzar un hechizo mágico.
     */
    virtual void usar() override = 0;

    /**
     * Obtiene el poder del arma.
     * @return Poder del arma como un entero.
     */
    virtual int getPoder() const override;

    /**
     * Obtiene el nombre del arma.
     * @return Nombre del arma como un string.
     */
    virtual string getNombre() const override;

    /**
     * Obtiene información detallada del arma.
     * @return Información del arma como un string.
     */
    virtual string getInfo() const override;

    /**
     * Obtiene el tipo del arma mágica.
     * @return Tipo del arma mágica como un string.
     */
    virtual string getTipo() const override;

    virtual void reducirDurabilidad() override = 0;
    virtual void mejorar() override = 0;

    /**
     * Verifica si el arma puede ser usada.
     * @return true si el arma puede ser usada, false en caso contrario.
     */
    bool puedeUsarse() const override;

    /**
     * Destructor virtual de ArmaMagica.
     */
    virtual ~ArmaMagica() = default;
};

/**
 * Clase para un bastón mágico.
 */
class Baston : public ArmaMagica {
private:
    bool estaEncantado; // Indica si el bastón está encantado.
    int energiaRestante; // Energía mágica disponible.
    string tipoHechizo; // Tipo de hechizo que lanza el bastón.
    bool esFerulaPapal; // Indica si el bastón está en modo Férula Papal.
    bool esBastonSatanas; // Indica si el bastón está en modo Bastón de Satanás.

public:
    /**
     * Constructor de Baston.
     * @param poder Poder mágico del bastón.
     * @param dur Durabilidad inicial del bastón.
     * @param nom Nombre del bastón.
     * @param niv Nivel del bastón.
     * @param encantado Indica si el bastón está encantado.
     * @param energia Energía inicial del bastón.
     * @param tipoHechizo Tipo de hechizo que lanza el bastón.
     */
    Baston(int poder, int dur, string nom, int niv, bool encantado, int energia, string tipoHechizo);

    /**
     * Usa el bastón para lanzar un hechizo mágico.
     */
    void usar() override;

    /**
     * Lanza un hechizo especial con el bastón.
     */
    void lanzarHechizoEspecial();

    /**
     * Recarga la energía mágica del bastón.
     */
    void recargarEnergia();

    /**
     * Mejora el bastón, aumentando su nivel y poder mágico.
     */
    void mejorar() override;

    /**
     * Reduce la durabilidad del bastón.
     */
    void reducirDurabilidad() override;

    /**
     * Encanta el bastón, aumentando su poder mágico.
     */
    void encantar();

    /**
     * Convierte el bastón en la Férula Papal.
     */
    void convertirEnFerulaPapal();

    /**
     * Convierte el bastón en el Bastón de Satanás.
     */
    void convertirEnBastonSatanas();

    /**
     * Obtiene información detallada del bastón.
     * @return Información del bastón como un string.
     */
    string getInfo() const override;
};

/**
 * Clase para un libro mágico.
 */
class Libro : public ArmaMagica {
private:
    int paginas; // Representa los usos que le quedan.
    bool estaSellado; // Indica si el libro está sellado.
    int poderConjuro; // Daño que hace al enemigo.
    string idioma; // Idioma del libro.
    bool esBiblia; // Indica si el libro es una Biblia.
    bool esNecronomicon; // Indica si el libro es el Necronomicón.
    vector<string> versiculos; // Base de datos de versículos para la Biblia.
    vector<string> frasesOscuras; // Base de datos de frases para el Necronomicón.

    /**
     * Inicializa la lista de versículos para la Biblia.
     */
    void listaVersiculos();

    /**
     * Inicializa la lista de frases oscuras para el Necronomicón.
     */
    void listaFrasesOscuras();

public:
    /**
     * Constructor de Libro.
     * @param poder Poder mágico del libro.
     * @param dur Durabilidad inicial del libro.
     * @param nom Nombre del libro.
     * @param pag Número de páginas del libro.
     * @param sellado Indica si el libro está sellado.
     * @param conjuro Poder del conjuro del libro.
     * @param idi Idioma del libro.
     */
    Libro(int poder, int dur, string nom, int pag, bool sellado, int conjuro, string idi);

    /**
     * Usa el libro para invocar un conjuro.
     */
    void usar() override;

    /**
     * Invoca un conjuro desde el libro.
     */
    void invocarConjuro();

    /**
     * Abre el libro si está sellado.
     */
    void abrirLibro();

    /**
     * Mejora el libro, aumentando su nivel y poder mágico.
     */
    void mejorar() override;

    /**
     * Reduce la durabilidad del libro.
     */
    void reducirDurabilidad() override;

    /**
     * Convierte el libro en una Biblia.
     */
    void convertirEnBiblia();

    /**
     * Convierte el libro en el Necronomicón.
     */
    void convertirEnNecronomicon();

    /**
     * Arranca un número específico de páginas del libro.
     * @param cantidad Cantidad de páginas a arrancar.
     */
    void arrancarPaginas(int cantidad);

    /**
     * Agrega un número específico de páginas al libro.
     * Consume 5 de poder por página agregada.
     * @param cantidad Cantidad de páginas a agregar.
     */
    void agregarPaginas(int cantidad);

    /**
     * Lee un versículo de la Biblia.
     * @return Un versículo aleatorio como un string.
     */
    string leerBiblia();

    /**
     * Lee una frase del Necronomicón.
     * @return Una frase oscura aleatoria como un string.
     */
    string leerNecronomicon();

    /**
     * Obtiene información detallada del libro.
     * @return Información del libro como un string.
     */
    string getInfo() const override;
};

/**
 * Clase para una poción mágica.
 */
class Pocion : public ArmaMagica {
private:
    string tipo; // Tipo de poción (ej. curativa, de energía, de fuerza).
    int cantidad; // Cantidad de usos que tiene la poción.
    int efecto; // Cantidad de vida o energía que restaura.
    bool esAguaBendita; // Indica si la poción es agua bendita.

public:
    /**
     * Constructor de Pocion.
     * @param poder Poder mágico de la poción.
     * @param dur Durabilidad inicial de la poción.
     * @param nom Nombre de la poción.
     * @param niv Nivel de la poción.
     * @param tipo Tipo de poción (ej. curativa, de energía, de fuerza).
     * @param cantidad Cantidad de usos que tiene la poción.
     * @param efecto Cantidad de vida o energía que restaura.
     * @param esAguaBendita Indica si la poción es agua bendita (opcional, por defecto `false`).
     */
    Pocion(int poder, int dur, string nom, int niv, string tipo, int cantidad, int efecto, bool esAguaBendita = false);

    /**
     * Usa la poción para aplicar su efecto.
     */
    void usar() override;

    /**
     * Reduce la durabilidad de la poción.
     */
    void reducirDurabilidad() override;

    /**
     * Mejora la efectividad de la poción.
     */
    void mejorar() override;

    /**
     * Convierte la poción en Agua Bendita.
     */
    void convertirEnAguaBendita();

    /**
     * Obtiene información detallada de la poción.
     * @return Información de la poción como un string.
     */
    string getInfo() const override;
};

/**
 * Clase para un amuleto mágico.
 */
class Amuleto : public ArmaMagica {
private:
    string efectoEspecial; // Efecto especial del amuleto.
    bool estaActivado; // Indica si el amuleto está activado.
    bool esCrucifijo; // Indica si el amuleto es un crucifijo.

public:
    /**
     * Constructor de Amuleto.
     * @param poder Poder mágico del amuleto.
     * @param dur Durabilidad inicial del amuleto.
     * @param nom Nombre del amuleto.
     * @param niv Nivel del amuleto.
     * @param efecto Efecto especial del amuleto (ej. "Aumenta la defensa").
     * @param duracion Duración del efecto especial en turnos.
     */
    Amuleto(int poder, int dur, string nom, int niv, string efecto);

    /**
     * Activa el efecto especial del amuleto.
     */
    void usar() override;

    /**
     * Reduce la durabilidad del amuleto.
     */
    void reducirDurabilidad() override;

    /**
     * Mejora el efecto especial del amuleto.
     */
    void mejorar() override;

    /**
     * Activa el amuleto.
     */
    void activar();

    /**
     * Desactiva el amuleto.
     */
    void desactivar();

    /**
     * Convierte el amuleto en un crucifijo.
     */
    void convertirEnCrucifijo();

    /**
     * 
     * Usa los poderes del crucifijo y luego lo devuelve a su estado normal.
     */
    void usarCrucifijo();

    /**
     * Obtiene información detallada del amuleto.
     * @return Información del amuleto como un string.
     */
    string getInfo() const override;
};

#endif // ARMASMAGICAS_HPP