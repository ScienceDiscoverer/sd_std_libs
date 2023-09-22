// SLIB
#include "ftools"

wtxta dirs_up = 16;
wtxta dirs_low = 512;
const cwstr *ign_dirs;

static wtxt star = WL("\\*");
static wtxt fnd_all = MAX_PATH;
static wtxt full_fn = MAX_PATH;
static wtxt ign_dir = MAX_PATH;
static wtxt fext = MAX_PATH;
static wtxt fn;

void scan(const wtxt &dir, wtxta &list)
{	
	HANDLE ffind;
	WIN32_FIND_DATAW fdata;
	
	fnd_all += dir, fnd_all += star;
	
	// Start files enumeration =================================================================
	ffind = FindFirstFileExW(
		fnd_all,					// [I] LPCSTR Full			dir + path
		FindExInfoBasic,			// [I] FINDEX_INFO_LEVELS	Search accuracy
		&fdata,						// [O] LPVOID				Ouput file data
		FindExSearchNameMatch,		// [I] FINDEX_SEARCH_OPS	Non wildcard filters
		NULL,						// [I] LPVOID				Must be NULL (no support)
		FIND_FIRST_EX_LARGE_FETCH);	// [I] DWORD				Additional search flags
	// =========================================================================================
	
	if(ffind == INVALID_HANDLE_VALUE)
	{
		return;
	}

	do
	{
		txtsdt(fn, MAX_PATH, 0, fdata.cFileName); // Always set direct manipulated text back to 0!
		txtszu(fn);
		
		if((~fn == 1 && fn[0] == '.') || (~fn == 2 && fn[0] == '.' && fn[1] == '.'))
		{
			continue;
		}
		
		full_fn += dir, full_fn += '\\', full_fn += fn;
		
		if(fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			dirs_low << full_fn;
		}
		else
		{
			list << full_fn;
		}
		
		txtclr(full_fn);
		txtclr(fext);
	}
	while(FindNextFileW(ffind, &fdata));
	FindClose(ffind);
	
	txtclr(fnd_all);
	txtsdt(fn, 0, 0, NULL); // Directly manipulated text set back to 0 before it goes out of scope
}

void scanIgn(const wtxt &dir, wtxta &list)
{	
	HANDLE ffind;
	WIN32_FIND_DATAW fdata;
	
	fnd_all += dir, fnd_all += star;
	
	// Start files enumeration =================================================================
	ffind = FindFirstFileExW(
		fnd_all,					// [I] LPCSTR Full			dir + path
		FindExInfoBasic,			// [I] FINDEX_INFO_LEVELS	Search accuracy
		&fdata,						// [O] LPVOID				Ouput file data
		FindExSearchNameMatch,		// [I] FINDEX_SEARCH_OPS	Non wildcard filters
		NULL,						// [I] LPVOID				Must be NULL (no support)
		FIND_FIRST_EX_LARGE_FETCH);	// [I] DWORD				Additional search flags
	// =========================================================================================
	
	if(ffind == INVALID_HANDLE_VALUE)
	{
		return;
	}

	do
	{
		txtsdt(fn, MAX_PATH, 0, fdata.cFileName); // Always set direct manipulated text back to 0!
		txtszu(fn);
		
		if((~fn == 1 && fn[0] == '.') || (~fn == 2 && fn[0] == '.' && fn[1] == '.'))
		{
			continue;
		}
		
		full_fn += dir, full_fn += '\\', full_fn += fn;
		
		if(fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			ui64 i = 0;
			while(ign_dirs[i].s != 0)
			{
				if(full_fn == ign_dirs[i])
				{
					goto skip_file;
				}
				++i;
			}
			
			dirs_low << full_fn;
		}
		else
		{
			list << full_fn;
		}
		
	skip_file:
		
		txtclr(full_fn);
		txtclr(fext);
	}
	while(FindNextFileW(ffind, &fdata));
	FindClose(ffind);
	
	txtclr(fnd_all);
	txtsdt(fn, 0, 0, NULL); // Directly manipulated text set back to 0 before it goes out of scope
}

void scan(const wtxt &dir, wtxta &list, const cwstr *ext, ui64 exts)
{	
	HANDLE ffind;
	WIN32_FIND_DATAW fdata;
	
	fnd_all += dir, fnd_all += star;
	
	// Start files enumeration =================================================================
	ffind = FindFirstFileExW(
		fnd_all,					// [I] LPCSTR Full			dir + path
		FindExInfoBasic,			// [I] FINDEX_INFO_LEVELS	Search accuracy
		&fdata,						// [O] LPVOID				Ouput file data
		FindExSearchNameMatch,		// [I] FINDEX_SEARCH_OPS	Non wildcard filters
		NULL,						// [I] LPVOID				Must be NULL (no support)
		FIND_FIRST_EX_LARGE_FETCH);	// [I] DWORD				Additional search flags
	// =========================================================================================
	
	if(ffind == INVALID_HANDLE_VALUE)
	{
		return;
	}

	do
	{
		txtsdt(fn, MAX_PATH, 0, fdata.cFileName); // Always set direct manipulated text back to 0!
		txtszu(fn);
		
		if((~fn == 1 && fn[0] == '.') || (~fn == 2 && fn[0] == '.' && fn[1] == '.'))
		{
			continue;
		}
		
		full_fn += dir, full_fn += '\\', full_fn += fn;
		
		if(fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			dirs_low << full_fn;
		}
		else
		{
			fishOutFileExt(fn, fext);
			t2low(fext);
			
			bool64 to_skip = true;
			for(ui64 i = 0; i < exts; ++i) // Include only selected file types
			{
				if(fext == ext[i])
				{
					to_skip = false;
					break;
				}
			}
			
			if(!to_skip)
			{
				list << full_fn;
			}
		}
		
		txtclr(full_fn);
		txtclr(fext);
	}
	while(FindNextFileW(ffind, &fdata));
	FindClose(ffind);
	
	txtclr(fnd_all);
	txtsdt(fn, 0, 0, NULL); // Directly manipulated text set back to 0 before it goes out of scope
}

void scanIgn(const wtxt &dir, wtxta &list, const cwstr *ext, ui64 exts)
{	
	HANDLE ffind;
	WIN32_FIND_DATAW fdata;
	
	fnd_all += dir, fnd_all += star;
	
	// Start files enumeration =================================================================
	ffind = FindFirstFileExW(
		fnd_all,					// [I] LPCSTR Full			dir + path
		FindExInfoBasic,			// [I] FINDEX_INFO_LEVELS	Search accuracy
		&fdata,						// [O] LPVOID				Ouput file data
		FindExSearchNameMatch,		// [I] FINDEX_SEARCH_OPS	Non wildcard filters
		NULL,						// [I] LPVOID				Must be NULL (no support)
		FIND_FIRST_EX_LARGE_FETCH);	// [I] DWORD				Additional search flags
	// =========================================================================================
	
	if(ffind == INVALID_HANDLE_VALUE)
	{
		return;
	}

	do
	{
		txtsdt(fn, MAX_PATH, 0, fdata.cFileName); // Always set direct manipulated text back to 0!
		txtszu(fn);
		
		if((~fn == 1 && fn[0] == '.') || (~fn == 2 && fn[0] == '.' && fn[1] == '.'))
		{
			continue;
		}
		
		full_fn += dir, full_fn += '\\', full_fn += fn;
		
		if(fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			ui64 i = 0;
			while(ign_dirs[i].s != 0)
			{
				if(full_fn == ign_dirs[i])
				{
					goto skip_file;
				}
				++i;
			}
			
			dirs_low << full_fn;
		}
		else
		{
			fishOutFileExt(fn, fext);
			t2low(fext);
			
			bool64 to_skip = true;
			for(ui64 i = 0; i < exts; ++i) // Include only selected file types
			{
				if(fext == ext[i])
				{
					to_skip = false;
					break;
				}
			}
			
			if(!to_skip)
			{
				list << full_fn;
			}
		}
		
	skip_file:
		
		txtclr(full_fn);
		txtclr(fext);
	}
	while(FindNextFileW(ffind, &fdata));
	FindClose(ffind);
	
	txtclr(fnd_all);
	txtsdt(fn, 0, 0, NULL); // Directly manipulated text set back to 0 before it goes out of scope
}