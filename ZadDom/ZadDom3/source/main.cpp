#include <Windows.h>
#include <atlstr.h>
#include "Res.h"
#include <stdlib.h>
#include <ctime>
HINSTANCE hInst;

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
  switch (uMsg)
  {
  case WM_CREATE:
    break;
  case WM_PAINT:

    HDC hDC; //uchwyt do kontekstu urzadzenia
    hDC = GetDC(hwndDlg);//pobranie uchwytu do kontekstu okna
    HBITMAP hBitmap;// w nawiasie kolor tekstu
    hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
    HDC hDCBitmap;
    hDCBitmap = CreateCompatibleDC(hDC);
    SelectObject(hDCBitmap, hBitmap);
    BitBlt(hDC, 0, 0, 900, 400, hDCBitmap, 0, 0, SRCCOPY);
    DeleteDC(hDCBitmap);
    DeleteObject(hBitmap);
    ReleaseDC(hwndDlg, hDC);// zwolnienie kontekstu urzadzenia
    break;

      

  case WM_COMMAND:
    switch (HIWORD(wParam))
    {
    
    case BN_CLICKED:
      switch (LOWORD(wParam))
      {
      
        }
       
       

        return TRUE;
      }
    
    return FALSE;
   case WM_CLOSE:
      DestroyWindow(hwndDlg);//zniszczenie okna
      PostQuitMessage(0);//Umieszczenie w petli komunikatow polecenia zakonczenia aplikacji
      return TRUE;
   
  }
return FALSE;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
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
