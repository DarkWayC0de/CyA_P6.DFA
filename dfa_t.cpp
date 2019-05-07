#include "dfa_t.h"




dfa_t::dfa_t(void):
estados(0),
estadoinicial(0),
vectorConjuntos(0),
vector_(0)
{}

int dfa_t::get_estados(void)
{
    return estados;
}

void dfa_t::set_estados(int estado)
{
    estados = estado;
}    

int dfa_t::get_estadoinicial(void)
{
    return estadoinicial;
}

void dfa_t::set_estadoinicial(int estadoini)
{
    estadoinicial = estadoini;
}
std::istream& dfa_t::leerdfa (std::istream& is)
{
    char aux;
    unsigned int aux2;
    is >> estados;
    is >> estadoinicial;
    vector_.resize(estados);
    
    for(int i = 0; i < estados; i++)
    {
        vector_[i].set_valor(is);
        vector_[i].set_aceptado(is);
        vector_[i].set_numerotransiciones(is);
        vector_[i].resizevector(vector_[i].get_numerotransiciones());
        for(int j = 0; j < vector_[i].get_numerotransiciones(); j++)
        {
            is >> aux;
            vector_[i].set_conexion(aux, j);
            is >> aux2;
            vector_[i].set_estadollegada(aux2, j);
        }
    }
    simbolostotales();
    return is;
}
std::ostream& dfa_t::write (std::ostream& os)
{
    os << "Estados totales : " << estados << std::endl;
    os << "Estado inicial  : " << estadoinicial << std::endl;
    
    for(int i = 0; i < estados; i++)
    {
        os << "Estado " << i << " --> " << vector_[i].get_valor() << " " << vector_[i].get_aceptado() << " " << vector_[i].get_numerotransiciones() << " "; 
        for(int j = 0; j < vector_[i].get_numerotransiciones(); j++)
            os << vector_[i].get_conexion(j) << " " << vector_[i].get_estadollegada(j) << " ";
        os << std::endl;
        
    }
    return os;
}

void dfa_t::destruccion (void)
{
    std::cout << "los estados muertos son: ";
    int muerte = 0;
    for(int i = 0; i < estados; i++)
    {
        for(int j = 0; j < vector_[i].get_numerotransiciones(); j++)
        {
            if(vector_[i].get_estadollegada(j) == vector_[i].get_valor())
                muerte++;
        }
        if(muerte == vector_[i].get_numerotransiciones())
            std::cout << vector_[i].get_valor() << "  ";
        muerte = 0;
    }
    std::cout << std::endl;
}
void dfa_t::verificarcadena (void)
{
    std::string cadena;
    int a = 0;
    int i = 0;
    int size = 0;
    std::cout << "Introduzca la cadena que desea verificar: " ;
    std::cin >> cadena;
    std::cout << "Estado actual" << std::setw(14) << "Entrada" << std::setw(29) << "Siguiente estado" << std::endl;
    int temporal = estadoinicial;
    size = cadena.size();
    while(size != 0)
    {
        for(int j = 0; j < vector_[temporal].get_numerotransiciones(); j++)
        {
            if(vector_[temporal].get_conexion(j) == cadena[i])
            {
                std::cout << temporal << std::setw(20) << vector_[temporal].get_conexion(j) << std::setw(20) << vector_[temporal].get_estadollegada(j) << std::endl;
                a = vector_[temporal].get_numerotransiciones();
                temporal = vector_[temporal].get_estadollegada(j);
                j = a;
            }
        }
        i++;
        size--;
    }

    if(!vector_[temporal].get_aceptado())
        std::cout << "El estado de aceptacion no es valido" << std::endl;
    else
        std::cout << "El estado de aceptacion es valido" << std::endl;
}

//**************************************************
void dfa_t::mindfa(void)
{
    vectorConjuntos = estadosRedundantes();
    std::vector<std::vector<estados_t>> copiaVectorConjuntos;
    do
    {
        copiaVectorConjuntos = vectorConjuntos;
        vectorConjuntos = nuevaParticion(copiaVectorConjuntos);
        writeconjuntos(std::cout,vectorConjuntos);

        
    }
    while(vectorConjuntos != copiaVectorConjuntos);
    std::cout<<"g";
    
}
std::vector<std::vector<estados_t>> dfa_t::estadosRedundantes(void)
{
    std::vector<std::vector<estados_t>> salidaVector;
    
    std::vector<estados_t> conjuntosEstadoNoAceptacion;
    std::vector<estados_t> conjuntoEstadoAceptacion;

    //guardar construirConjuntos
    
    for(int i = 0; i < estados; i++)
    {
        if(!vector_[i].get_aceptado())
        {
            conjuntosEstadoNoAceptacion.push_back(vector_[i]);
        }
        if(vector_[i].get_aceptado())
        {
            conjuntoEstadoAceptacion.push_back(vector_[i]);
        }
    }
    //actualizar conjuntosTotales
    
        if(!conjuntoEstadoAceptacion.empty())
        {
            salidaVector.push_back(conjuntoEstadoAceptacion);
        }
        if(!conjuntosEstadoNoAceptacion.empty())
        {
            salidaVector.push_back(conjuntosEstadoNoAceptacion);
        }
        return salidaVector;
}
std::vector<std::vector<estados_t>> dfa_t::nuevaParticion(std::vector<std::vector<estados_t>> copiaVectorConjuntos)
{
    std::vector<std::vector<estados_t>> devolverVectorConjuntos;
    for(auto& conjunto : copiaVectorConjuntos)
    {   
        
        std::vector<std::vector<estados_t>> auxiliar = descomponerConjunto(conjunto,copiaVectorConjuntos);
        
        devolverVectorConjuntos = setUnion(devolverVectorConjuntos,auxiliar);
    }
    return devolverVectorConjuntos;
}
std::vector<std::vector<estados_t>> dfa_t::descomponerConjunto(std::vector<estados_t> conjunto,std::vector<std::vector<estados_t>> copiaVectorConjuntos)
{
    
    std::vector<std::vector<estados_t>> devolverConjunto = { conjunto };
    for(auto& simbolo : simbolosUtilizados)
    {
        std::vector<std::vector<estados_t>> capaNueva;
        
        
        for(auto& conjunto : devolverConjunto)
        {
            
            std::vector<std::vector<estados_t>> capaActual = particion(conjunto,simbolo,copiaVectorConjuntos);
            capaNueva = setUnion(capaNueva,capaActual);
        }
        devolverConjunto = capaNueva;
    }
    return devolverConjunto;
}
std::vector<std::vector<estados_t>> dfa_t::particion (std::vector<estados_t> conjunto,char simbolo,std::vector<std::vector<estados_t>> copiaVectorConjuntos){
    std::vector<std::vector<estados_t>> devolverConjunto,helper2;
    std::vector<estados_t> helper;
    for(auto& H : copiaVectorConjuntos)
    {
        for(auto& estado : conjunto) {
            for (auto& estadoH : H) {
                if (estadoH.get_valor() == estado.get_estadollegada_simbolo(simbolo)) {
                    helper.push_back(estado);
                    if(helper.empty()){
                        helper.pop_back();
                    }
                }
            }
        }
        helper2.push_back(helper);
        if (!helper.empty()) {
            std::set_union(devolverConjunto.begin(),devolverConjunto.end(),helper2.begin(),helper2.end(),std::back_inserter(devolverConjunto));
        }
        helper2.erase(helper2.begin(),helper2.end());
        helper.erase(helper.begin(),helper.end());
    }
    
    return devolverConjunto;
}
std::vector<std::vector<estados_t>> dfa_t::setUnion (std::vector<std::vector<estados_t>> conjunto1,std::vector<std::vector<estados_t>> conjunto2)
{
    std::set_union(conjunto1.begin(),conjunto1.end(),conjunto2.begin(),conjunto2.end(),std::back_inserter(conjunto1));
    return conjunto1;   
}
void dfa_t::simbolostotales (void)
{
    for(int i = 0; i < vector_[0].get_numerotransiciones(); i++)
    {
        simbolosUtilizados.push_back(vector_[0].get_conexion(i));
        
    }
    
}

std::ostream& dfa_t::writeconjuntos (std::ostream& os, const std::vector<std::vector<estados_t>>& conjunto1)
{
    int contador = 0;
    for (auto& conjunto : conjunto1) {
        if(!conjunto.empty())
        {
            for (auto& estado : conjunto) {
               os  << estado << " ";
            
             }
        
        os << "\n";
        }
        else{}
            
        

    }
    
    return os;
}