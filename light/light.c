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

#define LED_TURN_ON() setColorRGB(0, 255, 255, 255)
#define LED_TURN_OFF() setColorRGB(0, 0, 0, 0)

int led_is_on() {
  uint8_t r, g, b;
  getColorRGB(0, &r, &g, &b);
  return (r | g | b);
}

RFLPC_IRQ_HANDLER _button_event(void) {
  if(LPC_GPIOINT->IO2IntStatR & (1<<3))
  {
    LPC_GPIOINT->IO2IntClr = (1<<3);
    led_is_on() ? LED_TURN_OFF() : LED_TURN_ON();
  }
}

static char init_led() {
  initColorRGB(BASE_SHIELD_D2);
  LED_TURN_OFF();

  // Active les interruptions gpio pour le bouton branché sur
  // le port D6 de la base shield (port 2 - pin 3 de lpc1768)
  rflpc_irq_enable(EINT3_IRQn);
  // EINT3_IRQn channel partagé avec les interruptions GPIO
  rflpc_irq_set_handler(EINT3_IRQn, _button_event);
  LPC_GPIOINT->IO2IntEnR |= (1<<3); // Interruption sur front montant

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
  }
  else {
    uint8_t r, g, b;
    getColorRGB(0, &r, &g, &b);
    out_uint(r);
    out_str("-");
    out_uint(g);
    out_str("-");
    out_uint(b);
  }

  return 1;
}
