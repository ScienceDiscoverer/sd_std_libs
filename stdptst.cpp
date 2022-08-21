// CONSOLE nDBG nDSEH
//#include <wtxt>
//#include <txtp>
#include <stdp>
#include <txtp>

//#include <sddb>

int wmain()
{
	ui64 ui64_var = 42;
	ui32 ui32_var = 34;
	ui16 ui16_var = 69;
	i64 i64_var = -42;
	i32 i32_var = -34;
	i16 i16_var = -69;
	wchar_t wc_var = '$';
	char c_var = '@';
	bool b_var = true;
	
	p|ui64_var|S|ui32_var|S|ui16_var|S|i64_var|S|i32_var|S|i16_var|S|wc_var|S|c_var|S|b_var|N;
	
	p|H|ui64_var|S|H|ui32_var|S|H|ui16_var|S|H|i64_var|S|H|i32_var|S|H|i16_var|S|H|wc_var|S|H|c_var|S|H|b_var|N;
	
	ui64 hex_tst = 0xBEEF;
	p|H|hex_tst|S|hex_tst|H|S|hex_tst|S|hex_tst|S|H|hex_tst|N;

	//float f
	//double d
	//long double d
	
	const void *vp_var = (const void *)0xDEADBEEF44332211;
	const char *ccp_var = "TEST CONST CHAR POINTER STRING";
	const wchar_t *cwcp_var = L"TEST CONST WIDE CHAR POINTER STRING";
	
	p|vp_var|N|ccp_var|N|cwcp_var|N;
	
	txt txt_var = "TEST TEXT VARIABLE";
	p|txt_var|N;
	#ifdef WTXT_UTF16
	wtxt wt_var = L"TEST WIDE TEXT VARIABLE";
	p|wt_var|N;
	#endif
	
	p|"default"|R|"red"|G|"green"|B|"blue"|Y|"yellow"|V|"violet"|C|"cayan"|D|"default"|N;
	p|"space"|S|"space"|S|"space"|S|"space"|S|"space"|N;
	p|"space"|S|"space"|S|"space"|S|"space"|S|"space"|N;
	
	ui32 hex32 = 0xBEEF2211;
	ui16 hex16 = 0xBEEF;
	p|PN|18446744073709551615|S|PN|111222333444555|S|PN|999|S|PN|44333|N;
	p|PN|H|0xDEADBEEF44332211|'|'|PN|H|hex32|'|'|PN|H|hex16|N;
	
	p|'|'|SP(20, '^')|"foo"|"bar"|L"baz"|N|DP;
	p|'|'|SP(20, '|')|"fii"|"bir"|L"boz"|N;
	p           |"faa"|"bor"|L"boo"|N|DP;
	
	p|SP(40, '*')|vp_var|N|ccp_var|N|cwcp_var|N|txt_var|N;
	
	p|SP(2, '0')|7|S|8|S|9|S|10|S|11|S|12|N|DP;
	
	p|SP(40, '@')|ui64_var|S|ui32_var|S|ui16_var|S|i64_var|S|i32_var|S|i16_var|S|wc_var|S|c_var|S|b_var|N;
	
	p|SP(50, '$')|H|ui64_var|S|H|ui32_var|S|H|ui16_var|S|H|i64_var|S|H|i32_var|S|H|i16_var|S;
	p|H|wc_var|S|H|c_var|S|H|b_var|N;
	
	p|SP(60, '_', PR)|H|hex_tst|S|hex_tst|H|S|hex_tst|S|hex_tst|S|H|hex_tst|N|DP;
	
	// TXT PRINTER
	TxtPrinter tp;
	
	tp|"Testing text printer......................................................................\n";
	tp|ui64_var|S|ui32_var|S|ui16_var|S|i64_var|S|i32_var|S|i16_var|S|wc_var|S|c_var|S|b_var|N;
	tp|H|ui64_var|S|H|ui32_var|S|H|ui16_var|S|H|i64_var|S|H|i32_var|S|H|i16_var|S|H|wc_var|S|H|c_var|S|H|b_var|N;
	tp|H|hex_tst|S|hex_tst|H|S|hex_tst|S|hex_tst|S|H|hex_tst|N;
	
	tp|PN|18446744073709551615|S|PN|111222333444555|S|PN|999|S|PN|44333|N;
	tp|PN|H|0xDEADBEEF44332211|'|'|PN|H|hex32|'|'|PN|H|hex16|N;
	
	tp|'|'|SP(tp, 20, '^')|"foo"|"bar"|"baz"|N|DP;
	tp|'|'|SP(tp, 20, '|')|"fii"|"bir"|"boz"|N;
	tp           |"faa"|"bor"|"boo"|N|DP;
	tp|SP(tp, 40, '*')|vp_var|N|ccp_var|N|"TEST CONST WIDE CHAR POINTER STRING"|N|txt_var|N;
	tp|SP(tp, 2, '0')|7|S|8|S|9|S|10|S|11|S|12|N|DP;
	tp|SP(tp, 40, '@')|ui64_var|S|ui32_var|S|ui16_var|S|i64_var|S|i32_var|S|i16_var|S|wc_var|S|c_var|S|b_var|N;
	tp|SP(tp, 50, '$')|H|ui64_var|S|H|ui32_var|S|H|ui16_var|S|H|i64_var|S|H|i32_var|S|H|i16_var|S;
	tp|H|wc_var|S|H|c_var|S|H|b_var|N;
	tp|SP(tp, 60, '_', PR)|H|hex_tst|S|hex_tst|H|S|hex_tst|S|hex_tst|S|H|hex_tst|N|DP;
	tp|"..........................................................................................\n";
	
	p|!tp;
	
	p|"Cursor on. Sleeping..."|N;
	Sleep(3000);
	p|"Cursor off. Sleeping..."|DC|N;
	Sleep(3000);
	p|"Cursor on. Sleeping..."|EC|N;
	Sleep(3000);
	
	p|"Setting pause..."|P|N;
	
	p|"Cursor on. Sleeping..."|EC|N;
	Sleep(3000);
	
	p|"Setting final pause..."|P;
	
	/* wchar_t buff[10];
	ReadFile(
	GetStdHandle(STD_INPUT_HANDLE),
	buff,
	10,
	(unsigned long *)(&ui64_var),
	NULL); */
	return 0;
}