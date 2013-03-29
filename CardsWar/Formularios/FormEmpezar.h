#ifndef FormEmpezarH
#define FormEmpezarH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include "deque.h"
#include "upared.h"


using namespace std;
//---------------------------------------------------------------------------
class TFEmpezar : public TForm
{
__published:	// IDE-managed Components
    TLabel *LModjuego;
    TLabel *Label6;
    TButton *BJugar;
    TComboBox *CBMazo1;
    TComboBox *CBMazo2;
    TComboBox *CBModo;
    TComboBox *CBNick1;
    TButton *BClose;
    TComboBox *CBNick2;
    TImage *IMapa;
    TLabel *Label5;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Jugador2;
    TLabel *Label3;
    TLabel *Label4;
    TImage *Fondo;
    TOpenDialog *OpenDialog1;
    TButton *BCargarMapa;
    TCheckBox *CheckBoxIA;
    void __fastcall BCloseClick(TObject *Sender);
    void __fastcall CBNick1Change(TObject *Sender);
    void __fastcall CBNick2Change(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall BJugarClick(TObject *Sender);
    void __fastcall guardarDatos(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall BCargarMapaClick(TObject *Sender);
    void __fastcall cargarMapa(String map);
    void __fastcall CBModoChange(TObject *Sender);
private:	// User declarations

    String pantallaSelec;
    TImage* IColina;
    TImage* IProteger[2];
    deque <TPared> pared;
public:		// User declarations
    __fastcall TFEmpezar(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFEmpezar *FEmpezar;
//---------------------------------------------------------------------------
#endif
