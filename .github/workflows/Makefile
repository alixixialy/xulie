CC = g++  # 编译器
CFLAGS = -Wall -std=c++11  # 编译参数
TARGET = msa_program  # 生成的可执行文件名
SOURCES = MSA.cpp kband.cpp kband1fasta.cpp kband2.cpp score_SP.cpp shuangxuliedp.cpp shuangxuliedpfasta.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
    $(CC) $(CFLAGS) -o $@ $^

clean:
    rm -f $(OBJECTS) $(TARGET)
