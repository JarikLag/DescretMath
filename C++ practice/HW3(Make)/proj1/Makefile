CXX := g++

NAME := mylib
LIBNAME  := lib$(NAME).a

SOURCES := hello.cpp here.cpp bye.cpp
OBJECTS := $(SOURCES:%.cpp=out/%.o)

out/main.exe: out/main.o out/$(LIBNAME)
	$(CXX) -o $@ $< -Lout -l$(NAME)
	
out/$(LIBNAME): $(OBJECTS)
	ar cr $@ $^
	
out/%.o: %.cpp
	mkdir -p out
	$(CXX) -c -o $@ $<

clean:
	rm -rf out