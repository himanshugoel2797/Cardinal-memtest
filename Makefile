TARGET = cardinal_memtest
CC = clang
OBJS = main.o

.PHONY:$(TARGET)

$(TARGET):$(OBJS)
	clang $(OBJS) -o $(TARGET)

clean:
	rm -rf $(OBJS)
	rm -rf $(TARGET)