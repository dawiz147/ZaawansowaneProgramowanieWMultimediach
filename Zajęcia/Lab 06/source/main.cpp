#include <Windows.h>
#include <atlstr.h>
#include "Res.h"
#include <gl\GL.h> // OpenGL32
#include <gl\GLU.h> // GLu32
//#include <gl\glaux.h> //Header File For The Glaux

//biblioteki
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
//#pragma comment(lib, "glaux.lib")
HWND hwndMainWindow;
static float kat;

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
int DrawGLScene(GLvoid)\
{
  kat+=0.01f;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0, 0, -10);
  
    glRotatef(kat, 10, 10, 0);
  
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
  kat = 50;
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







  //sMessage.Format(TEXT("Wybierz liczbe z zakresu od 1 do 40. Czy ta liczba jest wi�ksza od %d ?"), SrodekPrzedzialu);

  //int iRetKey = MessageBox(0, sMessage ,"GRA", MB_YESNO);
    //sz- ciag znakow       hwnd -uchwyt       u-unignet int      a - wektor
  return 0;
  //gra odwrotna komputer wybiera liczbe a my zgadujemy wpisuj�c warto�� w okienko !
}
