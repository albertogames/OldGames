#ifndef FormPersonajeH
#define FormPersonajeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TFPersonaje : public TForm
{
__published:	// IDE-managed Components
    TButton *BArma1;
    TButton *BArma2;
    TImage *Image1;
    TImage *ICarta;
    TLabel *LTipo;
    TLabel *LVida;
    TLabel *Label2;
    TLabel *LFuerza;
    TLabel *Label1;
    TLabel *LVelocidad;
    TLabel *Label3;
    TLabel *LRes1;
    TImage *ImagCuer;
    TLabel *LRes2;
    TImage *ImagDist;
    TLabel *LRes3;
    TImage *ImagMag;
    TLabel *LArma1;
    TLabel *LArma2;
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall BArma1Click(TObject *Sender);
    void __fastcall BArma2Click(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
    __fastcall TFPersonaje(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFPersonaje *FPersonaje;
//---------------------------------------------------------------------------
#endif
