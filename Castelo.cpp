#include <GL/glut.h>


void init(void){

    glClearColor(1.0, 1.0, 1.0, 1.0); // Define cor inicial (branco)

    // Define o sistema de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1,-1, 1, -1, 1);
}

void display(){

    glClear(GL_COLOR_BUFFER_BIT);

    /*
        DESENHA AS FIGURAS AQUI
    */

    quadrado();

    glFlush();
}

int main(int argc, char** argv){
    int janela_x = 800; 
    int janela_y = 800;
    int inicial_x = 200;
    int inicial_y = 200;


    glutInit(&argc, argv);  // Inicializa o GLUT
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(janela_x, janela_y); // Tamanho da janela
    glutInitWindowPosition(inicial_x, inicial_y); // Posição inicial da janela
    glutCreateWindow("Castelo de Itaipava"); // Título da janela
    init();
    glutDisplayFunc(display);
    glutMainLoop(); // Inicia o looping de desenho

    return 0;
}
