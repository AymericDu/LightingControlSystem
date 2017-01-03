/*
<generator>
  <handlers init="init_light_sensor" doGet="get_luminosity"/>
  <properties persistence="volatile" interaction="stream" channel="alertLightSensor"/>
</generator>
 */

#include "../lib/TM1637.h"
#include "../lib/LM358.h"
#include "../lib/connectors.h"
#include "timers.h"
#include <stdint.h>
#include <channels.h>

static int luminosity;

/*
 * Retourne la valeur du capteur de lumière.
 */
static char get_luminosity(struct args_t *args) {
  out_uint(luminosity);
  return 1;
}

/*
 * Affiche la valeur du capteur de lumière sur le 4digit
 */
static void luminosity_on_4digit() {
  int luminositybis;
  uint8_t raw[4];
  int i;

  luminosity = LM358_read_light();
  server_push(&alertLightSensor); // on notifie le changement

  luminositybis = luminosity;
  for (i = 3; i >= 0; i--) {
    raw[i] = luminositybis % 10;
    luminositybis /= 10;
  }
  TM1637_output(1, 0, raw);
}

/*
 * Initialise le 4digit et le capteur de lumière
 */
static char init_light_sensor() {
  LM358_init(BASE_SHIELD_A0);
  TM1637_init(BASE_SHIELD_D3);
  set_timer(&luminosity_on_4digit, 1000);
  return 1;
}
