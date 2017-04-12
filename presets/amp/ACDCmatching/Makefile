
NANOPB_DIR=../../../core
ifdef WINDOWS
	PROTOC_OPTS = --plugin=protoc-gen-nanopb=$(NANOPB_DIR)/generator/protoc-gen-nanopb.bat
else
	PROTOC_OPTS = --plugin=protoc-gen-nanopb=$(NANOPB_DIR)/generator/protoc-gen-nanopb
endif

SRC_DIR="$(PWD)"
DST_DIR="$(PWD)"

OUT=preset.out

# CFLAGS = -Wall -Werror -DPB_FIELD_16BIT -g -O0 # PB_FIELD_16BIT : see https://jpa.kapsi.fi/nanopb/docs/reference.html#compilation-options
CFLAGS = -Wall -Werror -DPB_FIELD_32BIT -g -O0 # PB_FIELD_32BIT : see https://jpa.kapsi.fi/nanopb/docs/reference.html#compilation-options
CFLAGS += -I$(NANOPB_DIR)

# C source code files that are required
CSRC  = preset.c                   # The main program
CSRC += callbacks.c                # The main program
CSRC += preset.pb.c                # The compiled protocol definition
CSRC += $(NANOPB_DIR)/pb_encode.c  # The nanopb encoder
CSRC += $(NANOPB_DIR)/pb_decode.c  # The nanopb decoder
CSRC += $(NANOPB_DIR)/pb_common.c  # The nanopb common parts

gen: preset.proto
	protoc -I=$(SRC_DIR) $(PROTOC_OPTS) --nanopb_out=$(DST_DIR) $(SRC_DIR)/preset.proto

exe: $(CSRC)
	$(CC) $(CFLAGS) -o $(OUT) $(CSRC)

clean:
	rm -r preset.pb.* $(OUT) $(OUT).*


