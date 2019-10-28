#include "bib.h"
#include "globalVariaveis.h"

using namespace std;
/**************************************************************
                FUNCOES GLOBAIS GLM (IMPLEMENTACAO)
**************************************************************/
void drawmodelSky(){

    if(!skyModel){
        skyModel = glmReadOBJ("assets/obj/arvore/Tree/Tree.obj");
        glmScale(skyModel, 200.0);
        if(!skyModel)
            exit(0);
        glmUnitize(skyModel);
        glmFacetNormals(skyModel);
        glmVertexNormals(skyModel, 90.0, 1);   //(model, angle, bool keep_existing)
    }

    glmDraw(skyModel, GLM_SMOOTH | GLM_TEXTURE | GLM_COLOR);
}

/**************************************************************
                OUTRAS FUNCOES GLOBAIS (IMPLEMENTACAO)
**************************************************************/
void HitBox(int x, int y, int largura, int altura){
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0);  glVertex3f(-largura+x, y, 0);
        glTexCoord2f(1, 0); glVertex3f(largura+x, y, 0);
        glTexCoord2f(1, 1); glVertex3f(largura+x, altura+y, 0);
        glTexCoord2f(0, 1);  glVertex3f(-largura+x, altura+y, 0);
    glEnd();
}

void HitBox2(int x, int y, int largura, int altura){
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0);  glVertex3f(x, y, 0);
        glTexCoord2f(1, 0); glVertex3f(largura+x, y, 0);
        glTexCoord2f(1, 1); glVertex3f(largura+x, altura+y, 0);
        glTexCoord2f(0, 1);  glVertex3f(x, altura+y, 0);
    glEnd();
}

void tocar_musica(char const nome[40], int loop){
    Mix_Chunk *som = NULL;
    int canal;
    int canal_audio=2;
    int taxa_audio = 22050;
    Uint16 formato_audio = AUDIO_S16SYS;
    int audio_buffers = 4096;
    if(Mix_OpenAudio(taxa_audio, formato_audio, canal_audio, audio_buffers) != 0)
    {
        printf("Não pode inicializar audio: %s\n", Mix_GetError());
    }
    som = Mix_LoadWAV(nome);
    if(som == NULL)
    {
        printf("Não pode inicializar audio: %s\n", Mix_GetError());
    }
    Mix_HaltChannel(-1);
    canal = Mix_PlayChannel( -1, som, loop);
    if(canal == -1)
    {
        printf("Não pode inicializar audio: %s\n", Mix_GetError());
    }
}

void parar_musica()
{
    Mix_HaltChannel(-1);
}

void ativaSom(){
    som = true;
}

void desativaSom(){
    som = false;
}

void pausar(){
    pause = true;
}

void despausar(){
    pause = false;
}

/******************************************************************
                IMPLEMENTACAO DAS FUNCOES GLOBAIS
******************************************************************/

void atualizaDirecaoCamera() {
    direcaoCamera = sub(&alvoCamera, &posicaoCamera);
}

void atualizaAlvoCamera() {
    alvoCamera = add(&posicaoCamera, &direcaoCamera);
}

GLuint carregaTextura(const char* arquivo) {
    GLuint idTextura = SOIL_load_OGL_texture(
                           arquivo,
                           SOIL_LOAD_AUTO,
                           SOIL_CREATE_NEW_ID,
                           SOIL_FLAG_INVERT_Y
                       );

    if (idTextura == 0) {
        cout <<"Erro do SOIL: " << SOIL_last_result() << endl;
    }

    return idTextura;
}

void mouse(int button, int state, int x, int y) {

}

void redimensionar(int width, int height) {
    if (hud.getTelaAtual() == 0 || hud.getTelaAtual() == 1 || hud.getTelaAtual() == 2 || hud.getTelaAtual() == 3 ||
        hud.getTelaAtual() == 5){

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, hud.getScreenSizeX(), 0, hud.getScreenSizeY() , -1, 1);
        //glOrtho(-2, 2, -2, 2, -1.0, 1.0);
        float razaoAspectoJanela = ((float)width)/height;
        //cout << hud.getScreenSizeX() << " " << hud.getScreenSizeY() << endl;
        float razaoAspectoMundo = ((float) hud.getScreenSizeX())/hud.getScreenSizeY();
        // se a janela está menos larga
        if (razaoAspectoJanela < razaoAspectoMundo) {
            // vamos colocar barras verticais (acima e abaixo)
            float hViewport = width / razaoAspectoMundo;
            float yViewport = (height - hViewport)/2;
            glViewport(0, yViewport, width, hViewport);
        }
        // se a janela está mais larga (achatada) do que o mundo (16:9)...
        else if (razaoAspectoJanela > razaoAspectoMundo) {
        // vamos colocar barras horizontais (esquerda e direita)
            float wViewport = ((float)height) * razaoAspectoMundo;
            float xViewport = (width - wViewport)/2;
            glViewport(xViewport, 0, wViewport, height);
        } else {
            glViewport(0, 0, width, height);
        }

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    else if (hud.getTelaAtual() == 4){
        glViewport(0, 0, hud.getScreenSizeX(), hud.getScreenSizeY());
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, ((float)hud.getScreenSizeX())/hud.getScreenSizeY(), 0.1, 4000.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
}

void inicializa(){
    glClearColor(1, 1, 1, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    hud.inicializaTexturas();
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
}

void inicializaJogo(){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glShadeModel(GL_FLAT);

    vec4 luzAmbiente = {{{ 0.3, 0.3, 0.3, 1.0 }}};
    vec4 luzDifusaEspecular = {{{ 1.0, 1.0, 1.0, 0.0 }}};
    vec4 luzPosicao = {{{-1.0, -1.0, 0.0, 0.0 }}};
    vec4 ambienteGlobal = {{{ 0.3, 0.3, 0.3, 1.0 }}};
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente.v);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusaEspecular.v);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzDifusaEspecular.v);
    glLightfv(GL_LIGHT0, GL_POSITION, luzPosicao.v);

    glEnable(GL_LIGHT0);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambienteGlobal.v);

    vec4 materialAmbienteDifusa = {{{0.42, 0.27, 0.07, 1.0}}};
    vec4 materialEspecular = {{{ 0.1, 0.1, 0.1, 1.0 }}};
    float materialExpoente = 20.0;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialAmbienteDifusa.v);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialEspecular.v);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialExpoente);

    // configura a posição e alvo inicial da câmera
    posicaoCamera.x = 0;
    posicaoCamera.y = 5;
    posicaoCamera.z = 30;
    alvoCamera.x = 0;
    alvoCamera.y = 0;
    alvoCamera.z = 0;
    atualizaDirecaoCamera();

    up.x = 0;
    up.y = 1;
    up.z = 0;
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glColor3f (1, 1, 1);

    switch(hud.getTelaAtual()){
    case 0:
        hud.showSplashScreen();
        break;
    case 1:
        hud.showMenu();
        break;
    case 2:
        hud.showMenuCreditos();
        break;
    case 3:
        hud.showMenuOpcoes();
        break;
    case 4:
        hud.showJogo();
        break;
    case 5:
        hud.showTelaSaida();
        break;
    default:
        break;
    }

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
    keys[key] = TRUE;
    switch(key){
    case 27:
        if (hud.getTelaAtual() == hud.TELA_SAIDA){
            exit(0);
        } else {
            hud.setTelaAtual(hud.TELA_SAIDA);
        }

        break;
    case 'm':
        if (hud.getTelaAtual() == hud.MENU || hud.getTelaAtual() == hud.JOGO || hud.getTelaAtual() == hud.MENU_OPCOES ||
            hud.getTelaAtual() == hud.MENU_CREDITOS || hud.getTelaAtual() == hud.SPLASHSCREEN || hud.getTelaAtual() == hud.TELA_SAIDA){

                hud.setTelaAtual(hud.MENU);
        }
        break;
    case 'o':
        if (hud.getTelaAtual() == hud.MENU){
            hud.setTelaAtual(hud.MENU_OPCOES);
        }
        break;
    case 'j':
        if (hud.getTelaAtual() == hud.MENU){
            hud.setTelaAtual(hud.JOGO);
            inicializaJogo();
        }
        break;
    case 'c':
    case 'C':
        posicaoCamera.x = 0;
        posicaoCamera.y = 30;
        posicaoCamera.z = 0;
        alvoCamera.x = 0;
        alvoCamera.y = 0;
        alvoCamera.z = 0;
        direcaoCamera.x = 0;
        direcaoCamera.y = -1;
        direcaoCamera.z = 0.5f;
        atualizaAlvoCamera();
    default:
        break;
    }
    //glutReshapeWindow(hud.getScreenSizeX(), hud.getScreenSizeY());
    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y){
    keys[key] = FALSE;
}

void specialInput(int key, int x, int y) {
}

void atualizaCena(int periodo){
    vec3 deslocamento;
    vec3 temp1, temp2;

    if (keys['w'] || keys['W']) {
        temp1 = normalize(&direcaoCamera);
        posicaoCamera = add(&posicaoCamera, &temp1);
        atualizaAlvoCamera();
    } else if (keys['s'] || keys['S']) {
        temp1 = normalize(&direcaoCamera);
        posicaoCamera = sub(&posicaoCamera, &temp1);
        atualizaAlvoCamera();
    }

    if (keys['d'] || keys['D']) {
        temp1 = cross(&direcaoCamera, &up);
        deslocamento = normalize(&temp1);
        temp2 = mult(&deslocamento, 1);
        direcaoCamera = add(&direcaoCamera, &temp2);
        atualizaAlvoCamera();
    } else if (keys['a'] || keys['A']) {
        temp1 = cross(&direcaoCamera, &up);
        deslocamento = normalize(&temp1);
        temp2 = mult(&deslocamento, 1);
        direcaoCamera = sub(&direcaoCamera, &temp2);
        atualizaAlvoCamera();
    }

    glutPostRedisplay();
    glutTimerFunc(periodo, atualizaCena, periodo);
}

void posicionaCamera(int x, int y) {

    glutPostRedisplay();
}

/**************************************************************
                CLASS HUD (IMPLEMENTACAO)
**************************************************************/
HUD::HUD(int screenSizeX, int screenSizeY, int screenInitPositionX, int screenInitPositionY, int telaAtual){
        this->screenSizeX = screenSizeX;
        this->screenSizeY = screenSizeY;
        this->screenInitPositionX = screenInitPositionX;
        this->screenInitPositionY = screenInitPositionY;
}

int HUD::getScreenInitPositionX(){
    return this->screenInitPositionX;
}

int HUD::getScreenInitPositionY(){
    return this->screenInitPositionY;
}

int HUD::getScreenSizeX(){
    return this->screenSizeX;
}

int HUD::getScreenSizeY(){
    return this->screenSizeY;
}

int HUD::getTelaAtual(){
    return this->telaAtual;
}

int HUD::getModoCamAtual(){
    return this->modoCamAtual;
}


void HUD::escreveTexto(void * font, char *s, float x, float y, float z) {
    int i;
    glRasterPos3f(x, y, z);

    for (i = 0; i < strlen(s); i++) {
        glutBitmapCharacter(font, s[i]);
    }
}

void HUD::mudaTela(Tela novaTela){
    this->telaAtual = novaTela;
}

void HUD::showSplashScreen(){
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_NORMALIZE);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHT0);
    glColor3f(0, 0, 0);
    hud.escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24, "SplashScreen", 100, 100, 0);
}

void HUD::showMenu(){
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_NORMALIZE);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHT0);
    glColor3f(0, 0, 0);
    hud.escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24, "Menu", 100, 100, 0);
}

void HUD::showMenuCreditos(){
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_NORMALIZE);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHT0);
    glColor3f(0, 0, 0);
    hud.escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24, "Creditos", 100, 100, 0);
}

void HUD::showMenuOpcoes(){
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_NORMALIZE);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHT0);
    glColor3f(0, 0, 0);
    hud.escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24, "Opcoes", 100, 100, 0);
}

void HUD::showJogo(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(posicaoCamera.x, posicaoCamera.y, posicaoCamera.z,
              alvoCamera.x, alvoCamera.y, alvoCamera.z,
              0.0, 1.0, 0.0);
    printf("%f %f %f\n", posicaoCamera.x, posicaoCamera.y, posicaoCamera.z);

    glPushMatrix();
    glTranslatef(500, 500, 0);
    glScalef(100, 100, 100);
    drawmodelSky();

    glPopMatrix();
}

void HUD::showTelaSaida() {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_NORMALIZE);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHT0);
    glColor3f(0, 0, 0);
    hud.escreveTexto(GLUT_BITMAP_TIMES_ROMAN_24, "Saida", 100, 100, 0);
}

void HUD::setTelaAtual(int novaTela){
    this->telaAtual = novaTela;
}

void HUD::setModoCamAtual(int modoCam){
    this->modoCamAtual = modoCam;
}

void HUD::inicializaTexturas(){
}

/**************************************************************
                 CLASS COORDENADA (IMPLEMENTACAO)
**************************************************************/
int Coordenada::getX(){
    return this->x;
}

int Coordenada::getY(){
    return this->y;
}

int Coordenada::getZ(){
    return this->z;
}

int Coordenada::getAltura(){
    return this->altura;
}

int Coordenada::getLargura(){
    return this->largura;
}

void Coordenada::setX(int x){
    this->x = x;
}

void Coordenada::setY(int y){
    this->y = y;
}

void Coordenada::setZ(int y){
    this->z = z;
}

void Coordenada::setAltura(int altura){
    this->altura = altura;
}

void Coordenada::setLargura(int largura){
    this->largura = largura;
}

