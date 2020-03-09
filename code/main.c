/************************************************************/
/*           Robot projet             */
/************************************************************/


/********************Header mac **********************/

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

/********************Header win **********************/


//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glut.h>
//#include<stdlib.h>
//#include<stdio.h>
//#include <math.h>


GLUquadricObj *quadratic = gluNewQuadric();

float X = 5.0;
float Y = 2.0;
float Z = 8.0;

float R = 5.0;
float phi = 0;
float const PI = 3.141592;
float alpha = -PI / 2;

float angle = 0.0;
float angleAntenne = 0.0;

int sens = 1;

float oeil = 10.0;
float oeilBas = 10.0;

static int braAngle= 0, coudeAngle=0;
float cameraAngle = 10.0;

/* prototypes de fonctions */
void initRendering();// Initialisation du rendu
 void IdleFunction(void );
void display();                             // modélisation
void reshape(int w,int h);                      // visualisation
// mise à jour: appelle Timer pour l'animation de la scène
void keyboard(unsigned char key, int x, int y); // fonction clavier
void wirecube(GLdouble width, GLdouble height, GLdouble depth); //fonction cube
void demiCercle(); //fonction demi cercle
void vise(); //fonction cercle pr faire les vises



/* Programme principal */
int main(int argc,       // argc: nombre d'arguments, argc vaut au moins 1
         char **argv){  // argv: tableau de chaines de caractères, argv[0] contient le nom du programme lancé (plus un éventuel chemin)


    /* Initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);                       // Initialisation
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // mode d'affichage RGB, et test prafondeur
    glutInitWindowSize(800 , 600);                // dimension fenêtre
    glutInitWindowPosition (100, 100);           // position coin haut gauche
    glutCreateWindow("Projet robot");  // nom

    /* Initialisation d'OpenGL */
    initRendering();

    /* Enregistrement des fonctions de rappel
     => initialisation des fonctions callback appelées par glut */
    glutDisplayFunc(display);
    glutIdleFunc(IdleFunction); /* appel de glutIdleFunc (Timer pr animation) */
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    /* rq: le callback de fonction (fonction de rappel) est une fonction qui est passée en argument à une
     autre fonction. Ici, le main fait usage des deux fonctions de rappel (qui fonctionnent en même temps)
     alors qu'il ne les connaît pas par avance.*/


    /* Entrée dans la boucle principale de glut, traitement des évènements */
    glutMainLoop();// lancement de la boucle de réception des évènements
    return 0;               // pour finir
}


/* Initialisation d'OpenGL pour le rendu de la scène */
void initRendering() {

    /* Active le z-buffer */
    glEnable(GL_DEPTH_TEST);

    /* Activation des couleurs */
    glEnable(GL_COLOR_MATERIAL);

    /* définit la couleur d'effacement et la couleur de fond */
    glClearColor(0.0, 0.0, 0.0, 0.0);

    /*  définit la taille d'un pixel*/
    glPointSize(2.0);

}


/* Creation des cubes */
void wirecube(GLdouble width, GLdouble height, GLdouble depth){
    glPushMatrix();
    glScalef(width, height, depth);
    glutWireCube(1.0);
    glPopMatrix();
}

void demiCercle(){
    glBegin(GL_POLYGON);
        for (int i=0 ; i<oeil; i++) {
            float mycos = 0.3*cos(i*2* PI /50);
            float mysin = 0.3*sin(i*2* PI/50);
            glColor3f(0.0,0.0,0.0);
            glVertex2f(mycos, mysin);
        }
    glEnd();

}

void vise(){
    glBegin(GL_POLYGON);
              for (int i=0 ; i<50; i++) {
                  float mycos = 0.1*cos(i*2* PI /50);
                  float mysin = 0.1*sin(i*2* PI/50);
                  glColor3f(0.0,0.0,0.0);
                  glVertex2f(mycos, mysin);
              }
    glEnd();
}


/* Création de la scène */
void display(){

    /* Efface les tampons de couleur et de profondeur de l'image avec la couleur de fond.
     rq: buffer: mémoire tampon, c'est donc une surface en memoire utilisée pour stocker une image*/
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    /* la mat de visualisation-modélisation est modifiable par défaut */
    glMatrixMode(GL_MODELVIEW);

    /* on charge l'identité dans la matrice de modélisation-visualisation*/
    // glLoadIdentity();

    glPushMatrix();
    /* Permet de créer un point de vue. Définit une matrice de modélisation-visualisation et la multiplie
     à droite de lma matrice active, ici l'identité*/
    gluLookAt(R * cos(phi) * sin(alpha), R * sin(phi), R * cos(phi) * cos(alpha),      // position caméra
              0.0, 0.0, 0.0,      // point de mire
              0.0, 1.0, 0.0);     // vecteur d'orientation caméra
    
    /************************************************************/
    /*            Tête                    */
    /************************************************************/

    
//triangle
   glColor3f(0.247, 0.103, 0.108); //rouge

   glTranslatef(1.0, 0.0, 0.0);
   glRotatef(0.0,0.0, 0.0, 0.0);
    
    
//    vise();
   
    glColor3f(0.247, 0.103, 0.108); //rouge

   glBegin(GL_TRIANGLES);
        glVertex3f(1.0, -1.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, -1.0, 0.0);

//    2ieme triangle
        glVertex3f(1.0, -1.0, 1.0);
        glVertex3f(0.0, 1.0, 1.0);
        glVertex3f(-1.0, -1.0, 1.0);

   glEnd();


//quad1
    glBegin(GL_QUADS);
              glVertex3f(0.0, 1.0, 0.0);
              glVertex3f(1.0, -1.0, 0.0);
              glVertex3f(1.0, -1.0, 1.0);
              glVertex3f(0.0, 1.0, 1.0);

    glEnd();

//   quad2
    glBegin(GL_QUADS);
              glVertex3f(0.0, 1.0, 0.0);
              glVertex3f(-1.0, -1.0, 0.0);
              glVertex3f(-1.0, -1.0, 1.0);
              glVertex3f(0.0, 1.0, 1.0);
    glEnd();


//quadBas
       glBegin(GL_QUADS);
            glVertex3f(-1.0, -1.0, 0.0);
            glVertex3f(1.0, -1.0, 0.0);
            glVertex3f(1.0, -1.0, 1.0);
            glVertex3f(-1.0, -1.0, 1.0);
       glEnd();


    /************************************************************/
    /*            OEIL                    */
    /************************************************************/


    glTranslatef(0.0, 0.0, 1.0);
    glRotatef(angle,0.0, 0.0, 1.0);

    glColor3f(0, 0, 0); //noir
    glutSolidSphere(0.1, 50, 50);




    gluCylinder(quadratic, 0.3f, 0.3f, 0.1, 32, 32);

    glTranslatef(0.0, 0.0, 0.1);

    demiCercle();

    glTranslatef(0.0, 0.0, -0.1);
    glRotatef(angle,0.0, 0.0, 1.0);


    /************************************************************/
    /*            BOUCHE                  */
    /************************************************************/
    glTranslatef(0.0, -0.7, 0.0);
    glRotatef(angle,0.0, 0.0, 0.0);

    glColor3f(1, 0, 0); //red

    wirecube(0.7, 0.3, 0.1);



    /************************************************************/
    /*            Antenne                 */
    /************************************************************/
    glTranslatef(0.0, 2.4, -0.5);
    glRotatef(100,0.0, 0.0, 0.0);

    glColor3f(1, 0, 0); //red

    gluCylinder(quadratic, 0.03f, 0.03f, 0.9, 30, 30);
    glColor3f(1, 1, 0); //red


    glTranslatef(0.0, 0.0, -0.01);
    glRotatef(0.0,0.0, 0.0, 0.0);
    glutSolidSphere(0.05, 50, 50);

glPopMatrix();

    /* On swap (échange) les buffers, càd, on fait passer l'image calculée et dessinée
     dans le back buffer au buffer qui va l'afficher: le front buffer (en général), c'est le bouble buffering
     Cela évite une image animée sacadée, si elle était directement tracée dans le front buffer*/
    glutSwapBuffers();

    /* On force l'affichage */
    glFlush(); // nettoie les fenêtres précédentes
}


/*  Animations qui utilise le temps */
void IdleFunction(void) {

    /*  Oeil */

    if ((oeil < 50.0  && sens == 1) || oeil < 9.0 ){
        oeil += 6.0;
        sens = 1;

    }
    else{
        oeil -= 6.0;
        sens = 0;
    }

    glutPostRedisplay();
}



/*  Mise en forme de la scène pour l'affichage */
void reshape(int w,  // w: largeur fenêtre
             int h)  // h: hauteur fenêtre
{
    /* Viewport: cadrage. Spécifie la région (position et taille en px) que l'image observée de la scène occupe
     à l'écran => réduction et agrandissement de l'image possible*/
    glViewport(0, 0,(GLsizei) w, (GLsizei) h);

    /* Spécifie que la matrice de projection va être modifiée  */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();             // matrice courante: l'identité
    //glOrtho(-2.0, 2.0, -2.0, 2.0, 1.5, 20.0);
    //glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

    /* Perspective avec point de fuite */
    gluPerspective(60.0,                       // angle d'ouverture vertical caméra
                   (GLfloat) w / (GLfloat) h,  // ratio largeur-hauteur
                   1.0,                           // plan proche z=1
                   200.0);                     // plan éloigné z=200


}

/* Fonction de gestion du clavier */
void keyboard(unsigned char key,       // Touche qui a été pressée
              int x, int y) {    // Coordonnées courante de la souris

    switch (key){

        case 'w':
            (coudeAngle += 5)% 360;
            break;

        case 'c':
            (coudeAngle -= 5)% 360;
            break;

        case 's':
            (braAngle += 5) % 360;
            break;

        case 'x':
            (braAngle -= 5)% 360;
            break;
            
         case 'h':
            alpha += 0.1;
            phi += 0.0;
            break;
        
        
        case 'f':
           alpha -= 0.1;
           phi += 0.0;
           break;
        
        
        case 't':
            alpha += 0.0;
            phi += 0.1;
            break;
        
        case 'g':
            alpha += 0.0;
            phi -= 0.1;
            break;

        default:return;
    }
    glutPostRedisplay();
}
