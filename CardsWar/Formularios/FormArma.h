//---------------------------------------------------------------------------

#ifndef FormArmaH
#define FormArmaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>


//---------------------------------------------------------------------------
class TFArma : public TForm
{
__published:	// IDE-managed Components
    TButton *BDesequipar;
    TImage *Image1;
    TImage *IArma;
    TImage *IResC;
    TImage *IResD;
    TImage *IResM;
    TLabel *LFuerza;
    TLabel *Label2;
    TLabel *LabelResistencia;
    TLabel *LResC;
    TLabel *LResD;
    TLabel *LResM;
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall BDesequiparClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall destruirArma();
private:	// User declarations
    static int numArma;
public:		// User declarations
    __fastcall TFArma(TComponent* Owner);
    static void setNumArma(int a) {numArma = a;}

};

//---------------------------------------------------------------------------
extern PACKAGE TFArma *FArma;
//---------------------------------------------------------------------------
#endif
