#ifndef WINMINE_H
#define WINMINE_H

#define REG_DWORD 0x4
#define REG_IDX_DIFFICULTY 0x0
#define REG_IDX_HEIGHT 0x2
#define REG_IDX_WIDTH 0x3
#define REG_IDX_MINES 0x1
#define REG_IDX_MARK 0x7
#define REG_IDX_ALREADY_PLAYED 0x11
#define REG_IDX_COLOR 0xa
#define REG_IDX_SOUND 0x6
#define REG_IDX_XPOS 0x4
#define REG_IDX_YPOS 0x5
#define REG_IDX_TIME1 0xb
#define REG_IDX_NAME1 0xc
#define REG_IDX_TIME2 0xd
#define REG_IDX_TIME3 0xf
#define REG_IDX_NAME2 0xe
#define REG_IDX_NAME3 0x10
#define NULL 0x0
#define REG_OPTION_NON_VOLATILE 0x0
#define KEY_WRITE 0x20006
#define REG_IDX_MENU 0x8
#define REG_IDX_TICK 0x9
#define KEY_READ 0x20019
#define NUMCOLORS 0x18
#define SND_PURGE 0x40
#define SND_RESOURCE_OR_SND_ASYNC 0x40005
#define MENUCHK_DIFFICULTY_BEGINNER 0x209
#define MENUCHK_DIFFICULTY_INTERMEDIATE 0x20a
#define MENUCHK_DIFFICULTY_EXPERT 0x20b
#define MENUCHK_DIFFICULTY_CUSTOM 0x20c
#define MENUCHK_DIFFICULTY_COLOR 0x211
#define MENUCHK_DIFFICULTY_MARK 0x20f
#define MENUCHK_DIFFICULTY_SOUND 0x20e
#define DLG_GAME_CUSTOM_HEIGHT 0x8d
#define DLG_GAME_CUSTOM_WIDTH 0x8e
#define DLG_GAME_CUSTOM_MINES 0x8f
#define TRUE 0x1
#define FALSE 0x0
#define HELP_WM_HELP 0xc
#define HELP_CONTEXTMENU 0xa
#define WM_HELP 0x53
#define WM_CONTEXTMENU 0x7b
#define WM_INITDIALOG 0x110
#define WM_COMMAND 0x111
#define DIFFICULTY_CUSTOM 0x3
#define MB_ICONERROR 0x10
#define RES_SHELL_ABOUT_APP 0xc
#define RES_SHELL_ABOUT_OTHER_STUFF 0xd
#define R2_COPYPEN 0xd
#define R2_WHITE 0x10
#define SRCCOPY 0xcc0020
#define SM_CYBORDER 0x6
#define SM_CXBORDER 0x5
#define SM_CYCAPTION 0x4
#define SM_CYMENU 0xf
#define SM_CXVIRTUALSCREEN 0x4e
#define SM_CYVIRTUALSCREEN 0x4f

#define TILE_HAS_MINE 0x80
#define TILE_IS_REVEALED 0x40
#define TILE_STATE_MASK 0x1f
#define TILE_NON_STATE_MASK 0xe0

#define TILE_STATE_BLANK 0x00
#define TILE_STATE_PRESSED_QUESTION 0x09
#define TILE_STATE_MINE 0x0a
#define TILE_STATE_WRONG_FLAG 0x0b
#define TILE_STATE_EXPLODED_MINE 0x0c
#define TILE_STATE_QUESTION 0x0d
#define TILE_STATE_FLAGGED 0x0e
#define TILE_STATE_COVERED 0x0f
#define TILE_STATE_BORDER 0x10

typedef unsigned char undefined;

typedef unsigned char bool;
typedef unsigned char byte;
typedef unsigned int dword;
typedef unsigned long long GUID;
typedef pointer32 ImageBaseOffset32;

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char undefined1;
typedef unsigned short undefined2;
typedef unsigned int undefined4;
typedef unsigned short ushort;
typedef unsigned short wchar16;
typedef short wchar_t;
typedef unsigned short word;
typedef union IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion
    IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion,
    *PIMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion;

typedef struct IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct
    IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct,
    *PIMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct;

struct IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct {
  dword OffsetToDirectory;
  dword DataIsDirectory;
};

union IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion {
  dword OffsetToData;
  struct IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct
      IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct;
};

typedef struct CLIENT_ID CLIENT_ID, *PCLIENT_ID;

struct CLIENT_ID {
  void *UniqueProcess;
  void *UniqueThread;
};

typedef struct _STARTUPINFOA _STARTUPINFOA, *P_STARTUPINFOA;

typedef ulong DWORD;

typedef char CHAR;

typedef CHAR *LPSTR;

typedef ushort WORD;

typedef uchar BYTE;

typedef BYTE *LPBYTE;

typedef void *HANDLE;

struct _STARTUPINFOA {
  DWORD cb;
  LPSTR lpReserved;
  LPSTR lpDesktop;
  LPSTR lpTitle;
  DWORD dwX;
  DWORD dwY;
  DWORD dwXSize;
  DWORD dwYSize;
  DWORD dwXCountChars;
  DWORD dwYCountChars;
  DWORD dwFillAttribute;
  DWORD dwFlags;
  WORD wShowWindow;
  WORD cbReserved2;
  LPBYTE lpReserved2;
  HANDLE hStdInput;
  HANDLE hStdOutput;
  HANDLE hStdError;
};

typedef struct _SECURITY_ATTRIBUTES _SECURITY_ATTRIBUTES, *P_SECURITY_ATTRIBUTES;

typedef void *LPVOID;

typedef int BOOL;

struct _SECURITY_ATTRIBUTES {
  DWORD nLength;
  LPVOID lpSecurityDescriptor;
  BOOL bInheritHandle;
};

typedef struct _STARTUPINFOA *LPSTARTUPINFOA;

typedef struct _SECURITY_ATTRIBUTES *LPSECURITY_ATTRIBUTES;

typedef struct _CONTEXT _CONTEXT, *P_CONTEXT;

typedef struct _FLOATING_SAVE_AREA _FLOATING_SAVE_AREA, *P_FLOATING_SAVE_AREA;

typedef struct _FLOATING_SAVE_AREA FLOATING_SAVE_AREA;

struct _FLOATING_SAVE_AREA {
  DWORD ControlWord;
  DWORD StatusWord;
  DWORD TagWord;
  DWORD ErrorOffset;
  DWORD ErrorSelector;
  DWORD DataOffset;
  DWORD DataSelector;
  BYTE RegisterArea[80];
  DWORD Cr0NpxState;
};

struct _CONTEXT {
  DWORD ContextFlags;
  DWORD Dr0;
  DWORD Dr1;
  DWORD Dr2;
  DWORD Dr3;
  DWORD Dr6;
  DWORD Dr7;
  FLOATING_SAVE_AREA FloatSave;
  DWORD SegGs;
  DWORD SegFs;
  DWORD SegEs;
  DWORD SegDs;
  DWORD Edi;
  DWORD Esi;
  DWORD Ebx;
  DWORD Edx;
  DWORD Ecx;
  DWORD Eax;
  DWORD Ebp;
  DWORD Eip;
  DWORD SegCs;
  DWORD EFlags;
  DWORD Esp;
  DWORD SegSs;
  BYTE ExtendedRegisters[512];
};

typedef struct _EXCEPTION_RECORD _EXCEPTION_RECORD, *P_EXCEPTION_RECORD;

typedef void *PVOID;

typedef ulong ULONG_PTR;

struct _EXCEPTION_RECORD {
  DWORD ExceptionCode;
  DWORD ExceptionFlags;
  struct _EXCEPTION_RECORD *ExceptionRecord;
  PVOID ExceptionAddress;
  DWORD NumberParameters;
  ULONG_PTR ExceptionInformation[15];
};

typedef struct _EXCEPTION_POINTERS _EXCEPTION_POINTERS, *P_EXCEPTION_POINTERS;

typedef struct _EXCEPTION_RECORD EXCEPTION_RECORD;

typedef EXCEPTION_RECORD *PEXCEPTION_RECORD;

typedef struct _CONTEXT CONTEXT;

typedef CONTEXT *PCONTEXT;

struct _EXCEPTION_POINTERS {
  PEXCEPTION_RECORD ExceptionRecord;
  PCONTEXT ContextRecord;
};

typedef struct PdbInfo PdbInfo, *PPdbInfo;

struct PdbInfo {
  char signature[4];
  dword offset;
  dword sig;
  dword age;
  char pdbpath[11];
};

typedef struct _startupinfo _startupinfo, *P_startupinfo;

struct _startupinfo {
  int newmode;
};

typedef struct tagMSG tagMSG, *PtagMSG;

typedef struct tagMSG MSG;

typedef struct HWND__ HWND__, *PHWND__;

typedef struct HWND__ *HWND;

typedef uint UINT;

typedef uint UINT_PTR;

typedef UINT_PTR WPARAM;

typedef long LONG_PTR;

typedef LONG_PTR LPARAM;

typedef struct tagPOINT tagPOINT, *PtagPOINT;

typedef struct tagPOINT POINT;

typedef long LONG;

struct tagPOINT {
  LONG x;
  LONG y;
};

struct tagMSG {
  HWND hwnd;
  UINT message;
  WPARAM wParam;
  LPARAM lParam;
  DWORD time;
  POINT pt;
};

struct HWND__ {
  int unused;
};

typedef struct tagMSG *LPMSG;

typedef struct tagPAINTSTRUCT tagPAINTSTRUCT, *PtagPAINTSTRUCT;

typedef struct tagPAINTSTRUCT *LPPAINTSTRUCT;

typedef struct HDC__ HDC__, *PHDC__;

typedef struct HDC__ *HDC;

typedef struct tagRECT tagRECT, *PtagRECT;

typedef struct tagRECT RECT;

struct HDC__ {
  int unused;
};

struct tagRECT {
  LONG left;
  LONG top;
  LONG right;
  LONG bottom;
};

struct tagPAINTSTRUCT {
  HDC hdc;
  BOOL fErase;
  RECT rcPaint;
  BOOL fRestore;
  BOOL fIncUpdate;
  BYTE rgbReserved[32];
};

typedef LONG_PTR LRESULT;

typedef LRESULT (*WNDPROC)(HWND, UINT, WPARAM, LPARAM);

typedef struct tagPAINTSTRUCT PAINTSTRUCT;

typedef struct tagWNDCLASSW tagWNDCLASSW, *PtagWNDCLASSW;

typedef struct tagWNDCLASSW WNDCLASSW;

typedef struct HINSTANCE__ HINSTANCE__, *PHINSTANCE__;

typedef struct HINSTANCE__ *HINSTANCE;

typedef struct HICON__ HICON__, *PHICON__;

typedef struct HICON__ *HICON;

typedef HICON HCURSOR;

typedef struct HBRUSH__ HBRUSH__, *PHBRUSH__;

typedef struct HBRUSH__ *HBRUSH;

typedef wchar_t WCHAR;

typedef WCHAR *LPCWSTR;

#define MAKEINTRESOURCEW(i) ((LPCWSTR)(ULONG_PTR)(WORD)(i))

struct HBRUSH__ {
  int unused;
};

struct HICON__ {
  int unused;
};

struct tagWNDCLASSW {
  UINT style;
  WNDPROC lpfnWndProc;
  int cbClsExtra;
  int cbWndExtra;
  HINSTANCE hInstance;
  HICON hIcon;
  HCURSOR hCursor;
  HBRUSH hbrBackground;
  LPCWSTR lpszMenuName;
  LPCWSTR lpszClassName;
};

struct HINSTANCE__ {
  int unused;
};

typedef void (*TIMERPROC)(HWND, UINT, UINT_PTR, DWORD);

typedef int INT_PTR;

typedef INT_PTR (*DLGPROC)(HWND, UINT, WPARAM, LPARAM);

typedef struct tagRGBQUAD tagRGBQUAD, *PtagRGBQUAD;

struct tagRGBQUAD {
  BYTE rgbBlue;
  BYTE rgbGreen;
  BYTE rgbRed;
  BYTE rgbReserved;
};

typedef struct tagBITMAPINFO tagBITMAPINFO, *PtagBITMAPINFO;

typedef struct tagBITMAPINFO BITMAPINFO;

typedef struct tagBITMAPINFOHEADER tagBITMAPINFOHEADER, *PtagBITMAPINFOHEADER;

typedef struct tagBITMAPINFOHEADER BITMAPINFOHEADER;

typedef struct tagRGBQUAD RGBQUAD;

struct tagBITMAPINFOHEADER {
  DWORD biSize;
  LONG biWidth;
  LONG biHeight;
  WORD biPlanes;
  WORD biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG biXPelsPerMeter;
  LONG biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
};

struct tagBITMAPINFO {
  BITMAPINFOHEADER bmiHeader;
  RGBQUAD bmiColors[1];
};

typedef CHAR *LPCSTR;

typedef WCHAR *LPWSTR;

typedef DWORD ACCESS_MASK;

typedef struct IMAGE_DOS_HEADER IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;

struct IMAGE_DOS_HEADER {
  char e_magic[2];     // Magic number
  word e_cblp;         // Bytes of last page
  word e_cp;           // Pages in file
  word e_crlc;         // Relocations
  word e_cparhdr;      // Size of header in paragraphs
  word e_minalloc;     // Minimum extra paragraphs needed
  word e_maxalloc;     // Maximum extra paragraphs needed
  word e_ss;           // Initial (relative) SS value
  word e_sp;           // Initial SP value
  word e_csum;         // Checksum
  word e_ip;           // Initial IP value
  word e_cs;           // Initial (relative) CS value
  word e_lfarlc;       // File address of relocation table
  word e_ovno;         // Overlay number
  word e_res[4][4];    // Reserved words
  word e_oemid;        // OEM identifier (for e_oeminfo)
  word e_oeminfo;      // OEM information; e_oemid specific
  word e_res2[10][10]; // Reserved words
  dword e_lfanew;      // File address of new exe header
  byte e_program[64];  // Actual DOS program
};

typedef struct tagINITCOMMONCONTROLSEX tagINITCOMMONCONTROLSEX, *PtagINITCOMMONCONTROLSEX;

typedef struct tagINITCOMMONCONTROLSEX INITCOMMONCONTROLSEX;

struct tagINITCOMMONCONTROLSEX {
  DWORD dwSize;
  DWORD dwICC;
};

typedef struct tagPOINT *LPPOINT;

typedef struct HKEY__ HKEY__, *PHKEY__;

struct HKEY__ {
  int unused;
};

typedef struct HACCEL__ HACCEL__, *PHACCEL__;

typedef struct HACCEL__ *HACCEL;

struct HACCEL__ {
  int unused;
};

typedef HINSTANCE HMODULE;

typedef struct HBITMAP__ HBITMAP__, *PHBITMAP__;

struct HBITMAP__ {
  int unused;
};

typedef struct HPEN__ HPEN__, *PHPEN__;

struct HPEN__ {
  int unused;
};

typedef int (*FARPROC)(void);

typedef WORD ATOM;

typedef struct tagRECT *LPRECT;

typedef void *HGDIOBJ;

typedef struct HKEY__ *HKEY;

typedef struct HRSRC__ HRSRC__, *PHRSRC__;

typedef struct HRSRC__ *HRSRC;

struct HRSRC__ {
  int unused;
};

typedef DWORD COLORREF;

typedef DWORD *LPDWORD;

typedef struct HPEN__ *HPEN;

typedef struct HMENU__ HMENU__, *PHMENU__;

typedef struct HMENU__ *HMENU;

struct HMENU__ {
  int unused;
};

typedef int INT;

typedef HKEY *PHKEY;

typedef HANDLE HGLOBAL;

typedef struct HBITMAP__ *HBITMAP;

typedef struct IMAGE_OPTIONAL_HEADER32 IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;

typedef struct IMAGE_DATA_DIRECTORY IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

struct IMAGE_DATA_DIRECTORY {
  ImageBaseOffset32 VirtualAddress;
  dword Size;
};

struct IMAGE_OPTIONAL_HEADER32 {
  word Magic;
  byte MajorLinkerVersion;
  byte MinorLinkerVersion;
  dword SizeOfCode;
  dword SizeOfInitializedData;
  dword SizeOfUninitializedData;
  ImageBaseOffset32 AddressOfEntryPoint;
  ImageBaseOffset32 BaseOfCode;
  ImageBaseOffset32 BaseOfData;
  pointer32 ImageBase;
  dword SectionAlignment;
  dword FileAlignment;
  word MajorOperatingSystemVersion;
  word MinorOperatingSystemVersion;
  word MajorImageVersion;
  word MinorImageVersion;
  word MajorSubsystemVersion;
  word MinorSubsystemVersion;
  dword Win32VersionValue;
  dword SizeOfImage;
  dword SizeOfHeaders;
  dword CheckSum;
  word Subsystem;
  word DllCharacteristics;
  dword SizeOfStackReserve;
  dword SizeOfStackCommit;
  dword SizeOfHeapReserve;
  dword SizeOfHeapCommit;
  dword LoaderFlags;
  dword NumberOfRvaAndSizes;
  struct IMAGE_DATA_DIRECTORY DataDirectory[16];
};

typedef struct Var Var, *PVar;

struct Var {
  word wLength;
  word wValueLength;
  word wType;
};

typedef struct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct,
    *PIMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct;

struct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct {
  dword NameOffset;
  dword NameIsString;
};

typedef struct IMAGE_BOUND_IMPORT_DESCRIPTOR_0 IMAGE_BOUND_IMPORT_DESCRIPTOR_0,
    *PIMAGE_BOUND_IMPORT_DESCRIPTOR_0;

struct IMAGE_BOUND_IMPORT_DESCRIPTOR_0 {
  dword TimeDateStamp;
  word OffsetModuleName;
  word NumberOfModuleForwarderRefs;
};

typedef struct IMAGE_DEBUG_DIRECTORY IMAGE_DEBUG_DIRECTORY, *PIMAGE_DEBUG_DIRECTORY;

struct IMAGE_DEBUG_DIRECTORY {
  dword Characteristics;
  dword TimeDateStamp;
  word MajorVersion;
  word MinorVersion;
  dword Type;
  dword SizeOfData;
  dword AddressOfRawData;
  dword PointerToRawData;
};

typedef struct IMAGE_FILE_HEADER IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

struct IMAGE_FILE_HEADER {
  word Machine; // 332
  word NumberOfSections;
  dword TimeDateStamp;
  dword PointerToSymbolTable;
  dword NumberOfSymbols;
  word SizeOfOptionalHeader;
  word Characteristics;
};

typedef struct IMAGE_NT_HEADERS32 IMAGE_NT_HEADERS32, *PIMAGE_NT_HEADERS32;

struct IMAGE_NT_HEADERS32 {
  char Signature[4];
  struct IMAGE_FILE_HEADER FileHeader;
  struct IMAGE_OPTIONAL_HEADER32 OptionalHeader;
};

typedef struct StringFileInfo StringFileInfo, *PStringFileInfo;

struct StringFileInfo {
  word wLength;
  word wValueLength;
  word wType;
};

typedef union IMAGE_RESOURCE_DIRECTORY_ENTRY IMAGE_RESOURCE_DIRECTORY_ENTRY,
    *PIMAGE_RESOURCE_DIRECTORY_ENTRY;

typedef union IMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion IMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion,
    *PIMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion;

union IMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion {
  struct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct;
  dword Name;
  word Id;
};

union IMAGE_RESOURCE_DIRECTORY_ENTRY {
  union IMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion NameUnion;
  union IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion DirectoryUnion;
};

typedef struct StringTable StringTable, *PStringTable;

struct StringTable {
  word wLength;
  word wValueLength;
  word wType;
};

typedef struct IMAGE_SECTION_HEADER IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;

typedef union Misc Misc, *PMisc;

typedef enum SectionFlags {
  IMAGE_SCN_TYPE_NO_PAD = 8,
  IMAGE_SCN_RESERVED_0001 = 16,
  IMAGE_SCN_CNT_CODE = 32,
  IMAGE_SCN_CNT_INITIALIZED_DATA = 64,
  IMAGE_SCN_CNT_UNINITIALIZED_DATA = 128,
  IMAGE_SCN_LNK_OTHER = 256,
  IMAGE_SCN_LNK_INFO = 512,
  IMAGE_SCN_RESERVED_0040 = 1024,
  IMAGE_SCN_LNK_REMOVE = 2048,
  IMAGE_SCN_LNK_COMDAT = 4096,
  IMAGE_SCN_GPREL = 32768,
  IMAGE_SCN_MEM_16BIT = 131072,
  IMAGE_SCN_MEM_PURGEABLE = 131072,
  IMAGE_SCN_MEM_LOCKED = 262144,
  IMAGE_SCN_MEM_PRELOAD = 524288,
  IMAGE_SCN_ALIGN_1BYTES = 1048576,
  IMAGE_SCN_ALIGN_2BYTES = 2097152,
  IMAGE_SCN_ALIGN_4BYTES = 3145728,
  IMAGE_SCN_ALIGN_8BYTES = 4194304,
  IMAGE_SCN_ALIGN_16BYTES = 5242880,
  IMAGE_SCN_ALIGN_32BYTES = 6291456,
  IMAGE_SCN_ALIGN_64BYTES = 7340032,
  IMAGE_SCN_ALIGN_128BYTES = 8388608,
  IMAGE_SCN_ALIGN_256BYTES = 9437184,
  IMAGE_SCN_ALIGN_512BYTES = 10485760,
  IMAGE_SCN_ALIGN_1024BYTES = 11534336,
  IMAGE_SCN_ALIGN_2048BYTES = 12582912,
  IMAGE_SCN_ALIGN_4096BYTES = 13631488,
  IMAGE_SCN_ALIGN_8192BYTES = 14680064,
  IMAGE_SCN_LNK_NRELOC_OVFL = 16777216,
  IMAGE_SCN_MEM_DISCARDABLE = 33554432,
  IMAGE_SCN_MEM_NOT_CACHED = 67108864,
  IMAGE_SCN_MEM_NOT_PAGED = 134217728,
  IMAGE_SCN_MEM_SHARED = 268435456,
  IMAGE_SCN_MEM_EXECUTE = 536870912,
  IMAGE_SCN_MEM_READ = 1073741824,
  IMAGE_SCN_MEM_WRITE = 2147483648
} SectionFlags;

union Misc {
  dword PhysicalAddress;
  dword VirtualSize;
};

struct IMAGE_SECTION_HEADER {
  char Name[8];
  union Misc Misc;
  ImageBaseOffset32 VirtualAddress;
  dword SizeOfRawData;
  dword PointerToRawData;
  dword PointerToRelocations;
  dword PointerToLinenumbers;
  word NumberOfRelocations;
  word NumberOfLinenumbers;
  enum SectionFlags Characteristics;
};

typedef struct IMAGE_RESOURCE_DIR_STRING_U_8 IMAGE_RESOURCE_DIR_STRING_U_8,
    *PIMAGE_RESOURCE_DIR_STRING_U_8;

struct IMAGE_RESOURCE_DIR_STRING_U_8 {
  word Length;
  wchar16 NameString[4];
};

typedef struct VS_VERSION_INFO VS_VERSION_INFO, *PVS_VERSION_INFO;

struct VS_VERSION_INFO {
  word StructLength;
  word ValueLength;
  word StructType;
  wchar16 Info[16];
  byte Padding[2];
  dword Signature;
  word StructVersion[2];
  word FileVersion[4];
  word ProductVersion[4];
  dword FileFlagsMask[2];
  dword FileFlags;
  dword FileOS;
  dword FileType;
  dword FileSubtype;
  dword FileTimestamp;
};

typedef struct IMAGE_RESOURCE_DATA_ENTRY IMAGE_RESOURCE_DATA_ENTRY, *PIMAGE_RESOURCE_DATA_ENTRY;

struct IMAGE_RESOURCE_DATA_ENTRY {
  dword OffsetToData;
  dword Size;
  dword CodePage;
  dword Reserved;
};

typedef struct VarFileInfo VarFileInfo, *PVarFileInfo;

struct VarFileInfo {
  word wLength;
  word wValueLength;
  word wType;
};

typedef struct IMAGE_RESOURCE_DIRECTORY IMAGE_RESOURCE_DIRECTORY, *PIMAGE_RESOURCE_DIRECTORY;

struct IMAGE_RESOURCE_DIRECTORY {
  dword Characteristics;
  dword TimeDateStamp;
  word MajorVersion;
  word MinorVersion;
  word NumberOfNamedEntries;
  word NumberOfIdEntries;
};

typedef struct StringInfo StringInfo, *PStringInfo;

struct StringInfo {
  word wLength;
  word wValueLength;
  word wType;
};

typedef ACCESS_MASK REGSAM;

typedef LONG LSTATUS;

extern undefined4 g_state_face;
extern HWND hWnd;
extern undefined4 g_rect_offset_right;
extern undefined4 g_state_color;
extern int g_state_difficulty;
extern int g_state_marks;
extern int g_state_sound;
extern int g_state_mine_counter;
extern int g_state_board_height_maybe;
extern int g_state_board_width_maybe;
extern undefined fmt_seconds_string;
extern BOOL g_state_should_commit_to_register;
extern undefined g_default_anon_name;
extern int g_state_time1;
extern int g_state_time2;
extern int g_state_time3;
extern WCHAR g_state_name1[32];
extern WCHAR g_state_name2[32];
extern WCHAR g_state_name3[32];
extern undefined *PTR_GetSystemMetrics_0100110c;
extern undefined4 g_rect_draw_preset_bottom;
extern int g_state_menu;
extern undefined4 g_window_width;
extern undefined4 hGameMenu;
extern int g_state_board_width;
extern undefined4 g_caption_height;
extern int g_state_board_height;
extern undefined4 g_menu_height;
extern BOOL g_state_minimized;
extern undefined4 g_window_height;
extern int g_state_xpos;
extern int g_state_ypos;
extern undefined DAT_00000050;
extern undefined4 hModule;
extern undefined DAT_00000258;
extern undefined DAT_000002bc;
extern byte g_state_game_flags;
extern uint DAT_01005154;
extern int DAT_01005140;
extern int g_mouse_tile_x;
extern int g_mouse_tile_y;
extern int DAT_0100514c;
extern uint DAT_01005144;
extern undefined DAT_01005010;
extern undefined DAT_01005014;
extern undefined DAT_01005018;
extern WCHAR u_XYZZY_01005034;
extern undefined4 DAT_01005148_ACTIVEMAYBE;
extern byte g_mine_board[27][32];
extern undefined DAT_00000064;
extern undefined DAT_000001f4;
extern HICON hIcon;
extern undefined DAT_000001f5;
extern undefined DAT_00007f00;
extern undefined g_class_name;
extern HGLOBAL DAT_01005954;
extern undefined4 BITMAPINFO_number_maybe_0100595c;
extern HGLOBAL DAT_01005a08;
extern undefined4 bitmap_number_maybe_01005a60;
extern HGLOBAL DAT_01005958;
extern undefined4 BITMAPINFO_face_maybe_01005a00;
extern undefined4 bitmap_face_maybe_01005960;
extern BITMAPINFO *DAT_01005a04;
extern undefined4 DAT_01005980;
extern undefined4 DAT_010059c0;
extern undefined4 DAT_01005a20;
extern undefined4 g_hPen;
extern undefined4 g_mines_left;
extern undefined4 g_state_timer_value;
extern undefined *PTR_u_Difficulty_010050d0;
extern undefined4 hKey;
extern int g_state_tick;
extern undefined DAT_80000001;
extern undefined4 g_state_game_active;
extern int g_reveal_queue_write_index;
extern int g_reveal_queue_x[100];
extern int g_reveal_queue_y[100];
extern undefined4 g_state_revealed_tiles;
extern undefined4 DAT_01005168;
extern undefined4 g_state_safe_tiles;
extern int g_mine_counter;
extern undefined DAT_000001b0;
extern undefined DAT_000001b1;
extern undefined DAT_000001b2;
extern WCHAR g_ini_file_name_u_entpack_ini_01005120;
extern int g_border_height;
extern undefined DAT_01005b8c;
extern undefined DAT_01005b90;
extern undefined4 DAT_01005178;
extern undefined4 DAT_01005174;
extern undefined *PTR__adjust_fdiv_01001180;
extern undefined DAT_01005b94;
extern int DAT_01005138;
extern undefined4 DAT_01005170;
extern int DAT_0100516c;
extern undefined *PTR__acmdln_01001190;
extern undefined DAT_010011b8;
extern undefined DAT_010011bc;
extern undefined DAT_010011c0;
extern undefined DAT_010011c4;
extern undefined DAT_01001390;
extern void *ExceptionList;
extern HMODULE DAT_01005180;
extern int DAT_01005188;
extern FARPROC DAT_01005190;
extern undefined DAT_0000000e;
extern undefined DAT_80000000;

#endif
