#include <GL/glut.h>
#include <cmath>

const char* title = "Quadro do carrinho";
int windowWidth = 800;
int windowHeight = 600;
bool whitBackground = true;
const double PI = 3.14;
const float orthoValue = 8.0;
const float squareWidth = 1.0;

// declare generic code
void reset_modelview_matrix();
void reset_projection_matrix();
void reshape(int w, int h);
void init();

///////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////// BASE CODE
//////////////////////// CARTESIAN PLANE
void axis_markers() {
    float interval = (5*orthoValue)/100;
    float length = (5*orthoValue)/100;
    glColor3f(1.0, 0.5, 0.0); // Cor preta para os marcadores
    glLineWidth(1.0);

    glBegin(GL_LINES);

    // Marcadores ao longo do eixo X
    for (float x = -orthoValue; x <= orthoValue; x += interval) {
        if (fabs(x) < 0.0001f) continue; // Pular o centro (0)
        glVertex2f(x, -length);
        glVertex2f(x, length);
    }

    // Marcadores ao longo do eixo Y
    for (float y = -orthoValue; y <= orthoValue; y += interval) {
        if (fabs(y) < 0.0001f) continue; // Pular o centro (0)
        glVertex2f(-length, y);
        glVertex2f(length, y);
    }

    glEnd();
}

void cartesian_plane(){
    glLineWidth(2.0); // mais espesso para melhor visualização

    // Eixo X - vermelho
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2f(-orthoValue, 0.0f);
        glVertex2f(orthoValue, 0.0f);
    glEnd();

    // Eixo Y - verde
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
        glVertex2f(0.0f, -orthoValue);
        glVertex2f(0.0f, orthoValue);
    glEnd();

    axis_markers();   
}
////////////////////////

//////////////////////// POLYGONS
void drawSquare() { 
    glBegin(GL_POLYGON);
        glVertex3f(squareWidth/2, squareWidth/2, 0.0);   
        glVertex3f(-squareWidth/2, squareWidth/2, 0.0);  
        glVertex3f(-squareWidth/2, -squareWidth/2, 0.0);
        glVertex3f(squareWidth/2, -squareWidth/2, 0.0);
    glEnd();
}

void drawEquilateralTriangle(){
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(-1.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
    glEnd();
}

void drawRightTriangle() {
    glBegin(GL_POLYGON);
        glVertex3f(-1.0, 1.0, 0.0);
        glVertex3f(-1.0, -1.0, 0.0);
        glVertex3f(1.0, -1.0, 0.0);
    glEnd();
}

void drawCircle(double radius){
    int d;
    glBegin(GL_POLYGON);
    for(d = 0; d < 32; d++){
        double angle =  (2*PI/32) * d;
        glVertex3f(radius*cos(angle), radius*sin(angle), 0);
    }
    glEnd();
}
////////////////////////

//////////////////////// SQUARE BOUNDS 
struct Bounds {
    float minX;
    float maxX;
    float minY;
    float maxY;
};

Bounds getTransformedSquareBounds() {
    glPushMatrix();
        /////////////////////// formatação do quadrado que será utilizado como base
        glTranslated(0, 2.8, 0.0);
        glScaled(10, 8, 1.0);
        // Vértices do quadrado ANTES da transformação (centrado na origem, lado 1)
        GLfloat vertices[4][2] = {
            {-squareWidth/2, -squareWidth/2},
            {squareWidth/2, -squareWidth/2},
            {squareWidth/2, squareWidth/2},
            {-squareWidth/2, squareWidth/2}
        };
        GLfloat transformedVertices[4][2];

        // Obtem a matriz de modelo atual
        GLfloat modelMatrix[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, modelMatrix);

        float minX = windowWidth;
        float maxX = 0;
        float minY = windowHeight;
        float maxY = 0;
        for (int i = 0; i < 4; ++i) {
            // Multiplicar as coordenadas do vértice pela matriz de modelo (considerando z=0, w=1)
            // |m0, m4,  m8, m12 | |x| = |m0​x+m4​y+m8​(0)+m12​(1)|
            // |m1, m5,  m9, m13 | |y| = |m1​x+m5​y+m9​(0)+m13​(1)|
            // |m2, m6, m10, m14 | |0| = |m2​x+m6​y+m10​(0)+m14​(1)|
            // |m3, m7, m11, m15 | |1| = |m3​x+m7​y+m11​(0)+m15​(1)​            
            float transformedX = modelMatrix[0] * vertices[i][0] + modelMatrix[4] * vertices[i][1] + modelMatrix[12];
            float transformedY = modelMatrix[1] * vertices[i][0] + modelMatrix[5] * vertices[i][1] + modelMatrix[13];
            
            // transformação
            // Assume que a projeção ortogonal mapeia -orthoValue a orthoValue para 0 a windowWidth/Height.
            float windowX = ((transformedX + orthoValue) / (2 * orthoValue)) * windowWidth;
            float windowY = ((transformedY + orthoValue) / (2 * orthoValue)) * windowHeight;

            transformedVertices[i][0] = windowX;
            transformedVertices[i][1] = windowY;

            minX = fmin(minX, windowX);
            maxX = fmax(maxX, windowX);
            minY = fmin(minY, windowY);
            maxY = fmax(maxY, windowY);
        }
    glPopMatrix();
    return {minX, maxX, minY, maxY}; // Retorna uma instância da struct Bounds
}
////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////// PAINTING
void drawWheel(){
    float extern_radius = 0.28;
    float intern_radius = 0.10; // Raio interno onde os raios começam

    glPushMatrix();
        glColor3f(0, 0, 0);
        drawCircle(0.35);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.8, 0.8, 0.8);
        drawCircle(extern_radius);
    glPopMatrix();

   // Desenhar os raios
   glPushMatrix();
        glColor3f(0.5, 0.5, 0.5);
        int num_radios = 8;
        glBegin(GL_LINES);
            for (int i = 0; i < num_radios; ++i) {
                float angle = 2.0 * M_PI * i / num_radios;
                glVertex3f(cos(angle) * intern_radius, sin(angle) * intern_radius, 0);
                glVertex3f(cos(angle) * extern_radius, sin(angle) * extern_radius, 0);
            }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3f(0, 0, 0);
        drawCircle(intern_radius);
    glPopMatrix();
}

void drawBody(){
    glPushMatrix();
        glColor3f(1, 0, 0);
        glTranslated(0.0, 0.8, 0.0);
        glScaled(2.5, 0.6, 1.0); 
        drawSquare();
    glPopMatrix();

    glPushMatrix();
        glColor3f(1, 0, 0);
        glTranslated(-0.4, 1.3, 0.0);
        glScaled(1.1, 0.5, 1.0); 
        drawSquare();
    glPopMatrix();
}

void drawCar(){
    glPushMatrix();
        glTranslated(0.8, 0.38, 0.0);
        drawWheel();
    glPopMatrix();

    glPushMatrix();
        glTranslated(-0.8, 0.38, 0.0);
        drawWheel();
    glPopMatrix();

    drawBody();
}

void drawTrack(){
    /////////////////////// pista
    glPushMatrix();
        glColor3f(0.5, 0.5, 0.5);
        glScaled(10, 0.6, 1.0); 
        drawSquare();
    glPopMatrix();

    glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslated(0.0, 0.35, 0.0);
        glScaled(10, 0.1, 1.0); 
        drawSquare();
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.5, 0.5, 0.5);
        glTranslated(0.0, 0.65, 0.0);
        glScaled(10, 0.6, 1.0); 
        drawSquare();
    glPopMatrix();
    ///////////////////////

    /////////////////////// gramado
    glPushMatrix();
        glColor3f(0, 1, 0);
        glTranslated(0.0, -0.7, 0.0);
        glScaled(10, 1.0, 1.0); 
        drawSquare();
    glPopMatrix();
    ///////////////////////
}

void drawMountains(){
    glPushMatrix();
        glTranslated(-3.5, 0.95, 0.0);
        glScaled(2, 2, 1.0); 
        glColor3f(0, 1, 0);
        drawEquilateralTriangle();
    glPopMatrix();

    glPushMatrix();
        glTranslated(-1.5, 0.95, 0.0);
        glScaled(3, 3, 1.0); 
        glColor3f(0, 1, 0);
        drawEquilateralTriangle();
    glPopMatrix();

    glPushMatrix();
        glTranslated(2.9, 0.1, 0.0);
        glScaled(3, 3, 1.0); 
        glColor3f(0, 1, 0);
        drawEquilateralTriangle();
    glPopMatrix();
}

void drawBackground(){
    glPushMatrix();
        glTranslated(0, 2.8, 0.0);
        glColor3f(1, 0.8, 0.95);
        glScaled(10, 8, 1.0); 
        drawSquare();
    glPopMatrix();
}

void drawBlades(){
    glColor3f(0.8, 0.0, 0.0);
    glPushMatrix();
        glScaled(0.09, 2.5, 1.0); 
        drawEquilateralTriangle();
    glPopMatrix();

    glPushMatrix();
        glRotated(120.0, 0.0, 0.0, 1.0);
        glScaled(0.09, 2.5, 1.0); 
        drawEquilateralTriangle();
    glPopMatrix();

    glPushMatrix();
        glRotated(240.0, 0.0, 0.0, 1.0);
        glScaled(0.09, 2.5, 1.0); 
        drawEquilateralTriangle();
    glPopMatrix();
}

void drawWindTower(float rotate=10.0){
    // pás
    glPushMatrix();
        glRotated(rotate, 0.0, 0.0, 1.0);
        drawBlades();
    glPopMatrix();

    // poste
    glPushMatrix();
        glTranslated(0.0, -2, 0.0);
        glScaled(0.15, 4, 1.0); 
        drawSquare();
    glPopMatrix();

    // circulo central
    glPushMatrix();
        drawCircle(0.15);
    glPopMatrix();
}

void drawWindTowers(){
    glPushMatrix();
        glTranslated(-4.0, 4, 0.0);
        glScaled(0.5, 0.5, 1.0); 
        drawWindTower(10);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-2.0, 5, 0.0);
        glScaled(0.5, 0.5, 1.0); 
        drawWindTower(-10);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0.0, 4, 0.0);
        glScaled(0.5, 0.5, 1.0); 
        drawWindTower();
    glPopMatrix();
}


void drawPicture(){
    Bounds scissorBounds = getTransformedSquareBounds();
    glEnable(GL_SCISSOR_TEST);
        glScissor(static_cast<GLint>(scissorBounds.minX), static_cast<GLint>(scissorBounds.minY),
                  static_cast<GLsizei>(scissorBounds.maxX - scissorBounds.minX), static_cast<GLsizei>(scissorBounds.maxY - scissorBounds.minY));

        drawBackground();
        drawWindTowers();
        drawMountains();
        drawTrack();
        drawCar();
    glDisable(GL_SCISSOR_TEST);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    reset_modelview_matrix();
    drawPicture();
    // cartesian_plane();
    glFlush();
}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////// GENERIC CODE
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    reset_projection_matrix();
    glOrtho(-orthoValue, orthoValue, -orthoValue, orthoValue, -orthoValue, orthoValue);
    reset_modelview_matrix();
    windowWidth = w;
    windowHeight = h;
}

void reset_modelview_matrix(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void reset_projection_matrix(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    reset_projection_matrix();
    glOrtho(-orthoValue, orthoValue, -orthoValue, orthoValue, -orthoValue, orthoValue);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow(title);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
///////////////////////////////////////////////////////////////////```


void carro() {
    // Corpo do carro (verde)
    glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);      // Verde
        glTranslatef(0.0, 0.0, 0.0);   // Posição do corpo
        glScalef(2.0, 0.5, 1.0);       // Escala para retângulo
        quadrado();
    glPopMatrix();

    // Teto do carro (verde escuro)
    glPushMatrix();
        glColor3f(0.0, 0.6, 0.0);      // Verde escuro
        glTranslatef(0.0, 0.5, 0.0);   // Posição do teto
        glScalef(0.7, 0.7, 1.0);       // Escala menor
        triangulo();
    glPopMatrix();

    // Roda esquerda (preta)
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);      // Preto
        glTranslatef(-0.8, -0.3, 0.0);
        circulo(0.2);
    glPopMatrix();

    // Roda direita (preta)
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);      // Preto
        glTranslatef(0.8, -0.3, 0.0);
        circulo(0.2);
    glPopMatrix();
}
