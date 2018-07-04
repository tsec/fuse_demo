MAKEROOT := $(shell pwd)

SRC_DIR=./src
SRC=$(wildcard ${SRC_DIR}/*.c)

OBJS=$(patsubst %.c, %.o, $(SRC))

TARGET_CFLAGS+= -D_GNU_SOURCE -I./include -I$(STAGING_DIR)/usr/include/glib-2.0/ -D_FILE_OFFSET_BITS=64 -fPIC

TARGET_LDFLAGS+=-lglib-2.0 -lfuse -lsqlite3 -lrt -pthread -luuid

TARGET=libg.so


$(TARGET): $(OBJS)
	$(CC) -fPIC -shared -Wall -O2 $(OBJS) -o ./build/$(TARGET) $(TARGET_LDFLAGS)
$(OBJS):%.o:%.c
	$(CC) -O2 -Wall -c $< -o $@ $(TARGET_CFLAGS)
clean:
	rm -fv $(OBJS)
	rm -fv $(TARGET)
