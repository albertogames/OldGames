
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
#include "FormMenuMazo.h"
#include "FormJuego.h"
#include "FormCarta.h"
#include "FormMensaje.h"
//---------------------------------------------------------------------------
TFMenuMazo *FMenuMazo;


//---------------------------------------------------------------------------

    TCarta* T[100];



//VARIABLES
    TCarta* mazoActual[60];
    TMenuItem* agregar;




__fastcall TFMenuMazo::TFMenuMazo(TComponent* Owner)
    : TForm(Owner)
{
    BNombre->Enabled = false;
    BMana->Enabled = true;
    BTipo->Enabled = true;
    randomize();
    Width = TVariables::getResolucionX() * 1280;
    Height = TVariables::getResolucionX() * 1024;
    Position = poScreenCenter;


    cambiarRes( CBJugador );
    cambiarRes( CBMazo );

    cambiarRes( BCreaMazo );
    cambiarRes( BBorrarMazo );
    cambiarRes( BCartas );
    cambiarRes( BVerTuMazo );

    cambiarRes( BNombre );
    cambiarRes( BMana );
    cambiarRes( BTipo );

    cambiarRes( Label1 );
    cambiarRes( Label2 );

    cambiarRes( BotonClose );

    T[0] = crearCarta("Dragon esqueleto");
    T[1] = crearCarta("Gigante de las cavernas");
    T[2] = crearCarta("Espada de dragon");
    T[3] = crearCarta("Espada legendaria");
    T[4] = crearCarta("Arquero solitario");
    T[5] = crearCarta("Enano con armadura");
    T[6] = crearCarta("Tierras lejanas");
    T[7] = crearCarta("Arco corto");
    T[8] = crearCarta("Murcielago");
    T[9] = crearCarta("Regenerar almas");
    T[10] = crearCarta("Preparacion de lucha");
    T[11] = crearCarta("Escuela de armas");
    T[12] = crearCarta("Tortuga gigante");
    T[13] = crearCarta("Heroes");
    T[14] = crearCarta("Zombi siniestro");
    T[15] = crearCarta("Aparicion del mal");
    T[16] = crearCarta("Dosis de supervivencia");
    T[17] = crearCarta("Mascara del diablo");
    T[18] = crearCarta("Mitosis");
    T[19] = crearCarta("Jinete oscuro");
    T[20] = crearCarta("Bosque tenebroso");
    T[21] = crearCarta("Hombre lobo");
    T[22] = crearCarta("Reina de los zombis");
    T[23] = crearCarta("Brazaletes de tormenta");
    T[24] = crearCarta("Meteoro");
    T[25] = crearCarta("Mana");
    T[26] = crearCarta("Curandera");
    T[27] = crearCarta("Hada de la noche");
    T[28] = crearCarta("Orco de hierro");
    T[29] = crearCarta("Mago del dragon");
    T[30] = crearCarta("Elfa exploradora");
    for ( int a = 31; a < 100; a++)
        T[a] = 0;

    cartas[0] = Carta1;      cartas[10] = Carta11;    cartas[20] = Carta21;
    cartas[1] = Carta2;      cartas[11] = Carta12;    cartas[21] = Carta22;
    cartas[2] = Carta3;      cartas[12] = Carta13;    cartas[22] = Carta23;
    cartas[3] = Carta4;      cartas[13] = Carta14;    cartas[23] = Carta24;
    cartas[4] = Carta5;      cartas[14] = Carta15;    cartas[24] = Carta25;
    cartas[5] = Carta6;      cartas[15] = Carta16;    cartas[25] = Carta26;
    cartas[6] = Carta7;      cartas[16] = Carta17;    cartas[26] = Carta27;
    cartas[7] = Carta8;      cartas[17] = Carta18;    cartas[27] = Carta28;
    cartas[8] = Carta9;      cartas[18] = Carta19;    cartas[28] = Carta29;
    cartas[9] = Carta10;     cartas[19] = Carta20;    cartas[29] = Carta30;

    cartas[30] = Carta31;    cartas[40] = Carta41;    cartas[50] = Carta51;
    cartas[31] = Carta32;    cartas[41] = Carta42;    cartas[51] = Carta52;
    cartas[32] = Carta33;    cartas[42] = Carta43;    cartas[52] = Carta53;
    cartas[33] = Carta34;    cartas[43] = Carta44;    cartas[53] = Carta54;
    cartas[34] = Carta35;    cartas[44] = Carta45;    cartas[54] = Carta55;
    cartas[35] = Carta36;    cartas[45] = Carta46;    cartas[55] = Carta56;
    cartas[36] = Carta37;    cartas[46] = Carta47;    cartas[56] = Carta57;
    cartas[37] = Carta38;    cartas[47] = Carta48;    cartas[57] = Carta58;
    cartas[38] = Carta39;    cartas[48] = Carta49;    cartas[58] = Carta59;
    cartas[39] = Carta40;    cartas[49] = Carta50;    cartas[59] = Carta60;






    for (int a = 0; a < 60; a++)
        cambiarRes(cartas[a]);

    BCreaMazo->Enabled = false;
    for (int a = 1;a <= 60; a++)
        mazoActual[a] = 0;
    menuc = new TPopupMenu(this);

    TMenuItem* ver = new TMenuItem(menuc);
    agregar = new TMenuItem(menuc);

    menuc->Items->Add(ver);
    ver->Caption = "Ver";
    ver->OnClick = verclick;

    menuc->Items->Add(agregar);
    agregar->Caption = "Agregar";
    agregar->OnClick = agregarclick;

    for (int a = 0;a < 60; a++)
        cartas[a]->PopupMenu = menuc;

    for ( int a = 0; strcmp(TVariables::getJugador(a).nombre, ""); a++ )
        CBJugador->Items->Add( TVariables::getJugador(a).nombre );

    mazoSelec = -1;
}

void __fastcall TFMenuMazo::borrarPantalla()
{
    for (unsigned int a = 0; a < 60; a++)
        if (mazoActual[a] != NULL)
        {
            delete mazoActual[a];
            mazoActual[a] = NULL;
        }
    cargar();

}

void __fastcall TFMenuMazo::cargar()
{
    if ( !BNombre->Enabled )
        for ( int a = 0; a < 59; a++)
            for ( int b = 0; b < 59-a && mazoActual[b+1]; b++)
                if ( mazoActual[b]->getNombre() > mazoActual[b+1]->getNombre()  )
                {
                    TCarta* cartaAux = mazoActual[b];
                    mazoActual[b] = mazoActual[b+1];
                    mazoActual[b+1] = cartaAux;
                }


    if ( !BMana->Enabled )
        for ( int a = 0; a < 59; a++)
            for ( int b = 0; b < 59-a && mazoActual[b+1]; b++)
                if ( mazoActual[b]->getPm() > mazoActual[b+1]->getPm()  )
                {
                    TCarta* cartaAux = mazoActual[b];
                    mazoActual[b] = mazoActual[b+1];
                    mazoActual[b+1] = cartaAux;
                }
                else
                    if ( mazoActual[b]->getPm() == mazoActual[b+1]->getPm()  )
                        if (  mazoActual[b]->getNombre() > mazoActual[b+1]->getNombre() )
                        {
                            TCarta* cartaAux = mazoActual[b];
                            mazoActual[b] = mazoActual[b+1];
                            mazoActual[b+1] = cartaAux;
                        }

    if ( !BTipo->Enabled )
        for ( int a = 0; a < 59; a++)
            for ( int b = 0; b < 59-a && mazoActual[b+1]; b++)
                if ( mazoActual[b]->getTipo() > mazoActual[b+1]->getTipo()  )
                {
                    TCarta* cartaAux = mazoActual[b];
                    mazoActual[b] = mazoActual[b+1];
                    mazoActual[b+1] = cartaAux;
                }
                else
                    if ( mazoActual[b]->getTipo() == mazoActual[b+1]->getTipo()  )
                        if (  mazoActual[b]->getNombre() > mazoActual[b+1]->getNombre() )
                        {
                            TCarta* cartaAux = mazoActual[b];
                            mazoActual[b] = mazoActual[b+1];
                            mazoActual[b+1] = cartaAux;
                        }

    for (int a= 0; a < 60; a++)
    {
        if ( mazoActual[a] != NULL )
        {
            cartas[a]->Picture->LoadFromFile( mazoActual[a]->getImagen() );
            cartas[a]->Enabled = true;
        }
        else
        {
            cartas[a]->Picture = NULL;
            cartas[a]->Enabled = false;
        }
    }
}


//---------------------------------------------------------------------------
void __fastcall TFMenuMazo::BotonCloseClick(TObject *Sender)
{
    guardar();
    borrarPantalla();
	for (int i = 0;T[i] != NULL; i++)
		delete T[i];
    Close();
}
//---------------------------------------------------------------------------



void __fastcall TFMenuMazo::BCartasClick(TObject *Sender)      //Ver cartas disponibles
{
    BCartas->Enabled = false;
    agregar->Caption ="Agregar";
    borrarPantalla();
    for (int a= 0; a < 60 ; a++ )
    {
        if ( T[a] != NULL )
            mazoActual[a] = crearCarta( T[a]->getNombre().c_str() );
        else
            if ( mazoActual[a] != NULL )
                delete ( mazoActual[a] );
    }
    if (mazoSelec != -1)
        BVerTuMazo->Enabled = true;
    cargar();
}
//---------------------------------------------------------------------------

void __fastcall TFMenuMazo::BVerTuMazoClick(TObject *Sender)
{
    BVerTuMazo->Enabled = false;
    BCartas->Enabled = true;
    agregar->Caption = "Quitar";
    borrarPantalla();
    for (int a = 0;a < 60; a++)
        if ( *TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[mazoSelec].carta[a])
            mazoActual[a] = crearCarta( TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[mazoSelec].carta[a] );

    cargar();

}
//---------------------------------------------------------------------------


void __fastcall TFMenuMazo::verclick(TObject *Sender)
{
    TFCarta::setNombreCarta( mazoActual[cartaSelec]->getNombre() );
    TFCarta* FormVerCarta;
    FormVerCarta = new TFCarta(Application);
    FormVerCarta->ShowModal();
}

void __fastcall TFMenuMazo::agregarclick(TObject *Sender)
{
    if (mazoSelec == -1)
        ShowMessage("Selecciona un Mazo");
    else
    {
        int cont = 0;
        if (BVerTuMazo->Enabled)
        {       //Agregar
            int a = 0;
            for ( ;*TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[mazoSelec].carta[a] &&   a < 60 ;a++)
                if (!strcmp( TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[mazoSelec].carta[a],mazoActual[cartaSelec]->getNombre().c_str() ))
                    cont++;
            if (a < 60)
            {
                if (cont >= 3 && mazoActual[cartaSelec]->getNombre()!= "Mana" )
                    ShowMessage("Solo puedes tener 3 cartas iguales en el mazo");
                else
                    TVariables::setJugadorMazoCarta( TVariables::getJugadorSelec(0), mazoSelec, a, mazoActual[cartaSelec]->getNombre().c_str() ) ;
            }
            else
                ShowMessage("Solo puedes tener 60 cartas en un mazo");
        }
        else
        {    //Quitar
            int a = 0;
            for( ;strcmp( TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[mazoSelec].carta[a],mazoActual[cartaSelec]->getNombre().c_str()); a++);

            *TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[mazoSelec].carta[a] = '\0';

            for ( ;(*TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[mazoSelec].carta[a+1]) && (a+1 < 60);a++)
                TVariables::setJugadorMazoCarta( TVariables::getJugadorSelec(0), mazoSelec, a, TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[mazoSelec].carta[a+1] );

            if (a < 60)
                TVariables::setJugadorMazoCarta( TVariables::getJugadorSelec(0), mazoSelec, a, "");

            delete mazoActual[cartaSelec];
            mazoActual[cartaSelec] = NULL;

            a = cartaSelec;
            for( ;mazoActual[a+1] && (a+1 < 60);a++)
                mazoActual[a] = mazoActual[a + 1];

            if (a < 60)
                mazoActual[a] = NULL;

            cargar();

        }
    }
}

void __fastcall TFMenuMazo::cartaClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    for ( cartaSelec = 0; cartas[cartaSelec]!= static_cast<TImage*>(Sender) ; cartaSelec++);
	
}
//---------------------------------------------------------------------------
void __fastcall TFMenuMazo::BCreaMazoClick(TObject *Sender)
{

    TVariables::setNumMensaje(1);

    TFMensaje* NewForm;
    NewForm = new TFMensaje(Application);
    NewForm->ShowModal();

    if ( TVariables::getNumBoton() == 1 )
    {
        CBMazo->Items->Add( TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[mazoSelec].nombre );
        CBMazo->Text = TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[mazoSelec].nombre;
        BBorrarMazo->Enabled = true;
        BCartas->Enabled = true;
        BVerTuMazo->Enabled = false;
        TVariables::iniciarMazo(mazoSelec);
        borrarPantalla();
    }
}
//---------------------------------------------------------------------------

void __fastcall TFMenuMazo::CBJugadorChange(TObject *Sender)
{
    TVariables::setJugadorSelec(0, CBJugador->Items->IndexOf(CBJugador->Text) );

    mazoSelec = -1;
    CBMazo->Text = "";
    CBMazo->Items->Clear();
    if (TVariables::getJugadorSelec(0)+1)  //si hay un jugador seleccionado
    {
        for(int a = 0 ; *TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[a].nombre;a++)
            CBMazo->Items->Add( TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[a].nombre );
        BCreaMazo->Enabled = true;
        BCartas->Enabled = true;
    }
    else
    {
        BCreaMazo->Enabled = false;
        BVerTuMazo->Enabled = false;
    }
    borrarPantalla();
    BBorrarMazo->Enabled = false;
    BCartas->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TFMenuMazo::CBMazoChange(TObject *Sender)
{
    agregar->Caption ="Quitar"; //Menu k sale cuando le das a la carta.
    mazoSelec = CBMazo->Items->IndexOf(CBMazo->Text) ;

    borrarPantalla();

    if (mazoSelec != -1)
    {
        for (int a = 0; a < 60;a++)
            if (*TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[mazoSelec].carta[a])
            mazoActual[a] = crearCarta( TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[mazoSelec].carta[a] );
        BBorrarMazo->Enabled = true;
    }
    else
        BBorrarMazo->Enabled = false;
    BVerTuMazo->Enabled = false;
    BCartas->Enabled = true;

    cargar();
    
}
//---------------------------------------------------------------------------

void __fastcall TFMenuMazo::BBorrarMazoClick(TObject *Sender)
{
    TVariables::borrarJugadorMazo( TVariables::getJugadorSelec(0),mazoSelec );
    borrarPantalla();
    cargar();
    int a = mazoSelec;
    for ( ; *TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[a+1].nombre && a < 50 /* != '\0' */; a++)
        TVariables::setJugadorMazo( TVariables::getJugadorSelec(0),a,TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[a+1]);

    TVariables::borrarJugadorMazo( TVariables::getJugadorSelec(0),a );
    
    CBMazo->Items->Delete(mazoSelec);
    mazoSelec = -1;
    BBorrarMazo->Enabled = false;
    CBMazo->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TFMenuMazo::BNombreClick(TObject *Sender)
{
    BNombre->Enabled = false;
    BMana->Enabled = true;
    BTipo->Enabled = true;
    cargar();
}
//---------------------------------------------------------------------------

void __fastcall TFMenuMazo::BManaClick(TObject *Sender)
{
    BNombre->Enabled = true;
    BMana->Enabled = false;
    BTipo->Enabled = true;
    cargar();
}
//---------------------------------------------------------------------------

void __fastcall TFMenuMazo::BTipoClick(TObject *Sender)
{
    BNombre->Enabled = true;
    BMana->Enabled = true;
    BTipo->Enabled = false;
    cargar();
}
//---------------------------------------------------------------------------





void __fastcall TFMenuMazo::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    Action = caFree;    
}
//---------------------------------------------------------------------------

