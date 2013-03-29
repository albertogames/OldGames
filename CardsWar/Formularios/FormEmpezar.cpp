//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#pragma package(smart_init)
#pragma resource "*.dfm"


//---------------------------------------------------------------------------

#include "FormEmpezar.h"
#include "FormJuego.h"


//---------------------------------------------------------------------------

TFEmpezar *FEmpezar;


//---------------------------------------------------------------------------
__fastcall TFEmpezar::TFEmpezar(TComponent* Owner)
    : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TFEmpezar::FormActivate(TObject *Sender)
{

    TRegDatos datos;

    ifstream fentrada( "save\\datos.dat" );
    datos.leer( fentrada );
    fentrada.close();


    Randomize;
    Width = TVariables::getResolucionX() * 1280;
    Height = TVariables::getResolucionX() * 1024;
    Position = poScreenCenter;
    TFJuego::setModJuego( -1 );

    IColina= new TImage(this);
    IColina->Parent = this;
    IProteger[0] = new TImage(this);
    IProteger[1] = new TImage(this);
    IProteger[0]->Parent = this;
    IProteger[1]->Parent = this;

    cambiarRes( BJugar );

    cambiarRes( CBNick1 );
    cambiarRes( CBNick2 );
    cambiarRes( CBMazo1 );
    cambiarRes( CBMazo2 );
    cambiarRes( CBModo );

    cambiarRes( LModjuego );
    cambiarRes( Jugador2 );
    cambiarRes( Label1 );
    cambiarRes( Label2 );
    cambiarRes( Label3 );
    cambiarRes( Label4 );
    cambiarRes( Label5 );
    cambiarRes( Label6 );
    cambiarRes( BCargarMapa);
    cambiarRes( IMapa );
    cambiarRes( BClose );
    cambiarRes ( CheckBoxIA );

    

    for ( int a = 0; *TVariables::getJugador( a ).nombre && a < 10; a++)
    {
        CBNick1->Items->Add( TVariables::getJugador( a ).nombre);
        CBNick2->Items->Add( TVariables::getJugador( a ).nombre);
    }

    CBModo->Items->Add("Rey de la colina");
    CBModo->Items->Add("Proteger");

    CBNick1->Text = TVariables::getJugador( datos.jugador1 ).nombre;
    CBNick1Change(this);
    CBMazo1->Text = TVariables::getJugador( datos.jugador1 ).mazos[datos.mazo1].nombre;
  //  CBMazo1Change(this);

    CBNick2->Text = TVariables::getJugador( datos.jugador2 ).nombre;
    CBNick2Change(this);
    CBMazo2->Text = TVariables::getJugador( datos.jugador2 ).mazos[datos.mazo2].nombre;
  //  CBMazo2Change(this);
    pantallaSelec = datos.mapa;
    CBModo->Text = datos.modJuego == 0 ? "Rey de la colina" : "Proteger";

    cargarMapa(pantallaSelec);
    CBModoChange(Application);
}
//---------------------------------------------------------------------------
void __fastcall TFEmpezar::guardarDatos(TObject *Sender)
{
    TRegDatos dat;
    ifstream fentrada( "save\\datos.dat" );
    dat.leer( fentrada );
    fentrada.close();
    dat.jugador1 = CBNick1->Items->IndexOf(CBNick1->Text);
    dat.jugador2 = CBNick2->Items->IndexOf(CBNick2->Text);
    dat.mazo1 = CBMazo1->Items->IndexOf(CBMazo1->Text);
    dat.mazo2 = CBMazo2->Items->IndexOf(CBMazo2->Text);
    dat.modJuego = CBModo->Items->IndexOf(CBModo->Text);
    strcpy(dat.mapa,pantallaSelec.c_str());
    ofstream fsalida( "save\\datos.dat" );
    dat.escribir( fsalida );
    fsalida.close();
}
void __fastcall TFEmpezar::BCloseClick(TObject *Sender)
{
    guardarDatos(this);
    Close();
}
//---------------------------------------------------------------------------


void __fastcall TFEmpezar::CBNick1Change(TObject *Sender)
{
    CBMazo1->Text = "";
    int a = CBNick1->Items->IndexOf( CBNick1->Text );
    TVariables::setJugadorSelec(0, a );
    CBMazo1->Items->Clear();
    if ( a != -1 )
        for ( a = 0; *TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[a].nombre ; a++ )
            CBMazo1->Items->Add( TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[a].nombre );
}
//---------------------------------------------------------------------------

void __fastcall TFEmpezar::CBNick2Change(TObject *Sender)
{
    CBMazo2->Text = "";
    int a = CBNick2->Items->IndexOf( CBNick2->Text );

    TVariables::setJugadorSelec(1,a);
    CBMazo2->Items->Clear();
    if ( a != -1 )
        for ( a = 0; *TVariables::getJugador( TVariables::getJugadorSelec(1) ).mazos[a].nombre ; a++ )
            CBMazo2->Items->Add( TVariables::getJugador( TVariables::getJugadorSelec(1) ).mazos[a].nombre );
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TFEmpezar::BJugarClick(TObject *Sender)
{
    if (TFJuego::getModJuego() != -1)
    {
        if ( ( TVariables::getJugadorSelec(0) == -1 ) || TVariables::getJugadorSelec(1) == -1 || CBMazo1->Items->IndexOf( CBMazo1->Text.c_str() ) == -1 || CBMazo2->Items->IndexOf( CBMazo2->Text.c_str() ) == -1 ) // || (TVariables::getJugadorSelec(0) == jugadorSelec[1]) )
            ShowMessage("Elige dos jugadores y un mazo para cada jugador");
        else
        {
            if ( CheckBoxIA->Checked && TFJuego::getModJuego() == 0 )
                ShowMessage("La IA no esta disponible para este modo de juego");
            else
            {
                TFJuego::setIA( CheckBoxIA->Checked );
                TFJuego::setNombre(0, TVariables::getJugador( TVariables::getJugadorSelec(0) ).nombre);
                TFJuego::setNombre(1 , TVariables::getJugador( TVariables::getJugadorSelec(1) ).nombre);
                int a = 0;



                a = CBMazo1->Items->IndexOf( CBMazo1->Text.c_str() );





                for (int c =0; c < 60; c++)
                    if ( *TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[a].carta[c] )
                        TFJuego::setMazo(0, c, crearCarta( TVariables::getJugador( TVariables::getJugadorSelec(0) ).mazos[a].carta[c] ) );
                    else
                        TFJuego::setMazo(0, c, NULL );

                a = 0;
                for(; strcmp( TVariables::getJugador( TVariables::getJugadorSelec(1) ).mazos[a].nombre, CBMazo2->Text.c_str() ) ; a++);

                for (int c =0; c < 60; c++)
                    if ( *TVariables::getJugador( TVariables::getJugadorSelec(1) ).mazos[a].carta[c] )
                        TFJuego::setMazo(1, c, crearCarta( TVariables::getJugador( TVariables::getJugadorSelec(1)).mazos[a].carta[c]) );
                    else
                        TFJuego::setMazo(1, c, NULL );

                FJuego = new TFJuego(Application);
                FJuego->ShowModal();
                guardarDatos(this);

                Close();
            }
        }
    }
    else
        ShowMessage("Selecciona un modo de juego");
}
//---------------------------------------------------------------------------

void __fastcall TFEmpezar::FormClose(TObject *Sender, TCloseAction &Action)
{
    pared.clear();
    Action = caFree;
    delete IColina;
    delete IProteger[0];
    delete IProteger[1];
}
//---------------------------------------------------------------------------

void __fastcall TFEmpezar::BCargarMapaClick(TObject *Sender)
{
    if (OpenDialog1->Execute())
        cargarMapa(OpenDialog1->FileName);
}

void __fastcall TFEmpezar::cargarMapa(String map)
{
        pared.clear();
        char aux[200];
        ifstream fichEntrada( map.c_str() );
        pantallaSelec = strstr(map.c_str(),"save\\Mapas" ) ;
        fichEntrada >> aux;
        IMapa->Picture->LoadFromFile(aux);

        TFJuego::setNomPantalla( map.c_str() );

        fichEntrada >> aux;
        pared.push_back( TPared(10/2 + IMapa->Left / TVariables::getResolucionX() - 10,50/2 + IMapa->Top / TVariables::getResolucionY() - 8, aux,false, this, 25/2,734/2)  );
        fichEntrada >> aux;
        pared.push_back( TPared(10/2 + IMapa->Left / TVariables::getResolucionX() - 10,10/2 + IMapa->Top / TVariables::getResolucionY() - 8, aux,false, this,1261/2,25/2)  );
        fichEntrada >> aux;
        pared.push_back( TPared(1245/2 + IMapa->Left / TVariables::getResolucionX() - 10,50/2 + IMapa->Top / TVariables::getResolucionY() - 8, aux,false, this,25/2,734/2)  );
        fichEntrada >> aux;
        pared.push_back( TPared(10/2 + IMapa->Left / TVariables::getResolucionX() - 10,800/2 + IMapa->Top / TVariables::getResolucionY() - 8, aux,false, this,1261/2,25/2)  );

        while ( !fichEntrada.eof() )
        {
            int x,y,w,h;
            bool r;
            char n[50];
            fichEntrada >> x;
            fichEntrada >> y;
            fichEntrada >> w;
            fichEntrada >> h;
            fichEntrada >> r;
            fichEntrada >> n;
            pared.push_back( TPared(x/2 + IMapa->Left / TVariables::getResolucionX() - 10,y/2 + IMapa->Top / TVariables::getResolucionY() - 8,n,r,this,w/2,h/2));
        }



        for ( deque<TPared>::iterator i = pared.begin(); i != pared.end(); i++)
            cambiarRes( (*i).getImagen() );
        fichEntrada.close();
}
//---------------------------------------------------------------------------


void __fastcall TFEmpezar::CBModoChange(TObject *Sender)
{
    TFJuego::setModJuego(CBModo->Items->IndexOf(CBModo->Text));
    switch (CBModo->Items->IndexOf(CBModo->Text))
    {
        case 0:
        {
            IProteger[0]->Visible = false;
            IProteger[1]->Visible = false;
            IColina->Picture->LoadFromFile("imagenes\\varios\\ColinaN.bmp");
            IColina->Transparent=true;
            IColina->AutoSize = true;
            IColina->AutoSize = false;
            IColina->Stretch = true;
            IColina->Width *= TVariables::getResolucionX( )/2;
            IColina->Height *= TVariables::getResolucionY( )/2;
            IColina->Left= IMapa->Left + IMapa->Width/2 - IColina->Width/2;
            IColina->Top= IMapa->Top + IMapa->Height/2 - IColina->Height/2;
            IColina->Visible=true;
            break;
        }
        case 1:
        {
            IColina->Visible = false;
            IProteger[0]->Picture->LoadFromFile("imagenes\\varios\\ProtegerA.bmp");
            IProteger[1]->Picture->LoadFromFile("imagenes\\varios\\ProtegerR.bmp");
            for (int  a = 0;a < 2;a++)
            {
                IProteger[a]->Transparent = true;
                IProteger[a]->AutoSize = true;
                IProteger[a]->AutoSize = false;
                IProteger[a]->Stretch = true;
                IProteger[a]->Width *= TVariables::getResolucionX( )/2;
                IProteger[a]->Height *= TVariables::getResolucionY( )/2;
                IProteger[a]->Visible = true;
                IProteger[a]->Top = IMapa->Top + IMapa->Height / 2 - IProteger[a]->Height/2;
            }
            IProteger[0]->Left = pared[0].getImagen()->Left + pared[0].getImagen()->Width;
            IProteger[1]->Left = pared[2].getImagen()->Left - IProteger[1]->Width;



        }
    }
}
//---------------------------------------------------------------------------


