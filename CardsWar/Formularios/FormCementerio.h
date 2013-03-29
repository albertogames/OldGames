#ifndef FormCementerioH
#define FormCementerioH
//---------------------------------------------------------------------------

#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include <jpeg.hpp>

#pragma hdrstop
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class TFCementerio : public TForm
{
__published:	// IDE-managed Components
    TButton *BCementerio;
    TComboBox *CBCementerio;
    TImage *Image1;
    TImage *ICarta;
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall CBCementerioChange(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall BCementerioClick(TObject *Sender);
private:	// User declarations

    static int recuperarCriaturas;
public:		// User declarations
    __fastcall TFCementerio(TComponent* Owner);
    static int getRecuperarCriaturas() { return recuperarCriaturas; }
    static void setRecuperarCriaturas(int t) { recuperarCriaturas = t;}
};

//---------------------------------------------------------------------------
extern PACKAGE TFCementerio *FCementerio;
//---------------------------------------------------------------------------
#endif
