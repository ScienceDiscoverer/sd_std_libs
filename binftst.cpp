// CONSOLE
#include <sddb>
#include <binf>

i32 wmain()
{
	// Create or open File or Device =================================================================
	HANDLE ih = CreateFileA(
		"tstf\\strmatch.html",		//   [I]  Name of the file or device to create/open
		GENERIC_READ,				//   [I]  Requested access GENERIC_READ|GENERIC_WRITE|0
		FILE_SHARE_READ,			//   [I]  Sharing mode FILE_SHARE_READ|WRITE|DELETE|0
		NULL,						// [I|O]  SECURITY_ATTRIBUTES for file, handle inheritability
		OPEN_EXISTING,				//   [I]  Action to take if file/device exist or not
		FILE_FLAG_SEQUENTIAL_SCAN,	//   [I]  Attributes and flags for file/device
		NULL);						// [I|O]  Handle to template file to copy attributes from
	// ===============================================================================================
	
	binf bf;
	p|DC|"------------------------ADD----------------------"|N;
	
	DWORD br;
	char buf[13];
	ui64 prev_ts = 0;
	SWSET
	while(ReadFile(ih, buf, 13, &br, NULL) && br > 0) // SW0: 145.548'200 ms
	{
		bf.Add(buf, br);
		if(!bf > prev_ts)
		{
			p|"TS: "|!bf|" S: "|~bf|N;
			prev_ts = !bf;
		}
	}
	SWSTOP
	p|"FINAL TS: "|!bf|" S: "|~bf|N;
	
	binf bff;
	p|"------------------------<<-----------------------"|N;
	
	LARGE_INTEGER li;
	li.QuadPart = 0;
	SetFilePointerEx(ih, li, NULL, FILE_BEGIN);
	
	prev_ts = 0;
	SWSET
	while(ReadFile(ih, buf, 1, &br, NULL) && br > 0) // SW1: 1.834 s --> Reading 1 byte at time sucks!
	{
		bff << buf[0];
		if(!bff > prev_ts)
		{
			p|"TS: "|!bff|" S: "|~bff|N;
			prev_ts = !bff;
		}
	}
	SWSTOP
	p|"FINAL TS: "|!bff|" S: "|~bff|N;
	
	p|"------------------------END----------------------"|N;
	
	SWPRINT
	SWPRINT
	
	CloseHandle(ih);
	
	p|TB|P;
	return 0;
}