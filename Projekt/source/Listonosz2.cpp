#include "Listonosz2.h"
#pragma once
#include <Windows.h>
#include <atlstr.h>
#include "Listonosz2.h"
#include <gl\GL.h> // OpenGL32
#include <gl\GLU.h> // GLu32

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

float RuchCzlowieka=0;

void DrawCube(float x, float y, float z, float dx, float dy, float dz)
{
  glPushMatrix();// zapisanie ustawień "świata"
  glTranslatef(x, y, z); // zmiana położenia "świata"
  glScalef(dx, dy, dz); // przeskalowanie "świata"
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
  glPopMatrix(); // wczytanie podstawowych ustawień 

}
//void MoveHuman(bool Move)
//{
 // if(Move==true)
 // {
    
 // }
//}
void DrawHuman(float x, float y, float z, float dx, float dy, float dz) {

  glPushMatrix();
  glTranslatef(x, y, z); // zmiana położenia "świata"
  glScalef(dx, dy, dz); // przeskalowanie "świata"
  DrawCube(0.5f, 1.5f, 0, 1, 1, 1); // głowa
  DrawCube(0.75f, 1.25f, 0.25f, 0.5f, 0.25f, 0.5f); // Szyja
  DrawCube(0.0f, -1.0f, -0.25f, 2.0f, 2.25f, 1.5f); // tułów

  RuchCzlowieka += 0.01f;
  glPushMatrix();
  glRotatef(15 * sin(RuchCzlowieka*0.1f + 1.570796), 1, 0, 0);
  DrawCube(2.0f, -1.25f, 0.125f, 0.5f, 2.25f, 0.75f); // prawa ręka
  DrawCube(0.125f, -3.15f, 0.125f, 1.0f, 2.25f, 0.90f); // lewa noga
  glPopMatrix();

  glPushMatrix();
  glRotatef(15 * sin(RuchCzlowieka*0.1f + 4.712388), 1, 0, 0);
  DrawCube(-0.5f, -1.25f, 0.125f, 0.5f, 2.25f, 0.75f); // lewa ręka
  DrawCube(1.25f, -3.15f, 0.125f, 1.0f, 2.25f, 0.90f); // prawa noga
  glPopMatrix();
  glEnd();
  glPopMatrix();

}
