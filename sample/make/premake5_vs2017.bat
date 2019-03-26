@echo OFF

pushd ..\..\make\
call premake5_vs2017.bat
popd

call ..\..\tool\premake\premake5.exe vs2017

pause