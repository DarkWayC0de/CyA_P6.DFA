
#include "dfa_t.h"


int main (void)
{
    std::string comprobar;   
    dfa_t dfa;
    std::string fich;
    std::ifstream copia;
    std::ifstream fichero;
    bool ficheroleido = false;
    bool ficheroabierto = false;
    bool salida = false;
    int opcion = 0;
    std::cout << "PRACTICA NUMERO 6 CyA: DFA" << std::endl;
    
    
    
    while(!ficheroabierto)
    {
        std::cout << "introduzca el fichero con el que trbajar: ";
        std::cin >> fich;
        fichero.open(fich);
        copia.open(fich);
        getline(copia,comprobar);
        if(!fichero)
        {
            std::cout << std::endl << "Error al abrir el archivo, intentelo de nuevo: ";
        }
        else
        {

            if(comprobar.length() == 1)
            {
                getline(copia,comprobar);
                if(comprobar.length() == 1)
                {
                    ficheroabierto = true;
                }
                else
                {
                    std::cout <<"error mal ingresado el estado inicial" << std::endl;
                    copia.close();
                    fichero.close();
                }
           }
           else
           {
               std::cout << "error mal ingresado el numero de estados" << std::endl;
               copia.close();
               fichero.close();
           }
        }
    }
    std::cout << "fichero abierto correctamente" << std::endl;
    
    while(!salida)
    {
        std::cout<< "**********MENU**********" << std::endl << "1. Leer DFA." << std::endl << "2. Mostrar el dfa." << std::endl;
        std::cout<< "3. Buscar los estados de muerte." << std::endl << "4. Analizar cadena."<< std::endl << "5. Minimizar DFA" << std::endl << "Cualquier otra opcion para salir" << std::endl;
        std::cin >> opcion;
        switch(opcion)
        {
            case 1: dfa.leerdfa(fichero); ficheroleido = true; 
            break;
            case 2: if(ficheroleido) dfa.write(std::cout); else std::cout << "lea un fichero primero" << std::endl;
            break;
            case 3: if(ficheroleido) dfa.destruccion(); else std::cout <<"lea un fichero primero" << std::endl;
            break;
            case 4: if(ficheroleido) dfa.verificarcadena(); else std::cout <<"lea un fichero primero" << std::endl;
            break;
            case 5: if(ficheroleido) dfa.mindfa(); else std::cout << "lea un fichero primero" << std::endl;
            break;
            default:
            salida = true;
            
        }
    }
        
    
    
    
}

