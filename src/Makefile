#BOX_TYPE?=pc_x86_64
#BOX_TYPE?=hisi_v100
BOX_TYPE?=hisi_v300


ifeq ($(BOX_TYPE), pc_x86_64)
CC=gcc
STRIP=strip
CFLAGS = -Wall -O2
INC_PATH = -I../inc -I../inc/audio -I../inc/common -I../inc/udp_server -I../inc/upload_pic
LIBS :=  -L../lib/X86_64 \
			-lxml -levent -lavformat \
			-lavcodec -lavfilter -lswscale -lavutil -lswresample -lm -ldl -lpthread -lrt

APPBIN = elevator_mainX86_64
DEST_BIN = /mnt/hgfs/nfs_dir/share_dir/hb/elevator/bin
endif


ifeq ($(BOX_TYPE), hisi_v100)
CC=arm-hisiv100nptl-linux-gcc
STRIP=arm-hisiv100nptl-linux-strip
CFLAGS = -Wall -O2
INC_PATH = -I../inc -I../inc/audio -I../inc/common -I../inc/udp_server -I../inc/upload_pic
LIBS :=  -L../lib/hisiv100 \
			-lxml -levent -lavformat \
			-lavcodec -lavfilter -lswscale -lavutil -lswresample -lm -ldl -lpthread -lrt

APPBIN = elevator_main100
DEST_BIN = /mnt/hgfs/nfs_dir/share_dir/hb/elevator/bin
endif

ifeq ($(BOX_TYPE), hisi_v300)
CC=arm-hisiv300-linux-gcc
STRIP=arm-hisiv300-linux-strip
CFLAGS = -Wall -O2
INC_PATH = -I../inc -I../inc/audio -I../inc/common -I../inc/udp_server -I../inc/upload_pic
LIBS :=  -L../lib/hisiv300 \
			-lxml -levent -lavformat \
			-lavcodec -lavfilter -lswscale -lavutil -lswresample -lm -ldl -lsysapi -lpthread -lrt

DEST_BIN_LOCAL = ../bin
DEST_BIN = /mnt/hgfs/ShareDir/share/work/elevator/bin
APPBIN = elevator_main300
endif


SRCS = $(wildcard ./common/*.c *.c ./sensor/*.c ./udp_server/*.c ./audio/*.c ./uart/*.c)
OBJS = $(patsubst %.c,%.o,$(notdir ${SRCS})) 


all:
	$(CC) $(SRCS) $(INC_PATH) $(LIBS) $(CFLAGS) -o $(APPBIN)
	$(STRIP) $(APPBIN)
	cp $(APPBIN) $(DEST_BIN)/$(APPBIN)
	mv $(APPBIN) $(DEST_BIN_LOCAL)/$(APPBIN)
clean:
	rm -rf $(OBJS) $(DEST_BIN_LOCAL)/$(APPBIN)
