#include QMK_KEYBOARD_H
#include "quantum.h"

#include "menu_state.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
   _QWERTY = 0,
   _FN,
};

#define FN_ESC   LT(_FN, KC_ESC)
#define FN_CAPS  LT(_FN, KC_CAPS)
#define QWERTY   DF(_QWERTY)
#define COLEMAK  DF(_COLEMAK)


#define _LAYOUT( \
   /*       0    1    2    3    4    5    6    7    8    9    10   11     12 */\
   /* 0 */  K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11,   K12, \
   /* 1 */  K13, K14, K15, K16, K17, K18, K19, K20, K21, K22, K23, K24,        \
   /* 2 */  K26, K27, K28, K29, K30, K31, K32, K33, K34, K35, K36, K37,        \
   /* 3 */  K38, K39, K40, K41, K42, K43, K44, K45, K46, K47, K48, K49,   K50, \
   /* 4 */  K51, K52, K53, K54, K55, K56, K57, K58, K59, K60, K61, K62         \
) { \
   /* 0 */{ K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11,   K12   }, \
   /* 1 */{ K13, K14, K15, K16, K17, K18, K19, K20, K21, K22, K23, K24,   KC_NO }, \
   /* 2 */{ K26, K27, K28, K29, K30, K31, K32, K33, K34, K35, K36, K37,   KC_NO }, \
   /* 3 */{ K38, K39, K40, K41, K42, K43, K44, K45, K46, K47, K48, K49,   K50   }, \
   /* 4 */{ K51, K52, K53, K54, K55, K56, K57, K58, K59, K60, K61, KC_NO, K62   }  \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [_QWERTY] = _LAYOUT( \
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_0,  KC_BSPC, \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,         \
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT, \
      KC_LCTL, KC_LGUI, KC_LALT, KC_LALT, MO(_FN), KC_SPC, KC_DEL, MO(_FN), KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT         \
   ),

   [_FN] = _LAYOUT( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F11,  KC_F12, \
      KC_GRV,  KC_PSCR, KC_SLCK, KC_PAUS, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______,         \
      _______, _______, _______, _______, KC_INS,  KC_PGUP, KC_HOME, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, KC_ENT,         \
      _______, _______, _______, KC_CAPS, KC_DEL,  KC_PGDN, KC_END,  _______, _______, _______, _______, _______, _______,\
      _______, _______, _______, _______, _______, KC_SPC,  KC_DEL,  _______, _______, _______, _______, _______          \
   )
};


int menu_tick = 0;

const int SHOW_MENU_TIMEOUT = 5000;

bool rewrite_layer_info = false;


menu_state_t menustate;

#ifdef OLED_DRIVER_ENABLE

uint8_t old_layer = 0;
uint8_t old_led_state = 0;

void oled_task_user(void) {
   if(0 == menu_tick)
   {
      // Host Keyboard Layer Status
      uint8_t layer = layer_state ? biton(layer_state) : biton32(default_layer_state);
      uint8_t led_state = host_keyboard_leds();
      if(layer != old_layer || led_state != old_led_state || rewrite_layer_info)
      {
         oled_scroll_off();

         // oled_write_P(PSTR("Tim's Keyboard\n"), false);
         // oled_write_P(PSTR("Layer: "), false);
         switch (layer) {
            case _QWERTY:
            // oled_write_P(PSTR("Default\n"), false);
            oled_write_P(PSTR(" BASE   BASE   BASE \n"), false);
            break;
            case _FN:
            // oled_write_P(PSTR("Function\n"), false);
            oled_write_P(PSTR(" FUNC   FUNC   FUNC \n"), false);
            break;
            default:
            oled_write_P(PSTR("Undefined\n"), false);
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            //oled_write_ln_P(PSTR("Undefined"), false);
         }
         oled_write_P(PSTR("------ ------ ------\n"), false);
         oled_write_P(IS_LED_ON(led_state, USB_LED_NUM_LOCK) ? PSTR(" NUM    NUM    NUM  \n") : PSTR("           \n"), false);
         oled_write_P(IS_LED_ON(led_state, USB_LED_CAPS_LOCK) ? PSTR(" CAPS   CAPS   CAPS \n") : PSTR("           \n"), false);
      }
      oled_scroll_left();

      old_layer = layer;
      old_led_state = led_state;
      rewrite_layer_info = false;
   }
   else // show rgb settings menu
   {
      rewrite_layer_info = true;
      oled_scroll_off();

      displayMenu(menustate);

      if (!menustate.selected)
      {
         --menu_tick;
      }
   }
}
#endif


void encoder_update_user(uint8_t index, bool clockwise) {
   if (index == 0) {         // First encoder - right
      if (clockwise) {
         tap_code(KC_VOLU);
      }
      else {
         tap_code(KC_VOLD);
      }
   }
   else if (index == 1) {  // Second encoder - left
      if (clockwise) {
         if (0 != menu_tick)
         {
            advanceState(&menustate, INPUT_INCREASE);
         }

         menu_tick = SHOW_MENU_TIMEOUT;
      }
      else {
         if (0 != menu_tick)
         {
            advanceState(&menustate, INPUT_DECREASE);
         }

         menu_tick = SHOW_MENU_TIMEOUT;
      }
   }
}

void dip_switch_update_user(uint8_t index, bool active) {
   switch (index) {
      case 0:          // right encoder
      if (active)  // pressed
      {
         tap_code(KC_MUTE);
      } else  // released
      {
         // do nothing
      }
      break;

      case 1:          // left encoder
      if (active)  // pressed
      {
         if (0 != menu_tick)
         {
            advanceState(&menustate, INPUT_SELECT);
         }

         menu_tick = SHOW_MENU_TIMEOUT;
      } else  // released
      {
         // do nothing
      }
      break;
   }
}

void suspend_power_down_user(void)
{
   oled_off();
   rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void)
{
   rgb_matrix_set_suspend_state(false);
}
