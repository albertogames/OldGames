//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormEncantamientos.h"
#include "FormJuego.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFEncantamientos *FEncantamientos;
//---------------------------------------------------------------------------
__fastcall TFEncantamientos::TFEncantamientos(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFEncantamientos::FormActivate(TObject *Sender)
{
    Caption = "Encantamientos de " + TFJuego::getNombre( TVariables::getJugadorSelec(0) );
    CBJugador->Items->Add( TFJuego::getNombre( 0 ) );
    CBJugador->Items->Add( TFJuego::getNombre( 1 ) );

    CBJugador->Text = TFJuego::getNombre( TVariables::getJugadorSelec(0) );
    int a = 0;
    for( ; FJuego->getEncantamiento( TVariables::getJugadorSelec(0), a) != NULL; a++ )
        CBEncantamiento->Items->Add( TFJuego::getEncantamiento( TVariables::getJugadorSelec(0),a)->getNombre() );
    a--;
    if ( TFJuego::getEncantamiento( TVariables::getJugadorSelec(0),a) != NULL )
    {
        CBEncantamiento->Text = TFJuego::getEncantamiento( TVariables::getJugadorSelec(0),a)->getNombre();
        ICarta->Picture->LoadFromFile(TFJuego::getEncantamiento(TVariables::getJugadorSelec(0), a)->getImagen());
    }
    if ( FJuego->getDestruirEncantamientos() > 0 )
    {
        BEncantamiento->Caption = "DESTRUIR";
        BEncantamiento->Visible = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFEncantamientos::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TFEncantamientos::CBJugadorChange(TObject *Sender)
{

    int numJugador = CBJugador->Items->IndexOf(CBJugador->Text);
    if (numJugador != -1)
    {
        Caption = "Encantamientos de " + TFJuego::getNombre( TVariables::getJugadorSelec(0) );
        TVariables::setJugadorSelec(0, CBJugador->Text == TFJuego::getNombre(0) ? 0 : 1 );


        CBEncantamiento->Items->Clear();
        int a=0;
        for (; TFJuego::getEncantamiento(TVariables::getJugadorSelec(0),a)!=NULL ; a++)
            CBEncantamiento->Items->Add(TFJuego::getEncantamiento(TVariables::getJugadorSelec(0),a)->getNombre());
        a--;
        if ( a >= 0 && TFJuego::getEncantamiento( TVariables::getJugadorSelec(0),a) != NULL )
        {
            ICarta->Visible = true;
            CBEncantamiento->Text = TFJuego::getEncantamiento( TVariables::getJugadorSelec(0), a )->getNombre();
            ICarta->Picture->LoadFromFile(TFJuego::getEncantamiento(TVariables::getJugadorSelec(0), a)->getImagen());
        }
        else
        {
            ICarta->Visible = false;
            CBEncantamiento->Text = "";
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TFEncantamientos::CBEncantamientoChange(TObject *Sender)
{
    int numEncantamiento = CBEncantamiento->Items->IndexOf(CBEncantamiento->Text);
    if (numEncantamiento != -1)
    {
        ICarta->Visible = true;

        ICarta->Picture->LoadFromFile(TFJuego::getEncantamiento(TVariables::getJugadorSelec(0), numEncantamiento)->getImagen());
    }
    else
        ICarta->Visible = false;

}
//---------------------------------------------------------------------------


void __fastcall TFEncantamientos::ordenarEncantamientos(int d)
{
    int a = 0;
    for ( ; FJuego->getEncantamiento( d,  a  ) != NULL; a++);
    for ( ; FJuego->getEncantamiento( d, a+1 ) != NULL; a++ )
        FJuego->setEncantamiento( d, a, FJuego->getEncantamiento( d, a+1 ) );
    FJuego->setEncantamiento( d, a, NULL);
}


//---------------------------------------------------------------------------



void __fastcall TFEncantamientos::BEncantamientoClick(TObject *Sender)
{
    if ( FJuego->getDestruirEncantamientos() > 0 )
    {
        int a = 0;
        for ( ; FJuego->getEncantamiento( TVariables::getJugadorSelec( 0 ) , a)->getNombre()  != CBEncantamiento->Text ; a++);

        TFJuego::setDestruyeEncant( true );            //llama al "destructor" del encantamiento
        TFJuego::getEncantamiento( TVariables::getJugadorSelec( 0 ) , a)->usarHabilidad();
        TFJuego::setDestruyeEncant( false );

        FJuego->setNumCartasCem( TVariables::getJugadorSelec( 0 ) , TFJuego::getNumCartasCem( TVariables::getJugadorSelec( 0 ) ) +1 );//Sumar 1 a las cartas del cementerio;

        FJuego->setCementerio( TVariables::getJugadorSelec( 0 ) ,TFJuego::getNumCartasCem( TVariables::getJugadorSelec( 0 ) )-1, TFJuego::getEncantamiento( TVariables::getJugadorSelec( 0 ) ,a ) );//Mandar la carta al cementerio;
        FJuego->setEncantamiento( TVariables::getJugadorSelec( 0 ) ,a, NULL );//Borrarla;
        CBEncantamiento->Items->Delete(a);
        CBEncantamiento->Text = "";
        ICarta->Picture = NULL;
        if ( FJuego->getTurno() == TVariables::getJugadorSelec( 0 ) )
        {
//            FJuego->ICementerio->Picture->LoadFromFile( FJuego->getCementerio( FJuego->getTurno(), FJuego->getNumCartasCem( FJuego->getTurno() )-1 )->getImagen() );//Ver la ultima carta del cementerio;
//            FJuego->ICementerio->Visible = true;
        }
        TFJuego::setDestruirEncantamientos( FJuego->getDestruirEncantamientos() - 1 );
        ordenarEncantamientos( TVariables::getJugadorSelec( 0 ) );
        if ( FJuego->getDestruirEncantamientos() == 0 )
            BEncantamiento->Visible = false;
    }
}
//---------------------------------------------------------------------------




