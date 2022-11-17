set PATH=%QTDIR%;%QTDIR%\bin;%PATH%
mkdir ..\build_VS2022
cd ..\build_VS2022
cmake -Wno-dev -G "Visual Studio 17 2022" -A x64 ..\source

pause .