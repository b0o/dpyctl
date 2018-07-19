OS = LINUX
# OS = MACOSX
# OS = WINDOWS

PROG = dpyctl_server

# directory to build in
BUILDDIR = $(abspath $(CURDIR)/build)

# directory to place compiled products in
DISTDIR = $(abspath $(CURDIR)/dist)

LDFLAGS = -Os -Wl,--gc-sections

ifeq ($(OS), LINUX)
	TARGET = $(DISTDIR)/$(PROG)
	CC = gcc
	STRIP = strip
	CFLAGS = -Wall -O2 -DOS_$(OS)
	LIBS = -lusb
else ifeq ($(OS), MACOSX)
	TARGET = $(DISTDIR)/$(PROG).dmg
	SDK = /Developer/SDKs/MacOSX10.5.sdk
	ARCH = -mmacosx-version-min=10.5 -arch ppc -arch i386
	CC = gcc
	STRIP = strip
	CFLAGS = -Wall -O2 -DOS_$(OS) -isysroot $(SDK) $(ARCH)
	LIBS = $(ARCH) -Wl,-syslibroot,$(SDK) -framework IOKit -framework CoreFoundation
else ifeq ($(OS), WINDOWS)
	TARGET = $(DISTDIR)/$(PROG).exe
	CC = i586-mingw32msvc-gcc
	STRIP = i586-mingw32msvc-strip
	CFLAGS = -Wall -O2 -DOS_$(OS)
	LIBS = -lhid -lsetupapi
endif

OBJS = $(BUILDDIR)/$(PROG).o $(BUILDDIR)/hid.o

all: $(TARGET)

$(BUILDDIR)/hid.o: hid_$(OS).c hid.h
	@echo -e "[CC]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CC) $(CFLAGS) $(LIBS) -o "$@" -c "$<"

$(BUILDDIR)/%.o: %.c
	@echo -e "[CC]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CC) $(CFLAGS) $(LIBS) -o "$@" -c "$<"

$(DISTDIR)/$(PROG): $(OBJS)
	@echo -e "[DIST]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CC) $(LDFLAGS) -o "$@" $(OBJS) $(LIBS)
	@$(STRIP) "$@"

$(DISTDIR)/$(PROG).exe: $(DISTDIR)/$(PROG)
	cp $(DISTDIR)/$(PROG) $(DISTDIR)/$(PROG).exe

$(DISTDIR)/$(PROG).dmg: $(DISTDIR)/$(PROG)
	mkdir $(BUILDDIR)/tmp
	cp $(DISTDIR)/$(PROG) $(BUILDDIR)/tmp
	hdiutil create -ov -volname $(PROG) -srcfolder $(BUILDDIR)/tmp $(DISTDIR)/$(PROG).dmg

clean:
	rm -rf $(BUILDDIR) $(DISTDIR)

