CXXFLAGS = -Wall -g --std=c++11

all : dates lists
	@echo "all compiled"

# make sure object files get linked properly
# (or make forgets to link the standard library)
%: %.o
	$(LINK.cc) $^ -o $@

dates : dates.cc CDate.o

CDate.o : CDate.cc CDate.h

linked_list.o : linked_list.cc linked_list.h

lists.o : lists.cc linked_list.h

lists : lists.o linked_list.o

clean :
	rm -f dates CDate.o linked_list.o lists.o lists
