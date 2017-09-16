/*
 * SPI testing utility (using spidev driver)
 *
 * Copyright (c) 2007  MontaVista Software, Inc.
 * Copyright (c) 2007  Anton Vorontsov <avorontsov@ru.mvista.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * Cross-compile with cross-gcc -I/path/to/cross-kernel/include
 */

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <spi.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

/* Configuration parameters of SPI1 */
static const char *device = "/dev/spidev1.0";
struct spi_prms spi1;

static void print_usage(const char *prog)
{
	printf("Usage: %s [-DsbdlHOLC3]\n", prog);
	puts("  -D --device   device to use (default /dev/spidev1.1)\n"
	     "  -s --speed    max speed (Hz)\n"
	     "  -d --delay    delay (usec)\n"
	     "  -b --bpw      bits per word \n"
	     "  -l --loop     loopback\n"
	     "  -H --cpha     clock phase\n"
	     "  -O --cpol     clock polarity\n"
	     "  -L --lsb      least significant bit first\n"
	     "  -C --cs-high  chip select active high\n"
	     "  -3 --3wire    SI/SO signals shared\n");
	exit(1);
}

static void parse_opts(int argc, char *argv[])
{
	while (1) {
		static const struct option lopts[] = {
			{ "device",  1, 0, 'D' },
			{ "speed",   1, 0, 's' },
			{ "delay",   1, 0, 'd' },
			{ "bpw",     1, 0, 'b' },
			{ "loop",    0, 0, 'l' },
			{ "cpha",    0, 0, 'H' },
			{ "cpol",    0, 0, 'O' },
			{ "lsb",     0, 0, 'L' },
			{ "cs-high", 0, 0, 'C' },
			{ "3wire",   0, 0, '3' },
			{ "no-cs",   0, 0, 'N' },
			{ "ready",   0, 0, 'R' },
			{ NULL, 0, 0, 0 },
		};
		int c;

		c = getopt_long(argc, argv, "D:s:d:b:lHOLC3NR", lopts, NULL);

		printf("getopt_long: %d\n", c);
		printf("Delay: %d\n", lopts[2]);printf("Reday: %d\n", lopts[11]);printf("CPHA: %d\n", lopts[5]);

		if (c == -1)
			break;

		switch (c) {
		case 'D':
			device = optarg;
			break;
		case 's':
			spi1.speed = atoi(optarg);
			break;
		case 'd':
			spi1.delay = atoi(optarg);
			break;
		case 'b':
			spi1.bits = atoi(optarg);
			break;
		case 'l':
			spi1.mode |= SPI_LOOP;
			break;
		case 'H':
			spi1.mode |= SPI_CPHA;
			break;
		case 'O':
			spi1.mode |= SPI_CPOL;
			break;
		case 'L':
			spi1.mode |= SPI_LSB_FIRST;
			break;
		case 'C':
			spi1.mode |= SPI_CS_HIGH;
			break;
		case '3':
			spi1.mode |= SPI_3WIRE;
			break;
		case 'N':
			spi1.mode |= SPI_NO_CS;
			break;
		case 'R':
			spi1.mode |= SPI_READY;
			break;
		default:
			print_usage(argv[0]);
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	int ret = 0;
	int fd;
    uint8_t tx[10] = {0};
    uint8_t rx[10] = {0};

//	parse_opts(argc, argv);

    spi1.mode = 3;
    spi1.bits = 8;
    spi1.speed = 500000;
  
	fd = spi_fd_open(device);
	if (fd < 0)
    {    
        printf("can't open spi1 device \n");
	    pabort("can't open device");
    }else
    {
        ret = spi_init(fd, &spi1);
        if (ret != -1)
        {
            printf("SPI1 init done succesfully \n");
	        printf("spi mode: %d\n", spi1.mode);
	        printf("bits per word: %d\n", spi1.bits);
	        printf("max speed: %d Hz (%d KHz)\n", spi1.speed, spi1.speed/1000);

            tx[0]=0x00;
	        while(1)
    	    {
	    	    spi_transfer(fd, &spi1, tx, rx, 4);
		        sleep(2);
	        }
        }
	}
    spi_fd_close(fd);

	return ret;
}

