#include "winmine.h"

void updateMenuCheckmarks(void) {
  updateMenuCheckmark(MENUCHK_DIFFICULTY_BEGINNER, (uint)((short)g_state_difficulty == 0));
  updateMenuCheckmark(MENUCHK_DIFFICULTY_INTERMEDIATE, (uint)((short)g_state_difficulty == 1));
  updateMenuCheckmark(MENUCHK_DIFFICULTY_EXPERT, (uint)((short)g_state_difficulty == 2));
  updateMenuCheckmark(MENUCHK_DIFFICULTY_CUSTOM, (uint)((short)g_state_difficulty == 3));
  updateMenuCheckmark(MENUCHK_DIFFICULTY_COLOR, g_state_color);
  updateMenuCheckmark(MENUCHK_DIFFICULTY_MARK, g_state_marks);
  updateMenuCheckmark(MENUCHK_DIFFICULTY_SOUND, g_state_sound);
  return;
}

int readRegIntClampedOrDefault(int value_id, int default_value, int lower_bound, int upper_bound) {
  LSTATUS LVar1;
  int iVar2;
  DWORD local_8;

  local_8 = 4;
  LVar1 = RegQueryValueExW(hKey, (LPCWSTR)(&PTR_u_Difficulty_010050d0)[value_id], (LPDWORD)0x0,
                           (LPDWORD)0x0, (LPBYTE)&value_id, &local_8);
  if (LVar1 == 0) {
    iVar2 = upper_bound;
    if (value_id <= upper_bound) {
      iVar2 = value_id;
    }
    default_value = lower_bound;
    if ((lower_bound <= iVar2) && (default_value = upper_bound, value_id <= upper_bound)) {
      default_value = value_id;
    }
  }
  return default_value;
}

void readRegStringClampedOrDefault(int value_id, LPWSTR destination) {
  LSTATUS LVar1;
  DWORD local_8;

  local_8 = 0x40;
  // Nan:
  // TODO: turn PTR_u_Difficulty_010050d0 into a table of strings
  LVar1 = RegQueryValueExW(hKey, (LPCWSTR)(&PTR_u_Difficulty_010050d0)[value_id], (LPDWORD)0x0,
                           (LPDWORD)0x0, (LPBYTE)destination, &local_8);
  if (LVar1 != 0) {
    lstrcpyW(destination, (LPCWSTR)&g_default_anon_name);
  }
  return;
}

void loadSettingsFromRegistry(void) {
  char cVar1;
  int iVar2;
  HWND hWnd;
  HDC hdc;
  undefined3 extraout_var;
  int lower_bound;
  int upper_bound;
  DWORD lpdwDisposition;

  RegCreateKeyExW((HKEY)&HKEY_CURRENT_USER, L"Software\\Microsoft\\winmine", 0, (LPWSTR)NULL,
                  REG_OPTION_NON_VOLATILE, KEY_READ, (LPSECURITY_ATTRIBUTES)NULL, &hKey,
                  &lpdwDisposition);
  g_state_board_height = readRegIntClampedOrDefault(REG_IDX_HEIGHT, 9, 9, 0x19);
  g_state_board_height_maybe = g_state_board_height;
  g_state_board_width = readRegIntClampedOrDefault(REG_IDX_WIDTH, 9, 9, 0x1e);
  g_state_board_width_maybe = g_state_board_width;
  iVar2 = readRegIntClampedOrDefault(REG_IDX_DIFFICULTY, 0, 0, 3);
  // g_state_difficulty._0_2_ = (undefined2)iVar2;
  g_state_difficulty = iVar2;
  g_state_mine_counter = readRegIntClampedOrDefault(REG_IDX_MINES, 10, 10, 999);
  g_state_xpos = readRegIntClampedOrDefault(REG_IDX_XPOS, 0x50, 0, 0x400);
  g_state_ypos = readRegIntClampedOrDefault(REG_IDX_YPOS, 0x50, 0, 0x400);
  g_state_sound = readRegIntClampedOrDefault(REG_IDX_SOUND, 0, 0, 3);
  g_state_marks = readRegIntClampedOrDefault(REG_IDX_MARK, 1, 0, 1);
  g_state_tick = readRegIntClampedOrDefault(REG_IDX_TICK, 0, 0, 1);
  g_state_menu = readRegIntClampedOrDefault(REG_IDX_MENU, 0, 0, 2);
  g_state_time1 = readRegIntClampedOrDefault(REG_IDX_TIME1, 999, 0, 999);
  g_state_time2 = readRegIntClampedOrDefault(REG_IDX_TIME2, 999, 0, 999);
  g_state_time3 = readRegIntClampedOrDefault(REG_IDX_TIME3, 999, 0, 999);
  readRegStringClampedOrDefault(REG_IDX_NAME1, g_state_name1);
  readRegStringClampedOrDefault(REG_IDX_NAME2, g_state_name2);
  readRegStringClampedOrDefault(REG_IDX_NAME3, g_state_name3);
  hWnd = GetDesktopWindow();
  hdc = GetDC(hWnd);
  upper_bound = 1;
  lower_bound = 0;
  // Nan:
  // iVar2 = num_colors
  iVar2 = GetDeviceCaps(hdc, NUMCOLORS);
  g_state_color = readRegIntClampedOrDefault(10, iVar2 != 2, lower_bound, upper_bound);
  hWnd = GetDesktopWindow();
  ReleaseDC(hWnd, hdc);
  if (g_state_sound == 3) {
    cVar1 = stopAllSounds();
    g_state_sound = CONCAT31(extraout_var, cVar1);
  }
  RegCloseKey(hKey);
  return;
}

void setRegInt(int target_key, int data) {
  // Nan:
  // Should probably have a table of values for they keys instead of indexing
  // PTR_u_Difficulty_010050d0
  RegSetValueExW(hKey, (LPCWSTR)(&PTR_u_Difficulty_010050d0)[target_key], 0, REG_DWORD,
                 (BYTE *)&data, 4);
  return;
}

void setRegStr(int param_1, LPCWSTR param_2) {
  int iVar1;

  iVar1 = lstrlenW(param_2);
  RegSetValueExW(hKey, (LPCWSTR)(&PTR_u_Difficulty_010050d0)[param_1], 0, 1, (BYTE *)param_2,
                 iVar1 * 2 + 2);
  return;
}

void commitSettingsToRegister(void) {
  DWORD lpdwDisposition;

  RegCreateKeyExW((HKEY)&HKEY_CURRENT_USER, L"Software\\Microsoft\\winmine", 0, (LPWSTR)NULL,
                  REG_OPTION_NON_VOLATILE, KEY_WRITE, (LPSECURITY_ATTRIBUTES)NULL, &hKey,
                  &lpdwDisposition);
  setRegInt(REG_IDX_DIFFICULTY, (uint)(ushort)g_state_difficulty);
  setRegInt(REG_IDX_HEIGHT, g_state_board_height_maybe);
  setRegInt(REG_IDX_WIDTH, g_state_board_width_maybe);
  setRegInt(REG_IDX_MINES, g_state_mine_counter);
  setRegInt(REG_IDX_MARK, g_state_marks);
  setRegInt(REG_IDX_ALREADY_PLAYED, 1);
  setRegInt(REG_IDX_COLOR, g_state_color);
  setRegInt(REG_IDX_SOUND, g_state_sound);
  setRegInt(REG_IDX_XPOS, g_state_xpos);
  setRegInt(REG_IDX_YPOS, g_state_ypos);
  setRegInt(REG_IDX_TIME1, g_state_time1);
  setRegInt(REG_IDX_TIME2, g_state_time2);
  setRegInt(REG_IDX_TIME3, g_state_time3);
  setRegStr(REG_IDX_NAME1, g_state_name1);
  setRegStr(REG_IDX_NAME2, g_state_name2);
  setRegStr(REG_IDX_NAME3, g_state_name3);
  RegCloseKey(hKey);
  return;
}

UINT getIntFromIniFileClamped(int reg_value_name_idx, INT default_value, UINT lower_bound, UINT upper_bound) {
  UINT UVar1;
  UINT UVar2;
  LPCWSTR key_name;

  key_name = (LPCWSTR)(&PTR_u_Difficulty_010050d0 + reg_value_name_idx);
  UVar1 = GetPrivateProfileIntW((LPCWSTR)&g_class_name, *(LPCWSTR *)key_name, default_value,
                                g_ini_file_name_u_entpack_ini_01005120);
  UVar2 = upper_bound;
  if ((int)UVar1 <= (int)upper_bound) {
    UVar2 = GetPrivateProfileIntW((LPCWSTR)&g_class_name, *(LPCWSTR *)key_name, default_value,
                                  g_ini_file_name_u_entpack_ini_01005120);
  }
  if (((int)lower_bound <= (int)UVar2) &&
      (UVar2 = GetPrivateProfileIntW((LPCWSTR)&g_class_name, *(LPCWSTR *)key_name, default_value,
                                     g_ini_file_name_u_entpack_ini_01005120),
       lower_bound = upper_bound, (int)UVar2 <= (int)upper_bound)) {
    lower_bound = GetPrivateProfileIntW((LPCWSTR)&g_class_name, *(LPCWSTR *)key_name, default_value,
                                        g_ini_file_name_u_entpack_ini_01005120);
  }
  return lower_bound;
}

void getStrFromIniFile(int reg_value_name_idx, LPWSTR lpReturnedString) {
  GetPrivateProfileStringW((LPCWSTR)&g_class_name,
                           (LPCWSTR)(&PTR_u_Difficulty_010050d0)[reg_value_name_idx],
                           (LPCWSTR)&g_default_anon_name, lpReturnedString, 0x20,
                           g_ini_file_name_u_entpack_ini_01005120);
  return;
}

void initSettingsFirstTime(void) {
  char cVar1;
  DWORD DVar2;
  int iVar3;
  LSTATUS LVar4;
  UINT UVar5;
  HWND pHVar6;
  HDC hdc;
  undefined3 extraout_var;
  DWORD DStack_4;
  UINT UVar7;

  DVar2 = GetTickCount();
  srand(DVar2 & 0xffff);
  getStrFromResources(1, (LPWSTR)&g_class_name, 0x20);
  getStrFromResources(7, (LPWSTR)&fmt_seconds_string, 0x20);
  getStrFromResources(8, (LPWSTR)&g_default_anon_name, 0x20);
  iVar3 = GetSystemMetrics(SM_CYCAPTION);
  g_caption_height = iVar3 + 1;
  iVar3 = GetSystemMetrics(SM_CYMENU);
  g_menu_height = iVar3 + 1;
  iVar3 = GetSystemMetrics(SM_CYBORDER);
  g_border_height = iVar3 + 1;
  iVar3 = GetSystemMetrics(SM_CXBORDER);
  g_window_width = iVar3 + 1;
  LVar4 = RegCreateKeyExW((HKEY)&HKEY_CURRENT_USER, L"Software\\Microsoft\\winmine", 0, (LPWSTR)0x0,
                          0, 0x20019, (LPSECURITY_ATTRIBUTES)0x0, &hKey, &DStack_4);
  if (LVar4 == 0) {
    iVar3 = readRegIntClampedOrDefault(0x11, 0, 0, 1);
    RegCloseKey(hKey);
    if (iVar3 != 0) {
      return;
    }
  }
  g_state_board_height_maybe = getIntFromIniFileClamped(2, 9, 9, 0x19);
  g_state_board_width_maybe = getIntFromIniFileClamped(3, 9, 9, 0x1e);
  UVar5 = getIntFromIniFileClamped(0, 0, 0, 3);
  // g_state_difficulty._0_2_ = (undefined2)UVar5;
  g_state_difficulty = UVar5;
  g_state_mine_counter = getIntFromIniFileClamped(1, 10, 10, 999);
  g_state_xpos = getIntFromIniFileClamped(4, 0x50, 0, 0x400);
  g_state_ypos = getIntFromIniFileClamped(5, 0x50, 0, 0x400);
  g_state_sound = getIntFromIniFileClamped(6, 0, 0, 3);
  g_state_marks = getIntFromIniFileClamped(7, 1, 0, 1);
  g_state_tick = getIntFromIniFileClamped(9, 0, 0, 1);
  g_state_menu = getIntFromIniFileClamped(8, 0, 0, 2);
  g_state_time1 = getIntFromIniFileClamped(0xb, 999, 0, 999);
  g_state_time2 = getIntFromIniFileClamped(0xd, 999, 0, 999);
  g_state_time3 = getIntFromIniFileClamped(0xf, 999, 0, 999);
  getStrFromIniFile(0xc, g_state_name1);
  getStrFromIniFile(0xe, g_state_name2);
  getStrFromIniFile(0x10, g_state_name3);
  pHVar6 = GetDesktopWindow();
  hdc = GetDC(pHVar6);
  UVar7 = 1;
  UVar5 = 0;
  iVar3 = GetDeviceCaps(hdc, 0x18);
  g_state_color = getIntFromIniFileClamped(10, iVar3 != 2, UVar5, UVar7);
  pHVar6 = GetDesktopWindow();
  ReleaseDC(pHVar6, hdc);
  if (g_state_sound == 3) {
    cVar1 = stopAllSounds();
    g_state_sound = CONCAT31(extraout_var, cVar1);
  }
  commitSettingsToRegister();
  return;
}

void updateMenuCheckmark(ushort menu_item, int checked) {
  // Nan:
  // hMenu: The menu of interest
  // uIDCheckItem: The menu _item_ of interest
  // uCheck: flags. este chorizo se lee tal que
  // - if param_2  = 0 --> uCheck = 0 = MF_UNCHECKED
  // - if param_2 != 0 --> uCheck = 8 = MF_CHECKED
  CheckMenuItem(hGameMenu, (uint)menu_item, -(uint)(checked != 0) & 8);
  return;
}

void FUN_01003ce5(uint param_1) {
  g_state_menu = param_1;
  updateMenuCheckmarks();
  SetMenu(hWnd, (HMENU)(~-(uint)((g_state_menu & 1U) != 0) & hGameMenu));
  maybeUpdateWindowLayoutIDK(2);
  return;
}
