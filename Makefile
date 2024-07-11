CXX = g++
CXXFLAGS = -std=c++11 -pthread

TARGET = ex3.out
OBJS = main.o BoundedBuffer.o Producer.o Dispatcher.o CoEditor.o ScreenManager.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp BoundedBuffer.h Producer.h Dispatcher.h CoEditor.h ScreenManager.h
	$(CXX) $(CXXFLAGS) -c main.cpp

BoundedBuffer.o: BoundedBuffer.cpp BoundedBuffer.h
	$(CXX) $(CXXFLAGS) -c BoundedBuffer.cpp

Producer.o: Producer.cpp Producer.h BoundedBuffer.h
	$(CXX) $(CXXFLAGS) -c Producer.cpp

Dispatcher.o: Dispatcher.cpp Dispatcher.h BoundedBuffer.h
	$(CXX) $(CXXFLAGS) -c Dispatcher.cpp

CoEditor.o: CoEditor.cpp CoEditor.h BoundedBuffer.h
	$(CXX) $(CXXFLAGS) -c CoEditor.cpp

ScreenManager.o: ScreenManager.cpp ScreenManager.h BoundedBuffer.h
	$(CXX) $(CXXFLAGS) -c ScreenManager.cpp

clean:
	rm -f $(OBJS) $(TARGET)
