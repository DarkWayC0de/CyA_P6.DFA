#include "estados.h"

#ifndef estados_h
#define estados_h

estados_t::estados_t(void):
valor_(0),
estadoaceptacion(false),
numerotransiciones(0), 
estadollegada(0),
conexion(0)
{

}
//******************************************

unsigned int estados_t::get_valor (void) const
{
    return valor_;
}
void estados_t::set_valor (unsigned int val)
{
    valor_ = val;
}
std::istream& estados_t::set_valor (std::istream& is)
{
    is >> valor_;
    return is;
}
    

//******************************************

bool estados_t::get_aceptado (void)
{
    return estadoaceptacion;
}

void estados_t::set_aceptado (bool acept)
{
    estadoaceptacion = acept;
}
std::istream& estados_t::set_aceptado (std::istream& is)
{
    is >> estadoaceptacion;
    return is;
}
    
//*******************************************

int estados_t::get_numerotransiciones (void)
{
    return numerotransiciones;
}
void estados_t::set_numerotransiciones (int numero)
{
    numerotransiciones = numero;
}
std::istream& estados_t::set_numerotransiciones (std::istream& is)
{
    is >>numerotransiciones;
    return is;
}

//******************************************

char estados_t::get_conexion (int pos)
{
 return conexion[pos];   
}
std::vector<char> estados_t::get_conexion (void)
{
    return conexion;
}
void estados_t::set_conexion (char conex, int posicion)
{
    conexion[posicion] = conex;
}
    
//*******************************************
unsigned int estados_t::get_estadollegada (int pos)
{
    return estadollegada[pos];
}
std::vector<unsigned int> estados_t::get_estadollegada (void)
{
    return estadollegada;
}
void estados_t::set_estadollegada (unsigned int llegada,int pos)
{
    estadollegada[pos] += llegada;
}


    
//*******************************************

void estados_t::resizevector (int size)
{
    conexion.resize(size);
    estadollegada.resize(size);
} 

bool estados_t::operator==(const estados_t& estado)const
{
    return valor_ == estado.valor_;
}

bool estados_t::operator<(const estados_t& estado)const
{
    return valor_ < estado.valor_;
}
std::ostream& operator<<(std::ostream& os, const estados_t& estado)
{
    estado.write(os);
    
    return os; 
    
}
void estados_t::write(std::ostream& os) const
{
    os << "{" << get_valor() << "}";
    
}

int estados_t::get_estadollegada_simbolo(char simbolo)
{
    for(int i = 0; i < estadollegada.size(); i++)
    {
        if(simbolo == conexion[i])
            return estadollegada[i];
    }
}
#endif