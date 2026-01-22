CXX = clang++
CXXFLAGS = -std=c++23 -Wall -Wextra -pedantic -g
LDFLAGS = -pthread

SRCS = CMS.cpp
TARGET = CMS
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

test: $(TARGET)
	./$(TARGET)