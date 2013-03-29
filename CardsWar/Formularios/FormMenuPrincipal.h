#ifndef FormMenuPrincipalH
#define FormMenuPrincipalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>



//---------------------------------------------------------------------------
class TFMenuPrincipal : public TForm
{
__published:	// IDE-managed Components
    TButton *B2Jugadores;
    TButton *BEditMazo;
    TButton *BOpciones;
    TButton *BSalir;
    TImage *Image1;
    TButton *BEditMapas;
    TButton *BCreditos;
    void __fastcall BSalirClick(TObject *Sender);
    void __fastcall BEditMazoClick(TObject *Sender);
    void __fastcall BOpcionesClick(TObject *Sender);
    void __fastcall B2JugadoresClick(TObject *Sender);
    void __fastcall BEditMapasClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall BCreditosClick(TObject *Sender);
private:	// User declarations






    public:		// User declarations
    __fastcall TFMenuPrincipal(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFMenuPrincipal *FMenuPrincipal;
//---------------------------------------------------------------------------
#endif
