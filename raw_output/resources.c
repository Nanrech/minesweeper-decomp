#include "winmine.h"

void showMessageBoxError(ushort str_id) {
  WCHAR msgbox_text[128];
  WCHAR msgbox_caption[128];

  if (str_id < 999) {
    LoadStringW(hModule, (uint)str_id, msgbox_text, 0x80);
  } else {
    LoadStringW(hModule, 6, msgbox_caption, 0x80);
    wsprintfW(msgbox_text, msgbox_caption, (uint)str_id);
  }
  LoadStringW(hModule, 3, msgbox_caption, 0x80);
  MessageBoxW((HWND)0x0, msgbox_text, msgbox_caption, MB_ICONERROR);
  return;
}

void getStrFromResources(ushort str_id, LPWSTR buffer, int buffer_max_size) {
  int iVar1;

  iVar1 = LoadStringW(hModule, (uint)str_id, buffer, buffer_max_size);
  if (iVar1 == 0) {
    showMessageBoxError(0x3e9);
  }
  return;
}
