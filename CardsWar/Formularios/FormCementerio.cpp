
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
#include "FormCementerio.h"
#include "FormJuego.h"
#
TFCementerio *FCementerio;
int TFCementerio::recuperarCriaturas = 0;


    TCarta* cartaC;
//---------------------------------------------------------------------------
__fastcall TFCementerio::TFCementerio(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TFCementerio::FormActivate(TObject *Sender)
{
    Caption = "Cementerio de " + TFJuego::getNombre( TFJuego::getTurnoC() );
    ICarta->Picture->LoadFromFile( TFJuego::getCementerio( TFJuego::getTurnoC() , TFJuego::getNumCartasCem(TFJuego::getTurnoC())-1 )->getImagen());
    CBCementerio->Text = TFJuego::getCementerio( TFJuego::getTurnoC(), TFJuego::getNumCartasCem(TFJuego::getTurnoC())-1 )->getNombre();
    for(int i= 0; i < TFJuego::getNumCartasCem(TFJuego::getTurnoC());i++)
        CBCementerio->Items->Add( TFJuego::getCementerio( TFJuego::getTurnoC(), i )->getNombre() );
    CBCementerioChange(this);
}

//---------------------------------------------------------------------------
void __fastcall TFCementerio::CBCementerioChange(TObject *Sender)
{
    BCementerio->Visible = false;
    int numCartaC = CBCementerio->Items->IndexOf(CBCementerio->Text);

    if ( numCartaC != -1 )
    {
        cartaC = TFJuego::getCementerio( TFJuego::getTurnoC(),numCartaC );
        ICarta->Picture->LoadFromFile( cartaC->getImagen() );
        ICarta->Visible = true;
        if (( recuperarCriaturas > 0 ) && ( cartaC->getTipo() == criatura ) && ( FJuego->getNumCartasMano(TFJuego::getTurno()) < 7 ))
        {
            BCementerio->Caption= "Recuperar";
            BCementerio->Visible= true;
        }
    }
    else
        ICarta->Visible = false;
}
//---------------------------------------------------------------------------
void ordenarCementerio()
{
    int i= 0;
    for(; TFJuego::getCementerio( TFJuego::getTurnoC(), i ) != NULL ;i++);

    for(;i < TFJuego::getNumCartasCem(TFJuego::getTurnoC()) - 1;i++)
        TFJuego::setCementerio( TFJuego::getTurnoC(), i, TFJuego::getCementerio( TFJuego::getTurnoC(), i + 1 ) );

    TFJuego::setCementerio( TFJuego::getTurnoC(), TFJuego::getNumCartasCem(TFJuego::getTurnoC()), NULL );
    TFJuego::setNumCartasCem(TFJuego::getTurnoC(),TFJuego::getNumCartasCem(TFJuego::getTurnoC()) - 1);
    FCementerio->Close();
};









void __fastcall TFCementerio::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    Action = caFree;
}
//---------------------------------------------------------------------------




void __fastcall TFCementerio::BCementerioClick(TObject *Sender)
{
    if (recuperarCriaturas > 0)
    {
        recuperarCriaturas--;

        FJuego->setNumCartasMano(TFJuego::getTurno(), FJuego->getNumCartasMano(TFJuego::getTurno())  +1);

        int i = 0;
        for (;TFJuego::getCementerio(TFJuego::getTurnoC(),i) != cartaC;i++);    //busca la carta del cementerio a kitar
        TFJuego::setCementerio(TFJuego::getTurnoC(),i,NULL);

        i = 0;
        for (; FJuego->getMano(TFJuego::getTurno(),i) != NULL;i++);      //Añade la carta a la mano
        FJuego->setMano(TFJuego::getTurno(),i,cartaC);

        cartaC= NULL;

        FJuego->setManoIImagen(i, FJuego->getMano(TFJuego::getTurno(),i)->getImagen());

        ordenarCementerio();
    }
}
//---------------------------------------------------------------------------




