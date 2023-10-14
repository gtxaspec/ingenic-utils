#===============================================================
#	 @Author: dyye
#	 @Created Time : Wed 10 Aug 2016 08:32:05 AM CST
#
#	 @File Name: Makefile
#	 @Description:
#
#================================================================

CC=/home/turismo/toolchain/mips-gcc472-glibc216-64bit-master/bin/mips-linux-uclibc-gnu-gcc
CCFLAGS += -pthread -Wall -muclibc -g -static
target = pwm_test
sources = $(wildcard *.c)
objects = $(patsubst %.c, %.o, $(sources))

$(target):$(objects)
	$(CC) $(CCFLAGS) -o $@ $^
	rm $(objects)
	echo "generate $@"

%.o:%.c
	$(CC) -Wall -muclibc -c -g -o $@ $<

.PHONY : clean
clean:
	rm -f $(target) *.o
