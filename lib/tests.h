#pragma once

#include <sddb>
#include <txta>
#include <wtxta>

#include <Mmsystem.h>
#pragma comment ( lib , "winmm" )

#define T(x,y,z) test(false, false, __LINE__, (x), (y), (z))
#define TNOT(x,y,z) test(false, true, __LINE__, (x), (y), (z))
#define TS(x,y,z) test(true, false, __LINE__, (x), (y), (z))

#define TBOOL(x,y,z) testBool(false, false, __LINE__, (x), (y), (z))

#define CMP_START	p|Y|"--------------------------CMP--------------------------"|D|N|G|I|D
#define CMP_END(x)	p|G|I|N|I|D|(x)|G|I|D;p|N|Y|"--------------------------END--------------------------"|D|N;

ui64 first_fail = UI64_MAX;
COORD first_fail_con_pos;

inline bool fail()
{
	p|R|"FAILED"|D;
	PlaySoundA("D:\\Dropbox\\Sounds\\wahwahwaaaaah.wav", NULL, SND_FILENAME | SND_ASYNC);
	return true;
}

inline bool pass(bool silent)
{
	if(!silent)
	{
		p|G|"PASSED"|D;
	}
	return false;
}

inline bool goToTestFail()
{
	if(first_fail != UI64_MAX)
	{
		_dbgSelLineNoMark(first_fail);
		_dbgSetFocusToNpp();
		SetConsoleCursorPosition(_dbg_std_out_, first_fail_con_pos);
		p|DC;
		return true;
	}
	
	return false;
}

inline void setFirstFail(ui64 line)
{
	if(first_fail == UI64_MAX)
	{
		first_fail = line;
		static CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(_dbg_std_out_, &csbi);
		first_fail_con_pos = csbi.dwCursorPosition;
		--first_fail_con_pos.Y;
		_dbgSetCleanSelectsHandler();
	}
}

inline bool test(bool silent, bool nequ, ui64 line, const char *name, const txt &tst, const txt &res)
{
	bool failed;
	if(nequ)
	{
		failed = tst == res ? fail() : pass(silent);
	}
	else
	{
		failed = tst != res ? fail() : pass(silent);
	}
	
	if(!silent)
	{
		p|S|name|N;
	}
	
	if(failed)
	{
		if(~tst != ~res)
		{
			p|Y|"SIZE MISTMATCH: "|R|~tst|D|S|~res|N;
		}
		
		setFirstFail(line);
		
		_dbgHighlightLine(line);
		CMP_START;
		for(ui64 i = 0; i < ~tst; ++i)
		{
			p|(tst[i] != res[i] || i >= ~res ? R : D)|tst[i];
		}
		CMP_END(res);
	}
	
	return failed;
}

inline bool test(bool silent, bool nequ, ui64 line, const char *name, const wtxt &tst, const wtxt &res)
{
	bool failed;
	if(nequ)
	{
		failed = tst == res ? fail() : pass(silent);
	}
	else
	{
		failed = tst != res ? fail() : pass(silent);
	}
	
	if(!silent)
	{
		p|S|name|N;
	}
	
	if(failed)
	{
		if(~tst != ~res)
		{
			p|Y|"SIZE MISTMATCH: "|R|~tst|D|S|~res|N;
		}
		
		setFirstFail(line);
		
		_dbgHighlightLine(line);
		CMP_START;
		for(ui64 i = 0; i < ~tst; ++i)
		{
			p|(tst[i] != res[i] || i >= ~res ? R : D)|tst[i];
		}
		CMP_END(res);
	}
	
	return failed;
}

inline bool test(bool silent, bool nequ, ui64 line, const char *name, ui64 tst, ui64 res)
{
	bool failed;
	if(nequ)
	{
		failed = tst == res ? fail() : pass(silent);
	}
	else
	{
		failed = tst != res ? fail() : pass(silent);
	}
	
	if(!silent)
	{
		p|S|name|N;
	}
	
	if(failed)
	{
		setFirstFail(line);
		
		_dbgHighlightLine(line);
		txt tst_txt = i2t(tst);
		txt res_txt = i2t(res);
		
		CMP_START;
		for(ui64 i = 0; i < ~tst_txt; ++i)
		{
			p|(tst_txt[i] != res_txt[i] || i >= ~res_txt ? R : D)|tst_txt[i];
		}
		CMP_END(res_txt);
	}
	
	return failed;
}

inline bool test(bool silent, bool nequ, ui64 line, const char *name, i64 tst, i64 res)
{
	bool failed;
	if(nequ)
	{
		failed = tst == res ? fail() : pass(silent);
	}
	else
	{
		failed = tst != res ? fail() : pass(silent);
	}
	
	if(!silent)
	{
		p|S|name|N;
	}
	
	if(failed)
	{
		setFirstFail(line);
		
		_dbgHighlightLine(line);
		txt tst_txt = i2t(tst);
		txt res_txt = i2t(res);
		
		CMP_START;
		for(ui64 i = 0; i < ~tst_txt; ++i)
		{
			p|(tst_txt[i] != res_txt[i] || i >= ~res_txt ? R : D)|tst_txt[i];
		}
		CMP_END(res_txt);
	}
	
	return failed;
}

inline bool testBool(bool silent, bool nequ, ui64 line, const char *name, bool tst, bool res)
{
	bool failed;
	if(nequ)
	{
		failed = tst == res ? fail() : pass(silent);
	}
	else
	{
		failed = tst != res ? fail() : pass(silent);
	}
	
	if(!silent)
	{
		p|S|name|N;
	}
	
	if(failed)
	{
		setFirstFail(line);
		
		_dbgHighlightLine(line);
		txt tst_txt = tst ? L("true") : L("false");
		txt res_txt = res ? L("true") : L("false");
		
		CMP_START;
		for(ui64 i = 0; i < ~tst_txt; ++i)
		{
			p|(tst_txt[i] != res_txt[i] || i >= ~res_txt ? R : D)|tst_txt[i];
		}
		CMP_END(res_txt);
	}
	
	return failed;
}

inline bool testBool(bool silent, bool nequ, ui64 line, const char *name, bool64 tst, bool res)
{
	return testBool(silent, nequ, line, name, (bool)tst, res);;
}

inline bool test(bool silent, bool nequ, ui64 line, const char *name, const txta &tst, const txta &res)
{
	bool failed = false;
	ui64 failed_i = UI64_MAX;
	if(nequ)
	{
		if(~tst != ~res)
		{
			failed = pass(silent);
		}
		else
		{
			for(ui64 i = 0; i < ~tst; ++i)
			{
				failed = tst[i] == res[i];
				if(failed)
				{
					failed_i = i;
					break;
				}
			}
			
			if(failed)
			{
				fail();
			}
			else
			{
				pass(silent);
			}
		}
	}
	else
	{
		if(~tst != ~res)
		{
			failed = fail();
		}
		else
		{
			for(ui64 i = 0; i < ~tst; ++i)
			{
				failed = tst[i] != res[i];
				if(failed)
				{
					failed_i = i;
					break;
				}
			}
			
			if(failed)
			{
				fail();
			}
			else
			{
				pass(silent);
			}
		}
	}
	
	if(!silent)
	{
		p|S|name|N;
	}
	
	if(failed)
	{
		setFirstFail(line);
		
		_dbgHighlightLine(line);
		
		if(failed_i == UI64_MAX)
		{
			CMP_START;
			p|Y|"TXTA SIZE MISMATCH:"|N;
			p|R|~tst|D|N;
			CMP_END(~res);
			return failed;
		}
		
		txt tst_txt = tst[failed_i];
		txt res_txt = res[failed_i];
		
		p|"ARRAY ELEMENT MISTMATCH AT "|C|"INDEX "|failed_i|D|N;
		
		CMP_START;
		for(ui64 i = 0; i < ~tst_txt; ++i)
		{
			p|(tst_txt[i] != res_txt[i] || i >= ~res_txt ? R : D)|tst_txt[i];
		}
		CMP_END(res_txt);
	}
	
	return failed;
}

inline bool test(bool silent, bool nequ, ui64 line, const char *name, const wtxta &tst, const wtxta &res)
{
	bool failed = false;
	ui64 failed_i = UI64_MAX;
	if(nequ)
	{
		if(~tst != ~res)
		{
			failed = pass(silent);
		}
		else
		{
			for(ui64 i = 0; i < ~tst; ++i)
			{
				failed = tst[i] == res[i];
				if(failed)
				{
					failed_i = i;
					break;
				}
			}
			
			if(failed)
			{
				fail();
			}
			else
			{
				pass(silent);
			}
		}
	}
	else
	{
		if(~tst != ~res)
		{
			failed = fail();
		}
		else
		{
			for(ui64 i = 0; i < ~tst; ++i)
			{
				failed = tst[i] != res[i];
				if(failed)
				{
					failed_i = i;
					break;
				}
			}
			
			if(failed)
			{
				fail();
			}
			else
			{
				pass(silent);
			}
		}
	}
	
	if(!silent)
	{
		p|S|name|N;
	}
	
	if(failed)
	{
		setFirstFail(line);
		
		_dbgHighlightLine(line);
		
		if(failed_i == UI64_MAX)
		{
			CMP_START;
			p|Y|"WTXTA SIZE MISMATCH:"|N;
			p|R|~tst|D|N;
			CMP_END(~res);
			return failed;
		}
		
		wtxt tst_txt = tst[failed_i];
		wtxt res_txt = res[failed_i];
		
		p|"ARRAY ELEMENT MISTMATCH AT "|C|"INDEX "|failed_i|D|N;
		
		CMP_START;
		for(ui64 i = 0; i < ~tst_txt; ++i)
		{
			p|(tst_txt[i] != res_txt[i] || i >= ~res_txt ? R : D)|tst_txt[i];
		}
		CMP_END(res_txt);
	}
	
	return failed;
}