#include <Windows.h>
#include <atlstr.h>
#include "Res.h"
#pragma comment(lib, "winmm.lib")
INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
  switch (uMsg)
  {
  case EN_CHANGE:
    switch (LOWORD(wParam))
  {
    HWND hwndEditBox = GetDlgItem(hwndDlg, IDC_EDIT1);// poranie uchwytu kontrolki IDC_EDIT1
    int iTextLength = GetWindowTextLength(hwndEditBox);//pobranie dl tekstu
    CHAR szText[500];
    GetWindowText(hwndEditBox, szText, iTextLength + 1);//pobranie tekstu
    SetWindowText((HWND)IParam, szText);
    return TRUE;
  }
  case WM_COMMAND:
    switch (HIWORD(wParam))
    {
    
    case BN_CLICKED://zdarzenie klikniecia na UI
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON1:// Klikniecie na przycisku
        MessageBox(hwndDlg, TEXT("test"), TEXT("Klikniecie"), MB_OK);
        //zmienic pole text na przycisku na ten z edit box
        HWND hwndEditBox = GetDlgItem(hwndDlg, IDC_EDIT1);// poranie uchwytu kontrolki IDC_EDIT1

        int iTextLength = GetWindowTextLength(hwndEditBox);//pobranie dl tekstu
        CHAR szText[500];
        GetWindowText(hwndEditBox, szText, iTextLength + 1);//pobranie tekstu
        SetWindowText((HWND)IParam, szText);

        return TRUE;
      }
    }
    return FALSE;
    //obsluga myszki:
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
  
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);
  WAVEFORMATEX pcmWaveFormat; //definicja formatu tekstu
  pcmWaveFormat.wFormatTag = WAVE_FORMAT_PCM;//format probek
  pcmWaveFormat.nChannels = 1;//liczba kana³ow
  pcmWaveFormat.nSamplesPerSec = 44100L;//prbkowanie
  pcmWaveFormat.wBitsPerSample = 8;//ilosc bitow na probke
  pcmWaveFormat.nAvgBytesPerSec = 44100L;//ilosc bajtow na sekunde
  pcmWaveFormat.nBlockAlign = 1;
  pcmWaveFormat.cbSize = 0;
  MMRESULT mmResult;
  HWAVEOUT hwo=0; //uchwyt do interfejsu urz odtwo
  UINT devId;
  for (devId = 0; devId < waveOutGetNumDevs(); devId++)
  {
    mmResult = waveOutOpen(&hwo, devId, &pcmWaveFormat, 0, 0, CALLBACK_NULL);
    if (mmResult == MMSYSERR_NOERROR)break;
  }
      if(mmResult!=MMSYSERR_NOERROR)
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

      //wype³nienie bufora probkami o czest 880HZ
      for (int i = 0; i < whdr.dwBufferLength; i++) {
        //whdr.lpData[i] = (127 * sin(i*1200.0*3.141592 / (double)pcmWaveFormat.nSamplesPerSec) + 128+ (127 * sin(i*1000.0*3.141592 / (double)pcmWaveFormat.nSamplesPerSec) + 128)>0?127:-127)/2;
        if (i < whdr.dwBufferLength / 2) {
          whdr.lpData[i] = (127 * sin(i*1200.0*3.141592 / (double)pcmWaveFormat.nSamplesPerSec) + 128);
        }
        else whdr.lpData[i] = (127 * sin(i*20000*3.141592 / (double)pcmWaveFormat.nSamplesPerSec) + 128);

      }
      waveOutSetVolume(hwo, 0xFFFFFFFF);
      mmResult = waveOutPrepareHeader(hwo, &whdr, sizeof(WAVEHDR));
      if (mmResult != MMSYSERR_NOERROR) {
        MessageBox(hwndMainWindow, TEXT("nie mozna zainicjowac karty"), TEXT("ERROR"), MB_OK);
        return mmResult;
      }
      mmResult = waveOutWrite(hwo, &whdr, sizeof(WAVEHDR));
      if(mmResult != MMSYSERR_NOERROR)
      {
        MessageBox(hwndMainWindow, TEXT("nie mozna zaladowac probek"), TEXT("ERROR"), MB_OK);
        return mmResult;
      }
      while ((whdr.dwFlags & WHDR_DONE) != WHDR_DONE) Sleep(100);
     
      mmResult = waveOutUnprepareHeader(hwo, &whdr, sizeof(WAVEHDR));
      mmResult = waveOutClose(hwo);
      delete[] whdr.lpData;




 // while (true);
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);

  }
    








  //sMessage.Format(TEXT("Wybierz liczbe z zakresu od 1 do 40. Czy ta liczba jest wiêksza od %d ?"), SrodekPrzedzialu);

  //int iRetKey = MessageBox(0, sMessage ,"GRA", MB_YESNO);
    //sz- ciag znakow       hwnd -uchwyt       u-unignet int      a - wektor
  return 0;
  //gra odwrotna komputer wybiera liczbe a my zgadujemy wpisuj¹c wartoœæ w okienko !
}
