#include <GL/glut.h>

const char* tituloJanela = "Janela GLUT Básica";
const int larguraJanela = 800; 
const int alturaJanela = 600;  
// Função de desenho
void desenhar() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0); // Vermelho
        glVertex2f(-0.5, -0.5);
        glColor3f(0.0, 1.0, 0.0); // Verde
        glVertex2f(0.5, -0.5);
        glColor3f(0.0, 0.0, 1.0); // Azul
        glVertex2f(0.0, 0.5);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    // Inicializa o GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(larguraJanela, alturaJanela);

    // Usa a variável para o título da janela
    glutCreateWindow(tituloJanela);

    // Define a cor de fundo
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Callback de desenho
    glutDisplayFunc(desenhar);

    // Inicia o loop principal
    glutMainLoop();

    return 0;
}
