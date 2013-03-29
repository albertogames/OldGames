#ifndef TioH
#define TioH
#include "UPared.h"
#include "UArma.h"





class TTio
{
    private:
        static TPopupMenu* menuj;
        static int tj,tt;
        static TTio* tio[2][20];
        TArma* arma1;
        TArma* arma2;
        int acciones;
        String nombre;


    public:


        //Caracteristicas del menu
        bool mover,atacar,distancia,cuerpo; //Acciones que esta realizando
                 //Atributos del tio
        TImage * imagen;
        int mov; //Movimiento que le queda;
        int vida;
        int vidaMax;
        int fuerza;
        int resistenciaC;
        int resistenciaD;
        int resistenciaM;
        int movMax;
        TImage* sombra;
         //Tipo
        AnsiString  tipo;
        bool armas[4];      // 1= espadas, 2= Arcos, 3= bastones, 4= guantes
        TCarta* carta;

        void TTio2 ( char* dibujo);
        TTio ( char* dibujo)
        {
            TTio2(dibujo);
        }
        ~TTio()
        {
            if (imagen != NULL)
                delete imagen;
            delete sombra;
        }
        static void TTio::setMenuj(TPopupMenu* pop)     {menuj = pop;}
        static void TTio::destruirMenuj()     {delete menuj;}
        static TPopupMenu* TTio::getMenuj()     {return menuj;}
        static void TTio::setTj(int j)  {tj=j;}
        static void TTio::setTt(int t)  {tt=t;}
        static int TTio::getTj()  {return tj;}
        static int TTio::getTt()  {return tt;}
        static TTio* TTio::getTio() {return tio[tj][tt];}
        static void TTio::setTio(int a, int b, TTio* t) { tio[a][b] = t;}                       
        static TTio* TTio::getTio(int j,int t) {return tio[j][t];}
        static void TTio::setNullTio(int j, int t) {tio[j][t] = NULL;}
        static void TTio::setInvocarTio(int j,int t,TTio* criaturaInvocar) {tio[j][t] = criaturaInvocar;}
        void TTio::usaAccion(int s = 0){acciones++;if (s == 0)ponerSombra();}//Si no se pasa nada se pone la sombra
        int TTio::getAcciones() {return acciones;}


        void __fastcall TTio::nomVlick(TObject *Sender);

        bool mueve(int x,int y);
        void atacarCuerpo();
        void atacarDistancia(int x2, int y2);
        void iniciar();
        void setNombre( String n ) { nombre = n; }
        String getNombre() { return nombre; }

        TArma* getArma(int x) { if ( x ) return arma2; else return arma1 ;}
        void setArma( int x, TArma* arm) { if ( x ) arma2 = arm; else arma1 = arm; }
        String getArmaNombre(int x) {if ( x ) return arma2->getNombre(); else return arma1->getNombre();}

        TImage* & getImagen() {return imagen;}

        void setMov( int n ) { mov = n; }
        int getMov() { return mov; }
        void setCarta( TCarta* n ) { carta = n; }
        TCarta* getCarta() {return carta;}

        /*
        TImage* getSombra() { return sombra; }



        void setMovMax( int n ) { movMax = n; }
        int getMovMax() { return movMax; }

        void setMover( bool n ) { mover = n; }
        bool getMover() { return mover; }

        void setAtacar( bool n ) { atacar = n; }
        bool getAtacar() { return atacar; }

        void setDistancia( bool n ) { distancia = n; }
        bool getDistancia() { return distancia; }

        void setCuerpo( bool n ) { cuerpo = n; }
        bool getCuerpo() { return cuerpo; }

        void setVida( int n ) { vida = n; }
        int getVida() { return vida; }

        void setVidaMax( int n ) { vidaMax = n; }
        int getVidaMax() { return vidaMax; }

        void setFuerza( int n ) { fuerza = n; }
        int getFuerza() { return fuerza; }

        int getResistenciaC() { return resistenciaC; }
        int getResistenciaD() { return resistenciaD; }
        int getResistenciaM() { return resistenciaM; }

        //void setSombra( TImage* n ) { sombra = n; }

        String getTipo() { return tipo; }



        bool getArmas(int i) {return armas[i];}
         */
        TTio* copia ()
        {
            TTio* result;

            result = new TTio("Imagenes\\caras\\AparicionDelMal.bmp");       //uno por poner

            result->imagen->Picture = imagen->Picture;
            result->imagen->Parent = imagen->Parent;

            result->nombre = nombre;
            result->movMax = movMax;
            result->mover = mover;
            result->atacar = mover;
              result->distancia = distancia;
              result->cuerpo= cuerpo;


        //Atributos del tio
            result->vida = vida;
            result->vidaMax = vidaMax;
            result->fuerza = fuerza;
            result->resistenciaC = resistenciaC;
            result->resistenciaD = resistenciaD;
            result->resistenciaM = resistenciaM;
            result->arma1 = NULL;
            result->arma2 = NULL;
        //Tipo
            result->tipo = tipo;
            result->acciones = 1;
       //     result->imagen->OnMouseDown = imagen->OnMouseDown;
            result->carta = NULL;
            for (int i = 0;i < 5; i++)
                result->armas[i] = armas[i];
            return result;
        }
        void ponerSombra ();

static TTio* crearDragonEsqueleto();
static TTio* crearMurcielago();
static TTio* crearGigante();
static TTio* crearArqueroSolitario();
static TTio* crearEnanoConArmadura();
static TTio* crearTortugaGigante();
static TTio* crearZombiSiniestro();
static TTio* crearAparicionDelMal();
static TTio* crearJineteOscuro();
static TTio* crearHombreLobo();
static TTio* crearReinaDeLosZombis();
static TTio* crearZombi();
static TTio* crearCurandera();
static TTio* crearHadaDeLaNoche();
static TTio* crearOrcoDeHierro();
static TTio* crearMagoDelDragon();
static TTio* crearElfaExploradora();


};









#endif

