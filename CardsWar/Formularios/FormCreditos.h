//---------------------------------------------------------------------------

#ifndef FormCreditosH
#define FormCreditosH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TFCreditos : public TForm
{
__published:	// IDE-managed Components
    TImage *Image1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
    __fastcall TFCreditos(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFCreditos *FCreditos;
//---------------------------------------------------------------------------
#endif
