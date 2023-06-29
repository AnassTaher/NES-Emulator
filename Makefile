IDIR=include
ODIR=obj
SRCDIR=src

DEPS = $(wildcard $(IDIR)/*.hpp)
SRCS = $(wildcard $(SRCDIR)/*.cc)
_OBJ = $(patsubst $(SRCDIR)/%,$(ODIR)/%,$(SRCS:.cc=.o))	
OBJ = $(filter-out $(ODIR)/main.o,$(_OBJ))

CXX = g++
override ccFLAGS+=-I$(IDIR) -g -Wall -Wpedantic -std=c++11 -Wformat-extra-args -fPIE -Wno-deprecated

DEPS2 := $(OBJ:.o=.d)

$(OBJ) $(ODIR)/main.o: $(DEPS)

-include $(DEPS2)

$(ODIR)/%.o: $(SRCDIR)/%.cc
	+@[ -d $(ODIR) ] || mkdir -p $(ODIR)
	$(CXX) -MMD $(ccFLAGS) -c -o $@ $<

main: $(OBJ) $(ODIR)/main.o
	$(CXX) -o $@ $^ $(ccFLAGS) $(LIBS)


clean:
	-rm -f $(ODIR)/*.o *~ core.* $(INCDIR)/*~
	-rm -f $(ODIR)/*.d
	-rm -f main

