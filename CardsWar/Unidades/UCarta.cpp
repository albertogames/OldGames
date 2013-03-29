#include "UCarta.h"

#include "UPersonaje.h"
#include "FormJuego.h"
#include "UVariables.h"

#include "FormCementerio.h"
#include "FormEncantamientos.h"

// --------------       MANA       ----------------
    void habilidad_Mana()
    {
    }
    TCarta* crearCarta_Mana()
    {
        void (*h)() = habilidad_Mana;
        return (new TCarta("Mana",0,"Imagenes\\Cartas\\Mana.bmp",h,mana));
    }
// --------------       CRIATURAS       ----------------

//Esqueleto
    void habilidad_DragonEsqueleto()
    {
        TVariables::setCriaturaInvocar( TTio::crearDragonEsqueleto() );
    }
    TCarta* crearCarta_DragonEsqueleto()
    {
        void (*h)() = habilidad_DragonEsqueleto;
        return ( new TCarta("Dragon esqueleto",3,"Imagenes\\cartas\\Criaturas\\DragonEsqueleto.bmp",h,criatura) );
    }


//Gigante de las cavernas
    void habilidad_GiganteDeLasCavernas()
    {
        TVariables::setCriaturaInvocar( TTio::crearGigante() );
    }
    TCarta* crearCarta_GiganteDeLasCavernas()
    {
        void (*h)() = habilidad_GiganteDeLasCavernas;
        return ( new TCarta("Gigante de las cavernas",5,"Imagenes\\cartas\\Criaturas\\GiganteDeLasCavernas.bmp",h, criatura) );
    }
//Arquero solitario
    void habilidad_ArqueroSolitario()
    {
        TVariables::setCriaturaInvocar( TTio::crearArqueroSolitario() );
    }
    TCarta* crearCarta_ArqueroSolitario()
    {
        void (*h)() = habilidad_ArqueroSolitario;
        return ( new TCarta("Arquero solitario",4,"Imagenes\\cartas\\Criaturas\\ArqueroSolitario.bmp",h, criatura) );
    }
//Enano con armadura
    void habilidad_EnanoConArmadura()
    {
        TVariables::setCriaturaInvocar( TTio::crearEnanoConArmadura() );
    }
    TCarta* crearCarta_EnanoConArmadura()
    {
        void (*h)() = habilidad_EnanoConArmadura;
        return ( new TCarta("Enano con armadura",3,"Imagenes\\cartas\\Criaturas\\EnanoConArmadura.bmp",h, criatura) );
    }
//Murcielago
    void habilidad_Murcielago()
    {
        TVariables::setCriaturaInvocar( TTio::crearMurcielago() );
    }
    TCarta* crearCarta_Murcielago()
    {
        void (*h)() = habilidad_Murcielago;
       return ( new TCarta("Murcielago",1,"Imagenes\\cartas\\Criaturas\\Murcielago.bmp",h, criatura) );
    }
//Tortuga gigante
    void habilidad_TortugaGigante()
    {
        TVariables::setCriaturaInvocar( TTio::crearTortugaGigante() );
    }
    TCarta* crearCarta_TortugaGigante()
    {
        void (*h)() = habilidad_TortugaGigante;
        return ( new TCarta("Tortuga gigante",3,"Imagenes\\cartas\\Criaturas\\TortugaGigante.bmp",h, criatura) );
    }
//Zombi siniestro
    void habilidad_ZombiSiniestro()
    {
        TVariables::setCriaturaInvocar( TTio::crearZombiSiniestro() );
    }
    TCarta* crearCarta_ZombiSiniestro()
    {
        void (*h)() = habilidad_ZombiSiniestro;
        return ( new TCarta("Zombi siniestro",4,"Imagenes\\cartas\\Criaturas\\ZombiSiniestro.bmp",h, criatura) );
    }
//Aparicion del mal
    void habilidad_AparicionDelMal()
    {
        TVariables::setCriaturaInvocar( TTio::crearAparicionDelMal() );
    }
    TCarta* crearCarta_AparicionDelMal()
    {
        void (*h)() = habilidad_AparicionDelMal;
        return ( new TCarta("Aparicion del mal",3,"Imagenes\\cartas\\Criaturas\\AparicionDelMal.bmp",h, criatura) );
    }
//Aparicion del mal
    void habilidad_JineteOscuro()
    {
        TVariables::setCriaturaInvocar( TTio::crearJineteOscuro() );
    }
    TCarta* crearCarta_JineteOscuro()
    {
        void (*h)() = habilidad_JineteOscuro;
        return ( new TCarta("Jinete oscuro",4,"Imagenes\\cartas\\Criaturas\\JineteOscuro.bmp",h, criatura) );
    }
//Hombre lobo
    void habilidad_HombreLobo()
    {
        TVariables::setCriaturaInvocar( TTio::crearHombreLobo() );
    }
    TCarta* crearCarta_HombreLobo()
    {
        void (*h)() = habilidad_HombreLobo;
        return ( new TCarta("Hombre lobo",5,"Imagenes\\cartas\\Criaturas\\HombreLobo.bmp",h, criatura) );
    }
//Reina de los zombis
    void habilidad_ReinaDeLosZombis()
    {
        TVariables::setCriaturaInvocar( TTio::crearReinaDeLosZombis() );
    }
    TCarta* crearCarta_ReinaDeLosZombis()
    {
        void (*h)() = habilidad_ReinaDeLosZombis;
        return ( new TCarta("Reina de los zombis",7,"Imagenes\\cartas\\Criaturas\\ReinaDeLosZombis.bmp",h, criatura) );
    }
//Curandera
    void habilidad_Curandera()
    {
        TVariables::setCriaturaInvocar( TTio::crearCurandera() );
    }
    TCarta* crearCarta_Curandera()
    {
        void (*h)() = habilidad_Curandera;
        return ( new TCarta("Curandera",2,"Imagenes\\cartas\\Criaturas\\Curandera.bmp",h, criatura) );
    }
//Hada de la noche
    void habilidad_HadaDeLaNoche()
    {
        TVariables::setCriaturaInvocar( TTio::crearHadaDeLaNoche() );
    }
    TCarta* crearCarta_HadaDeLaNoche()
    {
        void (*h)() = habilidad_HadaDeLaNoche;
        return ( new TCarta("Hada de la noche",1,"Imagenes\\cartas\\Criaturas\\HadaDeLaNoche.bmp",h, criatura) );
    }
// Orco de hierro
    void habilidad_OrcoDeHierro()
    {
        TVariables::setCriaturaInvocar( TTio::crearOrcoDeHierro() );
    }
    TCarta* crearCarta_OrcoDeHierro()
    {
        void (*h)() = habilidad_OrcoDeHierro;
        return ( new TCarta("Orco de hierro",2,"Imagenes\\cartas\\Criaturas\\OrcoDeHierro.bmp",h, criatura) );
    }
// Mago del dragon
    void habilidad_MagoDelDragon()
    {
        TVariables::setCriaturaInvocar( TTio::crearMagoDelDragon() );
    }
    TCarta* crearCarta_MagoDelDragon()
    {
        void (*h)() = habilidad_MagoDelDragon;
        return ( new TCarta("Mago del dragon",6,"Imagenes\\cartas\\Criaturas\\MagoDelDragon.bmp",h, criatura) );
    }
// Mago del dragon
    void habilidad_ElfaExploradora()
    {
        TVariables::setCriaturaInvocar( TTio::crearElfaExploradora() );
    }
    TCarta* crearCarta_ElfaExploradora()
    {
        void (*h)() = habilidad_ElfaExploradora;
        return ( new TCarta("Elfa exploradora",2,"Imagenes\\cartas\\Criaturas\\ElfaExploradora.bmp",h, criatura) );
    }

// --------------       OBJETOS       ----------------
//Espada de dragón
    void habilidad_EspadaDeDragon()
    {
        TArma::setArmaCrear(crearEspadaDeDragon());
    }
    TCarta* crearCarta_EspadaDeDragon()
    {
        void (*h)() = habilidad_EspadaDeDragon;
        return ( new TCarta("Espada de dragon",1,"Imagenes\\cartas\\Objetos\\EspadaDeDragon.bmp",h, objeto) );
    }
//Espada legendaria
    void habilidad_EspadaLegendaria()
    {
        TArma::setArmaCrear( crearEspadaLegendaria() ) ;
    }
    TCarta* crearCarta_EspadaLegendaria()
    {
        void (*h)() = habilidad_EspadaLegendaria;
        return ( new TCarta("Espada legendaria",2,"Imagenes\\cartas\\Objetos\\EspadaLegendaria.bmp",h, objeto) );
    }
//Arco corto
    void habilidad_ArcoCorto()
    {
        TArma::setArmaCrear( crearArcoCorto() );
    }
    TCarta* crearCarta_ArcoCorto()
    {
        void (*h)() = habilidad_ArcoCorto;
        return ( new TCarta("Arco corto",1,"Imagenes\\cartas\\Objetos\\ArcoCorto.bmp",h, objeto) );
    }
//Mascara del diablo
    void habilidad_MascaraDelDiablo()
    {
        TArma::setArmaCrear( crearMascaraDelDiablo() );
    }
    TCarta* crearCarta_MascaraDelDiablo()
    {
        void (*h)() = habilidad_MascaraDelDiablo;
        return ( new TCarta("Mascara del diablo",1,"Imagenes\\cartas\\Objetos\\MascaraDelDiablo.bmp",h, objeto) );
    }
//Brazaletes de tormenta
    void habilidad_BrazaletesDeTormenta()
    {
        TArma::setArmaCrear( crearBrazaletesDeTormenta() );
    }
    TCarta* crearCarta_BrazaletesDeTormenta()
    {
        void (*h)() = habilidad_BrazaletesDeTormenta;
        return ( new TCarta("Brazaletes de tormenta",2,"Imagenes\\cartas\\Objetos\\BrazaletesDeTormenta.bmp",h, objeto) );
    }



// --------------       HECHIZOS       ----------------
//RegenerarAlmas
    void habilidad_RegenerarAlmas()
    {
        //carta = mano[turno][cartaSelec];
        if ( TFJuego::getNumCartasCem(0) + TFJuego::getNumCartasCem(1) > 0 )
        {
            FJuego->setUsaHechizo(true);
            FJuego->descartar();
            if (FJuego->getNumCartasMano(TFJuego::getTurno()) == 6)
                ShowMessage("Solo podras recuperar una criatura ya que tienes demasiadas cartas en tu mano");
        }
        else
            ShowMessage("No hay cartas en ningun cementerio");

        if (TFJuego::getNumCartasCem(TFJuego::getTurno()) > 0)
        {
            TFJuego::setTurnoC(TFJuego::getTurno());
            FCementerio= new TFCementerio(Application);
            FCementerio->setRecuperarCriaturas(1);
            FCementerio->ShowModal();
            FCementerio->setRecuperarCriaturas(0);
        }
        switch (TFJuego::getTurno())
        {
            case 0: {TFJuego::setTurnoC(1);break;}
            case 1: TFJuego::setTurnoC(0);
        }
        if (TFJuego::getNumCartasCem(TFJuego::getTurnoC()) > 0)
        {
            FCementerio= new TFCementerio(Application);
            FCementerio->setRecuperarCriaturas(1);
            FCementerio->ShowModal();
            FCementerio->setRecuperarCriaturas(0);
        }
        FJuego->BCambiarTurno -> Enabled = true;
    }
    TCarta* crearCarta_RegenerarAlmas()
    {
        void (*h)() = habilidad_RegenerarAlmas;
        return ( new TCarta("Regenerar almas",5,"Imagenes\\cartas\\Hechizos\\RegenerarAlmas.bmp",h, hechizo) );
    }
//Preparacion de lucha
    void habilidad_PreparacionDeLucha()
    {
        FJuego->BCambiarTurno->Enabled = true;

        for ( int i = 0; TTio::getTio(TFJuego::getTurno(), i) != NULL; i++ )
        {
            TTio::getTio(TFJuego::getTurno(),i)->iniciar();
        }
        FJuego->setUsaHechizo(true);
    }
    TCarta* crearCarta_PreparacionDeLucha()
    {
        void (*h)() = habilidad_PreparacionDeLucha;
        return ( new TCarta("Preparacion de lucha",3,"Imagenes\\cartas\\Hechizos\\PreparacionDeLucha.bmp",h, hechizo) );
    }
//Escuela de armas
    void habilidad_EscuelaDeArmas()
    {
        FJuego->setEscuelaDeArmas(true);
    }
    TCarta* crearCarta_EscuelaDeArmas()
    {
        void (*h)() = habilidad_EscuelaDeArmas;
        return ( new TCarta("Escuela de armas",2,"Imagenes\\cartas\\Hechizos\\EscuelaDeArmas.bmp",h, hechizo) );
    }
//Dosis de supervivencia
    void habilidad_DosisDeSupervivencia()
    {
        if ( FJuego->getDosisDeSupervivencia() == false )
        {
            FJuego->setDosisDeSupervivencia(true);
        }
    }
    TCarta* crearCarta_DosisDeSupervivencia()
    {
        void (*h)() = habilidad_DosisDeSupervivencia;
        return ( new TCarta("Dosis de supervivencia",1,"Imagenes\\cartas\\Hechizos\\DosisDeSupervivencia.bmp",h, hechizo) );
    }
//Mitosis
    void habilidad_Mitosis()
    {
        FJuego->setMitosis ( true );
    }
    TCarta* crearCarta_Mitosis()
    {
        void (*h)() = habilidad_Mitosis;
        return ( new TCarta("Mitosis",2,"Imagenes\\cartas\\Hechizos\\Mitosis.bmp",h, hechizo) );
    }
//Meteoro
    void habilidad_Meteoro()
    {
        TVariables::setJugadorSelec(0, TFJuego::getTurno()==0 ? 1 : 0 );
        FJuego->BCambiarTurno->Enabled = true;
        FJuego->setDestruirEncantamientos( 1 );
        FEncantamientos = new TFEncantamientos(NULL);
        FEncantamientos->ShowModal();
        if ( FJuego->getDestruirEncantamientos() == 0)
            FJuego->setUsaHechizo( true );
        else
            FJuego->setDestruirEncantamientos( 0 );
    }
    TCarta* crearCarta_Meteoro()
    {
        void (*h)() = habilidad_Meteoro;
        return ( new TCarta("Meteoro",2,"Imagenes\\cartas\\Hechizos\\Meteoro.bmp",h, hechizo) );
    }


// --------------       ENCANTAMIENTOS       ----------------
//Tierras lejanas
    void habilidad_TierrasLejanas()
    {
        if ( FJuego->getDestruirEncantamientos() == false )
        {
            FJuego->setTierrasLejanas( TFJuego::getTurno(), FJuego->getTierrasLejanas( TFJuego::getTurno() ) + 150 );
            FJuego->setUsaHechizo( true );
        }
        else
            FJuego->setTierrasLejanas( TVariables::getJugadorSelec(0) , FJuego->getTierrasLejanas( TVariables::getJugadorSelec(0) ) - 150 );

    }
    TCarta* crearCarta_TierrasLejanas()
    {
        void (*h)() = habilidad_TierrasLejanas;
        return ( new TCarta("Tierras lejanas",2,"Imagenes\\cartas\\Encantamientos\\TierrasLejanas.bmp",h, encantamientos) );
    }
//Heroes
    void habilidad_Heroes()
    {                                 
        if (FJuego->getDestruirEncantamientos() == false  )
        {
            if ( !FJuego->getHeroes( TFJuego::getTurno() ) )
            {
                FJuego->setHeroes( TFJuego::getTurno(), true);
                FJuego->setUsaHechizo( true );
            }
            else
                ShowMessage("Solo puedes tener una en juego");
        }
        else
            FJuego->setHeroes( TVariables::getJugadorSelec(0), false );

    }
    TCarta* crearCarta_Heroes()
    {
        void (*h)() = habilidad_Heroes;
        return ( new TCarta("Heroes",3,"Imagenes\\cartas\\Encantamientos\\Heroes.bmp",h, encantamientos) );
    }
//Bosque tenebroso
    void habilidad_BosqueTenebroso()
    {                        
        if ( FJuego->getDestruirEncantamientos()  == false )
         {
            FJuego->BCambiarTurno->Enabled = false;
            if ( FJuego->getImagenBT( TFJuego::getTurno() ) == NULL )
            {
                FJuego->setImagenBT( TFJuego::getTurno(), new TImage(NULL) ) ;
                FJuego->getImagenBT( TFJuego::getTurno() )->Picture->LoadFromFile("Imagenes\\varios\\BosqueTenebroso.bmp");
                FJuego->getImagenBT( TFJuego::getTurno() )->Parent = FJuego;
                FJuego->recrear();
                FJuego->getImagenBT( TFJuego::getTurno() )->Visible =true;
                FJuego->getImagenBT( TFJuego::getTurno() )->AutoSize =true;
                FJuego->getImagenBT( TFJuego::getTurno() )->Transparent = true;
                FJuego->getImagenBT( TFJuego::getTurno() )->Parent = FJuego;
                FJuego->TimerVarios->Enabled = true;
                FJuego->setTurnosBT( TFJuego::getTurno(), 0);
                cambiarRes( FJuego->getImagenBT( TFJuego::getTurno() ) );
                FJuego->setBosqueT(true);
            }
            else
            {
                ShowMessage("Solo puedes tener una en juego");
                FJuego->BCambiarTurno->Enabled = true;
            }
        }
      else
        {
            delete FJuego->getImagenBT( TVariables::getJugadorSelec(0) );
            FJuego->setImagenBT( TVariables::getJugadorSelec(0), NULL );
        }
    }
    TCarta* crearCarta_BosqueTenebroso()
    {
        void (*h)() = habilidad_BosqueTenebroso;
        return ( new TCarta("Bosque tenebroso",3,"Imagenes\\cartas\\Encantamientos\\BosqueTenebroso.bmp",h, encantamientos) );
    }


    TCarta* crearCarta(char* N)
    {
        if ( !strcmp(N, "Dragon esqueleto" ) )          return ( crearCarta_DragonEsqueleto() );         else
        if ( !strcmp(N, "Gigante de las cavernas" ) )   return ( crearCarta_GiganteDeLasCavernas() );    else
        if ( !strcmp(N, "Espada de dragon" ) )          return ( crearCarta_EspadaDeDragon() );          else
        if ( !strcmp(N, "Espada legendaria" ) )         return ( crearCarta_EspadaLegendaria() );        else
        if ( !strcmp(N, "Arquero solitario" ) )         return ( crearCarta_ArqueroSolitario() );        else
        if ( !strcmp(N, "Enano con armadura" ) )        return ( crearCarta_EnanoConArmadura() );        else
        if ( !strcmp(N, "Tierras lejanas" ) )           return ( crearCarta_TierrasLejanas() );          else
        if ( !strcmp(N, "Arco corto" ) )                return ( crearCarta_ArcoCorto() );               else
        if ( !strcmp(N, "Murcielago" ) )                return ( crearCarta_Murcielago() );              else
        if ( !strcmp(N, "Regenerar almas" ) )           return ( crearCarta_RegenerarAlmas() );          else
        if ( !strcmp(N, "Preparacion de lucha" ) )      return ( crearCarta_PreparacionDeLucha() );      else
        if ( !strcmp(N, "Escuela de armas" ) )          return ( crearCarta_EscuelaDeArmas() );          else
        if ( !strcmp(N, "Tortuga gigante" ) )           return ( crearCarta_TortugaGigante() );          else
        if ( !strcmp(N, "Heroes" ) )                    return ( crearCarta_Heroes() );                  else
        if ( !strcmp(N, "Zombi siniestro" ) )           return ( crearCarta_ZombiSiniestro() );          else
        if ( !strcmp(N, "Aparicion del mal" ) )         return ( crearCarta_AparicionDelMal() );         else
        if ( !strcmp(N, "Dosis de supervivencia" ) )    return ( crearCarta_DosisDeSupervivencia() );    else
        if ( !strcmp(N, "Mascara del diablo" ) )        return ( crearCarta_MascaraDelDiablo() );        else
        if ( !strcmp(N, "Mitosis" ) )                   return ( crearCarta_Mitosis() );                 else
        if ( !strcmp(N, "Jinete oscuro" ) )             return ( crearCarta_JineteOscuro() );            else
        if ( !strcmp(N, "Bosque tenebroso" ) )          return ( crearCarta_BosqueTenebroso() );         else
        if ( !strcmp(N, "Hombre lobo" ) )               return ( crearCarta_HombreLobo() );              else
        if ( !strcmp(N, "Reina de los zombis" ) )       return ( crearCarta_ReinaDeLosZombis() );        else
        if ( !strcmp(N, "Brazaletes de tormenta" ) )    return ( crearCarta_BrazaletesDeTormenta() );    else
        if ( !strcmp(N, "Mana") )                       return ( crearCarta_Mana() );                    else
        if ( !strcmp(N, "Curandera") )                  return ( crearCarta_Curandera() );               else
        if ( !strcmp(N, "Hada de la noche") )           return ( crearCarta_HadaDeLaNoche() );           else
        if ( !strcmp(N, "Orco de hierro") )             return ( crearCarta_OrcoDeHierro() );            else
        if ( !strcmp(N, "Mago del dragon") )            return ( crearCarta_MagoDelDragon() );           else
        if ( !strcmp(N, "Elfa exploradora") )           return ( crearCarta_ElfaExploradora() );         else

       /* if ( !strcmp(N, "Meteoro" ) )  */           return ( crearCarta_Meteoro() );
    }
