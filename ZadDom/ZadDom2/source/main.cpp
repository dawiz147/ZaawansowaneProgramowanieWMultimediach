#include <Windows.h>
#include <atlstr.h>
#include "Res.h"
#include <stdlib.h>
#include <ctime>

int LosowaLiczba,licznik;
INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
  switch (uMsg)
  {

  case WM_COMMAND:
    switch (HIWORD(wParam))
    {
    
    case BN_CLICKED://zdarzenie klikniecia na UI
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON1: // klikniecie na przycisk
        HWND hwndEditBox = GetDlgItem(hwndDlg, IDC_EDIT1);// poranie uchwytu kontrolki IDC_EDIT1

        int iTextLength = GetWindowTextLength(hwndEditBox);//pobranie dl tekstu
        CHAR szText[500];
        GetWindowText(hwndEditBox, szText, iTextLength + 1);//pobranie tekstu
        SetWindowText((HWND)IParam, szText);
        int WpisanaLiczba = atoi(szText); // przypisanie liczby z CHAR szText
        if (WpisanaLiczba >= 0 && WpisanaLiczba <= 100) {
          if (WpisanaLiczba == LosowaLiczba)
          {
            CString sMessage = TEXT("");
            sMessage.Format(TEXT("Uda³o Ci siê trafiæ po %d próbach"), licznik);
            int iRetKey = MessageBox(0, sMessage, "BRAWO!!!", MB_OK);
          }
          else if (WpisanaLiczba > LosowaLiczba)
          {
            SetWindowText((HWND)IParam, "wpisana liczba jest za du¿a");
            licznik++;
          }
          else if (WpisanaLiczba < LosowaLiczba) {
            SetWindowText((HWND)IParam, "wpisana liczba jest za ma³a");
            licznik++;
          }
        }
        else int iRetKey = MessageBox(0, "Coœ posz³o nie tak...", "UPS!", MB_OK);
       

        return TRUE;
      }
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
  int iRetKey = MessageBox(0, "zagrajmy w grê! wylosuje dla Ciebie liczbe z przedzia³u od 1-100 a ty zgadnij co to za liczba!", "GRA", MB_OK);
    srand((time(NULL)));
    LosowaLiczba = rand() % 100 + 1;

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
