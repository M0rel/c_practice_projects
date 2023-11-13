CC = gcc
CCFLAGS = -Wall -Wpedantic
LDFLAGS =

TARGET = template

SRCS = source_file.c
INCV_PATH = ../third-party
BUILD_DIR = build

.PHONY: build_dir all

all: build_dir program

program:
	$(CC) $(SRCS) $(CCFLAGS) -I$(INCV_PATH) $(LDFLAGS) -o $(BUILD_DIR)/$(TARGET)

build_dir: ${BUILD_DIR}

${BUILD_DIR}:
	mkdir ${BUILD_DIR}

clean:
	rm -rf $(BUILD_DIR)
