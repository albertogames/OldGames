//---------------------------------------------------------------------------

#ifndef FormCartaH
#define FormCartaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFCarta : public TForm
{
__published:	// IDE-managed Components
    TImage *imagCarta;
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private:	// User declarations
    static String nombreCarta;
    
public:		// User declarations
    __fastcall TFCarta(TComponent* Owner);

    static String getNombreCarta() {return nombreCarta; }
    static void setNombreCarta(String n) { nombreCarta = n; }

};




//---------------------------------------------------------------------------
extern PACKAGE TFCarta *FCarta;
//---------------------------------------------------------------------------
#endif
