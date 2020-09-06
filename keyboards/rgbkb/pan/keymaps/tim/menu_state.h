#pragma once

#include QMK_KEYBOARD_H
#include "quantum.h"

#include "settings_data.h"

#include "string.h"

enum menu_state_input
{
   INPUT_SELECT,
   INPUT_INCREASE,
   INPUT_DECREASE
};

typedef struct
{
   int setting_index;
   int selected;
} menu_state_t;

void advanceState(menu_state_t* state, enum menu_state_input input)
{
   if(INPUT_SELECT == input)
   {
      state->selected = (state->selected + 1) % 2;
   }
   else
   {
      if(1 == state->selected)
      {
         uint16_t code;
         if(INPUT_INCREASE == input)
         {
            // increase selected setting
            code = settings_data[state->setting_index].icode;
         }
         else
         {
            // decrease selected setting
            code = settings_data[state->setting_index].dcode;
         }

         keyrecord_t keyrecord;
         keyrecord.event.pressed = true;
         process_rgb(code, &keyrecord);
         process_music(code, &keyrecord);

         // special thing for scale because there is no way to read it back
         if(MUSIC_SCALE == state->setting_index)
         {
            current_music_mode = (current_music_mode + 1) % 4;
         }
      }
      else
      {
         // move to next/previous setting
         if(INPUT_INCREASE == input)
         {
            state->setting_index = (state->setting_index + 1) % NUM_SETTINGS;
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
}

void displayMenu(menu_state_t state)
{
   const size_t buf_len = 21;
   char writebuffer[buf_len];
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
            strcpy(writebuffer, "> ");
         }
         else
         {
            strcpy(writebuffer, "  ");
         }


         strncat(writebuffer, settings_data[setting_to_display].name, buf_len-3);
         strcat(writebuffer, "\n");

         oled_write_P(PSTR(writebuffer), false);
      }
   }

   else
   {
      // empty first line
      oled_write_P(PSTR("\n"), false);

      // selected setting
      strcpy(writebuffer, "> ");
      strncat(writebuffer, settings_data[state.setting_index].name, buf_len-3);
      strcat(writebuffer, "\n");
      oled_write_P(PSTR(writebuffer), false);

      // empty third line
      oled_write_P(PSTR("\n"), false);

      // call the function that gets the string to display for the setting value
      (*(settings_data[state.setting_index].getDisplayVal))(writebuffer, buf_len-1);

      strcat(writebuffer, "\n");
      oled_write_P(PSTR(writebuffer), false);
   }
}
