#include "estados.h"
#pragma once


class dfa_t
{
    private:
    
    int estados;
    int estadoinicial;
    std::vector<estados_t> vector_;
    std::vector<std::vector<estados_t>> vectorConjuntos;
    std::vector<char> simbolosUtilizados;
    
    public:
    
    dfa_t(void);
    ~dfa_t(void) = default;
    
    std::istream& leerdfa (std::istream& is);
    std::ostream& write (std::ostream& os);
    
    int get_estados(void);
    void set_estados(int estado);
    
    int get_estadoinicial(void);
    void set_estadoinicial(int estadoini);
    
    void destruccion (void);
    void verificarcadena (void);
    
    
    void mindfa(void);
    std::vector<std::vector<estados_t>> estadosRedundantes(void);
    std::vector<std::vector<estados_t>> nuevaParticion(std::vector<std::vector<estados_t>> copiaVectorConjuntos);
    std::vector<std::vector<estados_t>> descomponerConjunto(std::vector<estados_t> conjunto,std::vector<std::vector<estados_t>> copiaVectorConjuntos);
    std::vector<std::vector<estados_t>> particion (std::vector<estados_t> conjunto,char simbolo,std::vector<std::vector<estados_t>> copiaVectorConjuntos);

    std::vector<std::vector<estados_t>> setUnion (std::vector<std::vector<estados_t>> conjunto1,std::vector<std::vector<estados_t>> conjunto2);
    void simbolostotales(void);
    std::ostream& writeconjuntos (std::ostream& os,const std::vector<std::vector<estados_t>>& conjunto1);
};