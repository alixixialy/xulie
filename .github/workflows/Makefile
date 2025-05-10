CC = g++
CFLAGS = -Wall -std=c++11
TARGET = msa_program
SOURCES = MSA.cpp kband.cpp kband1fasta.cpp kband2.cpp score_SP.cpp shuangxuliedp.cpp shuangxuliedpfasta.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
    $(CC) $(CFLAGS) -o $@ $^  # 必须用 Tab 缩进

clean:
    rm -f $(OBJECTS) $(TARGET)  # 同样需要 Tab 缩进
