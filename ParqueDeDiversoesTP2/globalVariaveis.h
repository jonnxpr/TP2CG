#ifndef GLOBALVARIAVEIS_H_INCLUDED
#define GLOBALVARIAVEIS_H_INCLUDED

#include "bib.h"
/**************************************************************
                        VARIAVEIS GLOBAIS
**************************************************************/
//variavel de controle do tamanho da tela

//Objetos
HUD hud(1360, 768, 0, 0, 0);

//Texturas

//GLM_Models
GLMmodel *modelTeste = NULL;
GLMmodel *skyModel = NULL;

//variavel de controle do teclado
unsigned char keys[256];

//variavel de controle do pause
bool pause;

//variavel de controle do som
bool som;

//variavel de controle da camera
vec3 posicaoCamera;
vec3 alvoCamera;
vec3 direcaoCamera;
vec3 up;
#endif // GLOBALVARIAVEIS_H_INCLUDED
