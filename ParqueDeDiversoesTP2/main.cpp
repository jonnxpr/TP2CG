/****************************************************************************
*                     PARQUE DE DIVERSÕES V.01                              *
* --------------------------------------------------------------------------*
* @AUTHOR: Jonathan Douglas Diego Tavares                                   *
* @TEACHER: Flávio Coutinho                                                 *
* @ENGINE: OpenGL + Glut + Glew + SOIL                                      *
* @LINGUAGEM: C++                                                           *
* @DATE: 07 de Setembro de 2019                                             *
****************************************************************************/

#include "bib.h"

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitContextVersion(2, 1);
    glutInitWindowSize(1360, 768);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("TP2 - Parque de Diversões - Copyright Tavares Games");

    inicializa();

    glutReshapeFunc(redimensionar);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutTimerFunc(33, atualizaCena, 33);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(posicionaCamera);
    glutSpecialFunc(specialInput);

    glutMainLoop();
    return 0;
}
