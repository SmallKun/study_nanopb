
NANOPB_DIR=../../core

PROTOC = protoc
ifdef WINDOWS
	PROTOC_OPTS = --plugin=protoc-gen-nanopb=$(NANOPB_DIR)/generator/protoc-gen-nanopb.bat
else
	PROTOC_OPTS = --plugin=protoc-gen-nanopb=$(NANOPB_DIR)/generator/protoc-gen-nanopb
endif

# Compiler flags to enable all warnings & debug info
CFLAGS = -Wall -Werror -g -O0
CFLAGS += -I$(NANOPB_DIR)

# C source code files that are required
ENCODER  = encoder.c
DECODER  = decoder.c

SRC_ENCODER  = $(ENCODER)                 # The main program
SRC_ENCODER += simple.pb.c                # The compiled protocol definition
SRC_ENCODER += $(NANOPB_DIR)/pb_encode.c  # The nanopb encoder
SRC_ENCODER += $(NANOPB_DIR)/pb_decode.c  # The nanopb decoder
SRC_ENCODER += $(NANOPB_DIR)/pb_common.c  # The nanopb common parts

SRC_DECODER  = $(DECODER)                 # The main program
SRC_DECODER += simple.pb.c                # The compiled protocol definition
SRC_DECODER += $(NANOPB_DIR)/pb_encode.c  # The nanopb encoder
SRC_DECODER += $(NANOPB_DIR)/pb_decode.c  # The nanopb decoder
SRC_DECODER += $(NANOPB_DIR)/pb_common.c  # The nanopb common parts

# Build rule for the protocol
gen: simple.proto
	$(PROTOC) $(PROTOC_OPTS) --nanopb_out=. simple.proto

# Build rule for the main program
encoder: $(SRC_ENCODER)
	$(CC) $(CFLAGS) -o encoder.out $(SRC_ENCODER)
decoder: $(SRC_DECODER)
	$(CC) $(CFLAGS) -o decoder.out $(SRC_DECODER)

clean:
	rm -r encoder.out.dSYM
	rm -r decoder.out.dSYM
	rm -r simple.pb.h
	rm -r simple.pb.c
	rm encoder.out
	rm decoder.out
	rm data.bin

