CC=gcc
CFLAGS=`pkg-config --cflags libdpdk`
LDFLAGS=`pkg-config --libs libdpdk`

all:
	$(CC) main.c flow_hash.c l4_lb.c metrics.c numa.c \
	-o dpdk_app $(CFLAGS) $(LDFLAGS)
