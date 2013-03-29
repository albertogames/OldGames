//---------------------------------------------------------------------------
//#include <vcl.h>

#pragma hdrstop
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
#include "FormCarta.h"
#include "FormJuego.h"


//---------------------------------------------------------------------------
TFCarta *FCarta;

String TFCarta::nombreCarta;
//---------------------------------------------------------------------------






__fastcall TFCarta::TFCarta(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFCarta::FormActivate(TObject *Sender)
{
    TCarta* carta = crearCarta( nombreCarta.c_str() );
    imagCarta->Picture->LoadFromFile(carta->getImagen());
    Caption = nombreCarta;
    delete carta;
}
//---------------------------------------------------------------------------



void __fastcall TFCarta::FormClose(TObject *Sender, TCloseAction &Action)
{
    Action = caFree;    
}
//---------------------------------------------------------------------------

