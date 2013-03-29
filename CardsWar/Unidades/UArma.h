#ifndef ArmaH
#define ArmaH
#include "UCarta.h"
enum TipoObjeto{ESPADA, ARCO, BASTON, GUANTES,MASCARA,NINGUNO};
class TArma
{
    private:
    //Atributos generales
        String nombre;
        String texto;
        TCarta* carta;
        TipoObjeto tipo;
        bool dosManos;
        bool cuerpoACuerpo;
        bool distancia;
        int fuerza;
        int resistenciaC,resistenciaD,resistenciaM;
        int alcance;
        
        static TArma* armaCrear;
    public:
        TArma ( )
        {
            nombre = "";
            texto = "";
            carta = NULL;
            dosManos = false;
            fuerza = 0;
            cuerpoACuerpo = false;
            distancia = false;
            resistenciaC = 0;
            resistenciaD = 0;
            resistenciaM = 0;
            tipo = NINGUNO;
            alcance = 0;
        }

        void setNombre(String s) {nombre = s;}
        String getNombre(){return nombre;}

        void setTexto(String s) {texto = s;}
        String getTexto(){return texto;}

        void setTipo(TipoObjeto t){tipo = t;}
        int getTipo(){ return tipo ;}



        //case ESPADA:{return 0; break;}  case ARCO:{return 1; break;}   case BASTON:{return 2; break; }   case GUANTES:{return 3;break;}    case MASCARA: {return 4;}




        void setCarta(TCarta* c) {carta = c;}
        TCarta* getCarta(){return carta;}

        void setDosManos(bool b) {dosManos = b;}
        bool getDosManos(){return dosManos;}

        void setCuerpoACuerpo(bool b) {cuerpoACuerpo = b;}
        bool getCuerpoACuerpo(){return cuerpoACuerpo;}

        void setDistancia(bool b) {distancia = b;}
        bool getDistancia(){return distancia;}

        void setFuerza(int i) {fuerza = i;}
        int getFuerza() {return fuerza;}

        void setResistenciaC(int i) {resistenciaC = i;}
        int getResistenciaC() {return resistenciaC;}

        void setResistenciaD(int i) {resistenciaD = i;}
        int getResistenciaD() {return resistenciaD;}

        void setResistenciaM(int i) {resistenciaM = i;}
        int getResistenciaM() {return resistenciaM;}

        void setAlcance(int i) {alcance = i;}
        int getAlcance() {return alcance;}



        static TArma* TArma::getArmaCrear() {return armaCrear;}
        static void TArma::setArmaCrear(TArma* arm) {armaCrear = arm;}


};


        TArma* crearEspadaDeDragon();
        TArma* crearEspadaLegendaria();
        TArma* crearArcoCorto();
        TArma* crearMascaraDelDiablo();
        TArma* crearBrazaletesDeTormenta();


#endif