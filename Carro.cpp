#include <GL/glut.h>
#include <math.h>

void init();
void display();

void circulo(double radius){
    int d;
    glBegin(GL_LINE_LOOP);
    for(d = 0; d < 32; d++){
        double angle =  (6.14/32) * d;
        glVertex3f(radius*cos(angle), radius*sin(angle), 0);
    }
    glEnd();
}

void quadrado(){

    glColor3f(0, 0, 0); // Define cor do quadrado (preto)
         
    glBegin(GL_LINE_LOOP);
        // Vértices do quadrado
        glVertex3f(1.0, 1.0, 0.0);   
        glVertex3f(-1.0, 1.0, 0.0);  
        glVertex3f(-1.0, -1.0, 0.0);
        glVertex3f(1.0, -1.0, 0.0);
    glEnd();
}

void triangulo(){
    glBegin(GL_LINE_LOOP);
        // Vértices do triângulo
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(-1.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
    glEnd();
}

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(1, -1, 1, -1, 1, -1);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    /* DESENHE AQUI */


    glFlush();
}

int main(int argc, char** argv){
    int janela_x = 800;
    int janela_y = 600;
    int inicial_x = 300;
    int inicial_y = 300;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(janela_x, janela_y);
    glutInitWindowPosition(inicial_x, inicial_y);
    glutCreateWindow("Renault 19");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}