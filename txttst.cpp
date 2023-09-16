// CONSOLE NOPT
#include <sddb>
#include <stdp>
#include <tests.h>

#include <string>	//
#include <sstream>	// Just for profiling test, otherwise, casual std, ugh!
#include <ios>		//

#pragma warning( disable : 4834 )
#pragma warning( disable : 4189 )

// TODO ADD SORTING OPERATORS < > TESTS!!

// TODO BETTER COMPARISION... TEST MAKE IT MORE REAISTIC USE CASE ALSO TEST COMPARISON OF MANY SMOL STRINGZ
// TODO BETTER FIND... MAKE BEST CASE SCENARIO, REALISTIC, AND WORSE CASE WHERE AAA FINDIN-> AAAAAAAA...
// TODO INSPERCT STRINGLENGTH IMPLEMENTATION MB IT IS SLOWER THAN STD/STRLEN AND THATS WHY SLOWER FIND/INIT? ADD ALLOC TEST FROM ANOTHER TXT, NOT CSTR!!! FOR LOOP VS while(*++doc != 0) TEST!!! vs while(++d != de) this

//////PERFORMANCE COST OF CALLIN FUNCTION TO GET HEAP EVERY TIME!!
//TXT_FREE;		// NULL just gives error
//
//  00004	e8 00 00 00 00	 call	 ?txt_heap@@YAAEBQEAXXZ	; txt_heap
//  00009	45 33 c0	 xor	 r8d, r8d
//  0000c	33 d2		 xor	 edx, edx
//  0000e	48 8b 08	 mov	 rcx, QWORD PTR [rax]
//  00011	ff 15 00 00 00
//	00		 call	 QWORD PTR __imp_HeapFree
// WITH FULL OPTIMISATION ON! THIS IS VERY BAD!


// TRY TO DO CHAR ALLOC FIRST!! MB HEAP IS GETTIN DEGRADED AFTER PREVIOUS ALLOCATIONS!!!!! STD MIGHT CLEAN DA HEAP


/////POTENTIALLY INCREASE START SIZE OF HEAP! MB FASTER CHARS ALLOC??

cstr buff_worker_str = L("BUFF TEST PASSED!");

void buff_worker(char *b, uli32 *s)
{
	uli32 i = 0;
	while(buff_worker_str.t[i] != 0 && i < *s)
	{
		b[i] = buff_worker_str.t[i];
		++i;
	}
	*s = i;
}

void dispPos(ui64 pos, const txt& s, ui64 correct_pos)
{	
	if(pos == NFND)
	{
		p|"NOT FOUND!"|" -> |" | s | "|";
		p|(pos == correct_pos ? p|G|" PASSED"|D : p|R|" FAILED"|D)|N;
		return;
	}
	
	for(ui64 i = 0; i < pos; ++i)
	{
		p|'-';
		if(i + 1 == pos)
		{
			break;
		}
	}
	p|'^';
	p|' ' | pos | " -> |" | s | "|";
	p|(pos == correct_pos ? p|G|" PASSED"|D : p|R|" FAILED"|D)|N;
}

bool t2ii2tTest()
{
	p|DC;
	p|"T2II2T PROGRESS: " |N;
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
			p|'\r';
			p|"[";
			while(--j >= 0)
			{
				p|'|';
			}
			while(--k >= 0)
			{
				p|' ';
			}
			p|"]";
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
		txt h8 = b2h(x8);
		
		ui64 rdec = t2i(dec);
		i32 rsdec = (i32)t2i(sdec);
		ui64 rh64 = h2i(h64);
		ui64 rh32 = h2i(h32);
		ui64 rh16 = h2i(h16);
		ui64 rh8 = h2i(h8);
		
		if(rdec != i)
		{
			epic_fail = true;
			p|R | "T2II2T EPIC FAIL! rdec:  " | D | rdec | " txt: "
				| dec | " i:    " | i |N;
		}
		
		if(rsdec != sx32)
		{
			epic_fail = true;
			p|R | "T2II2T EPIC FAIL! rsdec: " | D | rsdec | " txt: "
				| sdec | " sx32: " | sx32 |N;
		}
		
		if(rh64 != i)
		{
			epic_fail = true;
			p|R | "T2II2T EPIC FAIL! rh64:  " | D | H | rh64 | " txt: "
				| h64 | " i:    " | i |N;
		}
		
		if(rh32 != x32)
		{
			epic_fail = true;
			p|R | "T2II2T EPIC FAIL! rh32:  " | D | H | rh32 | " txt: "
				| h32 | " x32:  " | x32 |N;
		}
		
		if(rh16 != x16)
		{
			epic_fail = true;
			p|R | "T2II2T EPIC FAIL! rh16:  " | D | H | rh16 | " txt: "
				| h16 | " x16:  " | x16 |N;
		}
		
		if(rh8 != x8)
		{
			epic_fail = true;
			p|R | "T2II2T EPIC FAIL! rh8:   " | D | H | rh8 | " txt: "
				| h8 | " x8:  " | x8 |N;
		}
	}
	
	ui64 bin64 = 0xF0F0F0F0F0F0F0F0;
	ui32 bin32 = 0xF0F0F0F0;
	ui16 bin16 = 0xF0F0;
	ui8 bin8 = 0xF0;
	
	if(i2b(bin64) != L("1111000011110000111100001111000011110000111100001111000011110000"))
	{
		p|R|"T2II2T EPIC FAIL! bin64 "|D|N;
		p|"GOT:  "|i2b(bin64)|N;
		p|"NEED: "|"1111000011110000111100001111000011110000111100001111000011110000"|N;
		epic_fail = true;
	}
	if(i2b(bin32) != L("11110000111100001111000011110000"))
	{
		p|R|"T2II2T EPIC FAIL! bin32 "|D|N;
		p|"GOT:  "|i2b(bin32)|N;
		p|"NEED: "|"11110000111100001111000011110000"|N;
		epic_fail = true;
	}
	if(i2b(bin16) != L("1111000011110000"))
	{
		p|R|"T2II2T EPIC FAIL! bin16 "|D|N;
		p|"GOT:  "|i2b(bin16)|N;
		p|"NEED: "|"1111000011110000"|N;
		epic_fail = true;
	}
	if(b2b(bin8) != L("11110000"))
	{
		p|R|"T2II2T EPIC FAIL! bin8 "|D|N;
		p|"GOT:  "|b2b(bin8)|N;
		p|"NEED: "|"11110000"|N;
		epic_fail = true;
	}
	
	i8 nbyte = -112;
	i8 pbyte = 42;
	ui8 ubyte = 222;
	
	if(b2t(nbyte) != L("-112"))
	{
		p|R|"T2II2T EPIC FAIL! nbyte "|D|N;
		p|"GOT:  "|b2t(nbyte)|N;
		p|"NEED: "|"-112"|N;
		epic_fail = true;
	}
	if(b2t(pbyte) != L("42"))
	{
		p|R|"T2II2T EPIC FAIL! pbyte "|D|N;
		p|"GOT:  "|b2t(pbyte)|N;
		p|"NEED: "|"42"|N;
		epic_fail = true;
	}
	if(b2t(ubyte) != L("222"))
	{
		p|R|"T2II2T EPIC FAIL! ubyte "|D|N;
		p|"GOT:  "|b2t(ubyte)|N;
		p|"NEED: "|"222"|N;
		epic_fail = true;
	}
	
	return epic_fail;
}

inline ui64 getTerminator(const txt &t)
{
	return (ui64)*((const char *)t + ~t);
}

cstr insert_tst_arr[] = {
	L("<|||>This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("T<|||>his_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("Th<|||>is_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("Thi<|||>s_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This<|||>_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_<|||>is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_i<|||>s_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is<|||>_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_<|||>tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_t<|||>esuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_te<|||>suto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tes<|||>uto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesu<|||>to_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesut<|||>o_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto<|||>_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_<|||>insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_i<|||>nsertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_in<|||>sertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_ins<|||>ertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_inse<|||>rtion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_inser<|||>tion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insert<|||>ion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_inserti<|||>on_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertio<|||>n_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion<|||>_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_<|||>!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!<|||>baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!b<|||>aka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!ba<|||>ka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!bak<|||>a_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka<|||>_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_<|||>this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_t<|||>his_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_th<|||>is_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_thi<|||>s_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this<|||>_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_<|||>T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T<|||>_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_<|||>tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_t<|||>esutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_te<|||>sutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tes<|||>utoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesu<|||>toraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesut<|||>oraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesuto<|||>raptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutor<|||>aptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutora<|||>ptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutorap<|||>tor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutorapt<|||>or_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutorapto<|||>r_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor<|||>_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_<|||>text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_t<|||>ext_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_te<|||>xt_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_tex<|||>t_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text<|||>_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_<|||>baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_b<|||>aka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_ba<|||>ka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_bak<|||>a!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka<|||>!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!<|||>") };
	
cstr insert_char_tst_arr[] = {
	L("$This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("T$his_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("Th$is_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("Thi$s_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This$_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_$is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_i$s_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is$_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_$tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_t$esuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_te$suto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tes$uto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesu$to_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesut$o_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto$_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_$insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_i$nsertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_in$sertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_ins$ertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_inse$rtion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_inser$tion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insert$ion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_inserti$on_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertio$n_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion$_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_$!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!$baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!b$aka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!ba$ka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!bak$a_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka$_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_$this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_t$his_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_th$is_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_thi$s_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this$_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_$T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T$_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_$tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_t$esutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_te$sutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tes$utoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesu$toraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesut$oraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesuto$raptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutor$aptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutora$ptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutorap$tor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutorapt$or_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutorapto$r_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor$_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_$text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_t$ext_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_te$xt_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_tex$t_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text$_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_$baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_b$aka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_ba$ka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_bak$a!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka$!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!$") };
	
cstr overwr_tst_arr[] = {
	L("<|||>is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("T<|||>s_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("Th<|||>_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("Thi<|||>tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This<|||>esuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_<|||>suto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_i<|||>uto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is<|||>to_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_<|||>o_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_t<|||>_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_te<|||>insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tes<|||>nsertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesu<|||>sertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesut<|||>ertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto<|||>rtion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_<|||>tion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_i<|||>ion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_in<|||>on_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_ins<|||>n_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_inse<|||>_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_inser<|||>!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insert<|||>baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_inserti<|||>aka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertio<|||>ka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion<|||>a_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_<|||>_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!<|||>this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!b<|||>his_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!ba<|||>is_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!bak<|||>s_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka<|||>_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_<|||>T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_t<|||>_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_th<|||>tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_thi<|||>esutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this<|||>sutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_<|||>utoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T<|||>toraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_<|||>oraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_t<|||>raptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_te<|||>aptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tes<|||>ptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesu<|||>tor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesut<|||>or_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesuto<|||>r_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutor<|||>_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutora<|||>text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutorap<|||>ext_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutorapt<|||>xt_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutorapto<|||>t_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor<|||>_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_<|||>baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_t<|||>aka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_te<|||>ka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_tex<|||>a!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text<|||>!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_<|||>"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_b<|||>"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_ba<|||>"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_bak<|||>"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka<|||>") };
	
cstr overwr_char_tst_arr[] = {
	L("$his_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("T$is_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("Th$s_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("Thi$_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This$is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_$s_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_i$_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is$tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_$esuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_t$suto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_te$uto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tes$to_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesu$o_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesut$_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto$insertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_$nsertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_i$sertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_in$ertion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_ins$rtion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_inse$tion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_inser$ion_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insert$on_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_inserti$n_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertio$_!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion$!baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_$baka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!$aka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!b$ka_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!ba$a_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!bak$_this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka$this_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_$his_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_t$is_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_th$s_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_thi$_T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this$T_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_$_tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T$tesutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_$esutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_t$sutoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_te$utoraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tes$toraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesu$oraptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesut$raptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesuto$aptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutor$ptor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutora$tor_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutorap$or_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutorapt$r_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutorapto$_text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor$text_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_$ext_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_t$xt_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_te$t_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_tex$_baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text$baka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_$aka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_b$ka!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_ba$a!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_bak$!"),
	L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka$") };

cstr global_text_big_str = L(
	"-------------------------------------------------------------------------------"
	"-------------------------------------------------------------------------------"
	"-------------------------------------------------------------------------------"
	"-------------------------------------------------------------------------------"
	"-------------------------------------------------------------------------------"
	"-------------------------------------------------------------------------------"
	"-------------------------------------------------------------------------------"
	"-------------------------------------------------------------------------------"
	"-------------------------------------------------------------------------------"
	"-------------------------------------------------------------------------------"
	"-------------------------------------------------------------------------------"
	"-------------------------------------------------------------------------------"
	"-------------------------------------------------------------------------------"
	"-------------------------------------------------------------------------------");
txt global_text_big = global_text_big_str;

cstr global_text_empty_str = L("");
txt global_text_empty;
cstr global_text_small_str = L("i'm very smol :'(");
txt global_text_small = global_text_small_str;

void test();

int wmain()
{
	txt total_empty;
	T("TOTAL EMPTY SIZE", ~total_empty, 0);
	T("TOTAL EMPTY TRUE SIZE", !total_empty, 0);
	T("TOTAL EMPTY DATA", (ui64)(const char *)total_empty, NULL);
	
	T("GLOBAL TEXT BIG", global_text_big, global_text_big_str);
	T("GLOBAL TEXT EMPTY", global_text_empty, global_text_empty_str);
	T("GLOBAL TEXT SMALL", global_text_small, global_text_small_str);
	
#ifndef BASIC_TESTZ
#ifdef BUFFER_MODE
	txt conbuff = 20;
	ReadConsoleA(
		GetStdHandle(STD_INPUT_HANDLE),
		conbuff,
		(DWORD)!conbuff,
		*conbuff,
		NULL);
		
	p|"|" | conbuff | "| S: " | ~conbuff | " | TS: " | !conbuff |N;
	p|"|" | (conbuff += "___APPENDED_TO_TEST_TEXT!"), p|"| S: " | ~conbuff
		| " | TS: " | !conbuff |N; // I guess coz of optimisations here old sizes are reported. Nope. Not anymore!
	p|"| S: " | ~conbuff	| " | TS: " | !conbuff |N; // Here sizes are correct
	
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
	p|P;
#endif
	
	txt t(L("Hello Baka"));
	txt g = L("Whale Hallo Dere");
	//////////////////////////////////////////////////////////////////////////
	T("CONSTRUCTION FROM CSTR LITERAL t", t, L("Hello Baka"));
	T("CONSTRUCTION FROM CSTR LITERAL STRLEN t", ~t, strlen(t));
	T("CONSTRUCTION FROM CSTR LITERAL g", g, L("Whale Hallo Dere"));
	T("CONSTRUCTION FROM CSTR LITERAL STRLEN g", ~g, strlen(g));
	//////////////////////////////////////////////////////////////////////////
	txt ch = '$';
	T("CONSTRUCTION FROM CHAR", ch, '$');
	//////////////////////////////////////////////////////////////////////////
	txt buff = 20;
	buff_worker(buff, *buff);
	if(T("BUFFER WORKER", buff, buff_worker_str))
	{
		p|"buff in hex: "|str2hex((const char *)buff);
		p|N|I|buff|I|" buff_work size/true size: "|~buff|S|!buff|N;
	}
	//////////////////////////////////////////////////////////////////////////
	t = g;
	T("TXT 2 TXT ASSIGNMENT", t, g);
	t = txt(L("I'm tmp floop!"));
	T("TXT 2 TXT ASSIGNMENT FROM RVAL", t, L("I'm tmp floop!"));
	t = L("NEW char literal ready for duty!");
	T("TXT 2 CSTR ASSIGNMENT", t, L("NEW char literal ready for duty!"));
	t = '#';
	T("TXT 2 CHAR ASSIGNMENT", t, (txt)'#');
	t = -42;
	T("TXT 2 NEGATIVE INT ASSIGNMENT", t, L(""));
	TNOT("TXT 2 NEGATIVE INT ASSIGNMENT TRUE SIZE", !t, 0);
	t = g;
	t = 0;
	T("TXT 2 ZERO INT ASSIGNMENT", t, L(""));
	TNOT("TXT 2 ZERO INT ASSIGNMENT TRUE SIZE", !t, 0);
	t = g;
	t = 42;
	T("TXT 2 POSITIVE INT ASSIGNMENT", t, L(""));
	T("TXT 2 POSITIVE INT ASSIGNMENT TRUE SIZE", !t, 42 + 1);
	T("TXT 2 POSITIVE INT ASSIGNMENT STRLEN", ~t, strlen(t));
	//////////////////////////////////////////////////////////////////////////
	//for(ui64 i = 0; i < !t; ++i)
	//{
	//	//p|"t[" | i | "]: " | hex | uppercase | +t[0] |N;
	//	p|/* (char *) */(t[i]) | '_';
	//}
	// _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ msvc
	//__________________________________________ gcc -> because gcc does not pring \0 chars for SOME reason ._.
	//char a[42];
	//memset(a, 0x0, 42);
	//for(ui64 i = 0; i < 42; ++i)
	//{
	//	//p|"t[" | i | "]: " | hex | uppercase | +t[0] |N;
	//	p|(a[i]) | '_';
	//}
	//for(ui64 i = 0; i < ~g; ++i)
	//{
	//	p|g[i] | '_';
	//}
	//////////////////////////////////////////////////////////////////////////
	T("t[0]", (ui64)t[0], 0);
	T("~t", ~t, 0);
	T("!t", !t, 42 + 1);
	//////////////////////////////////////////////////////////////////////////
	txt t0, t1;
	t0 = L("Baka Part 1");
	t1 = L("-Baka Part 2");
	t0 += t1;
	T("TXT 2 TXT += APPEND", t0, L("Baka Part 1-Baka Part 2"));
	t0 += L("-Baka Part 3");
	T("CSTR 2 TXT += APPEND", t0, L("Baka Part 1-Baka Part 2-Baka Part 3"));
	t0 += '*';
	T("CHAR 2 TXT += APPEND", t0, L("Baka Part 1-Baka Part 2-Baka Part 3*"));
	//////////////////////////////////////////////////////////////////////////
	txt txt_lval = L("Test CSTR made from TXT rvalue...") + i2t(6934) + t1;
	const char *conv_txt = txt_lval;
	if(T("CSTR FROM TXT ADDITION RVALUE", cstr({ conv_txt, ~txt_lval }), L("Test CSTR made from TXT rvalue...6934-Baka Part 2")))
	{
		p|"conv_txt hex: "|txt2hex(txt_lval);
		p|N|I|txt_lval|I|" txt_lval size/true size: "|~txt_lval|S|!txt_lval|N;
	}/*Test CSTR made from TXT rvalue...6934-Baka Part 2*//*"Test CSTR made from TXT rvalue...6934-Baka Part 2"*/
	//////////////////////////////////////////////////////////////////////////

#ifndef COMARIZON
	t0 = L("-comp"), t1 = L("-comp");
	txt t2 = L("-compper"), t3 = L("-co$p"), t4 = (txt)'$', t5, t6 = (txt)'-';

	TBOOL("OP == TXT-TXT	|-comp| == |-comp|",	t0 == t1, true);
	TBOOL("OP == TXT-TXT	|-comp| == |-compper|",	t0 == t2, false);
	TBOOL("OP == TXT-TXT	|-comp| == |-co$p|",	t0 == t3, false);
	
	TBOOL("OP != TXT-TXT	|-comp| != |-comp|",	t0 != t1, false);
	TBOOL("OP != TXT-TXT	|-comp| != |-compper|",	t0 != t2, true);
	TBOOL("OP != TXT-TXT	|-comp| != |-co$p|",	t0 != t3, true);
	
	TBOOL("OP == TXT-CSTR	|-comp| == |-comp|",	t0 == L("-comp"),		true);
	TBOOL("OP == TXT-CSTR	|-comp| == |-compper|",	t0 == L("-compper"),	false);
	TBOOL("OP == TXT-CSTR	|-comp| == |-co$p|",	t0 == L("-co$p"),		false);
	
	TBOOL("OP != TXT-CSTR	|-comp| != |-comp|",	t0 != L("-comp"),		false);
	TBOOL("OP != TXT-CSTR	|-comp| != |-compper|",	t0 != L("-compper"),	true);
	TBOOL("OP != TXT-CSTR	|-comp| != |-co$p|",	t0 != L("-co$p"),		true);
	
	TBOOL("OP == CSTR-TXT	|-comp| == |-comp|",	t0 == L("-comp"),		true);
	TBOOL("OP == CSTR-TXT	|-comp| == |-compper|",	t0 == L("-compper"),	false);
	TBOOL("OP == CSTR-TXT	|-comp| == |-co$p|",	t0 == L("-co$p"),		false);
	
	TBOOL("OP != CSTR-TXT	|-comp| != |-comp|",	t0 != L("-comp"),		false);
	TBOOL("OP != CSTR-TXT	|-comp| != |-compper|",	t0 != L("-compper"),	true);
	TBOOL("OP != CSTR-TXT	|-comp| != |-co$p|",	t0 != L("-co$p"),		true);
	
	TBOOL("OP == TXT-CHAR	|-|	== |-|",		t6 == '-', true);
	TBOOL("OP == TXT-CHAR	|-comp| == |c|",	t0 == 'c', false);
	TBOOL("OP == TXT-CHAR	|$| == |-|",		t4 == '-', false);
	
	TBOOL("OP != TXT-CHAR	|-| != |-|",		t6 != '-', false);
	TBOOL("OP != TXT-CHAR	|-comp| != |c|",	t0 != 'c', true);
	TBOOL("OP != TXT-CHAR	|$| != |-|",		t4 != '-', true);
	
	TBOOL("OP == CHAR-TXT	|-| == |-|",		'-' == t6, true);
	TBOOL("OP == CHAR-TXT	|-comp| == |c|",	'c' == t0, false);
	TBOOL("OP == CHAR-TXT	|$| == |-|",		'-' == t4, false);
	
	TBOOL("OP != CHAR-TXT	|-| != |-|",		'-' != t6, false);
	TBOOL("OP != CHAR-TXT	|-comp| != |c|",	'c' != t0, true);
	TBOOL("OP != CHAR-TXT	|$| != |-|",		'-' != t4, true);
	
	TBOOL("OP == TXT-EMPTY	|-comp| == ||",	t0 == empty, false);
	TBOOL("OP == TXT-EMPTY	|| == ||",		t5 == empty, true);
	
	TBOOL("OP != TXT-EMPTY	|-comp| != ||",	t0 != empty, true);
	TBOOL("OP != TXT-EMPTY	|| != ||",		t5 != empty, false);
	
	TBOOL("OP == EMPTY-TXT	|-comp| == ||",	empty == t0, false);
	TBOOL("OP == EMPTY-TXT	|| == ||",		empty == t5, true);
	
	TBOOL("OP != EMPTY-TXT	|-comp| != ||",	empty != t0, true);
	TBOOL("OP != EMPTY-TXT	|| != ||",		empty != t5, false);
#endif
	
	txt sub_eq_tst = L("ABCDz-b3$f-414b-b@2e-826$a1bd__BAK__081bf9b-a6c1-4$54-a9a3-8b9a1221__END");
	
	TBOOL("TXTSEQ SUBSTRING EQUALITY 0", txtseq(sub_eq_tst, 0, L("ABCDz")), true);
	TBOOL("TXTSEQ SUBSTRING EQUALITY 1", txtseq(sub_eq_tst, 29, L("__BAK__")), true);
	TBOOL("TXTSEQ SUBSTRING EQUALITY 2", txtseq(sub_eq_tst, 67, L("__END")), true);
	TBOOL("TXTNEQ SUBSTRING NONEQUALITY 0", txtsneq(sub_eq_tst, 68, L("__END")), true);
	TBOOL("TXTNEQ SUBSTRING NONEQUALITY 1", txtsneq(sub_eq_tst, 29, L("__PAK__")), true);
	
	//////////////////////////////////////////////////////////////////////////
	//p|"Baka + ' ' + Mono: |" | (txt("Baka") + ' ' + "Mono") | '|' |N;
	//////////////////////////////////////////////////////////////////////////
	
	cstr tofind = L("This_is_tesuto___________searching_!baka_this_T_tesutoraptor_text_baka!");
	cstr tofind_case = L("THis_Is_tesuTO___________SEARChInG_!baKa_tHis_T_TeSuToRAPtOR_tEXt_BAKa!");
	txt fthis = L("This");
	txt ftesuto = L("tesuto");
	txt fbaka = L("baka!");
	txt fnone = L("NONSENSE");
	
	txt fnd_tst = tofind;
	txt fnd_tst_case = tofind_case;
	
	//p|"\nSEARCHING FROM BEG >>>>>>>>>>>>>>>>>>\n";
	
	if(T("FINDING FROM BEG 0", txtf(fnd_tst, 0, L("tesuto")), 8))
	{
		p|tofind|N;
		dispPos(txtf(fnd_tst, 0, L("tesuto")), txt(L("tesuto")), 8);
	}
	if(T("FINDING FROM BEG 1", txtf(fnd_tst, 0, ftesuto), 8))
	{
		p|tofind|N;
		dispPos(txtf(fnd_tst, 0, ftesuto), txt(ftesuto), 8);
	}
	if(T("FINDING FROM BEG 2", txtf(fnd_tst, 0, 'r'), 28))
	{
		p|tofind|N;
		dispPos(txtf(fnd_tst, 0, 'r'), txt('r'), 28);
	}
	if(T("FINDING FROM BEG 3", txtf(fnd_tst, 24, L("tesuto")), 48))
	{
		p|tofind|N;
		dispPos(txtf(fnd_tst, 24, L("tesuto")), txt(L("tesuto")), 48);
	}
	if(T("FINDING FROM BEG 4", txtf(fnd_tst, 24, ftesuto), 48))
	{
		p|tofind|N;
		dispPos(txtf(fnd_tst, 24, ftesuto), ftesuto, 48);
	}
	if(T("FINDING FROM BEG 5", txtf(fnd_tst, 44, 'r'), 54))
	{
		p|tofind|N;
		dispPos(txtf(fnd_tst, 44, 'r'), txt('r'), 54);
	}
	if(T("FINDING FROM BEG 6", txtf(fnd_tst, 14, 'a', 'z'), 25))
	{
		p|tofind|N;
		dispPos(txtf(fnd_tst, 14, 'a', 'z'), txt(L("a-z")), 25);
	}
	
	//p|"\nSEARCHING FROM end <<<<<<<<<<<<<<<<<<\n";
	
	if(T("FINDING FROM END 0", txtfe(fnd_tst, 0, L("tesuto")), NFND))
	{
		p|tofind|N;
		dispPos(txtfe(fnd_tst, 0, L("tesuto")), txt(L("tesuto")), NFND);
	}
	if(T("FINDING FROM END 1", txtfe(fnd_tst, 0, ftesuto), NFND))
	{
		p|tofind|N;
		dispPos(txtfe(fnd_tst, 0, ftesuto), txt(ftesuto), NFND);
	}
	if(T("FINDING FROM END 2", txtfe(fnd_tst, 0, 'r'), NFND))
	{
		p|tofind|N;
		dispPos(txtfe(fnd_tst, 0, 'r'), txt('r'), NFND);
	}
	if(T("FINDING FROM END 3", txtfe(fnd_tst, 24, L("tesuto")), 8))
	{
		p|tofind|N;
		dispPos(txtfe(fnd_tst, 24, L("tesuto")), txt(L("tesuto")), 8);
	}
	if(T("FINDING FROM END 4", txtfe(fnd_tst, 24, ftesuto), 8))
	{
		p|tofind|N;
		dispPos(txtfe(fnd_tst, 24, ftesuto), ftesuto, 8);
	}
	if(T("FINDING FROM END 5", txtfe(fnd_tst, 24, 'r'), NFND))
	{
		p|tofind|N;
		dispPos(txtfe(fnd_tst, 24, 'r'), txt('r'), NFND);
	}
	if(T("FINDING FROM END 6", txtfe(fnd_tst, 24, 'a', 'z'), 13))
	{
		p|tofind|N;
		dispPos(txtfe(fnd_tst, 24, 'a', 'z'), txt(L("a-z")), 13);
	}
	
	//p|"\nSEARCHING IN RANGE <<<<<<<<<<<<<<<<<<\n";
	
	if(T("FINDING IN RANGE 0", txtfr(fnd_tst, 0, 18, L("tesuto")), 8))
	{
		p|tofind|N;
		dispPos(txtfr(fnd_tst, 0, 18, L("tesuto")), txt(L("tesuto")), 8);
	}
	if(T("FINDING IN RANGE 1", txtfr(fnd_tst, 0, 18, ftesuto), 8))
	{
		p|tofind|N;
		dispPos(txtfr(fnd_tst, 0, 18, ftesuto), txt(ftesuto), 8);
	}
	if(T("FINDING IN RANGE 2", txtfr(fnd_tst, 0, 5, 'r'), NFND))
	{
		p|tofind|N;
		dispPos(txtfr(fnd_tst, 0, 5, 'r'), txt('r'), NFND);
	}
	if(T("FINDING IN RANGE 3", txtfr(fnd_tst, 24, 43, L("tesuto")), NFND))
	{
		p|tofind|N;
		dispPos(txtfr(fnd_tst, 24, 43, L("tesuto")), txt(L("tesuto")), NFND);
	}
	if(T("FINDING IN RANGE 4", txtfr(fnd_tst, 24, 43, ftesuto), NFND))
	{
		p|tofind|N;
		dispPos(txtfr(fnd_tst, 24, 43, ftesuto), ftesuto, NFND);
	}
	if(T("FINDING IN RANGE 5", txtfr(fnd_tst, 24, 44, 'r'), 28))
	{
		p|tofind|N;
		dispPos(txtfr(fnd_tst, 24, 44, 'r'), txt('r'), 28);
	}
	if(T("FINDING IN RANGE 6", txtfr(fnd_tst, 14, 24, 'a', 'z'), NFND))
	{
		p|tofind|N;
		dispPos(txtfr(fnd_tst, 14, 24, 'a', 'z'), txt(L("a-z")), NFND);
	}
	
	//p|"\nSEARCHING FROM BEG CASE INSENSITIVE >>>>>>>>>>>>>>>>>>\n";
	
	if(T("FINDING FROM BEG CASE INSENSE 0", txtfci(fnd_tst_case, 0, L("tesuto")), 8))
	{
		p|tofind|N;
		dispPos(txtfci(fnd_tst_case, 0, L("tesuto")), txt(L("tesuto")), 8);
	}
	if(T("FINDING FROM BEG CASE INSENSE 1", txtfci(fnd_tst_case, 0, ftesuto), 8))
	{
		p|tofind|N;
		dispPos(txtfci(fnd_tst_case, 0, ftesuto), txt(ftesuto), 8);
	}
	if(T("FINDING FROM BEG CASE INSENSE 2", txtfci(fnd_tst_case, 0, 'r'), 28))
	{
		p|tofind|N;
		dispPos(txtfci(fnd_tst_case, 0, 'r'), txt('r'), 28);
	}
	if(T("FINDING FROM BEG CASE INSENSE 3", txtfci(fnd_tst_case, 24, L("tesuto")), 48))
	{
		p|tofind|N;
		dispPos(txtfci(fnd_tst_case, 24, L("tesuto")), txt(L("tesuto")), 48);
	}
	if(T("FINDING FROM BEG CASE INSENSE 4", txtfci(fnd_tst_case, 24, ftesuto), 48))
	{
		p|tofind|N;
		dispPos(txtfci(fnd_tst_case, 24, ftesuto), ftesuto, 48);
	}
	if(T("FINDING FROM BEG CASE INSENSE 5", txtfci(fnd_tst_case, 44, 'r'), 54))
	{
		p|tofind|N;
		dispPos(txtfci(fnd_tst_case, 44, 'r'), txt('r'), 54);
	}
	
	//p|"\nSEARCHING FROM BEG ANY CHAR >>>>>>>>>>>>>>>>>>\n";
	txt fnd_any_char = L("_83c3415-b3$f-414b-b@2e-826$a1bd7789a081bf9b-a6c1-4$54-a9a3-8b9a1221@@d_");
	
	ui64 fres = txtfa(fnd_any_char, 0, L("_$@a"));
	T("FINDING FROM BEG ANY CHAR 0", fres, 0);
	fres = txtfa(fnd_any_char, fres+1, L("_$@a"));
	T("FINDING FROM BEG ANY CHAR 1", fres, 11);
	fres = txtfa(fnd_any_char, fres+1, L("_$@a"));
	T("FINDING FROM BEG ANY CHAR 2", fres, 20);
	fres = txtfa(fnd_any_char, fres+1, L("_$@a"));
	T("FINDING FROM BEG ANY CHAR 3", fres, 27);
	fres = txtfa(fnd_any_char, fres+1, L("_$@a"));
	T("FINDING FROM BEG ANY CHAR 4", fres, 28);
	fres = txtfa(fnd_any_char, fres+1, L("_$@a"));
	T("FINDING FROM BEG ANY CHAR 5", fres, 36);
	fres = txtfa(fnd_any_char, fres+1, L("_$@a"));
	T("FINDING FROM BEG ANY CHAR 6", fres, 45);
	fres = txtfa(fnd_any_char, fres+1, L("_$@a"));
	T("FINDING FROM BEG ANY CHAR 7", fres, 51);
	fres = txtfa(fnd_any_char, fres+1, L("_$@a"));
	T("FINDING FROM BEG ANY CHAR 8", fres, 55);
	fres = txtfa(fnd_any_char, fres+1, L("_$@a"));
	T("FINDING FROM BEG ANY CHAR 9", fres, 57);
	fres = txtfa(fnd_any_char, fres+1, L("_$@a"));
	T("FINDING FROM BEG ANY CHAR 10", fres, 63);
	fres = txtfa(fnd_any_char, fres+1, L("_$@a"));
	T("FINDING FROM BEG ANY CHAR 11", fres, 68);
	fres = txtfa(fnd_any_char, fres+1, L("_$@a"));
	T("FINDING FROM BEG ANY CHAR 12", fres, 69);
	fres = txtfa(fnd_any_char, fres+1, L("_$@a"));
	T("FINDING FROM BEG ANY CHAR 13", fres, 71);
	
	///////////////////////////////////////////////////////////////////////
	
	#define IOT_SZ 61
	cstr toins = L("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!");
	txt ins = L("<|||>");
	bool ins_ovr_failed = false;
	
	for(ui64 i = 0; i < IOT_SZ; ++i)
	{
		txt ins_tst = toins;
		txti(ins_tst, i, ins);
		if(TS(L("INSERTION TEST TXT I") + i2t(i), ins_tst, insert_tst_arr[i]))
		{
			ins_ovr_failed = true;
		}
	}
	for(ui64 i = 0; i < IOT_SZ; ++i)
	{
		txt ins_tst = toins;
		txti(ins_tst, i, L("<|||>"));
		if(TS(L("INSERTION TEST CSTR I") + i2t(i), ins_tst, insert_tst_arr[i]))
		{
			ins_ovr_failed = true;
		}
	}
	for(ui64 i = 0; i < IOT_SZ; ++i)
	{
		txt ins_tst = toins;
		txti(ins_tst, i, '$');
		if(TS(L("INSERTION TEST CHAR I") + i2t(i), ins_tst, insert_char_tst_arr[i]))
		{
			ins_ovr_failed = true;
		}
	}
	
	TBOOL("INSERTION TESTS", ins_ovr_failed, false);
	
	for(ui64 i = 0; i < IOT_SZ; ++i)
	{
		txt ins_tst = toins;
		txto(ins_tst, i, ins);
		if(TS(L("INSERTION TEST TXT I") + i2t(i), ins_tst, overwr_tst_arr[i]))
		{
			ins_ovr_failed = true;
		}
	}
	for(ui64 i = 0; i < IOT_SZ; ++i)
	{
		txt ins_tst = toins;
		txto(ins_tst, i, L("<|||>"));
		if(TS(L("INSERTION TEST CSTR I") + i2t(i), ins_tst, overwr_tst_arr[i]))
		{
			ins_ovr_failed = true;
		}
	}
	for(ui64 i = 0; i < IOT_SZ; ++i)
	{
		txt ins_tst = toins;
		txto(ins_tst, i, '$');
		if(TS(L("INSERTION TEST CHAR I") + i2t(i), ins_tst, overwr_char_tst_arr[i]))
		{
			ins_ovr_failed = true;
		}
	}
	
	TBOOL("OVERWRITING TESTS", ins_ovr_failed, false);
	
	txt overwrite_in_big_buf = 1024;
	overwrite_in_big_buf = L("012345678");
	txto(overwrite_in_big_buf, 4, L("____________REP____________"));
	T("OVERWRITING IN BIG BUFFER", overwrite_in_big_buf, L("0123____________REP____________"));
	
	txt tst_path = L("D:\\foo\\baka\\bar\\mod\\bot\\pot\\spot\\omicron.html");
	T("OVERWRITING ALL CHARACTERS", txtoa(tst_path, '\\', '/'), L("D:/foo/baka/bar/mod/bot/pot/spot/omicron.html"));
	
	///////////////////////////////////////////////////////////////////////

	txt rep_tst = L("0123456789_____0123456789");
	txt rep_txt = L("|REPLACED|");
	txt rep_empty;
	txt rep = rep_tst;
	
	T("REPLACE POSITIONS TXT 0 3", txtrp(rep, 10, 14, rep_txt), L("0123456789|REPLACED|0123456789"));
	rep = rep_tst;
	T("REPLACE POSITIONS CSTR 0 3", txtrp(rep, 15, TEND, L("|REPLACED|")), L("0123456789_____|REPLACED|"));
	rep = rep_tst;
	T("REPLACE POSITIONS CHAR 0 3", txtrp(rep, 0, 9, '$'), L("$_____0123456789"));
	rep = rep_tst;
	
	T("REPLACE TXT 0 3", txtr(rep, 0, 3, rep_txt), L("|REPLACED|3456789_____0123456789"));
	rep = rep_tst;
	T("REPLACE CSTR 0 3", txtr(rep, 0, 3, L("|REPLACED|")), L("|REPLACED|3456789_____0123456789"));
	rep = rep_tst;
	T("REPLACE CHAR 0 3", txtr(rep, 0, 3, '$'), L("$3456789_____0123456789"));
	rep = rep_tst;
	
	T("REPLACE TXT 0 TEND", txtr(rep, 0, TEND, rep_txt), L("|REPLACED|"));
	rep = rep_tst;
	T("REPLACE CSTR 0 TEND", txtr(rep, 0, TEND, L("|REPLACED|")), L("|REPLACED|"));
	rep = rep_tst;
	T("REPLACE CHAR 0 TEND", txtr(rep, 0, TEND, '$'), L("$"));
	rep = rep_tst;
	
	T("REPLACE TXT 10 5", txtr(rep, 10, 5, rep_txt), L("0123456789|REPLACED|0123456789"));
	rep = rep_tst;
	T("REPLACE CSTR 10 5", txtr(rep, 10, 5, L("|REPLACED|")), L("0123456789|REPLACED|0123456789"));
	rep = rep_tst;
	T("REPLACE CHAR 10 5", txtr(rep, 10, 5, '$'), L("0123456789$0123456789"));
	rep = rep_tst;
	
	T("REPLACE TXT 10 0", txtr(rep, 10, 0, rep_txt), L("0123456789|REPLACED|_____0123456789"));
	rep = rep_tst;
	T("REPLACE CSTR 10 0", txtr(rep, 10, 0, L("|REPLACED|")), L("0123456789|REPLACED|_____0123456789"));
	rep = rep_tst;
	T("REPLACE CHAR 10 0", txtr(rep, 10, 0, '$'), L("0123456789$_____0123456789"));
	rep = rep_tst;
	
	T("REPLACE TXT 10 TEND", txtr(rep, 10, TEND, rep_txt), L("0123456789|REPLACED|"));
	rep = rep_tst;
	T("REPLACE CSTR 10 TEND", txtr(rep, 10, TEND, L("|REPLACED|")), L("0123456789|REPLACED|"));
	rep = rep_tst;
	T("REPLACE CHAR 10 TEND", txtr(rep, 10, TEND, '$'), L("0123456789$"));
	rep = rep_tst;
	
	T("REPLACE TXT ~rep-1 0", txtr(rep, ~rep-1, 0, rep_txt), L("0123456789_____012345678|REPLACED|9"));
	rep = rep_tst;
	T("REPLACE CSTR ~rep-1 0", txtr(rep, ~rep-1, 0, L("|REPLACED|")), L("0123456789_____012345678|REPLACED|9"));
	rep = rep_tst;
	T("REPLACE CHAR ~rep-1 0", txtr(rep, ~rep-1, 0, '$'), L("0123456789_____012345678$9"));
	rep = rep_tst;
	
	T("REPLACE TXT ~rep-3 6969", txtr(rep, ~rep-3, 6969, rep_txt), L("0123456789_____0123456|REPLACED|"));
	rep = rep_tst;
	T("REPLACE CSTR ~rep-3 6969", txtr(rep, ~rep-3, 6969, L("|REPLACED|")), L("0123456789_____0123456|REPLACED|"));
	rep = rep_tst;
	T("REPLACE CHAR ~rep-3 6969", txtr(rep, ~rep-3, 6969, '$'), L("0123456789_____0123456$"));
	rep = rep_tst;
	
	T("REPLACE EMPTY TXT 10 5", txtr(rep, 10, 5, rep_empty), L("01234567890123456789"));
	rep = rep_tst;
	T("REPLACE EMPTY CSTR 10 5", txtr(rep, 10, 5, L("")), L("01234567890123456789"));
	rep = rep_tst;
	// Replacing with \0 is mistake, as size wont get updated, unless used with trimm operator!
	// Use txtd() for safe removal of text parts!
	
	T("DELETE 10 5", txtd(rep, 10, 5), L("01234567890123456789"));
	rep = rep_tst;
	T("DELETE 3 TEND", txtd(rep, 3, TEND), L("012"));
	rep = rep_tst;
	T("DELETE ~rep-1 1", txtd(rep, ~rep-1, 1), L("0123456789_____012345678"));
	rep = rep_tst;
	T("DELETE POSITIONS", txtdp(rep, 10, 14), L("01234567890123456789"));
	rep = rep_tst;
	
	T("REPLACE TXT ~rep-3 ~rep", txtr(rep, ~rep-3, ~rep, rep_txt), L("0123456789_____0123456|REPLACED|"));
	rep = rep_tst;
	T("REPLACE CSTR ~rep-3 ~rep", txtr(rep, ~rep-3, ~rep, L("|REPLACED|")), L("0123456789_____0123456|REPLACED|"));
	rep = rep_tst;
	T("REPLACE CHAR ~rep-3 ~rep", txtr(rep, ~rep-3, ~rep, '$'), L("0123456789_____0123456$"));
	rep = rep_tst;
	T("DELETE 3 ~rep", txtd(rep, 3, ~rep), L("012"));
	rep = rep_tst;
	T("DELETE POSITIONS 10 ~rep", txtdp(rep, 10, ~rep), L("0123456789"));
	rep = rep_tst;
	
#endif
	
#ifndef DEBUG
	bool t2ii2t_res = t2ii2tTest();
	p|N;
	TBOOL("TEXT 2 INT INT 2 TEXT", t2ii2t_res, false);
#endif
	
	T("I2HEX UI64 BEEF", i2h((ui64)0xDEADBEEF), L("00000000DEADBEEF"));
	T("I2HEX UI32 BEEF", i2h((ui32)0xDEADBEEF), L("DEADBEEF"));
	T("I2HEX UI16 BEEF", i2h((ui16)0xBEEF), L("BEEF"));
	T("I2HEX UI8 EF", b2h((ui8)0xEF), L("EF"));
	
	T("HEX2I UI64 BEEF", h2i(txt(L("00000000DEADBEEF"))), 0xDEADBEEF);
	T("HEX2I UI32 BEEF", h2i(txt(L("DEADBEEF"))), 0xDEADBEEF);
	T("HEX2I UI16 BEEF", h2i(txt(L("BEEF"))), 0xBEEF);
	T("HEX2I UI8 EF", h2i(txt(L("EF"))), 0xEF);
	
	T("I2TXT UI64 MAX", i2t(UI64_MAX), L("18446744073709551615"));
	T("I2TXT UI32 MAX", i2t(UI32_MAX), L("4294967295"));
	T("I2TXT UI16 MAX", i2t(UI16_MAX), L("65535"));
	T("I2TXT UI8 MAX", i2t(UI8_MAX), L("255"));
	
	T("I2TXT I64 MAX", i2t(I64_MAX), L("9223372036854775807"));
	T("I2TXT I32 MAX", i2t(I32_MAX), L("2147483647"));
	T("I2TXT I16 MAX", i2t(I16_MAX), L("32767"));
	T("I2TXT I8 MAX", i2t(I8_MAX), L("127"));
	
	T("I2TXT I64 MIN", i2t(I64_MIN), L("-9223372036854775808"));
	T("I2TXT I64 MIN+1", i2t(I64_MIN+1), L("-9223372036854775807"));
	T("I2TXT I32 MIN", i2t(I32_MIN), L("-2147483648"));
	T("I2TXT I32 MIN+1", i2t(I32_MIN+1), L("-2147483647"));
	T("I2TXT I16 MIN", i2t(I16_MIN), L("-32768"));
	T("I2TXT I16 MIN+1", i2t(I16_MIN+1), L("-32767"));
	T("I2TXT I8 MIN", i2t(I8_MIN), L("-128"));
	T("I2TXT I8 MIN+1", i2t(I8_MIN+1), L("-127"));
	
	T("TXT2I UI64 MAX", t2i(L("18446744073709551615")), UI64_MAX);
	T("TXT2I UI32 MAX", t2i(L("4294967295")), UI32_MAX);
	T("TXT2I UI16 MAX", t2i(L("65535")), UI16_MAX);
	T("TXT2I UI8 MAX", t2i(L("255")), UI8_MAX);
	
	T("TXT2I I64 MAX", (i64)t2i(L("9223372036854775807")), I64_MAX);
	T("TXT2I I32 MAX", t2i(L("2147483647")), I32_MAX);
	T("TXT2I I16 MAX", t2i(L("32767")), I16_MAX);
	T("TXT2I I8 MAX", t2i(L("127")), I8_MAX);
	
	T("TXT2I I64 MIN", t2i(L("-9223372036854775808")), (ui64)I64_MIN);
	T("TXT2I I32 MIN", t2i(L("-2147483648")), (ui64)I32_MIN);
	T("TXT2I I16 MIN", t2i(L("-32768")), (ui64)I16_MIN);
	T("TXT2I I8 MIN", t2i(L("-128")), (ui64)I8_MIN);
	
	ui64 i2hex_compact_ui64 = 0x4269;
	ui64 i2hex_compact_ui64_zero = 0x0;
	ui64 i2hex_compact_ui64_max = UI64_MAX;
	ui32 i2hex_compact_ui32 = 0x34;
	ui16 i2hex_compact_ui16 = 0xA;
	ui8 i2hex_compact_ui8 = 0xF;
	
	T("I2HEX COMPACT UI64", i2hc(i2hex_compact_ui64), L("4269"));
	T("I2HEX COMPACT UI64 ZERO", i2hc(i2hex_compact_ui64_zero), L("0"));
	T("I2HEX COMPACT UI64 MAX", i2hc(i2hex_compact_ui64_max), L("FFFFFFFFFFFFFFFF"));
	T("I2HEX COMPACT UI32", i2hc(i2hex_compact_ui32), L("34"));
	T("I2HEX COMPACT UI16", i2hc(i2hex_compact_ui16), L("A"));
	T("I2HEX COMPACT UI8", i2hc(i2hex_compact_ui8), L("F"));
	
	TBOOL("TXT NOT UNSIGNED INT 0", txtnui(L("bak2234")), true);
	TBOOL("TXT NOT UNSIGNED INT 1", txtnui(L("693442")), false);
	TBOOL("TXT NOT SIGNED INT 0", txtnsi(L("-234")), false);
	TBOOL("TXT NOT SIGNED INT 1", txtnsi(L("-6934~42")), true);
	TBOOL("TXT NOT SIGNED INT 2", txtnsi(L("69F442")), true);
	TBOOL("TXT NOT HEX INT 0", txtnhi(L("FF34AA")), false);
	TBOOL("TXT NOT HEX INT 1", txtnhi(L("A93-04F2")), true);
	
	//////////////////////////////////// TOLOW/UPPERCASE TEST ///////////////////////////////////////
	
	txt to_low_test =			L("LOREM IPsUM DOLOR SIT aMET, CONSEcTETUR ADIPiSCING ELIT. P[LL]NTESqUE UT SUS__PIT MI, VEL CONDIMenTUM MetUS\t");
	const txt to_low_test_res =	L("lorem ipsum dolor sit amet, consectetur adipiscing elit. p[ll]ntesque ut sus__pit mi, vel condimentum metus\t");
	txt to_up_test =			L("Lorem Ipsum dolor sit Amet Consectetur adipiscing elit p{ll}ntesque Ut suscipit M~~vel condi012tum metus\t");
	const txt to_up_test_res =	L("LOREM IPSUM DOLOR SIT AMET CONSECTETUR ADIPISCING ELIT P{LL}NTESQUE UT SUSCIPIT M~~VEL CONDI012TUM METUS\t");
	
	t2low(to_low_test);
	t2up(to_up_test);
	
	T("TO LOWERCASE", to_low_test, to_low_test_res);
	T("TO UPPERCASE", to_up_test, to_up_test_res);
	
	//////////////////////////////////// SUBSTEXTS TEST ///////////////////////////////////////
	
	txt subtxt_src = L("-----------------------EXTRACT-ME-SENPAI!----------------");
	txt subtxt;
	
	T("SUBTEXT NUM OF CHARS", txts(subtxt_src, 23, 18), L("EXTRACT-ME-SENPAI!"));
	T("SUBTEXT POSITIONS", txtsp(subtxt_src, 23, 40), L("EXTRACT-ME-SENPAI!"));
	txts(subtxt, subtxt_src, 23, 18);
	T("SET SUBTEXT NUM OF CHARS", subtxt, L("EXTRACT-ME-SENPAI!"));
	txtclr(subtxt);
	txtsp(subtxt, subtxt_src, 23, 40);
	T("SET SUBTEXT POSITIONS", subtxt, L("EXTRACT-ME-SENPAI!"));
	
	/////////////////////////// ZERO TERMINATION CORRECTNESS TEST /////////////////////////////
	
	cstr zero_term_cstr = L("I. AM. ZERO. AND. I. AM. TERMINATED!!!");
	txt zero_term = zero_term_cstr;
	
	cstr zero_concat_big_cstr = L("--------------------THIS-IS-MUCH-BIGGER-THAN-BASE-TEXT--------------------");
	cstr zero_concat_smol_cstr = L("imsmol");
	txt zero_concat_big = zero_concat_big_cstr;
	txt zero_concat_smol = zero_concat_smol_cstr;
	
	txt zero_construct_txt = zero_term;
	T("ZERO TERMINATION CONSTRUCT TXT", getTerminator(zero_construct_txt), 0);
	txt zero_construct_cstr = zero_term_cstr;
	T("ZERO TERMINATION CONSTRUCT CSTR", getTerminator(zero_construct_cstr), 0);
	
	ui64 zero_sz_ui64 = 42;
	txt zero_construct_ui64 = zero_sz_ui64;
	T("ZERO TERMINATION CONSTRUCT UI64", getTerminator(zero_construct_ui64), 0);
	i64 zero_sz_i64 = 42;
	txt zero_construct_i64 = zero_sz_i64;
	T("ZERO TERMINATION CONSTRUCT I64", getTerminator(zero_construct_i64), 0);
	i32 zero_sz_i32 = 42;
	txt zero_construct_i32 = zero_sz_i32;
	T("ZERO TERMINATION CONSTRUCT I32", getTerminator(zero_construct_i32), 0);
	
	txt zero_construct_char = (txt)'X';
	T("ZERO TERMINATION CONSTRUCT CHAR", getTerminator(zero_construct_char), 0);
	
	
	txt zero_assign = zero_term;
	T("ZERO TERMINATION ASSIGN TXT", getTerminator(zero_assign), 0);
	zero_assign = zero_term_cstr;
	T("ZERO TERMINATION ASSIGN CSTR", getTerminator(zero_assign), 0);
	
	zero_assign = zero_sz_ui64;
	T("ZERO TERMINATION ASSIGN UI64", getTerminator(zero_assign), 0);
	zero_assign = zero_sz_i64;
	T("ZERO TERMINATION ASSIGN I64", getTerminator(zero_assign), 0);
	zero_assign = zero_sz_i32;
	T("ZERO TERMINATION ASSIGN I32", getTerminator(zero_assign), 0);
	
	zero_assign = (txt)'X';
	T("ZERO TERMINATION ASSIGN CHAR", getTerminator(zero_assign), 0);
	
	
	txt zero_manip = zero_term;
	zero_manip += zero_concat_big;
	T("ZERO TERMINATION CONCAT OPERATOR TXT REALLOC", getTerminator(zero_manip), 0);
	zero_manip += zero_concat_smol;
	T("ZERO TERMINATION CONCAT OPERATOR TXT", getTerminator(zero_manip), 0);
	
	zero_manip = zero_term;
	zero_manip += zero_concat_big_cstr;
	T("ZERO TERMINATION CONCAT OPERATOR CSTR REALLOC", getTerminator(zero_manip), 0);
	zero_manip += zero_concat_smol_cstr;
	T("ZERO TERMINATION CONCAT OPERATOR CSTR", getTerminator(zero_manip), 0);
	
	zero_manip = zero_term;
	zero_manip += 'X';
	T("ZERO TERMINATION CONCAT OPERATOR CHAR REALLOC", getTerminator(zero_manip), 0);
	zero_manip += 'X';
	T("ZERO TERMINATION CONCAT OPERATOR CHAR", getTerminator(zero_manip), 0);
	
	
	txttrm(zero_manip);
	T("ZERO TERMINATION TRIMM", getTerminator(zero_manip), 0);
	
	
	txt zero_big_manip = 1024;
	zero_big_manip = zero_term;
	zero_manip = zero_term;
	txti(zero_manip, 10, zero_concat_big_cstr);
	T("ZERO TERMINATION INSERT TXT REALLOC", getTerminator(zero_manip), 0);
	txti(zero_big_manip, 10, zero_concat_smol_cstr);
	T("ZERO TERMINATION INSERT TXT", getTerminator(zero_big_manip), 0);
	zero_big_manip = zero_term;
	zero_manip = zero_term;
	txti(zero_manip, 10, zero_concat_big_cstr);
	T("ZERO TERMINATION INSERT CSTR REALLOC", getTerminator(zero_manip), 0);
	txti(zero_big_manip, 10, zero_concat_smol_cstr);
	T("ZERO TERMINATION INSERT CSTR", getTerminator(zero_big_manip), 0);
	zero_big_manip = zero_term;
	zero_manip = zero_term;
	txti(zero_manip, 10, 'X');
	T("ZERO TERMINATION INSERT CHAR REALLOC", getTerminator(zero_manip), 0);
	txti(zero_big_manip, 10, 'X');
	T("ZERO TERMINATION INSERT CHAR", getTerminator(zero_big_manip), 0);
	
	zero_big_manip = zero_term;
	zero_manip = zero_term;
	txto(zero_manip, 10, zero_concat_big_cstr);
	T("ZERO TERMINATION OVERWRITE TXT REALLOC", getTerminator(zero_manip), 0);
	txto(zero_big_manip, 10, zero_concat_smol_cstr);
	T("ZERO TERMINATION OVERWRITE TXT", getTerminator(zero_big_manip), 0);
	zero_big_manip = zero_term;
	zero_manip = zero_term;
	txto(zero_manip, 10, zero_concat_big_cstr);
	T("ZERO TERMINATION OVERWRITE CSTR REALLOC", getTerminator(zero_manip), 0);
	txto(zero_big_manip, 10, zero_concat_smol_cstr);
	T("ZERO TERMINATION OVERWRITE CSTR", getTerminator(zero_big_manip), 0);
	zero_big_manip = zero_term;
	zero_manip = zero_term;
	txto(zero_manip, 10, 'X');
	T("ZERO TERMINATION OVERWRITE CHAR REALLOC", getTerminator(zero_manip), 0);
	txto(zero_big_manip, 10, 'X');
	T("ZERO TERMINATION OVERWRITE CHAR", getTerminator(zero_big_manip), 0);
	
	zero_big_manip = zero_term;
	zero_manip = zero_term;
	txtr(zero_manip, 10, 1, zero_concat_big_cstr);
	T("ZERO TERMINATION REPLACE TXT REALLOC", getTerminator(zero_manip), 0);
	txtr(zero_big_manip, 10, 1, zero_concat_smol_cstr);
	T("ZERO TERMINATION REPLACE TXT", getTerminator(zero_big_manip), 0);
	zero_big_manip = zero_term;
	zero_manip = zero_term;
	txtr(zero_manip, 10, 1, zero_concat_big_cstr);
	T("ZERO TERMINATION REPLACE CSTR REALLOC", getTerminator(zero_manip), 0);
	txtr(zero_big_manip, 10, 1, zero_concat_smol_cstr);
	T("ZERO TERMINATION REPLACE CSTR", getTerminator(zero_big_manip), 0);
	zero_big_manip = zero_term;
	zero_manip = zero_term;
	txtr(zero_manip, 10, 1, 'X');
	T("ZERO TERMINATION REPLACE CHAR REALLOC", getTerminator(zero_manip), 0);
	txtr(zero_big_manip, 10, 1, 'X');
	T("ZERO TERMINATION REPLACE CHAR", getTerminator(zero_big_manip), 0);
	
	zero_manip = zero_term;
	txtd(zero_manip, 10, TEND);
	T("ZERO TERMINATION DELETE TEND", getTerminator(zero_manip), 0);
	zero_manip = zero_term;
	txtd(zero_manip, 10, 6);
	T("ZERO TERMINATION DELETE MID", getTerminator(zero_manip), 0);
	zero_manip = zero_term;
	txtdl(zero_manip);
	txtdl(zero_manip);
	txtdl(zero_manip);
	T("ZERO TERMINATION DELETE LAST", getTerminator(zero_manip), 0);
	zero_manip = zero_term;
	txtdp(zero_manip, 10, 15);
	T("ZERO TERMINATION DELETE POSITIONS", getTerminator(zero_manip), 0);
	
	
	zero_manip = zero_term;
	txtssz(zero_manip, 12);
	T("ZERO TERMINATION SET SIZE", getTerminator(zero_manip), 0);
	zero_manip = zero_term;
	txtclr(zero_manip);
	T("ZERO TERMINATION CLEAR", getTerminator(zero_manip), 0);
	zero_manip = zero_term;
	txtz(zero_manip);
	T("ZERO TERMINATION ZERO", getTerminator(zero_manip), 0);
	zero_manip = zero_term;
	txtadd(zero_manip, zero_term_cstr.t, zero_term_cstr.s);
	T("ZERO TERMINATION ADD", getTerminator(zero_manip), 0);
	
	
	T("ZERO TERMINATION SUBTEXT NUM OF CHARS", getTerminator(txts(subtxt_src, 23, 18)), 0);
	T("ZERO TERMINATION SUBTEXT POSITIONS", getTerminator(txtsp(subtxt_src, 23, 40)), 0);
	txtclr(subtxt);
	txts(subtxt, subtxt_src, 23, 18);
	T("ZERO TERMINATION SET SUBTEXT NUM OF CHARS", getTerminator(subtxt), 0);
	txtclr(subtxt);
	txtsp(subtxt, subtxt_src, 23, 40);
	T("ZERO TERMINATION SET SUBTEXT POSITIONS", getTerminator(subtxt), 0);
	
	/////////////////////////// ZERO TERMINATION CORRECTNESS TEST /////////////////////////////
	
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
	
	if(goToTestFail())
	{
		p|TB|P;
	}

//#define PROFILING_ON
#ifdef PROFILING_ON
	SWSET
	for(ui64 i = 0; i < 34000; ++i)
	{
		t2low(to_low_test);
	}
	SWSTOP
	SWSET
	for(ui64 i = 0; i < 34000; ++i)
	{
		t2up(to_low_test);
	}
	SWSTOP
	
	p|TM;
	p|TCP(0)|TCP(0)	 |TCP(8)  |TCP(0);
	p|"  "|TAC|R|"TO LOWER"|  ""  |G|"TO UPPER"|D|TN|"  ";
	SWPDIFF
	p|TE;
	
	SWRESET
	
	p|N | "!THE ULTIMATE SHOWDOWN!" |N;
	p|"SIZEOF(STDBS): " | sizeof(std::string) |N;
	p|"SIZEOF(TXT):   " | sizeof(txt) |N |N;
	
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	
	test();
#endif
	
	p|N|N|N|N|TB|P;
	
	return 0;
}

#ifdef PROFILING_ON
///////////////////////////////////////////////////////////////////////////////////////////////
char lorem[2048];
const char *lorem_lit = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque ut suscipit mi, vel condimentum metus. Etiam vestibulum dapibus fermentum. Vivamus in maximus velit. Donec tempor turpis justo. Duis luctus id risus vitae accumsan. Duis volutpat tincidunt felis, non ullamcorper augue cursus quis. Morbi maximus, odio at pellentesque eleifend, erat magna accumsan risus, sollicitudin aliquet est nulla eu augue. Donec lectus nulla, volutpat eget diam at, egestas sodales neque. Sed interdum libero eget semper posuere. Interdum et malesuada fames ac ante ipsum primis in faucibus. In odio urna, ultrices in commodo in, sagittis fringilla elit. Sed non luctus ligula."

"Nullam condimentum vitae turpis non tincidunt. Suspendisse vulputate leo ut pharetra viverra. Fusce varius purus sed quam vestibulum, non ullamcorper odio volutpat. Curabitur interdum tincidunt magna eget aliquet. Aliquam sit amet leo quis tellus eleifend tristique. Donec non risus massa. Nullam tincidunt sollicitudin sodales."

"Cras rhoncus malesuada ligula, vitae sodales metus luctus sit amet. Interdum et malesuada fames ac ante ipsum primis in faucibus. Mauris eleifend neque vitae tortor semper condimentum. Phasellus aliquet neque nisl, ut auctor dui varius ac. Cras ut metus neque. Nunc consequat, leo ut lacinia venenatis, nisi orci hendrerit ex, ut lacinia sapien augue quis magna. Proin scelerisque at ex eu condimentum. Quisque ac condimentum quam. Vestibulum a pulvinar dolor. Nunc sodales lacinia varius. Cras luctus leo dui, quis lacinia quam ornare tempus. Maecenas magna libero, scelerisque quis pellentesque eu, efficitur sed magna. Mauris vestibulum lobortis sagittis. Vivamus mollis lacus ut risus vehicula pellentesque. Suspendisse a blandit augue.HA! DIDNT EXPECT DA !BAKA! HERE?!";

char lorem_sm[416];
const char *lorem_sm_lit = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque ut suscipit mi, vel condimentum metus. Etiam vestibulum dapibus fermentum. Vivamus in maximus velit. Donec tempor turpis justo. Duis luctus id risus vitae accumsan. Duis volutpat tincidunt felis, non ullamcorper augue cursus quis. Morbi maximus, odio at pellentesque eleifend, erat magna accumsan risus, sollicitudin aliquet est nulla eu augue.";

char chars_100[128];
const char *chars_100_lit = "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";

std::string lorem_std = lorem;
txt lorem_txt = lorem;

std::string char_std = "$";
txt char_txt = '$';

#ifdef DEBUG
	#define DBGM 100
#else
	#define DBGM 1
#endif
	
#define RUN_TEST(x,y) tst_nms[tst_id++]=(#x);p|S(50)|"\r"|(#x)|"...\r"; SWSET tst_cyc=(y);for(ui64 i = 0; i < tst_cyc; ++i) {
#define MID_TEST } SWSTOP SWSET for(ui64 i = 0; i < tst_cyc; ++i) {
#define END_TEST } SWSTOP

// =======================================================================================================
void __declspec(noinline) stdAllocCstrS1770()
{
	volatile std::string s0 = lorem;
}
void __declspec(noinline) txtAllocCstrS1770()
{
	volatile txt s0 = lorem;
}
// =======================================================================================================
void __declspec(noinline) stdAllocTxtS1770()
{
	std::string s0 = lorem_std;
	
	for(ui64 i = 0; i < s0.size(); ++i)
	{
		s0[i] = (char)(GetTickCount() % 127);
	}
	
	volatile char *c = (volatile char *)HeapAlloc(GetProcessHeap(), 0, s0.size());
	memcpy((void *)c, s0.c_str(), s0.size());
	HeapFree(GetProcessHeap(), 0, (void *)c);
}
void __declspec(noinline) txtAllocTxtS1770()
{
	txt s0 = lorem_txt;
	
	for(ui64 i = 0; i < ~s0; ++i)
	{
		s0[i] = (char)(GetTickCount() % 127);
	}
	
	volatile char *c = (volatile char *)HeapAlloc(GetProcessHeap(), 0, ~s0);
	memcpy((void *)c, s0, ~s0);
	HeapFree(GetProcessHeap(), 0, (void *)c);
}
// =======================================================================================================
void __declspec(noinline) stdAllocChar()
{
	volatile char c0[2];
	volatile char c1[2];
	volatile char c2[2];
	volatile char c3[2];
	
	c0[0] = (GetTickCount() % 127);
	c1[0] = (GetTickCount() % 127);
	c2[0] = (GetTickCount() % 127);
	c3[0] = (GetTickCount() % 127);
	c0[1] = 0, c1[1] = 0, c2[1] = 0, c3[1] = 0;
	
	std::string s0 = (const char *)c0;
	std::string s1 = (const char *)c1;
	std::string s2 = (const char *)c2;
	std::string s3 = (const char *)c3;
	volatile char c;
	c = s0[0], c = s1[0], c = s2[0], c = s3[0];
}
void __declspec(noinline) txtAllocChar()
{
	volatile char c0[2];
	volatile char c1[2];
	volatile char c2[2];
	volatile char c3[2];
	
	c0[0] = (GetTickCount() % 127);
	c1[0] = (GetTickCount() % 127);
	c2[0] = (GetTickCount() % 127);
	c3[0] = (GetTickCount() % 127);
	c0[1] = 0, c1[1] = 0, c2[1] = 0, c3[1] = 0;
	
	txt s0 = (const char *)c0;
	txt s1 = (const char *)c1;
	txt s2 = (const char *)c2;
	txt s3 = (const char *)c3;
	volatile char c;
	c = s0[0], c = s1[0], c = s2[0], c = s3[0];
}
// =======================================================================================================
void __declspec(noinline) stdAllocTxtChar()
{
	std::string s0 = char_std;
	std::string s1 = char_std;
	std::string s2 = char_std;
	std::string s3 = char_std;
	volatile char c;
	c = s0[0], c = s1[0], c = s2[0], c = s3[0];
}
void __declspec(noinline) txtAllocTxtChar()
{
	txt s0 = char_txt;
	txt s1 = char_txt;
	txt s2 = char_txt;
	txt s3 = char_txt;
	volatile char c;
	c = s0[0], c = s1[0], c = s2[0], c = s3[0];
}
// =======================================================================================================
void __declspec(noinline) stdArrayAccess(std::string &s, volatile ui64 sz)
{
	for(ui64 i = 0; i < sz; ++i)
	{
		s[i] = '$';
	}
}
void __declspec(noinline) txtArrayAccess(txt &t, volatile ui64 sz)
{
	for(ui64 i = 0; i < sz; ++i)
	{
		t[i] = '$';
	}
}
// =======================================================================================================
void __declspec(noinline) stdAppendingStr(std::string &s)
{
	s += lorem_sm;
}
void __declspec(noinline) txtAppendingStr(txt &t)
{
	t += lorem_sm;
}
// =======================================================================================================
void __declspec(noinline) stdAppendingChar(std::string &s)
{
	s += '$';
}
void __declspec(noinline) txtAppendingChar(txt &t)
{
	t += '$';
}
// =======================================================================================================
void __declspec(noinline) stdFindingCstr(const std::string &s, const char *ccstr, volatile ui64 i)
{
	volatile ui64 res = s.find(ccstr + i % 30);
}
void __declspec(noinline) txtFindingCstr(const txt &t, const char *ccstr, volatile ui64 i)
{
	volatile ui64 res = txtf(t, 0, ccstr + i % 30);
}
// =======================================================================================================
void __declspec(noinline) stdFindingTxt(const std::string &s, const std::string &so)
{
	volatile ui64 res = s.find(so);
}
void __declspec(noinline) txtFindingTxt(const txt &t, const txt &to)
{
	volatile ui64 res = txtf(t, 0, to);
}
// =======================================================================================================
void __declspec(noinline) stdInserting(std::string &s, volatile ui64 sz)
{
	for(ui64 i = 0; i < sz; i += 100)
	{
		s.insert(i, "!BAKA!_!IS!_!!HERE?!");
	}
}
void __declspec(noinline) txtInserting(txt &t, volatile ui64 sz)
{
	for(ui64 i = 0; i < sz; i += 100)
	{
		txti(t, i, "!BAKA!_!IS!_!!HERE?!");
	}
}
// =======================================================================================================
void __declspec(noinline) stdOverwriting(std::string &s, volatile ui64 sz)
{
	for(ui64 i = 0; i + 100 < sz; i += 100)
	{
		s.replace(i, 20, "!BAKA!_!IS!_!!HERE?!");
	}
}
void __declspec(noinline) txtOverwriting(txt &t, volatile ui64 sz)
{
	for(ui64 i = 0; i + 100 < sz; i += 100)
	{
		txtr(t, i, 20, "!BAKA!_!IS!_!!HERE?!");
	}
}
// =======================================================================================================
void __declspec(noinline) stdCmpCstr(const std::string &s, const char *ccstr)
{
	volatile bool res = s == ccstr;
}
void __declspec(noinline) txtCmpCstr(const txt &t, const char *ccstr)
{
	volatile bool64 res = t == ccstr;
}
// =======================================================================================================
void __declspec(noinline) stdCmpTxt(const std::string &s, const std::string &so)
{
	volatile bool res = s == so;
}
void __declspec(noinline) txtCmpTxt(const txt &t, const txt &to)
{
	volatile bool64 res = t == to;
}
// =======================================================================================================
void __declspec(noinline) stdIntToText(std::string &s, volatile ui64 num)
{
	s = std::to_string(num);
}
void __declspec(noinline) txtIntToText(txt &t, volatile ui64 num)
{
	t = i2t(num);
}
// =======================================================================================================
void __declspec(noinline) stdTextToInt(const std::string &s)
{
	volatile ui64 res = stoull(s);
}
void __declspec(noinline) txtTextToInt(const txt &t)
{
	volatile ui64 res = t2i(t);
}
// =======================================================================================================
void __declspec(noinline) stdIntToHex(std::string &s, volatile ui64 num)
{
	std::stringstream ss;
	ss << std::hex << std::uppercase << num;
	s = ss.str();
}
void __declspec(noinline) txtIntToHex(txt &t, volatile ui64 num)
{
	t = i2h(num);
}
// =======================================================================================================
void __declspec(noinline) stdHexToInt(const std::string &s)
{
	volatile ui64 res = stoull(s, nullptr, 16);
}
void __declspec(noinline) txtHexToInt(const txt &t)
{
	volatile ui64 res = h2i(t);
}
// =======================================================================================================
void __declspec(noinline) stdClearing(std::string &s)
{
	s.clear();
}
void __declspec(noinline) txtClearing(txt &t)
{
	txtclr(t); //txt_clr_a[i] = 0; // This is slower way to clear text
}
// =======================================================================================================
void __declspec(noinline) stdDestructing(std::string &s)
{
	typedef std::string std_string;
	s.~std_string();
}
void __declspec(noinline) txtDestructing(txt &t)
{
	t.~txt();
}
// =======================================================================================================
void __declspec(noinline) stdToLower()
{
	for(auto & c: lorem_std) c = (char)(rand() % 127);
	for(auto & c: lorem_std) c = (char)tolower(c);
}

void __declspec(noinline) txtToLower()
{
	for(ui64 i = 0; i < ~lorem_txt; ++i)
	{
		lorem_txt[i] = (char)(rand() % 127);
	}
	t2low(lorem_txt);
}
// =======================================================================================================
void __declspec(noinline) stdToUpper()
{
	for(auto & c: lorem_std) c = (char)(rand() % 127);
	for(auto & c: lorem_std) c = (char)toupper(c);
}
void __declspec(noinline) txtToUpper()
{
	for(ui64 i = 0; i < ~lorem_txt; ++i)
	{
		lorem_txt[i] = (char)(rand() % 127);
	}
	t2up(lorem_txt);
}
// =======================================================================================================

#pragma optimize( "", off )
void test()
{
	memcpy(lorem, lorem_lit, 1770);
	lorem[1770] = 0;
	memcpy(lorem_sm, lorem_sm_lit, 414);
	lorem_sm[414] = 0;
	memcpy(chars_100, chars_100_lit, 100);
	chars_100[100] = 0;
	
	const char *tst_nms[100];
	
	ui64 tst_id = 0;
	ui64 tst_amount = 0;
	const ui64 prof_runs = 2;
	ui64 tst_cyc = 0;
	for(ui64 pi = 0; pi < prof_runs; ++pi)
	{
		p|DC;
		p|"PROFILING RUN "|pi|S(50)|N;
		
		RUN_TEST(ALLOC CSTR S1770, 142000/DBGM)
			stdAllocCstrS1770();
		MID_TEST
			txtAllocCstrS1770();
		END_TEST
		
		RUN_TEST(ALLOC TXT S1770, 142000/DBGM)
			stdAllocTxtS1770();
		MID_TEST
			txtAllocTxtS1770();
		END_TEST
		
		RUN_TEST(ALLOC CHAR, 1420000/DBGM)
			stdAllocChar();
		MID_TEST
			txtAllocChar();
		END_TEST
		
		RUN_TEST(ALLOC TXT CHAR, 1420000/DBGM)
			stdAllocTxtChar();
		MID_TEST
			txtAllocTxtChar();
		END_TEST
		
		std::string str_lorem = lorem;
		txt txt_lorem = lorem;
		ui64 lorems = str_lorem.size();
		
		RUN_TEST(ARRAY ACCESS, 142000/DBGM)
			stdArrayAccess(str_lorem, lorems);
		MID_TEST
			txtArrayAccess(txt_lorem, lorems);
		END_TEST
		
		str_lorem = lorem_sm;
		txt_lorem = lorem_sm;
		
		RUN_TEST(APPENDING STR, 142000/DBGM)
			stdAppendingStr(str_lorem);
		MID_TEST
			txtAppendingStr(txt_lorem);
		END_TEST
		
		str_lorem = lorem_sm;
		txt_lorem = lorem_sm;
		
		RUN_TEST(APPENDING CHAR, 42420000/DBGM)
			stdAppendingChar(str_lorem);
		MID_TEST
			txtAppendingChar(txt_lorem);
		END_TEST
		
		const char *fnd_str = "HA! DIDNT EXPECT DA !BAKA! HERE?!";
		std::string fnd_str_std = fnd_str;
		txt fnd_str_txt = fnd_str;
		ui64 res = 0;
		str_lorem = lorem;
		txt_lorem = lorem;
		
		RUN_TEST(FINDING CSTR, 242000/DBGM)
			stdFindingCstr(str_lorem, fnd_str, i);
		MID_TEST
			txtFindingCstr(txt_lorem, fnd_str, i);
		END_TEST
		
		RUN_TEST(FINDING TXT, 420000/DBGM)
			stdFindingTxt(str_lorem, fnd_str_std);
		MID_TEST
			txtFindingTxt(txt_lorem, fnd_str_txt);
		END_TEST
		
		str_lorem = lorem;
		txt_lorem = lorem;

		RUN_TEST(INSERTING, 3400/DBGM)
			stdInserting(str_lorem, lorems);
		MID_TEST
			txtInserting(txt_lorem, lorems);
		END_TEST
		
		str_lorem = lorem;
		txt_lorem = lorem;
		
		RUN_TEST(OVERWRITING, 442000/DBGM)
			stdOverwriting(str_lorem, lorems);
		MID_TEST
			txtOverwriting(txt_lorem, lorems);
		END_TEST
		
		str_lorem = lorem;
		std::string str_lorem_o = str_lorem;
		txt_lorem = lorem;
		txt txt_lorem_o = txt_lorem;
		std::string str_not_lorem = "NOT LOREM!";
		txt txt_not_lorem = "NOT LOREM!";
		
		RUN_TEST(CMP CSTR WC, 242000/DBGM) // WORST CASE
			stdCmpCstr(str_lorem, lorem);
		MID_TEST
			txtCmpCstr(txt_lorem, lorem);
		END_TEST
		
		RUN_TEST(CMP CSTR BC, 4420000/DBGM) // BEST CASE
			stdCmpCstr(str_lorem, "NOT LOREM!");
		MID_TEST
			txtCmpCstr(txt_lorem, "NOT LOREM!");
		END_TEST
		
		RUN_TEST(CMP TXT WC, 242000/DBGM)
			stdCmpTxt(str_lorem, str_lorem_o);
		MID_TEST
			txtCmpTxt(txt_lorem, txt_lorem_o);
		END_TEST
		
		RUN_TEST(CMP TXT BC, 4420000/DBGM)
			stdCmpTxt(str_lorem, str_not_lorem);
		MID_TEST
			txtCmpTxt(txt_lorem, txt_not_lorem);
		END_TEST
		
		volatile ui64 num = 18000000042000000000;
		std::string str_num;
		txt txt_num;
		
		RUN_TEST(INT TO TEXT, 1420000/DBGM)
			stdIntToText(str_num, num);
		MID_TEST
			txtIntToText(txt_num, num);
		END_TEST
		
		const char *num_str = "18000000042000000000";
		str_num = num_str;
		txt_num = num_str;
		
		RUN_TEST(TEXT TO INT, 4420000/DBGM)
			stdTextToInt(str_num);
		MID_TEST
			txtTextToInt(txt_num);
		END_TEST
		
		num = 0xBEEFFAAA42006934;
		
		RUN_TEST(INT TO HEX, 442000/DBGM)
			stdIntToHex(str_num, num);
		MID_TEST
			txtIntToHex(txt_num, num);
		END_TEST
		
		num_str = "BEEFFAAA42006934";
		str_num = num_str;
		txt_num = num_str;
		
		RUN_TEST(HEX TO INT, 4420000/DBGM)
			stdHexToInt(str_num);
		MID_TEST
			txtHexToInt(txt_num);
		END_TEST
		
		std::string *std_clr_a =
			(std::string *)VirtualAlloc(NULL, 420000 * sizeof(std::string), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		txt *txt_clr_a =
			(txt *)VirtualAlloc(NULL, 420000 * sizeof(txt), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		for(int i = 0; i < 420000; ++i)
		{
			std_clr_a[i].reserve(512);
			std_clr_a[i] = chars_100;
		}
		for(int i = 0; i < 420000; ++i)
		{
			txt_clr_a[i] = 512;
			txt_clr_a[i] = chars_100;
		}
		
		RUN_TEST(CLEARING, 420000/DBGM)
			stdClearing(std_clr_a[i]);
		MID_TEST
			txtClearing(txt_clr_a[i]);
		END_TEST
		
		RUN_TEST(DESTRUCTING, 420000/DBGM)
			stdDestructing(std_clr_a[i]);
		MID_TEST
			txtDestructing(txt_clr_a[i]);
		END_TEST
		
		VirtualFree(std_clr_a, 0, MEM_RELEASE);
		VirtualFree(txt_clr_a, 0, MEM_RELEASE);
		
		RUN_TEST(TO LOWERCASE, 420000/DBGM)
			stdToLower();
		MID_TEST
			txtToLower();
		END_TEST
		
		RUN_TEST(TO UPPERCASE, 420000/DBGM)
			stdToUpper();
		MID_TEST
			txtToUpper();
		END_TEST
		
		SWIDRESET
		if(tst_amount == 0)
		{
			tst_amount = tst_id;
		}
		tst_id = 0;
	}
	
	p|TM;
	p|TCP(1)|TCP(0)		|TCP(8)	|TCP(0);
	p|""	|TAC|"STD"	|""		|"TXT"|TN;
	for(ui64 i = 0; i < tst_amount; ++i)
	{
		p|TAL|tst_nms[i] + txt(':');
		SWPDIFF
		p|TN;
	}
	p|TE;
}
#pragma optimize( "", on )
#endif