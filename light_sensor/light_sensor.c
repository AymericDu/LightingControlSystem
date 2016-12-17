/*
<generator>
  <handlers init="init_light_sensor" doGet="get_luminosity"/>
	<properties persistence="volatile" />
</generator>
 */

#include "../lib/TM1637.h"
#include "../lib/LM358.h"
#include "../lib/connectors.h"
#include <stdint.h>

#define TIMER_4DIGIT RFLPC_TIMER3

RFLPC_IRQ_HANDLER luminosity_on_4digit() {
  if (rflpc_timer_test_irq(TIMER_4DIGIT, RFLPC_TIMER_MATCH0)) {
    int luminosity;
    uint8_t raw[4];
    int i;

    rflpc_timer_reset_irq(TIMER_4DIGIT, RFLPC_TIMER_MATCH0);

    luminosity = LM358_read_light();
    for (i = 3; i >= 0; i--) {
      raw[i] = luminosity % 10;
      luminosity /= 10;
    }
    TM1637_output(1, 0, raw);
  }
}

static char init_light_sensor() {
  LM358_init(BASE_SHIELD_A0);
  TM1637_init(BASE_SHIELD_D3);

  rflpc_timer_enable(TIMER_4DIGIT);
  rflpc_timer_set_clock(TIMER_4DIGIT, RFLPC_CCLK);
  rflpc_timer_set_pre_scale_register(TIMER_4DIGIT, rflpc_clock_get_system_clock());
  rflpc_timer_set_counter(TIMER_4DIGIT, 0);
  rflpc_timer_set_callback(TIMER_4DIGIT, luminosity_on_4digit);
  rflpc_timer_set_match_value(TIMER_4DIGIT, RFLPC_TIMER_MATCH0, 4);
  rflpc_timer_set_irq_on_match(TIMER_4DIGIT, RFLPC_TIMER_MATCH0, RFLPC_TIMER_IRQ_ON_MATCH | RFLPC_TIMER_RESET_ON_MATCH);
  rflpc_timer_start(TIMER_4DIGIT);

  return 1;
}

static char get_luminosity(struct args_t *args) {
  out_uint(LM358_read_light());

  return 1;
}
