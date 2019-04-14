#include <Windows.h>
#include <atlstr.h>
#include "Res.h"
#include <stdlib.h>
#include <ctime>
HINSTANCE hInst;
HWND hwndMainWindow;
HDC hDCBitmap;
HDC hDCBitmap2;
int XMousePos;
int YMousePos;
HDC hDC; //uchwyt do kontekstu urzadzenia
bool draw;
void HBITMAP_UserSize(double x, double x1);

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
  switch (uMsg)
  {
  case WM_CREATE:
    break;
  case WM_PAINT:
  {
    if (draw == true) {
      /*
      HBITMAP hBitmap2;// w nawiasie kolor tekstu
      hBitmap2 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
      HDC hDCBitmap2;
      hDCBitmap2 = CreateCompatibleDC(hDC);


      SelectObject(hDCBitmap2, hBitmap2);
      */
      HDC hDC; //uchwyt do kontekstu urzadzenia
      hDC = GetDC(hwndDlg);//pobranie uchwytu do kontekstu okna
      HBITMAP hBitmap;// w nawiasie kolor tekstu
      hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
      HDC hDCBitmap;
      hDCBitmap = CreateCompatibleDC(hDC);
      SelectObject(hDCBitmap, hBitmap);
      BitBlt(hDC, 0, 0, 900, 400, hDCBitmap, 0, 0, SRCCOPY);
      
     
      BitBlt(hDC, 0, 0, 100, 100, hDCBitmap, XMousePos, YMousePos, SRCCOPY);

      // RectangleF rect = new RectangleF(150, 200, 25, 25);
      DeleteDC(hDCBitmap);
      DeleteObject(hBitmap);
      ReleaseDC(hwndDlg, hDC);// zwolnienie kontekstu urzadzenia
      draw = false;
    }
    return true;
  }
     
      case WM_LBUTTONDOWN:
      {
        TextOut(hDC, 0, 0, TEXT("Text output to client area"), 100);
        int x = LOWORD(IParam);
        int y = HIWORD(IParam);
        XMousePos = x;
        YMousePos = y;
        draw = true;
       // BitBlt(hDC, 0, 0, 100, 100, hDCBitmap, XMousePos, YMousePos, SRCCOPY);
        //InvalidateRect(hwndDlg, NULL, TRUE);
       // UpdateWindow(hwndDlg);

        return true;
       
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
 
  draw = true;
  XMousePos=100;
  YMousePos=100;
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
