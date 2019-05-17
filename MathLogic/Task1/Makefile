HC=ghc
SOURCES=src/Main.hs src/Lex.hs src/Synt.hs

.PHONY: all run

all: parser

run: 
	./parser

parser: $(SOURCES)
	$(HC) -i./src -tmpdir . ./src/Main.hs -o parser
