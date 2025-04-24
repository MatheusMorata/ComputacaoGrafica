/*

    Carro com movimento, por teclas

*/

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void init();
void display();
int frameNumber = 0;
float velocidadeCarro = 0.0;
float direcaoCarro = 0.0;
bool teclaPressionada = true;

typedef struct {
    float x;
    float tamanho;
} CirculoAzul;

#define MAX_CIRCULOS 10 // Define o número máximo de círculos
float circulosX[MAX_CIRCULOS]; // Posições X dos círculos
float circulosTamanho[MAX_CIRCULOS]; // Tamanhos dos círculos
int numCirculos = 0; // Contador de círculos ativos


void circulo(double radius){
    int d;

    glBegin(GL_POLYGON);
    for(d = 0; d < 32; d++){
        double angle =  (6.14/32) * d;
        glVertex3f(radius*cos(angle), radius*sin(angle), 0);
    }
    glEnd();
}

void quadrado(){
         
    glBegin(GL_POLYGON);
        // Vértices do quadrado
        glVertex3f(1.0, 1.0, 0.0);   
        glVertex3f(-1.0, 1.0, 0.0);  
        glVertex3f(-1.0, -1.0, 0.0);
        glVertex3f(1.0, -1.0, 0.0);
    glEnd();
}

void triangulo(){

    glBegin(GL_POLYGON);
        // Vértices do triângulo
        glVertex3f(0.0, -1.0, 0.0);
        glVertex3f(-1.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
    glEnd();
}

void roda() {
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(1.0, 0.8, 0.0);
        glScaled(0.8, 0.8, 0.0);
        circulo(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.8, 0.8, 0.8);
        glTranslated(1.0, 0.8, 0.0);
        glScaled(0.6, 0.6, 0.0);
        circulo(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(1.0, 0.8, 0.0);
        glScaled(0.2, 0.2, 0.0);
        circulo(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0); 
        glTranslated(1.0, 0.8, 0.0);
        if(teclaPressionada){
            glRotated( direcaoCarro * (frameNumber * 5.0), 0.0, 0.0, 1.0);
        }  

        glBegin(GL_LINES);
        for (int i = 0; i < 8; i++) {
            float angle = i * M_PI / 4.0; 
            float x = 0.8 * cos(angle);  
            float y = 0.8 * sin(angle);
            glVertex2f(0.0f, 0.0f);       
            glVertex2f(x, y);           
        }
        glEnd();
    glPopMatrix();
}

void chassi(){

    glColor3f(1.0, 0.0, 0.0); // Define cor do quadrado (Vermelho)
    // Quadrado inferior
    glPushMatrix();  
        glScaled(2.5, 0.5, 1.0);     
        quadrado();
    glPopMatrix();
        
    // Quadrado superior
    glPushMatrix();
        glTranslated(0.8, -0.9, 0.0);
        glScaled(1.0, 0.4, 0.0);
        quadrado();
    glPopMatrix();
}

void carro() {

    // Roda traseira
    glPushMatrix();
        glTranslated(0.5, 0.0, 0.0);
        roda(); 
    glPopMatrix();

    // Roda dianteira
    glPushMatrix();
        glTranslated(-2.5, 0.0, 0.0);
        roda();
    glPopMatrix();

    chassi();
}

void grama(){
    
    glColor3f(0.0, 1.0, 0.0); // Cor: verde
    glPushMatrix();
        glTranslated(0.0, 6.0, 0.0);
        glScaled(6.0, 2.0, 1.0);
        quadrado();
    glPopMatrix();
}

void asfalto(){

    glColor3f(0.5, 0.5, 0.5); // Cor: cinza
    glPushMatrix();
        glTranslated(0.0, 3.0, 0.0);
        glScaled(6.0, 1.4, 1.0);
        quadrado();
    glPopMatrix();

}

void ceu(){

    glColor3f(0.0, 0.8, 1.0); // Cor: azul

    glPushMatrix();
        glTranslated(0.0, -3.0, 0.0);
        glScaled(6.0, 4.0, 1.0);
        quadrado();
    glPopMatrix();
}

void montanha(){

    glColor3f(0.0, 1.0, 0.0); // Cor: verde
    triangulo();

}

void sol() {

    glColor3f(1.0, 1.0, 0.0); // Cor: Amarelo
    circulo(1.0);
    
    glColor3f(1.0, 0.5, 0.0); // Cor: Laranja
    glBegin(GL_LINES);
    for(int i = 0; i < 12; i++) {
        double angle = (2 * 3.1415926535 / 12) * i; 
        
        float x1 = cos(angle);
        float y1 = sin(angle);
        
        float x2 = 1.5 * cos(angle);
        float y2 = 1.5 * sin(angle);
        
        glVertex3f(x1, y1, 0);
        glVertex3f(x2, y2, 0);
    }
    glEnd();
}

void helice(){

    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.5, -0.1, 0.0);
        glVertex3f(1.5, 0.0, 0.0);
        glVertex3f(0.5, 0.1, 0.0);
    glEnd();
}

void aerogerador() {
    // Mastro (não gira)
    glPushMatrix();
        glTranslated(0.0, 1.0, 0.0);
        glScaled(0.05, 1.0, 1.0);
        quadrado();
    glPopMatrix();

    glPushMatrix();
        glRotated(-(frameNumber * 2), 0.0, 0.0, 1.0); 
        
        for(int i = 0; i < 3; i++) {
            glPushMatrix();
                glRotated(120 * i, 0.0, 0.0, 1.0);
                helice();
            glPopMatrix();
        }
    glPopMatrix();
}

void doFrame(int v){
    frameNumber+=1;
    glutPostRedisplay();
    glutTimerFunc(33, doFrame,0); 
}

/* 
   Move o carro para direita, apertando D 
   Move o carro para esquerda, apertando A
*/
void teclado(unsigned char tecla, int x, int y){
    teclaPressionada = true;

    if(tecla == 'a' || tecla == 'A'){
        velocidadeCarro += 0.3;
        direcaoCarro = 1.0;
    }else if(tecla == 'd' || tecla == 'D'){
        velocidadeCarro -= 0.3;
        direcaoCarro = -1.0;
    }else{
        direcaoCarro = 0.0;
    }
}

void tecladoSolto(unsigned char tecla, int x, int y){
    teclaPressionada = false;
}

void gerarCirculosAzuis(int v) {
    // Limpa círculos antigos periodicamente
    if (frameNumber % 100 == 0) {
        numCirculos = 0;
    }
    
    // Adiciona um novo círculo a cada 30 frames
    if (frameNumber % 30 == 0 && numCirculos < MAX_CIRCULOS) {
        circulosX[numCirculos] = (rand() % 120 - 60) / 10.0f; // Posição X aleatória (-6 a 6)
        circulosTamanho[numCirculos] = (rand() % 30 + 10) / 100.0f; // Tamanho (0.1 a 0.4)
        numCirculos++;
    }
    
    glutPostRedisplay();
    glutTimerFunc(33, gerarCirculosAzuis, 0);
}

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(6, -6, 6, -6, 6, -6);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    /* DESENHE AQUI */

    ceu();

    glPushMatrix();
        glTranslated(-4.0, -4.5, 1.0);
        glRotated(-(frameNumber)/2, 0.0, 0.0, 1.0);
        sol();
    glPopMatrix();

    // Montanha da esquerda
    glPushMatrix();
        glTranslated(4.0, -0.7, 1.0);
        glScaled(4.0, 3.5, 1.0);
        montanha();
    glPopMatrix();

    // Montanha do meio
    glPushMatrix();
        glTranslated(1.0, -0.7, 1.0);
        glScaled(4.0, 4.0, 1.0);
        montanha();
    glPopMatrix();

    // Montanha da direita
    glPushMatrix();
        glTranslated(-4.0, -0.7, 1.0);
        glScaled(-3.0, 2.0, 1.0);
        montanha();
    glPopMatrix();

    glPushMatrix();
        glTranslated(0.0, -2.0, 0.0);
        glScaled(1.0, 0.8, 1.0);
        asfalto();
    glPopMatrix();
    
    // Aerogerador esquerda
    glPushMatrix();
        glTranslated(4.0, -3.0, 1.0);
        aerogerador();
    glPopMatrix();

    // Aerogerador centro
    glPushMatrix();
        glTranslated(1.5, -3.5, 1.0);
        aerogerador();
    glPopMatrix();

    //Aerogerador direita
    glPushMatrix();
        glTranslated(-1.0, -3.2, 1.0);
        aerogerador();
    glPopMatrix();

    grama();
    asfalto();

    glPushMatrix();
        glTranslated(velocidadeCarro, 1.0,0.0);
        carro();
    glPopMatrix();

    // Desenha os círculos azuis
    glColor3f(0.0, 0.0, 1.0); // Cor: Azul
    for (int i = 0; i < numCirculos; i++) {
        glPushMatrix();
            glTranslated(circulosX[i], 0.0, 0.0); 
            glScaled(circulosTamanho[i], circulosTamanho[i], 1.0); 
            circulo(1.0);
        glPopMatrix();
    }

    glFlush();
}

int main(int argc, char** argv){
    int janela_x = 800;
    int janela_y = 600;
    int inicial_x = 300;
    int inicial_y = 300;

    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(janela_x, janela_y);
    glutInitWindowPosition(inicial_x, inicial_y);
    glutCreateWindow("Renault 19");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutKeyboardUpFunc(tecladoSolto);
    glutTimerFunc(33, doFrame, 0);
    glutTimerFunc(33, gerarCirculosAzuis, 0);
    glutMainLoop();
    return 0;
}