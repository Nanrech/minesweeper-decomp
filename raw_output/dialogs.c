#include "winmine.h"

BOOL handleClickingFace(uint lParam) {
  POINT pt;
  POINT pt_00;
  bool bVar1;
  BOOL BVar2;
  int face_id;
  tagMSG local_30;
  RECT face_area;

  local_30.pt.x = lParam & 0xffff;
  local_30.pt.y = lParam >> 0x10;
  face_area.left = g_rect_offset_right + -0x18 >> 1;
  face_area.right = face_area.left + 0x18;
  bVar1 = TRUE;
  face_area.top = 0x10;
  face_area.bottom = 0x28;
  // BVar2 = PtInRect(&face_area, (POINT)(CONCAT44(local_30.pt.y, lParam) & 0xffffffff0000ffff));
  BVar2 = PtInRect(&face_area, local_30.pt);
  if (BVar2 != 0) {
    SetCapture(hWnd);
    drawFace(4);
    MapWindowPoints(hWnd, (HWND)0x0, (LPPOINT)&face_area, 2);
  LAB_0100148c:
    do {
      do {
        BVar2 = PeekMessageW(&local_30, hWnd, 0x200, 0x20d, 1);
      } while (BVar2 == 0);
      if (local_30.message == 0x200) {
        pt.y = local_30.pt.y;
        pt.x = local_30.pt.x;
        BVar2 = PtInRect(&face_area, pt);
        if (BVar2 == 0) {
          if (!bVar1)
            goto LAB_0100148c;
          bVar1 = FALSE;
          face_id = g_state_face;
        } else {
          if (bVar1)
            goto LAB_0100148c;
          bVar1 = FALSE;
          face_id = 4;
        }
        drawFace(face_id);
        goto LAB_0100148c;
      }
    } while (local_30.message != 0x202);
    if (bVar1) {
      pt_00.y = local_30.pt.y;
      pt_00.x = local_30.pt.x;
      BVar2 = PtInRect(&face_area, pt_00);
      if (BVar2 != 0) {
        g_state_face = 0;
        drawFace(0);
        prepareNewGame();
      }
    }
    ReleaseCapture();
    BVar2 = 1;
  }
  return BVar2;
}

BOOL inputCustomGameParamsProc(HWND hDlg, int uMsg, HWND wParam, int lParam) {
  uint low_wParam;
  UINT UVar1;

  // Nan:
  // This is a custom dialogue callback function (a la WinProc)
  if (uMsg == WM_HELP) {
    UVar1 = HELP_WM_HELP;
    wParam = *(HWND *)(lParam + 0xc);
  LAB_call_winhelp:
    // Nan:
    // For some reason, 0x100540 is a literal (it should be a pointer)
    // >Address of an array of DWORD pairs. The first DWORD in each pair is the
    // control identifier, and the second is the context identifier for the topic.
    // The array must be terminated by a pair of zeros {0,0}. If you do not want to
    // add Help to a particular control, set its context identifier to -1.
    WinHelpW(wParam, L"winmine.hlp", UVar1, 0x1005040);
    return 0;
  }

  if (uMsg == WM_CONTEXTMENU) {
    UVar1 = HELP_CONTEXTMENU;
    goto LAB_call_winhelp;
  }

  if (uMsg == WM_INITDIALOG) {
    SetDlgItemInt(hDlg, DLG_GAME_CUSTOM_HEIGHT, g_state_board_height_maybe, FALSE);
    SetDlgItemInt(hDlg, DLG_GAME_CUSTOM_WIDTH, g_state_board_width_maybe, FALSE);
    SetDlgItemInt(hDlg, DLG_GAME_CUSTOM_MINES, g_state_mine_counter, FALSE);
    return 1;
  }

  // Nan:
  // Weird decompiler output
  // If uMsg is anything but WM_COMMAND return early
  // Basically, everything after this is the WM_COMMAND handler
  if (uMsg != WM_COMMAND) {
    return 0;
  }

  // Nan:
  // wParam & 0xffff extracts the lower 16 bits of wParam
  // high word   |     low word     |    lParam
  // 0          --> menu id        --> 0
  // 1          --> accelerator id --> 0
  // notif code --> control id     --> handle to control window
  low_wParam = (uint)wParam & 0xffff;
  if (low_wParam != 1) {
    if (low_wParam == 2) {
      goto LAB_end_dialog;
    }
    if (low_wParam != 100) {
      if (low_wParam != 0x6d) {
        return 0;
      }
      goto LAB_end_dialog;
    }
  }

  g_state_board_height_maybe = getDlgItemValueClamped(hDlg, DLG_GAME_CUSTOM_HEIGHT, 9, 0x18);
  g_state_board_width_maybe = getDlgItemValueClamped(hDlg, DLG_GAME_CUSTOM_WIDTH, 9, 0x1e);
  // UVar1 : max_mines
  UVar1 = (g_state_board_width_maybe - 1U) * (g_state_board_height_maybe + -1);
  if (999 < (int)UVar1) {
    UVar1 = 999;
  }
  g_state_mine_counter = getDlgItemValueClamped(hDlg, DLG_GAME_CUSTOM_MINES, 10, UVar1);

LAB_end_dialog:
  EndDialog(hDlg, 1);
  return 1;
}

void setHighScoreDlgTimesFormat(HWND hDlg, int nIDDlgItem, int player_time, LPCWSTR player_name) {
  WCHAR final_time_formatted[32];

  wsprintfW(final_time_formatted, (LPCWSTR)&fmt_seconds_string, player_time);
  SetDlgItemTextW(hDlg, nIDDlgItem, final_time_formatted);
  SetDlgItemTextW(hDlg, nIDDlgItem + 1, player_name);
  return;
}

BOOL showHighScoresProc(HWND param_1, int param_2, HWND param_3, int param_4) {
  uint uVar1;
  UINT uCommand;

  if (param_2 == 0x53) {
    uCommand = 0xc;
    param_3 = *(HWND *)(param_4 + 0xc);
  } else {
    if (param_2 != 0x7b) {
      if (param_2 != 0x110) {
        if (param_2 != 0x111) {
          return 0;
        }
        uVar1 = (uint)param_3 & 0xffff;
        if (uVar1 == 0) {
          return 0;
        }
        if (((uVar1 < 3) || (uVar1 == 100)) || (uVar1 == 0x6d)) {
          EndDialog(param_1, 1);
          return 1;
        }
        if (uVar1 != 0x2c3) {
          return 0;
        }
        g_state_time3 = 999;
        g_state_time2 = 999;
        g_state_time1 = 999;
        lstrcpyW(g_state_name1, (LPCWSTR)&g_default_anon_name);
        lstrcpyW(g_state_name2, (LPCWSTR)&g_default_anon_name);
        lstrcpyW(g_state_name3, (LPCWSTR)&g_default_anon_name);
        g_state_should_commit_to_register = TRUE;
      }
      setHighScoreDlgTimesFormat(param_1, 0x2bd, g_state_time1, g_state_name1);
      setHighScoreDlgTimesFormat(param_1, 0x2bf, g_state_time2, g_state_name2);
      setHighScoreDlgTimesFormat(param_1, 0x2c1, g_state_time3, g_state_name3);
      return 1;
    }
    uCommand = 10;
  }
  WinHelpW(param_3, L"winmine.hlp", uCommand, 0x1005078);
  return 0;
}

BOOL inputNewHighScoreNameProc(HWND dlg_item, int param_2, ushort param_3) {
  short sVar1;
  LPWSTR lpString;
  HWND hWnd;
  LPCWSTR lpString_00;
  UINT Msg;
  WPARAM wParam;
  LPARAM lParam;
  WCHAR local_104[128];

  sVar1 = (short)g_state_difficulty;
  if (param_2 == 0x110) {
    getStrFromResources(sVar1 + 9, local_104, 0x80);
    SetDlgItemTextW(dlg_item, 0x259, local_104);
    lParam = 0;
    wParam = 0x20;
    Msg = 0xc5;
    hWnd = GetDlgItem(dlg_item, 0x25a);
    SendMessageW(hWnd, Msg, wParam, lParam);
    if ((short)g_state_difficulty == 0) {
      lpString_00 = g_state_name1;
    } else {
      lpString_00 = g_state_name2;
      if ((short)g_state_difficulty != 1) {
        lpString_00 = g_state_name3;
      }
    }
    SetDlgItemTextW(dlg_item, 0x25a, lpString_00);
  } else {
    if (((param_2 != 0x111) || (param_3 == 0)) ||
        ((2 < param_3 && ((param_3 != 100 && (param_3 != 0x6d)))))) {
      return 0;
    }
    if (sVar1 == 0) {
      lpString = g_state_name1;
    } else {
      lpString = g_state_name2;
      if (sVar1 != 1) {
        lpString = g_state_name3;
      }
    }
    GetDlgItemTextW(dlg_item, 0x25a, lpString, 0x20);
    EndDialog(dlg_item, 1);
  }
  return 1;
}

void inputCustomGameParams(void) {
  // DAT_00000050_maybe_template_name --> 0x50
  DialogBoxParamW(hModule, MAKEINTRESOURCEW(RES_DLG_CUSTOM), hWnd, inputCustomGameParamsProc, 0);
  // Nan:
  // This syntax tells us that the assembly is writing to the lower 16 bits of
  // g_state_difficulty
  //
  // If we need to preserve that behavior for some reason:
  // x =(x & 0xFFFF0000) | DIFFICULTY_CUSTOM;
  //
  // Otherwise just do this since it doesn't really matter
  // g_state_difficulty = DIFFICULTY_CUSTOM; */
  g_state_difficulty = DIFFICULTY_CUSTOM;
  updateMenuCheckmarks();
  g_state_should_commit_to_register = TRUE;
  prepareNewGame();
  return;
}

void inputNewHighScoreName(void) {
  // DAT_00000258 --> 0x258
  DialogBoxParamW(hModule, MAKEINTRESOURCEW(RES_DLG_NEWHS), hWnd, inputNewHighScoreNameProc, 0);
  g_state_should_commit_to_register = TRUE;
  return;
}

void showHighScores(void) {
  // DAT_000002bc --> 0x2bc
  DialogBoxParamW(hModule, MAKEINTRESOURCEW(RES_DLG_SHOWHS), hWnd, showHighScoresProc, 0);
  return;
}

UINT getDlgItemValueClamped(HWND hDlg, int nIDDlgItem, UINT lower_bound, UINT upper_bound) {
  UINT result;

  result = GetDlgItemInt(hDlg, nIDDlgItem, &nIDDlgItem, FALSE);
  if (((int)lower_bound <= (int)result) && (lower_bound = result, (int)upper_bound < (int)result)) {
    lower_bound = upper_bound;
  }
  return lower_bound;
}
