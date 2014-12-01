#
# Makefile
#

.SUFFIXES: .tex .dvi .ps .fig .eps .gnu .c
#PDF = ps2pdf -dPDFSETTINGS=/printer -dMaxSubsetPct=100 \
#      -dCompatibilityLevel=1.4 -dSubsetFonts=true -dEmbedAllFonts=true
PDF = ps2pdf14 -dPDFSETTINGS=/prepress -dEmbedAllFonts=true \
      -dSubsetFonts=true -dMaxSubsetPct=100

TARGET=report
DOBIB=yes
DOPLOT=no

SPELL := aspell -a
UNAME := $(shell uname)
VIEWER := evince
ifeq ($(UNAME), Darwin)
	#VIEWER := open -a Skim
	VIEWER := open
endif

all:    pdf

display: $(TARGET)
	dvips -Ppdf -Pcmz -Pamz -t letter -D600 -G0 -o $(TARGET).ps $(TARGET).dvi
	$(PDF) $(TARGET).ps
	$(VIEWER) $(TARGET).pdf

pdf: $(TARGET)
	dvips -Ppdf -Pcmz -Pamz -t letter -D600 -G0 -o $(TARGET).ps $(TARGET).dvi
	$(PDF) $(TARGET).ps

pdftex: $(TARGET)
	pdftex -o $(TARGET).pdf

$(TARGET): $(TARGET).tex
ifeq ($(DOPLOT),yes)
	cd plots; make
endif
	latex $(TARGET)
	latex $(TARGET)
	latex $(TARGET)
ifeq ($(DOBIB),yes)
	bibtex $(TARGET)
	latex $(TARGET)
	latex $(TARGET)
	latex $(TARGET)
endif

clean:
	$(RM) $(TARGET).ps $(TARGET).pdf $(TARGET).log $(TARGET).aux \
	      $(TARGET).dvi $(TARGET).tex.flc
	$(RM) $(TARGET).bbl $(TARGET).blg
	$(RM) *.kill kill*
ifeq ($(DOPLOT),yes)
	cd plots; make clean
endif

purge:  clean
	$(RM) *~

nums:
	gnuplot plotGraph

#spell:
#	cat $(TF) | awk '{ if (index($$0,"%")!=1) print $$0}' |  $(SPELL)
#	#       detex $(TF) |  spell
