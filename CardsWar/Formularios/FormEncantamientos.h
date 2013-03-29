#ifndef FormEncantamientosH
#define FormEncantamientosH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TFEncantamientos : public TForm
{
__published:	// IDE-managed Components
    TButton *BEncantamiento;
    TComboBox *CBJugador;
    TComboBox *CBEncantamiento;
    TImage *Image1;
    TImage *ICarta;
    TLabel *Label1;
    TLabel *Label2;
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall CBJugadorChange(TObject *Sender);
    void __fastcall CBEncantamientoChange(TObject *Sender);
    void __fastcall BEncantamientoClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
    __fastcall TFEncantamientos(TComponent* Owner);
    void __fastcall ordenarEncantamientos(int d);
};
//---------------------------------------------------------------------------
extern PACKAGE TFEncantamientos *FEncantamientos;
//---------------------------------------------------------------------------
#endif
