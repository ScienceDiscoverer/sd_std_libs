// CONSOLE
#include <conint>




////////////////////////////////////////////////////////////////// TODO IMPROVE THE RNG!@!
typedef unsigned long long ull;
const ull mod_rng = 0x10000000000; //2^40 modulus for RNG engine!

ull getSeed()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
    return (ull)(li.QuadPart % 100000000000000/100); //max seed 1*10^12 - 1
}

//Linear Congruential Pseudo Random Number Generator
ull rng(int seed) //seed must be 0 <= seed < mod!
{   //multiplyer also must be multi%8 = 5 !!! For best uniformal distribution!
	const ull multi = 0x4C8F53A795; //multiplier 2.|multi - 1 must be % = 0 for all mod's prime factors|
	const ull inc = 1; //increment 1.|inc and mod must be co-prime|
	const ull mod = mod_rng; //2^40 modulus 3.|multi must be %4 = 0 if mod%4 = 0|
	
	return (multi * seed + inc) % mod;
}

const ull seed = getSeed(); //get seed
ull rnd_num = seed;

//uniform random number distribution of range
int rngRange(int min, int max) //min,max must be non negative!
{
	const ull rngrg = mod_rng;//RNG range
	int range = max - min + 1;
	ull scale = rngrg/range; //big range part to 1 part of range
	rnd_num = rng((int)rnd_num);
	return (int)(rnd_num/scale + min); //downscale
}
////////////////////////////////////////////////////////////////// TODO IMPROVE THE RNG!@!




THREAD progBar(void *param)
{
	DWORD to_sleep = (DWORD)rngRange(20, 400);
	for(ui64 i = 0; i < 101; ++i)
	{
		printProgBar(100, i, 0, (ui64)param, 0);
		Sleep(to_sleep);
	}
	return 0;
}

i32 wmain()
{
	p|DC;
	
	CreateThread(NULL, 0, progBar, (void *)0, 0, NULL);
	CreateThread(NULL, 0, progBar, (void *)2, 0, NULL);
	CreateThread(NULL, 0, progBar, (void *)4, 0, NULL);
	CreateThread(NULL, 0, progBar, (void *)6, 0, NULL);
	CreateThread(NULL, 0, progBar, (void *)8, 0, NULL);
	CreateThread(NULL, 0, progBar, (void *)10, 0, NULL);
	
	p|P;
	return 0;
}