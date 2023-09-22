// CONSOLE
#include <sddb>
#include <txtp>
#include <wtxtp>
#include <filep>
#include <filer>
#include <ftools>
//#include <filepr>

#include <Mmsystem.h>
#pragma comment ( lib , "winmm" )

bool fail()
{
	p|R|"FAILED"|D;
	PlaySoundA("D:\\Dropbox\\Sounds\\wahwahwaaaaah.wav", NULL, SND_FILENAME | SND_ASYNC);
	return true;
}

bool pass()
{
	p|G|"PASSED"|D;
	return false;
}

void test(const char *name, const txt &tst, const txt &res)
{
	bool failed = tst != res ? fail() : pass();
	p|S|name|N;
	
	if(failed)
	{
		p|Y|"--------------------------CMP--------------------------"|D|N|G|I|D;
		for(ui64 i = 0; i < ~res; ++i)
		{
			p|(tst[i] != res[i] ? R : D)|tst[i];
		}
		p|G|I|N|I|D|res|G|I|D;
		p|N|Y|"--------------------------END--------------------------"|D|N;
	}
}

void test(const char *name, const wtxt &tst, const wtxt &res)
{
	bool failed = tst != res ? fail() : pass();
	p|S|name|N;
	
	if(failed)
	{
		if(~tst != ~res)
		{
			p|Y|"SIZE MISTMATCH: "|R|~tst|D|S|~res|N;
		}
		
		p|Y|"--------------------------CMP--------------------------"|D|N|G|I|D;
		for(ui64 i = 0; i < ~res; ++i)
		{
			p|(tst[i] != res[i] ? R : D)|tst[i];
		}
		p|G|I|N|I|D|res|G|I|D;
		p|N|Y|"--------------------------END--------------------------"|D|N;
	}
}

txt txtp_test = L(
"Testing text printer......................................................................\n"
"42 34 69 -42 -34 -69 $ @ true\n"
"000000000000002A 00000022 0045 FFFFFFFFFFFFFFD6 FFFFFFFFFFFFFFDE FFFFFFFFFFFFFFBB $ @ true\n"
"000000000000BEEF 48879 000000000000BEEF 48879 000000000000BEEF\n"
"18'446'744'073'709'551'615 111'222'333'444'555 999 44'333\n"
"DE AD BE EF 44 33 22 11|BE EF 22 11|BE EF\n"
"|^^^^^^^^^^^^^^^^^foo^^^^^^^^^^^^^^^^^bar^^^^^^^^^^^^^^^^^baz\n"
"||||||||||||||||||fii|||||||||||||||||bir|||||||||||||||||boz\n"
"|||||||||||||||||faa|||||||||||||||||bor|||||||||||||||||boo\n"
"**********************0xDEADBEEF44332211\n"
"**********TEST CONST CHAR POINTER STRING\n"
"**********TEST CONST CHAR LITERAL STRING\n"
"**********************TEST TEXT VARIABLE\n"
"07 08 09 10 11 12\n"
"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@42 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@34 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@69 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-42 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-34 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-69 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@$ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@true\n"
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$000000000000002A $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$00000022 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$0045 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$FFFFFFFFFFFFFFD6 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$FFFFFFFFFFFFFFDE $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$FFFFFFFFFFFFFFBB $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$@ $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$true\n"
"000000000000BEEF____________________________________________ 48879_______________________________________________________ 000000000000BEEF____________________________________________ 48879_______________________________________________________ 000000000000BEEF____________________________________________\n"
"..........................................................................................\n");

txt txtp_new_pad_test = L(
"Time: 03:07:42.009\n"
"12344321\n"
"[RPad      ][   LPadDef][RPAD______][NOPAD]\n"
"[            >!CENTERED!<            ][NOPAD]\n");

wtxt wtxtp_test = WL(
"Testing wtext printer......................................................................\n"
"42 34 69 -42 -34 -69 $ @ true\n"
"000000000000002A 00000022 0045 FFFFFFFFFFFFFFD6 FFFFFFFFFFFFFFDE FFFFFFFFFFFFFFBB $ @ true\n"
"000000000000BEEF 48879 000000000000BEEF 48879 000000000000BEEF\n"
"18'446'744'073'709'551'615 111'222'333'444'555 999 44'333\n"
"DE AD BE EF 44 33 22 11|BE EF 22 11|BE EF\n"
"|^^^^^^^^^^^^^^^^^foo^^^^^^^^^^^^^^^^^bar^^^^^^^^^^^^^^^^^baz\n"
"||||||||||||||||||fii|||||||||||||||||bir|||||||||||||||||boz\n"
"|||||||||||||||||faa|||||||||||||||||bor|||||||||||||||||boo\n"
"**********************0xDEADBEEF44332211\n"
"*****TEST CONST WIDE CHAR POINTER STRING\n"
"*****TEST CONST WIDE CHAR LITERAL STRING\n"
"*****************TEST WIDE TEXT VARIABLE\n"
"07 08 09 10 11 12\n"
"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@42 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@34 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@69 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-42 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-34 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-69 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@$ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@true\n"
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$000000000000002A $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$00000022 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$0045 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$FFFFFFFFFFFFFFD6 $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$FFFFFFFFFFFFFFDE $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$FFFFFFFFFFFFFFBB $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$@ $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$true\n"
"000000000000BEEF____________________________________________ 48879_______________________________________________________ 000000000000BEEF____________________________________________ 48879_______________________________________________________ 000000000000BEEF____________________________________________\n"
"..........................................................................................\n");

wtxt wtxtp_new_pad_test = t2u16(txtp_new_pad_test);

txt unicode_test = L(
"[✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶✶I'M A STAR!]\n"
"[░░░░░░░░░░░░░░░I'M SHADY!░░░░░░░░░░░░░░░]\n"
"░░░✶✶✶░░░\n"
"✶░░░✶");

wtxt wtxtp_unicode_test = t2u16(unicode_test);

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
	
	txt txt_var = L("TEST TEXT VARIABLE");
	p|txt_var|N;
	#ifdef WTXT_UTF16
	wtxt wt_var = WL("TEST WIDE TEXT VARIABLE");
	p|wt_var|N;
	#endif
	
	p|"default"|R|"red"|G|"green"|B|"blue"|Y|"yellow"|V|"violet"|C|"cayan"|D|"default"|N;
	p|"space"|S|"space"|S|"space"|S|"space"|S|"space"|N;
	p|"space"|S|"space"|S|"space"|S|"space"|S|"space"|N;
	
	ui32 hex32 = 0xBEEF2211;
	ui16 hex16 = 0xBEEF;
	p|PN|18446744073709551615|S|PN|111222333444555|S|PN|999|S|PN|44333|N;
	p|PN|H|0xDEADBEEF44332211|'|'|PN|H|hex32|'|'|PN|H|hex16|N;
	
	p|'|'|SP(20)|SPC('^')|"foo"|"bar"|L"baz"|N|DP;
	p|'|'|SP(20)|SPC('|')|"fii"|"bir"|L"boz"|N;
	p					 |"faa"|"bor"|L"boo"|N|DP;
	
	p|SP(40)|SPC('*')|vp_var|N|ccp_var|N|cwcp_var|N|txt_var|N;
	
	p|SP(2)|SPC('0')|7|S|8|S|9|S|10|S|11|S|12|N|DP;
	
	p|SP(40)|SPC('@')|ui64_var|S|ui32_var|S|ui16_var|S|i64_var|S|i32_var|S|i16_var|S|wc_var|S|c_var|S|b_var|N;
	
	p|SP(50)|SPC('$')|H|ui64_var|S|H|ui32_var|S|H|ui16_var|S|H|i64_var|S|H|i32_var|S|H|i16_var|S;
	p|H|wc_var|S|H|c_var|S|H|b_var|N;
	
	p|SP(60)|SPC('_')|SPD(PADR)|H|hex_tst|S|hex_tst|H|S|hex_tst|S|hex_tst|S|H|hex_tst|N|DP;
	
	p|"34 spaces "|I|S(34)|I|N; // result: 34 spaces [                                  ]
	
	p|N|"File table"|N;
	p|TM; // TABLE MODE ENGAGED ===============================
	p|"Name"		|  "Size"		|"Modify Date"		|"Type"					|TN;
	p|"backblue.gif"|  "5 KB"		|"01.08.2023 6:19"	|"GIF File"				|TN;
	p|"cookies.txt"	|  "30 KB"		|"04.08.2023 9:25"	|"Notepad++ Document"	|TN;
	p|"fade.gif"	|G|"1 KB"|D		|"01.08.2023 6:19"	|"GIF File"				|TN;
	p|"hts-log.txt"	|R|"3 792 KB"|D	|"04.08.2023 9:25"	|"Notepad++ Document"	|TN;
	p|"zoostar.org"	|  ""			|"04.08.2023 5:53"	|"Folder"				|TN;
	p|TE; // TABLE MODE DISENGAGED ============================
	
	p|N;
	
	p|"File table 2"|N;
	p|TM; // TABLE MODE ENGAGED ===============================
	p|TCP(8)					|TCP(4)			|TCP(2);
	p|		TAC|"Name"			| 	"Size"		|	"Modify Date"	|		 	"Type"			|TN;
	p|TAL|"backblue_long.gif"	|G|"5 KB"|D		|"01.08.2023 6:19"	|			  TAR|"GIF File"|TN;
	p|TAL|"cookies.txt"			|  "30 KB"		|"04.08.2023 9:25"	|	TAR|"Notepad++ Document"|TN;
	p|TAL|"fade.gif"			|  "1 KB"		|"01.08.2023 6:19"	|			  TAR|"GIF File"|TN;
	p|TAL|"hts-log.txt"			|R|"3 792 KB"|D	|"04.08.2023 9:25"	|	TAR|"Notepad++ Document"|TN;
	p|TAL|"zoostar.org"			|  ""			|"04.08.2023 5:53"	|				TAR|"Folder"|TN;
	p|TE; // TABLE MODE DISENGAGED ============================
	
	p|N;
	
	p|SPC('0');
	p|"Time: "|SPN(2)|3|":"|SPN(2)|7|":"|SPN(2)|42|"."|SPN(3)|9|N;
	p|DP;
	p|SPC('0')|SP(4)|1234|DP|SPN(4)|SPCN('0')|4321|N;
	p|I|SPN(10)|SPDN(PADR)|"RPad"|I|I|SPN(10)|"LPadDef"|I|I|SPN(10)|SPDN(PADR)|SPCN('_')|"RPAD"|I|I|"NOPAD"|I|N;
	p|I|SPN(24)|SPDN(PADC)|">!CENTERED!<"|I|I|"NOPAD"|I|N;
	
	p|N;
	
	p|I|SPN(30)|SPCN(0x2736)|"I'M A STAR!"|I|N; // SIX POINTED BLACK STAR ✶
	p|I|SPN(30)|SPCN(0x2591)|SPDN(PADC)|"I'M SHADY!"|I|N; // LIGHT SHADE ░
	p|"░░░✶✶✶░░░"|N;
	p|(wchar_t)0x2736|(wchar_t)0x2591|(wchar_t)0x2591|(wchar_t)0x2591|(wchar_t)0x2736|N;
	
	p|N|L("FAST PRINTING!")|N|N;
	
	// TXT PRINTER
	TxtPrinter tp;
	
	tp|"Testing text printer......................................................................\n";
	tp|ui64_var|S|ui32_var|S|ui16_var|S|i64_var|S|i32_var|S|i16_var|S|wc_var|S|c_var|S|b_var|N;
	tp|H|ui64_var|S|H|ui32_var|S|H|ui16_var|S|H|i64_var|S|H|i32_var|S|H|i16_var|S|H|wc_var|S|H|c_var|S|H|b_var|N;
	tp|H|hex_tst|S|hex_tst|H|S|hex_tst|S|hex_tst|S|H|hex_tst|N;
	
	tp|PN|18446744073709551615|S|PN|111222333444555|S|PN|999|S|PN|44333|N;
	tp|PN|H|0xDEADBEEF44332211|'|'|PN|H|hex32|'|'|PN|H|hex16|N;
	
	tp|'|'|SP(20)|SPC('^')|"foo"|"bar"|"baz"|N|DP;
	tp|'|'|SP(20)|SPC('|')|"fii"|"bir"|"boz"|N;
	tp          		  |"faa"|"bor"|"boo"|N|DP;
	tp|SP(40)|SPC('*')|vp_var|N|ccp_var|N|"TEST CONST CHAR LITERAL STRING"|N|txt_var|N;
	tp|SP(2)|SPC('0')|7|S|8|S|9|S|10|S|11|S|12|N|DP;
	tp|SP(40)|SPC('@')|ui64_var|S|ui32_var|S|ui16_var|S|i64_var|S|i32_var|S|i16_var|S|wc_var|S|c_var|S|b_var|N;
	tp|SP(50)|SPC('$')|H|ui64_var|S|H|ui32_var|S|H|ui16_var|S|H|i64_var|S|H|i32_var|S|H|i16_var|S;
	tp|H|wc_var|S|H|c_var|S|H|b_var|N;
	tp|SP(60)|SPC('_')|SPD(PADR)|H|hex_tst|S|hex_tst|H|S|hex_tst|S|hex_tst|S|H|hex_tst|N|DP;
	tp|"..........................................................................................\n";
	
	test("TXTP TEST", *tp, txtp_test);
	
	tp|CL;
	
	tp|SPC('0');
	tp|"Time: "|SPN(2)|3|":"|SPN(2)|7|":"|SPN(2)|42|"."|SPN(3)|9|N;
	tp|DP;
	tp|SPC('0')|SP(4)|1234|DP|SPN(4)|SPCN('0')|4321|N;
	tp|I|SPN(10)|SPDN(PADR)|"RPad"|I|I|SPN(10)|"LPadDef"|I|I|SPN(10)|SPDN(PADR)|SPCN('_')|"RPAD"|I|I|"NOPAD"|I|N;
	tp|I|SPN(24)|SPDN(PADC)|">!CENTERED!<"|I|I|"NOPAD"|I|N;
	
	test("TXTP NEW PADDING TEST", *tp, txtp_new_pad_test);
	
	txt tp_clear_0 = L(
	"baka\n"
	"sete\n"
	"noka\n"
	"rara\n");
	
	txt tp_clear_1 = L(
	"BAKA\n"
	"SETE\n");
	
	txt tp_clear_2 = L(
	"1000\n"
	"1111\n"
	"2222\n"
	"3333\n");
	
	txt tp_clear_3 = L(
	"4444\n"
	"5555\n");
	
	txtp tpcl0;
	tpcl0|"baka"|N|"sete"|N|"noka"|N|"rara"|N;
	test("TXTP CLEAR TEST 0", *tpcl0, tp_clear_0);
	
	tpcl0|CL|"BAKA"|N|"SETE"|N;
	test("TXTP CLEAR TEST 1", *tpcl0, tp_clear_1);
	
	txtp tpcl1;
	tpcl1|1000|N|1111|N|2222|N|3333|N;
	test("TXTP CLEAR TEST 2", *tpcl1, tp_clear_2);
	
	tpcl1|CL|4444|N|5555|N;
	test("TXTP CLEAR TEST 3", *tpcl1, tp_clear_3);
	test("TXTP CLEAR TEST 3 RAW BUFFER", *tpcl1, tp_clear_3);
	
	txt sp_34 = L("                                  ");
	txtp spp;
	spp|S(34);
	test("TXTP SPACE PRINT", *spp, sp_34);
	
	// WTXT PRINTER
	WtxtPrinter wtp;
	
	wtp|L"Testing wtext printer......................................................................\n";
	wtp|ui64_var|S|ui32_var|S|ui16_var|S|i64_var|S|i32_var|S|i16_var|S|wc_var|S|c_var|S|b_var|N;
	wtp|H|ui64_var|S|H|ui32_var|S|H|ui16_var|S|H|i64_var|S|H|i32_var|S|H|i16_var|S|H|wc_var|S|H|c_var|S|H|b_var|N;
	wtp|H|hex_tst|S|hex_tst|H|S|hex_tst|S|hex_tst|S|H|hex_tst|N;
	
	wtp|PN|18446744073709551615|S|PN|111222333444555|S|PN|999|S|PN|44333|N;
	wtp|PN|H|0xDEADBEEF44332211|'|'|PN|H|hex32|'|'|PN|H|hex16|N;
	
	wtp|'|'|SP(20)|SPC('^')|L"foo"|L"bar"|L"baz"|N|DP;
	wtp|'|'|SP(20)|SPC('|')|L"fii"|L"bir"|L"boz"|N;
	wtp         		   |L"faa"|L"bor"|L"boo"|N|DP;
	wtp|SP(40)|SPC('*')|vp_var|N|cwcp_var|N|L"TEST CONST WIDE CHAR LITERAL STRING"|N|wt_var|N;
	wtp|SP(2)|SPC('0')|7|S|8|S|9|S|10|S|11|S|12|N|DP;
	wtp|SP(40)|SPC('@')|ui64_var|S|ui32_var|S|ui16_var|S|i64_var|S|i32_var|S|i16_var|S|wc_var|S|c_var|S|b_var|N;
	wtp|SP(50)|SPC('$')|H|ui64_var|S|H|ui32_var|S|H|ui16_var|S|H|i64_var|S|H|i32_var|S|H|i16_var|S;
	wtp|H|wc_var|S|H|c_var|S|H|b_var|N;
	wtp|SP(60)|SPC('_')|SPD(PADR)|H|hex_tst|S|hex_tst|H|S|hex_tst|S|hex_tst|S|H|hex_tst|N|DP;
	wtp|L"..........................................................................................\n";
	
	test("WTXTP TEST", *wtp, wtxtp_test);
	
	wtp|CL;
	
	wtp|SPC('0');
	wtp|L"Time: "|SPN(2)|3|L":"|SPN(2)|7|L":"|SPN(2)|42|L"."|SPN(3)|9|N;
	wtp|DP;
	wtp|SPC('0')|SP(4)|1234|DP|SPN(4)|SPCN('0')|4321|N;
	wtp|I|SPN(10)|SPDN(PADR)|L"RPad"|I|I|SPN(10)|L"LPadDef"|I|I|SPN(10)|SPDN(PADR)|SPCN('_')|L"RPAD"|I|I|L"NOPAD"|I|N;
	wtp|I|SPN(24)|SPDN(PADC)|L">!CENTERED!<"|I|I|L"NOPAD"|I|N;
	
	test("WTXTP NEW PADDING TEST", *wtp, wtxtp_new_pad_test);
	
	wtp|CL;
	
	wtp|I|SPN(30)|SPCN(0x2736)|L"I'M A STAR!"|I|N; // SIX POINTED BLACK STAR ✶
	wtp|I|SPN(30)|SPCN(0x2591)|SPDN(PADC)|L"I'M SHADY!"|I|N; // LIGHT SHADE ░
	wtp|t2u16(L("░░░✶✶✶░░░"))|N;
	wtp|(wchar_t)0x2736|(wchar_t)0x2591|(wchar_t)0x2591|(wchar_t)0x2591|(wchar_t)0x2736;
	
	test("WTXTP UNICODE TEST", *wtp, wtxtp_unicode_test);
	
	wtxt wtp_clear_0 = WL(
	"baka\n"
	"sete\n"
	"noka\n"
	"rara\n");
	
	wtxt wtp_clear_1 = WL(
	"BAKA\n"
	"SETE\n");
	
	wtxt wtp_clear_2 = WL(
	"1000\n"
	"1111\n"
	"2222\n"
	"3333\n");
	
	wtxt wtp_clear_3 = WL(
	"4444\n"
	"5555\n");
	
	wtxtp wtpcl0;
	wtpcl0|L"baka"|N|L"sete"|N|L"noka"|N|L"rara"|N;
	test("WTXTP CLEAR TEST 0", *wtpcl0, wtp_clear_0);
	
	wtpcl0|CL|L"BAKA"|N|L"SETE"|N;
	test("WTXTP CLEAR TEST 1", *wtpcl0, wtp_clear_1);
	
	wtxtp wtpcl1;
	wtpcl1|1000|N|1111|N|2222|N|3333|N;
	test("WTXTP CLEAR TEST 2", *wtpcl1, wtp_clear_2);
	
	wtpcl1|CL|4444|N|5555|N;
	test("WTXTP CLEAR TEST 3", *wtpcl1, wtp_clear_3);
	test("WTXTP CLEAR TEST 3 RAW BUFFER", *wtpcl1, wtp_clear_3);
	
	wtxt wsp_34 = WL("                                  ");
	wtxtp wspp;
	wspp|S(34);
	test("WTXTP SPACE PRINT", *wspp, wsp_34);
	
	// FILE PRINTER/READER
	if(!fileExists("tstf"))
	{
		CreateDirectoryA("tstf", NULL);
	}
	
	FilePrinter fp = "tstf\\fpr.txt";
	
	fp|TRN;
	
	fp|"Testing text printer......................................................................\n";
	fp|ui64_var|S|ui32_var|S|ui16_var|S|i64_var|S|i32_var|S|i16_var|S|wc_var|S|c_var|S|b_var|N;
	fp|H|ui64_var|S|H|ui32_var|S|H|ui16_var|S|H|i64_var|S|H|i32_var|S|H|i16_var|S|H|wc_var|S|H|c_var|S|H|b_var|N;
	fp|H|hex_tst|S|hex_tst|H|S|hex_tst|S|hex_tst|S|H|hex_tst|N;
	
	fp|PN|18446744073709551615|S|PN|111222333444555|S|PN|999|S|PN|44333|N;
	fp|PN|H|0xDEADBEEF44332211|'|'|PN|H|hex32|'|'|PN|H|hex16|N;
	
	fp|'|'|SP(20)|SPC('^')|"foo"|"bar"|"baz"|N|DP;
	fp|'|'|SP(20)|SPC('|')|"fii"|"bir"|"boz"|N;
	fp          		  |"faa"|"bor"|"boo"|N|DP;
	fp|SP(40)|SPC('*')|vp_var|N|ccp_var|N|"TEST CONST CHAR LITERAL STRING"|N|txt_var|N;
	fp|SP(2)|SPC('0')|7|S|8|S|9|S|10|S|11|S|12|N|DP;
	fp|SP(40)|SPC('@')|ui64_var|S|ui32_var|S|ui16_var|S|i64_var|S|i32_var|S|i16_var|S|wc_var|S|c_var|S|b_var|N;
	fp|SP(50)|SPC('$')|H|ui64_var|S|H|ui32_var|S|H|ui16_var|S|H|i64_var|S|H|i32_var|S|H|i16_var|S;
	fp|H|wc_var|S|H|c_var|S|H|b_var|N;
	fp|SP(60)|SPC('_')|SPD(PADR)|H|hex_tst|S|hex_tst|H|S|hex_tst|S|hex_tst|S|H|hex_tst|N|DP;
	fp|"..........................................................................................\n";
	
	fp|FC;
	
	FileReader fr = "tstf\\fpr.txt";
	
	txt file;
	fr > file > FC;
	
	//FilePrinter fp0 = "tstf\\fpr_read_out.txt";
	//fp0|file|FC;
	
	test("FILEPR TEST", file, txtp_test);
	
	txt limited_file;
	fr < FO("tstf\\fpr.txt") > FRL(21) > limited_file > FC;
	
	test("FILER LIMIT", limited_file, txts(txtp_test, 0, 21));
	
	//MAKE O MANIPULATOR TO MAKE THIS WORK! O|"NEXTFAILENAME"; O > "NEXTFILENAME";
	
	fp|FO("tstf\\fpr.txt")|APP;
	
	fp|SPC('0');
	fp|"Time: "|SPN(2)|3|":"|SPN(2)|7|":"|SPN(2)|42|"."|SPN(3)|9|N;
	fp|DP;
	fp|SPC('0')|SP(4)|1234|DP|SPN(4)|SPCN('0')|4321|N;
	fp|I|SPN(10)|SPDN(PADR)|"RPad"|I|I|SPN(10)|"LPadDef"|I|I|SPN(10)|SPDN(PADR)|SPCN('_')|"RPAD"|I|I|"NOPAD"|I|N;
	fp|I|SPN(24)|SPDN(PADC)|">!CENTERED!<"|I|I|"NOPAD"|I|N;
	
	fp|FC;
	
	fr < FO("tstf\\fpr.txt");
	fr > file > FC;
	
	test("FILEPR NEW PADDING TEST", file, txtp_test + txtp_new_pad_test);
	
	// PAUSE
	p|"Press any button to go to pause test!"|P|N|"Cursor on. Sleeping..."|N;
	Sleep(3000);
	p|"Cursor off. Sleeping..."|DC|N;
	Sleep(3000);
	p|"Cursor on. Sleeping..."|EC|N;
	Sleep(3000);
	
	p|"Setting pause..."|P|N;
	
	p|"Cursor on. Sleeping..."|EC|N;
	Sleep(3000);
	
	p|CLS;
	
	p|"Screen was cleared. Setting final pause..."|P;
	
	/* wchar_t buff[10];
	ReadFile(
	GetStdHandle(STD_INPUT_HANDLE),
	buff,
	10,
	(unsigned long *)(&ui64_var),
	NULL); */
	return 0;
}