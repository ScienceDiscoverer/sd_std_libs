// SLIB
#include "stdp"

HANDLE StdPrinter::oh = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE StdPrinter::ih = GetStdHandle(STD_INPUT_HANDLE);
DWORD StdPrinter::bw;
WORD StdPrinter::defc = StdPrinter::GetDefConParams();
CONSOLE_CURSOR_INFO StdPrinter::con;
CONSOLE_CURSOR_INFO StdPrinter::coff;
DWORD StdPrinter::mod;

StdPrinter p;

StdPrinter & TB(StdPrinter &stdp)
{
    /* typedef struct _CONSOLE_SCREEN_BUFFER_INFO {
	  COORD      dwSize;
	  COORD      dwCursorPosition;
	  WORD       wAttributes;
	  SMALL_RECT srWindow;
	  COORD      dwMaximumWindowSize;
	} CONSOLE_SCREEN_BUFFER_INFO; */
	
	static CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(stdp.oh, &csbi);
	
	static HANDLE heap = GetProcessHeap();
	CHAR_INFO *pci = (CHAR_INFO *)HeapAlloc(heap, 0, csbi.dwSize.X * csbi.dwSize.Y * sizeof(CHAR_INFO));
	
	/* typedef struct _CHAR_INFO {
	  union {
		WCHAR UnicodeChar;
		CHAR  AsciiChar;
	  } Char;
	  WORD  Attributes;
	} CHAR_INFO, *PCHAR_INFO; */
	
	SMALL_RECT read_region;
	read_region.Left = 0;
	read_region.Top = 0;
	read_region.Right = csbi.dwSize.X;
	read_region.Bottom = csbi.dwSize.Y;
	COORD buff_sz = csbi.dwSize;
	COORD buff_coord = {0};
	ReadConsoleOutputA(stdp.oh,	pci, buff_sz, buff_coord, &read_region);
	
	ui32 last_row = 0;
	for(ui32 i = 0; i < (ui32)csbi.dwSize.Y; ++i)
	{
		ui32 spaces = 0;
		for(ui32 j = 0; j < (ui32)csbi.dwSize.X; ++j)
		{
			if(pci[i * csbi.dwSize.X + j].Char.AsciiChar == ' ')
			{
				++spaces;
			}
		}
		
		if(spaces != (ui32)csbi.dwSize.X)
		{
			last_row = i;
		}
	}
	
	//p|"last_row "|last_row|N;
	
	buff_sz.Y = (SHORT)last_row + 6;
	if(buff_sz.Y < csbi.srWindow.Bottom - csbi.srWindow.Top)
	{
		buff_sz.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	}
	
	// Window size must be always at least 1 cell less than buffer size
	// Reason: probably because srWindow is coordinates, swSize is actual number of cells
	SetConsoleScreenBufferSize(stdp.oh, buff_sz);
	
	HeapFree(heap, 0, pci);
	
	return stdp;
}