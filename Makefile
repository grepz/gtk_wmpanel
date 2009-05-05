CC = /usr/bin/gcc
MAKE = /usr/bin/make -s
LD = /usr/bin/ld
OBJDUMP = 
OBJCOPY = 
AS = /usr/bin/as
ASFLAGS = 
AR = /usr/bin/ar
Q = @
GREP = /bin/grep
ECHO = /bin/echo
LN = /bin/ln
VERSION = 0.0.1
NAME = TinyPanel
ATSIGN ?= @

CFLAGS  := -Wall -g $(shell pkg-config gtk+-2.0 --cflags)
LDFLAGS := $(shell pkg-config gtk+-2.0 --libs)

PANEL_OBJS = panel.o image.o applet.o menu-applet.o

all: panel

panel: $(PANEL_OBJS)
	$(Q)$(ECHO) "[BLD] Compiling ..."
	$(Q)$(CC) $(LDFLAGS) $(CFLAGS) $(PANEL_OBJS) -o $@

clean:
	$(Q)$(ECHO) "[CLN] Cleaning ..."
	$(Q)rm -f $(PANEL_OBJS) panel

