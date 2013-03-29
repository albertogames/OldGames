#ifndef FormEditorMapasH
#define FormEditorMapasH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <jpeg.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Graphics.hpp>

//---------------------------------------------------------------------------
class TFEditorMapas : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu1;
    TMenuItem *Archivo1;
    TMenuItem *Cargar1;
    TMenuItem *Guardar1;
    TMenuItem *Guardarcomo1;
    TMenuItem *Salir1;
    TMenuItem *Edicin1;
    TMenuItem *SelFondo;
    TOpenPictureDialog *OpenPictureDialog;
    TMenuItem *SelBordes;
    TMenuItem *SelBorde0;
    TMenuItem *SelBorde2;
    TMenuItem *SelBorde1;
    TMenuItem *SelBorde3;
    TSaveDialog *SaveDialog1;
    TOpenDialog *OpenDialog1;
    TOpenPictureDialog *OpenPictureDialog1;
    TButton *BNuevaPared;
    TTimer *TimerArrastrarPared;
    TEdit *EditAlto;
    TEdit *EditAncho;
        TMenuItem *Nuevapared1;
    TMenuItem *N1;
    TMenuItem *N2;
    TMenuItem *N3;
    TComboBox *CBModo;
    TImage *Image1;
    TImage *IMapa;
    TImage *IBorde1;
    TImage *IBorde0;
    TImage *IBorde3;
    TImage *IBorde2;
    TSpeedButton *BAltoInc;
    TSpeedButton *BAltoDec;
    TSpeedButton *BAnchoInc;
    TSpeedButton *BAnchoDec;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TButton *BBorrarPared;
    TMenuItem *N4;
    TMenuItem *Borrarpared1;
    TCheckBox *CBRio;
        TLabel *Label4;
    TMenuItem *Nuev1;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall Salir1Click(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall SelFondoClick(TObject *Sender);
    void __fastcall SelBorde0Click(TObject *Sender);
    void __fastcall SelBorde2Click(TObject *Sender);
    void __fastcall SelBorde1Click(TObject *Sender);
    void __fastcall SelBorde3Click(TObject *Sender);
    void __fastcall Guardar1Click(TObject *Sender);
    void __fastcall Cargar1Click(TObject *Sender);
    void __fastcall BNuevaParedClick(TObject *Sender);
    void __fastcall paredMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall TimerArrastrarParedTimer(TObject *Sender);
    void __fastcall EditAltoChange(TObject *Sender);
    void __fastcall EditAnchoChange(TObject *Sender);
        void __fastcall BAltoIncClick(TObject *Sender);
        void __fastcall BAltoDecClick(TObject *Sender);
        void __fastcall BAnchoIncClick(TObject *Sender);
        void __fastcall BAnchoDecClick(TObject *Sender);
        void __fastcall Guardarcomo1Click(TObject *Sender);
    void __fastcall CBModoChange(TObject *Sender);
    void __fastcall BBorrarParedClick(TObject *Sender);
    void __fastcall Borrarpared1Click(TObject *Sender);
    void __fastcall CBRioClick(TObject *Sender);
    void __fastcall Nuev1Click(TObject *Sender);

private:	// User declarations
    String fondo;
    String borde[4];
    int contParedes;
    String nombrePared[20];

    int paredSelec;
    void ordenarParedes();
    String nombreMapa;
    TImage* sombra;
    TImage* IColina;
    TImage* IProteger[2];
public:		// User declarations
    __fastcall TFEditorMapas(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFEditorMapas *FEditorMapas;
//---------------------------------------------------------------------------
#endif
