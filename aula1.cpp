#include <GL/glut.h>

const char* tituloJanela = "Janela GLUT Básica";
const int larguraJanela = 800; // Largura da janela
const int alturaJanela = 600;  // Altura da janela

// Função para desenhar um quadrado
void quadrado(float x, float y, float tamanho) {
    glBegin(GL_QUADS);
        glVertex2f(x, y);                         // Vértice inferior esquerdo
        glVertex2f(x + tamanho, y);              // Vértice inferior direito
        glVertex2f(x + tamanho, y + tamanho);    // Vértice superior direito
        glVertex2f(x, y + tamanho);              // Vértice superior esquerdo
    glEnd();
}

// Função de desenho
void desenhar() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha um quadrado
    glColor3f(1.0, 0.0, 0.0); // Vermelho
    quadrado(-0.5, -0.5, 1.0);

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
