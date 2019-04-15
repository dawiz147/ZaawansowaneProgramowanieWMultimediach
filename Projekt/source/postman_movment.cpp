#include "postman_movment.h"
#include <Windows.h>
#include <winuser.h>
int up_down = 0;
int left_right = 0;
int CheckTheKeyboardUpDown() {
  if (GetAsyncKeyState(VK_UP)) {
    up_down += 0.001f;
  }
  if (GetAsyncKeyState(VK_DOWN)) {
    up_down -= 0.001f;
  }
  return up_down;
}

int CheckTheKeyboardLeftRight() {
  if (GetAsyncKeyState(VK_LEFT)) {
    left_right += 0.001f;
  }
  if (GetAsyncKeyState(VK_RIGHT)) {
    left_right -= 0.001f;
  }
  return left_right;
}