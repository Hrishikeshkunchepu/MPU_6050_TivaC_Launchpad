#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define ESC  0x1B
#define SP   0x20
#define DEL  0x7F

//------------Output_Init------------
// Initialize the UART for 115,200 baud rate (assuming 16 MHz bus clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void Output_Init(void);


