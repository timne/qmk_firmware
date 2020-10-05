#pragma once

char* rgbmatrix_anim_names[] =
{
   "begin",
#ifndef DISABLE_RGB_MATRIX_SOLID_COLOR
   "SOLID_COLOR",
#endif     // Static single hue, no speed support
#ifndef DISABLE_RGB_MATRIX_ALPHAS_MODS
   "ALPHAS_MODS",
#endif         // Static dual hue, speed is hue for secondary hue
#ifndef DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
   "GRADIENT_UP_DOWN",
#endif    // Static gradient top to bottom, speed controls how much gradient changes
#ifndef DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
   "GRADIENT_LEFT_RIGHT",
#endif    // Static gradient left to right, speed controls how much gradient changes
#ifndef DISABLE_RGB_MATRIX_BREATHING
   "BREATHING",
#endif           // Single hue brightness cycling animation
#ifndef DISABLE_RGB_MATRIX_BAND_SAT
   "BAND_SAT",
#endif        // Single hue band fading saturation scrolling left to right
#ifndef DISABLE_RGB_MATRIX_BAND_VAL
   "BAND_VAL",
#endif        // Single hue band fading brightness scrolling left to right
#ifndef DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
   "BAND_PINWHEEL_SAT",
#endif   // Single hue 3 blade spinning pinwheel fades saturation
#ifndef DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
   "BAND_PINWHEEL_VAL",
#endif   // Single hue 3 blade spinning pinwheel fades brightness
#ifndef DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
   "BAND_SPIRAL_SAT",
#endif     // Single hue spinning spiral fades saturation
#ifndef DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
   "BAND_SPIRAL_VAL",
#endif     // Single hue spinning spiral fades brightness
#ifndef DISABLE_RGB_MATRIX_CYCLE_ALL
   "CYCLE_ALL",
#endif           // Full keyboard solid hue cycling through full gradient
#ifndef DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
   "CYCLE_LEFT_RIGHT",
#endif    // Full gradient scrolling left to right
#ifndef DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
   "CYCLE_UP_DOWN",
#endif       // Full gradient scrolling top to bottom
#ifndef DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
   "RAINBOW_MOVING_CHEVRON",
#endif  // Full gradent Chevron shapped scrolling left to right
#ifndef DISABLE_RGB_MATRIX_CYCLE_OUT_IN
   "CYCLE_OUT_IN",
#endif        // Full gradient scrolling out to in
#ifndef DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
   "CYCLE_OUT_IN_DUAL",
#endif   // Full dual gradients scrolling out to in
#ifndef DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
   "CYCLE_PINWHEEL",
#endif      // Full gradient spinning pinwheel around center of keyboard
#ifndef DISABLE_RGB_MATRIX_CYCLE_SPIRAL
   "CYCLE_SPIRAL",
#endif        // Full gradient spinning spiral around center of keyboard
#ifndef DISABLE_RGB_MATRIX_DUAL_BEACON
   "DUAL_BEACON",
#endif         // Full gradient spinning around center of keyboard
#ifndef DISABLE_RGB_MATRIX_RAINBOW_BEACON
   "RAINBOW_BEACON",
#endif      // Full tighter gradient spinning around center of keyboard
#ifndef DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
   "RAINBOW_PINWHEELS",
#endif   // Full dual gradients spinning two halfs of keyboard
#ifndef DISABLE_RGB_MATRIX_RAINDROPS
   "RAINDROPS",
#endif           // Randomly changes a single key's hue
#ifndef DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
   "JELLYBEAN_RAINDROPS",
#endif // Randomly changes a single key's hue and saturation
#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
#ifndef DISABLE_RGB_MATRIX_TYPING_HEATMAP
   "TYPING_HEATMAP",
#endif      // How hot is your WPM!
#ifndef DISABLE_RGB_MATRIX_DIGITAL_RAIN
   "DIGITAL_RAIN",
#endif        // That famous computer simulation
#endif
#if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
   "SOLID_REACTIVE_SIMPLE",
#endif   // Pulses keys hit to hue & value then fades value out
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE
   "SOLID_REACTIVE",
#endif      // Static single hue, pulses keys hit to shifted hue then fades to current hue
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
   "SOLID_REACTIVE_WIDE",
#endif       // Hue & value pulse near a single key hit then fades value out
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
   "SOLID_REACTIVE_MULTIWIDE",
#endif  // Hue & value pulse near multiple key hits then fades value out
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
   "SOLID_REACTIVE_CROSS",
#endif      // Hue & value pulse the same column and row of a single key hit then fades value out
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
   "SOLID_REACTIVE_MULTICROSS",
#endif // Hue & value pulse the same column and row of multiple key hits then fades value out
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
   "SOLID_REACTIVE_NEXUS",
#endif      // Hue & value pulse away on the same column and row of a single key hit then fades value out
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
   "SOLID_REACTIVE_MULTINEXUS",
#endif // Hue & value pulse away on the same column and row of multiple key hits then fades value out
#ifndef DISABLE_RGB_MATRIX_SPLASH
   "SPLASH",
#endif              // Full gradient & value pulse away from a single key hit then fades value out
#ifndef DISABLE_RGB_MATRIX_MULTISPLASH
   "MULTISPLASH",
#endif         // Full gradient & value pulse away from multiple key hits then fades value out
#ifndef DISABLE_RGB_MATRIX_SOLID_SPLASH
   "SOLID_SPLASH",
#endif        // Hue & value pulse away from a single key hit then fades value out
#ifndef DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
   "SOLID_MULTISPLASH",
#endif   // multi
#endif
#if defined(RGB_MATRIX_CUSTOM_USER)
   "Custom 1",
   "Custom 2",
#endif
   "end"
};

const int RGBMATRIX_ANIM_NAMES_SIZE = sizeof(rgbmatrix_anim_names) / sizeof(rgbmatrix_anim_names[0]);