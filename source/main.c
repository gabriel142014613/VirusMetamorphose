
#include <nds.h>
#include <stdio.h>
#include <math.h>

float playerX = 0;
float playerZ = 0;

int infection = 35;
int trust = 0;
int chapter = 1;
int survivorHelped = 0;
int laboratoryVisited = 0;
int gameEnding = 0;

char message[80] = "Reveil a l'hopital.";

void drawCube(float x, float y, float z,
              float sx, float sy, float sz,
              int r, int g, int b)
{
    glPushMatrix();

    glTranslatef32(
        floattof32(x),
        floattof32(y),
        floattof32(z)
    );

    glScalef32(
        floattof32(sx),
        floattof32(sy),
        floattof32(sz)
    );

    glColor3b(r,g,b);

    glBegin(GL_QUADS);

    glVertex3v16(-4096,-4096,4096);
    glVertex3v16(4096,-4096,4096);
    glVertex3v16(4096,4096,4096);
    glVertex3v16(-4096,4096,4096);

    glVertex3v16(4096,-4096,-4096);
    glVertex3v16(-4096,-4096,-4096);
    glVertex3v16(-4096,4096,-4096);
    glVertex3v16(4096,4096,-4096);

    glVertex3v16(-4096,-4096,-4096);
    glVertex3v16(-4096,-4096,4096);
    glVertex3v16(-4096,4096,4096);
    glVertex3v16(-4096,4096,-4096);

    glVertex3v16(4096,-4096,4096);
    glVertex3v16(4096,-4096,-4096);
    glVertex3v16(4096,4096,-4096);
    glVertex3v16(4096,4096,4096);

    glVertex3v16(-4096,4096,4096);
    glVertex3v16(4096,4096,4096);
    glVertex3v16(4096,4096,-4096);
    glVertex3v16(-4096,4096,-4096);

    glEnd();

    glPopMatrix(1);
}

void initializeGame(void)
{
    videoSetMode(MODE_0_3D);
    videoSetModeSub(MODE_0_0);

    vramSetBankA(VRAM_A_TEXTURE);

    consoleDemoInit();

    glInit();

    glEnable(GL_ANTIALIAS);
    glEnable(GL_DEPTH_TEST);

    glClearColor(5,8,15,31);
    glClearDepth(GL_MAX_DEPTH);
    glViewport(0,0,255,191);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60,256.0/192.0,0.1,100);

    glMatrixMode(GL_MODELVIEW);
}

void drawWorld(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        playerX,2.5,playerZ+6,
        playerX,0,playerZ-5,
        0,1,0
    );

    // Route
    drawCube(0,-1,-8,12,0.15,30,38,43,50);

    // Batiments
    drawCube(-6,2,-5,3,3,3,65,72,85);
    drawCube(7,3,-10,2,4,3,45,55,70);
    drawCube(-7,2,-18,3,3,3,50,45,65);
    drawCube(7,3,-22,3,4,3,60,50,65);

    // Survivant
    drawCube(2,0,-5,0.35,0.7,0.35,110,65,110);

    // Laboratoire
    drawCube(-2,0,-10,0.5,0.7,0.5,25,110,120);

    // Joueur
    drawCube(playerX,0,playerZ,0.35,0.7,0.35,110,75,115);

    glFlush(0);
}

float distanceTo(float x,float z)
{
    float dx=playerX-x;
    float dz=playerZ-z;

    return sqrtf(dx*dx+dz*dz);
}

void interact(void)
{
    if(distanceTo(2,-5)<2)
    {
        if(!survivorHelped)
        {
            survivorHelped=1;
            trust+=10;
            infection-=5;

            sprintf(message,"Survivant aide !");
        }
        else
        {
            sprintf(message,"Merci pour ton aide !");
        }
    }
    else if(distanceTo(-2,-10)<2)
    {
        laboratoryVisited=1;
        chapter=2;
        infection+=10;

        sprintf(message,"Virus FEM-X decouvert !");
    }
    else
    {
        sprintf(message,"Rien a proximite.");
    }

    if(infection<0) infection=0;
    if(infection>100) infection=100;
}

void drawInterface(void)
{
    consoleClear();

    iprintf("========================\n");
    iprintf(" VIRUS METAMORPHOSE\n");
    iprintf("========================\n\n");

    iprintf("Chapitre : %d\n",chapter);
    iprintf("Infection : %d%%\n",infection);
    iprintf("Confiance : %d\n\n",trust);

    iprintf("Personnage : Alex\n");
    iprintf("Etat : transforme(e)\n\n");

    iprintf("%s\n\n",message);

    iprintf("CROIX : DEPLACEMENT\n");
    iprintf("A : INTERAGIR\n");
    iprintf("START : RECOMMENCER\n");
}

int main(void)
{
    initializeGame();

    while(1)
    {
        scanKeys();

        int held=keysHeld();
        int pressed=keysDown();

        if(!gameEnding)
        {
            if(held&KEY_LEFT) playerX-=0.10f;
            if(held&KEY_RIGHT) playerX+=0.10f;
            if(held&KEY_UP) playerZ-=0.10f;
            if(held&KEY_DOWN) playerZ+=0.10f;
        }

        if(playerX < -9) playerX=-9;
        if(playerX > 9) playerX=9;
        if(playerZ < -29) playerZ=-29;
        if(playerZ > 5) playerZ=5;

        if(pressed&KEY_A) interact();

        if(pressed&KEY_START)
        {
            playerX=0;
            playerZ=0;
            infection=35;
            trust=0;
            chapter=1;
            survivorHelped=0;
            laboratoryVisited=0;
            gameEnding=0;

            sprintf(message,"Reveil a l'hopital.");
        }

        drawWorld();
        drawInterface();

        swiWaitForVBlank();
    }

    return 0;
}
