#include <GL/glut.h>

const char* tituloJanela = "Janela GLUT Básica";
const int larguraJanela = 800; // Largura da janela
const int alturaJanela = 600;  // Altura da janela

// Função para desenhar um retângulo
void retangulo(float x, float y, float largura, float altura) {
    glBegin(GL_QUADS);
        glVertex2f(x, y);                         // Vértice inferior esquerdo
        glVertex2f(x + largura, y);              // Vértice inferior direito
        glVertex2f(x + largura, y + altura);     // Vértice superior direito
        glVertex2f(x, y + altura);               // Vértice superior esquerdo
    glEnd();
}

// Função de desenho
void desenhar() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha um retângulo
    glColor3f(0.0, 1.0, 0.0); // Verde
    retangulo(0.2, 0.2, 0.6, 0.3);

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
