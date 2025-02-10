echo Starting build...
echo Removing old files
rmdir build /s /q
echo Old files were removed.
echo Starting CMAKE build
cmake -B build
echo CMAKE build finished. New files generated. You can view them in /build folder.
echo building Debug configuration
cmake --build build --config Debug
echo building configuration finished.
pause