
## Created by Anjuta

CXX = g++
CXXFLAGS = -g -Wall -std=c++11
INCFLAGS = 
LDFLAGS = -Wl,-rpath,/usr/local/lib
LIBS = 

PRIORITY_QUEUE_OBJECTS = priority-queue.o
RED_BLACK_BST_OBJECTS = red-black-bst.o
LIST_OBJECTS = list.o
SORT_OBJECTS = sort.o
INTERVAL_SEQUENCE_OBJECTS = interval-sequence.o

PROGRAMS = PriorityQueue RedBlackBST List Sort IntervalSequence

all: $(PROGRAMS) 

PriorityQueue: $(PRIORITY_QUEUE_OBJECTS)
	$(CXX) $^ $(LDFLAGS) $(LIBS) -o $@

RedBlackBST: $(RED_BLACK_BST_OBJECTS)
	$(CXX) $^ $(LDFLAGS) $(LIBS) -o $@

List: $(LIST_OBJECTS)
	$(CXX) $^ $(LDFLAGS) $(LIBS) -o $@

Sort: $(SORT_OBJECTS)
	$(CXX) $^ $(LDFLAGS) $(LIBS) -o $@

IntervalSequence: $(INTERVAL_SEQUENCE_OBJECTS)
	$(CXX) $^ $(LDFLAGS) $(LIBS) -o $@

.SUFFIXES:
.SUFFIXES:	.c .cc .C .cpp .o

priority-queue.o : priority-queue.cc priority-queue.h
	$(CXX) -o $@ -c $(CXXFLAGS) $< $(INCFLAGS)

red-black-bst.o : red-black-bst.cc red-black-bst.h
	$(CXX) -o $@ -c $(CXXFLAGS) $< $(INCFLAGS)

list.o : list.cc list.h
	$(CXX) -o $@ -c $(CXXFLAGS) $< $(INCFLAGS)

sort.o : sort.cc sort.h
	$(CXX) -o $@ -c $(CXXFLAGS) $< $(INCFLAGS)

interval-sequence.o : interval-sequence.cc interval-sequence.h
	$(CXX) -o $@ -c $(CXXFLAGS) $< $(INCFLAGS)

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

clean:
	rm -f *.o
	rm -f $(PROGRAMS)

.PHONY: all
.PHONY: count
.PHONY: clean
