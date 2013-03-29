


//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormPersonaje.h"
#include "FormJuego.h"
#include "FormArma.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFPersonaje *FPersonaje;

//---------------------------------------------------------------------------
__fastcall TFPersonaje::TFPersonaje(TComponent* Owner)
    : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TFPersonaje::FormActivate(TObject *Sender)
{
    Caption = TTio::getTio()->getNombre();
    if ( TTio::getTio()->getCarta() == NULL )
        ICarta->Picture->LoadFromFile( "imagenes\\cartas\\ficha.bmp" );
    else
        ICarta->Picture->LoadFromFile(  TTio::getTio()->getCarta()->getImagen()  )  ;
    LVida->Caption= IntToStr(TTio::getTio()->vida) + '/' + IntToStr(TTio::getTio()->vidaMax);
    LVelocidad->Caption= IntToStr(TTio::getTio()->movMax / 20);
    LFuerza->Caption= IntToStr(TTio::getTio()->fuerza);
    LRes1->Caption= IntToStr(TTio::getTio()->resistenciaC);
    LRes2->Caption= IntToStr(TTio::getTio()->resistenciaD);
    LRes3->Caption= IntToStr(TTio::getTio()->resistenciaM);
    LTipo->Caption=  TTio::getTio()->tipo;

    if ( TTio::getTio()->getArma(0) != NULL )
    {
        LArma1->Visible= true;
        BArma1->Caption= TTio::getTio()->getArma(0)->getNombre();
        BArma1->Visible= true;
        if (TTio::getTio()->getArma(1) != NULL )
        {
            LArma2->Visible= true;
            BArma2->Caption= TTio::getTio()->getArma(1)->getNombre();
            BArma2->Visible= true;
        }
    }

}
//---------------------------------------------------------------------------



void __fastcall TFPersonaje::BArma1Click(TObject *Sender)
{
    TFArma::setNumArma(0);
    TFArma* ventana = new TFArma(this);
    ventana->ShowModal();
    Close();

}
//---------------------------------------------------------------------------

void __fastcall TFPersonaje::BArma2Click(TObject *Sender)
{
    TFArma::setNumArma(1);
    TFArma* ventana = new TFArma(this);
    ventana->ShowModal();
    Close();

}
//---------------------------------------------------------------------------





void __fastcall TFPersonaje::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    Action = caFree;
}
//---------------------------------------------------------------------------






