#pragma once

#include QMK_KEYBOARD_H
#include "quantum.h"

#include "animation_names.h"

#include "string.h"

enum menu_state_input
{
   INPUT_SELECT,
   INPUT_INCREASE,
   INPUT_DECREASE
};

enum settings
{
   VALUE = 0,
   SATURATION,
   HUE,
   SPEED,
   MODE,
   TOGGLE_RGB,
   MUSIC_MODE,
   MUSIC_SCALE
};

enum setting_types
{
   TOGGLE_TYPE,
   ADJUST_TYPE,
   OPTIONS_TYPE
};

typedef struct
{
   int setting_index;
   enum settings selected;
} menu_state_t;

const int NUM_SETTINGS = 8;
const int NUM_RGB_SETTINGS = 5; // TODO: make setting types use the setting types enum instead of going by index

const char* setting_names[] = {
   "Value",
   "Saturation",
   "Hue",
   "Speed",
   "Mode",
   "Toggle RGB",
   "Music Mode",
   "Music Scale"
};

const uint16_t rgb_i_codes[] = {
   RGB_VAI,
   RGB_SAI,
   RGB_HUI,
   RGB_SPI,
   RGB_MOD
};

const uint16_t rgb_d_codes[] = {
   RGB_VAD,
   RGB_SAD,
   RGB_HUD,
   RGB_SPD,
   RGB_RMOD
};

void advanceState(menu_state_t* state, enum menu_state_input input)
{
   if(INPUT_SELECT == input)
   {
      if(state->setting_index < NUM_RGB_SETTINGS)
      {
         state->selected = (state->selected + 1) % 2;
      }
      else
      {
         // toggle music mode
         keyrecord_t keyrecord;
         keyrecord.event.pressed = true;
         if(MUSIC_MODE == state->setting_index)
         {
            process_music(MU_TOG, &keyrecord);
         }
         else if(MUSIC_SCALE == state->setting_index)
         {
            music_mode_cycle();
         }
         else if(TOGGLE_RGB == state->setting_index)
         {
            process_rgb(RGB_TOG, &keyrecord);
         }
      }
      
   }
   else if(INPUT_INCREASE == input)
   {
      if(1 == state->selected)
      {
         // increase selected setting
         keyrecord_t keyrecord;
         keyrecord.event.pressed = true;
         process_rgb(rgb_i_codes[state->setting_index], &keyrecord);
      }
      else
      {
         // move to next setting
         state->setting_index = (state->setting_index + 1) % NUM_SETTINGS;
      }
      
   }
   else if(INPUT_DECREASE == input)
   {
      if(1 == state->selected)
      {
         // decrease selected setting
         keyrecord_t keyrecord;
         keyrecord.event.pressed = true;
         process_rgb(rgb_d_codes[state->setting_index], &keyrecord);
      }
      else
      {
         // move to previous setting
         state->setting_index = (state->setting_index - 1);
         if(state->setting_index < 0)
         {
            state->setting_index = state->setting_index + NUM_SETTINGS;
         }
      }
   }
}

void settingValToIndicator(int val, int max_val, char* buffer, int buffer_len)
{
   double fraction_of_indicator = (double)val/max_val;
   int num_chars_to_fill = (fraction_of_indicator * buffer_len) + 0.5;

   buffer[0] = '\0';
   for (size_t i = 0; i < num_chars_to_fill; ++i)
   {
      strcat(buffer, "#");
   }
}

void displayMenu(menu_state_t state)
{
   char writebuffer[21];
   writebuffer[0] = '\0';

   if(0 == state.selected)
   {
      // display list of settings
      for (int i = 0; i < 4; ++i)
      {
         int setting_to_display = (state.setting_index - 1 + i) % NUM_SETTINGS;
         if(setting_to_display < 0)
         {
            setting_to_display += NUM_SETTINGS;
         }

         if(1 == i)
         {
            if(1 == state.selected)
            {
               strcat(writebuffer, " ");
            }
            strcat(writebuffer, "> ");
         }
         else
         {
            strcat(writebuffer, "  ");
         }
         

         strcat(writebuffer, setting_names[setting_to_display]);
         strcat(writebuffer, "\n");

         oled_write_P(PSTR(writebuffer), false);
         writebuffer[0] = '\0';
      }
   }

   else
   {
      // empty first line
      oled_write_P(PSTR("\n"), false);

      // selected setting
      strcat(writebuffer, " > ");
      strcat(writebuffer, setting_names[state.setting_index]);
      strcat(writebuffer, " <");
      strcat(writebuffer, "\n");
      oled_write_P(PSTR(writebuffer), false);

      // empty third line
      oled_write_P(PSTR("\n"), false);

      writebuffer[0] = '\0';

      // display value of current setting
      int val = 0;
      char valbuffer[10] = "\0";
      switch (state.setting_index)
      {
         case VALUE:
         val = rgb_matrix_get_val();
         settingValToIndicator(val, 255, writebuffer, 20);
         strcat(writebuffer, "\n");
         break;
         case SATURATION:
         val = rgb_matrix_get_sat();
         settingValToIndicator(val, 255, writebuffer, 20);
         strcat(writebuffer, "\n");
         break;
         case HUE:
         val = rgb_matrix_get_hue();
         settingValToIndicator(val, 255, writebuffer, 20);
         strcat(writebuffer, "\n");
         break;
         case SPEED:
         val = rgb_matrix_get_speed();
         settingValToIndicator(val, 255, writebuffer, 20);
         strcat(writebuffer, "\n");
         break;
         case MODE:
         val = rgb_matrix_get_mode();
         strncat(writebuffer, rgbmatrix_anim_names[val], 20);
         strcat(writebuffer, "\n");
         break;
         case TOGGLE_RGB:
         val = rgb_matrix_is_enabled();
         strcat(writebuffer, itoa(val, valbuffer, 10));
         strcat(writebuffer, "\n");
         break;
         case MUSIC_MODE:
         break;
         case MUSIC_SCALE:
         break;
      
      default:
         break;
      }

      oled_write_P(PSTR(writebuffer), false);
   }
}
