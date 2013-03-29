#ifndef FJugadorH
#define FJugadorH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#pragma hdrstop
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class TFJugador : public TForm
{
__published:	// IDE-managed Components
    TButton *BJugadorNuevo;
    TButton *BBorrarJugador;
    TButton *BVolver;
    TComboBox *CBJugador;
    TImage *Image1;
    TRadioGroup *RGResolucion;
    TButton *BAplicar;
    void __fastcall BJugadorNuevoClick(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall BVolverClick(TObject *Sender);
    void __fastcall BBorrarJugadorClick(TObject *Sender);
    void __fastcall CBJugadorChange(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall BAplicarClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFJugador(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFJugador *FJugador;
//---------------------------------------------------------------------------
#endif
