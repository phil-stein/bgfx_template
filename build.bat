@echo off

del _bin\bgfx_test.exe
cd _build\make
make
cd ..\..\_bin
bgfx_test
cd ..
