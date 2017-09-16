/*******************************************************************************
* FileName		: spi.h
* Description	: 
*******************************************************************************/

#include <spi.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>


void pabort(const char *s)
{
	perror(s);
	abort();
}

/** 
 * brief: open spi device and return the file descriptor
 * @Param: the spi number
 */  
int spi_fd_open(char *device)  
{  
    int fd;  
   
     
    fd = open(device, O_RDWR);

    if (fd < 0) {  
        perror("spi/fd_open");  
    }  
    return fd;  
}  
  
/** 
 * brief: close spi device 
 * @Param: fd: the file descriptor of spi
 */
int spi_fd_close(int fd)  
{  
    return close(fd);  
}  
  
/**
* bried: initialize the spi
* @Param: spi number, spi_prms structure
*/
int spi_init(int fd, struct spi_prms *spi)
{

    int ret = 0;    
 
    printf("Rxd: Struct: Mode:%d Speed:%d Bits:%d \n", spi->mode, spi->speed, spi->bits);
    /* spi mode */
    ret = ioctl(fd, SPI_IOC_WR_MODE, &spi->mode);
    if (ret == -1)
    {
        pabort("can't set spi mode");
        return ret;
    }
    ret = ioctl(fd, SPI_IOC_RD_MODE, &spi->mode);
    if (ret == -1)
    {
        pabort("can't get spi mode");
        return ret;
    }

    /* bits per word */
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &spi->bits);
    if (ret == -1)
    {
        pabort("can't set bits per word");
        return ret;
    }
    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &spi->bits);
    if (ret == -1)
    {
        pabort("can't get bits per word");
        return ret;
    }

    /* max speed hz */
    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi->speed);
    if (ret == -1)
    {
        pabort("can't set max speed hz");
        return ret;
    }
    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &spi->speed);
    if (ret == -1)
    {
        pabort("can't get max speed hz");
        return ret;
    }

    return ret;
}


/** 
 * brief: transfer SPI data 
 * @Param: fd: the file descriptor of spi
 */

int spi_transfer(int fd, struct spi_prms *spi, uint8_t *txbuff, uint8_t *rxbuff, int length)
{
	int ret;
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)txbuff,
		.rx_buf = (unsigned long)rxbuff,
		.len = length,
		.delay_usecs = spi->delay,
		.speed_hz = spi->speed,
		.bits_per_word = spi->bits,
	};

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
	{
	    pabort("can't send spi message");
	    return ret;
	}

	/* Print the received buffer can remove after testing*/
	for (ret = 0; ret < length; ret++) 
	{
	    //if (!(ret % 6))
	    //	puts("");
	    printf("%.2X ", rxbuff[ret]);
	}
	puts("");
	
	return ret;
}

