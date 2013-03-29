//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "FormJuego.h"
#include "FormCementerio.h"
#include "FormEncantamientos.h"
#include "FormCarta.h"
#include "FormPersonaje.h"
#include "FormArma.h"
#include "math.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFJuego *FJuego;

TCarta* TFJuego::mazo[2][60];
int TFJuego::modJuego = 0;
TRegMap TFJuego::AMap[10];
String TFJuego::nombre[2];
int TFJuego::turnoC;
int TFJuego::numCartasCem[2]={0,0};
TCarta* TFJuego::cementerio[2][60];
int TFJuego::turno;
TCarta* TFJuego::encantamiento[2][20];
TImage* TFJuego::imagenBT[2];
int TFJuego::destruirEncantamientos = 0;
bool TFJuego::destruyeEncant = false;
int TFJuego::tjAnt = 0;
int TFJuego::ttAnt = 0;
String TFJuego::nomPantalla;
deque <TPared> TFJuego::paredes;
bool TFJuego::IA;
//---------------------------------------------------------------------------
__fastcall TFJuego::TFJuego(TComponent* Owner)
    : TForm(Owner)
{                                                             

}
//---------------------------------------------------------------------------

float sqr(float f)
{
    return f * f;
}
void  barajear(int jugador);
void robar();//Roba el que tenga turno


void __fastcall TFJuego::FormActivate(TObject *Sender)
{
    cheat = 0;
    cheatIA = false;//ver cartas de la IA
    Width = TVariables::getResolucionX() * 1280;
    Height = TVariables::getResolucionX() * 1024;
    Position = poScreenCenter;


    cambiarRes(IMapa);
    tjAnt = ttAnt = 0;

    cambiarRes(Image1);
    cambiarRes(ICementerio);
    cambiarRes(IMazo);

    cambiarRes(LNombre);
    cambiarRes(LPm);
    cambiarRes(LMazo);

    cambiarRes(BEncant);
    cambiarRes(BCerrar);
    cambiarRes(BCambiarTurno);

    //Iniciar Cartas

    //tioMataTio = false;
    for (int i = 0; i<2;i++)
    {
        tierrasLejanas[i]= 0;
        heroes[i]= false;
        for (int k=0;k< 10;k++)
            zombiSiniestro[i][k]=0;
        imagenBT[i] = NULL;
    //Iniciar encantamientos
        for (int k = 0; k<20;k++)
            encantamiento[i][k] = NULL;

    }
    destruyeEncant= false;
    destruirEncantamientos = 0;
    TArma::setArmaCrear(NULL);
    desactivarHechizos();
    escuelaDeArmas= false;

    mataCriaturaACriatura= false;
    TFCementerio::setRecuperarCriaturas(0);

    bosqueT= false;

    //-------------

    menuc = new TPopupMenu(this);
    habilidadCriatura = false;
    //Inicializar mano
    for (int j = 0; j < 2; j++)
        for (int c = 0 ;c<7 ; c++)
            mano[j][c] = NULL;

    //Inicializar mazo
    barajear(0);
    barajear(1);

    //Inicializar numero de cartas
    for(int j = 0; j < 2;j++)
    {
        numCartasMano[j] = numCartasMazo[j] = 0;
        for( int c = 0; c < 60 ; c++ )
            if (mazo[j][c])
                numCartasMazo[j]++;
        numCartasCem[j]=0;
    }

    //Imagenes de la mano en array
    manoI[0]=IMano1;
    manoI[1]=IMano2;
    manoI[2]=IMano3;
    manoI[3]=IMano4;
    manoI[4]=IMano5;
    manoI[5]=IMano6;
    manoI[6]=IMano7;

    for(int c = 0; c < 7; c++)
    {
        manoI[c]->Visible = false;
        cambiarRes(manoI[c]);
    }

    //Inicializar tios
    for( int j = 0; j < 2 ; j++ )
        for( int t = 0; t < 20 ; t++)
            TTio::setNullTio(j,t);

    TTio::setMenuj( new TPopupMenu(this) );

    switch (modJuego)
    {
        case -1:
        {
            IColina->Visible = false;
            IProteger[0]->Visible = false;
            IProteger[1]->Visible = false;
            break;
        }
        case 0:
        {
            jugadorColina = 0;
            turnosColina =0;
            IColina= new TImage(this);
            IColina->Picture->LoadFromFile("imagenes\\varios\\ColinaN.bmp");
            IColina->Transparent=true;
            IColina->AutoSize = true;
            cambiarRes(IColina);
            IColina->Left= IMapa->Left + IMapa->Width/2 - IColina->Width/2;
            IColina->Top= IMapa->Top + IMapa->Height/2 - IColina->Height/2;
            IColina->Visible=true;
            IColina->Parent=this;

            LColina = new TLabel(this);
            LColina->Left= 600;
            LColina->Top= 8;
            LColina->Transparent= true;
            LColina->Font->Size= 16;
            LColina->Alignment= taCenter;


            cambiarRes(LColina);
            break;
        }
        case 1:
        {
            for ( int a = 0; a < 2; a++)
            {
                IProteger[a] = new TImage(this);
                IProteger[a]->Transparent = true;
                IProteger[a]->AutoSize = true;
                IProteger[a]->Visible = true;
                IProteger[a]->Parent = this;
                IProteger[a]->Top = 339;

                LProteger[a] = new TLabel(this);
                LProteger[a]->Font->Size = 16;
                LProteger[a]->Transparent = true;
                LProteger[a]->Visible=true;
                LProteger[a]->AutoSize = true;
                LProteger[a]->Top =  10;

                VProteger[a] = 40;
                LProteger[a]->Caption = "Vida: " + IntToStr(VProteger[a]);
            }
            LProteger[0]->Left = 80;
            LProteger[1]->Left = 1125;


            IProteger[0]->Left = 35;
            IProteger[1]->Left = 1167;

            LProteger[0]->Font->Color = clBlue;
            LProteger[1]->Font->Color = clRed;
            IProteger[0]->Picture->LoadFromFile("imagenes\\varios\\ProtegerA.bmp");
            IProteger[1]->Picture->LoadFromFile("imagenes\\varios\\ProtegerR.bmp");
            cambiarRes(IProteger[0]);
            cambiarRes(IProteger[1]);
            cambiarRes(LProteger[0]);
            cambiarRes(LProteger[1]);
        }
    }
    if (modJuego != 0)
        IColina = NULL, LColina = NULL ;
    if (modJuego != 1)
    {
        LProteger[0] = NULL;
        LProteger[1] = NULL;
    }
    //Crear paredes

        char aux[200];
        ifstream fichEntrada( nomPantalla.c_str() );
        fichEntrada >> aux;
        IMapa->Picture->LoadFromFile( aux );

        fichEntrada >> aux;
        paredes.push_back( TPared(10, 50, aux,false, this, 25,734)  );
        fichEntrada >> aux;
        paredes.push_back( TPared(10, 10, aux,false, this,1261,25)  );
        fichEntrada >> aux;
        paredes.push_back( TPared(1245, 50, aux,false, this,25,734)  );
        fichEntrada >> aux;
        paredes.push_back( TPared(10, 800, aux, false,this,1261,25)  );

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
            paredes.push_back( TPared( x, y, n,r,this, w, h) );
        }
        fichEntrada.close();
        

    for ( deque<TPared>::iterator i = paredes.begin(); i != paredes.end(); i++)
        cambiarRes( (*i).getImagen() );


    switch (modJuego)
    {
        case 0:{
                LColina->Parent = this;
                break;
               }
        case 1:{
                LProteger[0]->Parent = this;
                LProteger[1]->Parent = this;
               }
    }
    //Crear tios
    for(turno = 0; turno < 2; turno++)
        for(int i=0 ; i < 4 ;i++)
            robar();
    turno = random(2);
    turnoContrario = turno == 0 ? 1 : 0;
    robar();

    LMazo->Caption=IntToStr(numCartasMazo[turno]);

    BCambiarTurnoClick(this);

}
//---------------------------------------------------------------------------
void __fastcall TFJuego::BCerrarClick(TObject *Sender)
{
    Close();
}
void __fastcall TFJuego::barajear(int jugador)
{
    TCarta* carta;
    int num;
    for ( int i=0; i < 60; i++ )
    {
        num = random(60);
        carta = mazo[jugador][i];
        mazo[jugador][i] = mazo[jugador][num];
        mazo[jugador][num] = carta;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFJuego::robar()                                     // ROBAR -----------
{
    numCartasMazo[turno]--;
    LMazo->Caption =IntToStr(numCartasMazo[turno]);
    //Robar las cartas
    int j;
    for ( j=0 ; mano[turno][j] != NULL ; j++);    //Primera vacia
    int c=0;
    for ( ; mazo[turno][c] == NULL && c < 60 ; c++);   //Primera del mazo
    if ( c >= 60 )
    {
        ShowMessage("Te has quedado sin cartas, has perdido");
        ganar(turnoContrario);
    }
    mano[turno][j] = mazo[turno][c];   //Añadir a la mano
    mazo[turno][c] = NULL;

    numCartasMano[turno]++;
    actualizarMano();
}
void __fastcall TFJuego::ordenarMano()
{
    int j,i;
    do            //Ordenar las cartas al robar
    {
        for ( j=0 ; mano[turno][j] != NULL && j < 7; j++);    //Primera vacia

        for ( i=6 ; mano[turno][i] == NULL && i >= 0 ; i--  );       //Ultima ocupada

        if ( j < i )           //Intercambiar posiciones
        {
            mano[turno][j] = mano[turno][i];
            mano[turno][i] = NULL;
        }
    }
    while (!(j >= i));
}
void __fastcall TFJuego::actualizarMano()
{
    for (int i=0; i <7; i++)                                                                
        if  ( mano[turno][i] != NULL )
            {
                if ( turno == 0 || !IA || cheatIA)
                    manoI[i]->Picture->LoadFromFile( mano[turno][i]->getImagen() );
                else
                    manoI[i]->Picture->LoadFromFile( "imagenes//cartas//carta.bmp" );
                manoI[i]->Visible=true;
            }
        else
            manoI[i]->Visible=false;
}

void __fastcall TFJuego::desactivarHechizos()
{
    if (TArma::getArmaCrear()!=NULL)
        delete TArma::getArmaCrear();
    TArma::setArmaCrear( NULL );
    dosisDeSupervivencia = false;
    mitosis = false;
    iniciarDragon = false;
    if ( mano[turno][cartaSelec] != NULL && mano[turno][cartaSelec]->getTipo() != objeto )
        escuelaDeArmas = false;
    Screen->Cursor = crDefault;
}
void __fastcall TFJuego::BCambiarTurnoClick(TObject *Sender)            // CAMBIAR TURNO    ----------
{
    if ( numCartasMano[turno]== 7 )
        ShowMessage("Descarta de una carta");
    else
    {
        usaMana = false;
        desactivarHechizos();
        escuelaDeArmas= false;
        if (fuerzaReina > 0 )                 //Carta reina de los zombis
        {
            int a= 0;
            for (; TTio::getTio(turno,a) != NULL && TTio::getTio(turno,a)->getNombre() != "Reina de los zombis" ; a++ );
            if ( TTio::getTio(turno,a) != NULL )
                TTio::getTio(turno,a)->fuerza -= fuerzaReina;
            fuerzaReina = 0;
        }


        for (int d = 0; d < 2; d++)                       //Carta Bosque tenebroso
            if ( imagenBT[ d ] != NULL )
            {
                for ( int a = 0; a < 2; a++)
                    for( int b = 0; TTio::getTio(a, b) != NULL; b++)
                        if ( round(   sqrt(    sqr( imagenBT[d]->Left + imagenBT[d]->Width / 2 - ( TTio::getTio( a,b )->getImagen()->Left + TTio::getTio( a,b )->getImagen()->Width / 2))    +    sqr( imagenBT[d]->Top + imagenBT[d]->Height / 2 - ( TTio::getTio( a,b )->getImagen()->Top + TTio::getTio( a,b )->getImagen()->Height / 2)  )))   <   imagenBT[d]->Width / 2 + TTio::getTio( a,b )->getImagen()->Width / 2 )
                        {
                            TTio::getTio( a,b )->vida -= 10 * ( 100 -TTio::getTio( a,b )->resistenciaM ) / 100 ;
                            if ( TTio::getTio( a,b )->vida <= 0 )
                                destruirTio(a,b);
                        }
                turnosBT[d]++;
                if ( turnosBT[d] >= 6 )
                {
                    delete imagenBT[d];
                    imagenBT[d] = NULL;
                    int a=0;
                    for (; encantamiento[d][a]->getNombre() != "Bosque tenebroso"; a++ );

                    cementerio[d][ numCartasCem[d] ] = encantamiento[d][a];//Mandar la carta al cementerio;
                    encantamiento[d][a] = NULL;   //Borrarla de los encantamientos;

                    numCartasCem[d]++;//Sumar 1 a las cartas del cementerio;

                    if ( d == turno )
                    {
                        ICementerio->Picture->LoadFromFile( cementerio[d][numCartasCem[turno]]->getImagen() );  //Ver la ultima carta del cementerio;
                        ICementerio->Visible = true;
                    }
                    FEncantamientos->ordenarEncantamientos(d);
                }
            }

        for ( int j = 0;  j <= 20  && TTio::getTio(turno,j) != NULL ; j++)
            TTio::getTio(turno,j)->usaAccion();

        for(int j=0; j <= 20  &&  TTio::getTio(turno,j) != NULL;j++ )        //CartaZombiSiniestro
            if (zombiSiniestro[turno][j] > 0)
            {
                if (zombiSiniestro[turno][j] == 3)
                    destruirTio(turno,j);
                else
                    zombiSiniestro[turno][j]++;
            }

        turno = turno == 0 ? 1: 0;
        turnoContrario = turno == 1 ? 0: 1;
        LNombre->Font->Color = turno == 0 ? clBlue : clRed ;
        for ( int a = 0; a < 2 ; a++)          //Recorrer Todos los tios
            for ( int j = 0;  ( j < 20 ) && ( TTio::getTio(a,j) != NULL ); j++)
            {
                if ( TTio::getTio(a,j)->getNombre() == "Hombre lobo"  )
                {
                    TTio::getTio(a,j)->vida += 5 ;
                    if ( TTio::getTio(a,j)->vida > TTio::getTio(a,j)->vidaMax )
                        TTio::getTio(a,j)->vida= TTio::getTio(a,j)->vidaMax;
                }
                if ( TTio::getTio(a,j)->getNombre() == "Aparicion del mal" )        //CartaAparicionDelMal
                {
                    TTio::getTio(a,j)-> vida -= 30;
                    if ( TTio::getTio(a,j)->vida <= 0 )
                    {
                        destruirTio(a,j);
                        j--;
                    }
                }
            }

        for ( int j = 0;  j < 20  &&  TTio::getTio(turno,j) != NULL  ; j++ )
            TTio::getTio(turno,j)->iniciar();

        Pm[turno]=pmMax[turno];
        LPm-> Caption = IntToStr( Pm[turno] );
        //self.reproducir("SMasPM");
        LNombre->Caption = nombre[turno];
        ordenarMano();
        robar();

        LMazo->Caption = IntToStr( numCartasMazo[turno] );
        if ( numCartasCem[turno] > 0 )
        {
            ICementerio->Picture->LoadFromFile( cementerio[turno][numCartasCem[turno]-1]->getImagen());
            ICementerio->Visible=True;
        }
        else
            ICementerio->Visible = false;


        if ( modJuego == 0 )
        {
            int j = jugadorColina;
            jugadorColina= -1;
            for (int a = 0; a < 2 ; a++ )
                for(int b = 0; TTio::getTio(a,b) != NULL; b++ )
                    if (  round(   sqrt(    sqr( (TTio::getTio(a,b)->getImagen()->Left + TTio::getTio(a,b)->getImagen()->Width / 2.0) - (IColina->Left + IColina->Width / 2.0) )
                                +    sqr( (TTio::getTio(a,b)->getImagen()->Top + TTio::getTio(a,b)->getImagen()->Height / 2.0) - (IColina->Top + IColina->Width / 2.0) )
                                ) ) <=   ( IColina->Width / 2.0 /*+  TTio::getTio(a,b)->imagen->Width / 2.0*/) )
                        switch (jugadorColina) //Si hay una criatura de un jugador en la colina jugadorColina = jugador; si no hay nadie es 0, y si hya de los dos es 3
                        {
                            case -1: {jugadorColina = a;break;}
                            case 0: {if ( a == 1 )
                                        jugadorColina = 2;
                                    break;}
                            case 1: if ( a == 0 )
                                        jugadorColina = 2;
                        }
            if ( jugadorColina == 2 )
                jugadorColina = -1;

            if ( (jugadorColina == -1) || (jugadorColina != j) )
                turnosColina = 1;
            else
                if (jugadorColina == j )
                    turnosColina++;
            if ( jugadorColina == -1 )
                LColina->Caption= "Turnos - 0";
            else
                LColina->Caption= "Turnos - " + IntToStr( turnosColina );

            switch (jugadorColina)
            {
                case -1: {
                    LColina->Font->Color = clWindow;
                    IColina->Picture->LoadFromFile("imagenes\\varios\\colinaN.bmp");
                    break;
                }
                case 0: {
                    LColina->Font->Color = clAqua;
                    IColina->Picture->LoadFromFile("imagenes\\varios\\colinaA.bmp");
                    break;
                }
                case 1: {
                    LColina->Font->Color = clRed;
                    IColina->Picture->LoadFromFile("imagenes\\varios\\colinaR.bmp");
                }
            }

            if ( turnosColina == 6 )
                ganar(turno);
        }
        for ( int j = 0;  j < 20  && TTio::getTio(turnoContrario,j) != NULL ; j++) //Quita la sombra de las criaturas del turno contrario
            TTio::getTio(turnoContrario,j)->sombra->Visible = false;
        if ( turno == 1 && IA )
            activarIA();
    }
}
//---------------------------------------------------------------------------

void __fastcall TFJuego::descartarClick(TObject *Sender)       // DESCARTAR ---------
{
    descartar();
}

void __fastcall TFJuego::descartar()
{
    if (mano[turno][cartaSelec] != NULL)
    {
        cementerio[turno][numCartasCem[turno]] = mano[turno][cartaSelec];//Mandar la carta al cementerio;

        ICementerio->Picture->LoadFromFile(cementerio[turno][numCartasCem[turno]]->getImagen());//Ver la ultima carta del cementerio;
        numCartasCem[turno]++;//Sumar 1 a las cartas del cementerio;
        mano[turno][cartaSelec] = NULL;//Borrarla de la mano;

        numCartasMano[turno]--;//Restar el numero de cartas en mano;
        manoI[cartaSelec]->Visible=False;//Quitar de la mano la carta;

        ICementerio->Visible = True;
    }
}
void __fastcall TFJuego::verClick(TObject *Sender)          // VER CLICK --------------
{
    TFCarta::setNombreCarta ( mano[turno][cartaSelec]->getNombre() );
    TFCarta* FormVerCarta;
    FormVerCarta = new TFCarta(Application);
    FormVerCarta->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFJuego::IManoMouseDown(TObject *Sender,        //MANO CLICK -----
      TMouseButton Button, TShiftState Shift, int X, int Y)
{

    BCambiarTurno->Enabled = true;
    delete menuc;
    TPoint posicion;

    cartaSelec = -1;
    for( int i = 6; cartaSelec == -1; i-- )
        if (manoI[i] == static_cast<TImage*>(Sender))
            cartaSelec = i;
    desactivarHechizos();

    menuc = new TPopupMenu(this);

    TMenuItem* descartar = new TMenuItem(menuc);
    TMenuItem* usar = new TMenuItem(menuc);
    TMenuItem* ver =  new TMenuItem(menuc);

    menuc->Items->Add(usar);
    usar->Caption = "Usar";
    usar->OnClick = usarClick;

    menuc->Items->Add(ver);
    ver->Caption = "Ver";
    ver->OnClick = verClick;

    menuc->Items->Add(descartar);
    descartar->Caption = "Descartar";
    descartar->OnClick = descartarClick;

    GetCursorPos(&posicion);
    menuc->Popup( posicion.x , posicion.y);
}

//---------------------------------------------------------------------------
void __fastcall TFJuego::abrirCementerio(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    turnoC = turno;
    TFCementerio* FormVerCementerio;
    FormVerCementerio = new TFCementerio(Application);
    FormVerCementerio->ShowModal();
}

void __fastcall TFJuego::usarClick(TObject *Sender)          // USAR CARTA -----
{
    if (Pm[turno] >= mano[turno][cartaSelec]->getPm())
    {
        switch (mano[turno][cartaSelec]->getTipo())
        {
            case criatura:
            {
                mano[turno][cartaSelec]->usarHabilidad();

                if (TVariables::getCriaturaInvocar()->getNombre() == "Reina de los zombis")
                {
                    int a=0;
                    for (;TTio::getTio(turno,a) != NULL && TTio::getTio(turno,a)->getNombre() != "Reina de los zombis";a++);
                    if (TTio::getTio(turno,a) != NULL)
                    {
                        delete TVariables::getCriaturaInvocar()->getImagen();
                        delete TVariables::getCriaturaInvocar();
                        TVariables::setCriaturaInvocar( NULL );
                        ShowMessage("Solo puedes tener una Reina de los zombis en juego");
                    }
                }

                if (TVariables::getCriaturaInvocar() != NULL)
                {
                    cambiarRes( TVariables::getCriaturaInvocar()->getImagen());
                    area->Top= 32;
                    area->Height= 769;
                    area->Width= 150 + tierrasLejanas[turno];    //TierrasLejanas (carta especial)
					area->Left= turno == 0 ? 30 : 1280 - 30 - area->Width;
					
                    area->Visible= true;
                    this->BCambiarTurno->Enabled=false;
                    cambiarRes(area);
                    //se visualiza la imagen por primera vez en las coordenadas del raton
                    //si no parpadea en la eskina superior izkierda
                    TPoint posicion;
                    GetCursorPos(&posicion);
                    int x = posicion.x - Left;
                    int y = posicion.y - Top;
                    TVariables::getCriaturaInvocar()->getImagen()->Top = (y - TVariables::getCriaturaInvocar()->getImagen()->Height / 2);
                    TVariables::getCriaturaInvocar()->getImagen()->Left = (x - TVariables::getCriaturaInvocar()->getImagen()->Width / 2);
                    TVariables::getCriaturaInvocar()->getImagen()->Visible = true;
                    if ( !IA && turno == 1 || turno == 0 )
                        TimerCrearCriatura->Enabled= true;
                }
                break;
            }

            case objeto:
            {
                BCambiarTurno->Enabled = false;
                mano[turno][cartaSelec]->usarHabilidad();
                Screen->Cursor = crHandPoint;
                break;
            }
            case hechizo:
            {
                carta = mano[turno][cartaSelec];
                BCambiarTurno->Enabled=false;
                usaHechizo = false;
                carta->usarHabilidad();
                if ( usaHechizo )
                {
                    Pm[turno] -= carta->getPm();
                    LPm->Caption = IntToStr( Pm[turno] );
                    if ( carta == mano[turno][cartaSelec] )
                        descartar();
                }
                else
                    Screen->Cursor = crHandPoint;
                carta= NULL;
                break;
            }
            case encantamientos:
            {
                carta = mano[turno][cartaSelec];
                usaHechizo = false;
                carta->usarHabilidad();
                if ( usaHechizo )
                {
                    Pm[turno] -= carta->getPm();
                    LPm->Caption = IntToStr( Pm[turno] );
                    if ( carta == mano[turno][cartaSelec] )
                        usarEncantamiento();
                }
                break;
            }
            case mana:
            {
                if (!usaMana)
                {
                    usaMana = true;
                    pmMax[turno]++;
                    Pm[turno]++;
                    delete mano[turno][cartaSelec];
                    mano[turno][cartaSelec] = NULL;
                    manoI[cartaSelec]->Visible = false;
                    LPm->Caption = Pm[turno];
                    numCartasMano[turno]--;
                }
                else
                    ShowMessage("Solo puedes bajar un mana por turno");
            }

        }
    }
    else
        ShowMessage("PM Insuficiente");
}
//---------------------------------------------------------------------------



void __fastcall TFJuego::TimerCrearCriaturaTimer(TObject *Sender)        // TIMER CREAR CRIATURA ---------------
{
    TPoint posicion;
    GetCursorPos(&posicion);
    int x = posicion.x - Left;
    int y = posicion.y - Top;
    TVariables::getCriaturaInvocar()->getImagen()->Top = (y - TVariables::getCriaturaInvocar()->getImagen()->Height / 2);
    TVariables::getCriaturaInvocar()->getImagen()->Left = (x - TVariables::getCriaturaInvocar()->getImagen()->Width / 2);
    if ( HIWORD(GetKeyState(VK_LBUTTON)) )
        comprovarCrearCriatura(x,y);
}

bool __fastcall TFJuego::comprovarCrearCriatura(int x, int y)
{
        bool choca = false;

        //Si haces click dentro de una pared
        if ( ( area->Left > x - TVariables::getCriaturaInvocar()->getImagen()->Width / 2 ) || ( area->Left + area->Width < x + TVariables::getCriaturaInvocar()->getImagen()->Width / 2 ) || ( area->Top > y - TVariables::getCriaturaInvocar()->getImagen()->Height / 2 ) || (area->Top + area->Height < y + TVariables::getCriaturaInvocar()->getImagen()->Height / 2) )
            choca = true;
        for ( int a= 0; a < 2; a++ )         //Si choca con otro tio
            for ( int b = 0; TTio::getTio(a,b) != NULL && !choca; b++ )
            {
                int distX= (TTio::getTio(a,b)->getImagen()->Left + TTio::getTio(a,b)->getImagen()->Width / 2) - x;
                int distY= (TTio::getTio(a,b)->getImagen()->Top + TTio::getTio(a,b)->getImagen()->Height / 2) - y;
                int dist= round( sqrt( sqr(distX) + sqr(distY) ) );
                if ( dist < TVariables::getCriaturaInvocar()->getImagen()->Width / 2 + TTio::getTio(a,b)->getImagen()->Width / 2)
                    choca = true;
            }
        int r= TVariables::getCriaturaInvocar()->getImagen()->Width / 2;              //radio circunferencia
        for (deque <TPared>::iterator a = paredes.begin(); a != paredes.end() && (!choca); a++)     //Si choca con pared
        {
            int x1, y1;
            int x0, y0;
            int B, C ;

            if ( (*a).getImagen()->Left < x  && (*a).getImagen()->Left + (*a).getImagen()->Width > x && (*a).getImagen()->Top < y && (*a).getImagen()->Top + (*a).getImagen()->Height > y )
                choca= true;
            for ( int b=0; b < 2; b++)
            {

                y1 = (*a).getImagen()->Top + ( b == 0 ? 0 : (*a).getImagen()->Height );

                x0= x;      //cetro circunferencia
                y0= y;
/*  _a = 1  */  B = -2*x0;
                C = sqr(x0) + sqr(y1) - 2*y1*y0 + sqr(y0) - sqr(r);
                if ( sqr(B) - 4*C >=0 )
                {
                    x0= round( (-B + sqrt( sqr(B) - 4*C )) / 2 );     //puntos de corte de la recta con la circunferencia
                    if ( ( x0 > (*a).getImagen()->Left ) && ( x0 < (*a).getImagen()->Left + (*a).getImagen()->Width ) )
                        choca= true;
                    x0= round( (-B - sqrt( sqr(B) - 4*C )) / 2 );
                    if ( ( x0 > (*a).getImagen()->Left ) && ( x0 < (*a).getImagen()->Left + (*a).getImagen()->Width  ) )
                        choca= true;
                }
            }
            for ( int b=0 ; b < 2 ; b++)
            {

                x1 = (*a).getImagen()->Left + ( b == 0 ? 0 : (*a).getImagen()->Width );

                x0= x;      //cetro circunferencia
                y0= y;
                B= -2*y0;
                C= sqr(y0) + sqr(x1) - 2*x1*x0 + sqr(x0) - sqr(r);
                if ( sqr(B) - 4*C >=0 )
                {
                    y0= round( (-B + sqrt( sqr(B) - 4*C )) / 2 );     //puntos de corte de la recta con la circunferencia
                    if ( ( y0 > (*a).getImagen()->Top ) && ( y0 < (*a).getImagen()->Top + (*a).getImagen()->Height ) )
                        choca= true;
                    y0= round( (-B - sqrt( sqr(B) - 4*C )) / 2 );
                    if ( ( y0 > (*a).getImagen()->Top ) && ( y0 < (*a).getImagen()->Top + (*a).getImagen()->Height ) )
                        choca= true;
                }
            }
        }
        area->Visible = false;
        rango->Visible = false;
        if ( habilidadCriatura )  //carta mitosis
        {
            rango->Visible= false;
            if ( sqrt( sqr( TTio::getTio()->getImagen()->Left + TTio::getTio()->getImagen()->Width / 2 - x ) + sqr( TTio::getTio()->getImagen()->Top + TTio::getTio()->getImagen()->Height / 2 - y )) > TTio::getTio()->getImagen()->Width * 1.25 )
                choca= true;
        }

        if (choca)
        {
            delete TVariables::getCriaturaInvocar();
        }
        else
        {
            int i=0;                     //Crear Criatura
            for (;TTio::getTio(turno,i) != NULL;i++);

            TTio::setInvocarTio(turno,i,TVariables::getCriaturaInvocar());
            TVariables::setCriaturaInvocar( NULL );
            TTio::getTio(turno,i)->getImagen()->Left= x - TTio::getTio(turno,i)->getImagen()->Width / 2;
            TTio::getTio(turno,i)->getImagen()->Top= y - TTio::getTio(turno,i)->getImagen()->Height / 2;
            TTio::getTio(turno,i)->getImagen()->Visible= true;
            TTio::getTio(turno,i)->getImagen()->OnMouseDown = personajeClick;

            if ( mitosis )                              //carta mitosis
            {
                TTio::getTio()->vida = TTio::getTio()->vida / 2 + TTio::getTio()->vida % 2;
                TTio::getTio(turno,i)->vida = TTio::getTio(turno,i)->vida / 2 + TTio::getTio(turno,i)->vida % 2;
                TTio::getTio()->usaAccion();
                Pm[turno] = Pm[turno] - mano[turno][cartaSelec]->getPm();
                LPm->Caption = IntToStr( Pm[turno] );
                habilidadCriatura = true;
                descartar();                                //descartas la carta mitosis
            }

            if ( TTio::getTio(turno,i)->getNombre() == "Zombi" )
                TTio::getTio()->usaAccion();
            bool elfaExploradora = false;
            if ( mano[turno][cartaSelec]!= NULL && mano[turno][cartaSelec]->getNombre() == "Elfa exploradora" )
                elfaExploradora = true;
            if  (!habilidadCriatura) //Si la criatura no ha sido creada por alguna habilidad especial
            {
                Pm[turno] = Pm[turno] - mano[turno][cartaSelec]->getPm();
                LPm->Caption = IntToStr(Pm[turno]);

                TTio::getTio(turno,i)->setCarta(mano[turno][cartaSelec]);
                mano[turno][cartaSelec]=NULL;//Borrarla de la mano;

                numCartasMano[turno]=numCartasMano[turno]-1;//Restar el numero de cartas en mano;
                manoI[cartaSelec]->Visible = false;//Quitar de la mano la carta;
                if ( elfaExploradora )
                    robar();
            }
            else
            {
                TTio::getTio(turno,i)->setCarta(NULL);
                proteger(turno, i); //Modo de juego proteger
            }
            TTio::getTio(turno,i)->ponerSombra();
        }
        mitosis = false; //carta mitosis
        habilidadCriatura = false;
        BCambiarTurno->Enabled = true;
        TimerCrearCriatura->Enabled = false;
        return !choca;
}


void __fastcall TFJuego::personajeClick(TObject *Sender,        //CLICK UN TIO------------------
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    Screen->Cursor = crDefault;
    int j=0;
    bool enc = false;
    TPoint posicion;
    GetCursorPos(&posicion);
    int x1= posicion.x - Left;
    int y1= posicion.y - Top;

    for(; j < 2 && !enc;j++)
        for( int t=0; t<20 && !enc && TTio::getTio(j,t)!= NULL ;t++)
            if (TTio::getTio(j,t)->getImagen() == static_cast<TImage*>(Sender) )
            {          //si as hecho click dentro del circulo y no en una eskina
                if (  TTio::getTio(j,t)->getImagen()->Width / 2  >=   sqrt(  sqr( X-TTio::getTio(j,t)->getImagen()->Width / 2) + sqr(Y-TTio::getTio(j,t)->getImagen()->Height / 2) )  )
                {
                    //ShowMessage("tio " + IntToStr(j) + " " + IntToStr(t));
                    enc=true;
                    TTio::setTj(j);
                    TTio::setTt(t);
                }
				j=2; t = 20; //pa q salga de los fors
            }


    if ( enc )
    {
        TTio::destruirMenuj();
        TTio::setMenuj ( new TPopupMenu(this) );
        crearMenu( this, TTio::getTio() );
        TTio::getTio()->getImagen()->PopupMenu = TTio::getMenuj();
    }
    else
      //  if ( tjAnt != TTio::getTj() || ttAnt != TTio::getTt() )
            TTio::getTio()->getImagen()->PopupMenu = NULL;


    //Llamar a atacar cuerpo a cuerpo
    if (ataca &&  ((TTio::getTj() != tjAnt) || (TTio::getTt() != ttAnt) ))
            TTio::getTio(tjAnt, ttAnt)->atacarCuerpo();
    else
        BCambiarTurno->Enabled=false;

    ataca = false;

    //Llamar a atacar a distancia
    if (atacaDist &&  (TTio::getTj() != tjAnt || TTio::getTt() != ttAnt) )
        TTio::getTio(tjAnt, ttAnt)->atacarDistancia(x1,y1);
    else
        BCambiarTurno->Enabled =  true;

    atacaDist= false;

    rango->Visible= false;

    //UsarCarta Objeto     -------------------------
    if ( TArma::getArmaCrear() != NULL && enc)
    {
        if ( ( ( TTio::getTio()->armas[ TArma::getArmaCrear()->getTipo() ] || TArma::getArmaCrear()->getTipo() == 5 ) || escuelaDeArmas ) && TTio::getTio()->getArma(1) == NULL && ( TTio::getTio()->getArma(0) == NULL  || ( TTio::getTio()->getArma(0)->getDosManos() == false && TArma::getArmaCrear()->getDosManos() == false ) )  )
        {
            if (escuelaDeArmas &&  TTio::getTio()->armas[ TArma::getArmaCrear()->getTipo()] == false )
            {
                escuelaDeArmas= false;                       //Carta escuela de armas
                int a = cartaSelec;
                
                for (cartaSelec= 0; mano[turno][cartaSelec] == NULL ||  mano[turno][cartaSelec]->getNombre() != "Escuela de armas";cartaSelec++ );
                descartar();
                cartaSelec= a;
            }

            Pm[turno] -= mano[turno][cartaSelec]->getPm();
            LPm->Caption=IntToStr(Pm[turno]);

            if (TTio::getTio()->getArma(0) == NULL)
            {
                TTio::getTio()->setArma(0,TArma::getArmaCrear());
                TTio::getTio()->getArma(0)->setCarta(mano[turno][cartaSelec]);
            }
            else
            {
                TTio::getTio()->setArma(1,TArma::getArmaCrear());
                TTio::getTio()->getArma(1)->setCarta(mano[turno][cartaSelec]);
            }

            mano[turno][cartaSelec]=NULL;//Borrarla de la mano;

            numCartasMano[turno]--;//Restar el numero de cartas en mano;
            manoI[cartaSelec]->Visible=false;//Quitar de la mano la carta;

            descartar();
        }
        else
            ShowMessage("No puedes equipar este objeto a esta criatura");

        if (TArma::getArmaCrear()->getNombre() == "Mascara del diablo")                     //Carta MascaraDelDiablo
        {
            TTio::getTio()->vida /= 2;
            TTio::getTio()->vidaMax /= 2;
            TTio::getTio()->fuerza += 10;
            TTio::getTio()->setMov(round((TTio::getTio()->getMov() / TTio::getTio()->movMax) * ( TTio::getTio()->movMax + 40 )));
            TTio::getTio()->movMax += 40;
        }
        TArma::setArmaCrear(NULL);
    }

    if (dosisDeSupervivencia && enc)        //Carta DosisDeSupervivencia
    {
        ShowMessage("Pocion utilizada");
        TTio::getTio()->vida += 50;
        if (TTio::getTio()->vida  > TTio::getTio()->vidaMax )
            TTio::getTio()->vida= TTio::getTio()->vidaMax;
        dosisDeSupervivencia= false;
        descartar();
    }

    if ( mitosis && (TTio::getTio()->getAcciones() == 0) && enc )           //Carta mitosis
    {
        TVariables::setCriaturaInvocar( TTio::getTio()->copia() );

        invocarCerca( TTio::getTj(),TTio::getTt());
    }
    if ( iniciarDragon == true  )
    {
        if ( strstr( TTio::getTio()->tipo.c_str(), "dragon" ) != NULL )
        {
            TTio::getTio()->iniciar();
            TTio::getTio( tjAnt, ttAnt )->usaAccion();
        }
        iniciarDragon = false;
    }
}

void __fastcall TFJuego::crearRayoClick(TObject *Sender)     //Carta Brazaletes de tormenta
{
    if ( TTio::getTio()->getAcciones() == 0 )
    {
        rango->Height = TTio::getTio()->getArma(0)->getAlcance() * 2 + TTio::getTio()->getImagen()->Height;
        rango->Width  = TTio::getTio()->getArma(0)->getAlcance() * 2 + TTio::getTio()->getImagen()->Width;
        rango->Left   = TTio::getTio()->getImagen()->Left + TTio::getTio()->getImagen()->Width / 2 - rango->Width / 2;
        rango->Top    = TTio::getTio()->getImagen()->Top + TTio::getTio()->getImagen()->Height / 2 - rango->Height / 2;

        rango->Visible= true;

        tjAnt= TTio::getTj();
        ttAnt= TTio::getTt();
        atacaDist= true;
    }
}

void __fastcall TFJuego::nomClick(TObject *Sender)
{
    TFPersonaje* FormPersonaje;
    FormPersonaje = new TFPersonaje(Application);
    FormPersonaje->ShowModal();
}


void __fastcall  TFJuego::crearMenu(TObject *Sender, TTio* ti)                  //    CREAR MENU -------------------------------
{
    TMenuItem* nom;
    TMenuItem* move,*dist, *cuer;

    //Cartas-
    TMenuItem* crearZombi;   //Reina de los zombis
    TMenuItem* rayo ;          //Brazaletes de tormenta
    TMenuItem* generarMana ;          //Hada de la noche

    nom = new TMenuItem( TTio::getMenuj() );
    TTio::getMenuj()->Items->Add(nom);
    nom->Caption= ti->getNombre() + " " + IntToStr(ti->vida) + "/" + IntToStr(ti->vidaMax);
    nom->OnClick = nomClick;

    if ( ti->mover )
    {
        move = new TMenuItem(TTio::getMenuj());
        TTio::getMenuj()->Items->Add(move);
        move->Caption="Mover";
        move->OnClick = moverClick;
    }

    if ( ti->cuerpo || ti->distancia )
    {
        if ( ti->cuerpo )
        {
            cuer =new TMenuItem(TTio::getMenuj());
            TTio::getMenuj()->Items->Add(cuer);
            cuer->Caption="Cuerpo a cuerpo";
            if (ti->getNombre() == "Curandera" )
                cuer->Caption= "Curar";
            cuer->OnClick=cuerClick;
        }
        if ( ti->getArma(0) != NULL )
            if ( ti->getArma(0)->getDistancia()) //&& distancia )
            {
                dist= new TMenuItem(TTio::getMenuj());
                TTio::getMenuj()->Items->Add(dist);
                dist->Caption= "Distancia";
                dist->OnClick=distClick;
            }
    }

    if ( ti->getNombre() == "Reina de los zombis"  || strstr(ti->tipo.c_str(),"Zombie" ) != NULL )   //Carta Reina de los zombis
    {
        if ( ti->getNombre() == "Reina de los zombis" )
        {
            int c=0;

            for (int b = 0; TTio::getTio(turno, b) != NULL && c < 3 ; b++ )
                if ( TTio::getTio(turno, b)->getNombre() == "Zombi" )
                    c++;

            if (  c < 3 )
            {
                crearZombi= new TMenuItem(TTio::getMenuj());
                TTio::getMenuj()->Items->Add(crearZombi);
                crearZombi->Caption= "Crear zombi";
                crearZombi->OnClick = crearZombiClick;
            }
        }
        else
        {
            if ( fuerzaReina == 0 && TTio::getTj() == turno )
            {
                int a = 0;
                for (; TTio::getTio( turno,a ) != NULL  &&  TTio::getTio( turno, a)->getNombre() != "Reina de los zombis" ;a++);
                if ( TTio::getTio( turno, a ) != NULL )
                {
                    crearZombi = new TMenuItem( TTio::getMenuj() );
                    TTio::getMenuj()->Items->Add(crearZombi);
                    crearZombi->Caption= "Sacrificar";
                    crearZombi->OnClick= crearZombiClick ;
                }
            }
        }
    }
    if (  TTio::getTio()->getArma(0) != NULL  &&  TTio::getTio()->getArma(0)->getNombre() == "Brazaletes de tormenta" )
    {
        rayo= new TMenuItem( TTio::getMenuj() );
        TTio::getMenuj()->Items->Add(rayo);
        rayo->Caption = "Rayo";
        rayo->OnClick = crearRayoClick;
    }
    if ( ti->getNombre() == "Hada de la noche" )
    {
        generarMana = new TMenuItem( TTio::getMenuj() );
        TTio::getMenuj()->Items->Add(generarMana);
        generarMana->Caption = "Generar mana";
        generarMana->OnClick = generarManaClick;
    }
    if ( ti->getNombre() == "Mago del dragon" )
    {
        TMenuItem* iniciarDragon = new TMenuItem( TTio::getMenuj() );
        TTio::getMenuj()->Items->Add(iniciarDragon);
        iniciarDragon->Caption = "Inicializar dragon";
        iniciarDragon->OnClick = iniciarDragonClick;
    }
}

void __fastcall TFJuego::moverClick(TObject *Sender)                         //    MOVER     -------------------------
{
    if ( TTio::getTio()->getAcciones() == 0 )
    {
        rango->Height= TTio::getTio()->getMov() * 2 + TTio::getTio()->getImagen()->Height;
        rango->Width= TTio::getTio()->getMov()  * 2 + TTio::getTio()->getImagen()->Width;
        rango2->Height= TTio::getTio()->getMov()  * 2;
        rango2->Width= TTio::getTio()->getMov()  * 2;
        rango->Left= TTio::getTio()->getImagen()->Left + TTio::getTio()->getImagen()->Width / 2 - rango->Width / 2;
        rango->Top= TTio::getTio()->getImagen()->Top + TTio::getTio()->getImagen()->Height / 2 - rango->Height / 2;
        rango2->Left= TTio::getTio()->getImagen()->Left + TTio::getTio()->getImagen()->Width / 2 - rango2->Width / 2;
        rango2->Top= TTio::getTio()->getImagen()->Top + TTio::getTio()->getImagen()->Height / 2 - rango2->Height / 2;
        rango->Visible= true;
        rango2->Visible= true;
        tjAnt= TTio::getTj();
        ttAnt= TTio::getTt();
        puntero= new TImage(this);
        puntero->Picture->LoadFromFile("Imagenes\\raton\\mover.bmp");
        puntero->Stretch=true;
        puntero->Transparent=true;
        puntero->Height=TTio::getTio()->getImagen()->Height;
        puntero->Width=TTio::getTio()->getImagen()->Width;
        BCambiarTurno->Enabled=false;
        TimerMover->Enabled= true;
    }
}

void __fastcall TFJuego::cuerClick(TObject *Sender)
{
    if (TTio::getTio()->getAcciones()==0)
    {
        tjAnt= TTio::getTj();
        ttAnt= TTio::getTt();
        BCambiarTurno->Enabled=false;
        Screen->Cursor = crHandPoint;
        ataca= true;
        Screen->Cursor = crHandPoint;
    }
}

void __fastcall TFJuego::distClick(TObject *Sender)
{
    if (TTio::getTio()->getAcciones() == 0)
    {
        rango->Height=  TTio::getTio()->TTio::getArma(0)->getAlcance()  * TVariables::getResolucionY() * 2 + TTio::getTio()->getImagen()->Height;
        rango->Width= TTio::getTio()->TTio::getArma(0)->getAlcance() * TVariables::getResolucionX() * 2 + TTio::getTio()->getImagen()->Width ;
        rango->Height = (rango->Height + rango->Width )/2;
        rango->Width = rango->Height;
        rango->Left= TTio::getTio()->getImagen()->Left + TTio::getTio()->getImagen()->Width / 2 - rango->Width / 2;
        rango->Top= TTio::getTio()->getImagen()->Top + TTio::getTio()->getImagen()->Height / 2 - rango->Height / 2;

        rango->Visible= true;

        tjAnt= TTio::getTj();
        ttAnt= TTio::getTt();
        BCambiarTurno->Enabled=false;
        Screen->Cursor = crHandPoint;
        atacaDist= true;
    }
}

void __fastcall TFJuego::TimerMoverTimer(TObject *Sender)
{
    TPoint posicion;
    GetCursorPos(&posicion);
    int x = posicion.x - Left ;
    int y = posicion.y - Top ;
    puntero->Top = (y - TTio::getTio()->getImagen()->Height / 2);
    puntero->Left = (x - TTio::getTio()->getImagen()->Width / 2);
    puntero->Parent= this;
    if  ( HIWORD(GetKeyState(VK_LBUTTON)) != 0 )
    {
        delete puntero;
        TTio::getTio()->mueve( x, y);
        rango->Visible = false;
        rango2->Visible = false;
        BCambiarTurno->Enabled = true;
        proteger(TTio::getTj(),TTio::getTt()); //Modo de juego proteger
        TimerMover->Enabled= false;
    }
}
//---------------------------------------------------------------------------


void __fastcall TFJuego::destruirTio(int a,int b)           //  DESTRUIR TIO ------------------
{
    if ( heroes[turno] && mataCriaturaACriatura )       //Carta especial
    {
        TTio::getTio( tjAnt,ttAnt )->vidaMax = round( TTio::getTio( tjAnt,ttAnt )->vidaMax * 1.1 );
        TTio::getTio( tjAnt,ttAnt )->vida    = round( TTio::getTio( tjAnt,ttAnt )->vida    * 1.1 );
        TTio::getTio( tjAnt,ttAnt )->movMax  = round( TTio::getTio( tjAnt,ttAnt )->movMax  * 1.1 );
        TTio::getTio( tjAnt,ttAnt )->setMov((round( TTio::getTio( tjAnt,ttAnt )->getMov()     * 1.1 )));
        TTio::getTio( tjAnt,ttAnt )->fuerza  = round( TTio::getTio( tjAnt,ttAnt )->fuerza  * 1.1 );
    }

    zombiSiniestro[a][b]=0;

    if ( TTio::getTio( a,b )->getCarta() != NULL )
    {
        numCartasCem[a]++;//Sumar 1 a las cartas del cementerio;
        cementerio[a][numCartasCem[a]-1] = TTio::getTio(a,b)->getCarta() ;//Mandar la carta al cementerio;
        if ( turno == a )
        {
            ICementerio->Picture->LoadFromFile(cementerio[a][numCartasCem[a]-1]->getImagen() );//Ver la ultima carta del cementerio;
            ICementerio->Visible=True;
        }
    }

    while (TTio::getTio(a,b)->getArma(0) != NULL)
    {
        TFArma::setNumArma(0);
        FArma->destruirArma();
    }


    delete TTio::getTio( a,b );
    TTio::setNullTio( a,b);
    int b2= b;

    for ( ; TTio::getTio(a,b2+1) != NULL ; b2++ )
    {
        TTio::setTio( a, b2, TTio::getTio(a,b2+1) );
        TTio::setNullTio( a,b2+1);
        zombiSiniestro[a][b2]= zombiSiniestro[a][b2 +1];    // CartaEspecial;
        zombiSiniestro[a][b2 +1]=0;
    }
    mataCriaturaACriatura = false;
}

void __fastcall TFJuego::invocarCerca( int a, int b)
{
    if ( TVariables::getCriaturaInvocar()->getNombre() == "Reina de los zombis" )
    {
        int a = 0;
        for ( ; TTio::getTio( turno, a ) != NULL && TTio::getTio( turno, a )->getNombre() != "Reina de los zombis";a++ );
        if ( TTio::getTio( turno, a ) != NULL )
        {
            delete TVariables::getCriaturaInvocar()->getImagen();
            delete TVariables::getCriaturaInvocar();
            TVariables::setCriaturaInvocar(NULL);
            mitosis = false;
            ShowMessage("Solo puedes tener una Reina de los zombis en juego");
        }
    }
    if ( TVariables::getCriaturaInvocar() != NULL )
    {
        cambiarRes( TVariables::getCriaturaInvocar()->getImagen() );
        TVariables::getCriaturaInvocar()->getImagen()->Visible= false;

        area->Width = round( TTio::getTio( a, b )->getImagen()->Width * 3.5) ;
        area->Height = round( TTio::getTio( a, b )->getImagen()->Height * 3.5) ;

        area->Left = TTio::getTio( a, b )->getImagen()->Left - round( TTio::getTio( a, b )->getImagen()->Width * 1.25);
        area->Top = TTio::getTio( a, b )->getImagen()->Top - round( TTio::getTio( a, b )->getImagen()->Height * 1.25);

        rango->Width = round( TTio::getTio( a, b )->getImagen()->Width * 3.5);
        rango->Height = round( TTio::getTio( a, b )->getImagen()->Height * 3.5);
        rango->Visible = true;
        rango->Left = TTio::getTio( a, b )->getImagen()->Left - round( TTio::getTio( a, b )->getImagen()->Width * 1.25);
        rango->Top = TTio::getTio( a, b )->getImagen()->Top - round( TTio::getTio( a, b )->getImagen()->Height * 1.25);

        puntero = new TImage(this);
        puntero->Picture = TVariables::getCriaturaInvocar()->getImagen()->Picture;
        puntero->Stretch =true;
        puntero->Transparent =true;
        puntero->Height = TVariables::getCriaturaInvocar()->getImagen()->Height;
        puntero->Width = TVariables::getCriaturaInvocar()->getImagen()->Width;

        ShowMessage("Selecciona el lugar");
        BCambiarTurno->Enabled=false;
        TVariables::getCriaturaInvocar()->getImagen()->Visible = true;
        TimerCrearCriatura->Enabled= true;
    }
}

void __fastcall TFJuego::crearZombiClick(TObject *Sender)    //Carta Reina de los zombis

{
    if ( TTio::getTio()->getNombre() == "Reina de los zombis" )
    {
        if ( TTio::getTio()->getAcciones() == 0 )
        {
            habilidadCriatura = true;
            TVariables::setCriaturaInvocar ( TTio::crearZombi() );
            invocarCerca(TTio::getTj(),TTio::getTt());
        }
    }
    else
    {
        fuerzaReina = TTio::getTio()->fuerza;
        destruirTio( TTio::getTj(),TTio::getTt() );
        int a = 0;
        for ( ; TTio::getTio( turno, a )->getNombre() != "Reina de los zombis"; a++);
        TTio::getTio(turno,a)->fuerza += fuerzaReina;
    }
}

void __fastcall TFJuego::usarEncantamiento()
{
    int a = 0;
    for(; encantamiento[turno][a] != NULL ; a++);
    encantamiento[turno][a] = carta;
    mano[turno][cartaSelec] = NULL;//Borrarla de la mano
    numCartasMano[turno]--;//Restar el numero de cartas en mano;
    manoI[cartaSelec]->Visible = false;//Quitar de la mano la carta;
    carta = NULL;
}


void __fastcall TFJuego::BEncantClick(TObject *Sender)
{
    TVariables::setJugadorSelec(0, TFJuego::getTurno() );
    FEncantamientos = new TFEncantamientos(this);
    FEncantamientos->ShowModal();
}


//RECREAR  ---------
void __fastcall TFJuego::recrearImagen(TImage* & imagen)
{
    TImage* imag;
    imag = new TImage(this);
    imag->Picture = imagen->Picture;
    imag->Left = imagen->Left;
    imag->Top = imagen->Top;
    imag->Height = imagen->Height;
    imag->Width = imagen->Width;
    imag->Transparent = imagen->Transparent;
    imag->AutoSize = imagen->AutoSize;
    imag->Stretch = imagen->Stretch;
    imag->OnMouseDown = imagen->OnMouseDown;
    imag->Visible = imagen->Visible;
    imag->Parent = imagen->Parent;
    delete imagen;
    imagen = imag;
}
void __fastcall TFJuego::recrearShape(TShape* & s)
{
    TShape* shape;
    shape = new TShape(this);
    shape->Shape= s->Shape;
    shape->Visible=false;
    shape->Enabled=true;
    shape->Pen->Color = s->Pen->Color;
    shape->Pen->Mode = s->Pen->Mode;
    shape->Pen->Style = s->Pen->Style;
    shape->Pen->Width = s->Pen->Width;
    delete s;
    s = shape;
    s->Parent = this;
}

void __fastcall TFJuego::recrearLabel(TLabel* & l)
{
    TLabel* lab;
    lab = new TLabel(this);
    lab->Caption= l->Caption;
    lab->Left= l->Left;
    lab->Top= l->Top;
    lab->Font= l->Font;
    lab->Alignment= l->Alignment;
    lab->Width= l->Width;
    lab->Height= l->Height;
    lab->Transparent= l->Transparent;
    lab->AutoSize= l->AutoSize;
    delete l;;
    l = lab;
    l->Parent = this;
}

void __fastcall TFJuego::recrear()
{
    if ( IColina != NULL )
        recrearImagen( IColina );

    if (IProteger[0] != NULL)
    {
      recrearImagen(IProteger[0]);
      recrearImagen(IProteger[1]);
    }
    recrearShape( rango );
    recrearShape( rango2 );
    recrearShape( area );



    for ( int b = 0; b < 2; b++)
    {
        int a = 0;
        for ( ; TTio::getTio(b, a) != NULL; a++ )
            recrearImagen( TTio::getTio(b, a)->getImagen() );
    }

    for ( int b = 0; b < 7 ; b++)
    {
        recrearImagen( manoI[b] );
    }
    //recrear paredes
    for (deque <TPared>::iterator i = paredes.begin();i != paredes.end();i++)
        recrearImagen((*i).getImagen());
    if ( LColina != NULL )
    recrearLabel(LColina);
    recrearImagen(IMazo);
    recrearLabel(LPm);
    recrearLabel(LNombre);
    recrearLabel(LMazo);
    recrearImagen(ICementerio);
    
    if (LProteger[0] != NULL)
    {
        recrearLabel(LProteger[0]);
        recrearLabel(LProteger[1]);
    }

}

void __fastcall TFJuego::FormClose(TObject *Sender, TCloseAction &Action)
{
    paredes.clear();
    Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TFJuego::TimerVariosTimer(TObject *Sender)
{
    if (bosqueT )              //CartaBosqueTenebroso
    {
        TPoint posicion;
        GetCursorPos(&posicion);
        int x = posicion.x - Left;
        int y = posicion.y - Top ;
        imagenBT[turno]->Left= x - imagenBT[turno]->Width / 2;
        imagenBT[turno]->Top= y - imagenBT[turno]->Height / 2;
        imagenBT[turno]->Parent= this;

        if  ( HIWORD(GetKeyState(VK_LBUTTON)) != 0 )
        {
            usaHechizo= true;
            bosqueT= false;
            carta= mano[turno][cartaSelec];
            usarEncantamiento();
            BCambiarTurno->Enabled= true;
            Pm[turno]-=3;
            LPm->Caption = Pm[turno];
            TimerVarios->Enabled= false;
        }
    }
}
//---------------------------------------------------------------------------


bool __fastcall TFJuego::cercano(TTio* t)
    {
        bool result=false;
        for ( int i=0; TTio::getTio(turnoContrario,i) != NULL && !result; i++ )
            if ((   sqrt(    sqr((TTio::getTio(turnoContrario,i)->getImagen()->Left + TTio::getTio(turnoContrario,i)->getImagen()->Width / 2) - (t->getImagen()->Left + t->getImagen()->Width / 2))    +    sqr((TTio::getTio(turnoContrario,i)->getImagen()->Top + TTio::getTio(turnoContrario,i)->getImagen()->Height / 2)  - (t->getImagen()->Top + t->getImagen()->Height / 2)  )))   <= (15 + TTio::getTio(turnoContrario,i)->getImagen()->Width / 2 + t->getImagen()->Width / 2))
                result = true;
        return result;
    }

void __fastcall TFJuego::proteger(int j,int t)
{
    //Comprobar si hay algun tio en el area contraria
    if (modJuego == 1)
    {
        if ( sqrt(
                    sqr( TTio::getTio(j,t)->getImagen()->Left + TTio::getTio(j,t)->getImagen()->Width /2 - ( turnoContrario == 0? IProteger[0]->Left:IProteger[1]->Left + IProteger[1]->Width ) ) +
                    sqr( TTio::getTio(j,t)->getImagen()->Top + TTio::getTio(j,t)->getImagen()->Height /2 - (IProteger[0]->Top + IProteger[0]->Height/2)  )
            ) <=  IProteger[0]->Width )

            {
                VProteger[turnoContrario]-= TTio::getTio(j,t)->fuerza;
                LProteger[turnoContrario]->Caption = "Vida: " + IntToStr(VProteger[turnoContrario]);
                destruirTio(j,t);
                if (VProteger[turnoContrario] <= 0)
                    ganar(turno);
            }
    }
}


void __fastcall TFJuego::BEncantKeyPress(TObject *Sender, char &Key)
{
    switch ( cheat )
    {
        case 0: {if ( Key == 'A' || Key == 'a' ) cheat++; else cheat = 0;break;}
        case 1: {if ( Key == 'B' || Key == 'b' ) cheat++; else cheat = 0; break;}
        case 2: {if ( Key == 'C' || Key == 'c' ) {Pm[turno] += 10; LPm->Caption = Pm[turno]; cheatIA = true;} cheat = 0;  break;}
    }
}
//---------------------------------------------------------------------------
void __fastcall TFJuego::ganar(int j)
{
    TimerMover->Enabled= false; //sino da fallo en el proteger
    ShowMessage("Ha ganado el jugador " + nombre[j]);
    Close();
}


void __fastcall TFJuego::generarManaClick(TObject *Sender)
{
    if ( TTio::getTio()->getAcciones() == 0 )
    {
        Pm[turno]++;
        TTio::getTio()->usaAccion();
        LPm->Caption = IntToStr( Pm[turno] );
    }
}
void __fastcall TFJuego::iniciarDragonClick(TObject *Sender)
{
    if ( TTio::getTio()->getAcciones() == 0 )
    {
        iniciarDragon = true;
        tjAnt = TTio::getTj();
        ttAnt = TTio::getTt();
    }
}




void __fastcall TFJuego::activarIA()
{
    //bajar mana
    for ( int a = 0, enc = 0; mano[turno][a] != NULL && a < 7 && !enc; a++)
        if ( mano[turno][a]->getNombre() == "Mana" )
        {
            ShowMessage("Bajo mana");
            cartaSelec = a;
            usarClick(NULL);
            enc = 1; //true
        }
    //-------
    ordenarMano();
    actualizarMano();
    //bajar criatura(s)
    for ( int a = 0, enc = 0; mano[turno][a] != NULL && a < 7 && !enc; a++)
        if ( mano[turno][a]->getTipo() == criatura )
            if ( mano[turno][a]->getPm() <= Pm[turno] )
            {
                ShowMessage("Bajo la criatura " + mano[turno][a]->getNombre() );
                cartaSelec = a;

                for( int b = 0;/* mano[turno][a]!= NULL */; b++)
                {
                    int variacion = (b%2?1:-1) * b*5;
                    usarClick(NULL);
                    TVariables::getCriaturaInvocar()->getImagen()->Left = area->Left ;
                    int x1 = TVariables::getCriaturaInvocar()->getImagen()->Left + TVariables::getCriaturaInvocar()->getImagen()->Width / 2;
                    TVariables::getCriaturaInvocar()->getImagen()->Top = area->Top + area->Height / 2 + variacion;
                    int y1 = TVariables::getCriaturaInvocar()->getImagen()->Top + TVariables::getCriaturaInvocar()->getImagen()->Height / 2;

                    if ( comprovarCrearCriatura( x1, y1 ) )
                        break;
                }
                ordenarMano();
                actualizarMano();
                a = 0;
            }


    int signo = random(2) == 0 ? -1 : 1; // una criatura al eskivaar a otra la eskivara en ... pa arriba o pa abajo
    //Mover pa atacar-----
    bool repetir = true;
    while ( repetir )
    {
        repetir = false;
        //si hay algun enemigo cerca

        for( int a = 0; TTio::getTio(turno,a) && !repetir ; a++)
            for( int b = 0; TTio::getTio(turnoContrario,b) && !repetir ; b++)
                if ( TTio::getTio(turno,a)->getAcciones() == 0 )
                {
                    int dist= sqrt(
                        sqr( TTio::getTio(turno,a)->getImagen()->Left + TTio::getTio(turno,a)->getImagen()->Width / 2 - (TTio::getTio(turnoContrario,b)->getImagen()->Left + TTio::getTio(turnoContrario,b)->getImagen()->Width / 2) )  +
                        sqr ( TTio::getTio(turno,a)->getImagen()->Top + TTio::getTio(turno,a)->getImagen()->Height / 2 - (TTio::getTio(turnoContrario,b)->getImagen()->Top + TTio::getTio(turnoContrario,b)->getImagen()->Height/2) )
                        ) - TTio::getTio(turnoContrario,b)->getImagen()->Width / 2  ;
                    //    ShowMessage( IntToStr(turno) + " " + IntToStr(a) + " tiene a " + IntToStr(turnoContrario)+ " " + IntToStr(b) + " a una distancia de " + IntToStr( dist) );
                    if ( dist < TTio::getTio(turno,a)->getMov() )
                    {
                        int x, y;
                        if ( TTio::getTio(turno,a)->getImagen()->Top + TTio::getTio(turno,a)->getImagen()->Height / 2 < TTio::getTio(turnoContrario,b)->getImagen()->Top + TTio::getTio(turnoContrario,b)->getImagen()->Height / 2 )
                        //si esta mas arriba
                            y = TTio::getTio(turnoContrario,b)->getImagen()->Top - TTio::getTio(turno,a)->getImagen()->Height/2 * 0.7 + TTio::getTio(turnoContrario,b)->getImagen()->Height/2*0.3 - 10;
                        else
                        //si esta mas abajo
                            y = TTio::getTio(turnoContrario,b)->getImagen()->Top + TTio::getTio(turnoContrario,b)->getImagen()->Height + TTio::getTio(turno,a)->getImagen()->Height/2 * 0.7 - TTio::getTio(turnoContrario,b)->getImagen()->Height/2*0.3 + 10;
                        if ( TTio::getTio(turno,a)->getImagen()->Left + TTio::getTio(turno,a)->getImagen()->Width / 2 < TTio::getTio(turnoContrario,b)->getImagen()->Left + TTio::getTio(turnoContrario,b)->getImagen()->Width / 2 )
                        //si esta mas a la izkierda
                            x = TTio::getTio(turnoContrario,b)->getImagen()->Left - TTio::getTio(turno,a)->getImagen()->Width/2 * 0.7 + TTio::getTio(turnoContrario,b)->getImagen()->Width/2*0.3 - 10;
                        else
                        //si esta mas a la derecha
                            x = TTio::getTio(turnoContrario,b)->getImagen()->Left + TTio::getTio(turnoContrario,b)->getImagen()->Width + TTio::getTio(turno,a)->getImagen()->Width/2*0.7 - TTio::getTio(turnoContrario,b)->getImagen()->Width/2*0.3 + 10;



                        if ( TTio::getTio(turno,a)->mueve( x , y ) )
                        {
                          //  ShowMessage("Muevo la criatura " +TTio::getTio(turno,a)->getNombre() );
                            repetir = true;
                            proteger( turno,a);
                        }
                    }
                }
        atacarCuerpoIA();



        //mover
        for( int a = 0; TTio::getTio(turno,a) && !repetir ; a++)
            if ( TTio::getTio(turno,a)->getAcciones() == 0 )
            {
                                                    //intenta mover pa la izkierda
                if ( TTio::getTio(turno,a)->getMov() >= 5 && !repetir)
                {
                    int x = TTio::getTio(turno,a)->getImagen()->Left + TTio::getTio(turno,a)->getImagen()->Width/2 - 5;
                    int y = TTio::getTio(turno,a)->getImagen()->Top + TTio::getTio(turno,a)->getImagen()->Height / 2;
                    if ( TTio::getTio(turno,a)->mueve( x , y ) )
                    {
                     //   ShowMessage("Muevo la criatura " +TTio::getTio(turno,a)->getNombre() );
                        repetir = true;
                        proteger( turno,a);
                    }

                }
                if ( TTio::getTio(turno,a)->getMov()  >= 5 && !repetir)  //no a podido mover
                {                                                 //intenta mover pa arriba o pa abajo
                        int x = TTio::getTio(turno,a)->getImagen()->Left + TTio::getTio(turno,a)->getImagen()->Width/2 ;
                        int y = TTio::getTio(turno,a)->getImagen()->Top + TTio::getTio(turno,a)->getImagen()->Height / 2 + 5 * signo;
                        if ( TTio::getTio(turno,a)->mueve( x , y ) )
                        {
                        //   ShowMessage("Muevo la criatura " +TTio::getTio(turno,a)->getNombre() );
                            repetir = true;
                            proteger( turno,a);
                        }
                        else
                        {      //lo intenta pal otro lado
                            int i = TTio::getTio(turno,a)->getMov()  > 40 ? 40 : TTio::getTio(turno,a)->getMov() ;
                            signo = signo==-1? 1 : -1;
                            int y = TTio::getTio(turno,a)->getImagen()->Top + TTio::getTio(turno,a)->getImagen()->Height / 2 + i * signo;
                            if ( TTio::getTio(turno,a)->mueve( x , y ) )
                            {
                                repetir = true;
                                proteger( turno,a);
                            }
                        }
                }
            }
        atacarCuerpoIA();
    }
    if ( numCartasMano[turno] == 7 )
    {
        cartaSelec = 0; //descartará la carta de la que mas mana baje
        for ( int a = 1; a < 7; a++)
            cartaSelec = mano[turno][cartaSelec]->getPm() >  mano[turno][a]->getPm() ? cartaSelec : a;
        ShowMessage("Descarto carta " + mano[turno][cartaSelec]->getNombre() );
        descartar();
    }
    ShowMessage("Por ahora termino mi turno");
    BCambiarTurnoClick(NULL);
    
}

void __fastcall TFJuego::atacarCuerpoIA()
{
    for( int a = 0; TTio::getTio(turno,a) ; a++)
        for ( int i=0; TTio::getTio(turnoContrario,i) != NULL ; i++ )
            if (    sqrt(
                    sqr((TTio::getTio(turnoContrario,i)->getImagen()->Left + TTio::getTio(turnoContrario,i)->getImagen()->Width / 2) - (TTio::getTio(turno,a)->getImagen()->Left + TTio::getTio(turno,a)->getImagen()->Width / 2))    +
                    sqr((TTio::getTio(turnoContrario,i)->getImagen()->Top + TTio::getTio(turnoContrario,i)->getImagen()->Height / 2)  - (TTio::getTio(turno,a)->getImagen()->Top + TTio::getTio(turno,a)->getImagen()->Height / 2))
                    )   <= 15 + TTio::getTio(turnoContrario,i)->getImagen()->Width / 2 + TTio::getTio(turno,a)->getImagen()->Width / 2 )
            {
                //ataca
                if ( TTio::getTio(turno,a)->getAcciones() == 0 )
                {
                    TTio::setTj( turnoContrario );
                    TTio::setTt( i );
                    tjAnt = turno;
                    ttAnt = a;
                    TTio::getTio(turno,a)->atacarCuerpo();
                }
            }
}






