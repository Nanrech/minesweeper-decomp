#include "winmine.h"

int getScreenDimensions(int metric) {
  int iVar1;

  // Nan:
  // This here is a fucked up switch statement
  // switch (metric)
  // case 0:
  //   blablabla
  // case 1:
  //   blablabla
  // default:
  //   whatever
  if (metric == 0) {
    iVar1 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    if (iVar1 != 0) {
      return iVar1;
    }
    iVar1 = 0;
  } else {
    if (metric != 1) {
      // WARNING: Could not recover jumptable at 0x01001923. Too many branches
      // WARNING: Treating indirect jump as call
      iVar1 = GetSystemMetrics(metric);
      return iVar1;
    }
    iVar1 = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    if (iVar1 != 0) {
      return iVar1;
    }
    iVar1 = 1;
  }
  iVar1 = GetSystemMetrics(iVar1);
  return iVar1;
}

void maybeUpdateWindowLayoutIDK(uint param_1) {
  bool bVar1;
  BOOL BVar2;
  int iVar3;
  tagRECT local_30;
  tagRECT local_20;
  tagRECT local_10;

  bVar1 = FALSE;
  if (hWnd_main != (HWND)0x0) {
    g_window_height = g_caption_height;
    if ((((((byte)g_state_menu & 1) == 0) &&
          (g_window_height = g_menu_height + g_caption_height, hGameMenu != (HMENU)0x0)) &&
         (BVar2 = GetMenuItemRect(hWnd_main, hGameMenu, 0, &local_30), BVar2 != 0)) &&
        ((BVar2 = GetMenuItemRect(hWnd_main, hGameMenu, 1, &local_20),
          BVar2 != 0 && (local_30.top != local_20.top)))) {
      g_window_height = g_window_height + g_menu_height;
      bVar1 = TRUE;
    }
    g_rect_offset_right = g_state_board_width * 0x10 + 0x18;
    g_rect_draw_preset_bottom = g_state_board_height * 0x10 + 0x43;
    iVar3 = getScreenDimensions(0);
    iVar3 = (g_rect_offset_right + g_state_xpos) - iVar3;
    if (0 < iVar3) {
      param_1 = param_1 | 2;
      g_state_xpos = g_state_xpos - iVar3;
    }
    iVar3 = getScreenDimensions(1);
    iVar3 = (g_rect_draw_preset_bottom + g_state_ypos) - iVar3;
    if (0 < iVar3) {
      param_1 = param_1 | 2;
      g_state_ypos = g_state_ypos - iVar3;
    }
    if (g_state_minimized == 0) {
      if ((param_1 & 2) != 0) {
        MoveWindow(hWnd_main, g_state_xpos, g_state_ypos, g_window_width + g_rect_offset_right,
                   g_rect_draw_preset_bottom + g_window_height, 1);
      }
      if (((bVar1) && (hGameMenu != (HMENU)0x0)) &&
          ((BVar2 = GetMenuItemRect(hWnd_main, hGameMenu, 0, &local_30),
            BVar2 != 0 && ((BVar2 = GetMenuItemRect(hWnd_main, hGameMenu, 1, &local_20),
                            BVar2 != 0 && (local_30.top == local_20.top)))))) {
        g_window_height = g_window_height - g_menu_height;
        MoveWindow(hWnd_main, g_state_xpos, g_state_ypos, g_window_width + g_rect_offset_right,
                   g_rect_draw_preset_bottom + g_window_height, 1);
      }
      if ((param_1 & 4) != 0) {
        SetRect(&local_10, 0, 0, g_rect_offset_right, g_rect_draw_preset_bottom);
        InvalidateRect(hWnd_main, &local_10, 1);
      }
    }
  }
  return;
}
