/*Copyright 2019 coseyfannitutti

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

#include "config_common.h"
#define MATRIX_ROW_PINS { A15, B10, A14, A13, A7 }
#define MATRIX_COL_PINS { A8, A6, B0, B1, B2, B4, B5, A1, A2, B3, B9, A10, A9 }
#define ENCODERS_PAD_A { B14, B11 }
#define ENCODERS_PAD_B { B15, B12 }
#define DIP_SWITCH_PINS { A0, B13 }
#define RGB_DI_PIN A3
#define ENCODER_DIRECTION_FLIP
#define TAP_CODE_DELAY 15

#define RGB_DISABLE_WHEN_USB_SUSPENDED true

#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#define RGB_MATRIX_CENTER { 104, 42 }

#define RGB_MATRIX_HUE_STEP 7
#define RGB_MATRIX_SAT_STEP 13
#define RGB_MATRIX_VAL_STEP 13
#define RGB_MATRIX_SPD_STEP 13
