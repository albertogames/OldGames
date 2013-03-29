
#include "UPersonaje.h"
#include "math.h"
#include "FormJuego.h"

TPopupMenu* TTio::menuj;
int TTio::tj;
int TTio::tt;
TTio* TTio::tio[2][20];

float sqr(float f)
{
    return f * f;
}

bool TTio::mueve(int x,int y)       //    MOVER -------------------
{
    bool choca = false;

    float x0;
    float y0;

    float x3;
    float y3 =0;
    
    float x4=0;
    float y4;
    float x1= imagen->Left + imagen->Width / 2;
    float y1= imagen->Top + imagen->Height / 2;
    float x2= x;
    float y2= y;

    if ( x1 == x2 )
        x1++;
    float a = (y2 - y1) / (x2 - x1);
    float b= -a*x1 + y1;                          //  ec. recta  y = Ax + B

    float paredX;
    float paredY;
    float r;
    int eskina;        //la eskina q no hay q comprovar de la pared  (de 1 a 4 )

    float A;
    float B;
    float C;
    for (deque <TPared>::iterator i = TFJuego::getParedes().begin() ; i != TFJuego::getParedes().end() && !choca; i++)
    {

        if ( x2 - x1 >= 0 )
            paredX = (*i).getImagen()->Left
            - imagen->Width / 2;
        else
            paredX = (*i).getImagen()->Left + (*i).getImagen()->Width
            + imagen->Width / 2;

        if ( y2 - y1 >= 0 )
            paredY= (*i).getImagen()->Top - imagen->Height / 2;
        else
            paredY= (*i).getImagen()->Top + (*i).getImagen()->Height + imagen->Height / 2;

        y3 =  a*paredX + b ;            //X3, Y3, corte en el eje Y
        x3 = paredX;

        if ( (y1 != y2) )   // recta no horizontal
            x4 =  ( paredY - b ) /a ;       //X4, Y4, corte en el eje X

        y4= paredY;

        //---------------
        if ( ( y3 >= (*i).getImagen()->Top) && ( y3 <= (*i).getImagen()->Top + (*i).getImagen()->Height) )   //la recta corta en la pared en x3, y3
            if ( sqrt( sqr(x2-x1) + sqr(y2-y1) ) >= sqrt( sqr(x3-x1) + sqr(y3-y1) ) )         // Distancia de 1 a 2 > distancia entre 1 y 3
                if ( sqrt( sqr(x2-x1) + sqr(y2-y1) ) >= sqrt( sqr(x3-x2) + sqr(y3-y2) ) )     // Distancia de 1 a 2 > distancia entre 2 y 3
                    choca= true;
        if (  (y1 != y2) && ( x4 >= (*i).getImagen()->Left) && ( x4 <= (*i).getImagen()->Left + (*i).getImagen()->Width) )   //la recta corta en la pared en x4, y4
            if ( sqrt( sqr(x2-x1) + sqr(y2-y1) ) >= sqrt( sqr(x4-x1) + sqr(y4-y1) ) )
                if ( sqrt( sqr(x2-x1) + sqr(y2-y1) ) >= sqrt( sqr(x4-x2) + sqr(y4-y2) ) )
                    choca= true;

        r= imagen->Width / 2;
        if ( (x2 >= x1) && (y2 >= y1) )
            eskina=4;
        else
            if ( x2 >= x1 )
                eskina=3;
            else
                if ( y2 >=y1 )
                    eskina=2;
                else
                    eskina=1;

        for ( int k=1; k <=3;k++ )
        {
            switch ( k )
            {
                case 1:
                {                      //centro circunferencia
                    if ( eskina != 1 )
                    {
                        x0 = (*i).getImagen()->Left;
                        y0 = (*i).getImagen()->Top;
                    }
                    else
                    {
                        x0 = (*i).getImagen()->Left + (*i).getImagen()->Width ;
                        y0 = (*i).getImagen()->Top + (*i).getImagen()->Height;
                    }
                    break;
                }
                case 2:
                {
                    if ( eskina != 2 )
                    {
                        x0= (*i).getImagen()->Left;
                        y0= (*i).getImagen()->Top + (*i).getImagen()->Height;
                    }
                    else
                    {
                        x0= (*i).getImagen()->Left + (*i).getImagen()->Width ;
                        y0= (*i).getImagen()->Top + (*i).getImagen()->Height;
                    }
                    break;
                }
                case 3:
                {
                    if ( eskina != 3 )
                    {
                        x0= (*i).getImagen()->Left + (*i).getImagen()->Width ;
                        y0= (*i).getImagen()->Top;
                    }
                    else
                    {
                        x0= (*i).getImagen()->Left + (*i).getImagen()->Width ;
                        y0= (*i).getImagen()->Top + (*i).getImagen()->Height;
                    }
                }
            }
            A= sqr(a)+1;                                    //radio circunferencia
            B= -2*x0 + 2*a*(b-y0);
            C= sqr(x0) + sqr(b-y0) - sqr(r);
            if ( sqr(B) - 4*A*C >=0 )   //si exite algun punto comun entre la recta y la circunferencia
            {
                x0= ( (-B + sqrt( sqr(B) - 4*A*C )) / ( 2*A) );     //puntos de corte de la recta con la circunferencia
                y0= (a*x0 + b);
                if ( ( (x1 <= x2) && (y1 <= y2) && (x1 <= x0) && (x2 >= x0) && (y1 <= y0) && (y2 >= y0) ) || ( (x1 <= x2) && (y1 >= y2) && (x1 <= x0) && (x2 >= x0) && (y1 >= y0) && (y2 <= y0) ) || ( (x1 >= x2) && (y1 <= y2) && (x1 >= x0) && (x2 <= x0) && (y1 <= y0) && (y2 >= y0) ) || ( (x1 >= x2) && (y1 >= y2) && (x1 >= x0) && (x2 <= x0) && (y1 >= y0) && (y2 <= y0) ) )
                    choca= true;
                x0= ( (-B - sqrt( sqr(B) - 4*A*C )) / ( 2*A) );     //puntos de corte de la recta con la circunferencia
                y0= (a*x0 + b);
                if ( ( (x1 <= x2) && (y1 <= y2) && (x1 <= x0) && (x2 >= x0) && (y1 <= y0) && (y2 >= y0) ) || ( (x1 <= x2) && (y1 >= y2) && (x1 <= x0) && (x2 >= x0) && (y1 >= y0) && (y2 <= y0) ) || ( (x1 >= x2) && (y1 <= y2) && (x1 >= x0) && (x2 <= x0) && (y1 <= y0) && (y2 >= y0) ) || ( (x1 >= x2) && (y1 >= y2) && (x1 >= x0) && (x2 <= x0) && (y1 >= y0) && (y2 <= y0) ) )
                    choca= true;
            }
        }
    }

    int distX;
    int distY;
    int dist;
    for ( int i2= 0; i2 < 2; i2++ )
        for ( int i = 0; tio[i2][i] != NULL && !choca;i++ )
            if ( tio[i2][i] != this )
            {
                distX = (tio[i2][i]->imagen->Left + tio[i2][i]->imagen->Width / 2) - x;
                distY = (tio[i2][i]->imagen->Top + tio[i2][i]->imagen->Height / 2) - y;
                dist = round( sqrt( sqr(distX) + sqr(distY) ) );
                if ( dist < imagen->Width / 2 + tio[i2][i]->imagen->Width / 2 + 2 )
                    choca= true;
                x0= (tio[i2][i]->imagen->Left + tio[i2][i]->imagen->Width / 2);        //cetro circunferencia
                y0= (tio[i2][i]->imagen->Top + tio[i2][i]->imagen->Height / 2);
                r= tio[i2][i]->imagen->Width / 2 + imagen->Width / 2;              //radio circunferencia
                A = sqr(a)+1;
                B = -2*x0 + 2*a*(b-y0);
                C = sqr(x0) + sqr(b-y0) - sqr(r);
                if ( sqr(B) - 4*A*C >=0 )   //si exite algun punto común entre la recta y la circunferencia
                {
                    x0= ( (-B + sqrt( sqr(B) - 4*A*C )) / ( 2*A) );     //puntos de corte de la recta con la circunferencia
                    y0= (a*x0 + b);
                    if ( ( (x1 <= x2) && (y1 <= y2) && (x1 <= x0) && (x2 >= x0) && (y1 <= y0) && (y2 >= y0) ) || ( (x1 <= x2) && (y1 >= y2) && (x1 <= x0) && (x2 >= x0) && (y1 >= y0) && (y2 <= y0) ) || ( (x1 >= x2) && (y1 <= y2) && (x1 >= x0) && (x2 <= x0) && (y1 <= y0) && (y2 >= y0) ) || ( (x1 >= x2) && (y1 >= y2) && (x1 >= x0) && (x2 <= x0) && (y1 >= y0) && (y2 <= y0) ) )
                        choca= true;
                    x0= ( (-B - sqrt( sqr(B) - 4*A*C )) / ( 2*A) );     //puntos de corte de la recta con la circunferencia
                    y0= (a*x0 + b);
                    if ( ( (x1 <= x2) && (y1 <= y2) && (x1 <= x0) && (x2 >= x0) && (y1 <= y0) && (y2 >= y0) ) || ( (x1 <= x2) && (y1 >= y2) && (x1 <= x0) && (x2 >= x0) && (y1 >= y0) && (y2 <= y0) ) || ( (x1 >= x2) && (y1 <= y2) && (x1 >= x0) && (x2 <= x0) && (y1 <= y0) && (y2 >= y0) ) || ( (x1 >= x2) && (y1 >= y2) && (x1 >= x0) && (x2 <= x0) && (y1 >= y0) && (y2 <= y0) ) )
                        choca= true;
                }
            }

    distX= x - ( imagen->Left + imagen->Width / 2);
    distY= y - (imagen->Top + imagen->Height / 2);
    dist= ( sqrt( sqr(distX) + sqr(distY) ) );
    if ( dist <= mov && !choca )
    {
        mov -= dist;
        imagen->Left = x - imagen->Width / 2;
        imagen->Top = y - imagen->Height / 2;
        ponerSombra();
    }
    return !choca;
}
void TTio::atacarCuerpo()
{
    if (tj == TFJuego::getTjAnt() && nombre != "Curandera" )
        ShowMessage("No puedes atacar a una criatura tuya");
    else
    {
        int dist =  (sqrt(  sqr( ( tio[tj][tt]->imagen->Left + tio[tj][tt]->imagen->Width / 2 ) - ( imagen->Left + imagen->Width / 2 ) ) + sqr ( ( tio[tj][tt]->imagen->Top + tio[tj][tt]->imagen->Height / 2 ) - ( imagen->Top + imagen->Height / 2 ) ) )) - imagen->Width / 2 - tio[tj][tt]->imagen->Width / 2  ;


        int f = 0 ;
        if  (arma1 != NULL && arma1->getCuerpoACuerpo())
        {
            f= arma1->getFuerza();
            if (arma2 != NULL && arma2->getCuerpoACuerpo())
                f+= arma2->getFuerza();
        }
        if (dist <= 15)
        {
            if ( nombre == "Curandera" ) //carta curandera
            {
                tio[tj][tt]->vida += 20;
                tio[tj][tt]->vida = tio[tj][tt]->vida < tio[tj][tt]->vidaMax? tio[tj][tt]->vida : tio[tj][tt]->vidaMax;
                ShowMessage("Vida: " + IntToStr(tio[tj][tt]->vida) + "( +20)");
            }
            else
                tio[tj][tt]->vida -=round((fuerza + f) * (1 - tio[tj][tt]->resistenciaC / 100.0 ) );


            if (tio[tj][tt]->vida <= 0)
            {
                FJuego->setMataCriaturaACriatura(true);
                FJuego->destruirTio(tj,tt);
                FJuego->setTioMataTio(true);            //CartaEspecial
            }
            else
            {
                if (nombre != "Curandera")
                  ShowMessage("Fuerza: " + IntToStr(fuerza + f) + "\nDefensa: " + IntToStr(tio[tj][tt]->resistenciaC) + "\nDaño: " + IntToStr(round((fuerza + f) * (1 - tio[tj][tt]->resistenciaC / 100.0))) + "\nVida: " + IntToStr(tio[tj][tt]->vida));
                if (nombre == "Zombi siniestro")                  // CataEspecial
                    FJuego->incZombiSiniestro(tj,tt);
            }
            usaAccion();
        }
        else
            ShowMessage("Estas demasiado lejos");
    }
    FJuego->BCambiarTurno->Enabled=true;
}

void TTio::atacarDistancia(int x2,int y2)
{

    if (tj == TFJuego::getTjAnt())
        ShowMessage("No puedes atacar a una criatura tuya");
    else
    {
        bool choca = false;
        float x3;
        float y3=0;
        float x4=0;
        float y4;
        float x1= imagen->Left + imagen->Width / 2;
        float y1= imagen->Top + imagen->Height / 2;
        if ( x1 == x2 )
            x1++;
        float a = (y2 - y1) / (x2 - x1);
        float b = -a*x1 + y1;                            //  ec. recta  y = Ax + B

        int paredX,paredY;
        for (deque <TPared>::iterator i = TFJuego::getParedes().begin() ; i != TFJuego::getParedes().end() && !choca; i++ )
        {
        if ((*i).getRio() == false)
        {
            if ( x2 - x1 >= 0 )
                paredX= (*i).getImagen()->Left;
            else
                paredX= (*i).getImagen()->Left + (*i).getImagen()->Width;

            if (y2 - y1 >= 0 )
                paredY= (*i).getImagen()->Top;
            else
                paredY= (*i).getImagen()->Top + (*i).getImagen()->Height;

            y3 = round( a*paredX + b );            //X3, Y3, corte en el eje Y
            x3 = paredX;

            if (y1 != y2)   // recta no horizontal
                x4 =  ( paredY - b ) / a;       //X4, Y4, corte en el eje X

            y4= paredY;

            if ((( y3 >= (*i).getImagen()->Top) &&
                ( y3 <= (*i).getImagen()->Top + (*i).getImagen()->Height) &&
                ( sqrt( sqr(x2-x1) + sqr(y2-y1) ) >= sqrt( sqr(x3-x1) + sqr(y3-y1) ) ) &&
                ( sqrt( sqr(x2-x1) + sqr(y2-y1) ) >= sqrt( sqr(x3-x2) + sqr(y3-y2) ) ) )
                ||
                ((y1 != y2) &&
                ( x4 >= (*i).getImagen()->Left) &&
                ( x4 <= (*i).getImagen()->Left + (*i).getImagen()->Width ) &&
                ( sqrt( sqr(x2-x1) + sqr(y2-y1) ) >= sqrt( sqr(x4-x1) + sqr(y4-y1) ) ) &&
                ( sqrt( sqr(x2-x1) + sqr(y2-y1) ) >= sqrt( sqr(x4-x2) + sqr(y4-y2) ) ) ))

                    choca= true;
        }
        }

        for(int  i2= 0 ;i2 < 2;i2++)
        {
            for (int i = 0; tio[i2][i] != NULL && !choca;i++)
            {
                if ( tio[i2][i] != this && tio[i2][i] != tio[tj][tt]  )
                {
                    float x0= (tio[i2][i]->imagen->Left + tio[i2][i]->imagen->Width / 2);        //cetro circunferencia
                    float y0= (tio[i2][i]->imagen->Top + tio[i2][i]->imagen->Height / 2);
                    float r= tio[i2][i]->imagen->Width / 2;              //radio circunferencia

                    float _a= sqr(a)+1;
                    float _b= -2*x0 + 2*a*(b-y0);
                    float _c= sqr(x0) + sqr(b-y0) - sqr(r);
                    if ( sqr(_b) - 4*_a*_c >=0 )   //si exite algun punto comun entre la recta y la circunferencia
                    {
                        x0= ( (-_b + sqrt( sqr(_b) - 4*_a*_c )) / ( 2*_a) );     //puntos de corte de la recta con la circunferencia
                        y0= (a*x0 + b);
                        if (( (x1 <= x2) && (y1 <= y2) && (x1 <= x0) && (x2 >= x0) && (y1 <= y0) && (y2 >= y0) ) ||
                            ( (x1 <= x2) && (y1 >= y2) && (x1 <= x0) && (x2 >= x0) && (y1 >= y0) && (y2 <= y0) ) ||
                            ( (x1 >= x2) && (y1 <= y2) && (x1 >= x0) && (x2 <= x0) && (y1 <= y0) && (y2 >= y0) ) ||
                            ( (x1 >= x2) && (y1 >= y2) && (x1 >= x0) && (x2 <= x0) && (y1 >= y0) && (y2 <= y0) ))
                                choca = true;
                        x0= ( (-_b + sqrt( sqr(_b) - 4*_a*_c )) / ( 2*_a) );     //puntos de corte de la recta con la circunferencia
                        y0= (a*x0 + b);
                        if(( (x1 <= x2) && (y1 <= y2) && (x1 <= x0) && (x2 >= x0) && (y1 <= y0) && (y2 >= y0) ) ||
                           ( (x1 <= x2) && (y1 >= y2) && (x1 <= x0) && (x2 >= x0) && (y1 >= y0) && (y2 <= y0) ) ||
                           ( (x1 >= x2) && (y1 <= y2) && (x1 >= x0) && (x2 <= x0) && (y1 <= y0) && (y2 >= y0) ) ||
                           ( (x1 >= x2) && (y1 >= y2) && (x1 >= x0) && (x2 <= x0) && (y1 >= y0) && (y2 <= y0) ))
                            choca = true;
                    }
                }
            }
        }



        float dist= sqrt(  sqr( x2 - (imagen->Left + imagen->Width / 2) )  +  sqr ( y2  - (imagen->Top + imagen->Height/2) )  ) ;
        if ( dist <= FJuego->rango->Width / 2 && !choca)
        {
            if (arma1->getNombre() == "Brazaletes de tormenta")
                tio[tj][tt]->vida -= round( (fuerza / 2 + arma1->getFuerza()) * (1 - tio[tj][tt]->resistenciaM / 100.0 ) );
            else
                tio[tj][tt]->vida -= round( (fuerza / 2 + arma1->getFuerza()) * (1 - tio[tj][tt]->resistenciaD / 100.0 ) );

            if ( tio[tj][tt]->vida <= 0 )
            {
                FJuego->setMataCriaturaACriatura(true);
                FJuego->destruirTio(tj,tt);
                FJuego->setTioMataTio(true);            //CartaEspecial
            }
            else
                ShowMessage("Ataque a distancia" + IntToStr(tio[tj][tt]->vida));
            usaAccion();
        }
        else
            if ( choca )
                ShowMessage("Chocó!");
            else
                ShowMessage("Estas demasiado lejos para atacar");
    }
    FJuego->BCambiarTurno->Enabled = true;
}

void TTio::iniciar()
{
    if ( FJuego->cercano(this) )
        mov = movMax / 2;
    else
        mov = movMax * TVariables::getResolucionX();
    acciones = 0;
    ponerSombra();
}
void TTio::ponerSombra ()
{
    if (acciones == 1)
        sombra->Picture->LoadFromFile("imagenes\\varios\\SombraN.bmp");
    else
        if (TFJuego::getTurno() == 0)
            sombra->Picture->LoadFromFile("imagenes\\varios\\SombraA.bmp");
        else
            sombra->Picture->LoadFromFile("imagenes\\varios\\SombraR.bmp");
            
    sombra->Left = imagen->Left - 2;
    sombra->Top = imagen->Top - 2;
    sombra->Visible = true;
    sombra->Width = imagen->Width +4;
    sombra->Height = imagen->Height+4;

}

void TTio::TTio2 ( char* dibujo)
 {
            sombra = new TImage(Application);
            sombra->Visible= false;
            imagen = new TImage(Application);
            imagen->Visible= false;
            imagen->Enabled= true;
         //   imagen->Left=0;
         //   imagen->top=0;
            imagen->Picture->LoadFromFile(dibujo);
            imagen->AutoSize= true;
            imagen->Transparent= true;

            sombra->Stretch = true;
            sombra->Transparent= true;
            sombra->Width = imagen->Width + 4 ;
            sombra->Height = imagen->Height + 4 ;
            sombra->Parent = FJuego;
            imagen->Parent = FJuego;

            //MovMax= 0;
            mover= true;
            atacar= true;
              distancia= true;
              cuerpo= true;
        //Atributos del tio
            //Vida=0;
            //VidaMax=0;
            //Fuerza=0;
            //ResistenciaC=0;
            //ResistenciaD=0;
            //ResistenciaM=0;
        arma1=NULL;
        arma2=NULL;
            acciones = 0;

            carta = NULL;
            for ( int a=0; a < 5; a++ )
                armas[a] = false;
            armas[5] = true;
}






 


//enum TipoObjeto{ESPADA, ARCO, BASTON, GUANTES,MASCARA,NINGUNO};

TTio* TTio::crearDragonEsqueleto()
{
    TTio* result;
    result= new TTio("Imagenes\\caras\\DragonEsqueleto.bmp");
    result->nombre = "Dragon esqueleto" ;
    result->movMax= 260;
    result->mov = round( result->movMax * TVariables::getResolucionX() );
    result->vida = 60;
    result->vidaMax = 60;
    result->fuerza = 18;
    result->resistenciaC = 30;
    result->resistenciaD = 10;
    result->resistenciaM = 10;
    result->tipo = "dragon / esqueleto";
    return result;
}

TTio* TTio::crearMurcielago()
{
    TTio* result= new TTio("Imagenes\\caras\\Murcielago.bmp");
    result->nombre = "Murcielago";
    result->movMax= 400;
    result->mov= round( result->movMax * TVariables::getResolucionX() );
    result->vida= 20;
    result->vidaMax= 20;
    result->fuerza= 12;
    result->resistenciaC= 30;
    result->resistenciaD= 20;
    result->resistenciaM= 0;
    result->tipo = "Murcielago";
    result->usaAccion(1);
    return result;
}

TTio* TTio::crearGigante()
{
    TTio* result= new TTio("Imagenes\\caras\\GiganteDeLasCavernas.bmp");
    result->nombre = "Gigante de las cavernas";
    result->movMax= 135;
    result->mov= round( result->movMax * TVariables::getResolucionX() );
    result->vida= 200;
    result->vidaMax= 200;
    result->fuerza= 35;
    result->resistenciaC= 30;
    result->resistenciaD= 20;
    result->resistenciaM= 0;
    result->tipo = "Gigante";
    result->usaAccion(1);
    return result;
}
TTio* TTio::crearArqueroSolitario()
{
    TTio *result= new TTio("Imagenes\\caras\\ArqueroSolitario.bmp");
    result->nombre = "Arquero solitario";
    result->movMax= 150;
    result->mov= round( result->movMax * TVariables::getResolucionX() );
    result->vida= 70;
    result->vidaMax= 70;
    result->fuerza= 18;
    result->resistenciaC= 0;
    result->resistenciaD= 15;
    result->resistenciaM= 15;
    result->tipo = "Humano";
    result->setArma( 0, crearArcoCorto() );
    result->armas[0]= true;
    result->armas[1]= true;
    result->armas[2]= true;
    result->armas[3]= true;
    result->usaAccion(1);
    return result;
}

TTio* TTio::crearEnanoConArmadura()
{
    TTio* result= new TTio("Imagenes\\caras\\EnanoConArmadura.bmp");
    result->nombre ="Enano con armadura";
    result->movMax= 120;
    result->mov= round( result->movMax * TVariables::getResolucionX() );
    result->vida= 130;
    result->vidaMax= 130;
    result->fuerza= 25;
    result->resistenciaC= 30;
    result->resistenciaD= 25;
    result->resistenciaM= 10;
    result->tipo = "Enano";
    result->armas[0]= true;
    result->armas[1]= true;
    result->armas[3]= true;
    result->usaAccion(1);
    return result;
}


TTio* TTio::crearTortugaGigante()
{
    TTio* result= new TTio("Imagenes\\caras\\TortugaGigante.bmp");
    result->nombre ="Tortuga gigante";
    result->movMax= 80;
    result->mov= round(result-> movMax * TVariables::getResolucionX() );
    result->vida= 150;
    result->vidaMax= 150;
    result->fuerza= 10;
    result->resistenciaC= 30;
    result->resistenciaD= 80;
    result->resistenciaM= 0;
    result->tipo = "Tortuga / Gigante";
    result->usaAccion(1);
    return result;
}
TTio* TTio::crearZombiSiniestro()
{
    TTio* result= new TTio("Imagenes\\caras\\ZombiSiniestro.bmp");
    result->nombre ="Zombi siniestro";
    result->movMax= 90;
    result->mov= round(result->movMax * TVariables::getResolucionX() );
    result->vida= 90;
    result->vidaMax= 90;
    result->fuerza=9;
    result->resistenciaC= 0;
    result->resistenciaD= 0;
    result->resistenciaM= 0;
    result->tipo = "Zombie";
    result->armas[3]= true;
    result->usaAccion(1);
    return result;
}
TTio* TTio::crearAparicionDelMal()
{
    TTio* result= new TTio("Imagenes\\caras\\AparicionDelMal.bmp");
    result->nombre ="Aparicion del mal";
    result->movMax= 300;
    result->mov= round( result->movMax * TVariables::getResolucionX() );
    result->vida= 240;
    result->vidaMax= 240;
    result->fuerza= 35;
    result->resistenciaC= 20;
    result->resistenciaD= 20;
    result->resistenciaM= 0;
    result->tipo = "dragon / demonio";
    return result;
}
TTio* TTio::crearJineteOscuro()
{
    TTio* result= new TTio("Imagenes\\caras\\JineteOscuro.bmp");
    result->nombre ="Jinete oscuro";
    result->movMax= 300;
    result->mov= round( result->movMax * TVariables::getResolucionX() );
    result->vida= 120;
    result->vidaMax= 120;
    result->fuerza= 25;
    result->resistenciaC= 0;
    result->resistenciaD= 20;
    result->resistenciaM= 10;
    result->tipo = "Humano";
    result->armas[0]= true;
    result->armas[1]= true;
    result->armas[2]= true;
    result->armas[3]= true;
    result->armas[4]= true;
    result->usaAccion(1);
    return result;
}
TTio* TTio::crearHombreLobo()
{
    TTio* result= new TTio("Imagenes\\caras\\HombreLobo.bmp");
    result->nombre ="Hombre lobo";
    result->movMax= 200;
    result->mov= round(result-> movMax * TVariables::getResolucionX() );
    result->vida= 90;
    result->vidaMax= 90;
    result->fuerza= 25;
    result->resistenciaC= 10;
    result->resistenciaD= 10;
    result->resistenciaM= 10;
    result->tipo = "Lobo / Humano";
    result->usaAccion(1);
    return result;
}
TTio* TTio::crearReinaDeLosZombis()
{
    TTio* result= new TTio("Imagenes\\caras\\ReinaDeLosZombis.bmp");
    result->nombre ="Reina de los zombis";
    result->movMax= 140;
    result->mov= round(result-> movMax * TVariables::getResolucionX() );
    result->vida= 100;
    result->vidaMax= 100;
    result->fuerza= 20;
    result->resistenciaC= 0;
    result->resistenciaD= 10;
    result->resistenciaM= 60;
    result->tipo = "Rey";
    result->armas[0]= true;
    result->armas[1]= true;
    result->armas[2]= true;
    result->armas[3]= true;
    result->usaAccion(1);
    return result;
}
TTio* TTio::crearZombi()
{
    TTio* result = new TTio("Imagenes\\caras\\Zombi.bmp");
    result->nombre ="Zombi";
    result->movMax = 100;
    result->mov = round(result-> movMax * TVariables::getResolucionX() );
    result->vida = 45;
    result->vidaMax = 45;
    result->fuerza = 12;
    result->resistenciaC = 0;
    result->resistenciaD = 0;
    result->resistenciaM = 0;
    result->tipo = "Zombie";
    result->armas[3]= true;
    result->usaAccion(1);
    return result;    
}
TTio* TTio::crearCurandera()
{
    TTio* result = new TTio("Imagenes\\caras\\Curandera.bmp");
    result->nombre ="Curandera";
    result->movMax = 140;
    result->mov = round( result-> movMax * TVariables::getResolucionX() );
    result->vida = 45;
    result->vidaMax = 45;
    result->fuerza = 0;
    result->resistenciaC = 0;
    result->resistenciaD = 0;
    result->resistenciaM = 20;
    result->tipo = "Humano";
    result->armas[2]= true;
    result->armas[3]= true;
    result->armas[4]= true;
    result->usaAccion(1);
    return result;    
}
TTio* TTio::crearHadaDeLaNoche()
{
    TTio* result = new TTio("Imagenes\\caras\\HadaDeLaNoche.bmp");
    result->nombre ="Hada de la noche";
    result->movMax = 180;
    result->mov = round( result-> movMax * TVariables::getResolucionX() );
    result->vida = 35;
    result->vidaMax = 35;
    result->fuerza = 7;
    result->resistenciaC = 0;
    result->resistenciaD = 0;
    result->resistenciaM = 15;
    result->tipo = "Hada";
    result->usaAccion(1);
    return result;    
}
TTio* TTio::crearOrcoDeHierro()
{
    TTio* result = new TTio("Imagenes\\caras\\OrcoDeHierro.bmp");
    result->nombre ="Orco de hierro";
    result->movMax = 170;
    result->mov = round( result-> movMax * TVariables::getResolucionX() );
    result->vida = 80;
    result->vidaMax = 80;
    result->fuerza = 17;
    result->resistenciaC = 10;
    result->resistenciaD = 0;
    result->resistenciaM = 0;
    result->tipo = "Orco";
    result->armas[0]= true;
    result->armas[1]= true;
    result->armas[3]= true;
    result->armas[4]= true;
    result->usaAccion(1);
    return result;    
}
TTio* TTio::crearMagoDelDragon()
{
    TTio* result = new TTio("Imagenes\\caras\\MagoDelDragon.bmp");
    result->nombre ="Mago del dragon";
    result->movMax = 140;
    result->mov = round( result-> movMax * TVariables::getResolucionX() );
    result->vida = 90;
    result->vidaMax = 90;
    result->fuerza = 14;
    result->resistenciaC = 10;
    result->resistenciaD = 0;
    result->resistenciaM = 70;
    result->tipo = "Mago";
    result->armas[0]= true;
    result->armas[2]= true;
    result->armas[4]= true;
    result->usaAccion(1);
    return result;    
}
TTio* TTio::crearElfaExploradora()
{
    TTio* result = new TTio("Imagenes\\caras\\ElfaExploradora.bmp");
    result->nombre ="Elfa exploradora";
    result->movMax = 140;
    result->mov = round( result-> movMax * TVariables::getResolucionX() );
    result->vida = 40;
    result->vidaMax = 40;
    result->fuerza = 9;
    result->resistenciaC = 0;
    result->resistenciaD = 0;
    result->resistenciaM = 10;
    result->tipo = "Elfo";
    result->armas[0]= true;
    result->armas[1]= true;
    result->armas[2]= true;
    result->armas[3]= true;
    result->armas[4]= true;
    result->usaAccion(1);
    return result;
}

