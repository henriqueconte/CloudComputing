#include "main.h"
#include "parse_string.h"

#define ROWS 25
#define COLS 80
#define COM_SIZE 100

/**
 * This is the C entry point, upcalled once the hardware has been setup properly
 * in assembly language, see the reset.s file.
 */

void clearScreen(void);

int var1 = 0;
int var2 = 0;
int var3 = 4;

void clearScreen(void) {
    kprintf("%c%c%c%c", 0x1B, 0x5B, 0x32, 0x4A);
    for (int i = 0; i < ROWS; i++) {
        uart_send(UART0, 27);
        uart_send(UART0, 91);
        uart_send(UART0, 65);
    }
}
 
void _start() {
  int i = 0;
  int count = 0;

  char command[100];
  int commandCount = 0;

  for (int i = 0; i < 100; i++) {
    command[i] = '\0';
  }

  uart_send_string(UART0, "\nQuit with \"C-a c\" and then type in \"quit\".\n");
  uart_send_string(UART0, "\nHello world!\n");

  clearScreen();

  while (1) {
    unsigned char c;
    while (0 == uart_receive(UART0, &c)) {
      // friendly reminder that you are polling and therefore spinning...
      // not good for the planet! But until we introduce interrupts,
      // there is nothing you can do about it... except comment out
      // this annoying code ;-)
      count++;
      if (count > 10000000) {
        // uart_send_string(UART1, "\n\rZzzz....\n\r");
        count = 0;
      }
    }

    wfi();

    if (c == '\r')
      uart_send(UART0, '\n');

    // If user hits enter
    if (c == 13) {

      // If command is reset, cleans screen
      if (compareStrings(command, "reset") == 1) {
        clearScreen();
      } else if (compareStrings(command, "echo") == 1) { // If command is echo, prints echo
        kprintf("%s", command);
      }

      // Cleans command
      for (int i = 0; i < commandCount; i++) {
        command[i] = '\0';
      }
      commandCount = 0;

    } else {
      command[commandCount] = c;
      commandCount += 1;
    }

    kprintf("%c", c);
    uart_send(UART1, c);
  }
}
