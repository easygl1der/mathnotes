@echo off
chcp 65001 > nul
@echo Starting...
cd kaobook-template
xelatex -synctex=1 --extra-mem-bot=10000000 main
makeindex main.nlo -s nomencl.ist -o main.nls
makeindex main
biber main
makeglossaries main
xelatex -synctex=1 --extra-mem-bot=10000000 main
xelatex -synctex=1 --extra-mem-bot=10000000 main
@REM xelatex -synctex=1 --extra-mem-bot=10000000 main
cd ..
@echo Finish...
