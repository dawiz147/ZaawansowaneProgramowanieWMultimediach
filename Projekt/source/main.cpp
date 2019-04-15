#include <Windows.h>
#include <atlstr.h>
#include "Res.h"
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
GLfloat fKameraPositionX=0.0f;
GLfloat fKameraPositionY=0.0f;
GLfloat fKameraPositionZ=-10.0f;
bool bKey[6] = { false };
HDC hDC;
float HeightMap[7*7] =
{ 0.5f,0.5f,0.5f,0.5f,0.5f,0.5f,0.5f,
  0.5f, 0, 0, 0, 0, 0, 0.5f,
  0.5f, 0, 0, 0, 0, 0, 0.5f,
  0.5f, 0, 0, 0, 0, 0, 0.5f,
  0.5f, 0, 0, 0, 0, 0, 0.5f,
  0.5f, 0, 0, 0, 0, 0, 0.5f,
  0.5f, 0.5f,0.5f,0.5f,0.5f,0.5f,0.5f,
}; // TAB 2D
/*Mo�na te� tak :
 * float HeightMap[5][5] =
{{ 1,1,1,1,1,}
 { 1.5f, 1.15f, 1.25f, 1.115f, 1.85f,}
  {0.5f, 0.15f, 0.25f, 0.115f, 0.85f,}
  {0,0,0,0,0,}
  0.35f, 0.35f, 0.65f, 0.17f, 0.67f,
}; // TAB 2D
 */

void DrawCube(float x, float y,float z,float dx,float dy, float dz)
{
  glPushMatrix();// zapisanie ustawie� "�wiata"

  glTranslatef(x, y, z); // zmiana po�o�enia "�wiata"
  glScalef(dx, dy, dz); // przeskalowanie "�wiata"
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
  glPopMatrix(); // wczytanie podstawowych ustawie� 

}
void DrawHeightMap() // funkcja rysujaca HeighMape
{
  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      glPushMatrix();
      //glRotatef(90, 1, 0, 0);
      DrawCube(j, i, 0, 1, 1, HeightMap[i * 7 + j]);
      
      glPopMatrix();
    }
  }

}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
{
  if (height == 0)
  {
    height = 1;
  }
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int DrawGLScene(GLvoid)
{
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  Obrot+=0.01f;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
 
  glTranslatef(-4, -4, fKameraPositionZ); // zmiana po�o�enia "�wiata"
  
   // glRotatef(-90, 0, 1, 0);
  
  glBegin(GL_LINES);
  glColor3d(1, 0, 0);
  glVertex3d(10, 0, 0);
  glVertex3d(-10, 0, 0);

  glColor3d(0, 1, 0);
  glVertex3d(0, 10, 0);
  glVertex3d(0, -10, 0);

  glColor3d(0, 0, 1);
  glVertex3d(0, 0, 10);
  glVertex3d(0, 0, -10);
  glEnd();
  
  //DrawArmy();
  DrawHeightMap();
  if (bKey[0]) fKameraPositionX -= 0.01f;
  if (bKey[1]) fKameraPositionX += 0.01f;
  if (bKey[2]) fKameraPositionY -= 0.01f;
  if (bKey[3]) fKameraPositionY += 0.01f;
  DrawCube(5 - fKameraPositionX, 1 - fKameraPositionY, 0, 1, 1, 0.5f);
  return 1;
}

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
  switch (uMsg)
  {
  case WM_CREATE:
    return TRUE;
  case WM_PAINT:
  {

    return FALSE;
  }
  case WM_KEYDOWN:
  {
    if(wParam==VK_RIGHT)
    {
      bKey[0] = true;
    }
    if (wParam == VK_LEFT)
    {
      bKey[1] = true;
    }
    if (wParam == VK_UP)
    {
      bKey[2] = true;
    }
    if (wParam == VK_DOWN)
    {
      bKey[3] = true;
    }

    return TRUE;
  }
  case WM_TIMER:
    DrawGLScene();
    SwapBuffers(hDC);
    return TRUE;
  case WM_KEYUP:
  {
    if (wParam == VK_RIGHT)
    {
      bKey[0] = false;
    }
    if (wParam == VK_LEFT)
    {
      bKey[1] = false;
    }
    if (wParam == VK_UP)
    {
      bKey[2] = false;
    }
    if (wParam == VK_DOWN)
    {
      bKey[3] = false;
    }
    return TRUE;
  }

  case WM_SIZE:
  {
    ReSizeGLScene(LOWORD(IParam), HIWORD(IParam));

  }
    return TRUE;
  case EN_CHANGE:
    switch (LOWORD(wParam))
  {
    
    return TRUE;
  }
  case WM_COMMAND:
    switch (HIWORD(wParam))
    {
    
    case BN_CLICKED://zdarzenie klikniecia na UI
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON1:// Klikniecie na przycisku
        

        return TRUE;
      }

    }
    return FALSE;
  case WM_LBUTTONDOWN:
  

    return TRUE;

   case WM_CLOSE:
      DestroyWindow(hwndDlg);//zniszczenie okna
      PostQuitMessage(0);//Umieszczenie w petli komunikatow polecenia zakonczenia aplikacji
      return TRUE;
   
  }
return FALSE;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
  RuchCzlowieka = 0;
  Obrot = 50;
  hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  static PIXELFORMATDESCRIPTOR pfd =//struktura formatu pixeli
  {
    sizeof(PIXELFORMATDESCRIPTOR),//rozmiar struktury
    1,//numer wersji
    PFD_DRAW_TO_WINDOW |          //format musi obs�ugiwac okienka windows
    PFD_SUPPORT_OPENGL |          //format musi obslugiwac open gl
    PFD_DOUBLEBUFFER,             //w�aczenie podwojnego buferowania
    PFD_TYPE_RGBA,                //w�aczenie trybu koloru RGB
    16,                           //Ustawienie  trybu koloru
    0, 0, 0, 0, 0, 0,             //ignorowane bity koloru
    0,                            //brak buforu kana�u Alpha
    0,0,0, 0, 0, 0,               //Ignorowanie przesuniecia akumulatora
    16,                           //16 bitowy bufor g�
    0,                            //no stencil buffer
    0,                            //no auxiliary buffer
    PFD_MAIN_PLANE,               //g�owana warstwa tysowania
    0,                            //zarezerwowane
    0, 0, 0                       // ignorowane warstwy maski
  };
 // HDC hDC = NULL;
  HGLRC hRC = NULL;
  GLuint PixelFormat;

  if (!(hDC = GetDC(hwndMainWindow))) return 0; //pobieranie kontekstu
  if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd))) return 0; //wyszukiwanie formatu pixeli

  if (!SetPixelFormat(hDC, PixelFormat, &pfd)) return 0;// ustawienie formatu pixeli
  if (!(hRC = wglCreateContext(hDC))) return 0;//pobranie kontekstu renderowania
  if (!wglMakeCurrent(hDC, hRC)) return 0;//uruchomienie kontekstu renderowania

  ShowWindow(hwndMainWindow, SW_SHOW);
  SetForegroundWindow(hwndMainWindow);
  SetFocus(hwndMainWindow);
  SetTimer(hwndMainWindow, 100, 10, NULL);
 
  MSG msg = {};
  BOOL done = false;
  while (!done)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT) { done = TRUE; }
      else
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }
    else
    {
     // DrawGLScene();
     // SwapBuffers(hDC);
    }
  }
  
  if (hRC) {
    !wglMakeCurrent(NULL, NULL);//usuniecie kontekstu renderowanie
    !wglDeleteContext(hRC);//usuniecie kontekstu renderowanie
    hRC = NULL;//wyzerowanie kontekstu
    }
  if (hDC && !ReleaseDC(hwndMainWindow, hDC)) { hDC = NULL; }//wyzerowanie kontekstu
  if (hwndMainWindow && !DestroyWindow(hwndMainWindow)) { hwndMainWindow = NULL; }//wyzerowanie uchwytu okienka


  return 0;
 
}
