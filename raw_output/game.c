#include "winmine.h"

void updateAndRedrawTile(int x, int y, byte new_flag) {
  g_mine_board[y][x] = g_mine_board[y][x] & TILE_NON_STATE_MASK | new_flag;
  drawTile(x, y);
  return;
}

void clearBoard(void) {
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar5;
  byte(*pabVar6)[32];
  int iVar7;
  int iVar4;

  // Nan:
  // Strange constant pointers generated at compile time
  // 0x1005341 = g_mine_board + 1
  // 0x100533f = g_mine_board - 1
  // 0x1005360 = g_mine_board + 0x20 (1 row)
  iVar4 = 0x360;
  do {
    iVar2 = iVar4 + -1;
    *(undefined1 *)(iVar4 + 0x100533f) = TILE_STATE_COVERED;
    iVar7 = g_state_board_height;
    iVar1 = g_state_board_width;
    iVar4 = iVar2;
  } while (iVar2 != 0);
  if (g_state_board_width + 2 != 0) {
    iVar2 = g_state_board_height * 0x20;
    iVar4 = g_state_board_width + 2;
    do {
      iVar3 = iVar4 + -1;
      *(undefined1 *)(iVar4 + 0x100533f) = TILE_STATE_BORDER;
      *(undefined1 *)(iVar2 + 0x1005360 + iVar3) = TILE_STATE_BORDER;
      iVar4 = iVar3;
    } while (iVar3 != 0);
  }
  iVar7 = iVar7 + 2;
  if (iVar7 != 0) {
    pabVar6 = g_mine_board + iVar7;
    puVar5 = (undefined1 *)(iVar7 * 0x20 + 0x1005341 + iVar1);
    do {
      pabVar6 = pabVar6 + -1;
      puVar5 = puVar5 + -0x20;
      iVar7 = iVar7 + -1;
      (*pabVar6)[0] = TILE_STATE_BORDER;
      *puVar5 = TILE_STATE_BORDER;
    } while (iVar7 != 0);
  }
  return;
}

int countMines3x3(int x, int y) {
  int counter;
  int iVar1;
  byte(*pabVar2)[32];
  int iVar3;

  counter = 0;
  iVar3 = y + -1;
  if (iVar3 <= y + 1) {
    pabVar2 = g_mine_board + iVar3;
    iVar1 = ((y + 1) - iVar3) + 1;
    iVar3 = x + -1;
    do {
      for (; iVar3 <= x + 1; iVar3 = iVar3 + 1) {
        if (((*pabVar2)[iVar3] & TILE_HAS_MINE) != 0) {
          counter = counter + 1;
        }
      }
      pabVar2 = pabVar2 + 1;
      iVar1 = iVar1 + -1;
      iVar3 = x + -1;
    } while (iVar1 != 0);
  }
  return counter;
}

void updateAndRedrawBoardGameOver(byte game_result) {
  // Nan:
  // There's some weird stuff going on with game_result
  // not sure if it's a compiler artifact or coded like this
  // win  = TILE_STATE_FLAGGED
  // loss = TILE_STATE_MINE
  int iVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;

  iVar1 = g_state_board_width;
  if (0 < g_state_board_height) {
    // Nan:
    // See clearBoard
    // 0x1005360 = g_mine_board + 0x20 (1 row)
    iVar5 = 0x1005360;
    iVar4 = g_state_board_height;
    do {
      iVar3 = 1;
      if (0 < iVar1) {
        do {
          bVar2 = *(byte *)(iVar5 + iVar3);
          if ((bVar2 & TILE_IS_REVEALED) == 0) {
            if ((char)bVar2 < '\0') {
              if ((bVar2 & TILE_STATE_MASK) != TILE_STATE_FLAGGED) {
                bVar2 = bVar2 & TILE_NON_STATE_MASK | game_result;
              LAB_01002fc7:
                *(byte *)(iVar5 + iVar3) = bVar2;
              }
            } else if ((bVar2 & TILE_STATE_MASK) == TILE_STATE_FLAGGED) {
              bVar2 = bVar2 & 0xeb | TILE_STATE_WRONG_FLAG;
              goto LAB_01002fc7;
            }
          }
          iVar3 = iVar3 + 1;
        } while (iVar3 <= iVar1);
      }
      iVar5 = iVar5 + 0x20;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  DrawTiles();
  return;
}

void tickGameTimer(void) {
  if ((g_state_game_active != 0) && (g_state_timer_value < 999)) {
    g_state_timer_value = g_state_timer_value + 1;
    drawTimer();
    playSound(1);
  }
  return;
}

void revealTileAndQueueForFloodFill(int x, int y) {
  byte bVar1;
  int iVar2;

  if ((((g_mine_board[y][x] & TILE_IS_REVEALED) == 0) &&
       (bVar1 = g_mine_board[y][x] & TILE_STATE_MASK, bVar1 != TILE_STATE_BORDER)) &&
      (bVar1 != TILE_STATE_FLAGGED)) {
    g_state_revealed_tiles = g_state_revealed_tiles + 1;
    iVar2 = countMines3x3(x, y);
    g_mine_board[y][x] = (byte)iVar2 | TILE_IS_REVEALED;
    drawTile(x, y);
    if (iVar2 == 0) {
      g_reveal_queue_x[g_reveal_queue_write_index] = x;
      g_reveal_queue_y[g_reveal_queue_write_index] = y;
      g_reveal_queue_write_index = g_reveal_queue_write_index + 1;
      if (g_reveal_queue_write_index == 100) {
        g_reveal_queue_write_index = 0;
      }
    }
  }
  return;
}

void floodRevealFromTile(int start_x, int start_y) {
  int x;
  int x_00;
  int iVar1;
  int y;
  int iVar2;

  iVar1 = 1;
  g_reveal_queue_write_index = 1;
  revealTileAndQueueForFloodFill(start_x, start_y);
  if (g_reveal_queue_write_index != 1) {
    do {
      iVar2 = g_reveal_queue_y[iVar1];
      x_00 = g_reveal_queue_x[iVar1];
      y = iVar2 + -1;
      revealTileAndQueueForFloodFill(x_00 + -1, y);
      revealTileAndQueueForFloodFill(x_00, y);
      x = x_00 + 1;
      revealTileAndQueueForFloodFill(x, y);
      revealTileAndQueueForFloodFill(x_00 + -1, iVar2);
      revealTileAndQueueForFloodFill(x, iVar2);
      iVar2 = iVar2 + 1;
      revealTileAndQueueForFloodFill(x_00 + -1, iVar2);
      revealTileAndQueueForFloodFill(x_00, iVar2);
      revealTileAndQueueForFloodFill(x, iVar2);
      iVar1 = iVar1 + 1;
      if (iVar1 == 100) {
        iVar1 = 0;
      }
    } while (iVar1 != g_reveal_queue_write_index);
  }
  return;
}

int countFlags3x3(int x, int y) {
  int iVar1;
  byte(*pabVar2)[32];
  int iVar3;
  int local_8;

  local_8 = 0;
  iVar3 = y + -1;
  if (iVar3 <= y + 1) {
    pabVar2 = g_mine_board + iVar3;
    iVar1 = ((y + 1) - iVar3) + 1;
    iVar3 = x + -1;
    do {
      for (; iVar3 <= x + 1; iVar3 = iVar3 + 1) {
        if (((*pabVar2)[iVar3] & TILE_STATE_MASK) == TILE_STATE_FLAGGED) {
          local_8 = local_8 + 1;
        }
      }
      pabVar2 = pabVar2 + 1;
      iVar1 = iVar1 + -1;
      iVar3 = x + -1;
    } while (iVar1 != 0);
  }
  return local_8;
}

void setTilePressed(int x, int y) {
  byte bVar1;
  byte bVar2;

  bVar1 = g_mine_board[y][x];
  bVar2 = bVar1 & TILE_STATE_MASK;
  if (bVar2 == TILE_STATE_QUESTION) {
    bVar2 = TILE_STATE_PRESSED_QUESTION;
  } else if (bVar2 == TILE_STATE_COVERED) {
    bVar2 = TILE_STATE_BLANK;
  }
  g_mine_board[y][x] = bVar1 & TILE_NON_STATE_MASK | bVar2;
  return;
}

void setTileNotPressed(int x, int y) {
  byte bVar1;
  byte bVar2;

  bVar1 = g_mine_board[y][x];
  bVar2 = bVar1 & TILE_STATE_MASK;
  if (bVar2 == TILE_STATE_PRESSED_QUESTION) {
    bVar2 = TILE_STATE_QUESTION;
  } else if ((bVar1 & TILE_STATE_MASK) == TILE_STATE_BLANK) {
    bVar2 = TILE_STATE_COVERED;
  }
  g_mine_board[y][x] = bVar1 & TILE_NON_STATE_MASK | bVar2;
  return;
}

void FUN_010031d4(int x, int y) {
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  byte(*pabVar5)[32];
  int iVar6;
  int local_24;
  int local_20;
  int local_14;
  int local_10;
  int local_c;
  int local_8;

  iVar3 = y;
  iVar4 = x;
  local_8 = g_mouse_tile_y;
  iVar6 = g_mouse_tile_x;
  if ((x != g_mouse_tile_x) || (y != g_mouse_tile_y)) {
    g_mouse_tile_x = x;
    g_mouse_tile_y = y;
    if (DAT_01005144 == 0) {
      if ((((0 < iVar6) && (0 < local_8)) && (iVar6 <= g_state_board_width)) &&
          ((local_8 <= g_state_board_height &&
            ((g_mine_board[local_8][iVar6] & TILE_IS_REVEALED) == 0)))) {
        setTileNotPressed(iVar6, local_8);
        drawTile(iVar6, local_8);
      }
      iVar4 = g_mouse_tile_y;
      iVar6 = g_mouse_tile_x;
      if (((0 < x) && (0 < y)) &&
          ((x <= g_state_board_width &&
            (((y <= g_state_board_height &&
               ((g_mine_board[y][x] & TILE_IS_REVEALED) == 0)) &&
              ((g_mine_board[y][x] & TILE_STATE_MASK) != TILE_STATE_FLAGGED)))))) {
        setTilePressed(g_mouse_tile_x, g_mouse_tile_y);
        drawTile(iVar6, iVar4);
      }
    } else {
      if (((x < 1) || (y < 1)) || ((g_state_board_width < x || (g_state_board_height < y)))) {
        bVar2 = FALSE;
      } else {
        bVar2 = TRUE;
      }
      if (((iVar6 < 1) || (local_8 < 1)) ||
          ((g_state_board_width < iVar6 || (g_state_board_height < local_8)))) {
        bVar1 = FALSE;
      } else {
        bVar1 = TRUE;
      }
      local_10 = local_8 + -1;
      if (local_10 < 2) {
        local_10 = 1;
      }
      local_8 = local_8 + 1;
      if (g_state_board_height <= local_8) {
        local_8 = g_state_board_height;
      }
      local_20 = y + -1;
      if (local_20 < 2) {
        local_20 = 1;
      }
      local_c = y + 1;
      if (g_state_board_height <= local_c) {
        local_c = g_state_board_height;
      }
      local_14 = iVar6 + -1;
      if (local_14 < 2) {
        local_14 = 1;
      }
      y = iVar6 + 1;
      if (g_state_board_width <= y) {
        y = g_state_board_width;
      }
      local_24 = x + -1;
      if (local_24 < 2) {
        local_24 = 1;
      }
      x = x + 1;
      if (g_state_board_width <= x) {
        x = g_state_board_width;
      }
      if ((bVar1) && (local_10 <= local_8)) {
        pabVar5 = g_mine_board + local_10;
        g_mouse_tile_x = iVar4;
        g_mouse_tile_y = iVar3;
        iVar6 = local_14;
        iVar4 = local_10;
        do {
          for (; iVar6 <= y; iVar6 = iVar6 + 1) {
            if (((*pabVar5)[iVar6] & TILE_IS_REVEALED) == 0) {
              setTileNotPressed(iVar6, iVar4);
            }
          }
          iVar4 = iVar4 + 1;
          pabVar5 = pabVar5 + 1;
          iVar6 = local_14;
        } while (iVar4 <= local_8);
      }
      if ((bVar2) && (local_20 <= local_c)) {
        pabVar5 = g_mine_board + local_20;
        iVar6 = local_24;
        iVar4 = local_20;
        do {
          for (; iVar6 <= x; iVar6 = iVar6 + 1) {
            if (((*pabVar5)[iVar6] & TILE_IS_REVEALED) == 0) {
              setTilePressed(iVar6, iVar4);
            }
          }
          iVar4 = iVar4 + 1;
          pabVar5 = pabVar5 + 1;
          iVar6 = local_24;
        } while (iVar4 <= local_c);
      }
      if (bVar1) {
        for (; iVar6 = local_14, local_10 <= local_8; local_10 = local_10 + 1) {
          for (; iVar6 <= y; iVar6 = iVar6 + 1) {
            drawTile(iVar6, local_10);
          }
        }
      }
      if (bVar2) {
        for (; iVar6 = local_24, local_20 <= local_c; local_20 = local_20 + 1) {
          for (; iVar6 <= x; iVar6 = iVar6 + 1) {
            drawTile(iVar6, local_20);
          }
        }
      }
    }
  }
  return;
}

void FUN_0100341c(void) {
  stopAllSoundsButWeird();
  if ((g_state_game_flags & 2) == 0) {
    DAT_01005168 = g_state_game_active;
  }
  if ((g_state_game_flags & 1) != 0) {
    g_state_game_active = 0;
  }
  g_state_game_flags = g_state_game_flags | 2;
  return;
}

void FUN_0100344c(void) {
  if ((g_state_game_flags & 1) != 0) {
    g_state_game_active = DAT_01005168;
  }
  g_state_game_flags = g_state_game_flags & 0xfd;
  return;
}

void updateAndRedrawMineCounter(int mines_to_add) {
  g_mines_left = g_mines_left + mines_to_add;
  drawMineCounter();
  return;
}

void handleGameOver(int game_result) {
  g_state_game_active = 0;
  // Nan:
  // 0 --> 3 (loss)
  // 1 --> 2 (win)
  g_state_face = (game_result != 0) + 2;
  drawFace(g_state_face);
  updateAndRedrawBoardGameOver((game_result != 0) * 0x04 + TILE_STATE_MINE);
  if ((game_result != 0) && (g_mines_left != 0)) {
    updateAndRedrawMineCounter(-g_mines_left);
  }
  playSound(3 - (uint)(game_result != 0));
  g_state_game_flags = 0x10;
  if ((game_result != 0) && ((ushort)g_state_difficulty != 3)) {
    if (g_state_timer_value < (&g_state_time1)[(ushort)g_state_difficulty]) {
      (&g_state_time1)[(ushort)g_state_difficulty] = g_state_timer_value;
      inputNewHighScoreName();
      showHighScores();
    }
  }
  return;
}

void handleLeftClickTile(int x, int y) {
  int iVar1;
  int iVar2;
  int iVar3;

  if ((g_mine_board[y][x] & TILE_HAS_MINE) == 0) {
    floodRevealFromTile(x, y);
    if (g_state_revealed_tiles != g_state_safe_tiles) {
      return;
    }
    iVar1 = 1;
  } else {
    if (g_state_revealed_tiles == 0) {
      iVar1 = 1;
      if (g_state_board_height < 2) {
        return;
      }
      iVar3 = 0x1005360;
      do {
        iVar2 = 1;
        if (1 < g_state_board_width) {
          do {
            if ((*(byte *)(iVar3 + iVar2) & TILE_HAS_MINE) == 0) {
              g_mine_board[y][x] = TILE_STATE_COVERED;
              g_mine_board[iVar1][iVar2] = g_mine_board[iVar1][iVar2] | TILE_HAS_MINE;
              floodRevealFromTile(x, y);
              return;
            }
            iVar2 = iVar2 + 1;
          } while (iVar2 < g_state_board_width);
        }
        iVar1 = iVar1 + 1;
        iVar3 = iVar3 + 0x20;
      } while (iVar1 < g_state_board_height);
      return;
    }
    updateAndRedrawTile(x, y, TILE_IS_REVEALED | TILE_STATE_EXPLODED_MINE);
    iVar1 = 0;
  }
  handleGameOver(iVar1);
  return;
}

void FUN_010035b7(int x, int y) {
  byte bVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  byte(*pabVar5)[32];
  int x_00;

  bVar2 = FALSE;
  bVar1 = g_mine_board[y][x];
  if (((bVar1 & TILE_IS_REVEALED) == 0) ||
      (uVar3 = countFlags3x3(x, y), (bVar1 & TILE_STATE_MASK) != uVar3)) {
    FUN_010031d4(-2, -2);
    return;
  }
  iVar4 = y + -1;
  if (iVar4 <= y + 1) {
    pabVar5 = g_mine_board + iVar4;
    x_00 = x + -1;
    do {
      for (; x_00 <= x + 1; x_00 = x_00 + 1) {
        if ((((*pabVar5)[x_00] & TILE_STATE_MASK) == TILE_STATE_FLAGGED) ||
            (-1 < (char)(*pabVar5)[x_00])) {
          floodRevealFromTile(x_00, iVar4);
        } else {
          bVar2 = TRUE;
          updateAndRedrawTile(x_00, iVar4, TILE_IS_REVEALED | TILE_STATE_EXPLODED_MINE);
        }
      }
      iVar4 = iVar4 + 1;
      pabVar5 = pabVar5 + 1;
      x_00 = x + -1;
    } while (iVar4 <= y + 1);
    if (bVar2) {
      iVar4 = 0;
      goto LAB_01003663;
    }
  }
  if (g_state_revealed_tiles != g_state_safe_tiles) {
    return;
  }
  iVar4 = 1;
LAB_01003663:
  handleGameOver(iVar4);
  return;
}

// nee populateBoard
void prepareNewGame(void) {
  int x_rand;
  int y_rand;
  uint uVar1;

  g_state_game_active = 0;
  if ((g_state_board_width_maybe == g_state_board_width) &&
      (g_state_board_height_maybe == g_state_board_height)) {
    uVar1 = 4;
  } else {
    uVar1 = 6;
  }
  g_state_board_width = g_state_board_width_maybe;
  g_state_board_height = g_state_board_height_maybe;
  clearBoard();
  g_state_face = 0;
  g_mine_counter = g_state_mine_counter;
  do {
    do {
      x_rand = rng(g_state_board_width);
      y_rand = rng(g_state_board_height);
    } while ((g_mine_board[y_rand + 1][x_rand + 1] & TILE_HAS_MINE) != 0);
    g_mine_board[y_rand + 1][x_rand + 1] =
        g_mine_board[y_rand + 1][x_rand + 1] | TILE_HAS_MINE;
    g_mine_counter = g_mine_counter + -1;
  } while (g_mine_counter != 0);
  g_state_safe_tiles = g_state_board_height * g_state_board_width - g_state_mine_counter;
  g_state_timer_value = 0;
  g_mine_counter = g_state_mine_counter;
  g_mines_left = g_state_mine_counter;
  g_state_revealed_tiles = 0;
  g_state_game_flags = 1;
  updateAndRedrawMineCounter(0);
  maybeUpdateWindowLayoutIDK(uVar1);
  return;
}

void handleRightClickTile(int x, int y) {
  byte bVar1;
  int iVar2;

  if (x < 1) {
    return;
  }
  if (y < 1) {
    return;
  }
  if (g_state_board_width < x) {
    return;
  }
  if (g_state_board_height < y) {
    return;
  }
  bVar1 = g_mine_board[y][x];
  if ((bVar1 & TILE_IS_REVEALED) != 0) {
    return;
  }
  bVar1 = bVar1 & TILE_STATE_MASK;
  if (bVar1 == TILE_STATE_FLAGGED) {
    iVar2 = 1;
    bVar1 = (g_state_marks == 0) * 0x02 + TILE_STATE_QUESTION;
  } else {
    if (bVar1 == TILE_STATE_QUESTION) {
      bVar1 = TILE_STATE_COVERED;
      goto LAB_010037b4;
    }
    bVar1 = TILE_STATE_FLAGGED;
    iVar2 = -1;
  }
  updateAndRedrawMineCounter(iVar2);
LAB_010037b4:
  updateAndRedrawTile(x, y, bVar1);
  if (((g_mine_board[y][x] & TILE_STATE_MASK) == TILE_STATE_FLAGGED) &&
      (g_state_revealed_tiles == g_state_safe_tiles)) {
    handleGameOver(1);
  }
  return;
}

void FUN_010037e1(void) {
  UINT_PTR UVar1;

  if ((((0 < g_mouse_tile_x) && (0 < g_mouse_tile_y)) && (g_mouse_tile_x <= g_state_board_width)) &&
      (g_mouse_tile_y <= g_state_board_height)) {
    if ((g_state_revealed_tiles == 0) && (g_state_timer_value == 0)) {
      playSound(1);
      g_state_timer_value = g_state_timer_value + 1;
      drawTimer();
      g_state_game_active = 1;
      UVar1 = SetTimer(hWnd_main, 1, 1000, (TIMERPROC)0x0);
      if (UVar1 == 0) {
        showMessageBoxError(4);
      }
    }
    if ((g_state_game_flags & 1) == 0) {
      g_mouse_tile_y = -2;
      g_mouse_tile_x = -2;
    }
    if (DAT_01005144 == 0) {
      if (((g_mine_board[g_mouse_tile_y][g_mouse_tile_x] & TILE_IS_REVEALED) == 0) &&
          ((g_mine_board[g_mouse_tile_y][g_mouse_tile_x] & TILE_STATE_MASK) != TILE_STATE_FLAGGED)) {
        handleLeftClickTile(g_mouse_tile_x, g_mouse_tile_y);
      }
    } else {
      FUN_010035b7(g_mouse_tile_x, g_mouse_tile_y);
    }
  }
  drawFace(g_state_face);
  return;
}

int rng(int bound) {
  int iVar1;

  iVar1 = rand();
  return iVar1 % bound;
}
