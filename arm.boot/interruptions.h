#ifndef INTERRUPTIONS_H_
#include "uart.h"
#include "uart-irqs.h"
#include "main.h"
#include "cb.h"

void receiveInterruption(void *cookie);
void initCircularBuffers(void);
void put_char(unsigned char s);

#endif /* INTERRUPTIONS_H_ */