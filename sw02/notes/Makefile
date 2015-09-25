.PHONY: all build clean

all: round build clean

build:
	pdflatex notes_sw02.tex
	pdflatex notes_sw02.tex
	pdflatex notes_sw02.tex

round:
	octave round_matlab.m
	pdfcrop round_matlab.pdf round_matlab.pdf
clean:
	rm -f *.aux
	rm -f *.lof
	rm -f *.log
	rm -f *.lol
	rm -f *.lot
	rm -f *.out
	rm -f *.toc
