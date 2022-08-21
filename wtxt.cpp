// SLIB
#include "wtxt"

HANDLE wtxt::h = HeapCreate(HEAP_FLAGS, 0, 0);

wtxt & wtxt::operator+=(const wtxt &o)
{
	ui64 ns = s + o.s;
	if(ts <= ns)
	{
		ui64 nts;
		wchar_t *tmp = AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		memcpy(tmp, t, s * sizeof(wchar_t));
		this->wtxt::~wtxt(); // Uses true size
		t = tmp;
		ts = nts;
	}
	
	memcpy(t+s, o.t, o.s * sizeof(wchar_t));
	s = ns;
	t[s] = 0;
	
	return *this;
}

wtxt & wtxt::operator+=(const wchar_t *cs)
{
	ui64 ss = Sl(cs), ns = s + ss;
	if(ts <= ns)
	{
		ui64 nts;
		wchar_t *tmp = AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		memcpy(tmp, t, s * sizeof(wchar_t));
		this->wtxt::~wtxt(); // Uses true size
		t = tmp;
		ts = nts;
	}
	memcpy(t+s, cs, ss * sizeof(wchar_t));
	s = ns;
	t[s] = 0;
	
	return *this;
}

wtxt & wtxt::operator+=(wchar_t c) // Very effective for rapid chars appending
{
	ui64 ns = s + 1;
	if(ts <= ns)
	{
		ui64 nts;
		wchar_t *tmp = AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		memcpy(tmp, t, s * sizeof(wchar_t));
		this->wtxt::~wtxt(); // Uses true size
		t = tmp;
		ts = nts;
	}

	t[s] = c;
	s = ns;
	t[s] = 0;
	
	return *this;
}

wtxt & wtxt::operator--()
{
	s = wtxt::Sl(t);
	ui64 nts;
	wchar_t *tmp = AllocTmp(s, &nts);
	memcpy(tmp, t, s * sizeof(wchar_t));
	this->wtxt::~wtxt(); // Uses true size
	t = tmp;
	ts = nts;
	
	return *this;
}

void wtxt::ExceptBuff(DWORD c, ui64 pos) const
{
	static ui64 nts;               // Leaking memory here for debug purposes
	wchar_t *tmp = AllocTmp(s, &nts); // This will allow for temp texts to be passed
	memcpy(tmp, t, s * sizeof(wchar_t));
	
	static ULONG_PTR params[4];
	params[0] = (ULONG_PTR)tmp;
	params[1] = EXCEPT_TXT_UTF16;
	params[2] = s;
	params[3] = pos;
	RaiseException(c, 0, 4, params);
}

void wtxt::ExceptNum(DWORD c) const
{
	static ui64 nts;
	wchar_t *tmp = AllocTmp(s, &nts);
	memcpy(tmp, t, s * sizeof(wchar_t));
	
	static ULONG_PTR params[3];
	params[0] = (ULONG_PTR)tmp;
	params[1] = EXCEPT_TXT_UTF16;
	params[2] = s;
	RaiseException(c, 0, 3, params);
}

ui64 operator>>(const wtxt &fnd, const wtxt &t)
{
	const wchar_t *fb = fnd.t-1, *fe = fnd.t + fnd.s;
	const wchar_t *tb = t.t-1, *te = t.t + t.s - fnd.s;
	const wchar_t *tb_cur = NULL;
	
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

ui64 operator>>(const wchar_t *fnd, const wtxt &t) // x2.22 FASTER VS STD Finding Test
{
	ui64 fnds = wtxt::Sl(fnd);

	const wchar_t *fb = fnd-1, *fe = fnd + fnds;
	const wchar_t *tb = t.t-1, *te = t.t + t.s - fnds;
	const wchar_t *tb_cur = NULL;
	
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

ui64 operator>>(wchar_t fnd, const wtxt &t)
{
	const wchar_t *tb = t.t-1, *te = t.t + t.s;
	
	while(++tb != te)
	{	
		if(*tb == fnd)
		{
			return ui64(tb - t.t);
		}
	}
	
	return NFND;
}

ui64 operator<<(const wtxt &fnd, const wtxt &t)
{
	const wchar_t *fb = fnd.t-1, *fe = fnd.t + fnd.s;
	const wchar_t *tb = t.t-1, *te = t.t + t.s - fnd.s;
	const wchar_t *tb_cur = NULL;
	
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

ui64 operator<<(const wchar_t *fnd, const wtxt &t)
{
	ui64 fnds = wtxt::Sl(fnd);
	const wchar_t *fb = fnd-1, *fe = fnd + fnds;
	const wchar_t *tb = t.t-1, *te = t.t + t.s - fnds;
	const wchar_t *tb_cur = NULL;
	
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

ui64 operator<<(wchar_t fnd, const wtxt &t)
{
	const wchar_t *tb = t.t-1, *te = t.t + t.s;
	
	while(--te != tb)
	{	
		if(*te == fnd)
		{
			return ui64(te - t.t);
		}
	}
	
	return NFND;
}

ui64 txtf(const wtxt &t, ui64 pos, const wtxt &fnd)
{
	if(pos > t.s - fnd.s)
	{
		return NFND;
	}
	
	const wchar_t *fb = fnd.t-1, *fe = fnd.t + fnd.s;
	const wchar_t *tb = t.t + pos - 1, *te = t.t + t.s - fnd.s;
	const wchar_t *tb_cur = NULL;
	
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

ui64 txtf(const wtxt &t, ui64 pos, const wchar_t *fnd)
{
	ui64 fnds = wtxt::Sl(fnd);
	
	if(pos > t.s - fnds)
	{
		return NFND;
	}
	
	const wchar_t *fb = fnd-1, *fe = fnd + fnds;
	const wchar_t *tb = t.t + pos - 1, *te = t.t + t.s - fnds;
	const wchar_t *tb_cur = NULL;
	
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

ui64 txtf(const wtxt &t, ui64 pos, wchar_t fnd)
{
	if(pos >= t.s)
	{
		return NFND;
	}
	
	const wchar_t *tb = t.t + pos - 1, *te = t.t + t.s;
	
	while(++tb != te)
	{	
		if(*tb == fnd)
		{
			return ui64(tb - t.t);
		}
	}
	
	return NFND;
}

ui64 txtfe(const wtxt &t, ui64 pos, const wtxt &fnd)
{
	if(pos > t.s)
	{
		return NFND;
	}
	
	const wchar_t *fb = fnd.t-1, *fe = fnd.t + fnd.s;
	const wchar_t *tb = t.t-1, *te = NULL;
	const wchar_t *tb_cur = NULL;
	
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

ui64 txtfe(const wtxt &t, ui64 pos, const wchar_t *fnd)
{
	ui64 fnds = wtxt::Sl(fnd);
	
	if(pos > t.s)
	{
		return NFND;
	}
	
	const wchar_t *fb = fnd-1, *fe = fnd + fnds;
	const wchar_t *tb = t.t-1, *te = NULL;
	const wchar_t *tb_cur = NULL;
	
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

ui64 txtfe(const wtxt &t, ui64 pos, wchar_t fnd)
{
	if(pos >= t.s)
	{
		return NFND;
	}
	
	const wchar_t *tb = t.t-1, *te = t.t + pos + 1;
	
	while(--te != tb)
	{	
		if(*te == fnd)
		{
			return ui64(te - t.t);
		}
	}
	
	return NFND;
}

wtxt & txti(wtxt &t, ui64 pos, const wtxt &ins)
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
		wchar_t *tmp = wtxt::AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		wchar_t *ipos = tmp;
		memcpy(ipos, t.t, pos * sizeof(wchar_t));
		memcpy(ipos += pos, ins.t, ins.s * sizeof(wchar_t));
		memcpy(ipos + ins.s, t.t + pos, (t.s - pos) * sizeof(wchar_t));
		t.~wtxt(); // Uses true size
		t.t = tmp;
		t.ts = nts;
		t.s = ns;
		
		return t;
	}

	wchar_t *ipos = t.t + pos;
	memcpy(ipos + ins.s, t.t + pos, (t.s - pos) * sizeof(wchar_t));
	memcpy(ipos, ins.t, ins.s * sizeof(wchar_t));
	t.s = ns;
	t[t.s] = 0;
	
	return t;
}

wtxt & txti(wtxt &t, ui64 pos, const wchar_t *ins)
{
	if(pos > t.s)
	{
		t.ExceptBuff(EXCEPTION_TXTI_BUFF_OVERRUN, pos);
		return t;
	}
	
	ui64 inss = wtxt::Sl(ins);
	ui64 ns = t.s + inss;
	if(t.ts <= ns)
	{
		ui64 nts;
		wchar_t *tmp = wtxt::AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		wchar_t *ipos = tmp;
		memcpy(ipos, t.t, pos * sizeof(wchar_t));
		memcpy(ipos += pos, ins, inss * sizeof(wchar_t));
		memcpy(ipos + inss, t.t + pos, (t.s - pos) * sizeof(wchar_t));
		t.~wtxt(); // Uses true size
		t.t = tmp;
		t.ts = nts;
		t.s = ns;
		
		return t;
	}

	wchar_t *ipos = t.t + pos;
	memcpy(ipos + inss, t.t + pos, (t.s - pos) * sizeof(wchar_t));
	memcpy(ipos, ins, inss * sizeof(wchar_t));
	t.s = ns;
	t[t.s] = 0;
	
	return t;
}

wtxt & txti(wtxt &t, ui64 pos, wchar_t ins)
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
		wchar_t *tmp = wtxt::AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		wchar_t *ipos = tmp;
		memcpy(ipos, t.t, pos * sizeof(wchar_t));
		*(ipos += pos) = ins;
		memcpy(ipos + 1, t.t + pos, (t.s - pos) * sizeof(wchar_t));
		t.~wtxt(); // Uses true size
		t.t = tmp;
		t.ts = nts;
		t.s = ns;
		
		return t;
	}

	wchar_t *ipos = t.t + pos;
	memcpy(ipos + 1, t.t + pos, (t.s - pos) * sizeof(wchar_t));
	*ipos = ins;
	t.s = ns;
	t[t.s] = 0;
	
	return t;
}

wtxt & txto(wtxt &t, ui64 pos, const wtxt &ovr)
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
		wchar_t *tmp = wtxt::AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		memcpy(tmp, t.t, t.s * sizeof(wchar_t));
		memcpy(tmp + pos, ovr.t, ovr.s * sizeof(wchar_t));
		t.~wtxt(); // Uses true size
		t.t = tmp;
		t.ts = nts;
		t.s = ns;
		
		return t;
	}

	memcpy(t.t + pos, ovr.t, ovr.s * sizeof(wchar_t));
	
	return t;
}

wtxt & txto(wtxt &t, ui64 pos, const wchar_t *ovr)
{
	if(pos > t.s)
	{
		t.ExceptBuff(EXCEPTION_TXTO_BUFF_OVERRUN, pos);
		return t;
	}
	
	ui64 ovrs = wtxt::Sl(ovr);
	ui64 ns = pos + ovrs;
	if(t.ts <= ns)
	{
		ui64 nts;
		wchar_t *tmp = wtxt::AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		memcpy(tmp, t.t, t.s * sizeof(wchar_t));
		memcpy(tmp + pos, ovr, ovrs * sizeof(wchar_t));
		t.~wtxt(); // Uses true size
		t.t = tmp;
		t.ts = nts;
		t.s = ns;
		
		return t;
	}

	memcpy(t.t + pos, ovr, ovrs * sizeof(wchar_t));
	
	return t;
}

wtxt & txtr(wtxt &t, ui64 pos, ui64 n, const wtxt &rep)
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
		wchar_t *tmp = wtxt::AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		wchar_t *ipos = tmp;
		memcpy(ipos, t.t, pos * sizeof(wchar_t));
		memcpy(ipos += pos, rep.t, rep.s * sizeof(wchar_t));
		memcpy(ipos + rep.s, t.t + pos + n, (t.s - pos - n) * sizeof(wchar_t));
		t.~wtxt(); // Uses true size
		t.t = tmp;
		t.ts = nts;
		t.s = ns;
		
		return t;
	}

	wchar_t *ipos = t.t + pos;
	memcpy(ipos + rep.s, t.t + pos + n, (t.s - pos - n) * sizeof(wchar_t));
	memcpy(ipos, rep.t, rep.s * sizeof(wchar_t));
	t.s = ns;
	t[t.s] = 0;
	
	return t;
}

wtxt & txtr(wtxt &t, ui64 pos, ui64 n, const wchar_t *rep)
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
	
	ui64 reps = wtxt::Sl(rep);
	ui64 ns = t.s - n + reps;
	if(t.ts <= ns)
	{
		ui64 nts;
		wchar_t *tmp = wtxt::AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		wchar_t *ipos = tmp;
		memcpy(ipos, t.t, pos * sizeof(wchar_t));
		memcpy(ipos += pos, rep, reps * sizeof(wchar_t));
		memcpy(ipos + reps, t.t + pos + n, (t.s - pos - n) * sizeof(wchar_t));
		t.~wtxt(); // Uses true size
		t.t = tmp;
		t.ts = nts;
		t.s = ns;
		
		return t;
	}

	wchar_t *ipos = t.t + pos;
	memcpy(ipos + reps, t.t + pos + n, (t.s - pos - n) * sizeof(wchar_t));
	memcpy(ipos, rep, reps * sizeof(wchar_t));
	t.s = ns;
	t[t.s] = 0;
	
	return t;
}

wtxt & txtr(wtxt &t, ui64 pos, ui64 n, wchar_t rep)
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
		wchar_t *tmp = wtxt::AllocTmp(ns * TXT_CONCAT_MULT, &nts);
		wchar_t *ipos = tmp;
		memcpy(ipos, t.t, pos * sizeof(wchar_t));
		*(ipos += pos) = rep;
		memcpy(ipos + 1, t.t + pos + n, (t.s - pos - n) * sizeof(wchar_t));
		t.~wtxt(); // Uses true size
		t.t = tmp;
		t.ts = nts;
		t.s = ns;
		
		return t;
	}

	wchar_t *ipos = t.t + pos;
	memcpy(ipos + 1, t.t + pos + n, (t.s - pos - n) * sizeof(wchar_t));
	*ipos = rep;
	t.s = ns;
	t[t.s] = 0;
	
	return t;
}

wtxt & txtd(wtxt &t, ui64 pos, ui64 n)
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
	
	memcpy(t.t + pos, t.t + pos + n, (t.s - pos - n) * sizeof(wchar_t));
	t.s = t.s - n;
	t[t.s] = 0;
	
	return t;
}

wtxt i2wt(ui64 i)
{
	wchar_t b[21]; // Max number 18446744073709551616
	b[20] = 0; 
	int c = 20;
	
	do
	{
		b[--c] = i % 10 | 0x30;
		i /= 10;
	}
	while(i > 0);
	
	return wtxt(b + c);
}

wtxt i2wt(ui32 i)
{
	wchar_t b[11]; // Max number 4294967296
	b[10] = 0; 
	int c = 10;
	
	do
	{
		b[--c] = i % 10 | 0x30;
		i /= 10;
	}
	while(i > 0);
	
	return wtxt(b + c);
}

wtxt i2wt(i64 i)
{
	wchar_t b[21]; // Max number -9223372036854775808
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
	
	return wtxt(b + c);
}

wtxt i2wt(i32 i)
{
	wchar_t b[12]; // Max number -2147483648
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
	
	return wtxt(b + c);
}

wtxt i2wh(ui64 i)
{
	char b[34]; // Max number FFFFFFFFFFFFFFFF
	b[32] = 0;
	b[33] = 0;
	int c = 32;

	char *a = ((char *)&i) - 1;
	char *ae = a + 9;
	while(++a != ae)
	{
		b[c-=2] = char((*a & 0xF) | 0x30);
		b[c+1] = 0;
		if(b[c] > 0x39)
		{
			b[c] += 0x7;
		}
		
		b[c-=2] = char((*a >> 4) | 0x30);
		b[c+1] = 0;
		if(b[c] > 0x39)
		{
			b[c] += 0x7;
		}
	}
	
	return wtxt((wchar_t *)b);
}

wtxt i2wh(ui32 i)
{
	char b[18]; // Max number FFFFFFFF
	b[16] = 0; 
	b[17] = 0; 
	int c = 16;

	char *a = ((char *)&i) - 1;
	char *ae = a + 5;
	while(++a != ae)
	{
		b[c-=2] = char((*a & 0xF) | 0x30);
		b[c+1] = 0;
		if(b[c] > 0x39)
		{
			b[c] += 0x7;
		}
		
		b[c-=2] = char((*a >> 4) | 0x30);
		b[c+1] = 0;
		if(b[c] > 0x39)
		{
			b[c] += 0x7;
		}
	}
	
	return wtxt((wchar_t *)b);
}

wtxt i2wh(ui16 i)
{
	char b[10]; // Max number FFFF
	b[8] = 0;
	b[9] = 0;
	
	char *a = ((char *)&i);
	
	b[6] = char((a[0] & 0xF) | 0x30);
	b[7] = 0;
	if(b[6] > 0x39)
	{
		b[6] += 0x7;
	}
	
	b[4] = char((a[0] >> 4) | 0x30);
	b[5] = 0;
	if(b[4] > 0x39)
	{
		b[4] += 0x7;
	}
	
	b[2] = char((a[1] & 0xF) | 0x30);
	b[3] = 0;
	if(b[2] > 0x39)
	{
		b[2] += 0x7;
	}
	
	b[0] = char((a[1] >> 4) | 0x30);
	b[1] = 0;
	if(b[0] > 0x39)
	{
		b[0] += 0x7;
	}
	
	return wtxt((wchar_t *)b);
}

wtxt i2wh(ui8 i)
{
	char b[6]; // Max number FF
	b[4] = 0;
	b[5] = 0;
	
	b[2] = char((i & 0xF) | 0x30);
	b[3] = 0;
	if(b[2] > 0x39)
	{
		b[2] += 0x7;
	}
	
	b[0] = char((i >> 4) | 0x30);
	b[1] = 0;
	if(b[0] > 0x39)
	{
		b[0] += 0x7;
	}
	
	return wtxt((wchar_t *)b);
}

ui64 t2i(const wtxt &t)
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

ui64 h2i(const wtxt &t)
{
	if(t.s > 16)
	{
		t.ExceptNum(EXCEPTION_H2I_OVERFLOW);
		return 0x0;
	}
	
	ui64 n = 0;
	
	const wchar_t *tb = t.t-1;
	const wchar_t *te = t.t + t.s;
	ui64 i = 0;
	while((te -= 2) > tb)
	{
		ui8 ms = (ui8)(*te), ls = (ui8)(*(te+1));
		
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
		ui8 ls = (ui8)(*(te+1));
		
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