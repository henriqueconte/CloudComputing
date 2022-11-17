#include "main.h"
#include "parse_string.h"

#define ROWS 25
#define COLS 80
#define COM_SIZE 100
#define HISTORY_SIZE 20
#define ARROW_UP 1
#define ARROW_DOWN 0

/**
 * This is the C entry point, upcalled once the hardware has been setup properly
 * in assembly language, see the reset.s file.
 */

void clearScreen(void);
void saveCommand(char *command);
void clearLine(void);
void getPreviousCommand(int arrowDirection);
void getCommand(char *line);

int var1 = 0;
int var2 = 0;
int var3 = 4;
struct cb *rx_cb;

// Echo command
char exctractedCommand[COM_SIZE];
char commandArguments[COM_SIZE];

// Command history variables
char commandHistory[HISTORY_SIZE][COM_SIZE];
int historyCount = 0;
int historySearchCount = 0;
int was27Pressed = 0;
int was91Pressed = 0;
int isSpecialChar = 0;

void clearScreen(void) {
    kprintf("%c%c%c%c", 0x1B, 0x5B, 0x32, 0x4A);
    for (int i = 0; i < ROWS; i++) {
        uart_send(UART0, 27);
        uart_send(UART0, 91);
        uart_send(UART0, 65);
    }
}

// After reading a line from the command line, we will save it in a history with the 20 last executed commands. 
void saveCommand(char *command) {
    int i=0;
    while(i < COM_SIZE && command[i] != '\0') {
        commandHistory[historyCount][i] = command[i];
        // command[i] = '\0';
        i++;
    }
    historyCount = (historyCount + 1) % 20;
    historySearchCount = historyCount;
}

// https://www.reddit.com/r/C_Programming/comments/502xun/how_do_i_clear_a_line_on_console_in_c/
void clearLine(void) {
  kprintf("\x1b[2K");
  for (int i = 0; i < COM_SIZE; i++) {
      kputchar('\b');
      kputchar(' ');
      kputchar('\b');
  }
}

void getPreviousCommand(int arrowDirection) {
    if (arrowDirection == ARROW_UP) {
      clearLine();
      if (historySearchCount > 0) {
        historySearchCount--;
        kprintf("%s", commandHistory[historySearchCount]);
      }
    }
    else if (arrowDirection == ARROW_DOWN) {
      clearLine();
      if (historySearchCount + 1 < historyCount) {
        historySearchCount++;
        kprintf("%s", commandHistory[historySearchCount]);
      }
    }
}

void getCommand(char *line) {
    int i=0;

    // Cleans extracted command and its arguments.
    for (i = 0; i < COM_SIZE; i++) {
      exctractedCommand[i] = '\0';
      commandArguments[i] = '\0';
    }

    i = 0;

    // While we still have characters and there are no spaces, we save the command. Example: echo food. It will save echo. 
    while(line[i] != '\0' && line[i] != ' ') {
        exctractedCommand[i] = line[i];
        i++;
    }
    exctractedCommand[i] = '\0';

    int commandIndex = 0;
    i++;

    // Saves the arguments from the command. Example: echo food. It will save food. 
    while(line[i] != '\0' && i < COM_SIZE) {
      commandArguments[commandIndex] = line[i];
      i++;
      commandIndex++;
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

    // wfi();

    if (c == '\r')
      uart_send(UART0, '\n');

    // kprintf("%d", c);
    // If user hits enter
    if (c == 13) {

      saveCommand(command);
      getCommand(command);

      
      // If command is reset, cleans screen
      if (compareStrings(command, "reset") == 1) {
        clearScreen();
      } else if (compareStrings(exctractedCommand, "echo") == 1) { // If command is echo, prints echo
        kprintf("%s", commandArguments);
        kprintf("\n\r");
      }

      // Cleans command
      for (int i = 0; i < commandCount; i++) {
        command[i] = '\0';
      }
      commandCount = 0;

    } else if (c == 127) { // If user hits delete
      kputchar('\b');
      kputchar(' ');
      kputchar('\b');
    } else if (c == 27) { // The up arrow is a sequence of characters 27-91-65. Therefore we need a FSM to identify it.
      was27Pressed = 1;
      command[commandCount] = c;
      commandCount += 1;
    } else if (c == 91) { // The next state to detect the up arrow is 91.
      was91Pressed = 1;
      command[commandCount] = c;
      commandCount += 1;
    } else if (c == 65) { // Up arrow
      if (was27Pressed == 1 && was91Pressed == 1) { // If 27 and 91 were detected before a 65, then we have a up arrow key.
        isSpecialChar = 1;
        getPreviousCommand(ARROW_UP);
      } else {
        command[commandCount] = c;
        commandCount += 1;
      }
    } else if (c == 66) { // Down arrow
      if (was27Pressed == 1 && was91Pressed == 1) {
        isSpecialChar = 1;
        getPreviousCommand(ARROW_DOWN);
      } else {
        command[commandCount] = c;
        commandCount += 1;
      }
    } else {
      was27Pressed = 0;
      was91Pressed = 0;
      isSpecialChar = 0;
      command[commandCount] = c;
      commandCount += 1;
    }

    if (isSpecialChar == 0) {
      kprintf("%c", c);
    }
    uart_send(UART1, c);
  }
}
