CXX=g++
RM=rm -f
CPPFLAGS=-O2 -g -Wall -fmessage-length=0 -std=c++14
LDFLAGS=
LDLIBS= -lpthread

SRCS = tutor.cpp Config.cpp Tutorials.cpp
SRCS += samples/Dummy.cpp
SRCS += samples/Base.cpp
SRCS += samples/Thread1.cpp

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