/*
<generator>
  <handlers init="init_luminosity" doGet="set_luminosity"/>
	<properties persistence="volatile" />
	<args>
	  <arg name="l" type="uint16" />
	</args>
</generator>
 */

#include "../lib/P9813.h"
#include "../lib/LM358.h"
#include <stdint.h>
#include "channels.h"

static char init_luminosity() {
  /* La LED RGB et le capteur de lumière sont déjà initialisés dans les apps "light" et "light_sensor". */
  return 1;
}

static char set_luminosity(struct args_t *args) {
  if (args) {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t moyenne;
    int luminosity, luminosity_current;
    int difference;

    luminosity = (int) args->l;
    if (luminosity < 0 || luminosity > 4095) {
      out_str("NOT OK");

      return 1;
    }

    getColorRGB(0, &r, &g, &b);
    moyenne = (r + g + b) / 3;
    setColorRGB(0, moyenne, moyenne, moyenne);

    while (1) {
      luminosity_current = LM358_read_light();
      difference = luminosity_current - luminosity;

      if (difference > -10 && difference < 10)
        break;

      if (luminosity > luminosity_current) {
        if (moyenne == 255)
          break;
        moyenne++;
      } else {
        if (moyenne == 0)
          break;
        moyenne--;
      }
      setColorRGB(0, moyenne, moyenne, moyenne);
      /* Pour laisser le temps au capteur de lumière
      de détecter la variation */
      RFLPC_DELAY(1000000);
    }

    out_str("OK");
  } else {
    out_str("NOT OK");
  }

  server_push(&alertLight);
  return 1;
}
