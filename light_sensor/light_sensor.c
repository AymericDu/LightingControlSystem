/*
<generator>
  <handlers init="init_light_sensor" doGet="get_luminosity"/>
  <properties persistence="volatile"/>
</generator>
 */

#include "../lib/TM1637.h"
#include "../lib/LM358.h"
#include "../lib/connectors.h"
#include <stdint.h>


static void luminosity_on_4digit() {
  int luminosity;
  uint8_t raw[4];
  int i;

  luminosity = LM358_read_light();
  for (i = 3; i >= 0; i--) {
    raw[i] = luminosity % 10;
    luminosity /= 10;
  }
  TM1637_output(1, 0, raw);
}

static char init_light_sensor() {
  LM358_init(BASE_SHIELD_A0);
  TM1637_init(BASE_SHIELD_D3);
  set_timer(&luminosity_on_4digit, 200);
  return 1;
}

static char get_luminosity(struct args_t *args) {
  out_uint(LM358_read_light());
  return 1;
}
