#!/bin/sh

export PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/home/guolicun/work/moorebot/allwinner_develop/tina/staging_dir/toolchain-arm_cortex-a7+neon_gcc-4.8-linaro_uClibc-0.9.33.2_eabi/bin

export STAGING_DIR=/home/guolicun/work/moorebot/allwinner_develop/tina/staging_dir/target-arm_cortex-a7+neon_uClibc-0.9.33.2_eabi/usr

arm-openwrt-linux-gcc src/*.c -o build/test -I$STAGING_DIR/include -I$STAGING_DIR/include/glib-2.0  -I./include -L$STAGING_DIR/lib -lglib-2.0 -lfuse -lsqlite3 -lrt -pthread -D_FILE_OFFSET_BITS=64 -Wall

