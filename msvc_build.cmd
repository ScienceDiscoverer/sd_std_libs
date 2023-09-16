@echo off
REM ADD LOOP HERE TO TEST IF 2022 NOT EXIIST TEST 2021 2020 2019 ETC TAKE CURYEAR AND DECREMENT!

set "bat_dir=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
set "bin_dir=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.34.31933\bin\HostX64\x64"

if not exist "%bat_dir%" echo Failed to find VCVARS64.BAT at "%bat_dir%". Edit 'msvc_build.cmd' with the correct path to your Visual Studio! & pause & exit

if not exist "%bin_dir%" echo Failed to find VCVARS64.BAT at "%bin_dir%". Edit 'msvc_build.cmd' with the correct path to your Visual Studio 'bin' folder! & pause & exit

cmd /c "%bat_dir%"
set "path=%bin_dir%;%path%"

set "disabled_warns=/wd4530 /wd4710 /wd4711 /wd5045 /wd4626 /wd4625 /wd5026 /wd5027"

::NOTE: #pragma warning has priority over switches
::C4514 The optimizer removed an inline function that is not called. (DISABLE CANDIDATE)
::C4530 C++ exception handler used, but unwind semantics are not enabled. Specify /EHsc
::C4710 function not inlined (code gen.)
::C4711 function selected for automatic inline expansion (code gen.)
::C5045 compiler will insert Spectre mitigation for memory load if /Qspectre switch specified (code gen.)
::C4626 assignment operator was implicitly defined as deleted
::C4625 copy constructor was implicitly defined as deleted
::C5026 move constructor was implicitly defined as deleted
::C5027 move assignment operator was implicitly defined as deleted

set "libs=txt wtxt utf utfcase txtp wtxtp stdp stdr sddb darr time wndint"
set "obj_out_dir=/Folib\"

:build_all_libs_loop
for /f "tokens=1,* delims= " %%a in ("%libs%") do (
	set "libs=%%b"
	
	if not exist lib\%%a.cpp goto :continue
	if exist lib\%%a.lib ( if exist lib\%%ad.lib goto :continue )
	
	set "name=lib\%%a"
	goto :build_func
)

set "lib_build_done=1"
set "obj_out_dir="

for %%f in (*.cpp) do (
	set "name=%%~nf"
	call :build_func
)

exit

:build_func

set "ico_name="
set "manifest_name="
set "res_name=main"
set "build_rc=0"
set "no_res=1"
set "subsys=WINDOWS"
set "seh=/EHsc"
set "optim=/O2 /Oi /GL /Gy"
set "linkopt=/LTCG /INCREMENTAL:NO"
set "warns=/Wall"
set "slib="
set "asm="
set "debug=/MT"
set "debug_link="
set "debug_def="
set "no_def_lib=/NODEFAULTLIB:libcmtd.lib"
set "build_inc="
set "start_up=/ENTRY:wmainCRTStartup"
set "res_file="
set "inc_dir=/I %~dp0\lib\"
set "lib_dir=/LIBPATH:%~dp0\lib\"

title sd_msvc_build

set /p fline=< %name%.cpp

:parse_loop
for /f "tokens=1,* delims= " %%a in ("%fline%") do (
	if "%%a"=="CONSOLE" set "subsys=CONSOLE"
	if "%%a"=="DSEH" set "seh=/wd4577"
	if "%%a"=="NOPT" set "optim=/Od" & set "linkopt="
	if "%%a"=="NW" set "warns=/w"
	if "%%a"=="SLIB" set "slib=/c"
	if "%%a"=="DBG" set "debug=/MTd /Z7" & set "debug_link=/DEBUG" & set "debug_def=/D DEBUG" & set "no_def_lib=/NODEFAULTLIB:libcmt.lib"
	if "%%a"=="EPMAIN" set "start_up=/ENTRY:mainCRTStartup"
	
	set "fline=%%b"
	goto :parse_loop
)

if not exist man ( set "res_name=%name%" & goto :nomanifest ) else ( set "no_res=0" )
if not exist ico set "res_name=%name%" & goto :nodefres
if not exist man\%name%.manifest ( if not exist ico\%name%.ico (
if not exist res mkdir res
if not exist res\%res_name%.res (
echo 1 24 "man\%res_name%.manifest"> res\%res_name%.rc
echo MAINICON ICON "ico\%res_name%.ico">> res\%res_name%.rc
set "build_rc=1" )
if exist res\%name%.res ( set "res_name=%name%" )
goto :noico ) else ( set "res_name=%name%" ) ) else ( set "res_name=%name%" )

:nodefres

if not exist man\%name%.manifest ( set "manifest_name=main" ) else ( set "manifest_name=%name%" )
if not exist res mkdir res
if not exist res\%res_name%.res (
echo 1 24 "man\%manifest_name%.manifest"> res\%res_name%.rc
set "build_rc=1" )
:: REMEMBER TO MAKE ID 2 FOR DLL!

:nomanifest

if not exist ico ( goto :noico ) else ( set "no_res=0" )
if not exist ico\%name%.ico ( set "ico_name=main" ) else ( set "ico_name=%name%" )
if not exist res mkdir res
if not exist res\%res_name%.res (
if "%build_rc%"=="1" ( echo MAINICON ICON "ico\%ico_name%.ico">> res\%res_name%.rc ) else ( echo MAINICON ICON "ico\%ico_name%.ico"> res\%res_name%.rc ) 
set "build_rc=1" )

:noico

if "%build_rc%"=="1" rc /r /nologo res\%res_name%.rc

if "%no_res%"=="0" ( if "%slib%"=="" set "res_file=res\%res_name%.res" )

if "%debug%"=="/MTd /Z7" ( if "%optim%" neq "/Od" set "optim=/O2 /Oi /Gy" & set "linkopt=" )

:recompile
cl %warns% %disabled_warns% /external:anglebrackets /external:W0 /diagnostics:caret /I %~dp0 %optim% %debug_def% /D _%subsys% /D _UNICODE /D UNICODE /D _CRT_SECURE_NO_WARNINGS /Gm- %seh% %debug% /FC /GS- /J /permissive- /nologo %slib% %asm% %inc_dir% %name%.cpp %res_file% %obj_out_dir% /link /SUBSYSTEM:%subsys% %linkopt% %debug_link% %lib_dir% /DYNAMICBASE:NO /MACHINE:X64 %start_up% /NODEFAULTLIB:msvcrt.lib /NODEFAULTLIB:msvcrtd.lib %no_def_lib%

if %ERRORLEVEL% equ 1 pause >nul & exit /b
if %ERRORLEVEL% equ 2 pause >nul & goto :cleanup

::static lib assemble begin
if "%slib%"=="/c" ( if "%debug_link%"=="/DEBUG" (
lib /NOLOGO /VERBOSE /OUT:%name%d.lib %name%.obj ) else (
lib /NOLOGO /VERBOSE %name%.obj
set "debug=/MTd /Z7" & set "debug_link=/DEBUG" & set "debug_def=/D DEBUG" & set "no_def_lib=/NODEFAULTLIB:libcmt.lib"
if "%optim%" neq "/Od" set "optim=/O2 /Oi /Gy" & set "linkopt="
cls
goto :recompile )

if %ERRORLEVEL% neq 0 ( pause >nul & goto :cleanup ) else ( goto :cleanup ) )
::static lib assemble end

:cleanup
del %name%.obj >nul 2>&1
del res\%res_name%.rc >nul 2>&1

:continue
cls
if "%lib_build_done%"=="1" ( exit /b ) else ( goto :build_all_libs_loop )