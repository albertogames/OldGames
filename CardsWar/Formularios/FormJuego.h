#ifndef FormJuegoH
#define FormJuegoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>

#include <jpeg.hpp>
#include <deque>
#include "UVariables.h"

//---------------------------------------------------------------------------
class TFJuego : public TForm
{
__published:	// IDE-managed Components
    TImage *Image1;
    TImage *Image2;
    TLabel *LPm;
    TLabel *LNombre;
    TImage *IMano3;
    TImage *IMano2;
    TImage *IMano4;
    TImage *IMano7;
    TImage *IMano5;
    TImage *IMano6;
    TImage *IMano1;
    TImage *ICementerio;
    TImage *IMazo;
    TLabel *LMazo;
    TImage *IMapa;
    TShape *area;
    TShape *rango;
    TShape *rango2;
    TButton *BCambiarTurno;
    TButton *BEncant;
    TButton *BCerrar;
    TTimer *TimerCrearCriatura;
    TTimer *TimerVarios;
    TTimer *TimerMover;


    void __fastcall FormActivate(TObject *Sender);
    void __fastcall BCerrarClick(TObject *Sender);
    void __fastcall BCambiarTurnoClick(TObject *Sender);
    void __fastcall IManoMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall descartarClick(TObject *Sender);
    void __fastcall verClick(TObject *Sender);
    void __fastcall usarClick(TObject *Sender);
    void __fastcall abrirCementerio(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall TimerCrearCriaturaTimer(TObject *Sender);
    void __fastcall personajeClick(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall crearMenu(TObject *Sender, TTio* ti);
    void __fastcall nomClick(TObject *Sender);
    void __fastcall moverClick(TObject *Sender);
    void __fastcall TimerMoverTimer(TObject *Sender);
    void __fastcall descartar();
    void __fastcall barajear(int jugador);
    void __fastcall robar();
        void __fastcall ordenarMano();
        void __fastcall actualizarMano();
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall destruirTio(int a, int b);
    void __fastcall proteger(int j,int t);
    void __fastcall invocarCerca( int a, int b);
    void __fastcall desactivarHechizos();
    void __fastcall crearZombiClick(TObject *Sender);
    void __fastcall usarEncantamiento();
    void __fastcall BEncantClick(TObject *Sender);
    void __fastcall recrear();
    void __fastcall TimerVariosTimer(TObject *Sender);
    void __fastcall recrearLabel(TLabel* & l);
    void __fastcall recrearShape(TShape* & s);
    void __fastcall recrearImagen(TImage* & imagen);
    void __fastcall cuerClick(TObject *Sender);
    void __fastcall distClick(TObject *Sender);
    void __fastcall crearRayoClick(TObject *Sender);
    void __fastcall BEncantKeyPress(TObject *Sender, char &Key);
    void __fastcall ganar(int j);
    void __fastcall activarIA();
        void __fastcall atacarCuerpoIA();
    bool __fastcall comprovarCrearCriatura(int x, int y);
    void __fastcall generarManaClick(TObject *Sender);
    void __fastcall iniciarDragonClick(TObject *Sender);



private:	// User declarations

    static int tjAnt,ttAnt;
    TImage* puntero;
    TImage * IColina;

    TLabel* LColina;
    TLabel* LProteger[2];
    TImage* IProteger[2];
    int VProteger[2];
    int turnoContrario;
    int turnosColina,jugadorColina;
    TCarta* mano[2][7];
    int numCartasMazo[2], numCartasMano[2];
    TImage* manoI[7];
    int Pm[2];
    int pmMax[2];
    bool usaMana;
    TPopupMenu* menuc;
    int cartaSelec;
    bool habilidadCriatura; //true = la criatura creada es creada x la habilidad de otra criatura
    TCarta* carta;
    bool ataca;
    bool tioMataTio;
    bool distancia;
    bool atacaDist;
    int zombiSiniestro[2][10];
    int cheat;
    bool cheatIA;

    static int numCartasCem[2];
    static TCarta* mazo[2][60];
    static int modJuego;

    static TRegMap AMap[10];
    static String nombre[2];
    static int turnoC;
    static TCarta* cementerio[2][60];
    static int turno;
    static TCarta* encantamiento[2][20];

    bool usaHechizo; //Usada por todos los hechizos
    bool dosisDeSupervivencia;
    bool escuelaDeArmas;
    bool mitosis;
    int fuerzaReina;
    bool iniciarDragon;

    //encantamientos
    int tierrasLejanas[2];
    int turnosBT[2];
    static TImage* imagenBT[2];
    bool bosqueT;
    bool heroes[2];
    bool mataCriaturaACriatura;
    static int destruirEncantamientos;
    static bool destruyeEncant;
    
    static bool IA;

    static String nomPantalla;
    static deque <TPared> paredes;

public:		// User declarations

    

    __fastcall TFJuego(TComponent* Owner);

    static TCarta* getMazo(int a, int b) { return mazo[a][b];}
    static void setMazo(int a, int b, TCarta* carta) { mazo[a][b] = carta; }
    static void setModJuego(int m) { modJuego = m; }
    static int getModJuego() { return modJuego; }
    static TRegMap getAMap(int x) { return AMap[x];}
    static void setAMap(int x, TRegMap m) { AMap[x] = m; }
    static String getNombre(int a) { return nombre[a]; }
    static void setNombre(int a, String s ) { nombre[a] = s; }
    static int getTurnoC() { return turnoC;}
    static void setTurnoC(int a) { turnoC = a;}
    static int getNumCartasCem(int x) { return numCartasCem[x];}
    static void setNumCartasCem(int a, int x) { numCartasCem[a] = x;}
    static TCarta* getCementerio(int a, int b) { return cementerio[a][b];}
    static void setCementerio(int a, int b, TCarta* carta) { cementerio[a][b] = carta; }
    static int getTurno() { return turno; }
    static void setTurno(int t) { turno = t;}
    int getNumCartasMano(int x) { return numCartasMano[x];}
    void setNumCartasMano(int a, int x) { numCartasMano[a] = x;}
    void setMano(int a, int b, TCarta* c) {mano[a][b] = c;}
    TCarta* getMano(int a,int b) {return mano[a][b];}
    void setManoIImagen(int a,String i) {manoI[a]->Picture->LoadFromFile(i);manoI[a]->Visible = true;}
    static int getTjAnt() {return tjAnt;}
    static int getTtAnt() {return ttAnt;}
    void setTioMataTio(bool b) {tioMataTio = b;}
    void setMataCriaturaACriatura(bool b){mataCriaturaACriatura=b;}
  //  bool getUsaHechizo() { return usaHechizo;}
    void setUsaHechizo(bool t) { usaHechizo = t;}
    bool getDosisDeSupervivencia() { return dosisDeSupervivencia;}
    void setDosisDeSupervivencia(bool t) { dosisDeSupervivencia = t;}
    void setEscuelaDeArmas(bool t) {escuelaDeArmas = t;}
    void setMitosis( bool b) { mitosis = b; }
    //encantamientos
    int getTierrasLejanas(int x) { return tierrasLejanas[x];}
    void setTierrasLejanas( int a, int t) { tierrasLejanas[a] = t; }
    static TCarta* getEncantamiento(int a, int b) { return encantamiento[a][b];}
    static void setEncantamiento(int a, int b, TCarta* carta) { encantamiento[a][b] = carta; }
    static TImage* getImagenBT(int a) { return imagenBT[a]; }
    static void setImagenBT(int a, TImage* i) { imagenBT[a] = i; }
    void setTurnosBT(int a, int b) { turnosBT[a] = b; }
    void setBosqueT(bool t) { bosqueT = t;}
    bool getBosqueT() { return bosqueT;}
    void setHeroes(int t, bool h) { heroes[t] = h;}
    bool getHeroes( int t ) { return heroes[t];}
    void incZombiSiniestro(int a, int b) { zombiSiniestro[a][b]++; } 
    static void setIA(bool i) { IA = i; }


    bool __fastcall cercano(TTio* t);

    static void setDestruirEncantamientos(int e) { destruirEncantamientos = e;}
    static bool getDestruirEncantamientos() { return destruirEncantamientos;}

    static void setDestruyeEncant(bool e) { destruyeEncant = e;}
    static bool getDestruyeEncant() { return destruyeEncant;}

    static void setNomPantalla(String a) { nomPantalla = a; }
    static deque <TPared> &getParedes() {return paredes;}

};


//---------------------------------------------------------------------------
extern PACKAGE TFJuego *FJuego;
//---------------------------------------------------------------------------
#endif
