#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _NAV
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  NAV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_VOLD, KC_VOLU, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    KC_LCTL, KC_LGUI, KC_LALT, KC_LALT, MO(1),   KC_GRV,  KC_PGUP, KC_HOME, KC_QUOT, MO(1),   KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, \
                                                 KC_SPC,  KC_PGDN, KC_END,  KC_DEL \
  ),
  [_NAV] = LAYOUT( \
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
    KC_GRV,  RGB_MOD, RGB_HUI, RGB_SAI, RGB_SPI, RGB_TOG,                   _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______, \
    _______, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_SPD, KC_PGUP,                   KC_HOME, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, KC_ENT,   \
    _______, _______, _______, _______, _______, KC_PGDN, RGB_VAD, RGB_VAI, KC_END,  _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, \
                                                 _______, _______, _______, _______
  )
};

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      tap_code(KC_PGDN);
    } else {
      tap_code(KC_PGUP);
    }
  } else if (index == 1) { /* Second encoder from slave */
    if (clockwise) {
      tap_code(KC_UP);
    } else {
      tap_code(KC_DOWN);
    }
  }
}

void set_keylog(uint16_t keycode, keyrecord_t *record);
// void render_status(int, int);
void render_status(void);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
  #endif
  // if (record->event.pressed) {
  // #ifdef SSD1306OLED
  //   set_keylog(keycode, record);
  //   render_status(record->event.key.row, record->event.key.col);
  // #endif
  // }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(1UL<<_QWERTY);
      }
      return false;
      break;
    //case COLEMAK:
      //if (record->event.pressed) {
        //set_single_persistent_default_layer(1UL<<_COLEMAK);
      //}
      //return false;
      //break;
  }
  return true;
}


#if OLED_DRIVER_ENABLE
const char* layer_name_user(uint32_t layer) {
  switch (layer) {
    case _QWERTY:
      return PSTR("QWRTY");
    case _NAV:
      return PSTR("NAV\n");
    default:
      return PSTR("UNDEF");
  }
}
#endif
