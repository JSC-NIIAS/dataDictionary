
MAKEFLAGS += --no-print-directory --silent


TOPDIR=../

CC=cc
CPPFLAGS+=-I$(TOPDIR)/Foundation/Bits
CPPFLAGS+=-I$(TOPDIR)/Foundation/Packets
#CPPFLAGS+=-I$(TOPDIR)/Generated/Packets
CFLAGS += -std=c99 -Wall -pedantic 
#CFLAGS += -Werror 
#CFLAGS += -Weverything -Wno-padded 
LDFLAGS += -L$(TOPDIR)/Foundation/Bits -lbits
#LDFLAGS += -L$(TOPDIR)/Generated/Packets -lgenerated_packets

all: clean test_packets
	./test_packets

SRC := PacketFactory.o\
       PacketSequence.c\
       EurobaliseTelegram.c

FUNCTIONS := Packet_DecodeBit.c\
             Packet_Delete.c\
             Packet_EncodeBit.c\
             Packet_Equal.c\
             Packet_Length.c\
             Packet_Print.c

PACKETS := AdhesionFactor.o\
         ErrorReporting.o\
         Level23TransitionInformation.o\
         TemporarySpeedRestriction.o\
         EndOfInformation.o

TESTS := AdhesionFactor_Tests.o\
         ErrorReporting_Tests.o\
         Level23TransitionInformation_Tests.o\
         TemporarySpeedRestriction_Tests.o\
         EndOfInformation_Tests.o

OBJ := $(SRC:.c=.o) $(FUNCTIONS:.c=.o) $(PACKETS:.c=.o) $(TESTS:.c=.o)

test_packets: test_packets.o $(OBJ)
	$(CC) -o $@ $+ $(LDFLAGS)


clean:
	$(RM) test_packets
	$(RM) *.o
	$(RM) *.orig


ASTYLEOPTIONS += -A1
ASTYLEOPTIONS += --break-blocks
ASTYLEOPTIONS += --pad-oper
ASTYLEOPTIONS += --pad-header
ASTYLEOPTIONS += --lineend=linux
ASTYLEOPTIONS += --add-brackets
ASTYLEOPTIONS += --indent=spaces=4
ASTYLEOPTIONS += --indent-classes
ASTYLEOPTIONS += --indent-switches
ASTYLEOPTIONS += --indent-col1-comments
ASTYLEOPTIONS += --min-conditional-indent=0

export ASTYLE=astyle $(ASTYLEOPTIONS)

%.format:%.c FORCE
	@$(ASTYLE) $<

%.format:%.h FORCE
	@$(ASTYLE) $<


format: FORCE
	@$(ASTYLE) *.c *.h


FORCE:

