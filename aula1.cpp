#include <GL/glut.h>
#include <cmath> // Necessário para funções trigonométricas como sin/cos

const char* tituloJanela = "Janela GLUT Básica";
const int larguraJanela = 800; // Largura da janela
const int alturaJanela = 600;  // Altura da janela

float corFundo[3] = { 0.0, 0.0, 0.0 }; // Cor inicial do fundo (preto)

// Função para desenhar um retângulo
void retangulo(float x, float y, float largura, float altura) {
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + largura, y);
        glVertex2f(x + largura, y + altura);
        glVertex2f(x, y + altura);
    glEnd();
}

// Função para desenhar um triângulo
void triangulo(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    glEnd();
}

// Função para desenhar um círculo
void circulo(float cx, float cy, float raio, int segmentos) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segmentos; ++i) {
        float angulo = 2.0f * M_PI * i / segmentos;
        float x = cos(angulo) * raio;
        float y = sin(angulo) * raio;
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Função de desenho
void desenhar() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 1.0, 0.0); // Verde
    retangulo(0.2, 0.2, 0.6, 0.3);

    glColor3f(1.0, 0.0, 0.0); // Vermelho
    triangulo(-0.5, -0.5, 0.0, 0.5, 0.5, -0.5);

    glColor3f(0.0, 0.0, 1.0); // Azul
    circulo(-0.3, -0.3, 0.2, 50);

    glFlush();
}

// Callback para eventos de teclado
void teclado(unsigned char tecla, int x, int y) {
    if (tecla == 'm' || tecla == 'M') { // Se a tecla 'm' ou 'M' for pressionada
        // Altera a cor do fundo para valores aleatórios
        corFundo[0] = static_cast<float>(rand()) / RAND_MAX;
        corFundo[1] = static_cast<float>(rand()) / RAND_MAX;
        corFundo[2] = static_cast<float>(rand()) / RAND_MAX;

        glClearColor(corFundo[0], corFundo[1], corFundo[2], 1.0); // Atualiza a cor de fundo
        glutPostRedisplay(); // Solicita o redesenho da janela
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(larguraJanela, alturaJanela);
    glutCreateWindow(tituloJanela);

    glClearColor(corFundo[0], corFundo[1], corFundo[2], 1.0);

    glutDisplayFunc(desenhar);
    glutKeyboardFunc(teclado); // Configura o callback para eventos de teclado

    glutMainLoop();

    return 0;
}
