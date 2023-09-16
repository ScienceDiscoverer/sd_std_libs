// CONSOLE
#define MMANIP_VECTORS
#define MMANIP_INFERIOR
#include <mmanip>

#include <tests.h>

#pragma warning( disable : 4189 )

#define MMANIP_VECTORS
#define MMANIP_INFERIOR

char mem[10240];
char memo[10240];
char memb[1048576];
char mem_sm[42];
char mem_smo[42];
char membo[1048576];

const ui64 cstr_sz = 669;
const char *ccstr = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque ut suscipit mi, vel condimentum metus. Etiam vestibulum dapibus fermentum. Vivamus in maximus velit. Donec tempor turpis justo. Duis luctus id risus vitae accumsan. Duis volutpat tincidunt felis, non ullamcorper augue cursus quis. Morbi maximus, odio at pellentesque eleifend, erat magna accumsan risus, sollicitudin aliquet est nulla eu augue. Donec lectus nulla, volutpat eget diam at, egestas sodales neque. Sed interdum libero eget semper posuere. Interdum et malesuada fames ac ante ipsum primis in faucibus. In odio urna, ultrices in commodo in, sagittis fringilla elit. Sed non luctus ligula.";
const char *not_cstr = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque ut suscipit mi, vel condimentum metus. Etiam vestibulum dapibus fermentum. Vivamus in maximus velit. Donec tempor turpis justo. Duis luctus id risus vitae accumsan. Duis volutpat tincidunt felis, non ullamcorper augue cursus quis. Morbi maximus, odio at pellentesque eleifend, erat magna accumsan risus, sollicitudin aliquet est nulla eu augue. Donec lectus nulla, volutpat eget diam at, egestas sodales neque. Sed interdum libero eget SEMPER posuere. Interdum et malesuada fames ac ante ipsum primis in faucibus. In odio urna, ultrices in commodo in, sagittis fringilla elit. Sed non luctus ligula.";

const char *smol_tst0 = "i'm very smol :'(";
const char *smol_tst1 = "i'm very smol :'(";

const char *cstr_cmp = "123456789000____?";
const char *cstr_cmp_same = "123456789000____?";
const char *cstr_cmp_less = "12345678900+____?";
const char *cstr_cmp_bigg = "123456789001____?";

char mcpy_tst_buf[33] = "|REPLACED|";
const char *mcpy_tst = "3456789_____0123456789";
const char *mcpy_tst_res = "|REPLACED|3456789_____0123456789";

char lorem_buf[669];

ui64 mor_mand_tst_sz = 107;
char mor_test_buf_ch[108] = "LOREM IPsUM DOLOR SIT aMET, CONSEcTETUR ADIPiSCING ELIT. PELLENTESqUE UT SUSCIPIT MI, VEL CONDIMENTUM MetUS";
wchar_t mor_test_buf_wch[108] = L"LOREM IPsUM DOLOR SIT aMET, CONSEcTETUR ADIPiSCING ELIT. PELLENTESqUE UT SUSCIPIT MI, VEL CONDIMENTUM METUS";
char mand_test_buf[108] = "Lorem~Ipsum~dolor~sit~Amet~Consectetur~adipiscing~elit~pellentesque~Ut~suscipit~Mi~vel~condimentum~metus";
cstr mor_test_res_ch = L("lorem ipsum dolor sit amet, consectetur adipiscing elit. pellentesque ut suscipit mi, vel condimentum metus");
cwstr mor_test_res_wch = WL("lorem ipsum dolor sit amet, consectetur adipiscing elit. pellentesque ut suscipit mi, vel condimentum metus");
cstr mand_test_res = L("LOREM^IPSUM^DOLOR^SIT^AMET^CONSECTETUR^ADIPISCING^ELIT^PELLENTESQUE^UT^SUSCIPIT^MI^VEL^CONDIMENTUM^METUS");

//#define MEM_ALLIGN_TST
#ifdef MEM_ALLIGN_TST
void testMemAllign(const char *var_n, const void *m)
{
	p|var_n|" % 8 ---> ";
	if((ui64)m % 8 != 0)
	{
		p|R;
	}
	p|(ui64)m % 8|D|N;
}
#endif

void init()
{
#ifdef MEM_ALLIGN_TST
	testMemAllign("mem", mem);
	testMemAllign("memo", memo);
	testMemAllign("memb", memb);
	testMemAllign("mem_sm", mem_sm);
	testMemAllign("membo", membo);
	
	testMemAllign("ccstr", ccstr);
	testMemAllign("not_cstr", not_cstr);
	testMemAllign("smol_tst0", smol_tst0);
	testMemAllign("smol_tst1", smol_tst1);
	
	testMemAllign("cstr_cmp", cstr_cmp);
	testMemAllign("cstr_cmp_same", cstr_cmp_same);
	testMemAllign("cstr_cmp_less", cstr_cmp_less);
	testMemAllign("cstr_cmp_bigg", cstr_cmp_bigg);
	
	testMemAllign("mcpy_tst_buf", mcpy_tst_buf);
	testMemAllign("mcpy_tst", mcpy_tst);
	testMemAllign("mcpy_tst_res", mcpy_tst_res);
	
	testMemAllign("lorem_buf", lorem_buf);
	
	txt mtst0 = "hello wurld!";
	txt mtst1 = "hello wurldtxt hello wurld!hello wurld!";
	txt mtst2 = "hello wurld!hello wurld!";
	
	testMemAllign("mtst0", (const char *)mtst0);
	testMemAllign("mtst1", (const char *)mtst0);
	testMemAllign("mtst2", (const char *)mtst0);
	
	testMemAllign("mem + 2000", mem + 1995);
#endif
	
	memset(mem, 'x', 10240);
	memset(memo, 'x', 10240);
	memset(mem_sm, 'y', 42);
	memset(mem_smo, 'y', 42);
	memset(memb, 'x', 1048576);
	memset(membo, 'x', 1048576);
	memo[5555] = 'y';
	mem_smo[24] = 'x';
	membo[782458] = 'y';
}

void __declspec(noinline) trMcmp1mb()
{
	volatile ui64 x = (ui64)memcmp(memb, membo, 1048576);
}

void __declspec(noinline) tgMcmp1mb()
{
	volatile ui64 x = memeq(memb, membo, 1048576);
}

void __declspec(noinline) trMcmp10kb()
{
	volatile ui64 x = (ui64)memcmp(mem, memo, 10240);
}

void __declspec(noinline) tgMcmp10kb()
{
	volatile ui64 x = memeq(mem, memo, 10240);
}

void __declspec(noinline) trMcmp42b()
{
	volatile ui64 x = (ui64)memcmp(mem_sm, mem_smo, 42);
}

void __declspec(noinline) tgMcmp42b()
{
	volatile ui64 x = memeq(mem_sm, mem_smo, 42);
}

void __declspec(noinline) trMset10kb()
{
	volatile ui64 x = (ui64)memset(mem, 0, 10240);
}

void __declspec(noinline) tgMset10kb()
{
	mset(mem, 0, 10240);
}

void __declspec(noinline) trMsetc10kb()
{
	volatile ui64 x = (ui64)memset(mem, 'B', 10240);
}

void __declspec(noinline) tgMsetc10kb()
{
	msetc(mem, 'A', 10240);
}

void __declspec(noinline) trMsetwc10kb()
{
	volatile ui64 x = (ui64)memset(mem, 'C', 10240);
}

void __declspec(noinline) tgMsetwc10kb()
{
	msetwc(mem, 'D', 10240);
}

void __declspec(noinline) trMcpy1mb()
{
	volatile ui64 x = (ui64)memcpy(membo, memb, 1048576);
}

void __declspec(noinline) tgMcpy1mb()
{
	mcpy(membo, memb, 1048576);
}

void __declspec(noinline) trMcpy10kb()
{
	volatile ui64 x = (ui64)memcpy(memo, mem, 10240);
}

void __declspec(noinline) tgMcpy10kb()
{
	mcpy(memo, mem, 10240);
}

void __declspec(noinline) trMcpy42b()
{
	volatile ui64 x = (ui64)memcpy(mem_smo, mem_sm, 42);
}

void __declspec(noinline) tgMcpy42b()
{
	mcpy(mem_smo, mem_sm, 42);
}

void __declspec(noinline) trMmov10kb()
{
	volatile ui64 x = (ui64)memmove(mem + 1995, mem, 8000);
}

void __declspec(noinline) tgMmov10kb()
{
	mmov(mem + 1995, mem, 8000);
}

void minit();
void test(void (*testR)(), void (*testG)(), ui64 cyc);

i32 wmain()
{
	minit();
	init();
	
	p|TM;
	p|TCP(0)|TCP(0)	  |TCP(8)  |TCP(0);
	p|"  "|TAC|R|"RED"|  ""  |G|"GRN"|D|TN;
	p|TAL|"MCMP 1MB", test(trMcmp1mb, tgMcmp1mb, 20'000);
	p|TAL|"MCMP 10KB", test(trMcmp10kb, tgMcmp10kb, 200'000);
	p|TAL|"MCMP 4B", test(trMcmp42b, tgMcmp42b, 20'000'000);
	p|TAL|"MSET 10KB", test(trMset10kb, tgMset10kb, 200'000);
	p|TAL|"MSETC 10KB", test(trMsetc10kb, tgMsetc10kb, 200'000);
	p|TAL|"MSETWC 10KB", test(trMsetwc10kb, tgMsetwc10kb, 200'000);
	p|TAL|"MCPY 1MB", test(trMcpy1mb, tgMcpy1mb, 20'000);
	p|TAL|"MCPY 10KB", test(trMcpy10kb, tgMcpy10kb, 200'000);
	p|TAL|"MCPY 4B", test(trMcpy42b, tgMcpy42b, 20'000'000);
	p|TAL|"MMOV 10KB", test(trMmov10kb, tgMmov10kb, 200'000);
	p|TE|N;
	
	TBOOL("FMCMP EQU", memeq(ccstr, ccstr, cstr_sz), true);
	TBOOL("FMCMP NEQ", memeq(ccstr, not_cstr, cstr_sz), false);
	TBOOL("FMCMP SMOL", memeq(smol_tst0, smol_tst1, strl(smol_tst0)), true);
	
	TBOOL("MCMP EQU", mcmp(cstr_cmp_same, cstr_cmp, cstr_sz) == 0, true);
	TBOOL("MCMP SML", mcmp(cstr_cmp_less, cstr_cmp, cstr_sz) < 0, true);
	TBOOL("MCMP BIG", mcmp(cstr_cmp_bigg, cstr_cmp, cstr_sz) > 0, true);
	
	mcpy(lorem_buf, ccstr, cstr_sz);
	TBOOL("MCPY LOREM", memeq(lorem_buf, ccstr, cstr_sz), true);
	mcpy(mcpy_tst_buf + 10, mcpy_tst, 22);
	TBOOL("MCPY INSRT", memeq(mcpy_tst_buf, mcpy_tst_res, 32), true);
	
	mor(mor_test_buf_ch, 0x2020202020202020, mor_mand_tst_sz);
	mor(mor_test_buf_wch, 0x0020002000200020, mor_mand_tst_sz);
	mand(mand_test_buf, 0xDFDFDFDFDFDFDFDF, mor_mand_tst_sz);
	
	T("MOR CHAR", cstr({ mor_test_buf_ch, strl(mor_test_buf_ch) }), mor_test_res_ch);
	T("MOR WCHAR", cwstr({ mor_test_buf_wch, strl(mor_test_buf_wch) }), mor_test_res_wch);
	T("MAND", cstr({ mand_test_buf, strl(mand_test_buf) }), mand_test_res);
	
	p|P;
	return 0;
}

#pragma optimize( "", off )
void test(void (*testR)(), void (*testG)(), ui64 cyc)
{
	SWSET
	for(ui64 i = 0; i < cyc; ++i)
	{
		testR();
	}
	SWSTOP
	SWSET
	for(ui64 i = 0; i < cyc; ++i)
	{
		testG();
	}
	SWSTOP
	SWIDRESET
	
	SWPDIFF
	p|TN;
	
	SWIDRESET
	SWRESET
}
#pragma optimize( "", on )

void minit()
{
	COORD buf_s;
	buf_s.X = 64;
	buf_s.Y = 28;
	SMALL_RECT wnd_pos;
	wnd_pos.Top = 0;
	wnd_pos.Left = 0;
	wnd_pos.Right = 63;
	wnd_pos.Bottom = 27;
	HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(oh, TRUE, &wnd_pos);
	SetConsoleScreenBufferSize(oh, buf_s);
	
	p|DC;
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
}