@echo off
IF NOT EXIST build mkdir build
pushd build
//copy "c:\opencv\build\x64\vc16\bin\*.dll" .
cl /EHsc -Zi ..\tracker.cpp /I"c:\opencv\build\include" "c:\opencv\build\x64\vc16\lib\opencv_world500.lib"
popd
