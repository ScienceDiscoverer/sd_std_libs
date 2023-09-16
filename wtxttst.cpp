// CONSOLE NOPT
#include <sddb>
#include <stdp>
#include <tests.h>

#include <string>	//
#include <sstream>	// Just for profiling test, otherwise, casual std, ugh!
#include <ios>		//

#pragma warning( disable : 4834 )
#pragma warning( disable : 4189 )

cwstr buff_worker_str = WL("BUFF TEST PASSED!");

void buff_worker(wchar_t *b, uli32 *s)
{
	uli32 i = 0;
	while(buff_worker_str.t[i] != 0 && i < *s)
	{
		b[i] = buff_worker_str.t[i];
		++i;
	}
	*s = i;
}

void dispPos(ui64 pos, const wtxt& s, ui64 correct_pos)
{	
	if(pos == NFND)
	{
		p|L"NOT FOUND!"|L" -> |" | s | L"|";
		p|(pos == correct_pos ? p|G|L" PASSED"|D : p|S|fail()|D)|N;
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
	p|' ' | pos | L" -> |" | s | L"|";
	p|(pos == correct_pos ? p|G|L" PASSED"|D : p|S|fail()|D)|N;
}

bool t2ii2tTest()
{
	p|DC;
	p|L"T2II2T PROGRESS: "|N;
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
			p|L"[";
			while(--j >= 0)
			{
				p|'|';
			}
			while(--k >= 0)
			{
				p|' ';
			}
			p|L"]";
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
		wtxt h8 = b2wh(x8);
		
		ui64 rdec = t2i(dec);
		i32 rsdec = (i32)t2i(sdec);
		ui64 rh64 = h2i(h64);
		ui64 rh32 = h2i(h32);
		ui64 rh16 = h2i(h16);
		ui64 rh8 = h2i(h8);
		
		if(rdec != i)
		{
			epic_fail = true;
			p|R|L"T2II2T EPIC FAIL! rdec:  "|D|rdec|L" wtxt: "|dec|L" i:    "|i|N;
		}
		
		if(rsdec != sx32)
		{
			epic_fail = true;
			p|R|L"T2II2T EPIC FAIL! rsdec: "|D|rsdec|L" wtxt: "|sdec|L" sx32: "|sx32|N;
		}
		
		if(rh64 != i)
		{
			epic_fail = true;
			p|R|L"T2II2T EPIC FAIL! rh64:  "|D|H|rh64|L" wtxt: "|H|h64|L" i:    "|i|N;
		}
		
		if(rh32 != x32)
		{
			epic_fail = true;
			p|R|L"T2II2T EPIC FAIL! rh32:  "|D|H|rh32|L" wtxt: "|H|h32|L" x32:  "|x32|N;
		}
		
		if(rh16 != x16)
		{
			epic_fail = true;
			p|R|L"T2II2T EPIC FAIL! rh16:  "|D|H|rh16|L" wtxt: "|H|h16|L" x16:  "|x16|N;
		}
		
		if(rh8 != x8)
		{
			epic_fail = true;
			p|R|L"T2II2T EPIC FAIL! rh8:   "|D|H|rh8|L" wtxt: "|H|h8|L" x8:  "|x8|N;
		}
	}
	
	ui64 bin64 = 0xF0F0F0F0F0F0F0F0;
	ui32 bin32 = 0xF0F0F0F0;
	ui16 bin16 = 0xF0F0;
	ui8 bin8 = 0xF0;
	
	if(i2wb(bin64) != WL("1111000011110000111100001111000011110000111100001111000011110000"))
	{
		p|R|"T2II2T EPIC FAIL! bin64 "|D|N;
		p|"GOT:  "|i2wb(bin64)|N;
		p|"NEED: "|"1111000011110000111100001111000011110000111100001111000011110000"|N;
		epic_fail = true;
	}
	if(i2wb(bin32) != WL("11110000111100001111000011110000"))
	{
		p|R|"T2II2T EPIC FAIL! bin32 "|D|N;
		p|"GOT:  "|i2wb(bin32)|N;
		p|"NEED: "|"11110000111100001111000011110000"|N;
		epic_fail = true;
	}
	if(i2wb(bin16) != WL("1111000011110000"))
	{
		p|R|"T2II2T EPIC FAIL! bin16 "|D|N;
		p|"GOT:  "|i2wb(bin16)|N;
		p|"NEED: "|"1111000011110000"|N;
		epic_fail = true;
	}
	if(b2wb(bin8) != WL("11110000"))
	{
		p|R|"T2II2T EPIC FAIL! bin8 "|D|N;
		p|"GOT:  "|b2wb(bin8)|N;
		p|"NEED: "|"11110000"|N;
		epic_fail = true;
	}
	
	i8 nbyte = -112;
	i8 pbyte = 42;
	ui8 ubyte = 222;
	
	if(b2wt(nbyte) != WL("-112"))
	{
		p|R|"T2II2T EPIC FAIL! nbyte "|D|N;
		p|"GOT:  "|b2wt(nbyte)|N;
		p|"NEED: "|"-112"|N;
		epic_fail = true;
	}
	if(b2wt(pbyte) != WL("42"))
	{
		p|R|"T2II2T EPIC FAIL! pbyte "|D|N;
		p|"GOT:  "|b2wt(pbyte)|N;
		p|"NEED: "|"42"|N;
		epic_fail = true;
	}
	if(b2wt(ubyte) != WL("222"))
	{
		p|R|"T2II2T EPIC FAIL! ubyte "|D|N;
		p|"GOT:  "|b2wt(ubyte)|N;
		p|"NEED: "|"222"|N;
		epic_fail = true;
	}
	
	return epic_fail;
}

inline ui64 getTerminator(const wtxt &t)
{
	return (ui64)*((const wchar_t *)t + ~t);
}

cwstr insert_tst_arr[] = {
	WL("<|||>This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("T<|||>his_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("Th<|||>is_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("Thi<|||>s_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This<|||>_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_<|||>is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_i<|||>s_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is<|||>_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_<|||>tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_t<|||>esuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_te<|||>suto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tes<|||>uto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesu<|||>to_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesut<|||>o_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto<|||>_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_<|||>insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_i<|||>nsertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_in<|||>sertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_ins<|||>ertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_inse<|||>rtion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_inser<|||>tion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insert<|||>ion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_inserti<|||>on_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertio<|||>n_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion<|||>_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_<|||>!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!<|||>baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!b<|||>aka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!ba<|||>ka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!bak<|||>a_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka<|||>_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_<|||>this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_t<|||>his_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_th<|||>is_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_thi<|||>s_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this<|||>_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_<|||>T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T<|||>_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_<|||>tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_t<|||>esutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_te<|||>sutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tes<|||>utoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesu<|||>toraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesut<|||>oraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesuto<|||>raptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutor<|||>aptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutora<|||>ptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutorap<|||>tor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutorapt<|||>or_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutorapto<|||>r_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor<|||>_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_<|||>text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_t<|||>ext_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_te<|||>xt_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_tex<|||>t_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text<|||>_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_<|||>baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_b<|||>aka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_ba<|||>ka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_bak<|||>a!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka<|||>!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!<|||>") };
	
cwstr insert_char_tst_arr[] = {
	WL("$This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("T$his_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("Th$is_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("Thi$s_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This$_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_$is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_i$s_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is$_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_$tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_t$esuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_te$suto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tes$uto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesu$to_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesut$o_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto$_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_$insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_i$nsertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_in$sertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_ins$ertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_inse$rtion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_inser$tion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insert$ion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_inserti$on_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertio$n_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion$_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_$!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!$baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!b$aka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!ba$ka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!bak$a_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka$_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_$this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_t$his_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_th$is_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_thi$s_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this$_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_$T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T$_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_$tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_t$esutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_te$sutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tes$utoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesu$toraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesut$oraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesuto$raptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutor$aptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutora$ptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutorap$tor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutorapt$or_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutorapto$r_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor$_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_$text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_t$ext_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_te$xt_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_tex$t_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text$_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_$baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_b$aka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_ba$ka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_bak$a!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka$!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!$") };
	
cwstr overwr_tst_arr[] = {
	WL("<|||>is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("T<|||>s_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("Th<|||>_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("Thi<|||>tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This<|||>esuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_<|||>suto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_i<|||>uto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is<|||>to_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_<|||>o_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_t<|||>_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_te<|||>insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tes<|||>nsertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesu<|||>sertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesut<|||>ertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto<|||>rtion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_<|||>tion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_i<|||>ion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_in<|||>on_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_ins<|||>n_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_inse<|||>_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_inser<|||>!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insert<|||>baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_inserti<|||>aka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertio<|||>ka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion<|||>a_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_<|||>_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!<|||>this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!b<|||>his_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!ba<|||>is_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!bak<|||>s_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka<|||>_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_<|||>T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_t<|||>_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_th<|||>tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_thi<|||>esutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this<|||>sutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_<|||>utoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T<|||>toraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_<|||>oraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_t<|||>raptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_te<|||>aptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tes<|||>ptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesu<|||>tor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesut<|||>or_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesuto<|||>r_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutor<|||>_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutora<|||>text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutorap<|||>ext_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutorapt<|||>xt_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutorapto<|||>t_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor<|||>_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_<|||>baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_t<|||>aka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_te<|||>ka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_tex<|||>a!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text<|||>!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_<|||>"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_b<|||>"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_ba<|||>"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_bak<|||>"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka<|||>") };
	
cwstr overwr_char_tst_arr[] = {
	WL("$his_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("T$is_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("Th$s_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("Thi$_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This$is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_$s_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_i$_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is$tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_$esuto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_t$suto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_te$uto_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tes$to_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesu$o_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesut$_insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto$insertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_$nsertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_i$sertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_in$ertion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_ins$rtion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_inse$tion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_inser$ion_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insert$on_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_inserti$n_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertio$_!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion$!baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_$baka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!$aka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!b$ka_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!ba$a_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!bak$_this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka$this_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_$his_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_t$is_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_th$s_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_thi$_T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this$T_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_$_tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T$tesutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_$esutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_t$sutoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_te$utoraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tes$toraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesu$oraptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesut$raptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesuto$aptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutor$ptor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutora$tor_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutorap$or_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutorapt$r_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutorapto$_text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor$text_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_$ext_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_t$xt_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_te$t_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_tex$_baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text$baka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_$aka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_b$ka!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_ba$a!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_bak$!"),
	WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka$") };

cwstr global_text_big_str = WL(
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
wtxt global_text_big = global_text_big_str;

cwstr global_text_empty_str = WL("");
wtxt global_text_empty;
cwstr global_text_small_str = WL("i'm very smol :'(");
wtxt global_text_small = global_text_small_str;

void test();

int wmain()
{
	wtxt total_empty;
	T("TOTAL EMPTY SIZE", ~total_empty, 0);
	T("TOTAL EMPTY TRUE SIZE", !total_empty, 0);
	T("TOTAL EMPTY DATA", (ui64)(const wchar_t *)total_empty, NULL);
	
	T("GLOBAL TEXT BIG", global_text_big, global_text_big_str);
	T("GLOBAL TEXT EMPTY", global_text_empty, global_text_empty_str);
	T("GLOBAL TEXT SMALL", global_text_small, global_text_small_str);
	
#ifndef BASIC_TESTZ
#ifdef BUFFER_MODE
	wtxt conbuff = 20;
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
	
	wtxt t(WL("Hello Baka"));
	wtxt g = WL("Whale Hallo Dere");
	//////////////////////////////////////////////////////////////////////////
	T("CONSTRUCTION FROM CSTR LITERAL t", t, WL("Hello Baka"));
	T("CONSTRUCTION FROM CSTR LITERAL STRLEN t", ~t, wcslen(t));
	T("CONSTRUCTION FROM CSTR LITERAL g", g, WL("Whale Hallo Dere"));
	T("CONSTRUCTION FROM CSTR LITERAL STRLEN g", ~g, wcslen(g));
	//////////////////////////////////////////////////////////////////////////
	wtxt ch = '$';
	T("CONSTRUCTION FROM CHAR", ch, '$');
	//////////////////////////////////////////////////////////////////////////
	wtxt buff = 20;
	buff_worker(buff, *buff);
	if(T("BUFFER WORKER", buff, buff_worker_str))
	{
		p|"buff in hex: "|str2hex((const wchar_t *)buff);
		p|N|I|buff|I|" buff_work size/true size: "|~buff|S|!buff|N;
	}
	//////////////////////////////////////////////////////////////////////////
	t = g;
	T("TXT 2 TXT ASSIGNMENT", t, g);
	t = wtxt(WL("I'm tmp floop!"));
	T("TXT 2 TXT ASSIGNMENT FROM RVAL", t, WL("I'm tmp floop!"));
	t = WL("NEW wchar_t literal ready for duty!");
	T("TXT 2 CSTR ASSIGNMENT", t, WL("NEW wchar_t literal ready for duty!"));
	t = '#';
	T("TXT 2 CHAR ASSIGNMENT", t, (wtxt)'#');
	t = -42;
	T("TXT 2 NEGATIVE INT ASSIGNMENT", t, WL(""));
	TNOT("TXT 2 NEGATIVE INT ASSIGNMENT TRUE SIZE", !t, 0);
	t = g;
	t = 0;
	T("TXT 2 ZERO INT ASSIGNMENT", t, WL(""));
	TNOT("TXT 2 ZERO INT ASSIGNMENT TRUE SIZE", !t, 0);
	t = g;
	t = 42;
	T("TXT 2 POSITIVE INT ASSIGNMENT", t, WL(""));
	T("TXT 2 POSITIVE INT ASSIGNMENT TRUE SIZE", !t, 42 + 1);
	T("TXT 2 POSITIVE INT ASSIGNMENT STRLEN", ~t, wcslen(t));
	//////////////////////////////////////////////////////////////////////////
	//for(ui64 i = 0; i < !t; ++i)
	//{
	//	//p|"t[" | i | "]: " | hex | uppercase | +t[0] |N;
	//	p|/* (wchar_t *) */(t[i]) | '_';
	//}
	// _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ msvc
	//__________________________________________ gcc -> because gcc does not pring \0 chars for SOME reason ._.
	//wchar_t a[42];
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
	wtxt t0, t1;
	t0 = WL("Baka Part 1");
	t1 = WL("-Baka Part 2");
	t0 += t1;
	T("TXT 2 TXT += APPEND", t0, WL("Baka Part 1-Baka Part 2"));
	t0 += WL("-Baka Part 3");
	T("CSTR 2 TXT += APPEND", t0, WL("Baka Part 1-Baka Part 2-Baka Part 3"));
	t0 += '*';
	T("CHAR 2 TXT += APPEND", t0, WL("Baka Part 1-Baka Part 2-Baka Part 3*"));
	//////////////////////////////////////////////////////////////////////////
	wtxt txt_lval = WL("Test CSTR made from TXT rvalue...") + i2wt(6934) + t1;
	const wchar_t *conv_txt = txt_lval;
	if(T("CSTR FROM TXT ADDITION RVALUE", cwstr({ conv_txt, ~txt_lval }), WL("Test CSTR made from TXT rvalue...6934-Baka Part 2")))
	{
		p|"conv_txt hex: "|txt2hex(txt_lval);
		p|N|I|txt_lval|I|" txt_lval size/true size: "|~txt_lval|S|!txt_lval|N;
	}/*Test CSTR made from TXT rvalue...6934-Baka Part 2*//*"Test CSTR made from TXT rvalue...6934-Baka Part 2"*/
	//////////////////////////////////////////////////////////////////////////

#ifndef COMARIZON
	t0 = WL("-comp"), t1 = WL("-comp");
	wtxt t2 = WL("-compper"), t3 = WL("-co$p"), t4 = (wtxt)'$', t5, t6 = (wtxt)'-';

	TBOOL("OP == TXT-TXT	|-comp| == |-comp|",	t0 == t1, true);
	TBOOL("OP == TXT-TXT	|-comp| == |-compper|",	t0 == t2, false);
	TBOOL("OP == TXT-TXT	|-comp| == |-co$p|",	t0 == t3, false);
	
	TBOOL("OP != TXT-TXT	|-comp| != |-comp|",	t0 != t1, false);
	TBOOL("OP != TXT-TXT	|-comp| != |-compper|",	t0 != t2, true);
	TBOOL("OP != TXT-TXT	|-comp| != |-co$p|",	t0 != t3, true);
	
	TBOOL("OP == TXT-CSTR	|-comp| == |-comp|",	t0 == WL("-comp"),		true);
	TBOOL("OP == TXT-CSTR	|-comp| == |-compper|",	t0 == WL("-compper"),	false);
	TBOOL("OP == TXT-CSTR	|-comp| == |-co$p|",	t0 == WL("-co$p"),		false);
	
	TBOOL("OP != TXT-CSTR	|-comp| != |-comp|",	t0 != WL("-comp"),		false);
	TBOOL("OP != TXT-CSTR	|-comp| != |-compper|",	t0 != WL("-compper"),	true);
	TBOOL("OP != TXT-CSTR	|-comp| != |-co$p|",	t0 != WL("-co$p"),		true);
	
	TBOOL("OP == CSTR-TXT	|-comp| == |-comp|",	t0 == WL("-comp"),		true);
	TBOOL("OP == CSTR-TXT	|-comp| == |-compper|",	t0 == WL("-compper"),	false);
	TBOOL("OP == CSTR-TXT	|-comp| == |-co$p|",	t0 == WL("-co$p"),		false);
	
	TBOOL("OP != CSTR-TXT	|-comp| != |-comp|",	t0 != WL("-comp"),		false);
	TBOOL("OP != CSTR-TXT	|-comp| != |-compper|",	t0 != WL("-compper"),	true);
	TBOOL("OP != CSTR-TXT	|-comp| != |-co$p|",	t0 != WL("-co$p"),		true);
	
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
	
	wtxt sub_eq_tst = WL("ABCDz-b3$f-414b-b@2e-826$a1bd__BAK__081bf9b-a6c1-4$54-a9a3-8b9a1221__END");
	
	TBOOL("TXTSEQ SUBSTRING EQUALITY 0", txtseq(sub_eq_tst, 0, WL("ABCDz")), true);
	TBOOL("TXTSEQ SUBSTRING EQUALITY 1", txtseq(sub_eq_tst, 29, WL("__BAK__")), true);
	TBOOL("TXTSEQ SUBSTRING EQUALITY 2", txtseq(sub_eq_tst, 67, WL("__END")), true);
	TBOOL("TXTNEQ SUBSTRING NONEQUALITY 0", txtsneq(sub_eq_tst, 68, WL("__END")), true);
	TBOOL("TXTNEQ SUBSTRING NONEQUALITY 1", txtsneq(sub_eq_tst, 29, WL("__PAK__")), true);
	
	//////////////////////////////////////////////////////////////////////////
	//p|"Baka + ' ' + Mono: |" | (wtxt("Baka") + ' ' + "Mono") | '|' |N;
	//////////////////////////////////////////////////////////////////////////
	
	cwstr tofind = WL("This_is_tesuto___________searching_!baka_this_T_tesutoraptor_text_baka!");
	cwstr tofind_case = WL("THis_Is_tesuTO___________SEARChInG_!baKa_tHis_T_TeSuToRAPtOR_tEXt_BAKa!");
	wtxt fthis = WL("This");
	wtxt ftesuto = WL("tesuto");
	wtxt fbaka = WL("baka!");
	wtxt fnone = WL("NONSENSE");
	
	wtxt fnd_tst = tofind;
	wtxt fnd_tst_case = tofind_case;
	
	//p|"\nSEARCHING FROM BEG >>>>>>>>>>>>>>>>>>\n";
	
	if(T("FINDING FROM BEG 0", txtf(fnd_tst, 0, WL("tesuto")), 8))
	{
		p|tofind|N;
		dispPos(txtf(fnd_tst, 0, WL("tesuto")), wtxt(WL("tesuto")), 8);
	}
	if(T("FINDING FROM BEG 1", txtf(fnd_tst, 0, ftesuto), 8))
	{
		p|tofind|N;
		dispPos(txtf(fnd_tst, 0, ftesuto), wtxt(ftesuto), 8);
	}
	if(T("FINDING FROM BEG 2", txtf(fnd_tst, 0, 'r'), 28))
	{
		p|tofind|N;
		dispPos(txtf(fnd_tst, 0, 'r'), wtxt('r'), 28);
	}
	if(T("FINDING FROM BEG 3", txtf(fnd_tst, 24, WL("tesuto")), 48))
	{
		p|tofind|N;
		dispPos(txtf(fnd_tst, 24, WL("tesuto")), wtxt(WL("tesuto")), 48);
	}
	if(T("FINDING FROM BEG 4", txtf(fnd_tst, 24, ftesuto), 48))
	{
		p|tofind|N;
		dispPos(txtf(fnd_tst, 24, ftesuto), ftesuto, 48);
	}
	if(T("FINDING FROM BEG 5", txtf(fnd_tst, 44, 'r'), 54))
	{
		p|tofind|N;
		dispPos(txtf(fnd_tst, 44, 'r'), wtxt('r'), 54);
	}
	if(T("FINDING FROM BEG 6", txtf(fnd_tst, 14, 'a', 'z'), 25))
	{
		p|tofind|N;
		dispPos(txtf(fnd_tst, 14, 'a', 'z'), wtxt(WL("a-z")), 25);
	}
	
	//p|"\nSEARCHING FROM end <<<<<<<<<<<<<<<<<<\n";
	
	if(T("FINDING FROM END 0", txtfe(fnd_tst, 0, WL("tesuto")), NFND))
	{
		p|tofind|N;
		dispPos(txtfe(fnd_tst, 0, WL("tesuto")), wtxt(WL("tesuto")), NFND);
	}
	if(T("FINDING FROM END 1", txtfe(fnd_tst, 0, ftesuto), NFND))
	{
		p|tofind|N;
		dispPos(txtfe(fnd_tst, 0, ftesuto), wtxt(ftesuto), NFND);
	}
	if(T("FINDING FROM END 2", txtfe(fnd_tst, 0, 'r'), NFND))
	{
		p|tofind|N;
		dispPos(txtfe(fnd_tst, 0, 'r'), wtxt('r'), NFND);
	}
	if(T("FINDING FROM END 3", txtfe(fnd_tst, 24, WL("tesuto")), 8))
	{
		p|tofind|N;
		dispPos(txtfe(fnd_tst, 24, WL("tesuto")), wtxt(WL("tesuto")), 8);
	}
	if(T("FINDING FROM END 4", txtfe(fnd_tst, 24, ftesuto), 8))
	{
		p|tofind|N;
		dispPos(txtfe(fnd_tst, 24, ftesuto), ftesuto, 8);
	}
	if(T("FINDING FROM END 5", txtfe(fnd_tst, 24, 'r'), NFND))
	{
		p|tofind|N;
		dispPos(txtfe(fnd_tst, 24, 'r'), wtxt('r'), NFND);
	}
	if(T("FINDING FROM END 6", txtfe(fnd_tst, 24, 'a', 'z'), 13))
	{
		p|tofind|N;
		dispPos(txtfe(fnd_tst, 24, 'a', 'z'), wtxt(WL("a-z")), 13);
	}
	
	//p|"\nSEARCHING IN RANGE <<<<<<<<<<<<<<<<<<\n";
	
	if(T("FINDING IN RANGE 0", txtfr(fnd_tst, 0, 18, WL("tesuto")), 8))
	{
		p|tofind|N;
		dispPos(txtfr(fnd_tst, 0, 18, WL("tesuto")), wtxt(WL("tesuto")), 8);
	}
	if(T("FINDING IN RANGE 1", txtfr(fnd_tst, 0, 18, ftesuto), 8))
	{
		p|tofind|N;
		dispPos(txtfr(fnd_tst, 0, 18, ftesuto), wtxt(ftesuto), 8);
	}
	if(T("FINDING IN RANGE 2", txtfr(fnd_tst, 0, 5, 'r'), NFND))
	{
		p|tofind|N;
		dispPos(txtfr(fnd_tst, 0, 5, 'r'), wtxt('r'), NFND);
	}
	if(T("FINDING IN RANGE 3", txtfr(fnd_tst, 24, 43, WL("tesuto")), NFND))
	{
		p|tofind|N;
		dispPos(txtfr(fnd_tst, 24, 43, WL("tesuto")), wtxt(WL("tesuto")), NFND);
	}
	if(T("FINDING IN RANGE 4", txtfr(fnd_tst, 24, 43, ftesuto), NFND))
	{
		p|tofind|N;
		dispPos(txtfr(fnd_tst, 24, 43, ftesuto), ftesuto, NFND);
	}
	if(T("FINDING IN RANGE 5", txtfr(fnd_tst, 24, 44, 'r'), 28))
	{
		p|tofind|N;
		dispPos(txtfr(fnd_tst, 24, 44, 'r'), wtxt('r'), 28);
	}
	if(T("FINDING IN RANGE 6", txtfr(fnd_tst, 14, 24, 'a', 'z'), NFND))
	{
		p|tofind|N;
		dispPos(txtfr(fnd_tst, 14, 24, 'a', 'z'), wtxt(WL("a-z")), NFND);
	}
	
	//p|"\nSEARCHING FROM BEG CASE INSENSITIVE >>>>>>>>>>>>>>>>>>\n";
	
	if(T("FINDING FROM BEG CASE INSENSE 0", txtfci(fnd_tst_case, 0, WL("tesuto")), 8))
	{
		p|tofind|N;
		dispPos(txtfci(fnd_tst_case, 0, WL("tesuto")), wtxt(WL("tesuto")), 8);
	}
	if(T("FINDING FROM BEG CASE INSENSE 1", txtfci(fnd_tst_case, 0, ftesuto), 8))
	{
		p|tofind|N;
		dispPos(txtfci(fnd_tst_case, 0, ftesuto), wtxt(ftesuto), 8);
	}
	if(T("FINDING FROM BEG CASE INSENSE 2", txtfci(fnd_tst_case, 0, 'r'), 28))
	{
		p|tofind|N;
		dispPos(txtfci(fnd_tst_case, 0, 'r'), wtxt('r'), 28);
	}
	if(T("FINDING FROM BEG CASE INSENSE 3", txtfci(fnd_tst_case, 24, WL("tesuto")), 48))
	{
		p|tofind|N;
		dispPos(txtfci(fnd_tst_case, 24, WL("tesuto")), wtxt(WL("tesuto")), 48);
	}
	if(T("FINDING FROM BEG CASE INSENSE 4", txtfci(fnd_tst_case, 24, ftesuto), 48))
	{
		p|tofind|N;
		dispPos(txtfci(fnd_tst_case, 24, ftesuto), ftesuto, 48);
	}
	if(T("FINDING FROM BEG CASE INSENSE 5", txtfci(fnd_tst_case, 44, 'r'), 54))
	{
		p|tofind|N;
		dispPos(txtfci(fnd_tst_case, 44, 'r'), wtxt('r'), 54);
	}
	
	//p|"\nSEARCHING FROM BEG ANY CHAR >>>>>>>>>>>>>>>>>>\n";
	wtxt fnd_any_char = WL("_83c3415-b3$f-414b-b@2e-826$a1bd7789a081bf9b-a6c1-4$54-a9a3-8b9a1221@@d_");
	
	ui64 fres = txtfa(fnd_any_char, 0, WL("_$@a"));
	T("FINDING FROM BEG ANY CHAR 0", fres, 0);
	fres = txtfa(fnd_any_char, fres+1, WL("_$@a"));
	T("FINDING FROM BEG ANY CHAR 1", fres, 11);
	fres = txtfa(fnd_any_char, fres+1, WL("_$@a"));
	T("FINDING FROM BEG ANY CHAR 2", fres, 20);
	fres = txtfa(fnd_any_char, fres+1, WL("_$@a"));
	T("FINDING FROM BEG ANY CHAR 3", fres, 27);
	fres = txtfa(fnd_any_char, fres+1, WL("_$@a"));
	T("FINDING FROM BEG ANY CHAR 4", fres, 28);
	fres = txtfa(fnd_any_char, fres+1, WL("_$@a"));
	T("FINDING FROM BEG ANY CHAR 5", fres, 36);
	fres = txtfa(fnd_any_char, fres+1, WL("_$@a"));
	T("FINDING FROM BEG ANY CHAR 6", fres, 45);
	fres = txtfa(fnd_any_char, fres+1, WL("_$@a"));
	T("FINDING FROM BEG ANY CHAR 7", fres, 51);
	fres = txtfa(fnd_any_char, fres+1, WL("_$@a"));
	T("FINDING FROM BEG ANY CHAR 8", fres, 55);
	fres = txtfa(fnd_any_char, fres+1, WL("_$@a"));
	T("FINDING FROM BEG ANY CHAR 9", fres, 57);
	fres = txtfa(fnd_any_char, fres+1, WL("_$@a"));
	T("FINDING FROM BEG ANY CHAR 10", fres, 63);
	fres = txtfa(fnd_any_char, fres+1, WL("_$@a"));
	T("FINDING FROM BEG ANY CHAR 11", fres, 68);
	fres = txtfa(fnd_any_char, fres+1, WL("_$@a"));
	T("FINDING FROM BEG ANY CHAR 12", fres, 69);
	fres = txtfa(fnd_any_char, fres+1, WL("_$@a"));
	T("FINDING FROM BEG ANY CHAR 13", fres, 71);
	
	///////////////////////////////////////////////////////////////////////
	
	#define IOT_SZ 61
	cwstr toins = WL("This_is_tesuto_insertion_!baka_this_T_tesutoraptor_text_baka!");
	wtxt ins = WL("<|||>");
	bool ins_ovr_failed = false;
	
	for(ui64 i = 0; i < IOT_SZ; ++i)
	{
		wtxt ins_tst = toins;
		txti(ins_tst, i, ins);
		if(TS(L("INSERTION TEST TXT I") + i2t(i), ins_tst, insert_tst_arr[i]))
		{
			ins_ovr_failed = true;
		}
	}
	for(ui64 i = 0; i < IOT_SZ; ++i)
	{
		wtxt ins_tst = toins;
		txti(ins_tst, i, WL("<|||>"));
		if(TS(L("INSERTION TEST CSTR I") + i2t(i), ins_tst, insert_tst_arr[i]))
		{
			ins_ovr_failed = true;
		}
	}
	for(ui64 i = 0; i < IOT_SZ; ++i)
	{
		wtxt ins_tst = toins;
		txti(ins_tst, i, '$');
		if(TS(L("INSERTION TEST CHAR I") + i2t(i), ins_tst, insert_char_tst_arr[i]))
		{
			ins_ovr_failed = true;
		}
	}
	
	TBOOL("INSERTION TESTS", ins_ovr_failed, false);
	
	for(ui64 i = 0; i < IOT_SZ; ++i)
	{
		wtxt ins_tst = toins;
		txto(ins_tst, i, ins);
		if(TS(L("INSERTION TEST TXT I") + i2t(i), ins_tst, overwr_tst_arr[i]))
		{
			ins_ovr_failed = true;
		}
	}
	for(ui64 i = 0; i < IOT_SZ; ++i)
	{
		wtxt ins_tst = toins;
		txto(ins_tst, i, WL("<|||>"));
		if(TS(L("INSERTION TEST CSTR I") + i2t(i), ins_tst, overwr_tst_arr[i]))
		{
			ins_ovr_failed = true;
		}
	}
	for(ui64 i = 0; i < IOT_SZ; ++i)
	{
		wtxt ins_tst = toins;
		txto(ins_tst, i, '$');
		if(TS(L("INSERTION TEST CHAR I") + i2t(i), ins_tst, overwr_char_tst_arr[i]))
		{
			ins_ovr_failed = true;
		}
	}
	
	TBOOL("OVERWRITING TESTS", ins_ovr_failed, false);
	
	wtxt overwrite_in_big_buf = 1024;
	overwrite_in_big_buf = WL("012345678");
	txto(overwrite_in_big_buf, 4, WL("____________REP____________"));
	T("OVERWRITING IN BIG BUFFER", overwrite_in_big_buf, WL("0123____________REP____________"));
	
	wtxt tst_path = WL("D:\\foo\\baka\\bar\\mod\\bot\\pot\\spot\\omicron.html");
	T("OVERWRITING ALL CHARACTERS", txtoa(tst_path, '\\', '/'), WL("D:/foo/baka/bar/mod/bot/pot/spot/omicron.html"));
	
	///////////////////////////////////////////////////////////////////////

	wtxt rep_tst = WL("0123456789_____0123456789");
	wtxt rep_txt = WL("|REPLACED|");
	wtxt rep_empty;
	wtxt rep = rep_tst;
	
	T("REPLACE POSITIONS TXT 0 3", txtrp(rep, 10, 14, rep_txt), WL("0123456789|REPLACED|0123456789"));
	rep = rep_tst;
	T("REPLACE POSITIONS CSTR 0 3", txtrp(rep, 15, TEND, WL("|REPLACED|")), WL("0123456789_____|REPLACED|"));
	rep = rep_tst;
	T("REPLACE POSITIONS CHAR 0 3", txtrp(rep, 0, 9, '$'), WL("$_____0123456789"));
	rep = rep_tst;
	
	T("REPLACE TXT 0 3", txtr(rep, 0, 3, rep_txt), WL("|REPLACED|3456789_____0123456789"));
	rep = rep_tst;
	T("REPLACE CSTR 0 3", txtr(rep, 0, 3, WL("|REPLACED|")), WL("|REPLACED|3456789_____0123456789"));
	rep = rep_tst;
	T("REPLACE CHAR 0 3", txtr(rep, 0, 3, '$'), WL("$3456789_____0123456789"));
	rep = rep_tst;
	
	T("REPLACE TXT 0 TEND", txtr(rep, 0, TEND, rep_txt), WL("|REPLACED|"));
	rep = rep_tst;
	T("REPLACE CSTR 0 TEND", txtr(rep, 0, TEND, WL("|REPLACED|")), WL("|REPLACED|"));
	rep = rep_tst;
	T("REPLACE CHAR 0 TEND", txtr(rep, 0, TEND, '$'), WL("$"));
	rep = rep_tst;
	
	T("REPLACE TXT 10 5", txtr(rep, 10, 5, rep_txt), WL("0123456789|REPLACED|0123456789"));
	rep = rep_tst;
	T("REPLACE CSTR 10 5", txtr(rep, 10, 5, WL("|REPLACED|")), WL("0123456789|REPLACED|0123456789"));
	rep = rep_tst;
	T("REPLACE CHAR 10 5", txtr(rep, 10, 5, '$'), WL("0123456789$0123456789"));
	rep = rep_tst;
	
	T("REPLACE TXT 10 0", txtr(rep, 10, 0, rep_txt), WL("0123456789|REPLACED|_____0123456789"));
	rep = rep_tst;
	T("REPLACE CSTR 10 0", txtr(rep, 10, 0, WL("|REPLACED|")), WL("0123456789|REPLACED|_____0123456789"));
	rep = rep_tst;
	T("REPLACE CHAR 10 0", txtr(rep, 10, 0, '$'), WL("0123456789$_____0123456789"));
	rep = rep_tst;
	
	T("REPLACE TXT 10 TEND", txtr(rep, 10, TEND, rep_txt), WL("0123456789|REPLACED|"));
	rep = rep_tst;
	T("REPLACE CSTR 10 TEND", txtr(rep, 10, TEND, WL("|REPLACED|")), WL("0123456789|REPLACED|"));
	rep = rep_tst;
	T("REPLACE CHAR 10 TEND", txtr(rep, 10, TEND, '$'), WL("0123456789$"));
	rep = rep_tst;
	
	T("REPLACE TXT ~rep-1 0", txtr(rep, ~rep-1, 0, rep_txt), WL("0123456789_____012345678|REPLACED|9"));
	rep = rep_tst;
	T("REPLACE CSTR ~rep-1 0", txtr(rep, ~rep-1, 0, WL("|REPLACED|")), WL("0123456789_____012345678|REPLACED|9"));
	rep = rep_tst;
	T("REPLACE CHAR ~rep-1 0", txtr(rep, ~rep-1, 0, '$'), WL("0123456789_____012345678$9"));
	rep = rep_tst;
	
	T("REPLACE TXT ~rep-3 6969", txtr(rep, ~rep-3, 6969, rep_txt), WL("0123456789_____0123456|REPLACED|"));
	rep = rep_tst;
	T("REPLACE CSTR ~rep-3 6969", txtr(rep, ~rep-3, 6969, WL("|REPLACED|")), WL("0123456789_____0123456|REPLACED|"));
	rep = rep_tst;
	T("REPLACE CHAR ~rep-3 6969", txtr(rep, ~rep-3, 6969, '$'), WL("0123456789_____0123456$"));
	rep = rep_tst;
	
	T("REPLACE EMPTY TXT 10 5", txtr(rep, 10, 5, rep_empty), WL("01234567890123456789"));
	rep = rep_tst;
	T("REPLACE EMPTY CSTR 10 5", txtr(rep, 10, 5, WL("")), WL("01234567890123456789"));
	rep = rep_tst;
	// Replacing with \0 is mistake, as size wont get updated, unless used with trimm operator!
	// Use txtd() for safe removal of text parts!
	
	T("DELETE 10 5", txtd(rep, 10, 5), WL("01234567890123456789"));
	rep = rep_tst;
	T("DELETE 3 TEND", txtd(rep, 3, TEND), WL("012"));
	rep = rep_tst;
	T("DELETE ~rep-1 1", txtd(rep, ~rep-1, 1), WL("0123456789_____012345678"));
	rep = rep_tst;
	T("DELETE POSITIONS", txtdp(rep, 10, 14), WL("01234567890123456789"));
	rep = rep_tst;
	
	T("REPLACE TXT ~rep-3 ~rep", txtr(rep, ~rep-3, ~rep, rep_txt), WL("0123456789_____0123456|REPLACED|"));
	rep = rep_tst;
	T("REPLACE CSTR ~rep-3 ~rep", txtr(rep, ~rep-3, ~rep, WL("|REPLACED|")), WL("0123456789_____0123456|REPLACED|"));
	rep = rep_tst;
	T("REPLACE CHAR ~rep-3 ~rep", txtr(rep, ~rep-3, ~rep, '$'), WL("0123456789_____0123456$"));
	rep = rep_tst;
	T("DELETE 3 ~rep", txtd(rep, 3, ~rep), WL("012"));
	rep = rep_tst;
	T("DELETE POSITIONS 10 ~rep", txtdp(rep, 10, ~rep), WL("0123456789"));
	rep = rep_tst;
	
#endif
	
#ifndef DEBUG
	bool t2ii2t_res = t2ii2tTest();
	p|N;
	TBOOL("TEXT 2 INT INT 2 TEXT", t2ii2t_res, false);
#endif
	
	T("I2HEX UI64 BEEF", i2wh((ui64)0xDEADBEEF), WL("00000000DEADBEEF"));
	T("I2HEX UI32 BEEF", i2wh((ui32)0xDEADBEEF), WL("DEADBEEF"));
	T("I2HEX UI16 BEEF", i2wh((ui16)0xBEEF), WL("BEEF"));
	T("I2HEX UI8 EF", b2wh((ui8)0xEF), WL("EF"));
	
	T("HEX2I UI64 BEEF", h2i(wtxt(WL("00000000DEADBEEF"))), 0xDEADBEEF);
	T("HEX2I UI32 BEEF", h2i(wtxt(WL("DEADBEEF"))), 0xDEADBEEF);
	T("HEX2I UI16 BEEF", h2i(wtxt(WL("BEEF"))), 0xBEEF);
	T("HEX2I UI8 EF", h2i(wtxt(WL("EF"))), 0xEF);
	
	T("I2TXT UI64 MAX", i2wt(UI64_MAX), WL("18446744073709551615"));
	T("I2TXT UI32 MAX", i2wt(UI32_MAX), WL("4294967295"));
	T("I2TXT UI16 MAX", i2wt(UI16_MAX), WL("65535"));
	T("I2TXT UI8 MAX", i2wt(UI8_MAX), WL("255"));
	
	T("I2TXT I64 MAX", i2wt(I64_MAX), WL("9223372036854775807"));
	T("I2TXT I32 MAX", i2wt(I32_MAX), WL("2147483647"));
	T("I2TXT I16 MAX", i2wt(I16_MAX), WL("32767"));
	T("I2TXT I8 MAX", i2wt(I8_MAX), WL("127"));
	
	T("I2TXT I64 MIN", i2wt(I64_MIN), WL("-9223372036854775808"));
	T("I2TXT I64 MIN+1", i2wt(I64_MIN+1), WL("-9223372036854775807"));
	T("I2TXT I32 MIN", i2wt(I32_MIN), WL("-2147483648"));
	T("I2TXT I32 MIN+1", i2wt(I32_MIN+1), WL("-2147483647"));
	T("I2TXT I16 MIN", i2wt(I16_MIN), WL("-32768"));
	T("I2TXT I16 MIN+1", i2wt(I16_MIN+1), WL("-32767"));
	T("I2TXT I8 MIN", i2wt(I8_MIN), WL("-128"));
	T("I2TXT I8 MIN+1", i2wt(I8_MIN+1), WL("-127"));
	
	T("TXT2I UI64 MAX", t2i(WL("18446744073709551615")), UI64_MAX);
	T("TXT2I UI32 MAX", t2i(WL("4294967295")), UI32_MAX);
	T("TXT2I UI16 MAX", t2i(WL("65535")), UI16_MAX);
	T("TXT2I UI8 MAX", t2i(WL("255")), UI8_MAX);
	
	T("TXT2I I64 MAX", (i64)t2i(WL("9223372036854775807")), I64_MAX);
	T("TXT2I I32 MAX", t2i(WL("2147483647")), I32_MAX);
	T("TXT2I I16 MAX", t2i(WL("32767")), I16_MAX);
	T("TXT2I I8 MAX", t2i(WL("127")), I8_MAX);
	
	T("TXT2I I64 MIN", t2i(WL("-9223372036854775808")), (ui64)I64_MIN);
	T("TXT2I I32 MIN", t2i(WL("-2147483648")), (ui64)I32_MIN);
	T("TXT2I I16 MIN", t2i(WL("-32768")), (ui64)I16_MIN);
	T("TXT2I I8 MIN", t2i(WL("-128")), (ui64)I8_MIN);
	
	ui64 i2hex_compact_ui64 = 0x4269;
	ui64 i2hex_compact_ui64_zero = 0x0;
	ui64 i2hex_compact_ui64_max = UI64_MAX;
	ui32 i2hex_compact_ui32 = 0x34;
	ui16 i2hex_compact_ui16 = 0xA;
	ui8 i2hex_compact_ui8 = 0xF;
	
	T("I2HEX COMPACT UI64", i2whc(i2hex_compact_ui64), WL("4269"));
	T("I2HEX COMPACT UI64 ZERO", i2whc(i2hex_compact_ui64_zero), WL("0"));
	T("I2HEX COMPACT UI64 MAX", i2whc(i2hex_compact_ui64_max), WL("FFFFFFFFFFFFFFFF"));
	T("I2HEX COMPACT UI32", i2whc(i2hex_compact_ui32), WL("34"));
	T("I2HEX COMPACT UI16", i2whc(i2hex_compact_ui16), WL("A"));
	T("I2HEX COMPACT UI8", i2whc(i2hex_compact_ui8), WL("F"));
	
	TBOOL("TXT NOT UNSIGNED INT 0", txtnui(t2u16(L("2223④34"))), true);
	TBOOL("TXT NOT UNSIGNED INT 1", txtnui(WL("693442")), false);
	TBOOL("TXT NOT SIGNED INT 0", txtnsi(WL("-234")), false);
	TBOOL("TXT NOT SIGNED INT 1", txtnsi(t2u16(L("-6934④42"))), true);
	TBOOL("TXT NOT SIGNED INT 2", txtnsi(WL("69F442")), true);
	TBOOL("TXT NOT HEX INT 0", txtnhi(WL("FF34AA")), false);
	TBOOL("TXT NOT HEX INT 1", txtnhi(t2u16(L("A93④04F2"))), true);
	
	//////////////////////////////////// TOLOW/UPPERCASE TEST ///////////////////////////////////////
	
	wtxt to_low_test =			WL("LOREM IPsUM DOLOR SIT aMET, CONSEcTETUR ADIPiSCING ELIT. P[LL]NTESqUE UT SUS__PIT MI, VEL CONDIMenTUM MetUS\t");
	const wtxt to_low_test_res =	WL("lorem ipsum dolor sit amet, consectetur adipiscing elit. p[ll]ntesque ut sus__pit mi, vel condimentum metus\t");
	wtxt to_up_test =			WL("Lorem Ipsum dolor sit Amet Consectetur adipiscing elit p{ll}ntesque Ut suscipit M~~vel condi012tum metus\t");
	const wtxt to_up_test_res =	WL("LOREM IPSUM DOLOR SIT AMET CONSECTETUR ADIPISCING ELIT P{LL}NTESQUE UT SUSCIPIT M~~VEL CONDI012TUM METUS\t");
	
	t2low(to_low_test);
	t2up(to_up_test);
	
	T("TO LOWERCASE", to_low_test, to_low_test_res);
	T("TO UPPERCASE", to_up_test, to_up_test_res);
	
	//////////////////////////////////// SUBSTEXTS TEST ///////////////////////////////////////
	
	wtxt subtxt_src = WL("-----------------------EXTRACT-ME-SENPAI!----------------");
	wtxt subtxt;
	
	T("SUBTEXT NUM OF CHARS", txts(subtxt_src, 23, 18), WL("EXTRACT-ME-SENPAI!"));
	T("SUBTEXT POSITIONS", txtsp(subtxt_src, 23, 40), WL("EXTRACT-ME-SENPAI!"));
	txts(subtxt, subtxt_src, 23, 18);
	T("SET SUBTEXT NUM OF CHARS", subtxt, WL("EXTRACT-ME-SENPAI!"));
	txtclr(subtxt);
	txtsp(subtxt, subtxt_src, 23, 40);
	T("SET SUBTEXT POSITIONS", subtxt, WL("EXTRACT-ME-SENPAI!"));
	
	/////////////////////////// ZERO TERMINATION CORRECTNESS TEST /////////////////////////////
	
	cwstr zero_term_cstr = WL("I. AM. ZERO. AND. I. AM. TERMINATED!!!");
	wtxt zero_term = zero_term_cstr;
	
	cwstr zero_concat_big_cstr = WL("--------------------THIS-IS-MUCH-BIGGER-THAN-BASE-TEXT--------------------");
	cwstr zero_concat_smol_cstr = WL("imsmol");
	wtxt zero_concat_big = zero_concat_big_cstr;
	wtxt zero_concat_smol = zero_concat_smol_cstr;
	
	wtxt zero_construct_txt = zero_term;
	T("ZERO TERMINATION CONSTRUCT TXT", getTerminator(zero_construct_txt), 0);
	wtxt zero_construct_cstr = zero_term_cstr;
	T("ZERO TERMINATION CONSTRUCT CSTR", getTerminator(zero_construct_cstr), 0);
	
	ui64 zero_sz_ui64 = 42;
	wtxt zero_construct_ui64 = zero_sz_ui64;
	T("ZERO TERMINATION CONSTRUCT UI64", getTerminator(zero_construct_ui64), 0);
	i64 zero_sz_i64 = 42;
	wtxt zero_construct_i64 = zero_sz_i64;
	T("ZERO TERMINATION CONSTRUCT I64", getTerminator(zero_construct_i64), 0);
	i32 zero_sz_i32 = 42;
	wtxt zero_construct_i32 = zero_sz_i32;
	T("ZERO TERMINATION CONSTRUCT I32", getTerminator(zero_construct_i32), 0);
	
	wtxt zero_construct_char = (wtxt)'X';
	T("ZERO TERMINATION CONSTRUCT CHAR", getTerminator(zero_construct_char), 0);
	
	
	wtxt zero_assign = zero_term;
	T("ZERO TERMINATION ASSIGN TXT", getTerminator(zero_assign), 0);
	zero_assign = zero_term_cstr;
	T("ZERO TERMINATION ASSIGN CSTR", getTerminator(zero_assign), 0);
	
	zero_assign = zero_sz_ui64;
	T("ZERO TERMINATION ASSIGN UI64", getTerminator(zero_assign), 0);
	zero_assign = zero_sz_i64;
	T("ZERO TERMINATION ASSIGN I64", getTerminator(zero_assign), 0);
	zero_assign = zero_sz_i32;
	T("ZERO TERMINATION ASSIGN I32", getTerminator(zero_assign), 0);
	
	zero_assign = (wtxt)'X';
	T("ZERO TERMINATION ASSIGN CHAR", getTerminator(zero_assign), 0);
	
	
	wtxt zero_manip = zero_term;
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
	
	
	wtxt zero_big_manip = 1024;
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
	p|"SIZEOF(WSTD):   " | sizeof(std::wstring) |N;
	p|"SIZEOF(WTXT):   " | sizeof(txt) |N |N;
	
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	
	test();
#endif
	
	p|N|N|N|N|TB|P;
	
	return 0;
}

#ifdef PROFILING_ON
///////////////////////////////////////////////////////////////////////////////////////////////
wchar_t lorem[2048];
const wchar_t *lorem_lit = L"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque ut suscipit mi, vel condimentum metus. Etiam vestibulum dapibus fermentum. Vivamus in maximus velit. Donec tempor turpis justo. Duis luctus id risus vitae accumsan. Duis volutpat tincidunt felis, non ullamcorper augue cursus quis. Morbi maximus, odio at pellentesque eleifend, erat magna accumsan risus, sollicitudin aliquet est nulla eu augue. Donec lectus nulla, volutpat eget diam at, egestas sodales neque. Sed interdum libero eget semper posuere. Interdum et malesuada fames ac ante ipsum primis in faucibus. In odio urna, ultrices in commodo in, sagittis fringilla elit. Sed non luctus ligula."

L"Nullam condimentum vitae turpis non tincidunt. Suspendisse vulputate leo ut pharetra viverra. Fusce varius purus sed quam vestibulum, non ullamcorper odio volutpat. Curabitur interdum tincidunt magna eget aliquet. Aliquam sit amet leo quis tellus eleifend tristique. Donec non risus massa. Nullam tincidunt sollicitudin sodales."

L"Cras rhoncus malesuada ligula, vitae sodales metus luctus sit amet. Interdum et malesuada fames ac ante ipsum primis in faucibus. Mauris eleifend neque vitae tortor semper condimentum. Phasellus aliquet neque nisl, ut auctor dui varius ac. Cras ut metus neque. Nunc consequat, leo ut lacinia venenatis, nisi orci hendrerit ex, ut lacinia sapien augue quis magna. Proin scelerisque at ex eu condimentum. Quisque ac condimentum quam. Vestibulum a pulvinar dolor. Nunc sodales lacinia varius. Cras luctus leo dui, quis lacinia quam ornare tempus. Maecenas magna libero, scelerisque quis pellentesque eu, efficitur sed magna. Mauris vestibulum lobortis sagittis. Vivamus mollis lacus ut risus vehicula pellentesque. Suspendisse a blandit augue.HA! DIDNT EXPECT DA !BAKA! HERE?!";

wchar_t lorem_sm[416];
const wchar_t *lorem_sm_lit = L"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque ut suscipit mi, vel condimentum metus. Etiam vestibulum dapibus fermentum. Vivamus in maximus velit. Donec tempor turpis justo. Duis luctus id risus vitae accumsan. Duis volutpat tincidunt felis, non ullamcorper augue cursus quis. Morbi maximus, odio at pellentesque eleifend, erat magna accumsan risus, sollicitudin aliquet est nulla eu augue.";

wchar_t chars_100[128];
const wchar_t *chars_100_lit = L"0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";

std::wstring lorem_std = lorem;
wtxt lorem_txt = lorem;

std::wstring char_std = L"$";
wtxt char_txt = L"$";

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
	volatile std::wstring s0 = lorem;
}
void __declspec(noinline) txtAllocCstrS1770()
{
	volatile wtxt s0 = lorem;
}
// =======================================================================================================
void __declspec(noinline) stdAllocTxtS1770()
{
	std::wstring s0 = lorem_std;
	
	for(ui64 i = 0; i < s0.size(); ++i)
	{
		s0[i] = (wchar_t)(GetTickCount() % 127);
	}
	
	volatile wchar_t *c = (volatile wchar_t *)HeapAlloc(GetProcessHeap(), 0, s0.size());
	memcpy((void *)c, s0.c_str(), s0.size());
	HeapFree(GetProcessHeap(), 0, (void *)c);
}
void __declspec(noinline) txtAllocTxtS1770()
{
	wtxt s0 = lorem_txt;
	
	for(ui64 i = 0; i < ~s0; ++i)
	{
		s0[i] = (wchar_t)(GetTickCount() % 127);
	}
	
	volatile wchar_t *c = (volatile wchar_t *)HeapAlloc(GetProcessHeap(), 0, ~s0);
	memcpy((void *)c, s0, ~s0);
	HeapFree(GetProcessHeap(), 0, (void *)c);
}
// =======================================================================================================
void __declspec(noinline) stdAllocChar()
{
	volatile wchar_t c0[2];
	volatile wchar_t c1[2];
	volatile wchar_t c2[2];
	volatile wchar_t c3[2];
	
	c0[0] = (GetTickCount() % 127);
	c1[0] = (GetTickCount() % 127);
	c2[0] = (GetTickCount() % 127);
	c3[0] = (GetTickCount() % 127);
	c0[1] = 0, c1[1] = 0, c2[1] = 0, c3[1] = 0;
	
	std::wstring s0 = (const wchar_t *)c0;
	std::wstring s1 = (const wchar_t *)c1;
	std::wstring s2 = (const wchar_t *)c2;
	std::wstring s3 = (const wchar_t *)c3;
	volatile wchar_t c;
	c = s0[0], c = s1[0], c = s2[0], c = s3[0];
}
void __declspec(noinline) txtAllocChar()
{
	volatile wchar_t c0[2];
	volatile wchar_t c1[2];
	volatile wchar_t c2[2];
	volatile wchar_t c3[2];
	
	c0[0] = (GetTickCount() % 127);
	c1[0] = (GetTickCount() % 127);
	c2[0] = (GetTickCount() % 127);
	c3[0] = (GetTickCount() % 127);
	c0[1] = 0, c1[1] = 0, c2[1] = 0, c3[1] = 0;
	
	wtxt s0 = (const wchar_t *)c0;
	wtxt s1 = (const wchar_t *)c1;
	wtxt s2 = (const wchar_t *)c2;
	wtxt s3 = (const wchar_t *)c3;
	volatile wchar_t c;
	c = s0[0], c = s1[0], c = s2[0], c = s3[0];
}
// =======================================================================================================
void __declspec(noinline) stdAllocTxtChar()
{
	std::wstring s0 = char_std;
	std::wstring s1 = char_std;
	std::wstring s2 = char_std;
	std::wstring s3 = char_std;
	volatile wchar_t c;
	c = s0[0], c = s1[0], c = s2[0], c = s3[0];
}
void __declspec(noinline) txtAllocTxtChar()
{
	wtxt s0 = char_txt;
	wtxt s1 = char_txt;
	wtxt s2 = char_txt;
	wtxt s3 = char_txt;
	volatile wchar_t c;
	c = s0[0], c = s1[0], c = s2[0], c = s3[0];
}
// =======================================================================================================
void __declspec(noinline) stdArrayAccess(std::wstring &s, volatile ui64 sz)
{
	for(ui64 i = 0; i < sz; ++i)
	{
		s[i] = '$';
	}
}
void __declspec(noinline) txtArrayAccess(wtxt &t, volatile ui64 sz)
{
	for(ui64 i = 0; i < sz; ++i)
	{
		t[i] = '$';
	}
}
// =======================================================================================================
void __declspec(noinline) stdAppendingStr(std::wstring &s)
{
	s += lorem_sm;
}
void __declspec(noinline) txtAppendingStr(wtxt &t)
{
	t += lorem_sm;
}
// =======================================================================================================
void __declspec(noinline) stdAppendingChar(std::wstring &s)
{
	s += '$';
}
void __declspec(noinline) txtAppendingChar(wtxt &t)
{
	t += '$';
}
// =======================================================================================================
void __declspec(noinline) stdFindingCstr(const std::wstring &s, const wchar_t *cstr, volatile ui64 i)
{
	volatile ui64 res = s.find(cstr + i % 30);
}
void __declspec(noinline) txtFindingCstr(const wtxt &t, const wchar_t *cstr, volatile ui64 i)
{
	volatile ui64 res = txtf(t, 0, cstr + i % 30);
}
// =======================================================================================================
void __declspec(noinline) stdFindingTxt(const std::wstring &s, const std::wstring &so)
{
	volatile ui64 res = s.find(so);
}
void __declspec(noinline) txtFindingTxt(const wtxt &t, const wtxt &to)
{
	volatile ui64 res = txtf(t, 0, to);
}
// =======================================================================================================
void __declspec(noinline) stdInserting(std::wstring &s, volatile ui64 sz)
{
	for(ui64 i = 0; i < sz; i += 100)
	{
		s.insert(i, L"!BAKA!_!IS!_!!HERE?!");
	}
}
void __declspec(noinline) txtInserting(wtxt &t, volatile ui64 sz)
{
	for(ui64 i = 0; i < sz; i += 100)
	{
		txti(t, i, L"!BAKA!_!IS!_!!HERE?!");
	}
}
// =======================================================================================================
void __declspec(noinline) stdOverwriting(std::wstring &s, volatile ui64 sz)
{
	for(ui64 i = 0; i + 100 < sz; i += 100)
	{
		s.replace(i, 20, L"!BAKA!_!IS!_!!HERE?!");
	}
}
void __declspec(noinline) txtOverwriting(wtxt &t, volatile ui64 sz)
{
	for(ui64 i = 0; i + 100 < sz; i += 100)
	{
		txtr(t, i, 20, L"!BAKA!_!IS!_!!HERE?!");
	}
}
// =======================================================================================================
void __declspec(noinline) stdCmpCstr(const std::wstring &s, const wchar_t *cstr)
{
	volatile bool res = s == cstr;
}
void __declspec(noinline) txtCmpCstr(const wtxt &t, const wchar_t *cstr)
{
	volatile bool64 res = t == cstr;
}
// =======================================================================================================
void __declspec(noinline) stdCmpTxt(const std::wstring &s, const std::wstring &so)
{
	volatile bool res = s == so;
}
void __declspec(noinline) txtCmpTxt(const wtxt &t, const wtxt &to)
{
	volatile bool64 res = t == to;
}
// =======================================================================================================
void __declspec(noinline) stdIntToText(std::wstring &s, volatile ui64 num)
{
	s = std::to_wstring(num);
}
void __declspec(noinline) txtIntToText(wtxt &t, volatile ui64 num)
{
	t = i2wt(num);
}
// =======================================================================================================
void __declspec(noinline) stdTextToInt(const std::wstring &s)
{
	volatile ui64 res = stoull(s);
}
void __declspec(noinline) txtTextToInt(const wtxt &t)
{
	volatile ui64 res = t2i(t);
}
// =======================================================================================================
void __declspec(noinline) stdIntToHex(std::wstring &s, volatile ui64 num)
{
	std::wstringstream ss;
	ss << std::hex << std::uppercase << num;
	s = ss.str();
}
void __declspec(noinline) txtIntToHex(wtxt &t, volatile ui64 num)
{
	t = i2wh(num);
}
// =======================================================================================================
void __declspec(noinline) stdHexToInt(const std::wstring &s)
{
	volatile ui64 res = stoull(s, nullptr, 16);
}
void __declspec(noinline) txtHexToInt(const wtxt &t)
{
	volatile ui64 res = h2i(t);
}
// =======================================================================================================
void __declspec(noinline) stdClearing(std::wstring &s)
{
	s.clear();
}
void __declspec(noinline) txtClearing(wtxt &t)
{
	txtclr(t); //txt_clr_a[i] = 0; // This is slower way to clear text
}
// =======================================================================================================
void __declspec(noinline) stdDestructing(std::wstring &s)
{
	typedef std::wstring std_string;
	s.~std_string();
}
void __declspec(noinline) txtDestructing(wtxt &t)
{
	t.~wtxt();
}
// =======================================================================================================
void __declspec(noinline) stdToLower()
{
	for(auto & c: lorem_std) c = (wchar_t)(rand() % 127);
	for(auto & c: lorem_std) c = (wchar_t)tolower(c);
}

void __declspec(noinline) txtToLower()
{
	for(ui64 i = 0; i < ~lorem_txt; ++i)
	{
		lorem_txt[i] = (wchar_t)(rand() % 127);
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
		
		RUN_TEST(ALLOC WTXT S1770, 142000/DBGM)
			stdAllocTxtS1770();
		MID_TEST
			txtAllocTxtS1770();
		END_TEST
		
		RUN_TEST(ALLOC CHAR, 1420000/DBGM)
			stdAllocChar();
		MID_TEST
			txtAllocChar();
		END_TEST
		
		RUN_TEST(ALLOC WTXT CHAR, 1420000/DBGM)
			stdAllocTxtChar();
		MID_TEST
			txtAllocTxtChar();
		END_TEST
		
		std::wstring str_lorem = lorem;
		wtxt txt_lorem = lorem;
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
		
		const wchar_t *fnd_str = L"HA! DIDNT EXPECT DA !BAKA! HERE?!";
		std::wstring fnd_str_std = fnd_str;
		wtxt fnd_str_txt = fnd_str;
		ui64 res = 0;
		str_lorem = lorem;
		txt_lorem = lorem;
		
		RUN_TEST(FINDING CSTR, 242000/DBGM)
			stdFindingCstr(str_lorem, fnd_str, i);
		MID_TEST
			txtFindingCstr(txt_lorem, fnd_str, i);
		END_TEST
		
		RUN_TEST(FINDING WTXT, 420000/DBGM)
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
		std::wstring str_lorem_o = str_lorem;
		txt_lorem = lorem;
		wtxt txt_lorem_o = txt_lorem;
		std::wstring str_not_lorem = L"NOT LOREM!";
		wtxt txt_not_lorem = L"NOT LOREM!";
		
		RUN_TEST(CMP CSTR WC, 242000/DBGM) // WORST CASE
			stdCmpCstr(str_lorem, lorem);
		MID_TEST
			txtCmpCstr(txt_lorem, lorem);
		END_TEST
		
		RUN_TEST(CMP CSTR BC, 4420000/DBGM) // BEST CASE
			stdCmpCstr(str_lorem, L"NOT LOREM!");
		MID_TEST
			txtCmpCstr(txt_lorem, L"NOT LOREM!");
		END_TEST
		
		RUN_TEST(CMP WTXT WC, 242000/DBGM)
			stdCmpTxt(str_lorem, str_lorem_o);
		MID_TEST
			txtCmpTxt(txt_lorem, txt_lorem_o);
		END_TEST
		
		RUN_TEST(CMP WTXT BC, 4420000/DBGM)
			stdCmpTxt(str_lorem, str_not_lorem);
		MID_TEST
			txtCmpTxt(txt_lorem, txt_not_lorem);
		END_TEST
		
		volatile ui64 num = 18000000042000000000;
		std::wstring str_num;
		wtxt txt_num;
		
		RUN_TEST(INT TO TEXT, 1420000/DBGM)
			stdIntToText(str_num, num);
		MID_TEST
			txtIntToText(txt_num, num);
		END_TEST
		
		const wchar_t *num_str = L"18000000042000000000";
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
		
		num_str = L"BEEFFAAA42006934";
		str_num = num_str;
		txt_num = num_str;
		
		RUN_TEST(HEX TO INT, 4420000/DBGM)
			stdHexToInt(str_num);
		MID_TEST
			txtHexToInt(txt_num);
		END_TEST
		
		std::wstring *std_clr_a =
			(std::wstring *)VirtualAlloc(NULL, 420000 * sizeof(std::wstring), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		wtxt *txt_clr_a =
			(wtxt *)VirtualAlloc(NULL, 420000 * sizeof(wtxt), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
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
		
		VirtualFree(std_clr_a, 0, MEM_RELEASE);
		VirtualFree(txt_clr_a, 0, MEM_RELEASE);
		
		SWIDRESET
		if(tst_amount == 0)
		{
			tst_amount = tst_id;
		}
		tst_id = 0;
	}
	
	p|TM;
	p|TCP(1)|TCP(0)		|TCP(8)	|TCP(0);
	p|""	|TAC|"WSTD"	|""		|"WTXT"|TN;
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