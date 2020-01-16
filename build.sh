set -e    # if error, stop the build
cc -g -std=c99 -c -I /opt/raylib/src stat_screen.c -o ./obj/stat_screen.o
cc -o stat_screen  obj/stat_screen.o -s -Wall -std=c99 -I/opt/raylib/src -L/opt/raylib/release/libs/linux -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./stat_screen
