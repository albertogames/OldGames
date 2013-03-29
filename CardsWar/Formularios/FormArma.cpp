//---------------------------------------------------------------------------

//#include <vcl.h>
#pragma hdrstop

#include "FormArma.h"
#include "FormJuego.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"



TFArma *FArma;
int TFArma::numArma;

//---------------------------------------------------------------------------
__fastcall TFArma::TFArma(TComponent* Owner): TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFArma::FormActivate(TObject *Sender)
{
    TArma* arma= TTio::getTio()->getArma(numArma);
    Caption = arma->getNombre();
    LFuerza->Caption= IntToStr(arma->getFuerza());

    if (arma->getResistenciaC() + arma->getResistenciaD() + arma->getResistenciaM() != 0)
    {
        LResC->Caption= IntToStr(arma->getResistenciaC());
        LResD->Caption= IntToStr(arma->getResistenciaD());
        LResM->Caption= IntToStr(arma->getResistenciaM());
    }
    else
    {
        IResC->Visible= false;
        IResD->Visible= false;
        IResM->Visible= false;
        LabelResistencia->Visible= false;
    }
    if (TTio::getTj() != TFJuego::getTurno())
        BDesequipar->Visible= false;

    if (arma->getNombre() == "Mascara del diablo")        //Carta MascaraDelDiablo
        BDesequipar->Visible= false;
    if ( arma->getCarta() != NULL )
        IArma->Picture->LoadFromFile(arma->getCarta()->getImagen());
    else
        IArma->Picture->LoadFromFile("Imagenes\\Cartas\\ficha.bmp");
}
//---------------------------------------------------------------------------
void __fastcall TFArma::BDesequiparClick(TObject *Sender)
{
    destruirArma();
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TFArma::FormClose(TObject *Sender, TCloseAction &Action)
{
    Action = caFree;      
}
//---------------------------------------------------------------------------

void __fastcall TFArma::destruirArma()
{
    TArma* arma= TTio::getTio()->getArma(numArma);
    bool enc = false;
    if (TTio::getTio()->getArma(0)->getCarta() != NULL)
    {
        enc = true;
        TFJuego::setNumCartasCem(TTio::getTj(),TFJuego::getNumCartasCem(TTio::getTj()) + 1);      //Sumar 1 a las cartas del cementerio;
        if (TTio::getTio()->getArma(0) == arma)
            TFJuego::setCementerio( TTio::getTj(), TFJuego::getNumCartasCem(TTio::getTj())-1, TTio::getTio()->getArma(0)->getCarta() );
        else
            TFJuego::setCementerio( TTio::getTj(), TFJuego::getNumCartasCem(TTio::getTj())-1, TTio::getTio()->getArma(1)->getCarta() );
    }

    if (TTio::getTio()->getArma(0) == arma)              //si desekipas la 1º arma
        TTio::getTio()->setArma(0,TTio::getTio()->getArma(1));      //pones el arma 2 en el arma 1

    TTio::getTio()->setArma(1,NULL);                     //el arma 2 es null

    if (TFJuego::getTurno() == TTio::getTj() && enc )
    {
        FJuego->ICementerio->Picture->LoadFromFile(TFJuego::getCementerio(  TTio::getTj(), TFJuego::getNumCartasCem( TTio::getTj() )-1  )->getImagen());//Ver la ultima carta del cementerio;
        FJuego->ICementerio->Visible=true;
    }

    delete arma;
    //Poner enabled false del boton del arma
    arma= NULL;
}



