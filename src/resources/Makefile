INCLUDES = -I../ `pkg-config --cflags sdl`
CXXFLAGS += $(INCLUDES)
CXXSOURCES = $(shell find . -maxdepth 1 -type f -name '*.cpp' -not -name 'soundresource.cpp' -not -name 'musicresource.cpp')
CXXOBJECTS = $(patsubst %.cpp,%.o,$(CXXSOURCES))
DEPFILES = $(patsubst %.cpp,%.d,$(CXXSOURCES))
SUBDIRS = 

.PHONY: all clean

all: $(CXXOBJECTS)

clean:
	@for i in $(SUBDIRS); do ($(MAKE) -C $$i $(MFLAGS)); done
	$(RM) $(CXXOBJECTS) $(DEPFILES) *~

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(INCLUDES) $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(DEPFILES)

