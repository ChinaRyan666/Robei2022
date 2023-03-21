/* See LICENSE of license details. */

#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

#include "platform.h"
#include "stub.h"
#include "weak_under_alias.h"
extern void uart1_putchar(uint8_t data);
extern void uart0_putchar(uint8_t data);
uint8_t g_u8printsel=0;
ssize_t __wrap_write(int fd, const void* ptr, size_t len)
{


  const uint8_t * current = (const uint8_t *)ptr;
 


  if (isatty(fd)) {
#if 0
    while (!(UART0_REG(UART_REG_SR) & UART_FLAG_TC)) ;
    for (size_t jj = 0; jj < len; jj++) 
	{
		UART0_REG(UART_REG_TXFIFO) = current[jj];
		if (current[jj] == '\n') 
		{
			while (!(UART0_REG(UART_REG_SR) & UART_FLAG_TC)) ;
			UART0_REG(UART_REG_TXFIFO) = '\r';
		}
		while (!(UART0_REG(UART_REG_SR) & UART_FLAG_TC)) ;
#else
    for (size_t jj = 0; jj < len; jj++) 
	{
        if(g_u8printsel==1)
            uart1_putchar(current[jj]);
        else
            uart0_putchar(current[jj]);
#endif
    }
    return len;
  }

  return _stub(EBADF);
}
weak_under_alias(write);
