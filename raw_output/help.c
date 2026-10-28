#include "winmine.h"

void showAboutWindow(void) {
  HICON hIcon;
  WCHAR title_bar[128];
  WCHAR other_stuff[128];

  getStrFromResources(RES_STR_ABOUT_APP, title_bar, 0x80);
  getStrFromResources(RES_STR_ABOUT_OTHER_STUFF, other_stuff, 0x80);
  // g_icon_name_00000064 --> 0x64
  hIcon = LoadIconW(hModule, MAKEINTRESOURCEW(RES_ICONGROUP));
  ShellAboutW(hWnd, title_bar, other_stuff, hIcon);
  return;
}

void FUN_01003d76(short param_1, uint param_2) {
  char *pcVar1;
  DWORD DVar2;
  HWND pHVar3;
  char *pcVar4;
  char *pcVar5;
  undefined4 uVar6;
  char local_100[252];

  if (param_1 == 4) {
    builtin_strncpy(local_100, "NTHelp.chm", 10);
    pcVar1 = local_100 + 10;
    pcVar4 = "";
  } else {
    DVar2 = GetModuleFileNameA(hModule, local_100, 0xfa);
    pcVar5 = local_100 + (DVar2 - 1);
    if ((4 < (int)pcVar5 - (int)local_100) && (local_100[DVar2 - 4] == '.')) {
      pcVar5 = local_100 + (DVar2 - 4);
    }
    pcVar1 = pcVar5 + 4;
    pcVar4 = "";
    builtin_strncpy(pcVar5, ".chm", 4);
  }
  uVar6 = 0;
  pcVar5 = local_100;
  *pcVar1 = *pcVar4;
  pHVar3 = GetDesktopWindow();
  FUN_01004062(pHVar3, pcVar5, param_2, uVar6);
  return;
}

HWND FUN_01004062(HWND hwndCaller, LPCSTR helpFile, UINT command, ULONG_PTR data) {
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  BYTE local_108[260];

  if ((DAT_01005180 == (HMODULE)0x0) && (DAT_01005188 == 0)) {
    bVar1 = FUN_010040fb(local_108);
    if (CONCAT31(extraout_var, bVar1) != 0) {
      DAT_01005180 = LoadLibraryA((LPCSTR)local_108);
    }
    if (DAT_01005180 != (HMODULE)0x0)
      goto LAB_010040bf;
    DAT_01005180 = LoadLibraryA("hhctrl.ocx");
    if (DAT_01005180 != (HMODULE)0x0)
      goto LAB_010040bf;
  LAB_010040da:
    DAT_01005188 = 1;
    iVar2 = 0;
  } else {
  LAB_010040bf:
    if (DAT_01005190 == (FARPROC)0x0) {
      DAT_01005190 = GetProcAddress(DAT_01005180, &DAT_0000000e);
      if (DAT_01005190 == (FARPROC)0x0)
        goto LAB_010040da;
    }
    iVar2 = (*DAT_01005190)(param_1, param_2, param_3, param_4);
  }
  return iVar2;
}

bool FUN_010040fb(LPBYTE param_1) {
  LSTATUS LVar1;
  bool bVar2;
  DWORD local_c;
  HKEY local_8;

  LVar1 = RegOpenKeyExA((HKEY)&DAT_80000000,
                        "CLSID\\{ADB880A6-D8FF-11CF-9377-00AA003B7A11}\\InprocServer32", 0, 0x20019,
                        &local_8);
  if (LVar1 == 0) {
    local_c = 0x104;
    LVar1 = RegQueryValueExA(local_8, "", (LPDWORD)0x0, (LPDWORD)0x0, param_1, &local_c);
    bVar2 = LVar1 == 0;
    RegCloseKey(local_8);
  } else {
    bVar2 = false;
  }
  return bVar2;
}
