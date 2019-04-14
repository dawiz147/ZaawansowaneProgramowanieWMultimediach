#pragma once
#pragma once

#include <Windows.h>
#include <atlstr.h>
//#include "Res.h"
#include "Listonosz2.h"
#include <gl\GL.h> // OpenGL32
#include <gl\GLU.h> // GLu32
//#include <cmath>
//#include <gl\glaux.h> //Header File For The Glaux

//biblioteki
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
//#pragma comment(lib, "glaux.lib")
HWND hwndMainWindow;
static float Obrot;
float RuchCzlowieka;


void DrawCube(float x, float y, float z, float dx, float dy, float dz)
{
  glPushMatrix();// zapisanie ustawieñ "œwiata"
  glTranslatef(x, y, z); // zmiana po³o¿enia "œwiata"
  glScalef(dx, dy, dz); // przeskalowanie "œwiata"
  glBegin(GL_QUADS);



  glColor3f(1, 0, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 1, 0);
  glVertex3f(1, 1, 0);
  glVertex3f(1, 0, 0);

  glColor3f(1, 1, 0);
  glVertex3f(0, 0, 1);
  glVertex3f(0, 1, 1);
  glVertex3f(1, 1, 1);
  glVertex3f(1, 0, 1);

  glColor3f(1, 0, 1);
  glVertex3f(0, 1, 1);
  glVertex3f(0, 1, 0);
  glVertex3f(1, 1, 0);
  glVertex3f(1, 1, 1);

  glColor3f(1, 0, 1);
  glVertex3f(1, 1, 1);
  glVertex3f(1, 1, 0);
  glVertex3f(1, 0, 0);
  glVertex3f(1, 0, 1);

  glColor3f(0, 0, 1);
  glVertex3f(0, 0, 0);
  glVertex3f(1, 0, 0);
  glVertex3f(1, 0, 1);
  glVertex3f(0, 0, 1);

  glColor3f(0, 1, 1);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 1, 0);
  glVertex3f(0, 1, 1);
  glVertex3f(0, 0, 1);

  glEnd();
  glPopMatrix(); // wczytanie podstawowych ustawieñ 

}
void DrawHuman(float x, float y, float z, float dx, float dy, float dz) {

  glPushMatrix();
  glTranslatef(x, y, z); // zmiana po³o¿enia "œwiata"
  glScalef(dx, dy, dz); // przeskalowanie "œwiata"
  DrawCube(0.5f, 1.5f, 0, 1, 1, 1); // g³owa
  DrawCube(0.75f, 1.25f, 0.25f, 0.5f, 0.25f, 0.5f); // Szyja
  DrawCube(0.0f, -1.0f, -0.25f, 2.0f, 2.25f, 1.5f); // tu³ów




  RuchCzlowieka += 0.01f;
  glPushMatrix();
  glRotatef(15 * sin(RuchCzlowieka*0.1f + 1.570796), 1, 0, 0);
  DrawCube(2.0f, -1.25f, 0.125f, 0.5f, 2.25f, 0.75f); // prawa rêka
  DrawCube(0.125f, -3.15f, 0.125f, 1.0f, 2.25f, 0.90f); // lewa noga
  glPopMatrix();


  glPushMatrix();
  glRotatef(15 * sin(RuchCzlowieka*0.1f + 4.712388), 1, 0, 0);
  DrawCube(-0.5f, -1.25f, 0.125f, 0.5f, 2.25f, 0.75f); // lewa rêka
  DrawCube(1.25f, -3.15f, 0.125f, 1.0f, 2.25f, 0.90f); // prawa noga
  glPopMatrix();
  glEnd();
  glPopMatrix();

}
void DrawArmy()
{

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 5; j++) {
      DrawHuman(3 * i, 0, 3 * j, 0.25f, 0.25f, 0.25f);

    }
  }
}