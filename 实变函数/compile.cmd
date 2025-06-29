@echo off
chcp 65001 > nul
echo Starting compilation...

xelatex -synctex=1 --extra-mem-bot=10000000 real-analysis
xelatex -synctex=1 --extra-mem-bot=10000000 real-analysis
del *.aux
del *.bbl
del *.bcf
del *.blg
del *.glg
del *.glo
del *.gls
del *.idx
del *.ilg
del *.ind
del *.loe
del *.lof
del *.log
del *.lol
del *.lot
del *.mw
del *.nlo
del *.nls
del *(busy)
del *.toc
del *.unq
del *.xdy
del *.xml
del *.out

@echo Compilation finished!

