#include "interruptions.h"

struct cb *rx_cb;
struct cb *tx_cb;

void initCircularBuffers(void) {
    cb_init(rx_cb);
    cb_init(tx_cb);
}

// Given an interruption, interprets it and handles accordingly. 
void receiveInterruption(void *cookie) {
    if(UART0 + UART_MIS & UART_MIS_RTMIS) { // Receive timeout masked interrupt status.
        timeoutInterruption(cookie);
    } else if (UART0 + UART_MIS & UART_MIS_RXMIS) { // Receive masked interrupt status.
        rxInterruption(cookie);
    } else if (UART0 + UART_MIS & UART_MIS_TXMIS) { // Receive masked interrupt status.
        txInterruption(cookie);
    }
   
    // Clears the interruptions
    unsigned short* uart_ICR = (unsigned short*) (UART0+UART_ICR);
    *uart_ICR |= UART_ICR_RTIC | UART_ICR_TXIC | UART_ICR_RXIC;
}

void timeoutInterruption(void* cookie) {
    // handler_uart_tx(cookie);
    unsigned char c;
    unsigned short* uart_fr = (unsigned short*) (UART0+UART_FR);
    while(!(*uart_fr & UART_TXFF) && !cb_empty(tx_cb)){ // While queue is not empty, we get its data and send it to uart. 
        cb_get(tx_cb, &c);
        uart_send(UART0, c);
    }
}

void rxInterruption(void* cookie) {
    // I didn't manage to make this interruption work. 
}

void txInterruption(void* cookie) {
    // I didn't manage to make this interruption work. 
}

