#ifndef CartaH
#define CartaH
//---------------------------------------------------------------------------
#include <vcl.h>



enum TClase{criatura,objeto,encCriatura,hechizo,encantamientos,mana};

class TCarta
{
        int pm;
        String nombre ;                 // Private
        String imagen;
        void (*habilidad)() ;
        TClase tipo;
    public:
       // char nombre[30] ;

       // char imagen[30];


        TCarta( char* n , int p, char* im, void (*h)() , TClase t)
        {
            nombre =n;
            pm = p;
            imagen = im;
            habilidad = h;
            tipo = t;
        }

        TClase getTipo()          { return ( tipo ); }
        String getImagen()        {  return imagen;  }
        void setNombre( String n) {   nombre = n;    }
        String getNombre()        {  return nombre;  }
        int getPm ()              {  return ( pm );  }
        void setPm( int p)        {     pm = p;      }
        void setImagen(String i)  {   imagen = i;    }
        void usarHabilidad()      {   habilidad();   }



};
TCarta* crearCarta(char*);
#endif


