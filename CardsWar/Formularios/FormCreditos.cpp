//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormCreditos.h"
#include "UVariables.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFCreditos *FCreditos;
//---------------------------------------------------------------------------
__fastcall TFCreditos::TFCreditos(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFCreditos::FormActivate(TObject *Sender)
{

    Position = poScreenCenter;
}
//---------------------------------------------------------------------------
void __fastcall TFCreditos::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    Action = caFree;    
}
//---------------------------------------------------------------------------

