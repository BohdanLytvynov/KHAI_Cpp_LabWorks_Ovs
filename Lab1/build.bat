echo off
echo Starting build...
echo Removing old files
rmdir build /s /q
echo Old files were removed.
echo Starting CMAKE build
set BOOST_ROOT=C:\Users\Administrator\Projects\C++\AddLibs\boost_1_87_0
set BOOST_LIBRARYDIR=%BOOST_ROOT%\stage\lib
echo BOOST_ROOT path is %BOOST_ROOT%
echo BOOST_LIBRARYDIR path is %BOOST_LIBRARYDIR%
cmake -B build 
echo CMAKE build finished. New files generated. You can view them in /build folder.
echo building Debug configuration
cmake --build build --config Debug
echo building configuration finished.
pause