#pragma once

struct FileInfoA
{
	const char *fn;
};

struct FileInfoW
{
	const wchar_t *fn;
};

inline FileInfoA FO(const char *fn)
{
	FileInfoA fi;
	fi.fn = fn;
	return fi;
}

inline FileInfoW FO(const wchar_t *fn)
{
	FileInfoW fi;
	fi.fn = fn;
	return fi;
}

inline FileInfoA FO(const txt &fn)
{
	FileInfoA fi;
	fi.fn = fn;
	return fi;
}

inline FileInfoW FO(const wtxt &fn)
{
	FileInfoW fi;
	fi.fn = fn;
	return fi;
}

inline bool64 fileExists(const char *fn)
{
	DWORD attr = GetFileAttributesA(fn);
	if(attr == INVALID_FILE_ATTRIBUTES)
	{
		return false;
	}
	
	return true;
}

inline bool64 fileExists(const wchar_t *fn)
{
	DWORD attr = GetFileAttributesW(fn);
	if(attr == INVALID_FILE_ATTRIBUTES)
	{
		return false;
	}
	
	return true;
}