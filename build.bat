@ECHO OFF
set esy_skia_install=%1
call "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Auxiliary/Build/vcvars64.bat"
echo "Compiling..."
for /f "delims=" %%t in ('pkg-config --cflags --msvc-syntax skia') do set cflags=%%t;
for /f "delims=" %%t in ('pkg-config --libs --msvc-syntax skia') do set ldflags=%%t;
for /f "delims=" %%t in ('ocamlc -where') do set ocamlc_loc=%%t
cl.exe /EHsc %cflags% hello.cpp %esy_skia_install%/lib/skia.lib User32.lib
@.\hello.exe
