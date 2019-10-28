#ifndef BIB_H_INCLUDED
#define BIB_H_INCLUDED

#define TRUE 1
#define FALSE 0

#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "glm.h"
#include "glmint.h"
#include "vetor.h"

using namespace std;

/**************************************************************
Biblioteca de Classes e Funções para o Game Parque de Diversões.
Versão: 1.0 Alpha

@author: Jonathan Douglas Diego Tavares
@Professor: Flávio Coutinho
**************************************************************/

using namespace std;

/**************************************************************
                        CLASS HUD
    Função: Responsavel por controlar a Interface do Usuário
**************************************************************/
class HUD{
public:
    enum Tela { SPLASHSCREEN = 0, MENU = 1, MENU_CREDITOS = 2, MENU_OPCOES = 3, JOGO = 4, TELA_SAIDA = 5};
    enum ModoCamera {FIRST_PERSON = 0, THIRD_PERSON = 1};
    HUD(int screenSizeX, int screenSizeY, int screenInitPositionX, int screenInitPositionY, int telaAtual);

    void inicializaTexturas();
    void mudaTela(Tela novaTela);
    void showSplashScreen();
    void showMenu();
    void showMenuCreditos();
    void showMenuOpcoes();
    void showJogo();
    void showTelaSaida();
    int getScreenSizeX();
    int getScreenSizeY();
    int getScreenInitPositionX();
    int getScreenInitPositionY();
    void setTelaAtual(int novaTela);
    int getTelaAtual();
    void setModoCamAtual(int modoCam);
    int getModoCamAtual();
    void escreveTexto(void * font, char *s, float x, float y, float z);
protected:
    int telaAtual, modoCamAtual;
    int screenSizeX, screenSizeY;
    int screenInitPositionX, screenInitPositionY;
};

/**************************************************************
                        CLASS COORDENADA
    Função: Responsavel por controlar a Interface do Usuário
**************************************************************/

class Coordenada{
public:
    int getX();
    int getY();
    int getZ();
    int getAltura();
    int getLargura();
    void setX(int x);
    void setY(int y);
    void setZ(int y);
    void setAltura(int altura);
    void setLargura(int largura);
protected:
    int x, y, z;
    int altura, largura;
};

/**************************************************************
                Prototipos das Funcoes Globais
**************************************************************/
void inicializa();
void inicializaJogo();
void redimensionar(int width, int height);
void display();
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void atualizaCena(int periodo);
void mouse(int button, int state, int x, int y);
void posicionaCamera(int x, int y);
void specialInput(int key, int x, int y);
GLuint carregaTextura(const char* arquivo);
void drawmodelSky();
void atualizaDirecaoCamera();

void atualizaAlvoCamera();


#endif // BIB_H_INCLUDED
