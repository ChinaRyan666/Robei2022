/* See LICENSE of license details. */

#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

#include "platform.h"
#include "stub.h"
#include "weak_under_alias.h"
extern void uart0_putchar(uint8_t data);
int __wrap_puts(const char *s)
{
  while (*s != '\0') {
  	#if 0
    while (UART0_REG(UART_REG_TXFIFO) & 0x80000000) ;
    UART0_REG(UART_REG_TXFIFO) = *s;
#else
	uart0_putchar(*s);
#endif
    if (*s == '\n') {
	#if 0
      while (UART0_REG(UART_REG_TXFIFO) & 0x80000000) ;
      UART0_REG(UART_REG_TXFIFO) = '\r';
	#else
		uart0_putchar('\r');
	#endif
    }

    ++s;
  }

  return 0;
}
weak_under_alias(puts);
