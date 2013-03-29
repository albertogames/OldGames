#ifndef VariablesH
#define VariablesH
//---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include "iostream.h"
#include "fstream.h"
#include "string.h"
#include "UPersonaje.h"

using namespace std;
//---------------------------------------------------------------------------

int round( float num );

struct TRegDatos
{
    int jugador1,jugador2;
    int mazo1,mazo2;
    char mapa[50];
    int modJuego;
    int resolucion;
    //resolucion, etc...
    void leer(ifstream &in)
    {
        in.read((char*)this, sizeof(TRegDatos));
    }
    void escribir(ofstream &ot)
    {
        ot.write( (char*)this, sizeof(TRegDatos));
    }
};

struct  TRegPared
{
    char nombre[40];
    unsigned int x,y;
};

struct    TRegMap
{
    char nombre[20];
    TRegPared paredes[20];
    void leer(ifstream &in)
    {
        in.read((char*)this, sizeof(TRegMap));
    }
    void escribir(ofstream &ot)
    {
        ot.write( (char*)this, sizeof(TRegMap));
    }
};

struct TRegMazo
{
    char nombre[20];
    char (carta[60])[30];
};

struct TRegFich
{
    char nombre[20];
    TRegMazo mazos[50];
    //Estadisticas
    void leer(ifstream &in)
    {
        in.read((char*)this, sizeof(TRegFich));
    }
    void escribir(ofstream &ot)
    {
        ot.write( (char*)this, sizeof(TRegFich) );
    }
};


class TVariables
{
    private:
        static int jugadorSelec[2];
        static float resolucionX;
        static float resolucionY;
        static TTio* criaturaInvocar;
        static unsigned int numMensaje;
        static unsigned int numBoton;
        


    public:
        static TRegFich jugador[10];

        static int getJugadorSelec (int a) { return jugadorSelec[a]; }
        static void setJugadorSelec (int a, int b) { jugadorSelec[a] = b; }

        static void incJugadorSelec (int a) { jugadorSelec[a]++; }

        static float getResolucionX () {return resolucionX;}
        static float getResolucionY () {return resolucionY;}
        static void setResolucion (float x,float y) {resolucionX = x/1280.0,resolucionY = y/1024.0;}

        static TTio* getCriaturaInvocar() { return criaturaInvocar; }
        static void setCriaturaInvocar(TTio* t) { criaturaInvocar = t;}

        static void setNumMensaje(int x) {numMensaje = x;}
        static int getNumMensaje() {return numMensaje;}
        static void setNumBoton(int x) {numBoton = x;}
        static int getNumBoton() {return numBoton;}

        static TRegFich & getJugador( int a ) { return jugador[a]; }
        static void setJugador( int a, TRegFich b ) { jugador[a]= b ; }
        static void setJugadorMazoCarta( int jug, int mazoSel, int numCart, char* nombre )  { strcpy( jugador[jug].mazos[mazoSel].carta[numCart], nombre ); }
        static void setJugadorMazoNombre(int jug,int maz,char* nombre) {strcpy(jugador[jug].mazos[maz].nombre,nombre);}
        static void setJugadorMazo(int jug,int m,TRegMazo maz) {jugador[jug].mazos[m] = maz;}
        static void setJugadorNombre(int jug,char* nombre) {strcpy(jugador[jug].nombre,nombre);}
        static void borrarJugador(int jug) {*jugador[jug].nombre = '\0';}
        static void borrarJugadorMazo(int jug,int maz) {*jugador[jug].mazos[maz].nombre = '\0';}
        static void iniciarMazo(int mazoSelec);
};



// PROCEDIMIENTOS ---------------------------------------
void guardar();
void cambiarRes(TImage* imag);
void cambiarRes(TLabel* lab);
void cambiarRes(TButton* boton);
template <class tipo>
void cambiarRes(tipo* boton)
{
    boton->Left *= TVariables::getResolucionX() ,
    boton->Top *= TVariables::getResolucionY() ,
    boton->Width *= TVariables::getResolucionX() ,
    boton->Height *= TVariables::getResolucionY() ;
}





#endif

