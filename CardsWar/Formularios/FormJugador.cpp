//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop                    
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
#include "FormJugador.h"
#include "FormJuego.h"
#include "FormMensaje.h"
#include "FormMenuPrincipal.h"
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

TFJugador *FJugador;
//---------------------------------------------------------------------------
__fastcall TFJugador::TFJugador(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFJugador::BJugadorNuevoClick(TObject *Sender)
{
    if ( !*TVariables::getJugador( 9 ).nombre )
    {
        TVariables::setNumMensaje(2);

        TFMensaje* NewForm;
        NewForm = new TFMensaje(Application);
        NewForm->ShowModal();

        if (TVariables::getNumBoton() == 1 )
        {
            CBJugador->Items->Add( TVariables::getJugador( TVariables::getJugadorSelec(0) ).nombre );
            CBJugador->Text = TVariables::getJugador( TVariables::getJugadorSelec(0)).nombre;
        }
    }
    else
        ShowMessage("Solo puedes tener 10 jugadores creados, elimina alguno para poder crear otro");
        
}
//---------------------------------------------------------------------------

void __fastcall TFJugador::FormActivate(TObject *Sender)
{
    Width = TVariables::getResolucionX() * 1280;
    Height = TVariables::getResolucionX() * 1024;
    Position = poScreenCenter;
    TVariables::setJugadorSelec(0,-1);

    cambiarRes( Image1 );
    cambiarRes( BBorrarJugador );
    cambiarRes( BVolver );
    cambiarRes( BJugadorNuevo );
    cambiarRes( CBJugador );
    cambiarRes( RGResolucion );
    cambiarRes( BAplicar );

    switch (round(TVariables::getResolucionX()*1280))
    {
        case 640:{RGResolucion->ItemIndex = 0;break;}
        case 800:{RGResolucion->ItemIndex = 1;break;}
        case 1024:{RGResolucion->ItemIndex = 2;break;}
        case 1280:{RGResolucion->ItemIndex = 3;break;}

    }

    for ( int a = 0; *TVariables::getJugador( a ).nombre != 0 && a < 10; a++)
        CBJugador->Items->Add( TVariables::getJugador( a ).nombre );

}
//---------------------------------------------------------------------------
void __fastcall TFJugador::BVolverClick(TObject *Sender)
{
    guardar();
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TFJugador::BBorrarJugadorClick(TObject *Sender)
{
    if ( TVariables::getJugadorSelec(0)+1 )      //si hay algun jugador seleccionado
    {
        TVariables::borrarJugador( TVariables::getJugadorSelec(0) );
        CBJugador->Text = "";
        CBJugador->Items->Delete(TVariables::getJugadorSelec(0));

        int a = TVariables::getJugadorSelec(0);
        for ( ; a < 9 && *TVariables::getJugador( a + 1 ).nombre ; a++)    //mientras a+1 exista
            TVariables::setJugador( a, TVariables::getJugador( a+1 ) )  ;
        TVariables::borrarJugador( a );
        TVariables::setJugadorSelec(0, -1);
    }
    else
        ShowMessage( "Selecciona un jugador" );
}
//---------------------------------------------------------------------------
void __fastcall TFJugador::CBJugadorChange(TObject *Sender)
{
        TVariables::setJugadorSelec(0, 0);
        for( ;  TVariables::getJugadorSelec(0) < 10 && strcmp( TVariables::getJugador( TVariables::getJugadorSelec(0) ).nombre, CBJugador->Text.c_str());  TVariables::incJugadorSelec(0) ) ;
        if (TVariables::getJugadorSelec(0) > 9 || *TVariables::getJugador( TVariables::getJugadorSelec(0) ).nombre =='\0')
            TVariables::setJugadorSelec(0, -1);
}
//---------------------------------------------------------------------------
void __fastcall TFJugador::FormClose(TObject *Sender, TCloseAction &Action)
{
    Action = caFree;      
}
//---------------------------------------------------------------------------



void __fastcall TFJugador::BAplicarClick(TObject *Sender)
{
    switch (RGResolucion->ItemIndex)
    {
        case 0: {TVariables::setResolucion(640,480);break;}
        case 1: {TVariables::setResolucion(800,600);break;}
        case 2: {TVariables::setResolucion(1024,768);break;}
        case 3: TVariables::setResolucion(1280,1024);
    }
    FMenuPrincipal->Width = TVariables::getResolucionX() * 1280;
    FMenuPrincipal->Height = TVariables::getResolucionY() * 1024;
    FMenuPrincipal->Position = poScreenCenter;

    FMenuPrincipal->B2Jugadores->Width = 233 * TVariables::getResolucionX();
    FMenuPrincipal->B2Jugadores->Height = 41 * TVariables::getResolucionY();
    FMenuPrincipal->BOpciones->Width = 233 * TVariables::getResolucionX();
    FMenuPrincipal->BOpciones->Height = 41 * TVariables::getResolucionY();
    FMenuPrincipal->BEditMazo->Width = 233 * TVariables::getResolucionX();
    FMenuPrincipal->BEditMazo->Height = 41 * TVariables::getResolucionY();
    FMenuPrincipal->BEditMapas->Width = 233 * TVariables::getResolucionX();
    FMenuPrincipal->BEditMapas->Height = 41 * TVariables::getResolucionY();
    FMenuPrincipal->BSalir->Width = 233 * TVariables::getResolucionX();
    FMenuPrincipal->BSalir->Height = 41 * TVariables::getResolucionY();
    FMenuPrincipal->BCreditos->Width = 233 * TVariables::getResolucionX();
    FMenuPrincipal->BCreditos->Height = 41 * TVariables::getResolucionY();

    FMenuPrincipal->B2Jugadores->Left = 24 * TVariables::getResolucionX();
    FMenuPrincipal->B2Jugadores->Top = 320 * TVariables::getResolucionY();
    FMenuPrincipal->BOpciones->Left = 24 * TVariables::getResolucionX();
    FMenuPrincipal->BOpciones->Top = 464 * TVariables::getResolucionY();
    FMenuPrincipal->BEditMazo->Left = 24 * TVariables::getResolucionX();
    FMenuPrincipal->BEditMazo->Top = 368 * TVariables::getResolucionY();
    FMenuPrincipal->BEditMapas->Left = 24 * TVariables::getResolucionX();
    FMenuPrincipal->BEditMapas->Top = 416 * TVariables::getResolucionY();
    FMenuPrincipal->BSalir->Left = 24 * TVariables::getResolucionX();
    FMenuPrincipal->BSalir->Top = 560 * TVariables::getResolucionY();
    FMenuPrincipal->BCreditos->Left = 24 * TVariables::getResolucionX();
    FMenuPrincipal->BCreditos->Top = 512 * TVariables::getResolucionY();

    FMenuPrincipal->B2Jugadores->Font->Size = 14 * TVariables::getResolucionX();
    FMenuPrincipal->BOpciones->Font->Size = 14 * TVariables::getResolucionX();
    FMenuPrincipal->BEditMazo->Font->Size = 14 * TVariables::getResolucionX();
    FMenuPrincipal->BEditMapas->Font->Size = 14 * TVariables::getResolucionX();
    FMenuPrincipal->BSalir->Font->Size = 14 * TVariables::getResolucionX();
    FMenuPrincipal->BCreditos->Font->Size = 14 * TVariables::getResolucionX();


    TRegDatos datos;

    ifstream fentrada( "save\\datos.dat" );    //guardar la resolucion
    datos.leer( fentrada );
    fentrada.close();
    datos.resolucion = RGResolucion->ItemIndex;
    ofstream fescritura( "save\\datos.dat" );
    datos.escribir( fescritura );
    fescritura.close();



    TVariables::setJugadorSelec(0,-1);
    TFJugador* NewForm;
    NewForm = new TFJugador(Application);
    Close();
    Hide();
    NewForm->ShowModal();
}
//---------------------------------------------------------------------------




