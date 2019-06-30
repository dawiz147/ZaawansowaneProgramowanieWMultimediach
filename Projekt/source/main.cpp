#include <Windows.h>
#include <atlstr.h>
#include "Res.h"
#include <gl\GL.h> // OpenGL32
#include <gl\GLU.h> // GLu32
#include <vector>

#include <process.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "winmm.lib")

HWND hwndMainWindow;
HINSTANCE hInst;
HDC hDC;

DWORD WINAPI Music(LPVOID)
{

    WAVEFORMATEX pcmWaveFormat; 
    pcmWaveFormat.wFormatTag = WAVE_FORMAT_PCM;
    pcmWaveFormat.nChannels = 1;
    pcmWaveFormat.nSamplesPerSec = 44100L;
    pcmWaveFormat.wBitsPerSample = 8;
    pcmWaveFormat.nAvgBytesPerSec = 44100L;
    pcmWaveFormat.nBlockAlign = 1;
    pcmWaveFormat.cbSize = 0;
    MMRESULT mmResult;
    HWAVEOUT hwo = 0; 
    UINT devId;
    for (devId = 0; devId < waveOutGetNumDevs(); devId++)
    {
      mmResult = waveOutOpen(&hwo, devId, &pcmWaveFormat, 0, 0, CALLBACK_NULL);
      if (mmResult == MMSYSERR_NOERROR)break;
    }
    if (mmResult != MMSYSERR_NOERROR)
    {
      MessageBox(hwndMainWindow, TEXT("Nie znaleziono karty dziekowaej o wymaganych parametrach"), TEXT("ERROR"), MB_OK);
      return mmResult;
    }
    WAVEHDR whdr;
    ZeroMemory(&whdr, sizeof(WAVEHDR));
    whdr.lpData = new char[pcmWaveFormat.nAvgBytesPerSec * 5];
    whdr.dwBufferLength = pcmWaveFormat.nAvgBytesPerSec * 5;
    whdr.dwUser = 0;
    whdr.dwFlags = 0;
    whdr.dwLoops = 0;
    whdr.dwBytesRecorded = 0;
    whdr.lpNext = 0;
    whdr.reserved = 0;
  
    for (int i = 0; i < whdr.dwBufferLength; i++) {
      if (i < whdr.dwBufferLength / 2) {
        whdr.lpData[i] = (127 * sin(i*1200.0*3.141592 / (double)pcmWaveFormat.nSamplesPerSec) + 128);
      }
      else whdr.lpData[i] = (127 * sin(i * 20000 * 3.141592 / (double)pcmWaveFormat.nSamplesPerSec) + 128);

    }
    waveOutSetVolume(hwo, 0xFFFFFFFF);
    mmResult = waveOutPrepareHeader(hwo, &whdr, sizeof(WAVEHDR));
    if (mmResult != MMSYSERR_NOERROR) {
      MessageBox(hwndMainWindow, TEXT("nie mozna zainicjowac karty"), TEXT("ERROR"), MB_OK);
      return mmResult;
    }
    mmResult = waveOutWrite(hwo, &whdr, sizeof(WAVEHDR));
    if (mmResult != MMSYSERR_NOERROR)
    {
      MessageBox(hwndMainWindow, TEXT("nie mozna zaladowac probek"), TEXT("ERROR"), MB_OK);
      return mmResult;
    }
    while (true) {
    while ((whdr.dwFlags & WHDR_DONE) != WHDR_DONE) Sleep(100);

    mmResult = waveOutUnprepareHeader(hwo, &whdr, sizeof(WAVEHDR));
    mmResult = waveOutClose(hwo);
    delete[] whdr.lpData;
  }
  return 0;
}





bool Menu = true;
bool bKey[6] = { false };
float PlayerPositionX;
float PlayerPositionY;
float BoxPositionX;
float BoxPositionY;
float PlacePositionX;
float PlacePositionY;
float LevelOne[12][12] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0.5,0,0,1,0,0,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,0,0,0,0,1},
  {1,0,0,0,0,1,0,0,0,0,0,1},
  {1,0,0.75,0,0,0,0,0,0,1,-0.1,1},
  {1,0,0,0,0,0,0,0,0,0,1,1},
  {1,1,1,1,1,1,1,1,1,1,1,1},


};





void DrawCube(float x, float y,float z,float dx,float dy, float dz)
{
  glPushMatrix();// zapisanie ustawieñ "œwiata"

  glTranslatef(x, y, z); // zmiana po³o¿enia "œwiata"
  glScalef(dx, dy, dz); // przeskalowanie "œwiata"
  glBegin(GL_QUADS);
  if(dz==1)glColor3f(1, 0, 0);
  else if(dz==0.5f)glColor3f(1, 0, 1);
  else if(dz==0)glColor3f(1, 1, 1);
  else if (dz == 0.75f)glColor3f(0, 1, 0);
  else if (dz == -0.1f)glColor3f(1, 1, 0);
   
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glVertex3f(1, 1, 0);
    glVertex3f(1, 0, 0);

    glVertex3f(0, 0, 1);
    glVertex3f(0, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 0, 1);

    glVertex3f(0, 1, 1);
    glVertex3f(0, 1, 0);
    glVertex3f(1, 1, 0);
    glVertex3f(1, 1, 1);

    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(1, 0, 1);


    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(1, 0, 1);
    glVertex3f(0, 0, 1);

    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glVertex3f(0, 1, 1);
    glVertex3f(0, 0, 1);
 
  glEnd();
  glPopMatrix(); 

}
void CreateLevel() 
{
  
    for (int i = 0; i < 12; i++)
    {
      for (int j = 0; j < 12; j++)
      {
        if (LevelOne[i][j] == 1 || LevelOne[i][j] == 0 ) {
          glPushMatrix();
          glTranslatef(0, 0, 0);
          DrawCube(j*0.5f, i*0.5f, -1, 0.5f, 0.5f, LevelOne[i][j]);
          glPopMatrix();
        }
        else if(LevelOne[i][j]==0.5f)
        {
          PlayerPositionY = i;
          PlayerPositionX = j;
          LevelOne[i][j] = 0;
        }
        else if (LevelOne[i][j] == 0.75f)
        {
          BoxPositionY = i;
          BoxPositionX = j;
          LevelOne[i][j] = 0;
        }
        else if (LevelOne[i][j] == -0.1f)
        {
          PlacePositionY = i;
          PlacePositionX = j;
         // LevelOne[i][j] = 0;
        }
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(-3, -3, -7.0f);
    CreateLevel();
    glEnd();
  if (BoxPositionY==PlacePositionY && BoxPositionX==PlacePositionX)
  {
    CString sMessage2 = TEXT("");
    sMessage2.Format(TEXT("X: %d, y: %d YOU WIN"), (int)PlayerPositionX, (int)PlayerPositionY);
    SetWindowText(hwndMainWindow, _T(sMessage2));
  }
    if ((LevelOne[(int)(PlayerPositionY)][(int)(PlayerPositionX - 1)] <= 0) ||((PlayerPositionX-1 ==BoxPositionX) && (PlayerPositionY==BoxPositionY) && LevelOne[(int)(BoxPositionY)][(int)(BoxPositionX-1)]<=0))
    {
      if (bKey[1]) {
        if((PlayerPositionX - 1 == BoxPositionX) && (PlayerPositionY == BoxPositionY) && LevelOne[(int)(BoxPositionY)][(int)(BoxPositionX - 1)] <= 0)
        {
          PlayerPositionX--;
          BoxPositionX--;
        }
        else if(LevelOne[(int)(PlayerPositionY)][(int)(PlayerPositionX - 1)] <= 0 && ((PlayerPositionX - 1 != BoxPositionX) || (PlayerPositionY != BoxPositionY)))
          PlayerPositionX--;
      }
    }
    //
    if ((LevelOne[(int)(PlayerPositionY)][(int)(PlayerPositionX + 1)] <= 0) || ((PlayerPositionX + 1 == BoxPositionX) && (PlayerPositionY == BoxPositionY) && LevelOne[(int)(BoxPositionY)][(int)(BoxPositionX + 1)] <= 0))
    {
      if (bKey[0]) {
        if ((PlayerPositionX + 1 == BoxPositionX) && (PlayerPositionY == BoxPositionY) && LevelOne[(int)(BoxPositionY)][(int)(BoxPositionX + 1)] <= 0)
        {
          PlayerPositionX++;
          BoxPositionX++;
        }
        else if (LevelOne[(int)(PlayerPositionY)][(int)(PlayerPositionX + 1)] <= 0 && ((PlayerPositionX + 1 != BoxPositionX) || (PlayerPositionY != BoxPositionY)))
          PlayerPositionX++;
      }
    }

    if ((LevelOne[(int)(PlayerPositionY+1)][(int)(PlayerPositionX )] <= 0) || ((PlayerPositionY + 1 == BoxPositionY) && (PlayerPositionX == BoxPositionX) && LevelOne[(int)(BoxPositionY+1)][(int)(BoxPositionX)] <= 0))
    {
      if (bKey[2]) {
        if ((PlayerPositionY + 1 == BoxPositionY) && (PlayerPositionX == BoxPositionX) && LevelOne[(int)(BoxPositionY+1)][(int)(BoxPositionX )] <= 0)
        {
          PlayerPositionY++;
          BoxPositionY++;
        }
        else if (LevelOne[(int)(PlayerPositionY+1)][(int)(PlayerPositionX)] <= 0 && ((PlayerPositionY + 1 != BoxPositionY) || (PlayerPositionX != BoxPositionX)))
          PlayerPositionY++;
      }
    }
 
    if((LevelOne[(int)(PlayerPositionY - 1)][(int)(PlayerPositionX)] <= 0) || ((PlayerPositionY - 1 == BoxPositionY) && (PlayerPositionX == BoxPositionX) && LevelOne[(int)(BoxPositionY - 1)][(int)(BoxPositionX)] <= 0))
    {
      if (bKey[3]) {
        if ((PlayerPositionY - 1 == BoxPositionY) && (PlayerPositionX == BoxPositionX) && LevelOne[(int)(BoxPositionY +-1)][(int)(BoxPositionX)] <= 0)
        {
          PlayerPositionY--;
          BoxPositionY--;
        }
        else if (LevelOne[(int)(PlayerPositionY - 1)][(int)(PlayerPositionX)] <= 0 && ((PlayerPositionY - 1 != BoxPositionY) || (PlayerPositionX != BoxPositionX)))
          PlayerPositionY--;
      }
    }
 
   // CString sMessage2 = TEXT("");
   // sMessage2.Format(TEXT("X: %d, y: %d, xb:%d, yb:%d"), (int)PlayerPositionX, (int)PlayerPositionY,(int)BoxPositionX, (int)BoxPositionY);
   // SetWindowText(hwndMainWindow, _T(sMessage2));
    DrawCube(PlayerPositionX*0.5f, PlayerPositionY*0.5f, -1, 0.5f, 0.5f, 0.5f);
    DrawCube(BoxPositionX*0.5f, BoxPositionY*0.5f, -1, 0.5f, 0.5f, 0.75f);
    DrawCube(PlacePositionX*0.5f, PlacePositionY*0.5f, -1, 0.5f, 0.5f, -0.1f);
    return 1;
  }



INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
  switch (uMsg)
  {
  case WM_CREATE:
    CreateThread(0, 0, Music, 0, 0, NULL);
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
  SetTimer(hwndMainWindow, 100, 250, NULL);
 
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
