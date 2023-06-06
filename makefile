#Rio de Janeiro - Federal University of Rio de Janeiro

#depedency file to build the current project code.

CC = gcc
CFLAGS  = -Wall -Werror -std=C11 -D_POSIX_THREAD_SEMANTICS
LDFLAGS = -pthread -lpthread -lrt

ifdef DEBUG
CFLAGS = $(CFLAGS) -DEBUG
endif

TARGET = code

ALL = $(TARGET)

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LDFLAGS)

clean:
	$(RM) $(TARGET)

