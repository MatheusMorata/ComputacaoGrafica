#include <GL/glut.h>
#include <cmath> // Necessário para funções trigonométricas como sin/cos

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

// Função para desenhar um triângulo
void triangulo(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
        glVertex2f(x1, y1); // Primeiro vértice
        glVertex2f(x2, y2); // Segundo vértice
        glVertex2f(x3, y3); // Terceiro vértice
    glEnd();
}

// Função para desenhar um círculo
void circulo(float cx, float cy, float raio, int segmentos) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segmentos; ++i) {
        float angulo = 2.0f * M_PI * i / segmentos; // Calcula o ângulo do segmento
        float x = cos(angulo) * raio; // Coordenada X do ponto
        float y = sin(angulo) * raio; // Coordenada Y do ponto
        glVertex2f(cx + x, cy + y);   // Adiciona o vértice
    }
    glEnd();
}

// Função de desenho
void desenhar() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha um retângulo
    glColor3f(0.0, 1.0, 0.0); // Verde
    retangulo(0.2, 0.2, 0.6, 0.3);

    // Desenha um triângulo
    glColor3f(1.0, 0.0, 0.0); // Vermelho
    triangulo(-0.5, -0.5, 0.0, 0.5, 0.5, -0.5);

    // Desenha um círculo
    glColor3f(0.0, 0.0, 1.0); // Azul
    circulo(-0.3, -0.3, 0.2, 50); // 50 segmentos para suavizar o círculo

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
