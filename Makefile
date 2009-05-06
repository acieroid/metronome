CC = gcc
LD = $(CC)
CFLAGS = -Wall -g -O2 -ansi -pedantic
TARGET = metronome 
OBJS = main.o tics.o metronome.o

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET) : $(OBJS)
	$(LD) $(OBJS) -o $@ $(LIBS)

clean:
	@rm -f $(OBJS) 
distclean: clean
	@rm -f $(TARGET)
