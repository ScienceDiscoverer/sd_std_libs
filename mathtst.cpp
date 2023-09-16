// CONSOLE
#include <sddb>
#include <tests.h>
#include <math>

//#define MANUAL_TEST
#ifdef MANUAL_TEST
#include <stdr>
#endif

i32 wmain()
{
	T("ABS UI64", abs((ui64)(1 - 2)), (ui64)1);
	T("ABS UI32", abs((ui32)(1 - 2)), (ui64)1);
	T("ABS UI16", abs((ui16)(1 - 2)), (ui64)1);
	T("ABS UI8", abs((i16)(1 - 2)), (i64)1);
	T("ABS I64", abs((i64)(1 - 2)), (i64)1);
	T("ABS I32", abs((i32)(1 - 2)), (i64)1);
	T("ABS I16", abs((i16)(1 - 2)), (i64)1);
	T("ABS I8", abs((i8)(1 - 2)), (i64)1);
	
	T("MPOW", mpow(4, 13, 497), 445);
	T("MPOW STR", mpowStrMatch(4, 13, 497), 445);
	T("MPOW DIV & CONQ", mpowDivAndConq(4, 13, 497), 445);
	
	
	
	const ui64 d = 256;					// Radix, should equal to A
	//const ui64 q = 72057594037927931;	// Prime number to calculate modulus on (max prime such that d * q fits in CPU word)
	const ui64 q = 4294967291;
	const ui64 m = 17;
	ui64 h = mpowStrMatch(d, m-1, q);
	p|"mpowStrMatch "|h|N;
	h = mpow(d, m-1, q);
	p|"mpow "|h|N;
	h = mpowDivAndConq(d, m-1, q);
	p|"mpowDivAndConq "|h|N;
	
	
	
	T("SQRT", sqrt(254896524), 15965);
	T("SQRT MAX", sqrt(UI64_MAX), (ui64)4294967295);
	
	TBOOL("IS PRIME? 0", isPrime(7919), true);
	TBOOL("IS PRIME? 1", isPrime(668547), false);
	
#ifdef PRIME_UTILITIES
	T("BIGGEST WORD MULTIPLIER 256", bgstWordMult(256), (ui64)72057594037927935);
	T("BIGGEST PRIMAL WORD MULTIPLIER 256", bgstWordPrimeMult(256), (ui64)72057594037927931);
	T("BIGGEST WORD MULTIPLIER 65536", bgstWordMult(65536), (ui64)281474976710655);
	T("BIGGEST PRIMAL WORD MULTIPLIER 65536", bgstWordPrimeMult(65536), (ui64)281474976710597);
#endif
	
	
	
	
#ifdef MANUAL_TEST
	while(1)
	{
		ui64 x;
		r > x;
		p|sqrt(x)|N;
	}
#endif
	
	p|DC|TB|P;
	return 0;
}

// MANUAL TESTS
//ui64 base, exp, mod;
//r > base, r > exp, r > mod;
//p|"mpow()    "|base|'^'|exp|" mod "|mod|" = "|mpow(base, exp, mod)|N;
//p|"mpowBin() "|base|'^'|exp|" mod "|mod|" = "|mpowBin(base, exp, mod)|N;
///////////////////////////////////////////////////////////////////////////


// 256 CHAR
// MULT:  72057594037927935
// PRIME: 72057594037927931
// SW0: 1.824 s

// 65536 WCHAR
// MULT:  281474976710655
// PRIME: 281474976710597
// SW0: 108.224'000 ms


//ui64 in = (ui64)-24;
//p|in|N;
//i64 ii = (i64)in;
//p|ii|N;
//p|(i64)in * -1|N;
//ui16 u122 = (ui16)-22;
//p|abs(u122)|N;
//
//
//
//i64 num = -2245;
//SW0SET
//for(ui64 i = 0; i < 50000000; ++i)
//{
//	i64 res = abs((i64)(num+i%3));
//	++res;
//}
//SW0STOP
//
//SW1SET
//for(ui64 i = 0; i < 50000000; ++i)
//{
//	i64 res = (i64)abs((ui64)(num+i%3));
//	++res;
//}
//SW1STOP
//
// /Od
//SW0: 297.743'200 ms
//SW1: 296.83'900 ms
//
//i64 num = -2245;
//SW0SET
//for(ui64 i = 0; i < 50000000; ++i)
//{
//	i64 res = abs(num);
//	++res;
//}
//SW0STOP
//
//SW1SET
//for(ui64 i = 0; i < 50000000; ++i)
//{
//	i64 res = num < 0 ? num * -1 : num;
//	++res;
//}
//SW1STOP
//
//SW2SET
//for(ui64 i = 0; i < 50000000; ++i)
//{
//	if(num < 0)
//	{
//		num *= -1;
//	}
//	
//	i64 res = num;
//	++res;
//}
//SW2STOP
// /Od 
//SW0: 125.315'800 ms
//SW1: 40.758'100 ms
//
//SW0: 120.436'500 ms
//SW1: 48.49'600 ms
//SW2: 48.86'200 ms