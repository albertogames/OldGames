//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("CardsWar.res");
USEFORM("Formularios\FormMenuPrincipal.cpp", FMenuPrincipal);
USEFORM("Formularios\FormCarta.cpp", FCarta);
USEFORM("Formularios\FormMensaje.cpp", FMensaje);
USEFORM("Formularios\FormJugador.cpp", FJugador);
USEFORM("Formularios\FormEmpezar.cpp", FEmpezar);
USEFORM("Formularios\FormJuego.cpp", FJuego);
USEFORM("Formularios\FormCementerio.cpp", FCementerio);
USEFORM("Formularios\FormPersonaje.cpp", FPersonaje);
USEFORM("Formularios\FormArma.cpp", FArma);
USEFORM("Formularios\FormEncantamientos.cpp", FEncantamientos);
USEFORM("Formularios\FormEditorMapas.cpp", FEditorMapas);
USEFORM("Formularios\FormMenuMazo.cpp", FMenuMazo);
USEFORM("Formularios\FormCreditos.cpp", FCreditos);
USEUNIT("Unidades\UArma.cpp");
USEUNIT("Unidades\UCarta.cpp");
USEUNIT("Unidades\UPared.cpp");
USEUNIT("Unidades\UPersonaje.cpp");
USEUNIT("Unidades\UVariables.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->CreateForm(__classid(TFMenuPrincipal), &FMenuPrincipal);
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
