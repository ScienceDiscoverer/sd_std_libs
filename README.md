# ScienceDiscoverer's STD Libraries

[![GitHub release (with filter)](https://img.shields.io/github/v/release/ScienceDiscoverer/sd_std_libs)](../../releases/latest)
&nbsp;&nbsp;&nbsp;![GitHub all releases](https://img.shields.io/github/downloads/ScienceDiscoverer/sd_std_libs/total)
&nbsp;&nbsp;&nbsp;[![Sponsor Badge](https://img.shields.io/badge/%E2%98%95_Sponsor-blue)](https://www.buymeacoffee.com/sciencediscoverer)

Personal take on implementing all the standard C++ and C libraries using just low level API functions and a tiny subset of built-in C functions.

## Features
* Fully functional, minimal and fast custom text (`txt`) type optimised for Windows. It has no public functions, only operators to make it mimic built-in types (replaces `std::string`).
* Wide text type (`wtxt`) is not done by the way of a lazy template. It is a total copy of the `txt` except for the parts specific for the wide type. It is totally independent from `txt` and can be used by itself. Therefore, it is as fast, or sometimes even faster than `txt` and much faster than `std::wstring`.
* Dynamic array built without the overhead of templates. Currently arrays of texts and ints are supported, but custom array for any type can be quickly constructed if needed (replaces `std::vector` and `std::array`).
* Powerful console writer (replaces `std::iostream`) with compact syntax that supports colours, formatting, pauses, padding, table output, console buffer trimming and more!
* Fast and simple console input handler
* Printer to text types (replaces `std::stringstream`).
* Fast file printers/readers (replaces `std::fstream`).
* Custom math library. Not too many functions there yet, but I add only the ones I ever needed. And ones I actually understand, currently.
* Low level memory manipulation functions like `memcmp` and `memcpy` that beat standard implementations in speed of execution.
* Stopwatches for profiling with convenient and simple syntax.
* Extensive debugging tools library - output formatted debug info into special debugging window, set breakpoints without any debugger, display detailed exceptions information and much more!
* Seamless conversion between UTF16 and UTF8 texts on the fly, using correct UNICODE encoding.
* Simple, minimalistic libraries for console/window interfaces. Create low level, streamlined custom interfaces with ease!
### Not yet implemented
* Floating numbers (`double`, `float`). Yes, I know. But it's very hard to understand how the encoding of this numbers work, so I never have the time to actually implement the conversion to texts/printing.

## Full list of libraries
* `binf` - binary file container
* `clip` - make copy-pasting easy
* `conint` - console interface
* `darr` - dynamic array base interface, all other dynamic arrays must inherit from it
* `fileinf.h` - supporting header for all file printers/readers
* `filep` - file printer
* `filer` - file reader
* `filepr` - file printer/reader
* `fnmanip.h` - small file name manipulation helper library
* `math` - mathematical functions
* `mmanip` - low level memory manipulation
* `padinf.h` - helper header for STD/text printers
* `sddb` - debugging tools
* `stdp` - STD (console) printer
* `stdr` - STD (console) reader
* `tests.h` - functions common for all the unit tests
* `time` - stopwatches for profiling and other timing tools
* `txt` - the base of all of this, custom ~~string~~ text type
* `wtxt` - wide text type
* `txta` - dynamic array of texts
* `wtxta` - dynamic array of wide texts
* `txtp` - text printer
* `wtxtp` - wide text printer
* `types.h` - common types and constants definitions
* `ui64a` - dynamic array of 64 bit wide unsigned integers
* `utf` - UTF-8 to UTF-16 and vice versa conversion
* `utfcase` - humongous switch case for converting Unicode letters into lower/upper case
* `wndint` - small but powerful minimalistic windows creation and manipulation library

## How to build

Just double-click the `msvc_build.cmd` file. Yep. As easy as this. Well, that is, if you have your Visual Studio installed, of course. And if your VS `vcvars64.bat` file and `bin\HostX64\x64` directory are located at this paths:

```
set "bat_dir=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
set "bin_dir=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.34.31933\bin\HostX64\x64"
```
If not, you will have to merely located this file and directory and copy-paste it into the `msvc_build.cmd`. Then just launch it and wait until it does all the job for you. Yes, you don't even need to open the Visual Studio. Ever. I recommend you to try out my [Notepad++ C++ IDE](https://github.com/ScienceDiscoverer/npp_msvc_ide), if you like the idea of ditching the bloated, laggy and overengineered VS!

## Examples & Testing

You can see the examples of how to actually use this libraries in your code by looking at all the included unit tests (located in the root directory and has `tst.cpp` in the end of a filename). You can also see how `txt` and `wtxt` stands up in a pitched profiling battle versus the `std::string` and `std::wstring` by defining `#define PROFILING_ON`. Beware, however, that it is not possible to make this test 100% accurate, as optimising compiler cheats a lot in favour of standard libs (confirmed by looking at raw ASM output of the tests). But even so, my libs beat `std`-s consistently in most of the tests.