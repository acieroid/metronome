CC = gcc
GZIP = gzip
LD = $(CC)
CFLAGS = -Wall -g -O2 -ansi -pedantic 
TARGET = metronome 
OBJS = main.o tics.o metronome.o
MANPAGE = metronome.1
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
MANDIR = $(PREFIX)/share/man/man1


%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET) : $(OBJS)
	$(LD) $(OBJS) -o $@ $(LIBS)
	$(GZIP) $(MANPAGE)

clean:
	@rm -f $(OBJS) 
distclean: clean
	@rm -f $(TARGET)

install: $(TARGET) 
	install -d $(BINDIR)
	install -d $(MANDIR)
	install -s $(TARGET) $(BINDIR)/$(TARGET)
	install $(MANPAGE).gz $(MANDIR)/$(MANPAGE).gz

uninstall:
	rm $(BINDIR)/$(TARGET)
	rm $(MANDIR)/$(MANPAGE).gz
