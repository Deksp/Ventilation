#ifndef VENYILATION_H
#define VENTILATION_H

#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#define abs(x) ((x)>0? (x):-(x))

#define SMOOTH_PRD 200
#define DUTY_INTERVAL 20
#define SPEED 254
#define INVERT false
#define OPEN 0x01
#define CLOSE 0x00

#define enable
#undef enable

/*
PD2 ���� ������������ �������
PD3 ���� button_open
PD4 ���� button_close
PD6 ����� ���
PD7 ����� �����������
PB0 ����� enable (��� �������������)
*/

uint32_t tmr_millis();
void timer0_initialization(void);
void timer1_initialization(void);

extern volatile uint32_t millis_timer;

class Privod;

class Privod
{
public:
    Privod();
    void setDirection(bool);
    void setSpeed(uint8_t);
    void tick();
    bool triger();
    void buttons();
    void opcl(bool);
private:
	int bood;
    uint8_t speed;
    uint8_t duty;
    bool direction;
    bool button_open;
    bool button_close;
    enum {
        disable,
        move
    }state;
};
void blabla();
#endif
