
MAKEFLAGS += --no-print-directory --silent


TOPDIR=../

all: clean test_packets test_issue31_1 test_issue31_2 TrackToTrain_telegram_test
	./test_packets
	./test_issue31_1
	./test_issue31_2
	./TrackToTrain_telegram_test

VPATH = $(TOPDIR)/Telegram

include $(TOPDIR)/Makefile.template

CPPFLAGS+=-I$(TOPDIR)/Foundation/Bits
CPPFLAGS+=-I$(TOPDIR)/Foundation/Packets
CPPFLAGS+=-I$(TOPDIR)/Generated/PacketsWithoutNITER
CPPFLAGS+=-I$(TOPDIR)/Generated/PacketsWithNITER
CPPFLAGS+=-I$(TOPDIR)/Telegram

LDFLAGS += -L$(TOPDIR)/Foundation/Bits -lbits
LDFLAGS += -L$(TOPDIR)/Generated/PacketsWithoutNITER -lgenerated_packetswithoutniter
LDFLAGS += -L$(TOPDIR)/Generated/PacketsWithNITER -lgenerated_packetswithniter

SRC := PacketSequence.c\
       EurobaliseTelegram.c

TESTS := AdhesionFactor_Tests.o\
         ErrorReporting_Tests.o\
         Level23TransitionInformation_Tests.o\
         TemporarySpeedRestriction_Tests.o\
         EndOfInformation_Tests.o\

OBJ := $(SRC:.c=.o) $(TESTS:.c=.o)

test_packets: test_packets.o $(OBJ)
	$(CC) -o $@ $+ $(LDFLAGS)

test_issue31_1: test_issue31_1.o $(OBJ)
	$(CC) -o $@ $+ $(LDFLAGS)

test_issue31_2: test_issue31_2.o $(OBJ)
	$(CC) -o $@ $+ $(LDFLAGS)

TrackToTrain_telegram_test: TrackToTrain_telegram_test.o $(OBJ)
	$(CC) -o $@ $+ $(LDFLAGS)

clean::
	$(RM) test_packets
	$(RM) test_issue31_1
	$(RM) test_issue31_2
	$(RM) TrackToTrain_telegram_test
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

