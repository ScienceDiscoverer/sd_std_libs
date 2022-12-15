// SLIB
#include "txt"

HANDLE txt::h = HeapCreate(HEAP_FLAGS, 0, 0);

txt & txt::operator+=(const txt &o)
{
	ui64 ns = s + o.s;
	if(ts <= ns)
	{
		ui64 nts;
		char *tmp = AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		memcpy(tmp, t, s);
		this->txt::~txt(); // Uses true size
		t = tmp;
		ts = nts;
	}
	
	memcpy(t+s, o.t, o.s);
	s = ns;
	
	return *this;
}

txt & txt::operator+=(const char *cs)
{
	ui64 ss = Sl(cs), ns = s + ss;
	if(ts <= ns)
	{
		ui64 nts;
		char *tmp = AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		memcpy(tmp, t, s);
		this->txt::~txt(); // Uses true size
		t = tmp;
		ts = nts;
	}
	memcpy(t+s, cs, ss);
	s = ns;
	
	return *this;
}

txt & txt::operator+=(char c) // Very effective for rapid chars appending
{
	ui64 ns = s + 1;
	if(ts <= ns)
	{
		ui64 nts;
		char *tmp = AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		memcpy(tmp, t, s);
		this->txt::~txt(); // Uses true size
		t = tmp;
		ts = nts;
	}

	t[s] = c;
	s = ns;
	
	return *this;
}

txt & txt::operator--()
{
	s = txt::Sl(t);
	ui64 nts;
	char *tmp = AllocTmp(s, &nts);
	memcpy(tmp, t, s);
	this->txt::~txt(); // Uses true size
	t = tmp;
	ts = nts;
	
	return *this;
}

void txt::ExceptBuff(DWORD c, ui64 pos) const
{
	static ui64 nts;               // Leaking memory here for debug purposes
	char *tmp = AllocTmp(s, &nts); // This will allow for temp texts to be passed
	memcpy(tmp, t, s);
	
	static ULONG_PTR params[4];
	params[0] = (ULONG_PTR)tmp;
	params[1] = EXCEPT_TXT_UTF8;
	params[2] = s;
	params[3] = pos;
	RaiseException(c, 0, 4, params);
}

void txt::ExceptNum(DWORD c) const
{
	static ui64 nts;
	char *tmp = AllocTmp(s, &nts);
	memcpy(tmp, t, s);
	
	static ULONG_PTR params[3];
	params[0] = (ULONG_PTR)tmp;
	params[1] = EXCEPT_TXT_UTF8;
	params[2] = s;
	RaiseException(c, 0, 3, params);
}

ui64 operator>>(const txt &fnd, const txt &t)
{
	if(fnd.s > t.s)
	{
		return NFND;
	}
	
	const char *fb = fnd.t-1, *fe = fnd.t + fnd.s;
	const char *tb = t.t-1, *te = t.t + t.s - fnd.s;
	const char *tb_cur = NULL;
	
	while(tb != te)
	{
		tb_cur = tb;
		while(++fb != fe)
		{
			if(*fb != *(++tb_cur))
			{
				fb = fnd.t-1;
				break;
			}				
		}
		
		++tb;
		if(fb == fe)
		{
			return ui64(tb - t.t);
		}
	}
	
	return NFND;
}

ui64 operator>>(const char *fnd, const txt &t) // x2.93 VS STD Finding Test
{
	ui64 fnds = txt::Sl(fnd);
	
	if(fnds > t.s)
	{
		return NFND;
	}

	const char *fb = fnd-1, *fe = fnd + fnds;
	const char *tb = t.t-1, *te = t.t + t.s - fnds;
	const char *tb_cur = NULL;
	
	while(tb != te)
	{
		tb_cur = tb;
		while(++fb != fe)
		{
			if(*fb != *(++tb_cur))
			{
				fb = fnd-1;
				break;
			}				
		}
		
		++tb;
		if(fb == fe)
		{
			return ui64(tb - t.t);
		}
	}
	
	return NFND;
}

ui64 operator>>(char fnd, const txt &t)
{
	const char *tb = t.t-1, *te = t.t + t.s;
	
	while(++tb != te)
	{	
		if(*tb == fnd)
		{
			return ui64(tb - t.t);
		}
	}
	
	return NFND;
}

ui64 operator<<(const txt &fnd, const txt &t)
{
	if(fnd.s > t.s)
	{
		return NFND;
	}
	
	const char *fb = fnd.t-1, *fe = fnd.t + fnd.s;
	const char *tb = t.t-1, *te = t.t + t.s - fnd.s;
	const char *tb_cur = NULL;
	
	while(te != tb)
	{
		tb_cur = --te;
		while(++fb != fe)
		{
			if(*fb != *(++tb_cur))
			{
				fb = fnd.t-1;
				break;
			}				
		}
		
		if(fb == fe)
		{
			return ui64(te + 1 - t.t);
		}
	}
	
	return NFND;
}

ui64 operator<<(const char *fnd, const txt &t)
{
	ui64 fnds = txt::Sl(fnd);
	
	if(fnds > t.s)
	{
		return NFND;
	}
	
	const char *fb = fnd-1, *fe = fnd + fnds;
	const char *tb = t.t-1, *te = t.t + t.s - fnds;
	const char *tb_cur = NULL;
	
	while(te != tb)
	{
		tb_cur = --te;
		while(++fb != fe)
		{
			if(*fb != *(++tb_cur))
			{
				fb = fnd-1;
				break;
			}				
		}
		
		if(fb == fe)
		{
			return ui64(te + 1 - t.t);
		}
	}
	
	return NFND;
}

ui64 operator<<(char fnd, const txt &t)
{
	const char *tb = t.t-1, *te = t.t + t.s;
	
	while(--te != tb)
	{	
		if(*te == fnd)
		{
			return ui64(te - t.t);
		}
	}
	
	return NFND;
}

ui64 txtf(const txt &t, ui64 pos, const txt &fnd)
{
	if(fnd.s > t.s)
	{
		return NFND;
	}
	
	if(pos > t.s - fnd.s)
	{
		return NFND;
	}
	
	const char *fb = fnd.t-1, *fe = fnd.t + fnd.s;
	const char *tb = t.t + pos - 1, *te = t.t + t.s - fnd.s;
	const char *tb_cur = NULL;
	
	while(tb != te)
	{
		tb_cur = tb;
		while(++fb != fe)
		{
			if(*fb != *(++tb_cur))
			{
				fb = fnd.t-1;
				break;
			}				
		}
		
		++tb;
		if(fb == fe)
		{
			return ui64(tb - t.t);
		}
	}
	
	return NFND;
}

ui64 txtf(const txt &t, ui64 pos, const char *fnd)
{
	ui64 fnds = txt::Sl(fnd);
	
	if(fnds > t.s)
	{
		return NFND;
	}
	
	if(pos > t.s - fnds)
	{
		return NFND;
	}
	
	const char *fb = fnd-1, *fe = fnd + fnds;
	const char *tb = t.t + pos - 1, *te = t.t + t.s - fnds;
	const char *tb_cur = NULL;
	
	while(tb != te)
	{
		tb_cur = tb;
		while(++fb != fe)
		{
			if(*fb != *(++tb_cur))
			{
				fb = fnd-1;
				break;
			}				
		}
		
		++tb;
		if(fb == fe)
		{
			return ui64(tb - t.t);
		}
	}
	
	return NFND;
}

ui64 txtf(const txt &t, ui64 pos, char fnd)
{
	if(pos >= t.s)
	{
		return NFND;
	}
	
	const char *tb = t.t + pos - 1, *te = t.t + t.s;
	
	while(++tb != te)
	{	
		if(*tb == fnd)
		{
			return ui64(tb - t.t);
		}
	}
	
	return NFND;
}

ui64 txtfe(const txt &t, ui64 pos, const txt &fnd)
{
	if(fnd.s > t.s)
	{
		return NFND;
	}
	
	if(pos > t.s)
	{
		return NFND;
	}
	
	const char *fb = fnd.t-1, *fe = fnd.t + fnd.s;
	const char *tb = t.t-1, *te = NULL;
	const char *tb_cur = NULL;
	
	if(pos + fnd.s > t.s)
	{
		te = t.t + t.s - fnd.s;
	}
	else
	{
		te = t.t + pos;
	}
	
	while(te != tb)
	{
		tb_cur = --te;
		while(++fb != fe)
		{
			if(*fb != *(++tb_cur))
			{
				fb = fnd.t-1;
				break;
			}				
		}
		
		if(fb == fe)
		{
			return ui64(te + 1 - t.t);
		}
	}
	
	return NFND;
}

ui64 txtfe(const txt &t, ui64 pos, const char *fnd)
{
	ui64 fnds = txt::Sl(fnd);
	
	if(fnds > t.s)
	{
		return NFND;
	}
	
	if(pos > t.s)
	{
		return NFND;
	}
	
	const char *fb = fnd-1, *fe = fnd + fnds;
	const char *tb = t.t-1, *te = NULL;
	const char *tb_cur = NULL;
	
	if(pos + fnds > t.s)
	{
		te = t.t + t.s - fnds;
	}
	else
	{
		te = t.t + pos;
	}
	
	while(te != tb)
	{
		tb_cur = --te;
		while(++fb != fe)
		{
			if(*fb != *(++tb_cur))
			{
				fb = fnd-1;
				break;
			}				
		}
		
		if(fb == fe)
		{
			return ui64(te + 1 - t.t);
		}
	}
	
	return NFND;
}

ui64 txtfe(const txt &t, ui64 pos, char fnd)
{
	if(pos >= t.s)
	{
		return NFND;
	}
	
	const char *tb = t.t-1, *te = t.t + pos + 1;
	
	while(--te != tb)
	{	
		if(*te == fnd)
		{
			return ui64(te - t.t);
		}
	}
	
	return NFND;
}

txt & txti(txt &t, ui64 pos, const txt &ins)
{
	if(pos > t.s)
	{
		t.ExceptBuff(EXCEPTION_TXTI_BUFF_OVERRUN, pos);
		return t;
	}
	
	ui64 ns = t.s + ins.s;
	if(t.ts <= ns)
	{
		ui64 nts;
		char *tmp = txt::AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		char *ipos = tmp;
		memcpy(ipos, t.t, pos);
		memcpy(ipos += pos, ins.t, ins.s);
		memcpy(ipos + ins.s, t.t + pos, t.s - pos);
		t.~txt(); // Uses true size
		t.t = tmp;
		t.ts = nts;
		t.s = ns;
		
		return t;
	}

	char *ipos = t.t + pos;
	memcpy(ipos + ins.s, t.t + pos, t.s - pos);
	memcpy(ipos, ins.t, ins.s);
	t.s = ns;
	t[t.s] = 0;
	
	return t;
}

txt & txti(txt &t, ui64 pos, const char *ins)
{
	if(pos > t.s)
	{
		t.ExceptBuff(EXCEPTION_TXTI_BUFF_OVERRUN, pos);
		return t;
	}
	
	ui64 inss = txt::Sl(ins);
	ui64 ns = t.s + inss;
	if(t.ts <= ns)
	{
		ui64 nts;
		char *tmp = txt::AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		char *ipos = tmp;
		memcpy(ipos, t.t, pos);
		memcpy(ipos += pos, ins, inss);
		memcpy(ipos + inss, t.t + pos, t.s - pos);
		t.~txt(); // Uses true size
		t.t = tmp;
		t.ts = nts;
		t.s = ns;
		
		return t;
	}

	char *ipos = t.t + pos;
	memcpy(ipos + inss, t.t + pos, t.s - pos);
	memcpy(ipos, ins, inss);
	t.s = ns;
	t[t.s] = 0;
	
	return t;
}

txt & txti(txt &t, ui64 pos, char ins)
{
	if(pos > t.s)
	{
		t.ExceptBuff(EXCEPTION_TXTI_BUFF_OVERRUN, pos);
		return t;
	}
	
	ui64 ns = t.s + 1;
	if(t.ts <= ns)
	{
		ui64 nts;
		char *tmp = txt::AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		char *ipos = tmp;
		memcpy(ipos, t.t, pos);
		*(ipos += pos) = ins;
		memcpy(ipos + 1, t.t + pos, t.s - pos);
		t.~txt(); // Uses true size
		t.t = tmp;
		t.ts = nts;
		t.s = ns;
		
		return t;
	}

	char *ipos = t.t + pos;
	memcpy(ipos + 1, t.t + pos, t.s - pos);
	*ipos = ins;
	t.s = ns;
	t[t.s] = 0;
	
	return t;
}

txt & txto(txt &t, ui64 pos, const txt &ovr)
{
	if(pos > t.s)
	{
		t.ExceptBuff(EXCEPTION_TXTO_BUFF_OVERRUN, pos);
		return t;
	}
	
	ui64 ns = pos + ovr.s;
	if(t.ts <= ns)
	{
		ui64 nts;
		char *tmp = txt::AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		memcpy(tmp, t.t, t.s);
		memcpy(tmp + pos, ovr.t, ovr.s);
		t.~txt(); // Uses true size
		t.t = tmp;
		t.ts = nts;
		t.s = ns;
		
		return t;
	}

	memcpy(t.t + pos, ovr.t, ovr.s);
	
	return t;
}

txt & txto(txt &t, ui64 pos, const char *ovr)
{
	if(pos > t.s)
	{
		t.ExceptBuff(EXCEPTION_TXTO_BUFF_OVERRUN, pos);
		return t;
	}
	
	ui64 ovrs = txt::Sl(ovr);
	ui64 ns = pos + ovrs;
	if(t.ts <= ns)
	{
		ui64 nts;
		char *tmp = txt::AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		memcpy(tmp, t.t, t.s);
		memcpy(tmp + pos, ovr, ovrs);
		t.~txt(); // Uses true size
		t.t = tmp;
		t.ts = nts;
		t.s = ns;
		
		return t;
	}

	memcpy(t.t + pos, ovr, ovrs);
	
	return t;
}

txt & txtr(txt &t, ui64 pos, ui64 n, const txt &rep)
{
	if(pos > t.s)
	{
		t.ExceptBuff(EXCEPTION_TXTI_BUFF_OVERRUN, pos);
		return t;
	}
	
	if(n > t.s || pos + n > t.s)
	{
		n = t.s - pos;
	}
	
	ui64 ns = t.s - n + rep.s;
	if(t.ts <= ns)
	{
		ui64 nts;
		char *tmp = txt::AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		char *ipos = tmp;
		memcpy(ipos, t.t, pos);
		memcpy(ipos += pos, rep.t, rep.s);
		memcpy(ipos + rep.s, t.t + pos + n, t.s - pos - n);
		t.~txt(); // Uses true size
		t.t = tmp;
		t.ts = nts;
		t.s = ns;
		
		return t;
	}

	char *ipos = t.t + pos;
	memcpy(ipos + rep.s, t.t + pos + n, t.s - pos - n);
	memcpy(ipos, rep.t, rep.s);
	t.s = ns;
	t[t.s] = 0;
	
	return t;
}

txt & txtr(txt &t, ui64 pos, ui64 n, const char *rep)
{
	if(pos > t.s)
	{
		t.ExceptBuff(EXCEPTION_TXTI_BUFF_OVERRUN, pos);
		return t;
	}
	
	if(n > t.s || pos + n > t.s)
	{
		n = t.s - pos;
	}
	
	ui64 reps = txt::Sl(rep);
	ui64 ns = t.s - n + reps;
	if(t.ts <= ns)
	{
		ui64 nts;
		char *tmp = txt::AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		char *ipos = tmp;
		memcpy(ipos, t.t, pos);
		memcpy(ipos += pos, rep, reps);
		memcpy(ipos + reps, t.t + pos + n, t.s - pos - n);
		t.~txt(); // Uses true size
		t.t = tmp;
		t.ts = nts;
		t.s = ns;
		
		return t;
	}

	char *ipos = t.t + pos;
	memcpy(ipos + reps, t.t + pos + n, t.s - pos - n);
	memcpy(ipos, rep, reps);
	t.s = ns;
	t[t.s] = 0;
	
	return t;
}

txt & txtr(txt &t, ui64 pos, ui64 n, char rep)
{
	if(pos > t.s)
	{
		t.ExceptBuff(EXCEPTION_TXTI_BUFF_OVERRUN, pos);
		return t;
	}
	
	if(n > t.s || pos + n > t.s)
	{
		n = t.s - pos;
	}
	
	ui64 ns = t.s - n + 1;
	if(t.ts <= ns)
	{
		ui64 nts;
		char *tmp = txt::AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		char *ipos = tmp;
		memcpy(ipos, t.t, pos);
		*(ipos += pos) = rep;
		memcpy(ipos + 1, t.t + pos + n, t.s - pos - n);
		t.~txt(); // Uses true size
		t.t = tmp;
		t.ts = nts;
		t.s = ns;
		
		return t;
	}

	char *ipos = t.t + pos;
	memcpy(ipos + 1, t.t + pos + n, t.s - pos - n);
	*ipos = rep;
	t.s = ns;
	t[t.s] = 0;
	
	return t;
}

txt & txtd(txt &t, ui64 pos, ui64 n)
{
	if(pos >= t.s)
	{
		t.ExceptBuff(EXCEPTION_TXTI_BUFF_OVERRUN, pos);
		return t;
	}
	
	if(n > t.s || pos + n > t.s)
	{
		n = t.s - pos;
	}
	
	memcpy(t.t + pos, t.t + pos + n, t.s - pos - n);
	t.s = t.s - n;
	t[t.s] = 0;
	
	return t;
}

txt txts(const txt &t, ui64 pos, ui64 n)
{
	if(pos > t.s)
	{
		t.ExceptBuff(EXCEPTION_TXTI_BUFF_OVERRUN, pos);
		return txt();
	}
	
	if(n > t.s || pos + n > t.s)
	{
		n = t.s - pos;
	}
	
	txt res = n;
	memcpy(res.t, t.t + pos, n);
	res.s = n;
	
	return res;
}

txt txtsp(const txt &t, ui64 p0, ui64 p1)
{
	if(p0 > t.s)
	{
		t.ExceptBuff(EXCEPTION_TXTI_BUFF_OVERRUN, p0);
		return txt();
	}
	
	if(p1 > t.s)
	{
		p1 = t.s-1;
	}
	
	ui64 n = p1 - p0 + 1;
	txt res = n;
	memcpy(res.t, t.t + p0, n);
	res.s = n;
	
	return res;
}

txt i2t(ui64 i)
{
	char b[21]; // Max number 18446744073709551616
	b[20] = 0; 
	int c = 20;
	
	do
	{
		b[--c] = i % 10 | 0x30;
		i /= 10;
	}
	while(i > 0);
	
	return txt(b + c);
}

txt i2t(ui32 i)
{
	char b[11]; // Max number 4294967296
	b[10] = 0; 
	int c = 10;
	
	do
	{
		b[--c] = i % 10 | 0x30;
		i /= 10;
	}
	while(i > 0);
	
	return txt(b + c);
}

txt i2t(i64 i)
{
	char b[21]; // Max number -9223372036854775808
	b[20] = 0; 
	int c = 20;
	
	ui64 ia = i & 0x8000000000000000 ? ui64(~i + 1) : (ui64)i;
	
	do
	{
		b[--c] = ia % 10 | 0x30;
		ia /= 10;
	}
	while(ia > 0);
	
	if(i & 0x8000000000000000)
	{
		b[--c] = 0x2D;
	}
	
	return txt(b + c);
}

txt i2t(i32 i)
{
	char b[12]; // Max number -2147483648
	b[11] = 0; 
	int c = 11;
	
	ui32 ia = i & 0x80000000 ? ui32(~i + 1) : (ui32)i;
	
	do
	{
		b[--c] = ia % 10 | 0x30;
		ia /= 10;
	}
	while(ia > 0);
	
	if(i & 0x80000000)
	{
		b[--c] = 0x2D;
	}
	
	return txt(b + c);
}

txt i2h(ui64 i)
{
	char b[17]; // Max number FFFFFFFFFFFFFFFF
	b[16] = 0; 
	int c = 16;

	char *a = ((char *)&i) - 1;
	char *ae = a + 9;
	while(++a != ae)
	{
		b[--c] = char((*a & 0xF) | 0x30);
		if(b[c] > 0x39)
		{
			b[c] += 0x7;
		}
		
		b[--c] = char((*a >> 4) | 0x30);
		if(b[c] > 0x39)
		{
			b[c] += 0x7;
		}
	}
	
	return txt(b);
}

txt i2h(ui32 i)
{
	char b[9]; // Max number FFFFFFFF
	b[8] = 0; 
	int c = 8;

	char *a = ((char *)&i) - 1;
	char *ae = a + 5;
	while(++a != ae)
	{
		b[--c] = char((*a & 0xF) | 0x30);
		if(b[c] > 0x39)
		{
			b[c] += 0x7;
		}
		
		b[--c] = char((*a >> 4) | 0x30);
		if(b[c] > 0x39)
		{
			b[c] += 0x7;
		}
	}
	
	return txt(b);
}

txt i2h(ui16 i)
{
	char b[5]; // Max number FFFF
	b[4] = 0;
	
	char *a = ((char *)&i);
	
	b[3] = char((a[0] & 0xF) | 0x30);
	if(b[3] > 0x39)
	{
		b[3] += 0x7;
	}
	
	b[2] = char((a[0] >> 4) | 0x30);
	if(b[2] > 0x39)
	{
		b[2] += 0x7;
	}
	
	b[1] = char((a[1] & 0xF) | 0x30);
	if(b[1] > 0x39)
	{
		b[1] += 0x7;
	}
	
	b[0] = char((a[1] >> 4) | 0x30);
	if(b[0] > 0x39)
	{
		b[0] += 0x7;
	}
	
	return txt(b);
}

txt i2h(ui8 i)
{
	char b[3]; // Max number FF
	b[2] = 0;
	
	b[1] = char((i & 0xF) | 0x30);
	if(b[1] > 0x39)
	{
		b[1] += 0x7;
	}
	
	b[0] = char((i >> 4) | 0x30);
	if(b[0] > 0x39)
	{
		b[0] += 0x7;
	}
	
	return txt(b);
}

ui64 t2i(const txt &t) // Check out ql.cpp for most minimal and fastest implementation of this
{
	ui64 negative = 0;
	
	if(t.t[0] == 0x2D)
	{
		negative = 1;
	}
	else if(t.t[0] < 0x30 || t.t[0] > 0x39)
	{
		t.ExceptNum(EXCEPTION_T2I_NON_NUMBER);
		return 0;
	}
	
	ui64 n = 0;
	ui64 pren = 0;
	for(ui64 i = negative; i < t.s; ++i)
	{
		if(t.t[i] < 0x30 || t.t[i] > 0x39)
		{
			t.ExceptNum(EXCEPTION_T2I_NON_NUMBER);
			return 0;
		}
		
		n = n * 10 + (t.t[i] & 0xF);
		
		if(n < pren)
		{
			t.ExceptNum(EXCEPTION_T2I_OVERFLOW);
			return 0;
		}
		
		pren = n;
	}
	
	if(negative)
	{
		n = ~n + 1; // 2-s Complement
	}
	
	if(n < pren)
	{
		t.ExceptNum(EXCEPTION_T2I_OVERFLOW);
		return 0;
	}
	
	return n;
}

ui64 h2i(const txt &t)
{
	if(t.s > 16)
	{
		t.ExceptNum(EXCEPTION_H2I_OVERFLOW);
		return 0x0;
	}
	
	ui64 n = 0;
	
	const char *tb = t.t-1;
	const char *te = t.t + t.s;
	ui64 i = 0;
	while((te -= 2) > tb)
	{
		ui8 ms = *te, ls = *(te+1);
		
		if(ms > 0x39)
		{
			ms = ui8((ms & 0xDF) - 0x7);
		}
		
		if(ls > 0x39)
		{
			ls = ui8((ls & 0xDF) - 0x7);
		}
		
		if((ms < 0x30 || ms > 0x3F) || (ls < 0x30 || ls > 0x3F))
		{
			t.ExceptNum(EXCEPTION_H2I_NON_NUMBER);
			return 0x0;
		}
		
		ui8 b = ui8((ms << 4) | (ls & 0xF));
		
		n |= (ui64)b << i * 8;
		++i;
	}
	
	if(te == tb) // Uneven number of nibbles
	{
		ui8 ls = *(te+1);
		
		if(ls > 0x39)
		{
			ls = ui8((ls & 0xDF) - 0x7);
		}
		
		if(ls < 0x30 || ls > 0x3F)
		{
			t.ExceptNum(EXCEPTION_H2I_NON_NUMBER);
			return 0x0;
		}
		
		n |= (ui64)(ls & 0xF) << i * 8;
	}
	
	return n;
}