//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#pragma package(smart_init)
#pragma resource "*.dfm"

#include "FormEditorMapas.h"

#include "FormJuego.h"

using namespace std;
//---------------------------------------------------------------------------

TFEditorMapas *FEditorMapas;

    TPared* pared[20];
//---------------------------------------------------------------------------
__fastcall TFEditorMapas::TFEditorMapas(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFEditorMapas::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    for (int i = 0;pared[i] != NULL && i < 20 ;i++)
        delete pared[i];
    Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TFEditorMapas::Salir1Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TFEditorMapas::FormActivate(TObject *Sender)
{
    Width = TVariables::getResolucionX() * 1280;
    Height = TVariables::getResolucionX() * 1024;
    Position = poScreenCenter;

    CBModo->Items->Add("Rey de la colina");
    CBModo->Items->Add("Proteger");
    IColina = new TImage(this);
    IColina->Parent = this;
    IProteger[0] = new TImage(this);
    IProteger[0]->Parent =this;
    IProteger[1] = new TImage(this);
    IProteger[1]->Parent =this;
    VertScrollBar->Visible = false;
    HorzScrollBar->Visible = false;
    nombreMapa ="";
    cambiarRes(CBModo);
    cambiarRes(IBorde0);
    cambiarRes(IBorde1);
    cambiarRes(IBorde2);
    cambiarRes(IBorde3);
    cambiarRes(IMapa);
    cambiarRes(Label1);
    cambiarRes(Label2);
    cambiarRes(Label3);
    cambiarRes(BNuevaPared);
    cambiarRes(EditAlto);
    cambiarRes(EditAncho);
    cambiarRes(BAltoInc);
    cambiarRes(BAltoDec);
    cambiarRes(BAnchoInc);
    cambiarRes(BAnchoDec);
    cambiarRes(BBorrarPared);
    cambiarRes(Label4);

    sombra = new TImage(this);
    sombra->Picture->LoadFromFile("imagenes\\varios\\sombraM.bmp");
    sombra->Visible  = false;
    sombra->AutoSize = false;
    sombra->Stretch = true;
    sombra->Parent = this;

    CBRio->Left *= TVariables::getResolucionX();
    CBRio->Top *= TVariables::getResolucionY();

    paredSelec = -1;
    for (int i = 0;pared[i] != NULL && i < 20 ;i++)
        pared[i] = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFEditorMapas::SelFondoClick(TObject *Sender)
{
    OpenPictureDialog->InitialDir = "Imagenes\\Fondos";
    if ( OpenPictureDialog->Execute() )
    {
        fondo = OpenPictureDialog->FileName;
        char a[50];
        strcpy( a, strstr(fondo.c_str(),"Imagenes\\Fondos" ) );
        fondo = a;
        IMapa->Picture->LoadFromFile(fondo);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFEditorMapas::SelBorde0Click(TObject *Sender)
{
    if ( OpenPictureDialog1->Execute() )
    {
        borde[0] = OpenPictureDialog1->FileName;
        char a[50];
        strcpy( a, strstr(borde[0].c_str(),"Imagenes\\Paredes" ) );
        borde[0] = a;
        IBorde0->Picture->LoadFromFile(borde[0]);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFEditorMapas::SelBorde2Click(TObject *Sender)
{
    if ( OpenPictureDialog1->Execute() )
    {
        borde[2] = OpenPictureDialog1->FileName;
        char a[50];
        strcpy( a, strstr(borde[2].c_str(),"Imagenes\\Paredes" ) );
        borde[2] = a;
        IBorde2->Picture->LoadFromFile(borde[2]);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFEditorMapas::SelBorde1Click(TObject *Sender)
{
    if ( OpenPictureDialog1->Execute() )
    {
        borde[1] = OpenPictureDialog1->FileName;
        char a[50];
        strcpy( a, strstr(borde[1].c_str(),"Imagenes\\Paredes" ) );
        borde[1] = a;
        IBorde1->Picture->LoadFromFile(borde[1]);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFEditorMapas::SelBorde3Click(TObject *Sender)
{
    if ( OpenPictureDialog1->Execute() )
    {
        borde[3] = OpenPictureDialog1->FileName;
        char a[50];
        strcpy( a, strstr(borde[3].c_str(),"Imagenes\\Paredes" ) );
        borde[3] = a;
        IBorde3->Picture->LoadFromFile(borde[3]);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFEditorMapas::Guardarcomo1Click(TObject *Sender)
{
    if (fondo != "" && borde[0] != "" && borde[1] != "" && borde[2] != "" && borde[3] != "")
    {
        if (SaveDialog1->Execute() )
        {
            nombreMapa = SaveDialog1->FileName;
            Guardar1Click(NULL);
        }
    }
    else
        ShowMessage("Elige un fondo y los bordes");
}
void __fastcall TFEditorMapas::Guardar1Click(TObject *Sender)
{
    if (nombreMapa != "" )
    {
        ofstream fichSalida( nombreMapa.c_str() );

        fichSalida << fondo.c_str() << endl;

        for (int i = 0; i < 4; i++)
            fichSalida << borde[i].c_str() << endl;

        for (int i=0; i < 20 && pared[i] != NULL;i++)
        {
            fichSalida <<  round(pared[i]->getImagen()->Left/TVariables::getResolucionX()) << " " <<  round(pared[i]->getImagen()->Top/TVariables::getResolucionY()) << " " << round(pared[i]->getImagen()->Width/TVariables::getResolucionX()) << " " << round(pared[i]->getImagen()->Height/TVariables::getResolucionY()) << " " << pared[i]->getRio() << " " << nombrePared[i].c_str();
            if (i == 19 || pared[i+1] != NULL)
                fichSalida << endl;
        }
        fichSalida.close();
    }
    else
        Guardarcomo1Click(NULL);
}

//---------------------------------------------------------------------------
void __fastcall TFEditorMapas::Cargar1Click(TObject *Sender)
{
    if (OpenDialog1->Execute())
    {
        contParedes=0;
        for (int i = 0;pared[i] != NULL && i < 20 ;i++)
        {
            delete pared[i];
            pared[i] = NULL;
        }
        char aux[200];
        nombreMapa = OpenDialog1->FileName;
        ifstream fichEntrada( nombreMapa.c_str() );
        fichEntrada >> aux;
        fondo = aux;
        for (int i = 0;i < 4;i++)
        {
            fichEntrada >> aux;
            borde[i] = aux;
        }
        IMapa->Picture->LoadFromFile(fondo);
        IBorde0->Picture->LoadFromFile(borde[0]);
        IBorde1->Picture->LoadFromFile(borde[1]);
        IBorde2->Picture->LoadFromFile(borde[2]);
        IBorde3->Picture->LoadFromFile(borde[3]);
        for (int i=0;!fichEntrada.eof();i++)
        {
            int x,y,w,h;
            bool r;
            char n[50];
            fichEntrada >> x;
            fichEntrada >> y;
            fichEntrada >> w;
            fichEntrada >> h;
            fichEntrada >> r;
            fichEntrada >> n;
            pared[i] = new TPared(x,y,n,r);
            pared[i]->getImagen()->Width = w;
            pared[i]->getImagen()->Height = h;
            pared[i]->getImagen()->Parent = this;
            pared[i]->getImagen()->OnMouseDown = paredMouseDown;
            cambiarRes(pared[i]->getImagen());
            nombrePared[i] = n;
            contParedes++;
        }
        fichEntrada.close();
        sombra->Visible = false;
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TFEditorMapas::BNuevaParedClick(TObject *Sender)
{
    if ( OpenPictureDialog1->Execute() )
    {
        if (contParedes < 20)
        {
            String aux1;
            char aux2[50];
            aux1 = OpenPictureDialog1->FileName;
            strcpy( aux2, strstr(aux1.c_str(),"Imagenes\\Paredes" ) );
            pared[contParedes] = new TPared(0,0,aux2,false,this);
            pared[contParedes]->getImagen()->AutoSize = true;
            pared[contParedes]->getImagen()->AutoSize = false;
            pared[contParedes]->getImagen()->OnMouseDown = paredMouseDown;
            nombrePared[contParedes] = aux2;
            cambiarRes(pared[contParedes]->getImagen());
            pared[contParedes]->getImagen()->Top = IBorde1->Top + IBorde1->Height;
            pared[contParedes]->getImagen()->Left = IBorde0->Left + IBorde0->Width;
            TShiftState Shift ;
            paredMouseDown(pared[contParedes]->getImagen(),0,  Shift , 0, 0);
            CBRio->Checked = pared[contParedes]->getRio();
            contParedes++;
        }
        else
            ShowMessage("Solo puedes poner 20 paredes");
    }
}

void __fastcall TFEditorMapas::paredMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    int i=0;
    for (;pared[i]->getImagen() != static_cast <TImage*>(Sender);i++);
    paredSelec = i;
    sombra->Left = pared[i]->getImagen()->Left - 2;
    sombra->Top = pared[i]->getImagen()->Top -2;
    sombra->Width = pared[i]->getImagen()->Width + 4;
    sombra->Height = pared[i]->getImagen()->Height + 4;
    sombra->Visible = true;
    FJuego->recrearImagen(sombra);
    FJuego->recrearImagen(pared[i]->getImagen());
    EditAlto->Text = pared[i]->getImagen()->Height;
    EditAncho->Text = pared[i]->getImagen()->Width;
    TPoint posicion;
    SetCursorPos(pared[i]->getImagen()->Left + pared[i]->getImagen()->Width / 2+ Left,pared[i]->getImagen()->Top + pared[i]->getImagen()->Height/2 + 20 + Top);
    CBRio->Checked = pared[i]->getRio();
    TimerArrastrarPared->Enabled = true;



}
//---------------------------------------------------------------------------

void __fastcall TFEditorMapas::TimerArrastrarParedTimer(TObject *Sender)
{
    TPoint posicion;
    GetCursorPos(&posicion);
    int x = posicion.x - Left ;
    int y = posicion.y - Top ;
    if (x - pared[paredSelec]->getImagen()->Width / 2 < IBorde0->Left + IBorde0->Width )
    {
        pared[paredSelec]->getImagen()->Left = IBorde0->Left + IBorde0->Width;
        x  = pared[paredSelec]->getImagen()->Left + pared[paredSelec]->getImagen()->Width/2;
    }
    else if (x + pared[paredSelec]->getImagen()->Width/2 > IBorde2->Left)
    {
        pared[paredSelec]->getImagen()->Left = IBorde2->Left - pared[paredSelec]->getImagen()->Width;
        x = pared[paredSelec]->getImagen()->Left + pared[paredSelec]->getImagen()->Width/2;
    }

    if (y - pared[paredSelec]->getImagen()->Height/2   < IBorde1->Top + IBorde1->Height  + 20)
    {
        pared[paredSelec]->getImagen()->Top = IBorde1->Top + IBorde1->Height  ;
        y = pared[paredSelec]->getImagen()->Top + pared[paredSelec]->getImagen()->Height/2 +20;
    }
    else if (y + pared[paredSelec]->getImagen()->Height/2  > IBorde3->Top +20)
    {
        pared[paredSelec]->getImagen()->Top = IBorde3->Top  - pared[paredSelec]->getImagen()->Height ;
        y = pared[paredSelec]->getImagen()->Top + pared[paredSelec]->getImagen()->Height/2 +20 ;
    }
    if ( HIWORD(GetKeyState(VK_LBUTTON)) )
    {
        pared[paredSelec]->getImagen()->Left = x - pared[paredSelec]->getImagen()->Width/2;
        pared[paredSelec]->getImagen()->Top = y - pared[paredSelec]->getImagen()->Height/2 - 20;
    }
    else
        TimerArrastrarPared->Enabled = false;

    sombra->Left = pared[paredSelec]->getImagen()->Left - 2;
    sombra->Top = pared[paredSelec]->getImagen()->Top - 2;
}
//---------------------------------------------------------------------------

void TFEditorMapas::ordenarParedes()
{
    int i;
    for ( i=19 ; pared[i] == NULL && i >= 0 ; i--  );       //Ultima ocupada

    if ( paredSelec < i )           //Intercambiar posiciones
    {
        pared[paredSelec] = pared[i];
        pared[i] = NULL;
    }

}



void __fastcall TFEditorMapas::EditAltoChange(TObject *Sender)
{
    if (paredSelec != -1)
    {
        pared[paredSelec]->getImagen()->Height = atoi(EditAlto->Text.c_str());
        if (pared[paredSelec]->getImagen()->Top + pared[paredSelec]->getImagen()->Height > IBorde3->Top)
        {
            pared[paredSelec]->getImagen()->Height = IBorde3->Top - pared[paredSelec]->getImagen()->Top;
            EditAlto->Text = pared[paredSelec]->getImagen()->Height;
        }
        if (pared[paredSelec]->getImagen()->Height < 15 * TVariables::getResolucionY())
            pared[paredSelec]->getImagen()->Height = 15 * TVariables::getResolucionY();
        sombra->Height  = pared[paredSelec]->getImagen()->Height + 4;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFEditorMapas::EditAnchoChange(TObject *Sender)
{
    if (paredSelec != -1)
    {
        pared[paredSelec]->getImagen()->Width = atoi(EditAncho->Text.c_str());
        if (pared[paredSelec]->getImagen()->Left + pared[paredSelec]->getImagen()->Width > IBorde2->Left)
        {
            pared[paredSelec]->getImagen()->Width = IBorde2->Left -  pared[paredSelec]->getImagen()->Left;
            EditAncho->Text = pared[paredSelec]->getImagen()->Width;
        }
        if (pared[paredSelec]->getImagen()->Width < 15 * TVariables::getResolucionX())
            pared[paredSelec]->getImagen()->Width = 15 * TVariables::getResolucionX();
        sombra->Width  = pared[paredSelec]->getImagen()->Width + 4;
    }
}
//---------------------------------------------------------------------------


void __fastcall TFEditorMapas::BAltoIncClick(TObject *Sender)
{
    if (paredSelec != -1)
        EditAlto->Text = IntToStr(pared[paredSelec]->getImagen()->Height+5);

}
//---------------------------------------------------------------------------

void __fastcall TFEditorMapas::BAltoDecClick(TObject *Sender)
{
    if (paredSelec != -1)
        EditAlto->Text = IntToStr(pared[paredSelec]->getImagen()->Height-5);

}
//---------------------------------------------------------------------------

void __fastcall TFEditorMapas::BAnchoIncClick(TObject *Sender)
{
    if (paredSelec != -1)
        EditAncho->Text = IntToStr(pared[paredSelec]->getImagen()->Width+5);
}
//---------------------------------------------------------------------------

void __fastcall TFEditorMapas::BAnchoDecClick(TObject *Sender)
{
    if (paredSelec != -1)
        EditAncho->Text = IntToStr(pared[paredSelec]->getImagen()->Width-5);

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



void __fastcall TFEditorMapas::CBModoChange(TObject *Sender)
{
    switch (CBModo->Items->IndexOf(CBModo->Text))
    {
        case -1:
        {
            IColina->Visible = false;
            IProteger[0]->Visible = false;
            IProteger[1]->Visible = false;
            break;
        }
        case 0:
        {
            IProteger[0]->Visible = false;
            IProteger[1]->Visible = false;
            IColina->Picture->LoadFromFile("imagenes\\varios\\ColinaN.bmp");
            IColina->Transparent=true;
            IColina->AutoSize = true;
            IColina->AutoSize = false;
            IColina->Stretch = true;
            IColina->Width *= TVariables::getResolucionX( );
            IColina->Height *= TVariables::getResolucionY( );
            IColina->Left= IMapa->Left + IMapa->Width/2 - IColina->Width/2;
            IColina->Top= IMapa->Top + IMapa->Height/2 - IColina->Height/2;
            IColina->Visible=true;
            break;
        }
        case 1:
        {
            IColina->Visible = false;
            IProteger[0]->Picture->LoadFromFile("imagenes\\varios\\ProtegerA.bmp");
            IProteger[1]->Picture->LoadFromFile("imagenes\\varios\\ProtegerR.bmp");
            for (int  a = 0;a < 2;a++)
            {
                IProteger[a]->Transparent = true;
                IProteger[a]->AutoSize = true;
                IProteger[a]->AutoSize = false;
                IProteger[a]->Stretch = true;
                IProteger[a]->Width *= TVariables::getResolucionX( );
                IProteger[a]->Height *= TVariables::getResolucionY( );
                IProteger[a]->Visible = true;
                IProteger[a]->Top = IMapa->Top + IMapa->Height / 2 - IProteger[a]->Height/2;
            }
            IProteger[0]->Left = IBorde0->Left + IBorde0->Width;
            IProteger[1]->Left = IBorde2->Left - IProteger[1]->Width;
        }
    }

}
//---------------------------------------------------------------------------



void __fastcall TFEditorMapas::BBorrarParedClick(TObject *Sender)
{
    if ( paredSelec != -1)
    {
        delete pared[paredSelec];
        pared[paredSelec] = NULL;
        sombra->Visible = false;
        contParedes--;
        ordenarParedes();
        paredSelec=-1;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFEditorMapas::Borrarpared1Click(TObject *Sender)
{
    TimerArrastrarPared->Enabled = false;
    BBorrarParedClick(NULL);    
}
//---------------------------------------------------------------------------


void __fastcall TFEditorMapas::CBRioClick(TObject *Sender)
{
    if (paredSelec != -1)
        pared[paredSelec]->setRio(CBRio->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TFEditorMapas::Nuev1Click(TObject *Sender)
{
    for (int i = 0;pared[i] != NULL && i < 20 ;i++)
    {
        delete pared[i];
        pared[i] = NULL;
    }
    contParedes = 0;
    nombreMapa = "\0";
    sombra->Visible = false;
    IBorde0->Picture = NULL;
    IBorde1->Picture = NULL;
    IBorde2->Picture = NULL;
    IBorde3->Picture = NULL;
    IMapa->Picture = NULL;
}
//---------------------------------------------------------------------------

