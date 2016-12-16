/*
<generator>
  <handlers init="init_led" doGet="manage_color"/>
	<properties persistence="volatile" />
	<args>
	  <arg name="r" type="uint8" />
    <arg name="g" type="uint8" />
    <arg name="b" type="uint8" />
	</args>
</generator>
 */

#include "../lib/P9813.h"
#include "../lib/connectors.h"
#include <stdint.h>

static char init_led() {
  initColorRGB(BASE_SHIELD_D2);
  setColorRGB(0, 0, 0, 0);

  return 1;
}

static char manage_color(struct args_t *args) {
  if (args) {
    setColorRGB(0, args->r, args->g, args->b);

    out_uint(args->r);
    out_str("-");
    out_uint(args->g);
    out_str("-");
    out_uint(args->b);
  } else {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    getColorRGB(0, &r, &g, &b);

    out_uint(r);
    out_str("-");
    out_uint(g);
    out_str("-");
    out_uint(b);
  }

  return 1;
}
