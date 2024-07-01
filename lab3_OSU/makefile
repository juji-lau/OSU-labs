CC = gcc
CFLAGS = -gcc -Wall
TARGET = lab3_out
SRCS = lab3_juji.c
OBJS = $(SRCS:.c=.o)

#Default target
all: $(TARGET)

#link target to executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TAEGET) $(OBJS)

#Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean: 
	rm -f $(TARGET) $(OBJS)