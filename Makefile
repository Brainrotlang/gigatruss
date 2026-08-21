BRAINROT_DIR ?= brainrot
CC ?= gcc
BUILD_DIR ?= build
NATIVE_LIB := $(BUILD_DIR)/libgigatruss_stdrot.so

STDROT_SRCS := $(wildcard $(BRAINROT_DIR)/stdrot/*.c) $(BRAINROT_DIR)/lib/input.c
GIGATRUSS_NATIVE_SRCS := native/gigamath.c

.PHONY: native clean

native: $(NATIVE_LIB)

$(NATIVE_LIB): $(STDROT_SRCS) $(GIGATRUSS_NATIVE_SRCS)
	@mkdir -p $(BUILD_DIR)
	$(CC) -fPIC -shared \
		-I$(BRAINROT_DIR) -I$(BRAINROT_DIR)/stdrot \
		-o $@ $(STDROT_SRCS) $(GIGATRUSS_NATIVE_SRCS) -lm

clean:
	rm -rf $(BUILD_DIR)
