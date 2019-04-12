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
static float kat;
float Scale;
bool Move;
float MoveHumanRight;
float MoveHumanLeft;
float minsi;

void DrawCube(float x, float y,float z,float dx,float dy, float dz)
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
  //Move = false;
  glPushMatrix();
  glTranslatef(x, y, z); // zmiana po³o¿enia "œwiata"
  glScalef(dx, dy, dz); // przeskalowanie "œwiata"
  DrawCube(0.5f, 1.5f, 0, 1, 1,1); // g³owa
  DrawCube(0.75f , 1.25f, 0.25f , 0.5f , 0.25f , 0.5f ); // Szyja
  DrawCube(0.0f , -1.0f, -0.25f , 2.0f , 2.25f , 1.5f ); // tu³ów
   
  
    
  
    MoveHumanRight += 0.01f;
    //MoveHumanLeft += 0.1f;
    glPushMatrix();
    glRotatef(15*sin(MoveHumanRight*0.1f + 1.570796), 1, 0, 0);
     DrawCube(2.0f , -1.25f, 0.125f , 0.5f , 2.25f , 0.75f ); // prawa rêka
    DrawCube(0.125f , -3.15f, 0.125f , 1.0f , 2.25f , 0.90f ); // lewa noga
    glPopMatrix();


    glPushMatrix();
    glRotatef(15 * sin(MoveHumanRight*0.1f + 4.712388), 1, 0, 0);
    DrawCube(-0.5f , -1.25f, 0.125f , 0.5f , 2.25f , 0.75f ); // lewa rêka
    DrawCube(1.25f , -3.15f, 0.125f , 1.0f , 2.25f , 0.90f ); // prawa noga
    glPopMatrix();
    glEnd();
    glPopMatrix();
  
}
void DrawArmy()
{
  DrawHuman(0,0,0,1,1,1);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 5; j++) {
      DrawHuman(3 * i, 0, 3*j, 1, 1, 1);

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
  kat+=0.01f;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0, 0, -10);
  
    glRotatef(kat, 1, 1, 0);
  
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
  
  DrawArmy();
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
    CHAR szText[200];
    wsprintf(szText, "Kliknales myszka x=%d, y=%d", LOWORD(IParam), HIWORD(IParam));
    MessageBox(hwndDlg, szText, TEXT("klikneiecie"), MB_OK);

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
  MoveHumanRight = 0;
  kat = 50;
  hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  static PIXELFORMATDESCRIPTOR pfd =//struktura formatu pixeli
  {
    sizeof(PIXELFORMATDESCRIPTOR),//rozmiar struktury
    1,//numer wersji
    PFD_DRAW_TO_WINDOW |          //format musi obs³ugiwac okienka windows
    PFD_SUPPORT_OPENGL |          //format musi obslugiwac open gl
    PFD_DOUBLEBUFFER,             //w³aczenie podwojnego buferowania
    PFD_TYPE_RGBA,                //w³aczenie trybu koloru RGB
    16,                           //Ustawienie  trybu koloru
    0, 0, 0, 0, 0, 0,             //ignorowane bity koloru
    0,                            //brak buforu kana³u Alpha
    0,0,0, 0, 0, 0,               //Ignorowanie przesuniecia akumulatora
    16,                           //16 bitowy bufor g³
    0,                            //no stencil buffer
    0,                            //no auxiliary buffer
    PFD_MAIN_PLANE,               //g³owana warstwa tysowania
    0,                            //zarezerwowane
    0, 0, 0                       // ignorowane warstwy maski
  };
  HDC hDC = NULL;
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
      DrawGLScene();
      SwapBuffers(hDC);
    }
  }
  
  if (hRC) {
    !wglMakeCurrent(NULL, NULL);//usuniecie kontekstu renderowanie
    !wglDeleteContext(hRC);//usuniecie kontekstu renderowanie
    hRC = NULL;//wyzerowanie kontekstu
    }
  if (hDC && !ReleaseDC(hwndMainWindow, hDC)) { hDC = NULL; }//wyzerowanie kontekstu
  if (hwndMainWindow && !DestroyWindow(hwndMainWindow)) { hwndMainWindow = NULL; }//wyzerowanie uchwytu okienka







  //sMessage.Format(TEXT("Wybierz liczbe z zakresu od 1 do 40. Czy ta liczba jest wiêksza od %d ?"), SrodekPrzedzialu);

  //int iRetKey = MessageBox(0, sMessage ,"GRA", MB_YESNO);
    //sz- ciag znakow       hwnd -uchwyt       u-unignet int      a - wektor
  return 0;
  //gra odwrotna komputer wybiera liczbe a my zgadujemy wpisuj¹c wartoœæ w okienko !
}
