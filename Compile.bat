nasm -f win64 imgCvtGrayIntToDouble.asm
gcc -c CFile.c -o cfile.obj -m64
gcc cfile.obj imgCvtGrayIntToDouble.obj -o file.exe -m64
file.exe