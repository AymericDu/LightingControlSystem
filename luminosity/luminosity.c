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

#define TIMER_LUMINOSITY RFLPC_TIMER3
#define NB_TESTS_PER_SECOND 10
#define TOLERANCE_MARGIN 10 // Représente +/- 0,24%
#define MAX_CPT 300
#define MAX_MATCH_VALUE 4294967295

enum state_e {START, STOP, PAUSE};

static uint8_t intensity;
static int luminosity;
static unsigned int cpt;
static enum state_e state;

void start() {
  state = START;
  cpt = 0;
  rflpc_timer_set_match_value(TIMER_LUMINOSITY, RFLPC_TIMER_MATCH0, 1);
  rflpc_timer_set_counter(TIMER_LUMINOSITY, 0);
  rflpc_timer_reset_irq(TIMER_LUMINOSITY, RFLPC_TIMER_MATCH0);
}

void stop() {
  state = STOP;
  rflpc_timer_set_match_value(TIMER_LUMINOSITY, RFLPC_TIMER_MATCH0, MAX_MATCH_VALUE);
  cpt = MAX_CPT;
  rflpc_timer_reset_irq(TIMER_LUMINOSITY, RFLPC_TIMER_MATCH0);
}

void pause() {
  state = PAUSE;
  cpt = 0;
  rflpc_timer_set_match_value(TIMER_LUMINOSITY, RFLPC_TIMER_MATCH0, 5 * NB_TESTS_PER_SECOND);
  rflpc_timer_set_counter(TIMER_LUMINOSITY, 0);
  rflpc_timer_reset_irq(TIMER_LUMINOSITY, RFLPC_TIMER_MATCH0);
}

RFLPC_IRQ_HANDLER bring_luminosity_closer() {
  if (rflpc_timer_test_irq(TIMER_LUMINOSITY, RFLPC_TIMER_MATCH0)) {
    if (state == PAUSE)
      start();
    if (cpt < MAX_CPT) {
      uint8_t r, g, b;
      int luminosity_current;
      int difference;

      // En cas d'action extérieur à ce programme
      getColorRGB(0, &r, &g, &b);
      if (r != intensity || g != intensity || b != intensity) {
        stop();
        return;
      }

      luminosity_current = LM358_read_light();
      difference = luminosity_current - luminosity;

      if (difference > -TOLERANCE_MARGIN && difference < TOLERANCE_MARGIN) {
        pause();
        server_push(&alertLight); // on notifie le changement
        return;
      }

      if (luminosity > luminosity_current) {
        if (intensity == 255) {
          pause();
          server_push(&alertLight); // on notifie le changement
          return;
        }
        intensity++;
      } else {
        if (intensity == 0) {
          pause();
          server_push(&alertLight); // on notifie le changement
          return;
        }
        intensity--;
      }
      setColorRGB(0, intensity, intensity, intensity);

      cpt++;
      if ((cpt % NB_TESTS_PER_SECOND) == 0)
        server_push(&alertLight); // on notifie le changement toutes les secondes

      rflpc_timer_reset_irq(TIMER_LUMINOSITY, RFLPC_TIMER_MATCH0);
    } else {
      stop();
    }
  }
}

static char init_luminosity() {
  /* La LED RGB et le capteur de lumière sont déjà initialisés dans les apps "light" et "light_sensor". */

  rflpc_timer_enable(TIMER_LUMINOSITY);
  rflpc_timer_set_clock(TIMER_LUMINOSITY, RFLPC_CCLK);
  rflpc_timer_set_pre_scale_register(TIMER_LUMINOSITY, rflpc_clock_get_system_clock()/NB_TESTS_PER_SECOND);
  rflpc_timer_set_counter(TIMER_LUMINOSITY, 0);
  rflpc_timer_set_callback(TIMER_LUMINOSITY, bring_luminosity_closer);
  rflpc_timer_set_match_value(TIMER_LUMINOSITY, RFLPC_TIMER_MATCH0, MAX_MATCH_VALUE);
  rflpc_timer_set_irq_on_match(TIMER_LUMINOSITY, RFLPC_TIMER_MATCH0, RFLPC_TIMER_IRQ_ON_MATCH | RFLPC_TIMER_RESET_ON_MATCH);

  cpt = MAX_CPT;
  rflpc_timer_start(TIMER_LUMINOSITY);

  return 1;
}

static char set_luminosity(struct args_t *args) {
  if (args) {
    uint8_t r, g, b;

    luminosity = (int) args->l;
    if (luminosity < 0 || luminosity > 4095) {
      out_str("NOT OK");

      return 1;
    }

    getColorRGB(0, &r, &g, &b);
    intensity = (r + g + b) / 3;
    setColorRGB(0, intensity, intensity, intensity);
    server_push(&alertLight); // on notifie le changement

    start();

    out_str("OK");
  } else {
    out_str("NOT OK");
  }

  return 1;
}
