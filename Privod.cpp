#include "Ventilation.h"

/*
PD2 вход управл€ющего сигнала
PD3 вход button_open
PD4 вход button_close
PD6 выход Ў»ћ
PD7 выход направлени€
PB0 выход enable (при необходимости)
*/
Privod::Privod() 
{
#ifdef enable
    DDRB |= 1 << PB0;
    PORTB |= 1 << PB0;
#endif

    DDRD &= ~(1 << PD2) | ~(1 << PD3) | ~(1 << PD4);
    DDRD |= 1 << PD7;
    state = disable;
    direction = INVERT;
    speed = 0;
    duty = 0;
    buttons();
}

void Privod::buttons() 
{
    if (PIND & (1 << PD3)) button_open = true;
    if (!(PIND & (1 << PD3))) button_open = false;
    if (PIND & (1 << PD4)) button_close = true;
    if (!(PIND & (1 << PD4))) button_close = false;
}

bool Privod::triger() 
{
    if (PIND & (1 << PD2)) return true;
    return false;
}

void Privod::opcl(bool tooot) 
{
    if (tooot ? button_open : button_close) 
    {
        if (state == disable) return;
        setSpeed(0);
        state = disable;
        //move=!move;
        return;
    }
    if (!(tooot ? button_open : button_close) && state == disable) 
    {
        state = move;
        //move=!move;
        setDirection(tooot ? 1 : 0);
        setSpeed(SPEED);
    }
}

void Privod::setSpeed(uint8_t speed) 
{
    if (speed == 0) PORTD &= ~(1 << PD7);
    this->speed = speed;
}

void Privod::setDirection(bool direction) 
{
    this->direction = direction;
    if (direction) PORTD |= 1 << PD7;
    else PORTD &= ~(1 << PD7);
}

void Privod::tick() 
{
    static uint32_t tmr = 0;
    if (tmr_millis() - tmr >= SMOOTH_PRD && (speed || duty)) 
    {
        tmr = tmr_millis();
        if (abs(duty - speed) > DUTY_INTERVAL) 
            duty += (duty < speed) ? DUTY_INTERVAL : -DUTY_INTERVAL;
        else duty = speed;
        OCR0A = duty;
    }
}