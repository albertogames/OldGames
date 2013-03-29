//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
#include "FormMensaje.h"
#include "FormJuego.h"
#include "FormMenuMazo.h"
#include "String.h"
//---------------------------------------------------------------------------
TFMensaje *FMensaje;
//---------------------------------------------------------------------------


__fastcall TFMensaje::TFMensaje(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------



void __fastcall TFMensaje::FormActivate(TObject *Sender)
{
    switch (TVariables::getNumMensaje())
    {
        case 1:
            Texto->Caption = "Escribe un nombre para el nuevo mazo";
            B1->Caption = "Aceptar";
            B2->Caption = "Cancelar";
            break;
        case 2:
            Texto->Caption = "Escribe un nombre para el nuevo jugador";
            B1->Caption = "Aceptar" ;
            B2->Caption = "Cancelar" ;
            break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFMensaje::B1Click(TObject *Sender)
{
    TVariables::setNumBoton(0);
    switch (TVariables::getNumMensaje())
    {
        case 1:            //crearNuevoMazo
            if ( *paEscribir->Text.c_str() )    // Si hay texto
            {
                if ( paEscribir->Text.Length() >= 20 )
                    ShowMessage( "El nombre debe contener menos de 20 caracteres");
                else
                {
                    TVariables::setNumBoton(1);
                    int a =0;
                    for ( ; *TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[a].nombre; a++);        //mientras la cadena contenga algo a++
                    TVariables::setJugadorMazoNombre(  TVariables::getJugadorSelec(0),a, paEscribir->Text.c_str() );
                    TFMenuMazo::setMazoSelec( a );
                    Close();
                }
            }
            break;
        case 2:            //crearNuevoJugador
            if (*paEscribir->Text.c_str() )       // Si hay texto
            {
                if ( paEscribir->Text.Length() >= 20 )
                    ShowMessage( "El nombre debe contener menos de 20 caracteres");
                else
                {
                    TVariables::setNumBoton(1);
                    int a = 0;
                    for (; *( TVariables::getJugador( a ).nombre) ; a++);            //mientras la cadena contenga algo a++
                    TVariables::setJugadorNombre(  a, paEscribir->Text.c_str());
                    for (int b =0; b < 50; b++)
                    {
                        *TVariables::getJugador( a ).mazos[b].nombre = '\0';
                        for ( int c = 0; c < 60;c++)
                            *TVariables::getJugador( a ).mazos[b].carta[c] = '\0';
                    }
                    TVariables::setJugadorSelec(0,a);
                    Close();
                }
            }
            break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFMensaje::B2Click(TObject *Sender)
{
    TVariables::setNumBoton(0);
    switch (TVariables::getNumMensaje())
    {
        case 1:
        case 2:
            TVariables::setNumBoton(2);
            Close();
    }
}
//---------------------------------------------------------------------------



