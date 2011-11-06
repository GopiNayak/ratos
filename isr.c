#include "common.h"
#include "isr.h"
#include "screen.h"
#include "keyboard.h"

irq_handler irq_array[32];

void attachirqhandler(irq_handler fun, int irq_number)
{
	irq_array[irq_number] = fun;
}

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t *regs)
{
   if( irq_array[regs->int_no] )
   {
   	irq_handler fun = irq_array[regs->int_no];
	fun(regs);
	return;
   }
   puts("recieved interrupt: ");
   putint(regs->int_no);
   putch('\n');
   putint(0);
}

static void pittimer( registers_t *r)
{
  //      puts("in timer function\n");
        outb(0x20, 0x20);
}

//function body taken as it is from http://www.osdever.net/bkerndev/Docs/keyboard.htm

static void keyboardisr( registers_t *r)
{
    unsigned char scancode;

    /* Read from the keyboard's data buffer */
    scancode = inb(0x60);

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */
    }
    else
    {
        /* Here, a key was just pressed. Please note that if you
        *  hold a key down, you will get repeated key press
        *  interrupts. */

        /* Just to show you how this works, we simply translate
        *  the keyboard scancode into an ASCII value, and then
        *  display it to the screen. You can get creative and
        *  use some flags to see if a shift is pressed and use a
        *  different layout, or you can add another 128 entries
        *  to the above layout to correspond to 'shift' being
        *  held. If shift is held using the larger lookup table,
        *  you would add 128 to the scancode when you look for it */
        putch(kbdus[scancode]);
    }
    outb(0x20, 0x20);
}

void initializeisr()
{
        attachirqhandler(&pittimer, 32);
        attachirqhandler(&keyboardisr, 33);
}
 
