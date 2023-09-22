// SLIB

#include "wndint"

HINSTANCE exec_adress;
ATOM main_class;
HWND main_wnd;

HDC main_dc;
HFONT default_font;
HBRUSH backgrnd;
COLORREF def_back = 0x0C0C0C; // 0x00BBGGRR

ui64 cellw = 8, cellh = 16;
ui64 clw, clh;
ui64 y_scrl, x_scrl;
UINT mwheel_scroll_ln, mwheel_scroll_ch;

double dpi_scale;

ui64 clmx, clmy;	
ui64 snap_pix = 12;
bool64 snapping;

RECT work_pix;

bool64 topmost;

ATOM initGui(WNDPROC wnd_proc, ui64 opts)
{
	exec_adress = GetModuleHandle(NULL);

	// Create Fake Window to get active monitor's DPI
	HWND wnd = CreateWindowEx(0, L"Button", 0, 0,
		0, 0, 0, 0, 0, 0, exec_adress, 0);
	dpi_scale = (float)GetDpiForWindow(wnd) / 96.0f;
	DestroyWindow(wnd);

	cellw = DPIS(cellw);
	cellh = DPIS(cellh);

	// Create Font ===========================================================================
	default_font = CreateFontA(
		(i32)cellh,				// [I] Height, in logical units
		0,						// [I] Average width, in logical units [0 -> closest match]
		0,						// [I] Angle, between the esc. vect. & the x-ax. of device
		0,						// [I] Angle, between char's base and the x-ax. of device
		0,						// [I] Weight of font in the range 0 - 1000 [0 -> default]
		FALSE,					// [I] Specifies an italic font if set to TRUE
		FALSE,					// [I] Specifies an underlined font if set to TRUE
		FALSE,					// [I] A strikeout font if set to TRUE
		DEFAULT_CHARSET,		// [I] The character set
		OUT_DEFAULT_PRECIS,		// [I] Output precision match h, w, orient., esc., pitch, type
		CLIP_DEFAULT_PRECIS,	// [I] Clipping precision how to clip chars part. outside clip.
		CLEARTYPE_QUALITY,		// [I] Output quality how carefully GDI match to physical font
		DEFAULT_PITCH,			// [I] Pitch and family of the font [chars/25.4mm of text]
		"Consolas");			// [I] Typeface name of the font
	// =========================================================================================

	SystemParametersInfoA(SPI_GETWHEELSCROLLCHARS, 0, &mwheel_scroll_ch, 0);
	SystemParametersInfoA(SPI_GETWHEELSCROLLLINES, 0, &mwheel_scroll_ln, 0);
	SystemParametersInfo(SPI_GETWORKAREA, 0, &work_pix, 0);
	
	if(main_class == 0)
	{
		HICON ico = LoadIcon(exec_adress, L"MAINICON");
		HCURSOR cur = opts & IG_CUSTOM_CUR ? NULL : LoadCursor(NULL, IDC_ARROW);
		backgrnd = CreateSolidBrush(def_back);

		// Register Window Class Atom ==============================================================
		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);				// Structure size in bytes
		wc.style = CS_DBLCLKS;						// Class style, any combination
		wc.lpfnWndProc = wnd_proc;					// Window callback function
		wc.cbClsExtra = 0;							// Extra Class Memory (max 40B)
		wc.cbWndExtra = 0;							// Extra Window Memory (max 40B)
		wc.hInstance = exec_adress;					// Handle to module's instance
		wc.hIcon = ico;								// Def. icon for all windows
		wc.hCursor = cur;							// DC. If NULL app must set cur every time
		wc.hbrBackground = backgrnd;				// Def. brush for WM_ERASEBKGND
		wc.lpszMenuName = NULL;						// Def. menu name for all w.
		wc.lpszClassName = L"wndintMainWnd";		// Name of the Class (Atom)
		wc.hIconSm = 0;								// Def. small icon for all w.

		main_class = RegisterClassEx(&wc);
		// =========================================================================================
	}
	
	return main_class;
}

inline static void pickStyle(ui64 style, DWORD &ws_style, DWORD &ws_ex_style)
{
	if(style & W_BARE)
	{
		ws_style = WS_POPUP;
	}
	else if(style & W_MIN_TITLE)
	{
		ws_style = WS_THICKFRAME | WS_SYSMENU;
	}
	else if(style & W_FULL_TITLE)
	{
		ws_style = WS_OVERLAPPEDWINDOW;
	}
	else
	{
		ws_style = WS_OVERLAPPEDWINDOW;
	}
	
	if(style & W_SCROLL)
	{
		ws_style |= WS_VSCROLL | WS_HSCROLL;
	}
	
	if(style & W_HIDE_TBAR)
	{
		ws_ex_style |= WS_EX_TOOLWINDOW;
	}
}

HWND spawnMainWnd(ui64 style, const wchar_t* title, i32 w, i32 h, i32 x, i32 y)
{
	DWORD style_norm = 0, style_ex = WS_EX_COMPOSITED;
	pickStyle(style, style_norm, style_ex);

	//SystemParametersInfo(SPI_GETWORKAREA, 0, &work_pix, 0);
	//i32 x = (work_pix.right - work_pix.left - w)/2;
	//i32 y = work_pix.bottom - h;

	// Create Window ===========================================================================
	main_wnd = CreateWindowExW(
		style_ex,				//   [I] Extended window style
		(LPCWSTR)main_class,	// [I|O] Class Atom / Class Atom String
		title,					// [I|O] Window name String (Title)
		style_norm,				//   [I] Window style (WS_OVERLAPPED = 0x0)
		x, y, w, h,				//   [I] PosX, PoxY, Width, Height
		NULL,					// [I|O] Handle to this window's parent
		NULL,					// [I|O] Handle to menu / Child-window ID
		exec_adress,			// [I|O] Handle to instance of the module
		NULL);					// [I|O] CREATESTRUCT ptr. for lParam of WM_CREATE
	// =========================================================================================

	UpdateWindow(main_wnd);
	ShowWindow(main_wnd, SW_NORMAL);

	return main_wnd;
}

#pragma warning( disable : 4701 )
HWND spawnMainWnd(ui64 style, const wchar_t* title, i32 w, i32 h, ui64 pos)
{
	i32 x, y;
	
	if(pos & W_LEFT)
	{
		x = work_pix.left;
	}
	else if(pos & W_RIGHT)
	{
		x = work_pix.right - w;
	}
	
	if(pos & W_TOP)
	{
		y = work_pix.top;
	}
	else if(pos & W_BOTTOM)
	{
		y = work_pix.bottom - h;
	}
	
	if(pos & W_CENTER)
	{
		if(pos & 0x3) // LEFT or RIGHT was set
		{
			if(pos & 0xC) // BOTTOM or TOP was set
			{
				goto finish;
			}
			
			y = (work_pix.bottom - work_pix.top)/2 - h/2;
		}
		else  // LEFT or RIGHT was not set
		{
			if(pos & 0xC) // BOTTOM or TOP was set
			{
				x = (work_pix.right - work_pix.left)/2 - w/2;
				goto finish;
			}
			
			goto default_pos;
		}
	}
	
	if(pos == W_DEFAULT)
	{
	default_pos:
		y = (work_pix.bottom - work_pix.top)/2 - h/2;
		x = (work_pix.right - work_pix.left)/2 - w/2;
	}
	
finish:
	
	return spawnMainWnd(style, title, w, h, x, y);
}
#pragma warning( default : 4701 )

HWND spawnWnd(ui64 style, const wchar_t* title, i32 w, i32 h, i32 x, i32 y)
{
	DWORD style_norm = 0, style_ex = WS_EX_COMPOSITED;
	pickStyle(style, style_norm, style_ex);

	// Create Window ===========================================================================
	HWND wnd = CreateWindowExW(
		style_ex,				//   [I] Extended window style
		(LPCWSTR)main_class,	// [I|O] Class Atom / Class Atom String
		title,					// [I|O] Window name String (Title)
		style_norm,				//   [I] Window style (WS_OVERLAPPED = 0x0)
		x, y, w, h,				//   [I] PosX, PoxY, Width, Height
		NULL,					// [I|O] Handle to this window's parent
		NULL,					// [I|O] Handle to menu / Child-window ID
		exec_adress,			// [I|O] Handle to instance of the module
		NULL);					// [I|O] CREATESTRUCT ptr. for lParam of WM_CREATE
	// =========================================================================================

	UpdateWindow(wnd);
	ShowWindow(wnd, SW_NORMAL);

	return wnd;
}

LRESULT wmMovingSnap(LPARAM lp)
{
	if(!snapping)
	{
		return TRUE;
	}
	
	RECT &rec = *((RECT *)lp);
	
	i32 wx = rec.left, wy = rec.top, wxr = rec.right, wyb = rec.bottom;
	i32 sx = work_pix.left, sy = work_pix.top, sxr = work_pix.right, syb = work_pix.bottom;
	i32 ww = rec.right - rec.left, wh = rec.bottom - rec.top;
	i32 sp = (i32)snap_pix;
	
	if(wx - sx < sp)
	{
		rec.left = work_pix.left;
		rec.right = rec.left + ww;
	}
	if(wy - sy < sp)
	{
		rec.top = work_pix.top;
		rec.bottom = rec.top + wh;
	}
	if(sxr - wxr < sp)
	{
		rec.left = work_pix.right - ww;
		rec.right = work_pix.right;
	}
	if(syb - wyb < sp)
	{
		rec.top = work_pix.bottom - wh;
		rec.bottom = work_pix.bottom;
	}
	
	return TRUE;
}




// To make transparent window:
// https://learn.microsoft.com/en-us/windows/win32/winmsg/window-features#layered-windows

// Using a layered window can significantly improve performance and visual effects for a window that has a complex shape,
// animates its shape, or wishes to use alpha blending effects. The system automatically composes and repaints layered windows and the
// windows of underlying applications. As a result, layered windows are rendered smoothly, without the flickering typical of complex
// window regions. In addition, layered windows can be partially translucent, that is, alpha-blended.

// To create a layered window, specify the WS_EX_LAYERED extended window style when calling the CreateWindowEx function, or call the
// SetWindowLong function to set WS_EX_LAYERED after the window has been created. After the CreateWindowEx call, the layered window
// will not become visible until the SetLayeredWindowAttributes or UpdateLayeredWindow function has been called for this window.

// To hide taskbar button:

// The Shell creates a button on the taskbar whenever an application creates a window that isn't owned. To ensure that the window button
// is placed on the taskbar, create an unowned window with the WS_EX_APPWINDOW extended style. To prevent the window button from being
// placed on the taskbar, create the unowned window with the WS_EX_TOOLWINDOW extended style. As an alternative, you can create a hidden
// window and make this hidden window the owner of your visible window.

// ... If you want to dynamically change a window's style to one that does not support visible taskbar buttons, you must hide the window
// first (by calling ShowWindow with SW_HIDE), change the window style, and then show the window.


// Drawing outside of WM_PAINT:
//Although applications carry out most drawing operations while the WM_PAINT message is processing, it is sometimes more efficient for an application to draw directly in a window without relying on the WM_PAINT message. This can be useful when the user needs immediate feedback, such as when selecting text and dragging or sizing an object. In such cases, the application usually draws while processing keyboard or mouse messages.
//
//To draw in a window without using a WM_PAINT message, the application uses the GetDC or GetDCEx function to retrieve a display device context for the window. With the display device context, the application can draw in the window and avoid intruding into other windows. When the application has finished drawing, it calls the ReleaseDC function to release the display device context for use by other applications.
//
//When drawing without using a WM_PAINT message, the application usually does not invalidate the window. Instead, it draws in such a fashion that it can easily restore the window and remove the drawing. For example, when the user selects text or an object, the application typically draws the selection by inverting whatever is already in the window. The application can remove the selection and restore the original contents of the window by simply inverting again.
//
//The application is responsible for carefully managing any changes it makes to the window. In particular, if an application draws a selection and an intervening WM_PAINT message occurs, the application must ensure that any drawing done during the message does not corrupt the selection. To avoid this, many applications remove the selection, carry out usual drawing operations, and then restore the selection when drawing is complete.
