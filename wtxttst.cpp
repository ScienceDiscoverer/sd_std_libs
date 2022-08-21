// CONSOLE NOPT
// DSEH DBG
#include <wtxt>
#include <sddb>

#include <string> // Just for profiling test, otherwise, casual std bs!

/* DONE TRIMM OPERATOR, MB -- WILL REMOVE EMPTY 0 CHARS FROM THE END OF BUFFER AND RECALC IT'S SIZE
TODO t2i & i2t + hex
TODO < > OPERATORS FOR SORTING STRINGZ SMART NUMERIC\LEXICONUMERIC MB TEST ON WIN SHELL
TODO i2ts styling function that will produce styled numbers thousands/bytes separators no hex zero pad etc.
EXAMPLE
int digs = 0;
do
{
	b[--c] = i % 10 | 0x30;
	i /= 10;
	
	if(++digs % 3/*2fh/ == 0)
	{
		b[--c] = 0x27;
	}
}
while(i > 0);

DONE!!!!!! CREATE CUSTOM HEAP EXCLUSIVE FOR STRINGS EXCLUSIVE LOCK NO OTHER THREADZ CAN INTEFEARE IN STRIN OPERATIONS!
DONE!!!!!! Use of Lookaside lists. The heap data structure uses a fast cache for all free items of blocks sized between 8 and 1,024 bytes (in 8-byte increments)
8
16
32
64
128
256
512
1024

DONE!!!!!!!! You can also use VirtualAlloc() / VirtualFree() operations directly if needed for large block operations. */

// Just for testing, implement custom console writer
basic_ostream<wchar_t>& operator<<(basic_ostream<wchar_t>& os, const wtxt& t)
{
    os << (const wchar_t*)t;
    return os;
} // May be usefull for custom printer to stop consol output breaking up on chars > 255
//wchar_t *t = (wchar_t *)buff - 1;
//wchar_t *te = (wchar_t *)buff + s/2;
//while(++t != te)
//{
//	if(*t > 0xFF)
//	{
//		*t = '@'; // Stops console output from breaking up
//	}
//}

inline basic_ostream<wchar_t>& P(basic_ostream<wchar_t>& os)
{
	return os << gre << L" PASS!" << def;
}

inline basic_ostream<wchar_t>& F(basic_ostream<wchar_t>& os)
{
	return os << red << L" FAIL!" << def;
}

void buff_worker(wchar_t *b, ui64 s)
{
	const wchar_t *msg = L"BUFF TEST PASSED!"; // THIS FUNCTION FUKZ UP AND OVERREADS .DATA SEGMENT!!!!!!!
	for(ui64 i = 0; i < s; ++i)
	{
		b[i] = msg[i];
	}
}

void dispPos(ui64 pos, const wtxt& s)
{	
	if(pos == NFND)
	{
		wcout << L"NOT FOUND!" << L" -> |" << s << L"|" << endl;
		return;
	}
	
	for(ui64 i = 0; i < pos; ++i)
	{
		wcout << '-';
		if(i + 1 == pos)
		{
			break;
		}
	}
	wcout << '^';
	wcout << ' ' << pos << L" -> |" << s << L"|" << endl;
}

void t2ii2tTest()
{
	fkcursor();
	wcout << L"T2II2T PROGRESS: " << endl;
	int bars = 0;
	
	bool epic_fail = false;
	for(ui64 i = 0; i < 5000000000; i += 8888)
	{
		int perc = int((float)i / 5000000000.0f * 32.0f);
		
		if(perc > bars)
		{
			bars = perc;
			
			int j = bars;
			int k = 31 - j;
			wcout << '\r';
			wcout << L"[";
			while(--j >= 0)
			{
				wcout << '|';
			}
			while(--k >= 0)
			{
				wcout << ' ';
			}
			wcout << L"]";
		}
		
		// TEST NEGATIVE!!!
		
		i32 sx32 = (i32)i;
		ui32 x32 = (ui32)i;
		ui16 x16 = (ui16)i;
		ui8 x8 = (ui8)i;
		
		wtxt dec = i2wt(i);
		wtxt sdec = i2wt(sx32);
		wtxt h64 = i2wh(i);
		wtxt h32 = i2wh(x32);
		wtxt h16 = i2wh(x16);
		wtxt h8 = i2wh(x8);
		
		ui64 rdec = t2i(dec);
		i32 rsdec = (i32)t2i(sdec);
		ui64 rh64 = h2i(h64);
		ui64 rh32 = h2i(h32);
		ui64 rh16 = h2i(h16);
		ui64 rh8 = h2i(h8);
		
		if(rdec != i)
		{
			epic_fail = true;
			wcout << red << L"T2II2T EPIC FAIL! rdec:  " << def << std::dec << rdec << L" wtxt: "
				<< dec << L" i:    " << i << endl;
		}
		
		if(rsdec != sx32)
		{
			epic_fail = true;
			wcout << red << L"T2II2T EPIC FAIL! rsdec: " << def << std::dec << rsdec << L" wtxt: "
				<< sdec << L" sx32: " << sx32 << endl;
		}
		
		if(rh64 != i)
		{
			epic_fail = true;
			wcout << red << L"T2II2T EPIC FAIL! rh64:  " << def << hex << uppercase << rh64 << L" wtxt: "
				<< h64 << L" i:    " << i << endl;
		}
		
		if(rh32 != x32)
		{
			epic_fail = true;
			wcout << red << L"T2II2T EPIC FAIL! rh32:  " << def << hex << uppercase << rh32 << L" wtxt: "
				<< h32 << L" x32:  " << x32 << endl;
		}
		
		if(rh16 != x16)
		{
			epic_fail = true;
			wcout << red << L"T2II2T EPIC FAIL! rh16:  " << def << hex << uppercase << rh16 << L" wtxt: "
				<< h16 << L" x16:  " << x16 << endl;
		}
		
		if(rh8 != x8)
		{
			epic_fail = true;
			wcout << red << L"T2II2T EPIC FAIL! rh8:   " << def << hex << uppercase << rh8 << L" wtxt: "
				<< h8 << L" x8:  " << x8 << endl;
		}
	}
	
	if(!epic_fail)
	{
		wcout << gre << L"\nT2II2T PASSED!" << def << endl;
	}
	okcursor();
}

int wmain(/* int argc, wchar_t**argv */)
{
#ifndef BASIC_TESTZ
#ifdef BUFFER_MODE
	wtxt conbuff = 20;
	ReadConsoleW(
		GetStdHandle(STD_INPUT_HANDLE),
		conbuff,
		(DWORD)!conbuff,
		*conbuff,
		NULL);
		
	wcout << "|" << conbuff << "| S: " << ~conbuff << " | TS: " << !conbuff << endl;
	wcout << "|" << (conbuff += L"___APPENDED_TO_TEST_TEXT!"), cout << "| S: " << ~conbuff
		<< " | TS: " << !conbuff << endl; // I guess coz of optimisations here old sizes are reported
	wcout << "| S: " << ~conbuff	<< " | TS: " << !conbuff << endl; // Here sizes are correct
	
	/* REASON:
	Order of evaluation of any part of any expression, including order of evaluation of function arguments is
	unspecified (with some exceptions listed below). The compiler can evaluate operands and other subexpressions
	in any order, and may choose another order when the same expression is evaluated again.
	
	There is no concept of left-to-right or right-to-left evaluation in C++. This is not to be confused with
	left-to-right and right-to-left associativity of operators: the expression a() + b() + c() is parsed as
	(a() + b()) + c() due to left-to-right associativity of operator+, but c() may be evaluated first, last, or
	between a() or b() at run time 
	
	Bjarne Stroustrup also says it explicitly in "The C++ Programming Language" 3rd edition section 6.2.2,
	with some reasoning:
    Better code can be generated in the absence of restrictions on expression evaluation order */
	
	pause
#endif
	
	wtxt t(L"Hello Baka");
	wtxt g = L"Whale Hallo Dere";
	//////////////////////////////////////////////////////////////////////////
	wcout << t << L" S: " << dec << ~t << L" EXPECT S: " << wcslen(t) << endl;
	wcout << g << L" S: " << dec << ~g << L" EXPECT S: " << wcslen(g) << endl;
	//////////////////////////////////////////////////////////////////////////
	wtxt ch = '$';
	wcout << ch << endl;
	//////////////////////////////////////////////////////////////////////////
	wtxt buff(20);
	buff_worker(buff, !buff);
	wcout << buff << endl;
	//////////////////////////////////////////////////////////////////////////
	t = g;
	wcout << L"NEW t: |" << t << L"| S: " << dec << ~t << L" EXPECT S: " << wcslen(t) << endl;
	t = wtxt(L"I'm tmp floop!");
	wcout << L"NEW t: |" << t << L"| S: " << dec << ~t << L" EXPECT S: " << wcslen(t) << endl;
	t = L"NEW wchar_t literal ready for duty!";
	wcout << L"NEW t: |" << t << L"| S: " << dec << ~t << L" EXPECT S: " << wcslen(t) << endl;
	t = '#';
	wcout << L"NEW t: |" << t << L"| S: " << dec << ~t << L" EXPECT S: " << wcslen(t) << endl;
	t = -42;
	wcout << L"NEW t: |" << t << L"| S: " << dec << ~t << L" EXPECT S: " << wcslen(t) << endl;
	t = 42;
	wcout << L"NEW t: |" << t << L"| S: " << dec << ~t << L" EXPECT S: " << wcslen(t) << endl;
	//////////////////////////////////////////////////////////////////////////
	
	wtxt tchar0 = '-';
	wtxt tchar1 = L'-';
	wcout << "tchar0 S: " << ~tchar0 << endl;
	wcout << "tchar0 TS:" <<  !tchar0 << endl;
	wcout << "|" << tchar0 << "|" << (~tchar0 == 1 && !tchar0 == 4 && tchar0 == '-' && tchar0 == L'-'
		? P : F) << endl;
	wcout << "tchar0 S: " << ~tchar1 << endl;
	wcout << "tchar0 TS:" <<  !tchar1 << endl;
	wcout << "|" << tchar1 << "|" << (~tchar1 == 1 && !tchar1 == 4 && tchar1 == '-' && tchar1 == L'-'
		? P : F) << endl;
	
	//////////////////////////////////////////////////////////////////////////
	for(ui64 i = 0; i < !t; ++i)
	{
		//wcout << L"t[" << i << L"]: " << hex << uppercase << +t[0] << endl;
		wcout << /* (wchar_t *) */(t[i]) << '_';
	}
	wcout << endl;
	wcout << L"t[0]: " << hex << uppercase << +t[0] << dec << L" S: " << ~t << L" TS: " << !t << endl;
	// _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ msvc
	//__________________________________________ gcc
	
	wchar_t a[42];
	memset(a, 0x0, 84);
	for(ui64 i = 0; i < 42; ++i)
	{
		//wcout << L"t[" << i << L"]: " << hex << uppercase << +t[0] << endl;
		wcout << wchar_t(a[i]) << '_';
	}
	wcout << endl;
	
	for(ui64 i = 0; i < ~g; ++i)
	{
		wcout << g[i] << '_';
	}
	wcout << endl;
	//////////////////////////////////////////////////////////////////////////
	wtxt t0, t1;
	t0 = L"Baka Part 1";
	t1 = L"-Baka Part 2";
	t0 += t1;
	wcout << L"t0: " << t0 << L" S: " << dec << ~t0 << L" EXPECT S: " << wcslen(t0) << endl;
	//////////////////////////////////////////////////////////////////////////
	t0 += L"-Baka Part 3";
	wcout << L"t0: " << t0 << L" S: " << dec << ~t0 << L" EXPECT S: " << wcslen(t0) << endl;
	t0 += '*';
	wcout << L"NEW t: " << t0 << L" S: " << dec << ~t0 << L" EXPECT S: " << wcslen(t0) << endl;
	//////////////////////////////////////////////////////////////////////////
	
#ifndef COMARIZON
	t0 = L"-comp", t1 = L"-comp";
	wtxt t2 = L"-compper", t3 = L"-co$p", t4 = '$', t5, t6 = '-';
	
	wcout << "operator==(const wtxt& t0, const wtxt& t1)--------------------" << endl;
	wcout << "|-comp| == |-comp| ------>" << (t0 == t1 ? P : F) << endl;
	wcout << "|-comp| == |-compper| --->" << (t0 == t2 ? F : P) << endl;
	wcout << "|-comp| == |-co$p| ------>" << (t0 == t3 ? F : P) << endl;
	
	wcout << "operator!=(const wtxt& t0, const wtxt& t1)--------------------" << endl;
	wcout << "|-comp| != |-comp| ------>" << (t0 != t1 ? F : P) << endl;
	wcout << "|-comp| != |-compper| --->" << (t0 != t2 ? P : F) << endl;
	wcout << "|-comp| != |-co$p| ------>" << (t0 != t3 ? P : F) << endl;
	
	wcout << "operator==(const wtxt& t, const wchar_t *cs)------------------" << endl;
	wcout << "|-comp| == |-comp| ------>" << (t0 == L"-comp" ? P : F) << endl;
	wcout << "|-comp| == |-compper| --->" << (t0 == L"-compper" ? F : P) << endl;
	wcout << "|-comp| == |-co$p| ------>" << (t0 == L"-co$p" ? F : P) << endl;
	
	wcout << "operator!=(const wtxt& t, const wchar_t *cs)------------------" << endl;
	wcout << "|-comp| != |-comp| ------>" << (t0 != L"-comp" ? F : P) << endl;
	wcout << "|-comp| != |-compper| --->" << (t0 != L"-compper" ? P : F) << endl;
	wcout << "|-comp| != |-co$p| ------>" << (t0 != L"-co$p" ? P : F) << endl;
	
	wcout << "operator==(const wchar_t *cs, const wtxt& t)------------------" << endl;
	wcout << "|-comp| == |-comp| ------>" << (L"-comp" == t0 ? P : F) << endl;
	wcout << "|-comp| == |-compper| --->" << (L"-compper" == t0 ? F : P) << endl;
	wcout << "|-comp| == |-co$p| ------>" << (L"-co$p" == t0 ? F : P) << endl;
	
	wcout << "operator!=(const wchar_t *cs, const wtxt& t)------------------" << endl;
	wcout << "|-comp| != |-comp| ------>" << (L"-comp" != t0 ? F : P) << endl;
	wcout << "|-comp| != |-compper| --->" << (L"-compper" != t0 ? P : F) << endl;
	wcout << "|-comp| != |-co$p| ------>" << (L"-co$p" != t0 ? P : F) << endl;
	
	wcout << "operator==(const wtxt& t, wchar_t c)--------------------------" << endl;
	wcout << "|-| == |-| -------------->" << (t6 == '-' ? P : F) << endl;
	wcout << "|-comp| == |c| ---------->" << (t0 == 'c' ? F : P) << endl;
	wcout << "|$| == |-| -------------->" << (t4 == '-' ? F : P) << endl;
	
	wcout << "operator!=(const wtxt& t, wchar_t c)--------------------------" << endl;
	wcout << "|-| != |-| -------------->" << (t6 != '-' ? F : P) << endl;
	wcout << "|-comp| != |c| ---------->" << (t0 != 'c' ? P : F) << endl;
	wcout << "|$| != |-| -------------->" << (t4 != '-' ? P : F) << endl;
	
	wcout << "operator==(wchar_t c, const wtxt& t)--------------------------" << endl;
	wcout << "|-| == |-| -------------->" << ('-' == t6 ? P : F) << endl;
	wcout << "|-comp| == |c| ---------->" << ('c' == t0 ? F : P) << endl;
	wcout << "|$| == |-| -------------->" << ('-' == t4 ? F : P) << endl;
	
	wcout << "operator!=(wchar_t c, const wtxt& t)--------------------------" << endl;
	wcout << "|-| != |-| -------------->" << ('-' != t6 ? F : P) << endl;
	wcout << "|-comp| != |c| ---------->" << ('c' != t0 ? P : F) << endl;
	wcout << "|$| != |-| -------------->" << ('-' != t4 ? P : F) << endl;
	
	wcout << "operator==(const wtxt& t, void (*empty_func)(void))-----------" << endl;
	wcout << "|-comp| == || ----------->" << (t0 == empty ? F : P) << endl;
	wcout << "|| == || ---------------->" << (t5 == empty ? P : F) << endl;
	
	wcout << "operator!=(const wtxt& t, void (*empty_func)(void))-----------" << endl;
	wcout << "|-comp| != || ----------->" << (t0 != empty ? P : F) << endl;
	wcout << "|| != || ---------------->" << (t5 != empty ? F : P) << endl;
	
	wcout << "operator==(void (*empty_func)(void), const wtxt& t)-----------" << endl;
	wcout << "|-comp| == || ----------->" << (empty == t0 ? F : P) << endl;
	wcout << "|| == || ---------------->" << (empty == t5 ? P : F) << endl;
	
	wcout << "operator!=(void (*empty_func)(void), const wtxt& t)-----------" << endl;
	wcout << "|-comp| != || ----------->" << (empty != t0 ? P : F) << endl;
	wcout << "|| != || ---------------->" << (empty != t5 ? F : P) << endl;
#endif

	//////////////////////////////////////////////////////////////////////////
	wcout << L"Baka + ' ' + Mono: |" << (wtxt(L"Baka") + ' ' + L"Mono") << '|' << endl;
	//////////////////////////////////////////////////////////////////////////
	
	const wchar_t *tofind = L"This_is_tesuto_searching_!baka_this_T_tesutoraptor_text_baka!";
	wtxt fthis = L"This";
	wtxt ftesuto = L"tesuto";
	wtxt fbaka = L"baka!";
	wtxt fnone = L"NONSENSE";
	
	wcout << dec << L"\nSEARCHING FROM BEG >>>>>>>>>>>>>>>>>>\n";
	
	wtxt fnd_tst = tofind;
	wcout << tofind << endl;
	dispPos(L"This" >> fnd_tst, wtxt(L"This"));
	wcout << tofind << endl;
	dispPos(L"tesuto" >> fnd_tst, wtxt(L"tesuto"));
	wcout << tofind << endl;
	dispPos(L"baka!" >> fnd_tst, wtxt(L"baka!"));
	wcout << tofind << endl;
	dispPos(fthis >> fnd_tst, fthis);
	wcout << tofind << endl;
	dispPos(ftesuto >> fnd_tst, ftesuto);
	wcout << tofind << endl;
	dispPos(fbaka >> fnd_tst, wtxt(fbaka));
	wcout << tofind << endl;
	dispPos(L"NONSENSE" >> fnd_tst, wtxt(L"NONSENSE"));
	wcout << tofind << endl;
	dispPos(fnone >> fnd_tst, wtxt(fnone));
	wcout << tofind << endl;
	dispPos('T' >> fnd_tst, wtxt('T'));
	wcout << tofind << endl;
	dispPos('r' >> fnd_tst, wtxt('r' ));
	wcout << tofind << endl;
	dispPos('!' >> fnd_tst, wtxt('!'));
	wcout << tofind << endl;
	dispPos('$' >> fnd_tst, wtxt('$'));
	
	wcout << L"\nSEARCHING FROM end <<<<<<<<<<<<<<<<<<\n";
	
	wcout << tofind << endl;
	dispPos(L"This" << fnd_tst, wtxt(L"This"));
	wcout << tofind << endl;
	dispPos(L"tesuto" << fnd_tst, wtxt(L"tesuto"));
	wcout << tofind << endl;
	dispPos(L"baka!" << fnd_tst, wtxt(L"baka!"));
	wcout << tofind << endl;
	dispPos(fthis << fnd_tst, wtxt(fthis));
	wcout << tofind << endl;
	dispPos(ftesuto << fnd_tst, ftesuto);
	wcout << tofind << endl;
	dispPos(fbaka << fnd_tst, fbaka);
	wcout << tofind << endl;
	dispPos(L"NONSENSE" << fnd_tst, wtxt(L"NONSENSE"));
	wcout << tofind << endl;
	dispPos(fnone << fnd_tst, fnone);
	wcout << tofind << endl;
	dispPos('T' << fnd_tst, wtxt('T'));
	wcout << tofind << endl;
	dispPos('r' << fnd_tst, wtxt('r'));
	wcout << tofind << endl;
	dispPos('!' << fnd_tst, wtxt('!'));
	wcout << tofind << endl;
	dispPos('$' << fnd_tst, wtxt('$'));
	
	wcout << L"\nSEARCHING FROM BEG >>>>>>>>>>>>>>>>>>\n";
	
	wcout << tofind << endl;
	dispPos(txtf(fnd_tst, 0, L"tesuto"), wtxt(L"tesuto"));
	wcout << tofind << endl;
	dispPos(txtf(fnd_tst, 0, ftesuto), wtxt(ftesuto));
	wcout << tofind << endl;
	dispPos(txtf(fnd_tst, 0, 'r'), wtxt('r'));
	wcout << tofind << endl;
	dispPos(txtf(fnd_tst, 24, L"tesuto"), wtxt(L"tesuto"));
	wcout << tofind << endl;
	dispPos(txtf(fnd_tst, 24, ftesuto), ftesuto);
	wcout << tofind << endl;
	dispPos(txtf(fnd_tst, 0x2C, 'r'), wtxt('r'));
	wcout << L"\nSEARCHING FROM end <<<<<<<<<<<<<<<<<<\n";
	wcout << tofind << endl;
	dispPos(txtfe(fnd_tst, 0, L"tesuto"), wtxt(L"tesuto"));
	wcout << tofind << endl;
	dispPos(txtfe(fnd_tst, 0, ftesuto), wtxt(ftesuto));
	wcout << tofind << endl;
	dispPos(txtfe(fnd_tst, 0, 'r'), wtxt('r'));
	wcout << tofind << endl;
	dispPos(txtfe(fnd_tst, 24, L"tesuto"), wtxt(L"tesuto"));
	wcout << tofind << endl;
	dispPos(txtfe(fnd_tst, 24, ftesuto), ftesuto);
	wcout << tofind << endl;
	dispPos(txtfe(fnd_tst, 24, 'r'), wtxt('r'));
	
	wcout << endl;
	
	const wchar_t *toins = L"This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!";
	wtxt toins_txt = toins;
	const wchar_t *tie = toins + ~toins_txt;
	wtxt ins = L"<|||>";
	
	const wchar_t *ti = toins - 1;
	while(++ti <= tie)
	{
		wtxt ins_tst = toins;
		txti(ins_tst, ui64(ti - toins), ins);
		wcout << ins_tst << endl;
	}
	wcout << endl;
	ti = toins - 1;
	while(++ti <= tie)
	{
		wtxt ins_tst = toins;
		txti(ins_tst, ui64(ti - toins), L"<|||>");
		wcout << ins_tst << endl;
	}
	wcout << endl;
	ti = toins - 1;
	while(++ti <= tie)
	{
		wtxt ins_tst = toins;
		txti(ins_tst, ui64(ti - toins), '$');
		wcout << ins_tst << endl;
	}
	wcout << endl;
	
	///////////////////////////////////////////////////////////////////////
	
	ti = toins - 1;
	while(*(++ti) != 0)
	{
		wtxt ins_tst = toins;
		txto(ins_tst, ui64(ti - toins), ins);
		wcout << ins_tst << endl;
	}
	wcout << endl;
	ti = toins - 1;
	while(*(++ti) != 0)
	{
		wtxt ins_tst = toins;
		txto(ins_tst, ui64(ti - toins), L"<|||>");
		wcout << ins_tst << endl;
	}
	wcout << endl;
	ti = toins - 1;
	while(*(++ti) != 0)
	{
		wtxt ins_tst = toins;
		txto(ins_tst, ui64(ti - toins), '$');
		wcout << ins_tst << endl;
	}
	
	///////////////////////////////////////////////////////////////////////

	wtxt rep_tst = L"0123456789_____0123456789";
	wtxt rep_txt = L"|REPLACED|";
	wtxt rep_empty;
	
	wcout << L"    " << rep_tst << L" OGIRG" << endl << endl;
	
	wtxt rep = rep_tst;
	txtr(rep, 0, 3, rep_txt);
	wcout  << __LINE__ << L" " << rep << (rep == L"|REPLACED|3456789_____0123456789" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 0, 3, L"|REPLACED|");
	wcout  << __LINE__ << L" " << rep << (rep == L"|REPLACED|3456789_____0123456789" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 0, 3, '$');
	wcout  << __LINE__ << L" " << rep << (rep == L"$3456789_____0123456789" ? P : F) << endl << endl;
	rep = rep_tst;
	
	txtr(rep, 0, RALL, rep_txt);
	wcout  << __LINE__ << L" " << rep << (rep == L"|REPLACED|" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 0, RALL, L"|REPLACED|");
	wcout  << __LINE__ << L" " << rep << (rep == L"|REPLACED|" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 0, RALL, '$');
	wcout  << __LINE__ << L" " << rep << (rep == L"$" ? P : F) << endl << endl;
	rep = rep_tst;

	txtr(rep, 10, 5, rep_txt);
	wcout  << __LINE__ << L" " << rep << (rep == L"0123456789|REPLACED|0123456789" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 10, 5, L"|REPLACED|");
	wcout  << __LINE__ << L" " << rep << (rep == L"0123456789|REPLACED|0123456789" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 10, 5, '$');
	wcout  << __LINE__ << L" " << rep << (rep == L"0123456789$0123456789" ? P : F) << endl << endl;
	rep = rep_tst;

	txtr(rep, 10, 0, rep_txt);
	wcout  << __LINE__ << L" " << rep << (rep == L"0123456789|REPLACED|_____0123456789" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 10, 0, L"|REPLACED|");
	wcout  << __LINE__ << L" " << rep << (rep == L"0123456789|REPLACED|_____0123456789" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 10, 0, '$');
	wcout  << __LINE__ << L" " << rep << (rep == L"0123456789$_____0123456789" ? P : F) << endl << endl;
	rep = rep_tst;

	txtr(rep, 10, RALL, rep_txt);
	wcout  << __LINE__ << L" " << rep << (rep == L"0123456789|REPLACED|" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 10, RALL, L"|REPLACED|");
	wcout  << __LINE__ << L" " << rep << (rep == L"0123456789|REPLACED|" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 10, RALL, '$');
	wcout  << __LINE__ << L" " << rep << (rep == L"0123456789$" ? P : F) << endl << endl;
	rep = rep_tst;

	txtr(rep, ~rep, 0, rep_txt);
	wcout  << __LINE__ << L" " << rep << (rep == L"0123456789_____0123456789|REPLACED|" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, ~rep, 0, L"|REPLACED|");
	wcout  << __LINE__ << L" " << rep << (rep == L"0123456789_____0123456789|REPLACED|" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, ~rep, 0, '$');
	wcout  << __LINE__ << L" " << rep << (rep == L"0123456789_____0123456789$" ? P : F) << endl << endl;
	rep = rep_tst;

	txtr(rep, ~rep-3, 6969, rep_txt);
	wcout  << __LINE__ << L" " << rep << (rep == L"0123456789_____0123456|REPLACED|" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, ~rep-3, 6969, L"|REPLACED|");
	wcout  << __LINE__ << L" " << rep << (rep == L"0123456789_____0123456|REPLACED|" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, ~rep-3, 6969, '$');
	wcout  << __LINE__ << L" " << rep << (rep == L"0123456789_____0123456$" ? P : F) << endl << endl;
	rep = rep_tst;
	
	txtr(rep, 10, 5, rep_empty);
	wcout << __LINE__ << L" " << rep << (rep == L"01234567890123456789" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 10, 5, L"");
	wcout << __LINE__ << L" " << rep << (rep == L"01234567890123456789" ? P : F) << endl << endl;
	rep = rep_tst;
	// Replacing with \0 is mistake, as size wont get updated, unless used with trimm operator!
	// Use txtd() for safe removal of text parts!
	
	txtd(rep, 10, 5);
	wcout << __LINE__ << L" " << rep << (rep == L"01234567890123456789" ? P : F) << endl;
	rep = rep_tst;
	txtd(rep, 3, DALL);
	wcout << __LINE__ << L" " << rep << (rep == L"012" ? P : F) << endl;
	rep = rep_tst;
	txtd(rep, ~rep-1, 1);
	wcout << __LINE__ << L" " << rep << (rep == L"0123456789_____012345678" ? P : F) << endl;
	rep = rep_tst;
	
#endif
	
	t2ii2tTest();
	
	// EXCEPT TESTS
	/* TRY
	t2i(wtxt(L"20000000000000000000"));
	EXCEPT
	
	TRY
	t2i(wtxt(L"20000000000000000000111"));
	EXCEPT
	
	TRY
	t2i(wtxt(L"444222FFF111999"));
	EXCEPT
	
	TRY
	h2i(wtxt(L"20000000000000000000111FFFF"));
	EXCEPT
	
	TRY
	h2i(wtxt(L"FFaa4g44444"));
	EXCEPT
	
	wtxt ins_except_tst = L"123456789";
	TRY
	txti(ins_except_tst, 18, L"dis gonna make big badabooom!");
	EXCEPT
	
	TRY
	txto(ins_except_tst, 18, L"dis gonna make big badabooom!");
	EXCEPT */
	
#ifndef PROFILE_VS_STD
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	const wchar_t *lorem = L"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque ut suscipit mi, vel condimentum metus. Etiam vestibulum dapibus fermentum. Vivamus in maximus velit. Donec tempor turpis justo. Duis luctus id risus vitae accumsan. Duis volutpat tincidunt felis, non ullamcorper augue cursus quis. Morbi maximus, odio at pellentesque eleifend, erat magna accumsan risus, sollicitudin aliquet est nulla eu augue. Donec lectus nulla, volutpat eget diam at, egestas sodales neque. Sed interdum libero eget semper posuere. Interdum et malesuada fames ac ante ipsum primis in faucibus. In odio urna, ultrices in commodo in, sagittis fringilla elit. Sed non luctus ligula."

	L"Nullam condimentum vitae turpis non tincidunt. Suspendisse vulputate leo ut pharetra viverra. Fusce varius purus sed quam vestibulum, non ullamcorper odio volutpat. Curabitur interdum tincidunt magna eget aliquet. Aliquam sit amet leo quis tellus eleifend tristique. Donec non risus massa. Nullam tincidunt sollicitudin sodales."

	L"Cras rhoncus malesuada ligula, vitae sodales metus luctus sit amet. Interdum et malesuada fames ac ante ipsum primis in faucibus. Mauris eleifend neque vitae tortor semper condimentum. Phasellus aliquet neque nisl, ut auctor dui varius ac. Cras ut metus neque. Nunc consequat, leo ut lacinia venenatis, nisi orci hendrerit ex, ut lacinia sapien augue quis magna. Proin scelerisque at ex eu condimentum. Quisque ac condimentum quam. Vestibulum a pulvinar dolor. Nunc sodales lacinia varius. Cras luctus leo dui, quis lacinia quam ornare tempus. Maecenas magna libero, scelerisque quis pellentesque eu, efficitur sed magna. Mauris vestibulum lobortis sagittis. Vivamus mollis lacus ut risus vehicula pellentesque. Suspendisse a blandit augue.HA! DIDNT EXPECT DA !BAKA! HERE?!";
	
	const wchar_t *lorem_sm = L"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque ut suscipit mi, vel condimentum metus. Etiam vestibulum dapibus fermentum. Vivamus in maximus velit. Donec tempor turpis justo. Duis luctus id risus vitae accumsan. Duis volutpat tincidunt felis, non ullamcorper augue cursus quis. Morbi maximus, odio at pellentesque eleifend, erat magna accumsan risus, sollicitudin aliquet est nulla eu augue.";
	
	
	wcout << endl << L"!THE ULTIMATE SHOWDOWN!" << endl;
	wcout << L"SIZEOF(STDBS): " << sizeof(std::wstring) << endl;
	wcout << L"SIZEOF(WTXT):   " << sizeof(wtxt) << endl << endl;
	
	
	fkcursor();
	wcout << L"ALLOCIN BIG STR..." << endl;
	
	SW0SET //---------------------------------------
	for(int i = 0; i < 42000; ++i)
	{
		std::wstring s0 = lorem;
		std::wstring s1 = lorem;
		std::wstring s2 = lorem;
		std::wstring s3 = lorem;
	}
	SW0STOP //++++++++++++++++++++++++++++++++++++++
	SW1SET //---------------------------------------
	for(int i = 0; i < 42000; ++i)
	{
		wtxt s0 = lorem;
		wtxt s1 = lorem;
		wtxt s2 = lorem;
		wtxt s3 = lorem;
	}
	SW1STOP //++++++++++++++++++++++++++++++++++++++

	wcout << L"ALLOCIN CHARS..." << endl;
	
	SW2SET //---------------------------------------
	for(int i = 0; i < 420000; ++i)
	{
		std::wstring s0 = L"$";
		std::wstring s1 = L"&";
		std::wstring s2 = L"*";
		std::wstring s3 = L"#";
	}
	SW2STOP //++++++++++++++++++++++++++++++++++++++
	SW3SET //---------------------------------------
	for(int i = 0; i < 420000; ++i)
	{
		wtxt s0 = '$';
		wtxt s1 = '&';
		wtxt s2 = '*';
		wtxt s3 = '#';
	}
	SW3STOP //++++++++++++++++++++++++++++++++++++++
	
	wcout << L"ARRAY ACCESS..." << endl;
	
	std::wstring str_lorem = lorem;
	ui64 lorems = str_lorem.size();
	SW4SET //---------------------------------------
	for(ui64 k = 0; k < 42000; ++k)
	{
		for(ui64 i = 0; i < lorems; ++i)
		{
			str_lorem[i] = '$';
		}
	}
	SW4STOP //++++++++++++++++++++++++++++++++++++++
	wtxt txt_lorem = lorem;
	SW5SET //---------------------------------------
	for(ui64 k = 0; k < 42000; ++k)
	{
		for(ui64 i = 0; i < lorems; ++i)
		{
			txt_lorem[i] = '$';
		}
	}
	SW5STOP //++++++++++++++++++++++++++++++++++++++
	
	wcout << L"APPENDING STR..." << endl;
	
	str_lorem = lorem_sm;
	SW6SET //---------------------------------------
	for(int i = 0; i < 42000; ++i)
	{
		str_lorem += lorem_sm;
	}
	SW6STOP //++++++++++++++++++++++++++++++++++++++
	txt_lorem = lorem_sm;
	SW7SET //---------------------------------------
	for(int i = 0; i < 42000; ++i)
	{
		txt_lorem += lorem_sm;
	}
	SW7STOP //++++++++++++++++++++++++++++++++++++++
	
	wcout << L"APPENDING CHARS..." << endl; // TEST WITH NEW SMOL wstring!!!! INSTED OF REUSING GIANT!!
	
	str_lorem = lorem_sm;
	SWESET //---------------------------------------
	for(int i = 0; i < 420000; ++i)
	{
		str_lorem += '$';
	}
	SWESTOP //++++++++++++++++++++++++++++++++++++++
	txt_lorem = lorem_sm;
	SWFSET //---------------------------------------
	for(int i = 0; i < 420000; ++i)
	{
		txt_lorem += '$';
	}
	SWFSTOP //++++++++++++++++++++++++++++++++++++++
	
	wcout << L"FINDING..." << endl;
	
	const wchar_t *fnd_str = L"HA! DIDNT EXPECT DA !BAKA! HERE?!";
	ui64 res = 0;
	str_lorem = lorem;
	SW8SET //---------------------------------------
	for(int i = 0; i < 42000; ++i)
	{
		res = str_lorem.find(fnd_str + i % 30);
	}
	SW8STOP //++++++++++++++++++++++++++++++++++++++
	txt_lorem = lorem;
	SW9SET //---------------------------------------
	for(int i = 0; i < 42000; ++i)
	{
		res = fnd_str + i % 30 >> txt_lorem;
	}
	SW9STOP //++++++++++++++++++++++++++++++++++++++
	
	wcout << L"INSERTING..." << endl;
	
	str_lorem = lorem;
	SWASET //---------------------------------------
	for(int i = 0; i < 4200; ++i)
	{
		for(ui64 k = 0; k < lorems; k += 100)
		{
			str_lorem.insert(k, L"!BAKA!_!IS!_!!HERE?!");
		}
	}
	SWASTOP //++++++++++++++++++++++++++++++++++++++
	txt_lorem = lorem;
	SWBSET //---------------------------------------
	for(int i = 0; i < 4200; ++i)
	{
		for(ui64 k = 0; k < lorems; k += 100)
		{
			txti(txt_lorem, k, L"!BAKA!_!IS!_!!HERE?!");
		}
	}
	SWBSTOP //++++++++++++++++++++++++++++++++++++++
	
	wcout << L"OVERWRITING..." << endl;

	str_lorem = lorem;
	SWCSET //---------------------------------------
	for(int i = 0; i < 42000; ++i)
	{
		for(ui64 k = 0; k + 100 < lorems; k += 100)
		{
			str_lorem.replace(k, 20, L"!BAKA!_!IS!_!!HERE?!");
		}
	}
	SWCSTOP //++++++++++++++++++++++++++++++++++++++
	txt_lorem = lorem;
	SWDSET //---------------------------------------
	for(int i = 0; i < 42000; ++i)
	{
		for(ui64 k = 0; k + 100 < lorems; k += 100)
		{
			txto(txt_lorem, k, L"!BAKA!_!IS!_!!HERE?!");
		}
	}
	SWDSTOP //++++++++++++++++++++++++++++++++++++++
	
	wcout << L"COMPARISION..." << endl;
	
	str_lorem = lorem;
	SW10SET //---------------------------------------
	for(int i = 0; i < 42000; ++i)
	{
		#pragma warning( suppress : 4834 )
		str_lorem == lorem;
	}
	SW10STOP //++++++++++++++++++++++++++++++++++++++
	txt_lorem = lorem;
	SW11SET //---------------------------------------
	for(int i = 0; i < 42000; ++i)
	{
		#pragma warning( suppress : 4834 )
		txt_lorem == lorem;
	}
	SW11STOP //++++++++++++++++++++++++++++++++++++++
	
	wcout << L"INT TO TEXT..." << endl;
	
	ui64 num = 18000000042000000000;
	std::wstring str_num;
	SW12SET //---------------------------------------
	for(int i = 0; i < 420000; ++i)
	{
		str_num = to_wstring(num);
	}
	SW12STOP //++++++++++++++++++++++++++++++++++++++
	wtxt txt_num;
	SW13SET //---------------------------------------
	for(int i = 0; i < 420000; ++i)
	{
		txt_num = i2wt(num);
	}
	SW13STOP //++++++++++++++++++++++++++++++++++++++
	
	wcout << L"TEXT TO INT..." << endl;
	
	const wchar_t *num_str = L"18000000042000000000";
	str_num = num_str;
	SW14SET //---------------------------------------
	for(int i = 0; i < 420000; ++i)
	{
		#pragma warning( suppress : 4834 )
		stoull(str_num);
	}
	SW14STOP //++++++++++++++++++++++++++++++++++++++
	txt_num = num_str;
	SW15SET //---------------------------------------
	for(int i = 0; i < 420000; ++i)
	{
		t2i(txt_num);
	}
	SW15STOP //++++++++++++++++++++++++++++++++++++++
	
	wcout << L"INT TO HEX..." << endl;
	
	num = 0xBEEFFAAA42006934;
	SW16SET //---------------------------------------
	for(int i = 0; i < 42000; ++i)
	{
		wstringstream wss;
		wss << hex << uppercase << num;
		str_num = wss.str();
	}
	SW16STOP //++++++++++++++++++++++++++++++++++++++
	SW17SET //---------------------------------------
	for(int i = 0; i < 42000; ++i)
	{
		txt_num = i2wh(num);
	}
	SW17STOP //++++++++++++++++++++++++++++++++++++++
	
	wcout << L"HEX TO INT..." << endl;
	
	num_str = L"BEEFFAAA42006934";
	str_num = num_str;
	SW18SET //---------------------------------------
	for(int i = 0; i < 420000; ++i)
	{
		#pragma warning( suppress : 4834 )
		stoull(str_num, nullptr, 16);
	}
	SW18STOP //++++++++++++++++++++++++++++++++++++++
	txt_num = num_str;
	SW19SET //---------------------------------------
	for(int i = 0; i < 420000; ++i)
	{
		
		h2i(txt_num);
	}
	SW19STOP //++++++++++++++++++++++++++++++++++++++
	
#endif
	
#ifndef RESULTS

	wcout << L"           " << setw(16) << L"WSTD" << setw(28) << L"WTXT" << endl;
	wcout << L"ALLOC BIG STR:   ";
	SW0P
	swDiff(0x0, 0x1);
	SW1P
	wcout << endl;
	wcout << L"ALLOC CHARS:     ";
	SW2P
	swDiff(0x2, 0x3);
	SW3P
	wcout << endl;
	wcout << L"ARRAY ACCESS:    ";
	SW4P
	swDiff(0x4, 0x5);
	SW5P
	wcout << endl;
	wcout << L"APPENDING STR:   ";
	SW6P
	swDiff(0x6, 0x7);
	SW7P
	wcout << endl;
	wcout << L"APPENDING CHAR:  ";
	SWEP
	swDiff(0xE, 0xF);
	SWFP
	wcout << endl;
	wcout << L"FINDING:         ";
	SW8P
	swDiff(0x8, 0x9);
	SW9P
	wcout << endl;
	wcout << L"INSERTING:       ";
	SWAP
	swDiff(0xA, 0xB);
	SWBP
	wcout << endl;
	wcout << L"OVERWRITING:     ";
	SWCP
	swDiff(0xC, 0xD);
	SWDP
	wcout << endl;
	wcout << L"COMPARISION:     ";
	SW10P
	swDiff(0x10, 0x11);
	SW11P
	wcout << endl;
	wcout << L"INT TO TEXT:     ";
	SW12P
	swDiff(0x12, 0x13);
	SW13P
	wcout << endl;
	wcout << L"TEXT TO INT:     ";
	SW14P
	swDiff(0x14, 0x15);
	SW15P
	wcout << endl;
	wcout << L"INT TO HEX:      ";
	SW16P
	swDiff(0x16, 0x17);
	SW17P
	wcout << endl;
	wcout << L"HEX TO INT:      ";
	SW18P
	swDiff(0x18, 0x19);
	SW19P
	wcout << endl;
	
#endif

/* !THE ULTIMATE SHOWDOWN!
SIZEOF(STDBS): 32
SIZEOF(WTXT):  24

===================================================DEBUG=OFF==================================================
                       WSTD                        WTXT
ALLOC BIG STR:   209.731'100 ms      x4.28       897.919'000 ms  !!!!!!!!!!!!!
ALLOC CHARS:     94.72'700 ms        x2.75       258.233'600 ms  !!!!!!!!!!!!!
ARRAY ACCESS:    677.964'300 ms      x3.88       174.734'700 ms
APPENDING STR:   40.223'700 ms       x1.48       27.196'400 ms
APPENDING CHAR:  7.149'700 ms        x4.11       1.737'900 ms
FINDING:         228.798'100 ms      x2.22       103.231'400 ms
INSERTING:       5.53 s              x1.00       5.52 s
OVERWRITING:     27.257'000 ms       x1.81       15.32'900 ms
COMPARISION:     277.241'000 ms      x6.34       43.710'600 ms
INT TO TEXT:     298.460'700 ms      x3.62       82.533'400 ms
TEXT TO INT:     46.337'100 ms       x4.44       10.432'000 ms
INT TO HEX:      77.713'400 ms       x11.99      6.479'000 ms
HEX TO INT:      44.388'700 ms       x4.43       10.20'300 ms

===================================================DEBUG=ON===================================================
						WSTD                        WTXT
ALLOC BIG STR:   978.418'300 ms      x1.09       900.703'900 ms
ALLOC CHAR:      1.773 s             x1.91       3.384 s         !!!!!!!!!!!!!
ARRAY ACCESS:    654.806'800 ms      x3.76       174.93'300 ms
APPENDING STR:   62.347'100 ms       x1.52       41.8'200 ms
APPENDING CHAR:  7.132'800 ms        x4.12       1.732'600 ms
FINDING:         224.346'800 ms      x2.06       108.654'800 ms
INSERTING:       5.69 s              x1.01       5.20 s
OVERWRITING:     27.998'300 ms       x1.94       14.468'200 ms
COMPARISION:     276.163'600 ms      x6.33       43.612'600 ms
INT TO TEXT:     1.86 s              x3.34       325.10'000 ms
TEXT TO INT:     141.310'600 ms      x13.64      10.361'400 ms
INT TO HEX:      723.465'600 ms      x21.96      32.946'500 ms
HEX TO INT:      125.732'500 ms      x12.61      9.967'000 ms */
	
	pause
	
	return 0;
}

// DONE!!!!!! CREATE CUSTOM HEAP EXCLUSIVE FOR STRINGS EXCLUSIVE LOCK NO OTHER THREADZ CAN INTEFEARE IN STRIN OPERATIONS!
// Use of Lookaside lists. The heap data structure uses a fast cache for all free items of blocks sized between 8 and 1,024 bytes (in 8-byte increments)
// 8
// 16
// 32
// 64
// 128
// 256
// 512
// 1024

//You can also use VirtualAlloc() / VirtualFree() operations directly if needed for large block operations.