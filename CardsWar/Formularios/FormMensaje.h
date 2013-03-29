#ifndef FormMensajeH
#define FormMensajeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TFMensaje : public TForm
{
__published:	// IDE-managed Components
    TImage *Image1;
    TLabel *Texto;
    TButton *B1;
    TButton *B2;
    TEdit *paEscribir;
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall B1Click(TObject *Sender);
    void __fastcall B2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFMensaje(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFMensaje *FMensaje;
//---------------------------------------------------------------------------
#endif
