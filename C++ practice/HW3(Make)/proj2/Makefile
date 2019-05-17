CXX := g++

NAME := mylib
MAJOR := 5
MINOR := 1
RELEASE := 10
LIBNAME := lib$(NAME).dll
LIBNAME_FULL := $(LIBNAME).$(MAJOR).$(MINOR).$(RELEASE)

SOURCES := hello.cpp here.cpp bye.cpp
OBJECTS := $(SOURCES:%.cpp=out/%.o)

out/main.exe: out/main.o out/$(LIBNAME_FULL)
	$(CXX) -o $@ $< -Lout -l$(NAME)

out/$(LIBNAME_FULL): $(OBJECTS)
	$(CXX) -fPIC -shared -Wl,-soname,$(LIBNAME).$(MAJOR) -o $@ $(OBJECTS)
	ln -sf $(LIBNAME_FULL) out/$(LIBNAME).$(MAJOR)
	ln -sf $(LIBNAME_FULL) out/$(LIBNAME)

out/%.o: %.cpp
	mkdir -p out
	$(CXX) -c -o $@ $<

clean:
	rm -rf out