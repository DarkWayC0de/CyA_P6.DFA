#pragma once
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <istream>
#include <algorithm>


class estados_t
{
    private:
    
    unsigned valor_;
    bool estadoaceptacion;
    int numerotransiciones;
    std::vector<unsigned int> estadollegada;
    std::vector<char> conexion;
        
    public:
    
    estados_t(void);
    ~estados_t(void) = default;
    
    unsigned int get_valor (void) const;
    void set_valor (unsigned int val);
    std::istream& set_valor (std::istream& is);
    
    
    bool get_aceptado (void);
    void set_aceptado (bool acept);
    std::istream& set_aceptado (std::istream& is);
    
    int get_numerotransiciones (void);
    void set_numerotransiciones (int numero);
    std::istream& set_numerotransiciones (std::istream& is);
    
    char get_conexion (int pos);
    std::vector<char> get_conexion (void);
    void set_conexion (char conex, int posicion);
    
    unsigned int get_estadollegada (int pos);
    std::vector<unsigned int> get_estadollegada (void);
    void set_estadollegada (unsigned int llegada,int pos);
    
    int get_estadollegada_simbolo(char simbolo);

    
    void resizevector (int size);
    bool operator==(const estados_t& estado)const;
    bool operator<(const estados_t& estado)const;
    
    
    void write(std::ostream& os) const;
    
    
    
};

std::ostream& operator<<(std::ostream& os,const estados_t& estado);