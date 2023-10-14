# Specify the compiler
CC = mipsel-openipc-linux-musl-gcc
# Output binary name
TARGET = ingenic_spk_bitbang
# Compiler flags: static linking, Wall for all warnings
CFLAGS = -static -Wall

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	rm -f $(TARGET)
