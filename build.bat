@echo off

del bin\bgfx_test.exe
cd build\make
make
cd ..\..\bin
bgfx_test
cd ..
