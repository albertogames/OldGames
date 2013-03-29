
//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

#include "FormMenuPrincipal.h"

#include "FormMenuMazo.h"
#include "FormJugador.h"
#include "FormEmpezar.h"
#include "FormEditorMapas.h"
#include "FormJuego.h"
#include "FormCreditos.h"


//---------------------------------------------------------------------------
TFMenuPrincipal *FMenuPrincipal;
//---------------------------------------------------------------------------

__fastcall TFMenuPrincipal::TFMenuPrincipal(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

//ArrayTodasLasCartas = TCarta[1000];



void __fastcall TFMenuPrincipal::BSalirClick(TObject *Sender)
{
    Close();    
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------


void __fastcall TFMenuPrincipal::BOpcionesClick(TObject *Sender)
{
    TVariables::setJugadorSelec(0,-1);
    TFJugador* NewForm;
    NewForm = new TFJugador(Application);
    NewForm->ShowModal();
}
//---------------------------------------------------------------------------



void __fastcall TFMenuPrincipal::B2JugadoresClick(TObject *Sender)
{
    TVariables::setJugadorSelec(0, -1);
    TFEmpezar* NewForm;
    NewForm = new TFEmpezar(Application);
    NewForm->ShowModal();
}


//---------------------------------------------------------------------------


void __fastcall TFMenuPrincipal::BEditMapasClick(TObject *Sender)
{
    TFEditorMapas* NewForm;
    NewForm = new TFEditorMapas(Application);
    NewForm->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFMenuPrincipal::BEditMazoClick(TObject *Sender)
{
    TFMenuMazo* NewForm;
    NewForm = new TFMenuMazo(Application);
    NewForm->ShowModal();
}
void __fastcall TFMenuPrincipal::FormCreate(TObject *Sender)
{
    randomize();
        //Coordenadas del formulario


    //Iniciar mazo
    for ( int a = 0; a < 10; a++)
        *( TVariables::getJugador( a ).nombre) = '\0';





    //cargar mazo

    for ( int a = 0; a < 10; a++)     //cargar fichero
    {
        char nombre[25];
        strcpy( nombre, "save\\Jugadores\\Jugador");
        strcat( nombre, IntToStr(a).c_str() );
        ifstream fentrada( nombre );

        if ( !fentrada.eof() )
            TVariables::jugador[ a ].leer( fentrada );

        fentrada.close();
    }
    TRegDatos datos;
    ifstream fentrada( "save\\datos.dat" );    //guardar la resolucion
    datos.leer( fentrada );
    switch ( datos.resolucion)
    {
        case 0: { TVariables::setResolucion(640,480); break; }
        case 1: { TVariables::setResolucion(800,600); break; }
        case 2: { TVariables::setResolucion(1024,768); break; }
        case 3: { TVariables::setResolucion(1280,1024); break; }
    }

    fentrada.close();

    cambiarRes( B2Jugadores );
    cambiarRes( BEditMazo );
    cambiarRes( BOpciones );
    cambiarRes( BSalir );
    cambiarRes( BEditMapas );
    cambiarRes( BCreditos);

    Width = TVariables::getResolucionX() * 1280;
    Height = TVariables::getResolucionY() * 1024;
    Position = poScreenCenter;
}
//---------------------------------------------------------------------------

void __fastcall TFMenuPrincipal::BCreditosClick(TObject *Sender)
{
    TFCreditos* NewForm;
    NewForm = new TFCreditos(Application);
    NewForm->ShowModal();
}
//---------------------------------------------------------------------------

