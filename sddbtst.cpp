// CONSOLE
#include <sddb>

i32 wmain()
{
	char s[] = "123456789\n123456789\n123456789 123456789 123456789";
	char *e = s+49;
	_DBG_P(truncStr(s, e, 20));
	_DBG_P(truncStr(s, e, 80));
	
	dbgmb(L("HELLO WURLD"));
	
	_DBG_SBP;

	if(!dbgmbChoice(L("BAKA OR NO BAKA?!")))
	{
		_DBG_HBP;
	}
	
	
	_DBG_SBP;
	
	
	p|"tesuto"|N;
	
	_dbgWnd();
	
	txtp tp;
	
	dbgp|"someint";
	_pVarName();
	dbgp|4269;
	_pVarVal();
	
	dbgp|"somestring";
	_pVarName();
	dbgp|"bakaaaaaaaaaaaaaaamonoNEWLINE->\ndessssssss!~~~\ndessssssss!~~~\ndessssssss!~~~";
	_pVarVal();
	
	dbgp|"somebool";
	_pVarName();
	dbgp|true|N;
	_pVarVal();
	
	dbgp|"somehex";
	_pVarName();
	dbgp|H|0xDEADBEEF|N;
	_pVarVal();
	
	dbgp|"longline";
	_pVarName();
	dbgp|"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque ut suscipit mi, vel condimentum metus. Etiam vestibulum dapibus fermentum. Vivamus in maximus velit. Donec tempor turpis justo. Duis luctus id risus vitae accumsan. Duis volutpat tincidunt felis, non ullamcorper augue cursus quis. Morbi maximus, odio at pellentesque eleifend, erat magna accumsan risus, sollicitudin aliquet est nulla eu augue.";
	_pVarVal();
	
	//Sleep(2000);
	_DBG_SBP;
	
	dbgp|"someint";
	_pVarName();
	dbgp|34341619;
	_pVarVal();
	
	dbgp|"somestring";
	_pVarName();
	dbgp|"karamba!!!!!!!!!!!!!!!!!CR+NEWLINE->\r\ndessssssss~~~\r\ndessssssss~~~\r\ndessssssss~~~\ndessssssss~~~";
	_pVarVal();
	
	dbgp|"somebool";
	_pVarName();
	dbgp|false|N;
	_pVarVal();
	
	dbgp|"somehex";
	_pVarName();
	dbgp|H|0x1010101010101010|N;
	_pVarVal();
	
	dbgp|"longline";
	_pVarName();
	dbgp|"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque ut suscipit mi, vel condimentum metus. Etiam vestibulum dapibus fermentum. Vivamus in maximus velit. Donec tempor turpis justo. Duis luctus id risus vitae accumsan. Duis volutpat tincidunt felis, non ullamcorper augue cursus quis. Morbi maximus, odio at pellentesque eleifend, erat magna accumsan risus, sollicitudin aliquet est nulla eu augue.";
	_pVarVal();
	
	//Sleep(2000);
	_softBp(__LINE__);
	
	dbgp|"someint";
	_pVarName();
	dbgp|34341619;
	_pVarVal();
	
	dbgp|"somestring";
	_pVarName();
	dbgp|"karamba!!!!!!!!!!!!!!!!!CR+NEWLINE->\r\ndessssssss~~~\r\ndessssssss~~~\r\ndessssssss~~~\ndessssssss~~~";
	_pVarVal();
	
	dbgp|"somebool";
	_pVarName();
	dbgp|false|N;
	_pVarVal();
	
	dbgp|"somehex";
	_pVarName();
	dbgp|H|0x1010101010101010|N;
	_pVarVal();
	
	dbgp|"longline";
	_pVarName();
	dbgp|"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque ut suscipit mi, vel condimentum metus. Etiam vestibulum dapibus fermentum. Vivamus in maximus velit. Donec tempor turpis justo. Duis luctus id risus vitae accumsan. Duis volutpat tincidunt felis, non ullamcorper augue cursus quis. Morbi maximus, odio at pellentesque eleifend, erat magna accumsan risus, sollicitudin aliquet est nulla eu augue.";
	_pVarVal();
	
	p|"AFTER!!!";
	
	
	_DBG_P("_DBG_P TEST");
	_DBG_P(L"WIDESTRING LITERAL _DBG_P TEST");
	
	
	wtxt wtxt_tst = WL("WTXT VARIABLE Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque ut suscipit mi, vel...");
	_DBG_P(wtxt_tst);
	
	txt txt_tst = L("TXT VARIABLE Donec tempor turpis justo. Duis luctus id risus vitae accumsan. Duis volutpat tincidunt felis!");
	_DBG_P(txt_tst);
	
	ui64 var_tst = 123456789;
	_DBG_P(var_tst);
	
	ui64 var_tst_h = 0xDEADBEEF;
	_DBG_PH(var_tst_h);
	

	ui32 ui0 = 111222333;
	_DBG_P(ui0);
	uli32 ui1 = 333222111;
	_DBG_P(ui1);
	ui16 ui2 = 6996;
	_DBG_P(ui2);
	i64 i0 = -111444;
	_DBG_P(i0);
	i32 i1 = -343434;
	_DBG_P(i1);
	li32 i2 = -424242;
	_DBG_P(i2);
	i16 i3 = -22222;
	_DBG_P(i3);
	wchar_t wc = 0x2020; // Dagger
	_DBG_P(wc);
	char c = '*';
	_DBG_P(c);
	bool b = false;
	_DBG_P(b);
	const void *vp = (const void *)0xDEADBEEFFFFFFFFF;
	_DBG_P(vp);
	const char *ccp = "CONST CHAR POINTER VARIABLE Pellentesque ut suscipit mi, vel condimentum metus. Etiam vestibulum dapibus fermentum.";
	_DBG_P(ccp);
	const wchar_t *wccp = L"Duis volutpat tincidunt felis, non ullamcorper augue cursus quis. Morbi maximus, odio at pellentesque eleifend, erat magna accumsan risus, sollicitudin aliquet est nulla eu augue.";
	_DBG_P(wccp);
	
	_DBG_SBP;
	
	const char *nlstr = "Pellentesque ut suscipit mi, vel condimentum metus.\nEtiam vestibulum dapibus fermentum.\nVivamus in maximus velit.\nDonec tempor turpis justo.";
	for(ui64 i = 0; i < 10; ++i)
	{
		Sleep(600);
		_DBG_P(nlstr);
	}
	
	_DBG_P(42);
	
	_DBG_SBP;
	_DBG_SBP;
	_DBG_SBP;
	
	SWSET
	for(ui64 i = 0; i < 1024; ++i)
	{
		p|txt_tst|N;
	}
	SWSTOP
	SWSET
	for(ui64 i = 0; i < 1024; ++i)
	{
		_DBG_P(txt_tst);
	}
	SWSTOP
	SWSET
	for(ui64 i = 0; i < 1024; ++i)
	{
		dbgFileLog(txt_tst);
	}
	SWSTOP
	
	p|"CONSOLE:  "; SWPRINT // 364.340'500 ms
	p|"DBG WND:  "; SWPRINT // 2.301 s 6.32x slower than console
	p|"FILE LOG: "; SWPRINT // 40.171'600 ms 9.1x faster than console
	
	_DBG_SBP;
	return 0;
}