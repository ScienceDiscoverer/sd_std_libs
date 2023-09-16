// CONSOLE
#include <sddb>
#include <stdp>
#include <txta>
#include <wtxta>
#include <ui64a>

#include <tests.h>

#define TST_SZ 34

const char *rval_ret_cstra[] = {
	"Array entry #0",
	"Array entry #1",
	"Array entry #2",
	"Array entry #3",
	"Array entry #4",
	"Array entry #5",
	"Array entry #6",
	"Array entry #7",
	"Array entry #8",
	"Array entry #9",
	"Array entry #10",
	"Array entry #11",
	"Array entry #12",
	"Array entry #13",
	"Array entry #14",
	"Array entry #15",
	"Array entry #16",
	"Array entry #17",
	"Array entry #18",
	"Array entry #19",
	"Array entry #20",
	"Array entry #21",
	"Array entry #22",
	"Array entry #23",
	"Array entry #24",
	"Array entry #25",
	"Array entry #26",
	"Array entry #27",
	"Array entry #28",
	"Array entry #29",
	"Array entry #30",
	"Array entry #31",
	"Array entry #32",
	"Array entry #33",
	"" };

const wchar_t *rval_ret_wcstra[] = {
	L"Array entry #0",
	L"Array entry #1",
	L"Array entry #2",
	L"Array entry #3",
	L"Array entry #4",
	L"Array entry #5",
	L"Array entry #6",
	L"Array entry #7",
	L"Array entry #8",
	L"Array entry #9",
	L"Array entry #10",
	L"Array entry #11",
	L"Array entry #12",
	L"Array entry #13",
	L"Array entry #14",
	L"Array entry #15",
	L"Array entry #16",
	L"Array entry #17",
	L"Array entry #18",
	L"Array entry #19",
	L"Array entry #20",
	L"Array entry #21",
	L"Array entry #22",
	L"Array entry #23",
	L"Array entry #24",
	L"Array entry #25",
	L"Array entry #26",
	L"Array entry #27",
	L"Array entry #28",
	L"Array entry #29",
	L"Array entry #30",
	L"Array entry #31",
	L"Array entry #32",
	L"Array entry #33",
	L"" };
	
const wtxt rval_ret_wctxta[] = {
	WL("Array entry #0"),
	WL("Array entry #1"),
	WL("Array entry #2"),
	WL("Array entry #3"),
	WL("Array entry #4"),
	WL("Array entry #5"),
	WL("Array entry #6"),
	WL("Array entry #7"),
	WL("Array entry #8"),
	WL("Array entry #9"),
	WL("Array entry #10"),
	WL("Array entry #11"),
	WL("Array entry #12"),
	WL("Array entry #13"),
	WL("Array entry #14"),
	WL("Array entry #15"),
	WL("Array entry #16"),
	WL("Array entry #17"),
	WL("Array entry #18"),
	WL("Array entry #19"),
	WL("Array entry #20"),
	WL("Array entry #21"),
	WL("Array entry #22"),
	WL("Array entry #23"),
	WL("Array entry #24"),
	WL("Array entry #25"),
	WL("Array entry #26"),
	WL("Array entry #27"),
	WL("Array entry #28"),
	WL("Array entry #29"),
	WL("Array entry #30"),
	WL("Array entry #31"),
	WL("Array entry #32"),
	WL("Array entry #33"),
	WL("") };

txta rval_ret_txta_empty = rval_ret_cstra;
txta rval_ret_txta_sz(rval_ret_cstra, 34);

wtxta rval_ret_wtxta_empty = rval_ret_wcstra;
wtxta rval_ret_wtxta_sz(rval_ret_wcstra, 34);

wtxta rval_ret_wtxta_empty_wtxt = rval_ret_wctxta;
wtxta rval_ret_wtxta_sz_wtxt(rval_ret_wctxta, 34);

txta __declspec(noinline) rvalTxtReturner()
{
	txta taa = TST_SZ; // ...uses it instead of creating local [taa]!
	for(ui64 i = 0; i < TST_SZ; ++i)
	{
		taa << L("Array entry #") + i2t(i);
	}
	
	return taa;
}

wtxta __declspec(noinline) rvalWtxtReturner()
{
	wtxta taa = TST_SZ;
	for(ui64 i = 0; i < TST_SZ; ++i)
	{
		taa << WL("Array entry #") + i2wt(i);
	}
	
	return taa;
}

i32 wmain()
{
	// TXTA TESTS =======================================================================
{
	txta ta = rvalTxtReturner(); // Complier is smartass! Passes &ta as hidden parameter...
	
	T("TXTA RVAL GLOBAL CSTRA INIT EMPTY TERMINATED", ta, rval_ret_txta_empty);
	T("TXTA RVAL GLOBAL CSTRA INIT SIZE KNOWN", ta, rval_ret_txta_empty);
	
	txta empty_txta;
	TBOOL("TXTA TOTALLY EMPTY CHECK", empty_txta == empty, true);
	TBOOL("TXTA TOTALLY NOT EMPTY CHECK", ta == empty, false);
}
{
	const char *lval_res_construct_cstra[] = {
		"rval_val0", "rval_val1", "rval_val2", "rval_val3", "" };
	txta lval_res_construct = lval_res_construct_cstra;
	txta lval = txta(42) << L("rval_val0") << L("rval_val1") << L("rval_val2") << L("rval_val3");
	// Copy constructor is called here... Why in the world?
	
	T("TXTA LVAL FROM RVAL CONSTRUCT", lval, lval_res_construct);
	T("TXTA LVAL FROM RVAL CONSTRUCT TRUE SIZE", !lval, 4);

	const char *lval_res_assign_cstra[] = {
		"ass_rval_val0", "ass_rval_val1", "ass_rval_val2", "ass_rval_val3", "ASS_RVAL_VAL4", "" };
	txta lval_res_assign = lval_res_assign_cstra;
	lval = txta(69) << L("ass_rval_val0") << L("ass_rval_val1") << L("ass_rval_val2") << L("ass_rval_val3") << L("ASS_RVAL_VAL4");
	
	T("TXTA LVAL FROM RVAL ASSIGN", lval, lval_res_assign);
	T("TXTA LVAL FROM RVAL ASSIGN TRUE SIZE", !lval, 5);
}
{
	const char *uniq_res0_cstra[] = {
		"val_0", "val_0", "val_1", "val_2", "val_3", "" };
	txta uniq_res0 = uniq_res0_cstra;
	txta uniq;
	uniq << L("val_0") << L("val_0") << L("val_1");
	uniq.AddUnique(L("val_0"));
	uniq.AddUnique(L("val_0"));
	uniq.AddUnique(L("val_0"));
	uniq.AddUnique(L("val_1"));
	uniq.AddUnique(L("val_2"));
	uniq.AddUnique(L("val_3"));
	
	T("TXTA NORMAL + UNIQUE APPENDS", uniq, uniq_res0);
	
	uniq.Clear();
	
	T("TXTA CLEAR SIZE", ~uniq, 0);
	TNOT("TXTA CLEAR TRUE SIZE", !uniq, 0);
	
	const char *uniq_res1_cstra[] = {
		"val_0", "val_1", "val_2", "val_3", "val_4", "" };
	txta uniq_res1 = uniq_res1_cstra;
	
	uniq.AddUnique(L("val_0"));
	uniq.AddUnique(L("val_1"));
	uniq.AddUnique(L("val_2"));
	uniq.AddUnique(L("val_3"));
	uniq.AddUnique(L("val_4"));
	
	T("TXTA UNIQUE APPENDS", uniq, uniq_res1);
}
	// WTXTA TESTS ======================================================================
{
	wtxta ta = rvalWtxtReturner();
	
	T("WTXTA RVAL GLOBAL CSTRA INIT EMPTY TERMINATED", ta, rval_ret_wtxta_empty);
	T("WTXTA RVAL GLOBAL CSTRA INIT SIZE KNOWN", ta, rval_ret_wtxta_empty);
	
	T("WTXTA RVAL GLOBAL CWTXTA INIT EMPTY TERMINATED", ta, rval_ret_wtxta_empty_wtxt);
	T("WTXTA RVAL GLOBAL CWTXTA INIT SIZE KNOWN", ta, rval_ret_wtxta_sz_wtxt);
}
{
	const wchar_t *lval_res_construct_cstra[] = {
		L"rval_val0", L"rval_val1", L"rval_val2", L"rval_val3", L"" };
	wtxta lval_res_construct = lval_res_construct_cstra;
	wtxta lval = wtxta(42) << WL("rval_val0") << WL("rval_val1") << WL("rval_val2") << WL("rval_val3");
	// Copy constructor is called here... Why in the world?
	
	T("WTXTA LVAL FROM RVAL CONSTRUCT", lval, lval_res_construct);
	T("WTXTA LVAL FROM RVAL CONSTRUCT TRUE SIZE", !lval, 4);

	const wchar_t *lval_res_assign_cstra[] = {
		L"ass_rval_val0", L"ass_rval_val1", L"ass_rval_val2", L"ass_rval_val3", L"ASS_RVAL_VAL4", L"" };
	wtxta lval_res_assign = lval_res_assign_cstra;
	lval = wtxta(69) << WL("ass_rval_val0") << WL("ass_rval_val1") << WL("ass_rval_val2") << WL("ass_rval_val3") << WL("ASS_RVAL_VAL4");
	
	T("WTXTA LVAL FROM RVAL ASSIGN", lval, lval_res_assign);
	T("WTXTA LVAL FROM RVAL ASSIGN TRUE SIZE", !lval, 5);
}
{
	const wchar_t *uniq_res0_cstra[] = {
		L"val_0", L"val_0", L"val_1", L"val_2", L"val_3", L"" };
	wtxta uniq_res0 = uniq_res0_cstra;
	wtxta uniq;
	uniq << WL("val_0") << WL("val_0") << WL("val_1");
	uniq.AddUnique(WL("val_0"));
	uniq.AddUnique(WL("val_0"));
	uniq.AddUnique(WL("val_0"));
	uniq.AddUnique(WL("val_1"));
	uniq.AddUnique(WL("val_2"));
	uniq.AddUnique(WL("val_3"));
	
	T("WTXTA NORMAL + UNIQUE APPENDS", uniq, uniq_res0);
	
	uniq.Clear();
	
	T("WTXTA CLEAR SIZE", ~uniq, 0);
	TNOT("WTXTA CLEAR TRUE SIZE", !uniq, 0);
	
	const wchar_t *uniq_res1_cstra[] = {
		L"val_0", L"val_1", L"val_2", L"val_3", L"val_4", L"" };
	wtxta uniq_res1 = uniq_res1_cstra;
	
	uniq.AddUnique(WL("val_0"));
	uniq.AddUnique(WL("val_1"));
	uniq.AddUnique(WL("val_2"));
	uniq.AddUnique(WL("val_3"));
	uniq.AddUnique(WL("val_4"));
	
	T("WTXTA UNIQUE APPENDS", uniq, uniq_res1);
	
	wtxta move_from_me = rval_ret_wcstra;
	wtxta move_into_me = uniq_res1_cstra;
	move_from_me.MoveInto(move_into_me);
	
	T("WTXTA MOVE INTO DST", move_into_me, rval_ret_wtxta_empty);
	T("WTXTA MOVE INTO SRC SZ", ~move_from_me, 0);
	T("WTXTA MOVE INTO SRC TSZ", !move_from_me, 0);
}
	// UI64A TESTS ======================================================================	
{
	ui64a ints;
	bool64 ints_failed = false;
	ui64 ints_tst[10] = { 43, 34, 69, 42, 999987, 430, 340, 690, 420, 9999870 };
	
	ints << 43 << 34 << 69 << 42 << 999987;
	ints << 430 << 340 << 690 << 420 << 9999870;
	
	for(ui64 i = 0; i < ~ints; ++i)
	{
		if(TS(L("UI64A << OPERATOR") + i2t(i), ints[i], ints_tst[i]))
		{
			ints_failed = true;
		}
	}
	
	T("UI64A << OPERATOR", ints_failed, false);
}
{
	ui64 uniq_tst[10] = { 42, 34, 4477 };
	ui64a uniq;
	uniq.AddUnique(42);
	uniq.AddUnique(42);
	uniq.AddUnique(34);
	uniq.AddUnique(34);
	uniq.AddUnique(42);
	uniq.AddUnique(34);
	uniq.AddUnique(4477);
	
	T("UI64A UNIQUE APPENDS I0", uniq[0], uniq_tst[0]);
	T("UI64A UNIQUE APPENDS I1", uniq[1], uniq_tst[1]);
	T("UI64A UNIQUE APPENDS I2", uniq[2], uniq_tst[2]);
	
	ui64a fill = 12;
	fill.Fill(0);
	
	bool64 fill_failed = false;
	for(ui64 i = 0; i < ~fill; ++i)
	{
		if(TS(L("UI64A FILL ZERO ") + i2t(i), fill[i], 0))
		{
			fill_failed = true;
		}
	}
	
	T("UI64A FILL ZERO SIZE", ~fill, 12);
	T("UI64A FILL ZERO", fill_failed, false);
	
	ui64a fill_42 = 42;
	fill_42.Fill(42);
	
	fill_failed = false;
	for(ui64 i = 0; i < ~fill_42; ++i)
	{
		if(TS(L("UI64A 42FILL ") + i2t(i), fill_42[i], 42))
		{
			fill_failed = true;
		}
	}
	
	T("UI64A 42FILL SIZE", ~fill_42, 42);
	T("UI64A 42FILL", fill_failed, false);
	
	ui64a reserve;
	reserve.Reserve(69);
	
	T("UI64A RESERVE TSIZE", !reserve, 69);
	
	reserve << 69, reserve << 42, reserve << 34;
	
	reserve.Reserve(128);
	
	T("UI64A RESERVE WITH DATA TSIZE", !reserve, 128);
	T("UI64A RESERVE WITH DATA SIZE", ~reserve, 3);
	T("UI64A RESERVE WITH DATA 0", reserve[0], 69);
	T("UI64A RESERVE WITH DATA 1", reserve[1], 42);
	T("UI64A RESERVE WITH DATA 2", reserve[2], 34);
	
	reserve.Reserve(34);
	
	T("UI64A RESERVE LESS TSIZE", !reserve, 128);
	T("UI64A RESERVE LESS SIZE", ~reserve, 3);
	T("UI64A RESERVE LESS 0", reserve[0], 69);
	T("UI64A RESERVE LESS 1", reserve[1], 42);
	T("UI64A RESERVE LESS 2", reserve[2], 34);
	
	///////////////////////////// FND // DEL /////////////////////////////
	
	ui64a fnd;
	fnd << 43 << 34 << 69 << 42 << 999987 << 0xDEADBEEF;
	
	T("UI64A FIND 0", fnd.Find(0xDEADBEEF), 5);
	T("UI64A FIND 1", fnd.Find(69), 2);
	
	TBOOL("UI64A DEL LAST 0", ~fnd.DelLast() == 5 &&
	fnd[0] == 43 &&
	fnd[1] == 34 &&
	fnd[2] == 69 &&
	fnd[3] == 42 &&
	fnd[4] == 999987, true);
	TBOOL("UI64A DEL LAST 1", ~fnd.DelLast() == 4 &&
	fnd[0] == 43 &&
	fnd[1] == 34 &&
	fnd[2] == 69 &&
	fnd[3] == 42, true);
	TBOOL("UI64A DEL LAST 2", ~fnd.DelLast() == 3 &&
	fnd[0] == 43 &&
	fnd[1] == 34 &&
	fnd[2] == 69, true);
	TBOOL("UI64A DEL LAST 3", ~fnd.DelLast() == 2 &&
	fnd[0] == 43 &&
	fnd[1] == 34, true);
	TBOOL("UI64A DEL LAST 4", ~fnd.DelLast() == 1 &&
	fnd[0] == 43, true);
	TBOOL("UI64A DEL LAST 4", ~fnd.DelLast() == 0, true);
	
	fnd << 43 << 34 << 69 << 42 << 999987 << 0xDEADBEEF;
	
	TBOOL("UI64A DEL IDX 0", ~fnd.DelIdx(2) == 5 &&
	fnd[0] == 43 &&
	fnd[1] == 34 &&
	fnd[2] == 42 &&
	fnd[3] == 999987 &&
	fnd[4] == 0xDEADBEEF, true);
	
	fnd.Clear();
	fnd << 43 << 34 << 69 << 42 << 999987 << 0xDEADBEEF;
	
	TBOOL("UI64A DEL IDX 1", ~fnd.DelIdx(0) == 5 &&
	fnd[0] == 34 &&
	fnd[1] == 69 &&
	fnd[2] == 42 &&
	fnd[3] == 999987 &&
	fnd[4] == 0xDEADBEEF, true);
	
	fnd.Clear();
	fnd << 43 << 34 << 69 << 42 << 999987 << 0xDEADBEEF;
	
	TBOOL("UI64A DEL IDX 2", ~fnd.DelIdx(~fnd-1) == 5 &&
	fnd[0] == 43 &&
	fnd[1] == 34 &&
	fnd[2] == 69 &&
	fnd[3] == 42 &&
	fnd[4] == 999987, true);
	
	fnd.Clear();
	fnd << 43 << 34 << 69 << 42 << 999987 << 0xDEADBEEF;
	
	TBOOL("UI64A DEL VAL 0", ~fnd.DelVal(69) == 5 &&
	fnd[0] == 43 &&
	fnd[1] == 34 &&
	fnd[2] == 42 &&
	fnd[3] == 999987 &&
	fnd[4] == 0xDEADBEEF, true);
	
	fnd.Clear();
	fnd << 43 << 34 << 69 << 42 << 999987 << 0xDEADBEEF;
	
	TBOOL("UI64A DEL VAL 1", ~fnd.DelVal(43) == 5 &&
	fnd[0] == 34 &&
	fnd[1] == 69 &&
	fnd[2] == 42 &&
	fnd[3] == 999987 &&
	fnd[4] == 0xDEADBEEF, true);
	
	fnd.Clear();
	fnd << 43 << 34 << 69 << 42 << 999987 << 0xDEADBEEF;
	
	TBOOL("UI64A DEL VAL 2", ~fnd.DelVal(0xDEADBEEF) == 5 &&
	fnd[0] == 43 &&
	fnd[1] == 34 &&
	fnd[2] == 69 &&
	fnd[3] == 42 &&
	fnd[4] == 999987, true);
}
	
	
	
	
	goToTestFail();
	p|DC|TB|N|N|N|N|P;
	return 0;
}