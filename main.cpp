//=============================================================================
// Sample Application: Lighting (Per Fragment Phong)
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include <time.h>
#include "glm.h"
#include "Teclado.h"
#include "Maceta.h"
#include "Proyector.h"
#include "jupiter.h"
#include "puerta.h"
#include "planta.h"
#include "Mesa.h"
#include <FreeImage.h>
//-----------------------------------------------------------------------------


class myWindow : public cwc::glutWindow
{
protected:
   cwc::glShaderManager SM;
   cwc::glShader *shader, *shader1;
   GLuint ProgramObject;
   clock_t time0,time1;
   float timer010;  // timer counting 0->1->0
   bool bUp;        // flag if counting up or down.
   GLMmodel* objmodel_ptr;
   Teclado keyboard;
   Maceta flowerpot;
   Proyector holotable;
   jupiter planet;
   puerta door;
   planta flower;
   Mesa table;
   /*movimiento en X*/
   float posCamX;
   bool movXI, movXD;
   /*movimiento en Y*/
   float posCamY;
   bool movYI, movYS;

  //mover objeto
   float movimiento_objeto_x, movimiento_objeto_y;
   bool mov_objeto_derecha, mov_objeto_izquierda,mov_objeto_arriba, mov_objeto_abajo;

   //codigo texturas
   GLMmodel* objmodel_ptr1; //*** Para Textura: variable para objeto texturizado
   GLuint texid; //*** Para Textura: variable que almacena el identificador de textura

public:
	myWindow(){}

    //*** Para Textura: aqui adiciono un m�todo que abre la textura en JPG
    void initialize_textures(void)
    {
        int w, h;
        GLubyte* data = 0;
        //data = glmReadPPM("soccer_ball_diffuse.ppm", &w, &h);
        //std::cout << "Read soccer_ball_diffuse.ppm, width = " << w << ", height = " << h << std::endl;

        //dib1 = loadImage("soccer_ball_diffuse.jpg"); //FreeImage

        glGenTextures(1, &texid);
        glBindTexture(GL_TEXTURE_2D, texid);
        glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // Loading JPG file
        FIBITMAP* bitmap = FreeImage_Load(
            FreeImage_GetFileType("./texturas/jupiter.jpg", 0),
            "./texturas/jupiter.jpg");  //*** Para Textura: esta es la ruta en donde se encuentra la textura

        FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
        int nWidth = FreeImage_GetWidth(pImage);
        int nHeight = FreeImage_GetHeight(pImage);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
            0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

        FreeImage_Unload(pImage);
        //
        glEnable(GL_TEXTURE_2D);
    }

    void moverCamara() {
        if (movXI) {
            posCamX = posCamX + 0.5;
        }
        if(movXD){
            posCamX = posCamX - 0.5;
        }
        if (movYI) {
            posCamY = posCamY + 0.5;
        }
        if (movYS) {
            posCamY = posCamY - 0.5;
        }
        glTranslatef(posCamX, posCamY, 0);
    }

    void moverObjetoPlaneta() {
        if (mov_objeto_derecha) {
            movimiento_objeto_x = movimiento_objeto_x + 0.5;
        }
        if (mov_objeto_izquierda) {
            movimiento_objeto_x = movimiento_objeto_x - 0.5;
        }
        if (mov_objeto_arriba) {
            movimiento_objeto_y = movimiento_objeto_y + 0.5;
        }
        if (mov_objeto_abajo) {
            movimiento_objeto_y = movimiento_objeto_y - 0.5;
        }
        

    }

	virtual void OnRender(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
      //timer010 = 0.09; //for screenshot!

      
      glPushMatrix();
      //Simulaci�n de camara
      moverCamara();
      moverObjetoPlaneta();
      if (shader) shader->begin();
          //Translaci�n para visualizaci�n
          glTranslatef(0, 0, -5);
          //Comentar esta linea de abajo para la rotaci�n
          //glRotatef(timer010 * 360, 0.0, 0.1, 0.1);
          //Proyector y Holograma
          glPushMatrix();
            holotable.dibujarMalla((0+movimiento_objeto_x),(0+ movimiento_objeto_y), 0);
          glPopMatrix();
          //Puerta
          glPushMatrix();
              glTranslatef(7, 0, 0);
              glRotatef(90, 0, 1, 0);
              glScalef(2.0, 2.0, 2.0);
              door.dibujarMalla(0, 0.5, 0);
          glPopMatrix();
          //Teclados
          glPushMatrix();
            glTranslatef(-4, 0.5, 0);
            keyboard.dibujarMalla(0, 0, 0);
            glPushMatrix();
                glRotatef(45, 0, 1, 0);
                keyboard.dibujarMalla(-1, 0, 2);
            glPopMatrix();
            glPushMatrix();
                glRotatef(-45, 0, 1, 0);
                keyboard.dibujarMalla(-1, 0, -2);
            glPopMatrix();

            //Mesa con Ralph
            glPushMatrix();
                glTranslatef(10, 0, 0);
                table.dibujarMalla(0, 0, 0);
                glPushMatrix();
                    glScalef(0.7,0.7,0.7);
                    flowerpot.dibujarMalla(0, 1.4, 0);
                glPopMatrix();
                glPushMatrix();
                    flower.dibujarMalla(-0.5,1.3,0);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();


      if (shader) shader->end();
          

      if (shader1) shader1->begin();
        glPushMatrix();
        planet.dibujarMalla(0, 1, 0, texid);
        glPopMatrix();
            
      if (shader1) shader1->end();

      glutSwapBuffers();
      glPopMatrix();

      UpdateTimer();

		Repaint();
	}

	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!
	virtual void OnInit()
	{

        posCamX = 0.0;
        posCamY = 0.0;
        movYI = false;
        movYS = false;
        movXI = false;
        movXD = false;

        movimiento_objeto_x = 0.0;
        movimiento_objeto_y = 0.0;
        mov_objeto_derecha = false;
        mov_objeto_izquierda = false;
        mov_objeto_arriba = false;
        mov_objeto_abajo = false;


        keyboard.abrirMalla();
        flowerpot.abrirMalla();
        planet.abrirMalla();
        door.abrirMalla();
        flower.abrirMalla();
        holotable.abrirMalla();
        table.abrirMalla();

		glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);

		shader = SM.loadfromFile("vertexshader.txt","fragmentshader.txt"); // load (and compile, link) from file
		if (shader==0) 
         std::cout << "Error Loading, compiling or linking shader\n";
         else
         {
            ProgramObject = shader->GetProgramObject();
         }

        shader1 = SM.loadfromFile("vertexshaderT.txt", "fragmentshaderT.txt"); // load (and compile, link) from file
        if (shader1 == 0)
            std::cout << "Error Loading, compiling or linking shader\n";
        else
        {
            ProgramObject = shader1->GetProgramObject();
        }

      time0 = clock();
      timer010 = 0.0f;
      bUp = true;

      //*** Para Textura: abrir archivo de textura
      initialize_textures();
      DemoLight();

	}

	virtual void OnResize(int w, int h)
   {
      if(h == 0) h = 1;
	   float ratio = 1.0f * (float)w / (float)h;

      glMatrixMode(GL_PROJECTION);
	   glLoadIdentity();
	
	   glViewport(0, 0, w, h);

      gluPerspective(45,ratio,1,100);
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	   gluLookAt(0.0f,0.0f,4.0f, 
		          0.0,0.0,-1.0,
			       0.0f,1.0f,0.0f);
   }
	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y) {}    
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	virtual void OnKeyDown(int nKey, char cAscii)
	{       
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close Window!
		}
        else if (cAscii == 'a')  movXI = true;
        else if (cAscii == 'd')  movXD = true;
        else if (cAscii == 'w')  movYS = true;
        else if (cAscii == 's')  movYI = true;
        else if (cAscii == 'h')  mov_objeto_derecha = true;
        else if (cAscii == 'k')  mov_objeto_izquierda = true;
        else if (cAscii == 'u')  mov_objeto_arriba = true;
        else if (cAscii == 'j')  mov_objeto_abajo = true;
        
	};

	virtual void OnKeyUp(int nKey, char cAscii)
	{
      if (cAscii == 's')      // s: Shader
         shader->enable();
      else if (cAscii == 'f') // f: Fixed Function
         shader->disable();

      else if (cAscii == 'a')  movXI = false;
      else if (cAscii == 'd')  movXD = false;
      else if (cAscii == 'h')  mov_objeto_derecha = false;
      else if (cAscii == 'k')  mov_objeto_izquierda = false;
      else if (cAscii == 'u')  mov_objeto_arriba = false;
      else if (cAscii == 'j')  mov_objeto_abajo = false;
      if (cAscii == 'w')  movYS = false;
      if (cAscii == 's')  movYI = false;


    }

   void UpdateTimer()
   {
      time1 = clock();
      float delta = static_cast<float>(static_cast<double>(time1-time0)/static_cast<double>(CLOCKS_PER_SEC));
      delta = delta / 4;
      if (delta > 0.00005f)
      {
         time0 = clock();
         if (bUp)
         {
            timer010 += delta;
            if (timer010>=1.0f) { timer010 = 1.0f; bUp = false;}
         }
         else
         {
            timer010 -= delta;
            if (timer010<=0.0f) { timer010 = 0.0f; bUp = true;}
         }
      }
   }

   void DemoLight(void)
   {
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_NORMALIZE);
     
     // Light model parameters:
     // -------------------------------------------
     
     GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0 };
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
     
     glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
     glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
     
     // -------------------------------------------
     // Spotlight Attenuation
     
     GLfloat spot_direction[] = {1.0, -1.0, -1.0 };
     GLint spot_exponent = 30;
     GLint spot_cutoff = 180;
     
     glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
     glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
     glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
    
     GLfloat Kc = 1.0;
     GLfloat Kl = 0.0;
     GLfloat Kq = 0.0;
     
     glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,Kc);
     glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
     glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);
     
     
     // ------------------------------------------- 
     // Lighting parameters:

     GLfloat light_pos[] = {0.0f, 5.0f, 5.0f, 1.0f};
     GLfloat light_Ka[]  = {1.0f, 0.5f, 0.5f, 1.0f};
     GLfloat light_Kd[]  = {1.0f, 0.1f, 0.1f, 1.0f};
     GLfloat light_Ks[]  = {1.0f, 1.0f, 1.0f, 1.0f};
     /*
     glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
     glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
     glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);
     */
     // -------------------------------------------
     // Material parameters:

     GLfloat material_Ka[] = {0.5f, 0.0f, 0.0f, 1.0f};
     GLfloat material_Kd[] = {0.4f, 0.4f, 0.5f, 1.0f};
     GLfloat material_Ks[] = {0.8f, 0.8f, 0.0f, 1.0f};
     GLfloat material_Ke[] = {0.1f, 0.0f, 0.0f, 0.0f};
     GLfloat material_Se = 20.0f;
     /*
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
     glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
     glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
     */
   }
};

//-----------------------------------------------------------------------------

class myApplication : public cwc::glApplication
{
public:
	virtual void OnInit() {std::cout << "Hello World!\n"; }
};

//-----------------------------------------------------------------------------

int main(void)
{
	myApplication*  pApp = new myApplication;
	myWindow* myWin = new myWindow();

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------

