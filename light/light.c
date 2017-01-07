/*
<generator>
  <handlers init="init_light" doGet="manage_color"/>
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
#include <channels.h>

#define LED_TURN_ON() setColorRGB(0, 255, 255, 255)
#define LED_TURN_OFF() setColorRGB(0, 0, 0, 0)


/*
 * Retourne l'état de la LED
 */
int led_is_on() {
  uint8_t r, g, b;
  getColorRGB(0, &r, &g, &b);
  return (r | g | b);
}

/*
 * Fonction déclenchée lors d'une interruption GPIO
 */
RFLPC_IRQ_HANDLER _button_event(void) {
  // si l'interruption concerne le pin 3 (port 2) du lpc1768 sur un front montant
  if(LPC_GPIOINT->IO2IntStatR & (1<<3))
  {
    LPC_GPIOINT->IO2IntClr = (1<<3);
    led_is_on() ? LED_TURN_OFF() : LED_TURN_ON(); // on change l'état de la LED
    server_push(&alertLight); // on notifie le changement
  }
}

/*
 * Initialise la LED et le bouton qui permet de controler l'allumage de la LED.
 */
static char init_light() {
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

/*
 * Définit la couleur de la LED ou récupère sa couleur.
 */
static char manage_color(struct args_t *args) {
  if (args) {
    setColorRGB(0, args->r, args->g, args->b);
    server_push(&alertLight); // on notifie le changement
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
