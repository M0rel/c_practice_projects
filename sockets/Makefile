CC = gcc
CCFLAGS = -Wall
LDFLAGS =

INCV_PATH = ../third-party
BUILD_DIR = build

CLIENT_SRCS = client.c
CLIENT_TARGET = client

SERVER_SRCS = server.c
SERVER_TARGET = server

.PHONY: build_dir all

all: build_dir client server

client:
	$(CC) $(CLIENT_SRCS) $(CCFLAGS) -I$(INCV_PATH) $(LDFLAGS) -o 		\
		$(BUILD_DIR)/$(CLIENT_TARGET)
server:
	$(CC) $(SERVER_SRCS) $(CCFLAGS) -I$(INCV_PATH) $(LDFLAGS) -o 		\
		$(BUILD_DIR)/$(SERVER_TARGET)

build_dir: ${BUILD_DIR}

${BUILD_DIR}:
	mkdir ${BUILD_DIR}

clean:
	rm -rf $(BUILD_DIR)
