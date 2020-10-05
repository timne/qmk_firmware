/*
Copyright 2017 Danny Nguyen <danny@hexwire.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x3061
#define DEVICE_VER      0x0002
#define MANUFACTURER    Legonut
#define PRODUCT         "Project Zen"
#define DESCRIPTION     "Split gaming keyboard"

/* key matrix size */
// Rows are doubled-up

// wiring of each half
#ifdef CONVERT_TO_PROTON_C
  #define MATRIX_ROWS 5
  #define MATRIX_COLS 7
#else
  #define MATRIX_ROWS 10
  #define MATRIX_COLS 7
#endif

// Proton-C does pin conversion
#define MATRIX_ROW_PINS { C6, E6, B5, D7, B4 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B3, B1, B2 }

#define ENCODERS_PAD_A  { D4 }
#define ENCODERS_PAD_B  { D2 }

#define RGB_DI_PIN         B6
#define SOFT_SERIAL_PIN    D3

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define SSD1306OLED

#ifdef RGBLIGHT_ENABLE
  /* ws2812 RGB LED */
  #define RGBLED_NUM 62    // Number of LEDs
  #define RGBLIGHT_ANIMATIONS
#endif

#ifdef RGB_MATRIX_ENABLE
#   define DRIVER_LED_TOTAL 62
#   define RGB_MATRIX_KEYPRESSES // reacts to keypresses
// #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
// #   define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#   define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #   define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// #   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
// #    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 160 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 8
#    define RGB_MATRIX_VAL_STEP 8
#    define RGB_MATRIX_SPD_STEP 10

/* Disable the animations you don't want/need.  You will need to disable a good number of these    *
 * because they take up a lot of space.  Disable until you can successfully compile your firmware. */
// #   define DISABLE_RGB_MATRIX_ALPHAS_MODS
#   define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#   define DISABLE_RGB_MATRIX_BREATHING
#   define DISABLE_RGB_MATRIX_CYCLE_ALL
#   define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#   define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
#   define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
#   define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#   define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#   define DISABLE_RGB_MATRIX_DUAL_BEACON
#   define DISABLE_RGB_MATRIX_RAINBOW_BEACON
#   define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#   define DISABLE_RGB_MATRIX_RAINDROPS
#   define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#   define DISABLE_RGB_MATRIX_TYPING_HEATMAP
#   define DISABLE_RGB_MATRIX_DIGITAL_RAIN
#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE
#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#   define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#   define DISABLE_RGB_MATRIX_SPLASH
#   define DISABLE_RGB_MATRIX_MULTISPLASH
#   define DISABLE_RGB_MATRIX_SOLID_SPLASH
#   define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
