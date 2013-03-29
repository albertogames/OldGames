#include "UArma.h"

TArma* TArma::armaCrear = NULL;
//ESPADAS
    TArma* crearEspadaDeDragon()
    {
        TArma* arma;
        arma = new TArma();
        arma->setCuerpoACuerpo(true);
        arma->setFuerza(10);
        arma->setAlcance(15);
        arma->setTipo(ESPADA);
        arma->setNombre("Espada de dragón");
        arma->setTexto("wooooooaooooHHHHH  una pedazo de super mega super espadaza!!");
        return arma;
    }
    TArma* crearEspadaLegendaria()
    {
        TArma* arma;
        arma = new TArma();
        arma->setCuerpoACuerpo(true);
        arma->setFuerza(15);
        arma->setAlcance(15);
        arma->setTipo(ESPADA);
        arma->setNombre("Espada legendaria");
        arma->setTexto("wooooooaooooHHHHH  una pedazo de super mega super espadaza legendaria!!");
        return arma;
    }
//ARCOS
    TArma* crearArcoCorto()
    {
        TArma* arma;
        arma = new TArma();
        arma->setDosManos(true);
        arma->setDistancia(true);
        arma->setFuerza(10);
        arma->setAlcance(250);
        arma->setTipo(ARCO);
        arma->setNombre("Arco corto");
        arma->setTexto("Un arkito chikitito");
        return arma;
    }
//OBJETOS
    TArma* crearMascaraDelDiablo()
    {
        TArma* arma;
        arma = new TArma();
        arma->setNombre("Mascara del diablo");
        arma->setTexto("Mascara encantada");
        arma->setTipo(MASCARA);
        return arma;
    }
    TArma* crearBrazaletesDeTormenta()
    {
        TArma* arma;
        arma = new TArma();
        arma->setDosManos(true);
        arma->setDistancia(false);
        arma->setFuerza(25);
        arma->setAlcance(100);
        arma->setTipo(GUANTES);
        arma->setNombre("Brazaletes de tormenta");
        arma->setTexto("");
        return arma;
    }


 