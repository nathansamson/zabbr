INCLUDES = -I$(shell pwd) `pkg-config --cflags sdl`
CXXFLAGS = -Wall $(INCLUDES) -Werror -g
CXXSOURCES = $(shell find . -type f -name '*.cpp')
CXXOBJECTS = $(patsubst %.cpp,%.o,$(CXXSOURCES))
DEPFILES = $(patsubst %.cpp,%.d,$(CXXSOURCES))
LIB = libzabbr.a

.PHONY: all clean

all: $(LIB)

$(LIB): $(CXXOBJECTS)
	$(AR) cq $@ $(CXXOBJECTS)

clean:
	$(RM) $(CXXOBJECTS) $(LIB) $(DEPFILES) $(shell find -name "*.d.*") $(shell find -name "*~")

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(INCLUDES) $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(DEPFILES)
