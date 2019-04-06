#include <Windows.h>
#include <atlstr.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
  int koniec=40;
  int poczatek= 1;
  int srodek = (koniec+poczatek)/2;
  CString sMessage = TEXT("");
  sMessage.Format(TEXT("Wybierz liczbe z zakresu od 1 do 40."), srodek);

  int iRetKey = MessageBox(0, sMessage ,"GRA", MB_OK);
  while (poczatek <= koniec) {
    sMessage.Format(TEXT("Czy ta liczba jest wiêksza, lub równa od %d ?"), srodek);
    iRetKey = MessageBox(0, sMessage, "GRA", MB_YESNO);
    if (iRetKey == IDYES) 
    {
      poczatek = srodek+1;
      srodek = (koniec + poczatek) / 2;
    }
    else 
    {
      koniec = srodek-1;
      srodek = (koniec + poczatek) / 2;
    }
  }
  sMessage.Format(TEXT("TWOJA LICZBA TO: %d "), srodek);
  iRetKey = MessageBox(0, sMessage, "GRA", MB_OK);
  return 0;
}
