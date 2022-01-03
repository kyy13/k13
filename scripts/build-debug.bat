cd ..
mkdir build
cd build
mkdir Debug
cd Debug
cmake -D CMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++.exe -D CMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" ../../
mingw32-make
pause
