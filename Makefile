# Do not modify this file, as it is overwritten by the default file in the

IDIR=include
ODIR=obj
SRCDIR=src

DEPS = $(wildcard $(IDIR)/*.h)
SRCS = $(wildcard $(SRCDIR)/*.cpp)
_OBJ = $(patsubst $(SRCDIR)/%,$(ODIR)/%,$(SRCS:.cpp=.o))	
OBJ = $(filter-out $(ODIR)/main.o,$(_OBJ))

CXX = g++
override CPPFLAGS+=-I$(IDIR) -g -Wall -Wpedantic -std=c++11 -Wformat-extra-args -fPIE -Wno-deprecated

DEPS2 := $(OBJ:.o=.d)

$(OBJ) $(ODIR)/main.o: $(DEPS)

-include $(DEPS2)

$(ODIR)/%.o: $(SRCDIR)/%.cpp
	+@[ -d $(ODIR) ] || mkdir -p $(ODIR)
	$(CXX) -MMD $(CPPFLAGS) -c -o $@ $<

main: $(OBJ) $(ODIR)/main.o
	$(CXX) -o $@ $^ $(CPPFLAGS) $(LIBS)


clean:
	-rm -f $(ODIR)/*.o *~ core.* $(INCDIR)/*~
	-rm -f $(ODIR)/*.d
	-rm -f main

