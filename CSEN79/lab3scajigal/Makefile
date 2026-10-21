# CSEN 79
# Lab 3 Makefile

STD=-std=c++20
OPT=-g
CXXFLAGS=${STD} ${OPT}
TARFLAGS=--no-mac-metadata

%.o: %.cxx
	$(CXX) -c $(CXXFLAGS) $<

SRCS=roster.cxx rostermain.cxx
OBJS=$(SRCS:.cxx=.o)
ALL=rostertest

all: $(ALL)

rostertest:	$(OBJS)
	$(CXX) -o $@ $(CXXFLAGS) $+

clean:
	/bin/rm -f $(OBJS) $(ALL)
	/bin/rm -f roster.tar
	/bin/rm -rf $(ALL:=.dSYM)

depend: $(SRCS)
	TMP=`mktemp -p .`; export TMP; \
    sed -e '/^# DEPENDENTS/,$$d' Makefile > $$TMP; \
    echo '# DEPENDENTS' >> $$TMP; \
    $(CXX) -MM $+ >> $$TMP; \
    /bin/mv -f $$TMP Makefile


# DEPENDENTS
roster.o: roster.cxx person.h roster.h
rostermain.o: rostermain.cxx person.h roster.h
