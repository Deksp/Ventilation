#include "Ventilation.h"

int main() 
{
    cli();
    millis_timer = 0;
    timer0_initialization();
    timer1_initialization();
    sei();

    Privod privod;

    while (true) 	
    {
		//blabla();
        privod.tick();
        privod.buttons();
        if (privod.triger()) privod.opcl(OPEN);
        else privod.opcl(CLOSE);
    }
    return 0;
}