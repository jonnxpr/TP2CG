#ifndef GLOBALVARIAVEIS_H_INCLUDED
#define GLOBALVARIAVEIS_H_INCLUDED
#include "bib.h"
/**************************************************************
                        VARIAVEIS GLOBAIS
**************************************************************/
//variavel de controle do tamanho da tela

//Objetos
HUD hud(1500, 955, 0, 0, 0);

//Texturas

//GLM_Models
GLMmodel *modelTeste = NULL;
GLMmodel *skyModel = NULL;

//variavel de controle do teclado
int keys[256];

//variavel de controle do pause
bool pause;

//variavel de controle do som
bool som;
#endif // GLOBALVARIAVEIS_H_INCLUDED
