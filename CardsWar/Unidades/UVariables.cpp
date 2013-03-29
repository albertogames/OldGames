#include "UVariables.h"


float TVariables::resolucionX = 1024.0/1280;
float TVariables::resolucionY = 768.0/1024;
TTio* TVariables::criaturaInvocar = NULL;
unsigned int TVariables::numMensaje;
unsigned int TVariables::numBoton;
TRegFich TVariables::jugador[10];
int TVariables::jugadorSelec[2] = {0,0};
int round( float num )
{
    int a = num;
    return num - a  > 0.5 ? ++a : a;
}
void guardar()
{
    for ( int a = 0; a < 10; a++)               //  GUARDAR   JUGADORES
    {
        char nombre[25];
        strcpy( nombre, "save\\Jugadores\\Jugador");
        strcat( nombre, IntToStr(a).c_str() );

        ofstream fsalida( nombre );
        if ( *TVariables::getJugador( a ).nombre )
            TVariables::jugador[ a ].escribir( fsalida );
        fsalida.close();
    }
}

void cambiarRes(TImage* imag)
{
    imag->Left *= TVariables::getResolucionX();
    imag->Top *= TVariables::getResolucionY();
    imag->AutoSize = false;
    imag->Width *= TVariables::getResolucionX();
    imag->Height *= TVariables::getResolucionY();
    imag->Stretch = true;
}
void cambiarRes(TLabel* lab)
{
    lab->Left *= TVariables::getResolucionX() ;
    lab->Top *= TVariables::getResolucionY() ;
    lab->Width *= TVariables::getResolucionX() ;
    lab->Height *= TVariables::getResolucionY() ;
    lab->Font->Size *= TVariables::getResolucionX() ;
}
void cambiarRes(TButton* boton)
{
    boton->Left *= TVariables::getResolucionX() ;
    boton->Top *= TVariables::getResolucionY() ;
    boton->Width *= TVariables::getResolucionX() ;
    boton->Height *= TVariables::getResolucionY() ;
    boton->Font->Size *= TVariables::getResolucionX() ;
}
void TVariables::iniciarMazo(int mazoSelec)
{
    for (int a=0; a < 60; a++)
        *jugador[ jugadorSelec[0] ].mazos[mazoSelec].carta[a] = '\0';
}

















