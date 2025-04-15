#ifndef IPERSONAJES_HPP
#define IPERSONAJES_HPP

#include "IArmas.hpp"
#include <string>
#include <memory>
#include <vector>

using namespace std;

class InterfazPersonaje {
public:
    virtual void atacar() = 0;
    virtual void equiparArma(unique_ptr<InterfazArma> arma, bool esPrimaria) = 0;
    virtual string obtenerEstadisticas() const = 0;
    virtual void morir() const = 0;
    virtual int calcularDanio() const = 0;
    virtual void recibirDanio(int danio) = 0;
    virtual string getNombre() const = 0;
    virtual string getTipo() const = 0;
    virtual const vector<unique_ptr<InterfazArma>>& getArmas() const = 0;
    virtual void desequiparArma(bool esPrimaria) = 0;
    virtual ~InterfazPersonaje() = default;
};

#endif // IPERSONAJES_HPP