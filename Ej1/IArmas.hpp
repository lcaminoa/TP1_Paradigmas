#ifndef ARMAS_HPP
#define ARMAS_HPP

#include <string>

using namespace std;

class InterfazArma {
public:
    virtual void usar() = 0;
    virtual int getPoder() const = 0;
    virtual string getNombre() const = 0;
    virtual string getInfo() const = 0;
    virtual string getTipo() const = 0;
    virtual void reducirDurabilidad() = 0;
    virtual void mejorar() = 0;
    virtual bool puedeUsarse() const = 0;
    virtual ~InterfazArma() = default; // Destructor virtual
};

#endif // ARMAS_HPP