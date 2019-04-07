#include <Windows.h>
#include <atlstr.h>
#include "Res.h"
#include <stdlib.h>
#include <ctime>
int aaiBoard[3][3];
const int marginX=10;
const int marginY=10;
const int fieldDy = 40;
const int fieldDx = 40;
int innerMargin=10;
int iCurrentPlayer = 1;
int iLiczbaTur=0;
int iSprawdzanie = 0;
HWND hwndMainWindow;
int iSprawdzenie = 0;
int iPunktyO ;
int iPunktyX ;
bool bKoniecGry; 
bool bBlokada;

void drawO(HDC hDC, int x, int y) {
  int cx = x + fieldDx / 2;
  int cy = y + fieldDy / 2;
  int r = fieldDy / 2 - innerMargin;
    MoveToEx(hDC, cx + r, cy, NULL);
      for (int alpha = 0; alpha <= 360; alpha += 1) {
        LineTo(hDC, cx + r * cos(alpha*3.141592/180), cy + r * sin(alpha*3.141592 / 180));
    }
}

void drawX(HDC hDC, int x, int y) {
  MoveToEx(hDC,x + innerMargin,y+innerMargin,NULL);
  LineTo(hDC, x + fieldDx - innerMargin, y + fieldDy - innerMargin);
  MoveToEx(hDC, x + innerMargin, y + fieldDy - innerMargin, NULL);
  LineTo(hDC, x + fieldDx - innerMargin, y  + innerMargin);

  
  
}
HINSTANCE hInst;
INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
  switch (uMsg)
  {
  case WM_CREATE:
    UpdateWindow(hwndDlg);
    break;
  case WM_PAINT:
  {
    HWND hWndst = GetDlgItem(hwndDlg, IDC_STATIC1);
    HWND hWndst2 = GetDlgItem(hwndDlg, IDC_STATIC2);
    HDC hDC = GetDC(hwndDlg);// rysowanie szachownicy
    MoveToEx(hDC, marginX, marginY + fieldDy, NULL);
    LineTo(hDC, marginX+fieldDx*3 , marginY + fieldDy);
    MoveToEx(hDC, marginX, marginY + 2*fieldDy, NULL);
    LineTo(hDC, marginX + (3 * fieldDx), marginY + 2 * fieldDy);
    // |
    MoveToEx(hDC, marginX+ fieldDx, marginY, NULL);
    LineTo(hDC, marginX + fieldDx, marginY + 3*fieldDy);
    MoveToEx(hDC, marginX+fieldDx*2, marginY, NULL);
    LineTo(hDC, marginX + fieldDx * 2, marginY + 3 * fieldDy);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (aaiBoard[i][j] == 2)drawX(hDC, marginX + i * fieldDx, marginY + j * fieldDy);
        if (aaiBoard[i][j] == 1)drawO(hDC, marginX + i * fieldDx, marginY + j * fieldDy);
      }
    }
    

    if (iSprawdzenie != 0) {
      if (iSprawdzenie == 2 && bKoniecGry == true) {
        bKoniecGry = false;
        bBlokada = true;
        TextOut(hDC, 0, 0, TEXT("WYGRAŁ GRACZ X"), 15);
        iPunktyX++;
        CString sMessage2 = TEXT("");
        sMessage2.Format(TEXT("Punkty X: %d"), iPunktyX);
        SetWindowText(hWndst2, _T(sMessage2));
        UpdateWindow(hwndDlg);
        
      }
      else if (iSprawdzenie == 1 && bKoniecGry==true) {
        bKoniecGry = false;
        bBlokada = true;
        TextOut(hDC, 0, 0, TEXT("WYGRAŁ GRACZ O"), 15);
        iPunktyO++;
        CString sMessage = TEXT("");
        sMessage.Format(TEXT("Punkty O: %d"), iPunktyO);
        SetWindowText(hWndst, _T(sMessage));
        UpdateWindow(hwndDlg);
        bKoniecGry = false;
      }
     
    }
   
    

    


    ReleaseDC(hwndDlg, hDC);
  }
  return true;

  case WM_COMMAND:
    switch (HIWORD(wParam))
    {
    
    case BN_CLICKED://zdarzenie klikniecia na UI
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON1:
        // klikniecie na przycisk
        for (int i = 0; i < 3; i++) {
          for (int j = 0; j < 3; j++) {
            aaiBoard[i][j] = 0;
          }
        }
        iSprawdzenie = 0;
        iLiczbaTur = 0;
        InvalidateRect(hwndDlg, NULL, TRUE);
        bBlokada = false;
        UpdateWindow(hwndDlg);

       

        return TRUE;
      }
    }
    return FALSE;
  case WM_LBUTTONDOWN:
  {
    HDC hDC = GetDC(hwndDlg);
    if(bBlokada==false){
   
    int x = LOWORD(IParam);
    int y = HIWORD(IParam);
    int i = (x - marginX) / fieldDx;
    int j = (y - marginY) / fieldDy;
    if (aaiBoard[i][j] == 0) {
      aaiBoard[i][j] = iCurrentPlayer;
      iLiczbaTur++;
    }
    if (iCurrentPlayer == 1)iCurrentPlayer = 2;
    else iCurrentPlayer = 1;
    
    if (iLiczbaTur == 9) {
      TextOut(hDC, 0, 0, TEXT("REMIS!"), 7);
    }
    if (iLiczbaTur >= 5) {
      for (int i = 0; i < 3; i++) {
        if ((aaiBoard[i][0] == 1 && aaiBoard[i][1] == 1 && aaiBoard[i][2] == 1) || (aaiBoard[i][0] == 2 && aaiBoard[i][1] == 2 && aaiBoard[i][2] == 2)) {
          iSprawdzenie = aaiBoard[i][0];
        }
        else if (((aaiBoard[0][i] == 1 && aaiBoard[1][i] == 1 && aaiBoard[2][i] == 1) || (aaiBoard[0][i] == 2 && aaiBoard[1][i] == 2 && aaiBoard[2][i] == 2))) {
          iSprawdzenie = aaiBoard[0][i];
        }

      }
      if (((aaiBoard[0][0] == 1 && aaiBoard[1][1] == 1 && aaiBoard[2][2] == 1) || (aaiBoard[0][0] == 2 && aaiBoard[1][1] == 2 && aaiBoard[2][2] == 2))) {
        iSprawdzenie = aaiBoard[0][0];
      }
      else if (((aaiBoard[0][2] == 1 && aaiBoard[1][1] == 1 && aaiBoard[2][0] == 1) || (aaiBoard[0][2] == 2 && aaiBoard[1][1] == 2 && aaiBoard[2][0] == 2))) {
        iSprawdzenie = aaiBoard[1][1];
      }
    }
    

    bKoniecGry = true;
  }
    
    return TRUE;
  }
   case WM_CLOSE:
      DestroyWindow(hwndDlg);//zniszczenie okna
      PostQuitMessage(0);//Umieszczenie w petli komunikatow polecenia zakonczenia aplikacji
      return TRUE;
   
  }
return FALSE;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
  bBlokada = false;
  bKoniecGry = false;
  iPunktyO = 0;
  iPunktyX = 0;
  iSprawdzanie = 0;
  iLiczbaTur = 0;
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++) {
      aaiBoard[i][j]=0;
    }
  }
  hInst = hInstance;
    HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
    ShowWindow(hwndMainWindow, iCmdShow);
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    

  return 0;
  
}
