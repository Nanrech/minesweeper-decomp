#include "winmine.h"

int entry(void) {
  HMODULE pHVar1;
  undefined4 *puVar2;
  int iVar3;
  uint nCmdShow;
  int *piVar4;
  int unaff_EBP;
  byte *lpCmdLine;
  HINSTANCE hPrevInstance;

  FUN_0100400c_compiler(&DAT_01001390, 0x70);
  pHVar1 = GetModuleHandleA((LPCSTR)0x0);
  if (((short)pHVar1->unused == 0x5a4d) &&
      (piVar4 = (int *)((int)&pHVar1->unused + pHVar1[0xf].unused), *piVar4 == 0x4550)) {
    if ((short)piVar4[6] == 0x10b) {
      if (0xe < (uint)piVar4[0x1d]) {
        iVar3 = piVar4[0x3a];
        goto LAB_01003e84;
      }
    } else if (((short)piVar4[6] == 0x20b) && (0xe < (uint)piVar4[0x21])) {
      iVar3 = piVar4[0x3e];
    LAB_01003e84:
      *(uint *)(unaff_EBP + -0x1c) = (uint)(iVar3 != 0);
      goto LAB_01003e8a;
    }
  }
  *(undefined4 *)(unaff_EBP + -0x1c) = 0;
LAB_01003e8a:
  *(undefined4 *)(unaff_EBP + -4) = 0;
  __set_app_type(2);
  _DAT_01005b8c = 0xffffffff;
  _DAT_01005b90 = 0xffffffff;
  puVar2 = (undefined4 *)__p__fmode();
  *puVar2 = DAT_01005178;
  puVar2 = (undefined4 *)__p__commode();
  *puVar2 = DAT_01005174;
  _DAT_01005b94 = *(undefined4 *)_adjust_fdiv_exref;
  nopMaybe();
  if (DAT_01005138 == 0) {
    __setusermatherr(nopMaybe);
  }
  FUN_01003ff4_compiler();
  initterm(&DAT_010011c0, &DAT_010011c4);
  *(undefined4 *)(unaff_EBP + -0x20) = DAT_01005170;
  iVar3 = __getmainargs((int *)(unaff_EBP + -0x2c), (char ***)(unaff_EBP + -0x28),
                        (char ***)(unaff_EBP + -0x24), DAT_0100516c,
                        (_startupinfo *)(unaff_EBP + -0x20));
  *(int *)(unaff_EBP + -0x30) = iVar3;
  initterm(&DAT_010011b8, &DAT_010011bc);
  lpCmdLine = *(byte **)_acmdln_exref;
  *(byte **)(unaff_EBP + -0x34) = lpCmdLine;
  if (*lpCmdLine != 0x22) {
    do {
      if (*lpCmdLine < 0x21)
        goto LAB_01003f58;
      lpCmdLine = lpCmdLine + 1;
      *(byte **)(unaff_EBP + -0x34) = lpCmdLine;
    } while (true);
  }
  do {
    lpCmdLine = lpCmdLine + 1;
    *(byte **)(unaff_EBP + -0x34) = lpCmdLine;
    if (*lpCmdLine == 0)
      break;
  } while (*lpCmdLine != 0x22);
  if (*lpCmdLine != 0x22)
    goto LAB_01003f58;
  do {
    lpCmdLine = lpCmdLine + 1;
    *(byte **)(unaff_EBP + -0x34) = lpCmdLine;
  LAB_01003f58:
  } while ((*lpCmdLine != 0) && (*lpCmdLine < 0x21));
  *(undefined4 *)(unaff_EBP + -0x4c) = 0;
  GetStartupInfoA((LPSTARTUPINFOA)(unaff_EBP + -0x78));
  if ((*(byte *)(unaff_EBP + -0x4c) & 1) == 0) {
    nCmdShow = 10;
  } else {
    nCmdShow = (uint) * (ushort *)(unaff_EBP + -0x48);
  }
  hPrevInstance = (HINSTANCE)0x0;
  pHVar1 = GetModuleHandleA((LPCSTR)0x0);
  iVar3 = WinMain(pHVar1, hPrevInstance, (LPSTR)lpCmdLine, nCmdShow);
  *(int *)(unaff_EBP + -0x7c) = iVar3;
  if (*(int *)(unaff_EBP + -0x1c) == 0) {
    // WARNING: Subroutine does not return
    exit(iVar3);
  }
  _cexit();
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  return iVar3;
}

int __cdecl _XcptFilter(ulong _ExceptionNum, _EXCEPTION_POINTERS *_ExceptionPtr) {
  int iVar1;

  // WARNING: Could not recover jumptable at 0x01003fe8. Too many branches
  // WARNING: Treating indirect jump as call
  iVar1 = _XcptFilter(_ExceptionNum, _ExceptionPtr);
  return iVar1;
}

void __cdecl initterm(void) {
  // WARNING: Could not recover jumptable at 0x01003fee. Too many branches
  // WARNING: Treating indirect jump as call
  initterm();
  return;
}

void FUN_01003ff4_compiler(void) {
  _controlfp(0x10000, 0x30000);
  return;
}

int nopMaybe(void) {
  return 0;
}

void __cdecl FUN_0100400c_compiler(void* param_1, int param_2) {
  int iVar1;
  undefined4 unaff_EBX;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  undefined4 unaff_retaddr;
  undefined4 auStack_18[4];
  undefined1 auStack_8[8];

  ExceptionList = auStack_8;
  iVar1 = -param_2;
  *(undefined4 *)((int)auStack_18 + iVar1 + 0xc) = unaff_EBX;
  *(undefined4 *)((int)auStack_18 + iVar1 + 8) = unaff_ESI;
  *(undefined4 *)((int)auStack_18 + iVar1 + 4) = unaff_EDI;
  *(undefined4 *)((int)auStack_18 + iVar1) = unaff_retaddr;
  return;
}

void __SEH_epilog(void) {
  undefined4 *unaff_EBP;
  undefined4 unaff_retaddr;

  ExceptionList = (void *)unaff_EBP[-4];
  *unaff_EBP = unaff_retaddr;
  return;
}

uint __cdecl _controlfp(uint _NewValue, uint _Mask) {
  uint uVar1;

  // WARNING: Could not recover jumptable at 0x01004056. Too many branches
  // WARNING: Treating indirect jump as call
  uVar1 = _controlfp(_NewValue, _Mask);
  return uVar1;
}
