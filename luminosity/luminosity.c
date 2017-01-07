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
#include <channels.h>

#define TOLERANCE_MARGIN 10 // Représente +/- 0,24%
#define MAX_CPT 300
#define DELAY 1000000

static char init_luminosity() {
  /* La LED RGB et le capteur de lumière sont déjà initialisés dans les apps "light" et "light_sensor". */
  return 1;
}

static char set_luminosity(struct args_t *args) {
  if (args) {
    uint8_t r, g, b;
    uint8_t moyenne;
    int luminosity, luminosity_current;
    int difference;
    unsigned int cpt = 0;

    luminosity = (int) args->l;
    if (luminosity < 0 || luminosity > 4095) {
      out_str("NOT OK");

      return 1;
    }

    getColorRGB(0, &r, &g, &b);
    moyenne = (r + g + b) / 3;
    setColorRGB(0, moyenne, moyenne, moyenne);

    while (1) {
      if (cpt >= MAX_CPT) {
        server_push(&alertLight);
        return 1;
      }
      cpt++;

      luminosity_current = LM358_read_light();
      difference = luminosity_current - luminosity;

      if (difference > -TOLERANCE_MARGIN && difference < TOLERANCE_MARGIN)
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
      RFLPC_DELAY(DELAY);
    }

    out_str("OK");
    server_push(&alertLight);
  } else {
    out_str("NOT OK");
  }

  return 1;
}
