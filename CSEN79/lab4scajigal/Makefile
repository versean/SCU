# Lab 4 Makefile

STD=-std=c++20
OPT=-g
# redefine this to wherever lab3 is
INC=
CXXFLAGS=${STD} ${OPT} ${INC}
CFLAGS=${OPT}

%.o: %.cxx
	$(CXX) -c $(CXXFLAGS) $<

ROSTERSRCS=rosterptr.cxx rosterptrmain.cxx rostertest.cxx
ROSTEROBJS=$(ROSTERSRCS:.cxx=.o) roster.o
ALL=rosterptrtest

all: $(ALL)

rosterptrtest:	$(ROSTEROBJS)
	$(CXX) -o $@ $(CXXFLAGS) $+

clean:
	/bin/rm -f $(ROSTEROBJS) $(ALL)
	/bin/rm -rf $(ALL:=.dSYM)


depend: $(ROSTERSRCS)
	TMP=`mktemp -p .`; export TMP; \
	sed -e '/^# DEPENDENTS/,$$d' Makefile > $$TMP; \
	echo '# DEPENDENTS' >> $$TMP; \
	$(CXX) -MM $(INC) $+ >> $$TMP; \
	/bin/mv -f $$TMP Makefile

# DEPENDENTS
rosterptr.o: rosterptr.cxx person.h roster.h rosterptr.h
rosterptrmain.o: rosterptrmain.cxx person.h roster.h rosterptr.h
rostertest.o: rostertest.cxx person.h roster.h rosterptr.h
