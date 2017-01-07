/*
<generator>
  <handlers doGet="get_color"/>
	<properties persistence="volatile" interaction="stream" channel="alertLight"/>
</generator>
 */

#include "../lib/P9813.h"
#include "../lib/connectors.h"
#include <stdint.h>

static char get_color(struct args_t *args) {
  uint8_t r, g, b;
  getColorRGB(0, &r, &g, &b);
  out_uint(r);
  out_str("-");
  out_uint(g);
  out_str("-");
  out_uint(b);
  return 1;
}
