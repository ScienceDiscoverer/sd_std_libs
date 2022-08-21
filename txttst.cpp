// CONSOLE NOPT
// DSEH DBG
#include <txt>
#include <sddb>

#include <string> // Just for profiling test, otherwise, casual std bs!

// DONE TRIMM OPERATOR, MB -- WILL REMOVE EMPTY 0 CHARS FROM THE END OF BUFFER AND RECALC IT'S SIZE
// TODO t2i & i2t + hex
// TODO < > OPERATORS FOR SORTING STRINGZ SMART NUMERIC\LEXICONUMERIC MB TEST ON WIN SHELL
// TODO i2ts styling function that will produce styled numbers thousands/bytes separators no hex zero pad etc.
// EXAMPLE
// int digs = 0;
// do
// {
//	b[--c] = i % 10 | 0x30;
//	i /= 10;
//	
//	if(++digs % 3/*2fh*/ == 0)
//	{
//		b[--c] = 0x27;
//	}
// }
// while(i > 0);

// DONE!!!!!! CREATE CUSTOM HEAP EXCLUSIVE FOR STRINGS EXCLUSIVE LOCK NO OTHER THREADZ CAN INTEFEARE IN STRIN OPERATIONS!
// DONE!!!!!! Use of Lookaside lists. The heap data structure uses a fast cache for all free items of blocks sized between 8 and 1,024 bytes (in 8-byte increments)
// 8
// 16
// 32
// 64
// 128
// 256
// 512
// 1024

// DONE!!!!!!!! You can also use VirtualAlloc() / VirtualFree() operations directly if needed for large block operations.

inline ostream& P(ostream& os)
{
	return os << gre << " PASS!" << def;
}

inline ostream& F(ostream& os)
{
	return os << red << " FAIL!" << def;
}

void buff_worker(char *b, ui64 s)
{
	const char *msg = "BUFF TEST PASSED!"; // THIS FUNCTION FUKZ UP AND OVERREADS .DATA SEGMENT!!!!!!!
	for(ui64 i = 0; i < s; ++i)
	{
		b[i] = msg[i];
	}
}

void dispPos(ui64 pos, const txt& s)
{	
	if(pos == NFND)
	{
		cout << "NOT FOUND!" << " -> |" << s << "|" << endl;
		return;
	}
	
	for(ui64 i = 0; i < pos; ++i)
	{
		cout << '-';
		if(i + 1 == pos)
		{
			break;
		}
	}
	cout << '^';
	cout << ' ' << pos << " -> |" << s << "|" << endl;
}

void t2ii2tTest()
{
	fkcursor();
	cout << "T2II2T PROGRESS: " << endl;
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
			cout << '\r';
			cout << "[";
			while(--j >= 0)
			{
				cout << '|';
			}
			while(--k >= 0)
			{
				cout << ' ';
			}
			cout << "]";
		}
		
		// TEST NEGATIVE!!!
		
		i32 sx32 = (i32)i;
		ui32 x32 = (ui32)i;
		ui16 x16 = (ui16)i;
		ui8 x8 = (ui8)i;
		
		txt dec = i2t(i);
		txt sdec = i2t(sx32);
		txt h64 = i2h(i);
		txt h32 = i2h(x32);
		txt h16 = i2h(x16);
		txt h8 = i2h(x8);
		
		ui64 rdec = t2i(dec);
		i32 rsdec = (i32)t2i(sdec);
		ui64 rh64 = h2i(h64);
		ui64 rh32 = h2i(h32);
		ui64 rh16 = h2i(h16);
		ui64 rh8 = h2i(h8);
		
		if(rdec != i)
		{
			epic_fail = true;
			cout << red << "T2II2T EPIC FAIL! rdec:  " << def << std::dec << rdec << " txt: "
				<< dec << " i:    " << i << endl;
		}
		
		if(rsdec != sx32)
		{
			epic_fail = true;
			cout << red << "T2II2T EPIC FAIL! rsdec: " << def << std::dec << rsdec << " txt: "
				<< sdec << " sx32: " << sx32 << endl;
		}
		
		if(rh64 != i)
		{
			epic_fail = true;
			cout << red << "T2II2T EPIC FAIL! rh64:  " << def << hex << uppercase << rh64 << " txt: "
				<< h64 << " i:    " << i << endl;
		}
		
		if(rh32 != x32)
		{
			epic_fail = true;
			cout << red << "T2II2T EPIC FAIL! rh32:  " << def << hex << uppercase << rh32 << " txt: "
				<< h32 << " x32:  " << x32 << endl;
		}
		
		if(rh16 != x16)
		{
			epic_fail = true;
			cout << red << "T2II2T EPIC FAIL! rh16:  " << def << hex << uppercase << rh16 << " txt: "
				<< h16 << " x16:  " << x16 << endl;
		}
		
		if(rh8 != x8)
		{
			epic_fail = true;
			cout << red << "T2II2T EPIC FAIL! rh8:   " << def << hex << uppercase << rh8 << " txt: "
				<< h8 << " x8:  " << x8 << endl;
		}
	}
	
	if(!epic_fail)
	{
		cout << gre << "\nT2II2T PASSED!" << def << endl;
	}
	okcursor();
}

int wmain(/* int argc, wchar_t**argv */)
{
#ifndef BASIC_TESTZ
#ifdef BUFFER_MODE
	txt conbuff = 20;
	ReadConsoleA(
		GetStdHandle(STD_INPUT_HANDLE),
		conbuff,
		(DWORD)!conbuff,
		*conbuff,
		NULL);
		
	cout << "|" << conbuff << "| S: " << ~conbuff << " | TS: " << !conbuff << endl;
	cout << "|" << (conbuff += "___APPENDED_TO_TEST_TEXT!"), cout << "| S: " << ~conbuff
		<< " | TS: " << !conbuff << endl; // I guess coz of optimisations here old sizes are reported
	cout << "| S: " << ~conbuff	<< " | TS: " << !conbuff << endl; // Here sizes are correct
	
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
	
	txt t("Hello Baka");
	txt g = "Whale Hallo Dere";
	//////////////////////////////////////////////////////////////////////////
	cout << t << " S: " << dec << ~t << " EXPECT S: " << strlen(t) << endl;
	cout << g << " S: " << dec << ~g << " EXPECT S: " << strlen(g) << endl;
	//////////////////////////////////////////////////////////////////////////
	txt ch = '$';
	cout << ch << endl;
	//////////////////////////////////////////////////////////////////////////
	txt buff(20);
	buff_worker(buff, !buff);
	cout << buff << endl;
	//////////////////////////////////////////////////////////////////////////
	t = g;
	cout << "NEW t: |" << t << "| S: " << dec << ~t << " EXPECT S: " << strlen(t) << endl;
	t = txt("I'm tmp floop!");
	cout << "NEW t: |" << t << "| S: " << dec << ~t << " EXPECT S: " << strlen(t) << endl;
	t = "NEW char literal ready for duty!";
	cout << "NEW t: |" << t << "| S: " << dec << ~t << " EXPECT S: " << strlen(t) << endl;
	t = '#';
	cout << "NEW t: |" << t << "| S: " << dec << ~t << " EXPECT S: " << strlen(t) << endl;
	t = -42;
	cout << "NEW t: |" << t << "| S: " << dec << ~t << " EXPECT S: " << strlen(t) << endl;
	t = 42;
	cout << "NEW t: |" << t << "| S: " << dec << ~t << " EXPECT S: " << strlen(t) << endl;
	//////////////////////////////////////////////////////////////////////////
	for(ui64 i = 0; i < !t; ++i)
	{
		//cout << "t[" << i << "]: " << hex << uppercase << +t[0] << endl;
		cout << /* (char *) */(t[i]) << '_';
	}
	cout << endl;
	cout << "t[0]: " << hex << uppercase << +t[0] << dec << " S: " << ~t << " TS: " << !t << endl;
	// _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ msvc
	//__________________________________________ gcc
	
	char a[42];
	memset(a, 0x0, 42);
	for(ui64 i = 0; i < 42; ++i)
	{
		//cout << "t[" << i << "]: " << hex << uppercase << +t[0] << endl;
		cout << (a[i]) << '_';
	}
	cout << endl;
	
	for(ui64 i = 0; i < ~g; ++i)
	{
		cout << g[i] << '_';
	}
	cout << endl;
	//////////////////////////////////////////////////////////////////////////
	txt t0, t1;
	t0 = "Baka Part 1";
	t1 = "-Baka Part 2";
	t0 += t1;
	cout << "t0: " << t0 << " S: " << dec << ~t0 << " EXPECT S: " << strlen(t0) << endl;
	//////////////////////////////////////////////////////////////////////////
	t0 += "-Baka Part 3";
	cout << "t0: " << t0 << " S: " << dec << ~t0 << " EXPECT S: " << strlen(t0) << endl;
	t0 += '*';
	cout << "NEW t: " << t0 << " S: " << dec << ~t0 << " EXPECT S: " << strlen(t0) << endl;
	//////////////////////////////////////////////////////////////////////////

#ifndef COMARIZON
	t0 = "-comp", t1 = "-comp";
	txt t2 = "-compper", t3 = "-co$p", t4 = '$', t5, t6 = '-';
	
	cout << "operator==(const txt& t0, const txt& t1)-------------------" << endl;
	cout << "|-comp| == |-comp| ------>" << (t0 == t1 ? P : F) << endl;
	cout << "|-comp| == |-compper| --->" << (t0 == t2 ? F : P) << endl;
	cout << "|-comp| == |-co$p| ------>" << (t0 == t3 ? F : P) << endl;
	
	cout << "operator!=(const txt& t0, const txt& t1)-------------------" << endl;
	cout << "|-comp| != |-comp| ------>" << (t0 != t1 ? F : P) << endl;
	cout << "|-comp| != |-compper| --->" << (t0 != t2 ? P : F) << endl;
	cout << "|-comp| != |-co$p| ------>" << (t0 != t3 ? P : F) << endl;
	
	cout << "operator==(const txt& t, const char *cs)-------------------" << endl;
	cout << "|-comp| == |-comp| ------>" << (t0 == "-comp" ? P : F) << endl;
	cout << "|-comp| == |-compper| --->" << (t0 == "-compper" ? F : P) << endl;
	cout << "|-comp| == |-co$p| ------>" << (t0 == "-co$p" ? F : P) << endl;
	
	cout << "operator!=(const txt& t, const char *cs)-------------------" << endl;
	cout << "|-comp| != |-comp| ------>" << (t0 != "-comp" ? F : P) << endl;
	cout << "|-comp| != |-compper| --->" << (t0 != "-compper" ? P : F) << endl;
	cout << "|-comp| != |-co$p| ------>" << (t0 != "-co$p" ? P : F) << endl;
	
	cout << "operator==(const char *cs, const txt& t)-------------------" << endl;
	cout << "|-comp| == |-comp| ------>" << ("-comp" == t0 ? P : F) << endl;
	cout << "|-comp| == |-compper| --->" << ("-compper" == t0 ? F : P) << endl;
	cout << "|-comp| == |-co$p| ------>" << ("-co$p" == t0 ? F : P) << endl;
	
	cout << "operator!=(const char *cs, const txt& t)-------------------" << endl;
	cout << "|-comp| != |-comp| ------>" << ("-comp" != t0 ? F : P) << endl;
	cout << "|-comp| != |-compper| --->" << ("-compper" != t0 ? P : F) << endl;
	cout << "|-comp| != |-co$p| ------>" << ("-co$p" != t0 ? P : F) << endl;
	
	cout << "operator==(const txt& t, char c)---------------------------" << endl;
	cout << "|-| == |-| -------------->" << (t6 == '-' ? P : F) << endl;
	cout << "|-comp| == |c| ---------->" << (t0 == 'c' ? F : P) << endl;
	cout << "|$| == |-| -------------->" << (t4 == '-' ? F : P) << endl;
	
	cout << "operator!=(const txt& t, char c)---------------------------" << endl;
	cout << "|-| != |-| -------------->" << (t6 != '-' ? F : P) << endl;
	cout << "|-comp| != |c| ---------->" << (t0 != 'c' ? P : F) << endl;
	cout << "|$| != |-| -------------->" << (t4 != '-' ? P : F) << endl;
	
	cout << "operator==(char c, const txt& t)---------------------------" << endl;
	cout << "|-| == |-| -------------->" << ('-' == t6 ? P : F) << endl;
	cout << "|-comp| == |c| ---------->" << ('c' == t0 ? F : P) << endl;
	cout << "|$| == |-| -------------->" << ('-' == t4 ? F : P) << endl;
	
	cout << "operator!=(char c, const txt& t)---------------------------" << endl;
	cout << "|-| != |-| -------------->" << ('-' != t6 ? F : P) << endl;
	cout << "|-comp| != |c| ---------->" << ('c' != t0 ? P : F) << endl;
	cout << "|$| != |-| -------------->" << ('-' != t4 ? P : F) << endl;
	
	cout << "operator==(const txt& t, void (*empty_func)(void))---------" << endl;
	cout << "|-comp| == || ----------->" << (t0 == empty ? F : P) << endl;
	cout << "|| == || ---------------->" << (t5 == empty ? P : F) << endl;
	
	cout << "operator!=(const txt& t, void (*empty_func)(void))---------" << endl;
	cout << "|-comp| != || ----------->" << (t0 != empty ? P : F) << endl;
	cout << "|| != || ---------------->" << (t5 != empty ? F : P) << endl;
	
	cout << "operator==(void (*empty_func)(void), const txt& t)---------" << endl;
	cout << "|-comp| == || ----------->" << (empty == t0 ? F : P) << endl;
	cout << "|| == || ---------------->" << (empty == t5 ? P : F) << endl;
	
	cout << "operator!=(void (*empty_func)(void), const txt& t)---------" << endl;
	cout << "|-comp| != || ----------->" << (empty != t0 ? P : F) << endl;
	cout << "|| != || ---------------->" << (empty != t5 ? F : P) << endl;
#endif
	
	//////////////////////////////////////////////////////////////////////////
	cout << "Baka + ' ' + Mono: |" << (txt("Baka") + ' ' + "Mono") << '|' << endl;
	//////////////////////////////////////////////////////////////////////////
	
	const char *tofind = "This_is_tesuto_searching_!baka_this_T_tesutoraptor_text_baka!";
	txt fthis = "This";
	txt ftesuto = "tesuto";
	txt fbaka = "baka!";
	txt fnone = "NONSENSE";
	
	cout << dec << "\nSEARCHING FROM BEG >>>>>>>>>>>>>>>>>>\n";
	
	txt fnd_tst = tofind;
	cout << tofind << endl;
	dispPos("This" >> fnd_tst, txt("This"));
	cout << tofind << endl;
	dispPos("tesuto" >> fnd_tst, txt("tesuto"));
	cout << tofind << endl;
	dispPos("baka!" >> fnd_tst, txt("baka!"));
	cout << tofind << endl;
	dispPos(fthis >> fnd_tst, fthis);
	cout << tofind << endl;
	dispPos(ftesuto >> fnd_tst, ftesuto);
	cout << tofind << endl;
	dispPos(fbaka >> fnd_tst, txt(fbaka));
	cout << tofind << endl;
	dispPos("NONSENSE" >> fnd_tst, txt("NONSENSE"));
	cout << tofind << endl;
	dispPos(fnone >> fnd_tst, txt(fnone));
	cout << tofind << endl;
	dispPos('T' >> fnd_tst, txt('T'));
	cout << tofind << endl;
	dispPos('r' >> fnd_tst, txt('r' ));
	cout << tofind << endl;
	dispPos('!' >> fnd_tst, txt('!'));
	cout << tofind << endl;
	dispPos('$' >> fnd_tst, txt('$'));
	
	cout << "\nSEARCHING FROM end <<<<<<<<<<<<<<<<<<\n";
	
	cout << tofind << endl;
	dispPos("This" << fnd_tst, txt("This"));
	cout << tofind << endl;
	dispPos("tesuto" << fnd_tst, txt("tesuto"));
	cout << tofind << endl;
	dispPos("baka!" << fnd_tst, txt("baka!"));
	cout << tofind << endl;
	dispPos(fthis << fnd_tst, txt(fthis));
	cout << tofind << endl;
	dispPos(ftesuto << fnd_tst, ftesuto);
	cout << tofind << endl;
	dispPos(fbaka << fnd_tst, fbaka);
	cout << tofind << endl;
	dispPos("NONSENSE" << fnd_tst, txt("NONSENSE"));
	cout << tofind << endl;
	dispPos(fnone << fnd_tst, fnone);
	cout << tofind << endl;
	dispPos('T' << fnd_tst, txt('T'));
	cout << tofind << endl;
	dispPos('r' << fnd_tst, txt('r'));
	cout << tofind << endl;
	dispPos('!' << fnd_tst, txt('!'));
	cout << tofind << endl;
	dispPos('$' << fnd_tst, txt('$'));
	
	cout << "\nSEARCHING FROM BEG >>>>>>>>>>>>>>>>>>\n";
	
	cout << tofind << endl;
	dispPos(txtf(fnd_tst, 0, "tesuto"), txt("tesuto"));
	cout << tofind << endl;
	dispPos(txtf(fnd_tst, 0, ftesuto), txt(ftesuto));
	cout << tofind << endl;
	dispPos(txtf(fnd_tst, 0, 'r'), txt('r'));
	cout << tofind << endl;
	dispPos(txtf(fnd_tst, 24, "tesuto"), txt("tesuto"));
	cout << tofind << endl;
	dispPos(txtf(fnd_tst, 24, ftesuto), ftesuto);
	cout << tofind << endl;
	dispPos(txtf(fnd_tst, 0x2C, 'r'), txt('r'));
	cout << "\nSEARCHING FROM end <<<<<<<<<<<<<<<<<<\n";
	cout << tofind << endl;
	dispPos(txtfe(fnd_tst, 0, "tesuto"), txt("tesuto"));
	cout << tofind << endl;
	dispPos(txtfe(fnd_tst, 0, ftesuto), txt(ftesuto));
	cout << tofind << endl;
	dispPos(txtfe(fnd_tst, 0, 'r'), txt('r'));
	cout << tofind << endl;
	dispPos(txtfe(fnd_tst, 24, "tesuto"), txt("tesuto"));
	cout << tofind << endl;
	dispPos(txtfe(fnd_tst, 24, ftesuto), ftesuto);
	cout << tofind << endl;
	dispPos(txtfe(fnd_tst, 24, 'r'), txt('r'));
	
	cout << endl;
	
	const char *toins = "This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!";
	txt toins_txt = toins;
	const char *tie = toins + ~toins_txt;
	txt ins = "<|||>";
	
	const char *ti = toins - 1;
	while(++ti <= tie)
	{
		txt ins_tst = toins;
		txti(ins_tst, ui64(ti - toins), ins);
		cout << ins_tst << endl;
	}
	cout << endl;
	ti = toins - 1;
	while(++ti <= tie)
	{
		txt ins_tst = toins;
		txti(ins_tst, ui64(ti - toins), "<|||>");
		cout << ins_tst << endl;
	}
	cout << endl;
	ti = toins - 1;
	while(++ti <= tie)
	{
		txt ins_tst = toins;
		txti(ins_tst, ui64(ti - toins), '$');
		cout << ins_tst << endl;
	}
	cout << endl;
	
	///////////////////////////////////////////////////////////////////////
	
	ti = toins - 1;
	while(*(++ti) != 0)
	{
		txt ins_tst = toins;
		txto(ins_tst, ui64(ti - toins), ins);
		cout << ins_tst << endl;
	}
	cout << endl;
	ti = toins - 1;
	while(*(++ti) != 0)
	{
		txt ins_tst = toins;
		txto(ins_tst, ui64(ti - toins), "<|||>");
		cout << ins_tst << endl;
	}
	cout << endl;
	ti = toins - 1;
	while(*(++ti) != 0)
	{
		txt ins_tst = toins;
		txto(ins_tst, ui64(ti - toins), '$');
		cout << ins_tst << endl;
	}
	
	///////////////////////////////////////////////////////////////////////

	txt rep_tst = "0123456789_____0123456789";
	txt rep_txt = "|REPLACED|";
	txt rep_empty;
	
	cout << "    " << rep_tst << " OGIRG" << endl << endl;
	
	txt rep = rep_tst;
	txtr(rep, 0, 3, rep_txt);
	cout  << __LINE__ << " " << rep << (rep == "|REPLACED|3456789_____0123456789" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 0, 3, "|REPLACED|");
	cout  << __LINE__ << " " << rep << (rep == "|REPLACED|3456789_____0123456789" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 0, 3, '$');
	cout  << __LINE__ << " " << rep << (rep == "$3456789_____0123456789" ? P : F) << endl << endl;
	rep = rep_tst;
	
	txtr(rep, 0, RALL, rep_txt);
	cout  << __LINE__ << " " << rep << (rep == "|REPLACED|" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 0, RALL, "|REPLACED|");
	cout  << __LINE__ << " " << rep << (rep == "|REPLACED|" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 0, RALL, '$');
	cout  << __LINE__ << " " << rep << (rep == "$" ? P : F) << endl << endl;
	rep = rep_tst;

	txtr(rep, 10, 5, rep_txt);
	cout  << __LINE__ << " " << rep << (rep == "0123456789|REPLACED|0123456789" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 10, 5, "|REPLACED|");
	cout  << __LINE__ << " " << rep << (rep == "0123456789|REPLACED|0123456789" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 10, 5, '$');
	cout  << __LINE__ << " " << rep << (rep == "0123456789$0123456789" ? P : F) << endl << endl;
	rep = rep_tst;

	txtr(rep, 10, 0, rep_txt);
	cout  << __LINE__ << " " << rep << (rep == "0123456789|REPLACED|_____0123456789" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 10, 0, "|REPLACED|");
	cout  << __LINE__ << " " << rep << (rep == "0123456789|REPLACED|_____0123456789" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 10, 0, '$');
	cout  << __LINE__ << " " << rep << (rep == "0123456789$_____0123456789" ? P : F) << endl << endl;
	rep = rep_tst;

	txtr(rep, 10, RALL, rep_txt);
	cout  << __LINE__ << " " << rep << (rep == "0123456789|REPLACED|" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 10, RALL, "|REPLACED|");
	cout  << __LINE__ << " " << rep << (rep == "0123456789|REPLACED|" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 10, RALL, '$');
	cout  << __LINE__ << " " << rep << (rep == "0123456789$" ? P : F) << endl << endl;
	rep = rep_tst;

	txtr(rep, ~rep, 0, rep_txt);
	cout  << __LINE__ << " " << rep << (rep == "0123456789_____0123456789|REPLACED|" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, ~rep, 0, "|REPLACED|");
	cout  << __LINE__ << " " << rep << (rep == "0123456789_____0123456789|REPLACED|" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, ~rep, 0, '$');
	cout  << __LINE__ << " " << rep << (rep == "0123456789_____0123456789$" ? P : F) << endl << endl;
	rep = rep_tst;

	txtr(rep, ~rep-3, 6969, rep_txt);
	cout  << __LINE__ << " " << rep << (rep == "0123456789_____0123456|REPLACED|" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, ~rep-3, 6969, "|REPLACED|");
	cout  << __LINE__ << " " << rep << (rep == "0123456789_____0123456|REPLACED|" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, ~rep-3, 6969, '$');
	cout  << __LINE__ << " " << rep << (rep == "0123456789_____0123456$" ? P : F) << endl << endl;
	rep = rep_tst;
	
	txtr(rep, 10, 5, rep_empty);
	cout << __LINE__ << " " << rep << (rep == "01234567890123456789" ? P : F) << endl;
	rep = rep_tst;
	txtr(rep, 10, 5, "");
	cout << __LINE__ << " " << rep << (rep == "01234567890123456789" ? P : F) << endl << endl;
	rep = rep_tst;
	// Replacing with \0 is mistake, as size wont get updated, unless used with trimm operator!
	// Use txtd() for safe removal of text parts!
	
	txtd(rep, 10, 5);
	cout << __LINE__ << " " << rep << (rep == "01234567890123456789" ? P : F) << endl;
	rep = rep_tst;
	txtd(rep, 3, DALL);
	cout << __LINE__ << " " << rep << (rep == "012" ? P : F) << endl;
	rep = rep_tst;
	txtd(rep, ~rep-1, 1);
	cout << __LINE__ << " " << rep << (rep == "0123456789_____012345678" ? P : F) << endl;
	rep = rep_tst;
	
#endif
	
	t2ii2tTest();
	
	// EXCEPT TESTS
	/* TRY
	t2i(txt("20000000000000000000"));
	EXCEPT
	
	TRY
	t2i(txt("20000000000000000000111"));
	EXCEPT
	
	TRY
	t2i(txt("444222FFF111999"));
	EXCEPT
	
	TRY
	h2i(txt("20000000000000000000111FFFF"));
	EXCEPT
	
	TRY
	h2i(txt("FFaa4g44444"));
	EXCEPT
	
	txt ins_except_tst = "123456789";
	TRY
	txti(ins_except_tst, 18, "dis gonna make big badabooom!");
	EXCEPT
	
	TRY
	txto(ins_except_tst, 18, "dis gonna make big badabooom!");
	EXCEPT */
	
	///////////////////////////////////////////////////////////////////////////////////////////////
	const char *lorem = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque ut suscipit mi, vel condimentum metus. Etiam vestibulum dapibus fermentum. Vivamus in maximus velit. Donec tempor turpis justo. Duis luctus id risus vitae accumsan. Duis volutpat tincidunt felis, non ullamcorper augue cursus quis. Morbi maximus, odio at pellentesque eleifend, erat magna accumsan risus, sollicitudin aliquet est nulla eu augue. Donec lectus nulla, volutpat eget diam at, egestas sodales neque. Sed interdum libero eget semper posuere. Interdum et malesuada fames ac ante ipsum primis in faucibus. In odio urna, ultrices in commodo in, sagittis fringilla elit. Sed non luctus ligula."

	"Nullam condimentum vitae turpis non tincidunt. Suspendisse vulputate leo ut pharetra viverra. Fusce varius purus sed quam vestibulum, non ullamcorper odio volutpat. Curabitur interdum tincidunt magna eget aliquet. Aliquam sit amet leo quis tellus eleifend tristique. Donec non risus massa. Nullam tincidunt sollicitudin sodales."

	"Cras rhoncus malesuada ligula, vitae sodales metus luctus sit amet. Interdum et malesuada fames ac ante ipsum primis in faucibus. Mauris eleifend neque vitae tortor semper condimentum. Phasellus aliquet neque nisl, ut auctor dui varius ac. Cras ut metus neque. Nunc consequat, leo ut lacinia venenatis, nisi orci hendrerit ex, ut lacinia sapien augue quis magna. Proin scelerisque at ex eu condimentum. Quisque ac condimentum quam. Vestibulum a pulvinar dolor. Nunc sodales lacinia varius. Cras luctus leo dui, quis lacinia quam ornare tempus. Maecenas magna libero, scelerisque quis pellentesque eu, efficitur sed magna. Mauris vestibulum lobortis sagittis. Vivamus mollis lacus ut risus vehicula pellentesque. Suspendisse a blandit augue.HA! DIDNT EXPECT DA !BAKA! HERE?!";
	
	const char *lorem_sm = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque ut suscipit mi, vel condimentum metus. Etiam vestibulum dapibus fermentum. Vivamus in maximus velit. Donec tempor turpis justo. Duis luctus id risus vitae accumsan. Duis volutpat tincidunt felis, non ullamcorper augue cursus quis. Morbi maximus, odio at pellentesque eleifend, erat magna accumsan risus, sollicitudin aliquet est nulla eu augue.";
	
	
	cout << endl << "!THE ULTIMATE SHOWDOWN!" << endl;
	cout << "SIZEOF(STDBS): " << sizeof(std::string) << endl;
	cout << "SIZEOF(TXT):   " << sizeof(txt) << endl << endl;
	
	
	fkcursor();
	cout << "ALLOCIN BIG STR..." << endl;
	
	SW0SET //---------------------------------------
	for(int i = 0; i < 42000; ++i)
	{
		std::string s0 = lorem;
		std::string s1 = lorem;
		std::string s2 = lorem;
		std::string s3 = lorem;
	}
	SW0STOP //++++++++++++++++++++++++++++++++++++++
	SW1SET //---------------------------------------
	for(int i = 0; i < 42000; ++i)
	{
		txt s0 = lorem;
		txt s1 = lorem;
		txt s2 = lorem;
		txt s3 = lorem;
	}
	SW1STOP //++++++++++++++++++++++++++++++++++++++

	cout << "ALLOCIN CHARS..." << endl;
	
	SW2SET //---------------------------------------
	for(int i = 0; i < 420000; ++i)
	{
		std::string s0 = "$";
		std::string s1 = "&";
		std::string s2 = "*";
		std::string s3 = "#";
	}
	SW2STOP //++++++++++++++++++++++++++++++++++++++
	SW3SET //---------------------------------------
	for(int i = 0; i < 420000; ++i)
	{
		txt s0 = '$';
		txt s1 = '&';
		txt s2 = '*';
		txt s3 = '#';
	}
	SW3STOP //++++++++++++++++++++++++++++++++++++++
	
	cout << "ARRAY ACCESS..." << endl;
	
	std::string str_lorem = lorem;
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
	txt txt_lorem = lorem;
	SW5SET //---------------------------------------
	for(ui64 k = 0; k < 42000; ++k)
	{
		for(ui64 i = 0; i < lorems; ++i)
		{
			txt_lorem[i] = '$';
		}
	}
	SW5STOP //++++++++++++++++++++++++++++++++++++++
	
	cout << "APPENDING STR..." << endl;
	
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
	
	cout << "APPENDING CHAR..." << endl; // TEST WITH NEW SMOL STRING!!!! INSTED OF REUSING GIANT!!
	
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
	
	cout << "FINDING..." << endl;
	
	const char *fnd_str = "HA! DIDNT EXPECT DA !BAKA! HERE?!";
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
	
	cout << "INSERTING..." << endl;
	
	str_lorem = lorem;
	SWASET //---------------------------------------
	for(int i = 0; i < 4200; ++i)
	{
		for(ui64 k = 0; k < lorems; k += 100)
		{
			str_lorem.insert(k, "!BAKA!_!IS!_!!HERE?!");
		}
	}
	SWASTOP //++++++++++++++++++++++++++++++++++++++
	txt_lorem = lorem;
	SWBSET //---------------------------------------
	for(int i = 0; i < 4200; ++i)
	{
		for(ui64 k = 0; k < lorems; k += 100)
		{
			txti(txt_lorem, k, "!BAKA!_!IS!_!!HERE?!");
		}
	}
	SWBSTOP //++++++++++++++++++++++++++++++++++++++
	
	cout << "OVERWRITING..." << endl;

	str_lorem = lorem;
	SWCSET //---------------------------------------
	for(int i = 0; i < 42000; ++i)
	{
		for(ui64 k = 0; k + 100 < lorems; k += 100)
		{
			str_lorem.replace(k, 20, "!BAKA!_!IS!_!!HERE?!");
		}
	}
	SWCSTOP //++++++++++++++++++++++++++++++++++++++
	txt_lorem = lorem;
	SWDSET //---------------------------------------
	for(int i = 0; i < 42000; ++i)
	{
		for(ui64 k = 0; k + 100 < lorems; k += 100)
		{
			txto(txt_lorem, k, "!BAKA!_!IS!_!!HERE?!");
		}
	}
	SWDSTOP //++++++++++++++++++++++++++++++++++++++
	
	cout << "COMPARISION..." << endl;
	
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
	
	cout << "INT TO TEXT..." << endl;
	
	ui64 num = 18000000042000000000;
	std::string str_num;
	SW12SET //---------------------------------------
	for(int i = 0; i < 420000; ++i)
	{
		str_num = to_string(num);
	}
	SW12STOP //++++++++++++++++++++++++++++++++++++++
	txt txt_num;
	SW13SET //---------------------------------------
	for(int i = 0; i < 420000; ++i)
	{
		txt_num = i2t(num);
	}
	SW13STOP //++++++++++++++++++++++++++++++++++++++
	
	cout << "TEXT TO INT..." << endl;
	
	const char *num_str = "18000000042000000000";
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
	
	cout << "INT TO HEX..." << endl;
	
	num = 0xBEEFFAAA42006934;
	SW16SET //---------------------------------------
	for(int i = 0; i < 42000; ++i)
	{
		stringstream ss;
		ss << hex << uppercase << num;
		str_num = ss.str();
	}
	SW16STOP //++++++++++++++++++++++++++++++++++++++
	SW17SET //---------------------------------------
	for(int i = 0; i < 42000; ++i)
	{
		txt_num = i2h(num);
	}
	SW17STOP //++++++++++++++++++++++++++++++++++++++
	
	cout << "HEX TO INT..." << endl;
	
	num_str = "BEEFFAAA42006934";
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
	
	cout << "            " << setw(16) << "STD" << setw(28) << "TXT" << endl;
	cout << "ALLOC BIG STR:   ";
	SW0P
	swDiff(0x0, 0x1);
	SW1P
	cout << endl;
	cout << "ALLOC CHAR:      ";
	SW2P
	swDiff(0x2, 0x3);
	SW3P
	cout << endl;
	cout << "ARRAY ACCESS:    ";
	SW4P
	swDiff(0x4, 0x5);
	SW5P
	cout << endl;
	cout << "APPENDING STR:   ";
	SW6P
	swDiff(0x6, 0x7);
	SW7P
	cout << endl;
	cout << "APPENDING CHAR:  ";
	SWEP
	swDiff(0xE, 0xF);
	SWFP
	cout << endl;
	cout << "FINDING:         ";
	SW8P
	swDiff(0x8, 0x9);
	SW9P
	cout << endl;
	cout << "INSERTING:       ";
	SWAP
	swDiff(0xA, 0xB);
	SWBP
	cout << endl;
	cout << "OVERWRITING:     ";
	SWCP
	swDiff(0xC, 0xD);
	SWDP
	cout << endl;
	cout << "COMPARISION:     ";
	SW10P
	swDiff(0x10, 0x11);
	SW11P
	cout << endl;
	cout << "INT TO TEXT:     ";
	SW12P
	swDiff(0x12, 0x13);
	SW13P
	cout << endl;
	cout << "TEXT TO INT:     ";
	SW14P
	swDiff(0x14, 0x15);
	SW15P
	cout << endl;
	cout << "INT TO HEX:      ";
	SW16P
	swDiff(0x16, 0x17);
	SW17P
	cout << endl;
	cout << "HEX TO INT:      ";
	SW18P
	swDiff(0x18, 0x19);
	SW19P
	cout << endl;
	
#ifdef PROFILING

cout << endl << "inline txt& txt::operator+=(char c) // Very effective for rapid chars appending" << endl;
cout << setw(64) << left << "+---------------------------------------------------------------+" << endl;
cout << setw(64) << left << "|ui64 ns = s + 1;" << "|---> " << FSWT(0x2, 0x0) << endl;
cout << setw(64) << left << "+---------------------------------------------------------------+" << endl;
cout << setw(64) << left << "|if(ts <= ns)" << "|" << endl;
cout << setw(64) << left << "|{" << "|" << endl;
cout << setw(64) << left << "|    ui64 nts;" << "|" << endl;
cout << setw(64) << left << "|    char *tmp = AllocTmp(ns * TXT_CONCAT_MULT, &nts);" << "|------> " << FSWT(0x3, 0x0) << endl;
cout << setw(64) << left << "|    memcpy(tmp, t, s);" << "|------> " << FSWT(0x3, 0x1) << endl;
cout << setw(64) << left << "|    this->txt::~txt(); // Uses true size" << "|------> " << FSWT(0x3, 0x2) << endl;
cout << setw(64) << left << "|    t = tmp;" << "|" << endl;
cout << setw(64) << left << "|    ts = nts;" << "|------> " << FSWT(0x3, 0x3) << endl;
cout << setw(64) << left << "|}" << "|---> " << FSWT(0x2, 0x1) << endl;
cout << setw(64) << left << "+---------------------------------------------------------------+" << endl;
cout << setw(64) << left << "|t[s] = c;" << "|" << endl;
cout << setw(64) << left << "|s = ns;" << "|" << endl;
cout << setw(64) << left << "|t[s] = 0;" << "|---> " << FSWT(0x2, 0x2) << endl;
cout << setw(64) << left << "+---------------------------------------------------------------+" << endl;
cout << setw(64) << left << "                                                            TOTAL---> "
<< FSWTOT(0x2) << endl;
cout << setw(64) << left << "                                                            TOTAL------> "
<< FSWTOT(0x3) << endl;



cout << endl << "inline txt& txt::operator+=(const char *cs)" << endl;
cout << setw(64) << left << "+---------------------------------------------------------------+" << endl;
cout << setw(64) << left << "|ui64 ss = Sl(cs), ns = s + ss;" << "|---> " << FSWT(0x0, 0x0) << endl;
cout << setw(64) << left << "+---------------------------------------------------------------+" << endl;
cout << setw(64) << left << "|if(ts <= ns)" << "|" << endl;
cout << setw(64) << left << "|{" << "|" << endl;
cout << setw(64) << left << "|    ui64 nts;" << "|" << endl;
cout << setw(64) << left << "|    char *tmp = AllocTmp(ns * TXT_CONCAT_MULT, &nts);" << "|------> " << FSWT(0x1, 0x0) << endl;
cout << setw(64) << left << "|    memcpy(tmp, t, s);" << "|------> " << FSWT(0x1, 0x1) << endl;
cout << setw(64) << left << "|    this->txt::~txt(); // Uses true size" << "|------> " << FSWT(0x1, 0x2) << endl;
cout << setw(64) << left << "|    t = tmp;" << "|" << endl;
cout << setw(64) << left << "|    ts = nts;" << "|------> " << FSWT(0x1, 0x3) << endl;
cout << setw(64) << left << "|}" << "|---> " << FSWT(0x0, 0x1) << endl;
cout << setw(64) << left << "+---------------------------------------------------------------+" << endl;
cout << setw(64) << left << "|memcpy(t+s, cs, ss);" << "|---> " << FSWT(0x0, 0x2) << endl;
cout << setw(64) << left << "+---------------------------------------------------------------+" << endl;
cout << setw(64) << left << "|s = ns;" << "|" << endl;
cout << setw(64) << left << "|t[s] = 0;" << "|---> " << FSWT(0x0, 0x3) << endl;
cout << setw(64) << left << "+---------------------------------------------------------------+" << endl;
cout << setw(64) << left << "                                                            TOTAL---> "
<< FSWTOT(0x0) << endl;
cout << setw(64) << left << "                                                            TOTAL------> "
<< FSWTOT(0x1) << endl;

#endif

/* !THE ULTIMATE SHOWDOWN!
SIZEOF(STDBS): 40
SIZEOF(TXT):   16
Od
                              STD                         TXT
ALLOC_BIG_STR:   79.548'500 ms   x10.62->    844.578'200 ms
ALLOC_CHAR:      9.781'700 ms    x1.29->     12.655'200 ms
ARRAY_ACCESS:    63.426'700 ms   <-x3.37     18.795'000 ms
APPENDING STR:   1.710'600 ms    x578.06->   988.821'100 ms
APPENDING CHAR:  721.400 us      x87.59->    63.188'500 ms
FINDING:         3.798'100 ms    x9.19->     34.912'300 ms
INSERTING:       555.644'200 ms  x11.05->    6.141 s
OVERWRITING:     1.115'000 ms    x1.85->     2.58'700 ms

inline txt& txt::operator+=(char c) // Very ineffective for rapid chars appending
+------------------------------------------------------+
|ui64 ns = s + 1;                                      |---> 2.00%   870.100 us
+------------------------------------------------------+
|char *tmp = (char *)HeapAlloc(h, NULL, ns + 1);       |---> 19.74%  8.607'000 ms
+------------------------------------------------------+
|memcpy(tmp, t, s);                                    |---> 76.06%  33.161'900 ms
+------------------------------------------------------+
|tmp[s] = c;                                           |
|tmp[ns] = 0;                                          |---> 2.21%   962.500 us
+------------------------------------------------------+
|this->txt::~txt();                                    |---> 30.15%  13.145'900 ms
+------------------------------------------------------+
|s = ns;                                               |
|t = tmp;                                              |---> 2.06%   899.900 us
+------------------------------------------------------+
                                                   TOTAL---> 100.00% 43.601'500 ms

inline txt& txt::operator+=(const char *cs)
+------------------------------------------------------+
|ui64 ss = Sl(cs), ns = s + ss;                        |---> 0.51%   5.44'000 ms
+------------------------------------------------------+
|char *tmp = (char *)HeapAlloc(h, NULL, ns + 1);       |---> 1.37%   13.550'300 ms
+------------------------------------------------------+
|memcpy(tmp, t, s);                                    |---> 73.93%  730.181'500 ms
+------------------------------------------------------+
|memcpy(tmp+s, cs, ss+1);                              |---> 0.06%   624.100 us
+------------------------------------------------------+
|this->txt::~txt();                                    |---> 24.12%  238.228'700 ms
+------------------------------------------------------+
|s = ns;                                               |
|t = tmp;                                              |---> 0.01%   96.400 us
+------------------------------------------------------+
                                                   TOTAL---> 100.00% 987.725'000 ms
	
Od
                             STD                             TXT
ALLOC_BIG_STR:   80.170'500 ms         x10.53    844.648'100 ms
ALLOC_CHAR:      9.649'900 ms          x1.36     13.212'600 ms
ARRAY_ACCESS:    64.147'200 ms  x3.4             18.944'900 ms
APPENDING STR:   1.633'800 ms          x597.3    975.452'500 ms
APPENDING CHAR:  718.0 us              x74.3     53.583'800 ms
FINDING:         3.697'100 ms          x9.56     35.35'300 ms
INSERTING:       559.86'800 ms         x11.12    6.117 s
OVERWRITING:     1.128'100 ms          x2.32     2.97'400 ms

O2
                             STD                             TXT
ALLOC_BIG_STR:   18.752'400 ms                   170.628'000 ms
ALLOC_CHAR:      945.200 us                      11.883'600 ms
ARRAY_ACCESS:    4.962'500 ms                    154.900 us
APPENDING STR:   1.418'800 ms                    994.332'800 ms
APPENDING CHAR:  85.100 us                       38.13'500 ms
FINDING:         0 ns                            0 ns
INSERTING:       550.506'200 ms                  6.116 s
OVERWRITING:     223.400 us                      461.200 us */

/* =========================================AFTER=GRAND=OPTIMISATION=========================================
DEBUG LIB BUILD /Od
!THE ULTIMATE SHOWDOWN!
SIZEOF(STDBS): 40
SIZEOF(TXT):   24
===========================================O2=LIB=OPTIMISATION============================================
                      STD                         TXT
ALLOC BIG STR:   177.41'500 ms       x5.04       891.600'900 ms !!!!!!!!!!!!!
ALLOC CHAR:      45.43'200 ms        x4.87       219.470'800 ms !!!!!!!!!!!!!
ARRAY ACCESS:    296.693'800 ms      x1.71       173.915'700 ms
APPENDING STR:   24.886'300 ms       x1.31       19.16'200 ms
APPENDING CHAR:  5.31'300 ms         x3.24       1.550'800 ms
FINDING:         36.656'700 ms       x2.82       103.526'500 ms !!!!!!!!!!!!!
INSERTING:       2.561 s             x1.00       2.572 s
OVERWRITING:     21.411'300 ms       x1.70       12.578'800 ms
COMPARISION:     43.793'600 ms       x1.00       43.660'100 ms
INT TO TEXT:     227.103'000 ms      x3.58       63.417'900 ms
TEXT TO INT:     42.150'000 ms       x3.00       14.72'000 ms
INT TO HEX:      55.315'600 ms       x10.64      5.196'700 ms
HEX TO INT:      40.944'300 ms       x4.05       10.111'400 ms
===========================================NO=PROFILE=OVERHEAD============================================
                        STD                         TXT
ALLOC BIG STR:   962.121'100 ms      x1.60       1.536 s
ALLOC CHAR:      1.709 s             x1.78       3.36 s
ARRAY ACCESS:    307.904'100 ms      x1.62       190.364'500 ms
APPENDING STR:   33.212'200 ms       x1.86       61.810'800 ms
APPENDING CHAR:  4.791'300 ms        x1.98       2.424'200 ms
FINDING:         36.933'300 ms       x9.51       351.382'800 ms
INSERTING:       2.555 s             x1.01       2.519 s
OVERWRITING:     30.42'800 ms        x2.00       60.178'100 ms
COMPARISION:     43.490'400 ms       x4.82       209.797'300 ms
INT TO TEXT:     891.859'200 ms      x1.79       498.824'700 ms
TEXT TO INT:     138.507'700 ms      x2.70       51.243'600 ms
INT TO HEX:      17.414 s            x509.40     34.186'800 ms
HEX TO INT:      118.600'300 ms      x4.45       26.638'400 ms

==============================================PROFILE=OVERHEAD============================================
                         STD                         TXT
ALLOC BIG STR:   999.244'600 ms      x1.54       1.536 s
ALLOC CHAR:      1.836 s             x1.64       3.16 s
ARRAY ACCESS:    361.715'500 ms      x1.93       187.640'100 ms
APPENDING STR:   33.971'200 ms       x1.97       66.876'200 ms
APPENDING CHAR:  4.815'800 ms        x15.50      74.650'500 ms
FINDING:         37.660'400 ms       x9.29       349.862'200 ms
INSERTING:       2.554 s             x1.01       2.531 s
OVERWRITING:     21.98'400 ms        x2.04       42.995'500 ms
COMPARISION:     43.741'400 ms       x4.85       211.968'900 ms
INT TO TEXT:     951.791'600 ms      x1.90       500.676'100 ms
TEXT TO INT:     138.152'900 ms      x2.68       51.614'600 ms
INT TO HEX:      10.717 s            x312.51     34.296'500 ms
HEX TO INT:      118.646'000 ms      x4.46       26.630'000 ms

inline txt& txt::operator+=(char c) // Very effective for rapid chars appending
+---------------------------------------------------------------+
|ui64 ns = s + 1;                                               |---> 32.44%  9.35'200 ms
+---------------------------------------------------------------+
|if(ts <= ns)                                                   |
|{                                                              |
|    ui64 nts;                                                  |
|    char *tmp = AllocTmp(ns * TXT_CONCAT_MULT, &nts);          |------> 0.00%   0 ns
|    memcpy(tmp, t, s);                                         |------> 0.00%   0 ns
|    this->txt::~txt(); // Uses true size                       |------> 0.00%   0 ns
|    t = tmp;                                                   |
|    ts = nts;                                                  |------> 0.00%   0 ns
|}                                                              |---> 32.77%  9.127'600 ms
+---------------------------------------------------------------+
|t[s] = c;                                                      |
|s = ns;                                                        |
|t[s] = 0;                                                      |---> 34.79%  9.690'900 ms
+---------------------------------------------------------------+
                                                            TOTAL---> 100.00% 27.853'700 ms
                                                            TOTAL------> 0.00%   0 ns

inline txt& txt::operator+=(const char *cs)
+---------------------------------------------------------------+
|ui64 ss = Sl(cs), ns = s + ss;                                 |---> 81.07%  49.583'600 ms
+---------------------------------------------------------------+
|if(ts <= ns)                                                   |
|{                                                              |
|    ui64 nts;                                                  |
|    char *tmp = AllocTmp(ns * TXT_CONCAT_MULT, &nts);          |------> 0.58%   36.800 us
|    memcpy(tmp, t, s);                                         |------> 71.80%  4.520'000 ms
|    this->txt::~txt(); // Uses true size                       |------> 27.61%  1.738'100 ms
|    t = tmp;                                                   |
|    ts = nts;                                                  |------> 0.01%   400 ns
|}                                                              |---> 11.82%  7.230'100 ms
+---------------------------------------------------------------+
|memcpy(t+s, cs, ss);                                           |---> 5.54%   3.385'500 ms
+---------------------------------------------------------------+
|s = ns;                                                        |
|t[s] = 0;                                                      |---> 1.58%   965.800 us
+---------------------------------------------------------------+
                                                            TOTAL---> 100.00% 61.165'000 ms
                                                            TOTAL------> 100.00% 6.295'300 ms */
	
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