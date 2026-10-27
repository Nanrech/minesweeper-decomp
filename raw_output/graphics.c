#include "winmine.h"

HRSRC findBitmapResourceMAYBE(int resource_id) {
  HRSRC pHVar1;

  pHVar1 =
      FindResourceW(hModule, MAKEINTRESOURCEW((uint)(g_state_color == 0) + resource_id & 0xffff),
                    MAKEINTRESOURCEW(0x2));
  return pHVar1;
}

int calculateBitmapDataSize(int width, int height) {
  return ((int)(((-(uint)(g_state_color != 0) & 3) + 1) * width + 0x1f) >> 3 & 0xfffffffcU) *
         height;
}

BOOL FUN_01002414_scary(void) {
  HRSRC pHVar1;
  int iVar2;
  HDC hdc;
  HDC pHVar3;
  HBITMAP pHVar4;
  undefined4 uVar5;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int *piVar6;
  int iVar7;

  DAT_01005954 = (HGLOBAL)0x0;
  DAT_01005a08 = (HGLOBAL)0x0;
  DAT_01005958 = (HGLOBAL)0x0;
  pHVar1 = findBitmapResourceMAYBE(0x19a);
  if (pHVar1 != (HRSRC)0x0) {
    DAT_01005958 = LoadResource(hModule, pHVar1);
  }
  pHVar1 = findBitmapResourceMAYBE(0x1a4);
  if (pHVar1 != (HRSRC)0x0) {
    DAT_01005a08 = LoadResource(hModule, pHVar1);
  }
  pHVar1 = findBitmapResourceMAYBE(0x1ae);
  if (pHVar1 != (HRSRC)0x0) {
    DAT_01005954 = LoadResource(hModule, pHVar1);
  }
  if (((DAT_01005958 == (HGLOBAL)0x0) || (DAT_01005a08 == (HGLOBAL)0x0)) ||
      (DAT_01005954 == (HGLOBAL)0x0)) {
    uVar5 = 0;
  } else {
    DAT_01005a04 = (BITMAPINFO *)LockResource(DAT_01005958);
    BITMAPINFO_number_maybe_0100595c = LockResource(DAT_01005a08);
    BITMAPINFO_face_maybe_01005a00 = LockResource(DAT_01005954);
    if (g_state_color == 0) {
      g_hPen = (HPEN)GetStockObject(7);
    } else {
      g_hPen = CreatePen(0, 1, 0x808080);
    }
    iVar2 = calculateBitmapDataSize(0x10, 0x10);
    piVar6 = &DAT_010059c0;
    iVar7 = extraout_ECX;
    do {
      *piVar6 = iVar7;
      piVar6 = piVar6 + 1;
      iVar7 = iVar7 + iVar2;
    } while ((int)piVar6 < 0x1005a00);
    iVar2 = calculateBitmapDataSize(0xd, 0x17);
    piVar6 = &bitmap_number_maybe_01005a60;
    iVar7 = extraout_ECX_00;
    do {
      *piVar6 = iVar7;
      piVar6 = piVar6 + 1;
      iVar7 = iVar7 + iVar2;
    } while ((int)piVar6 < 0x1005a90);
    iVar2 = calculateBitmapDataSize(0x18, 0x18);
    piVar6 = &bitmap_face_maybe_01005960;
    iVar7 = extraout_ECX_01;
    do {
      *piVar6 = iVar7;
      piVar6 = piVar6 + 1;
      iVar7 = iVar7 + iVar2;
    } while ((int)piVar6 < 0x1005974);
    hdc = GetDC(hWnd_main);
    iVar7 = 0;
    do {
      pHVar3 = CreateCompatibleDC(hdc);
      *(HDC *)((int)&DAT_01005a20 + iVar7) = pHVar3;
      if (pHVar3 == (HDC)0x0) {
        OutputDebugStringA("FLoad failed to create compatible dc\n");
      }
      pHVar4 = CreateCompatibleBitmap(hdc, 0x10, 0x10);
      *(undefined4 *)((int)&DAT_01005980 + iVar7) = pHVar4;
      if (pHVar4 == (HBITMAP)0x0) {
        OutputDebugStringA("Failed to create Bitmap\n");
      }
      SelectObject(*(HDC *)((int)&DAT_01005a20 + iVar7), *(HGDIOBJ *)((int)&DAT_01005980 + iVar7));
      SetDIBitsToDevice(
          *(HDC *)((int)&DAT_01005a20 + iVar7), 0, 0, 0x10, 0x10, 0, 0, 0, 0x10,
          (void *)((int)&(((BITMAPINFO *)(DAT_01005a04->bmiColors + -10))->bmiHeader).biSize +
                   *(int *)((int)&DAT_010059c0 + iVar7)),
          DAT_01005a04, 0);
      iVar7 = iVar7 + 4;
    } while (iVar7 < 0x40);
    ReleaseDC(hWnd_main, hdc);
    uVar5 = 1;
  }
  return uVar5;
}

void destroyGDIObjects(void) {
  int iVar1;

  if (g_hPen != (HGDIOBJ)0x0) {
    DeleteObject(g_hPen);
  }
  iVar1 = 0;
  do {
    DeleteDC(*(HDC *)((int)&DAT_01005a20 + iVar1));
    DeleteObject(*(HGDIOBJ *)((int)&DAT_01005980 + iVar1));
    iVar1 = iVar1 + 4;
  } while (iVar1 < 0x40);
  return;
}

void cleanupGameResources(void) {
  destroyGDIObjects();
  stopAllSoundsButWeird();
  return;
}

void drawTile(int x, int y) {
  HDC hdc;

  hdc = GetDC(hWnd_main);
  BitBlt(hdc, x * 0x10 + -4, y * 0x10 + 0x27, 0x10, 0x10,
         (HDC)(&DAT_01005a20)[(int)(char)g_mine_board[y][x] & TILE_STATE_MASK], 0, 0, 0xcc0020);
  ReleaseDC(hWnd_main, hdc);
  return;
}

void drawTilesHDC(HDC hdc) {
  int iVar1;
  int iVar2;
  int local_10;
  int local_c;
  int local_8;

  local_c = 0x37;
  local_10 = 1;
  if (0 < g_state_board_height) {
    iVar1 = 0x1005360;
    do {
      iVar2 = 1;
      local_8 = 0xc;
      if (0 < g_state_board_width) {
        do {
          BitBlt(hdc, local_8, local_c, 0x10, 0x10,
                 (HDC)(&DAT_01005a20)[*(byte *)(iVar1 + iVar2) & TILE_STATE_MASK], 0, 0, SRCCOPY);
          local_8 = local_8 + 0x10;
          iVar2 = iVar2 + 1;
        } while (iVar2 <= g_state_board_width);
      }
      local_10 = local_10 + 1;
      local_c = local_c + 0x10;
      iVar1 = iVar1 + 0x20;
    } while (local_10 <= g_state_board_height);
  }
  return;
}

void DrawTiles(void) {
  HDC hdc;

  hdc = GetDC(hWnd_main);
  drawTilesHDC(hdc);
  ReleaseDC(hWnd_main, hdc);
  return;
}

void drawNumber(HDC hdc, int x_dest, int num_to_display) {
  SetDIBitsToDevice(
      hdc, x_dest, 0x10, 0xd, 0x17, 0, 0, 0, 0x17,
      (void *)((int)&(
                   ((BITMAPINFO *)(BITMAPINFO_number_maybe_0100595c->bmiColors + -10))->bmiHeader)
                   .biSize +
               (&bitmap_number_maybe_01005a60)[num_to_display]),
      BITMAPINFO_number_maybe_0100595c, 0);
  return;
}

void drawMineCounterHDC(HDC hdc) {
  int iVar1;
  DWORD l;
  int num_to_display;

  l = GetLayout(hdc);
  if ((l & 1) != 0) {
    SetLayout(hdc, 0);
  }
  if (g_mines_left < 0) {
    num_to_display = 0xb;
    iVar1 = -g_mines_left;
  } else {
    num_to_display = g_mines_left / 100;
    iVar1 = g_mines_left;
  }
  drawNumber(hdc, 0x11, num_to_display);
  drawNumber(hdc, 0x1e, (iVar1 % 100) / 10);
  drawNumber(hdc, 0x2b, (iVar1 % 100) % 10);
  if ((l & 1) != 0) {
    SetLayout(hdc, l);
  }
  return;
}

void drawMineCounter(void) {
  HDC hdc;

  hdc = GetDC(hWnd_main);
  drawMineCounterHDC(hdc);
  ReleaseDC(hWnd_main, hdc);
  return;
}

void drawTimerHDC(HDC hdc) {
  int iVar1;
  DWORD l;
  int iVar2;

  iVar1 = g_state_timer_value;
  l = GetLayout(hdc);
  if ((l & 1) != 0) {
    SetLayout(hdc, 0);
  }
  iVar2 = iVar1 % 100;
  drawNumber(hdc, (g_rect_offset_right - g_window_width) + -0x38, iVar1 / 100);
  drawNumber(hdc, (g_rect_offset_right - g_window_width) + -0x2b, iVar2 / 10);
  drawNumber(hdc, (g_rect_offset_right - g_window_width) + -0x1e, iVar2 % 10);
  if ((l & 1) != 0) {
    SetLayout(hdc, l);
  }
  return;
}

void drawTimer(void) {
  HDC hdc;

  hdc = GetDC(hWnd_main);
  drawTimerHDC(hdc);
  ReleaseDC(hWnd_main, hdc);
  return;
}

void drawFaceHDC(HDC hdc, int face_id) {
  SetDIBitsToDevice(
      hdc, g_rect_offset_right + -0x18 >> 1, 0x10, 0x18, 0x18, 0, 0, 0, 0x18,
      (void *)((int)&(((BITMAPINFO *)(BITMAPINFO_face_maybe_01005a00->bmiColors + -10))->bmiHeader)
                   .biSize +
               (&bitmap_face_maybe_01005960)[face_id]),
      BITMAPINFO_face_maybe_01005a00, 0);
  return;
}

void drawFace(int face_id) {
  HDC hdc;

  hdc = GetDC(hWnd_main);
  drawFaceHDC(hdc, face_id);
  ReleaseDC(hWnd_main, hdc);
  return;
}

void setROPWrapper(HDC hdc, byte mix_mode) {
  if ((mix_mode & 1) == 0) {
    SetROP2(hdc, R2_COPYPEN);
    SelectObject(hdc, g_hPen);
  } else {
    SetROP2(hdc, R2_WHITE);
  }
  return;
}

void drawRectangle(HDC hdc, int rect_left, int rect_top, int rect_right, int rect_bottom, int rect_thickness, int mix_mode) {
  HDC hdc_00;
  int local_8;

  hdc_00 = hdc;
  local_8 = 0;
  // Nan:
  // This function might have to use a RECT struct
  setROPWrapper(hdc, (byte)mix_mode);
  if (0 < rect_thickness) {
    hdc = (HDC)rect_thickness;
    local_8 = rect_thickness;
    do {
      rect_bottom = rect_bottom + -1;
      MoveToEx(hdc_00, rect_left, rect_bottom, (LPPOINT)0x0);
      LineTo(hdc_00, rect_left, rect_top);
      rect_left = rect_left + 1;
      LineTo(hdc_00, rect_right, rect_top);
      rect_right = rect_right + -1;
      rect_top = rect_top + 1;
      hdc = (HDC)((int)&hdc[-1].unused + 3);
    } while (hdc != (HDC)0x0);
  }
  if (mix_mode < 2) {
    setROPWrapper(hdc_00, (byte)mix_mode ^ 1);
  }
  for (; local_8 != 0; local_8 = local_8 + -1) {
    rect_bottom = rect_bottom + 1;
    MoveToEx(hdc_00, rect_left, rect_bottom, (LPPOINT)0x0);
    rect_left = rect_left + -1;
    rect_right = rect_right + 1;
    LineTo(hdc_00, rect_right, rect_bottom);
    rect_top = rect_top + -1;
    LineTo(hdc_00, rect_right, rect_top);
  }
  return;
}

void drawGameFrame(HDC hdc) {
  int iVar1;
  int iVar2;

  iVar1 = g_rect_offset_right;
  iVar2 = g_rect_draw_preset_bottom;
  drawRectangle(hdc, 0, 0, g_rect_offset_right + -1, g_rect_draw_preset_bottom + -1, 3, 1);
  drawRectangle(hdc, 9, 0x34, iVar1 + -10, iVar2 + -10, 3, 0);
  drawRectangle(hdc, 9, 9, iVar1 + -10, 0x2d, 2, 0);
  drawRectangle(hdc, 0x10, 0xf, 0x38, 0x27, 1, 0);
  drawRectangle(hdc, (g_rect_offset_right - g_window_width) + -0x39, 0xf,
                (g_rect_offset_right - g_window_width) + -0x11, 0x27, 1, 0);
  iVar2 = g_rect_offset_right + -0x18 >> 1;
  drawRectangle(hdc, iVar2 + -1, 0xf, iVar2 + 0x18, 0x28, 1, 2);
  return;
}

void drawGameHDC(HDC hdc) {
  drawGameFrame(hdc);
  drawMineCounterHDC(hdc);
  drawFaceHDC(hdc, g_state_face);
  drawTimerHDC(hdc);
  drawTilesHDC(hdc);
  return;
}

void drawGame(void) {
  HDC hdc;

  hdc = GetDC(hWnd_main);
  drawGameHDC(hdc);
  ReleaseDC(hWnd_main, hdc);
  return;
}

BOOL FUN_01002b14(void) {
  int iVar1;

  iVar1 = FUN_01002414_scary();
  if (iVar1 == 0) {
    return 0;
  }
  clearBoard();
  return 1;
}
