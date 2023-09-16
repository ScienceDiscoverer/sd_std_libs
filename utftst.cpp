// CONSOLE
#include <sddb>
#include <utf>

//#include <fstream> // REMOVE THIS!

// TODO UPDATE THIS TEST

int wmain()
{
	txt t = L("H\0e\0l\0l\0o\0 \0W\0u\0r\0l\0d\0!\0\0");
	txtsdt(t, !t, ~t+1, t);
	p|"S"|~t|S|"T"|!t|S|txt2hex(t)|N;
	wtxt wt = WL("I'M BAKA!");
	txtMovToWtxt(t, wt);
	p|"S"|~wt|S|"T"|!wt|S|wt|N;
	
	wt = WL("Hello Wurld!");
	p|"S"|~wt|S|"T"|!wt|S|wt|N;
	t = L("I'M BAKA!");
	wtxtMovToTxt(wt, t);
	p|"S"|~t|S|"T"|!t|S|txt2hex(t)|N;
	
	/* std::ifstream ifs("D:\\D\\Plissken_2097.htm", std::ios::in | std::ios::binary);
	
	char c;
	txt t8;
	while(ifs.get(c))
	{
		t8 += c;
	}
	
	wtxt t16 = t2u16(t8);
	txt t = wt2u8(t16);
	
	std::ofstream ofs("D:\\CONVED.htm", std::ios::out | std::ios::binary);
	ofs << t;
	ofs.close(); */
	
	
	//std::ifstream ifs(".\\tstf\\surrogate.cpp", std::ios::in | std::ios::binary);
	//std::ifstream ifs8(".\\tstf\\surrogate_utf8.cpp", std::ios::in | std::ios::binary);
	//
	//char b;
	//wtxt wt;
	//while(ifs.get(b))
	//{
	//	wchar_t ls = b;
	//	ifs.get(b);
	//	wchar_t ms = b;
	//	
	//	wt += wchar_t(ms << 8 | ls);
	//	
	//	//p|H|short(ms << 8 | ls)|N;
	//}
	//
	//char c;
	//txt t8;
	//while(ifs8.get(c))
	//{
	//	t8 += c;
	//}
	//
	//ifs.close();
	//ifs8.close();
	//
	//txt t = wt2u8(wt);
	//wtxt t16 = t2u16(t8);
	//
	//std::ofstream ofs(".\\tstf\\tesuto.txt", std::ios::out | std::ios::binary);
	//std::ofstream wofs(".\\tstf\\tesuto_utf16LE.txt", std::ios::out | std::ios::binary);
	//
	////txt t = "Hello wurld_F9EB匿__1F1FA+1F1E6_🇺🇦___1F6BD_🚽__1F328(🌨)_CLOUD_WITH_SNOW____бак䦌䦍䦎асете⛪іііно🚯🚯кара\nЛллЛл🚯лЛлл";
	//
	//ofs << t;
	//
	//wofs << (char)0xFF << (char)0xFE;
	//
	//for(ui64 i = 0; i < ~t16; ++i)
	//{
	//	char ls = char(t16[i] & 0xFF);
	//	char ms = char(t16[i] >> 8);
	//	
	//	wofs << ls << ms;
	//}
	//
	//ofs.close();
	//wofs.close();
	
	p|TB|P;
	return 0;
}