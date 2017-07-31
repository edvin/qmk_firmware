#include "tornado.h"
#include "action_layer.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   /* 0: qwerty */
    KEYMAP_TORNADO(
        KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_BSPC, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS,KC_EQL,\
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC,KC_RBRC, \
        F(0), KC_A, KC_S, KC_D, KC_F, KC_G, KC_ENT, KC_H, KC_J, KC_K, KC_L, KC_SCLN,KC_QUOT,KC_BSLS, \
        KC_LSPO,KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM,KC_DOT, KC_SLSH,KC_RSPC, \
        KC_LCTL,KC_LGUI,KC_LALT,F(1), KC_SPC, KC_INS,KC_DEL, F(2), KC_RCTL),
    /* 1: Numpad layer */
    KEYMAP_TORNADO(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_DEL,KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, KC_TRNS,  \
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_4,KC_5,KC_6,KC_TRNS,KC_TRNS,KC_TRNS,\
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_1,KC_2,KC_3,KC_TRNS,KC_TRNS,KC_TRNS,\
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_0,KC_DOT,KC_TRNS,KC_TRNS,KC_TRNS, \
        KC_TRNS,KC_TRNS,KC_TRNS,KC_BTN1,KC_BTN2, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS),
    /* 2: F + Arrow Keys layer */
    KEYMAP_TORNADO(
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_DEL,KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,\
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_PGUP,KC_UP,KC_PGDN,KC_PSCR,KC_SLCK,KC_PAUS,\
        KC_TRNS,KC_TRNS,KC_VOLD,KC_VOLU,KC_MUTE,KC_TRNS,KC_TRNS,KC_HOME,KC_LEFT,KC_DOWN,KC_RGHT,KC_INS,KC_DEL,KC_TRNS, \
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_END,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, \
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS),
};
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1), // To Mouse overlay
    [1] = ACTION_LAYER_MOMENTARY(2), // To F + Arrow Keys overlay
    [2] = ACTION_LAYER_TOGGLE(1),    // Toggle F + Arrow Keys overlay,
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    /*
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
      */
    return MACRO_NONE;
};

void matrix_scan_user(void) {
/*
//Layer LED indicators
    uint32_t layer = layer_state;

    if (layer & (1<<1)) {
        gh60_wasd_leds_on();
        gh60_fn_led_on();
    } else {
        gh60_wasd_leds_off();
        gh60_fn_led_off();
    }

    if (layer & (1<<2)) {
        gh60_poker_leds_on();
        gh60_esc_led_on();
    } else {
        gh60_poker_leds_off();
        gh60_esc_led_off();
    }
*/
};

#define RESET_BUTTON1 (1 << 0)
#define RESET_BUTTON2 (1 << 1)
#define RESET_BUTTON3 (1 << 2)
#define RESET_BUTTON4 (1 << 3)
#define TORNADO_SHL (1 << 4)
#define TORNADO_SHR (1 << 5)
#define RESET_TRIGGERED (RESET_BUTTON1 | RESET_BUTTON2 | RESET_BUTTON3 | RESET_BUTTON4)

static int combo_state = 0;

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
  if (keycode == KC_GESC) {
    if (record->event.pressed)
      combo_state |= RESET_BUTTON1;
    else
      combo_state &= ~RESET_BUTTON1;
  }

  if (keycode == KC_LCTL) {
    if (record->event.pressed)
      combo_state |= RESET_BUTTON2;
    else
      combo_state &= ~RESET_BUTTON2;
  }

  if (keycode == KC_RCTL) {
    if (record->event.pressed)
      combo_state |= RESET_BUTTON3;
    else
      combo_state &= ~RESET_BUTTON3;
  }

  if (keycode == KC_EQL) {
    if (record->event.pressed)
      combo_state |= RESET_BUTTON4;
    else
      combo_state &= ~RESET_BUTTON4;
  }

  // Space cadet left curly on steroids
  if (keycode == KC_LSPO) {
    if (record->event.pressed) {
      combo_state |= TORNADO_SHL;
      if (combo_state & TORNADO_SHR) {
          register_code16(KC_LCBR);
          unregister_code16(KC_LCBR);
          return false;
      }
    }
    else
      combo_state &= ~TORNADO_SHL;
  }
  
  // Space cadet right curly on steroids
  if (keycode == KC_RSPC) {
    if (record->event.pressed) {
      combo_state |= TORNADO_SHR;
      if (combo_state & TORNADO_SHL) {
          register_code16(KC_RCBR);
          unregister_code16(KC_RCBR);
          return false;
      }
    }
    else
      combo_state &= ~TORNADO_SHR;
  }
  
  if (combo_state == RESET_TRIGGERED) {
    reset_keyboard();
    return false;
  }

  return true;
};
