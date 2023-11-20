#include "system_time.h"

void init_system_tick()
{
	// Since we use no Output compare channel
	// and we use the Timer in Normal Mode, we just set it to zero
	TCCR1A = 0;

	// Setup prescaler
	TCCR1B = TIMER1_PRESCALER_REGVAL;

	TCNT1 = 0;
}

tTime timer1_get_time()
{
	return TCNT1;
}

void delay_ms(tTime ms)
{
	tTime now = timer1_get_time();
	tTime wait_time = (ms * TIMER1_MILLISECOND);

	while((time_passed(now) < wait_time))
	{
		// do nothing
	}
}

void delay_us(tTime us)
{
	tTime now = timer1_get_time();
	tTime wait_time = (us * TIMER1_MICROSECOND);

	while((time_passed(now) < wait_time))
	{
		// do nothing
	}
}

tTime time_passed(tTime since)
{
	tTime now = timer1_get_time();
	
	if(now >= since)
	{
		return (now - since);
	}
	else
	{
		// rollover has occured
		return (now + (1 + MAX_TIME - since));
	}
}