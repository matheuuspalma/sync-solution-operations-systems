#Rio de Janeiro - Federal University of Rio de Janeiro

#depedency file to build the current project code.

CC = gcc
LDFLAGS = -pthread -lpthread -lrt

ifdef debug
CFLAGS = -Wall -Werror -std=c11 -D_POSIX_THREAD_SEMANTICS -DDEBUG
else
CFLAGS = -Wall -Werror -std=c11 -D_POSIX_THREAD_SEMANTICS
endif

TARGET = code

ALL = $(TARGET)

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LDFLAGS)

clean:
	$(RM) $(TARGET)

