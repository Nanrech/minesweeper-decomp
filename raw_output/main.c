#include "winmine.h"

LRESULT Wndproc(HWND hWnd, uint uMsg, uint wParam, uint lParam) {
  char cVar1;
  HDC pHVar2;
  undefined3 extraout_var;
  uint uVar3;
  undefined3 extraout_var_00;
  int iVar4;
  BOOL BVar5;
  int x;
  LRESULT LVar6;
  bool bVar7;
  bool bVar8;
  short sVar9;
  undefined4 uVar10;
  tagPAINTSTRUCT lpPaint;

  // Nan:
  // This is the main Wndproc function
  // The signature should be LRESULT CALLBACK Wndproc(...)
  //
  // Trying to set equate for every one of these uMsg codes is a pain in the ass
  // Sometimes ghidra decides that a message should be represented as WM_X + n if
  // the message is close enough to another message's value
  if (uMsg < 0x201) {
    if (uMsg != 0x200) {
      if (uMsg < 0x101) {
        if (uMsg != 0x100) {
          if (uMsg == 2) {
            // Nan:
            // 1 here is the id of a timer so it should be renamed
            KillTimer(hWnd_main, 1);
            PostQuitMessage(0);
          } else {
            // Nan:
            // 6 = WM_ACTIVATE
            // wParam = WA_INACTIVE (0), WA_ACTIVE (1), WA_CLICKACTIVE (2)
            if (uMsg == 6) {
              if ((wchar_t)wParam == L'\x02') {
                DAT_01005148_ACTIVEMAYBE = 1;
              }
            } else {
              if (uMsg == 0xf) {
                pHVar2 = BeginPaint(hWnd, &lpPaint);
                drawGameHDC(pHVar2);
                EndPaint(hWnd, &lpPaint);
                return 0;
              }
              if ((uMsg == 0x47) && ((g_state_game_flags & 8) == 0)) {
                g_state_xpos = *(int *)(lParam + 8);
                g_state_ypos = *(int *)(lParam + 0xc);
              }
            }
          }
          goto switchD_01001f75_caseD_203;
        }
        if (wParam == 0x10) {
          if (4 < (int)DAT_01005154) {
            DAT_01005154 = DAT_01005154 ^ 0x14;
          }
          goto switchD_01001f75_caseD_203;
        }
        if (wParam == 0x73) {
          if (1 < g_state_sound) {
            if (g_state_sound == 3) {
              stopAllSoundsButWeird();
              g_state_sound = 2;
            } else {
              cVar1 = stopAllSounds();
              g_state_sound = CONCAT31(extraout_var, cVar1);
            }
          }
          goto switchD_01001f75_caseD_203;
        }
        if (wParam == 0x74) {
          if (g_state_menu == 0)
            goto switchD_01001f75_caseD_203;
          uVar3 = 1;
        } else {
          if (wParam != 0x75) {
            if ((int)DAT_01005154 < 5) {
              DAT_01005154 =
                  ~-(uint)(u_XYZZY_01005034[DAT_01005154] != (wchar_t)wParam) & DAT_01005154 + 1;
            }
            goto switchD_01001f75_caseD_203;
          }
          if (g_state_menu == 0)
            goto switchD_01001f75_caseD_203;
          uVar3 = 2;
        }
      } else {
        if (uMsg != 0x111) {
          if (uMsg == 0x112) {
            if ((wParam & 0xfff0) == 0xf020) {
              FUN_0100341c();
              g_state_game_flags = g_state_game_flags | 10;
            } else if ((wParam & 0xfff0) == 0xf120) {
              g_state_game_flags = g_state_game_flags & 0xf5;
              FUN_0100344c();
              DAT_01005148_ACTIVEMAYBE = 0;
            }
          } else if (uMsg == 0x113) {
            tickGameTimer();
            return 0;
          }
          goto switchD_01001f75_caseD_203;
        }
        uVar3 = wParam & 0xffff;
        if (uVar3 < 0x211) {
          if (uVar3 == 0x210) {
            showHighScores();
            goto switchD_01001f75_caseD_203;
          }
          if (uVar3 == 0x1fe) {
            prepareNewGame();
            goto switchD_01001f75_caseD_203;
          }
          if (uVar3 == 0x200) {
            ShowWindow(hWnd_main, 0);
            goto LAB_01001eac;
          }
          if (uVar3 < 0x209)
            goto switchD_01001f75_caseD_203;
          if (uVar3 < 0x20c) {
            g_state_difficulty._0_2_ = (wchar_t)wParam + L'ﷷ';
            iVar4 = (uint)(ushort)g_state_difficulty * 0xc;
            g_state_mine_counter = *(int *)(&DAT_01005010 + iVar4);
            g_state_board_height_maybe = *(int *)(&DAT_01005014 + iVar4);
            g_state_board_width_maybe = *(int *)(&DAT_01005018 + iVar4);
            prepareNewGame();
          } else {
            if (uVar3 == 0x20c) {
              inputCustomGameParams();
              goto switchD_01001f75_caseD_203;
            }
            if (uVar3 == 0x20e) {
              if (g_state_sound == 0) {
                cVar1 = stopAllSounds();
                g_state_sound = CONCAT31(extraout_var_00, cVar1);
              } else {
                stopAllSoundsButWeird();
                g_state_sound = 0;
              }
            } else {
              if (uVar3 != 0x20f)
                goto switchD_01001f75_caseD_203;
              g_state_marks = (int)(g_state_marks == 0);
            }
          }
        } else {
          if (uVar3 != 0x211) {
            if (uVar3 == 0x24e) {
              uVar10 = 0;
              sVar9 = 3;
            } else if (uVar3 == 0x24f) {
              uVar10 = 2;
              sVar9 = 1;
            } else {
              if (uVar3 != 0x250) {
                if (uVar3 == 0x251) {
                  showAboutWindow();
                  return 0;
                }
                goto switchD_01001f75_caseD_203;
              }
              uVar10 = 0;
              sVar9 = 4;
            }
            FUN_01003d76(sVar9, uVar10);
            goto switchD_01001f75_caseD_203;
          }
          g_state_color = (uint)(g_state_color == 0);
          destroyGDIObjects();
          iVar4 = FUN_01002414_scary();
          if (iVar4 == 0) {
            showMessageBoxError(5);
          LAB_01001eac:
            SendMessageW(hWnd_main, 0x112, 0xf060, 0);
            return 0;
          }
          drawGame();
        }
        g_state_should_commit_to_register = 1;
        uVar3 = g_state_menu;
      }
      FUN_01003ce5(uVar3);
      goto switchD_01001f75_caseD_203;
    }
    goto LAB_01002085;
  }
  switch (uMsg) {
  case 0x201:
    if (DAT_01005148_ACTIVEMAYBE != 0) {
      DAT_01005148_ACTIVEMAYBE = 0;
      return 0;
    }
    BVar5 = handleClickingFace(lParam);
    if (BVar5 != 0) {
      return 0;
    }
    if ((g_state_game_flags & 1) == 0)
      goto switchD_01001f75_caseD_203;
    DAT_01005144 = (uint)((wParam & 6) != 0);
    break;
  case 0x202:
  case 0x205:
  case 0x208:
    if (DAT_01005140 == 0)
      goto switchD_01001f75_caseD_203;
    goto LAB_01001fed;
  default:
    goto switchD_01001f75_caseD_203;
  case 0x204:
    if (DAT_01005148_ACTIVEMAYBE != 0) {
      DAT_01005148_ACTIVEMAYBE = 0;
      return 0;
    }
    if ((g_state_game_flags & 1) == 0)
      goto switchD_01001f75_caseD_203;
    if (DAT_01005140 != 0) {
      FUN_010031d4(-3, -3);
      DAT_01005144 = 1;
      PostMessageW(hWnd_main, 0x200, wParam, lParam);
      return 0;
    }
    if ((wParam & 1) == 0) {
      if (DAT_0100514c == 0) {
        handleRightClickTile((int)((lParam & 0xffff) + 4) >> 4,
                             (int)((lParam >> 0x10) - 0x27) >> 4);
        return 0;
      }
      return 0;
    }
    break;
  case 0x207:
    if (DAT_01005148_ACTIVEMAYBE != 0) {
      DAT_01005148_ACTIVEMAYBE = 0;
      return 0;
    }
    if ((g_state_game_flags & 1) == 0)
      goto switchD_01001f75_caseD_203;
    DAT_01005144 = 1;
    break;
  case 0x211:
    DAT_0100514c = 1;
    goto switchD_01001f75_caseD_203;
  case 0x212:
    DAT_0100514c = 0;
    goto switchD_01001f75_caseD_203;
  }
  SetCapture(hWnd);
  g_mouse_tile_x = -1;
  g_mouse_tile_y = -1;
  DAT_01005140 = 1;
  drawFace(1);
LAB_01002085:
  if (DAT_01005140 != 0) {
    if ((g_state_game_flags & 1) == 0) {
    LAB_01001fed:
      DAT_01005140 = 0;
      ReleaseCapture();
      if ((g_state_game_flags & 1) != 0) {
        FUN_010037e1();
        goto switchD_01001f75_caseD_203;
      }
      iVar4 = -2;
      x = -2;
    } else {
      iVar4 = (int)((lParam >> 0x10) - 0x27) >> 4;
      x = (int)((lParam & 0xffff) + 4) >> 4;
    }
    FUN_010031d4(x, iVar4);
    goto switchD_01001f75_caseD_203;
  }
  if (DAT_01005154 == 0)
    goto switchD_01001f75_caseD_203;
  bVar8 = SBORROW4(DAT_01005154, 5);
  bVar7 = DAT_01005154 == 5;
  if (bVar7) {
    if ((wParam & 8) == 0) {
      bVar8 = FALSE;
      bVar7 = TRUE;
      goto LAB_010020db;
    }
  } else {
  LAB_010020db:
    if (bVar7 || bVar8 != (int)(DAT_01005154 - 5) < 0)
      goto switchD_01001f75_caseD_203;
  }
  g_mouse_tile_x = (int)((lParam & 0xffff) + 4) >> 4;
  g_mouse_tile_y = (int)((lParam >> 0x10) - 0x27) >> 4;
  if ((((g_mouse_tile_x != 0) && (0 < g_mouse_tile_y)) && (g_mouse_tile_x <= g_state_board_width)) &&
      (g_mouse_tile_y <= g_state_board_height)) {
    pHVar2 = GetDC((HWND)0x0);
    SetPixel(pHVar2, 0, 0,
             (-(uint)((g_mine_board[g_mouse_tile_y][g_mouse_tile_x] & TILE_HAS_MINE) != 0) &
              0xff000001) + 0xffffff);
    ReleaseDC((HWND)0x0, pHVar2);
  }
switchD_01001f75_caseD_203:
  LVar6 = DefWindowProcW(hWnd, uMsg, wParam, lParam);
  return LVar6;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  ATOM AVar1;
  HACCEL hAccTable;
  BOOL BVar2;
  int iVar3;
  ushort str_id;
  WNDCLASSW wc;
  tagMSG local_28;
  INITCOMMONCONTROLSEX local_c;

  // Nan:
  // Signature should prob be int WINAPI WinMain(...)
  hModule = hInstance;
  initSettingsFirstTime();
  if ((nCmdShow == 7) || (g_state_minimized = 0, nCmdShow == 2)) {
    g_state_minimized = 1;
  }
  local_c.dwSize = 8;
  local_c.dwICC = 0x16fd;
  InitCommonControlsEx(&local_c);
  // g_icon_name_00000064 --> 0x64
  hIcon = LoadIconW(hModule, MAKEINTRESOURCEW(0x64));
  wc.style = 0;
  wc.lpfnWndProc = Wndproc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hModule;
  wc.hIcon = hIcon;
  // DAT_00007f00 --> 0x7f00
  wc.hCursor = LoadCursorW((HINSTANCE)0x0, MAKEINTRESOURCEW(0x7f00));
  wc.hbrBackground = (HBRUSH)GetStockObject(1);
  wc.lpszMenuName = (LPCWSTR)0x0;
  wc.lpszClassName = (LPCWSTR)&g_class_name;
  AVar1 = RegisterClassW(&wc);
  if (AVar1 != 0) {
    // DAT_000001f4 --> 0x1f4
    hGameMenu = LoadMenuW(hModule, MAKEINTRESOURCEW(0x1f4));
    // DAT_000001f5 --> 0x1f5
    hAccTable = LoadAcceleratorsW(hModule, MAKEINTRESOURCEW(0x1f5));
    loadSettingsFromRegistry();
    hWnd_main = CreateWindowExW(0, (LPCWSTR)&g_class_name, (LPCWSTR)&g_class_name, 0xca0000,
                                g_state_xpos - g_window_width, g_state_ypos - g_window_height,
                                g_rect_offset_right + g_window_width,
                                g_rect_draw_preset_bottom_01005b20 + g_window_height, (HWND)0x0,
                                (HMENU)0x0, hModule, (LPVOID)0x0);
    if (hWnd_main == (HWND)0x0) {
      str_id = 1000;
    } else {
      maybeUpdateWindowLayoutIDK(1);
      BVar2 = FUN_01002b14();
      if (BVar2 != 0) {
        FUN_01003ce5(g_state_menu);
        prepareNewGame();
        ShowWindow(hWnd_main, 1);
        UpdateWindow(hWnd_main);
        g_state_minimized = 0;
        while (BVar2 = GetMessageW(&local_28, (HWND)0x0, 0, 0), BVar2 != 0) {
          iVar3 = TranslateAcceleratorW(hWnd_main, hAccTable, &local_28);
          if (iVar3 == 0) {
            TranslateMessage(&local_28);
            DispatchMessageW(&local_28);
          }
        }
        cleanupGameResources();
        if (g_state_should_commit_to_register == 0) {
          return local_28.wParam;
        }
        commitSettingsToRegister();
        return local_28.wParam;
      }
      str_id = 5;
    }
    showMessageBoxError(str_id);
  }
  return 0;
}
