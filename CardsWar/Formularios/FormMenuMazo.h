#ifndef FormMenuMazoH
#define FormMenuMazoH
//---------------------------------------------------------------------------
/*#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>    solo estas*/

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <jpeg.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>

//---------------------------------------------------------------------------
class TFMenuMazo : public TForm
{
__published:	// IDE-managed Components
    TImage *Image1;
    TImage *Carta51;
    TImage *Carta41;
    TImage *Carta31;
    TImage *Carta21;
    TImage *Carta11;
    TImage *Carta1;
    TImage *Carta2;
    TImage *Carta3;
    TImage *Carta4;
    TImage *Carta5;
    TImage *Carta6;
    TImage *Carta7;
    TImage *Carta8;
    TImage *Carta9;
    TImage *Carta10;
    TImage *Carta20;
    TImage *Carta30;
    TImage *Carta40;
    TImage *Carta50;
    TImage *Carta58;
    TImage *Carta60;
    TImage *Carta59;
    TImage *Carta57;
    TImage *Carta56;
    TImage *Carta55;
    TImage *Carta54;
    TImage *Carta53;
    TImage *Carta52;
    TImage *Carta12;
    TImage *Carta13;
    TImage *Carta14;
    TImage *Carta15;
    TImage *Carta16;
    TImage *Carta17;
    TImage *Carta18;
    TImage *Carta19;
    TImage *Carta22;
    TImage *Carta23;
    TImage *Carta24;
    TImage *Carta25;
    TImage *Carta26;
    TImage *Carta27;
    TImage *Carta28;
    TImage *Carta29;
    TImage *Carta32;
    TImage *Carta33;
    TImage *Carta34;
    TImage *Carta35;
    TImage *Carta36;
    TImage *Carta37;
    TImage *Carta38;
    TImage *Carta39;
    TImage *Carta42;
    TImage *Carta43;
    TImage *Carta44;
    TImage *Carta45;
    TImage *Carta46;
    TImage *Carta47;
    TImage *Carta48;
    TImage *Carta49;
    TLabel *Label2;
    TLabel *Label1;
    TButton *BCreaMazo;
    TButton *BCartas;
    TButton *BVerTuMazo;
    TButton *BBorrarMazo;
    TButton *BNombre;
    TButton *BTipo;
    TButton *BMana;
    TButton *BotonClose;
    TComboBox *CBJugador;
    TComboBox *CBMazo;
    void __fastcall BotonCloseClick(TObject *Sender);
    void __fastcall BCartasClick(TObject *Sender);
    void __fastcall BVerTuMazoClick(TObject *Sender);

    void __fastcall verclick(TObject *Sender);
    void __fastcall agregarclick(TObject *Sender);
    void __fastcall cargar();
    void __fastcall cartaClick(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall BCreaMazoClick(TObject *Sender);
    void __fastcall CBJugadorChange(TObject *Sender);
    void __fastcall CBMazoChange(TObject *Sender);
    void __fastcall BBorrarMazoClick(TObject *Sender);
    void __fastcall BNombreClick(TObject *Sender);
    void __fastcall BManaClick(TObject *Sender);
    void __fastcall BTipoClick(TObject *Sender);
    void __fastcall borrarPantalla();
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private:	// User declarations

    TImage* cartas[60];
    TPopupMenu* menuc;

    int cartaSelec; //0..59


    static int mazoSelec;


public:		// User declarations
    __fastcall TFMenuMazo(TComponent* Owner);

    static void setMazoSelec(int m) { mazoSelec = m;}


};
int TFMenuMazo::mazoSelec = 0;

//---------------------------------------------------------------------------

extern PACKAGE TFMenuMazo *FMenuMazo;

//---------------------------------------------------------------------------
#endif
