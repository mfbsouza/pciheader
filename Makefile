# Makefile by Matheus Souza (github.com/mfbsouza)

# project name
PROJECT  := app

# paths
BUILDDIR := ./build
DBGDIR   := $(BUILDDIR)/debug
RELDIR   := $(BUILDDIR)/release
INCDIR   := ./src

# compiler
PREFIX :=
CC     := $(PREFIX)gcc
CXX    := $(PREFIX)g++
LD     := $(PREFIX)g++
OD     := $(PREFIX)objdump

# flags
CFLAGS   := -Wall -I $(INCDIR) -MMD -MP
CXXFLAGS := -Wall -I $(INCDIR) -MMD -MP
LDFLAGS  := -lpci

ifeq ($(DEBUG),1)
	BINDIR    := $(DBGDIR)
	OBJDIR    := $(DBGDIR)/obj
	CFLAGS    += -g -O0 -DDEBUG
	CXXFLAGS  += -g -O0 -DDEBUG
else
	BINDIR    := $(RELDIR)
	OBJDIR    := $(RELDIR)/obj
	CFLAGS    += -g -O3
	CXXFLAGS  += -g -O3
endif

# sources to compile
ALLCSRCS += $(shell find ./src -type f -name *.c)
ALLCXXSRCS += $(shell find ./src -type f -name *.cpp)

# objects settings
COBJS   := $(addprefix $(OBJDIR)/, $(notdir $(ALLCSRCS:.c=.o)))
CXXOBJS := $(addprefix $(OBJDIR)/, $(notdir $(ALLCXXSRCS:.cpp=.o)))
OBJS    := $(COBJS) $(CXXOBJS)
DEPS    := $(OBJS:.o=.d)

# paths where to search for sources
SRCPATHS := $(sort $(dir $(ALLCSRCS)) $(dir $(ALLCXXSRCS)))
VPATH     = $(SRCPATHS)

# output
OUTFILES := $(BINDIR)/$(PROJECT) $(BUILDDIR)/$(PROJECT).lst

# targets
.PHONY: all clean

all: $(OBJDIR) $(BINDIR) $(OBJS) $(OUTFILES)

# targets for the dirs
$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

# target for c objects
$(COBJS) : $(OBJDIR)/%.o : %.c
ifeq ($(VERBOSE),1)
	$(CC) -c $(CFLAGS) $< -o $@
else
	@echo -e "[CC]\t$<"
	@$(CC) -c $(CFLAGS) $< -o $@
endif

# target for cpp objects
$(CXXOBJS) : $(OBJDIR)/%.o : %.cpp
ifeq ($(VERBOSE),1)
	$(CXX) -c $(CXXFLAGS) $< -o $@
else
	@echo -e "[CXX]\t$<"
	@$(CXX) -c $(CXXFLAGS) $< -o $@
endif

# target for ELF file
$(BINDIR)/$(PROJECT): $(OBJS)
ifeq ($(VERBOSE),1)
	$(LD) $(LDFLAGS) $(OBJS) -o $@
else
	@echo -e "[LD]\t./$@"
	@$(LD) $(LDFLAGS) $(OBJS) -o $@
endif

# target for disassembly and sections header info
$(BUILDDIR)/$(PROJECT).lst: $(BINDIR)/$(PROJECT)
ifeq ($(VERBOSE),1)
	$(OD) -h -S $< > $@
else
	@echo -e "[OD]\t./$@"
	@$(OD) -h -S $< > $@
endif

# target for cleaning files
clean:
	rm -rf $(BUILDDIR)

# include the dependency files, should be the last of the makefile
-include $(DEPS)
