CXX=g++
RM=rm -f
CPPFLAGS=-O2 -g -Wall -fmessage-length=0 -std=c++14
LDFLAGS=
LDLIBS=

SRCS=samples/Dummy.cpp tutor.cpp Config.cpp Tutorials.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: tutor

tutor: $(OBJS)
	$(CXX) $(LDFLAGS) -o tutor $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) *~ .depend

include .depend