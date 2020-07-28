CFLAGS = -std=c99 -D_DEFAULT_SOURCE


INCLUDE_PATHS += -I/opt/vc/include
INCLUDE_PATHS += -I/opt/vc/include/interface/vmcs_host/linux
INCLUDE_PATHS += -I/opt/vc/include/interface/vcos/pthreads

LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lmysqlclient

%: %.c
	gcc -o stat_screen stat_screen.c $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS)

clean:
	rm stat_screen
