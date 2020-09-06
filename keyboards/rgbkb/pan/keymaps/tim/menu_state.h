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

typedef struct
{
   int setting_index;
   int selected;
} menu_state_t;

const int NUM_SETTINGS = 8;

enum settings
{
   VALUE = 0,
   SATURATION,
   HUE,
   SPEED,
   MODE,
   TOGGLE_RGB,
   TOGGLE_MUSIC_MODE,
   MUSIC_SCALE
};

void valueGetDisplayVal(char* buffer, int buf_len);
void satGetDisplayVal(char* buffer, int buf_len);
void hueGetDisplayVal(char* buffer, int buf_len);
void speedGetDisplayVal(char* buffer, int buf_len);
void nameGetDisplayVal(char* buffer, int buf_len);
void toggleRgbGetDisplayVal(char* buffer, int buf_len);
void toggleMusicGetDisplayVal(char* buffer, int buf_len);
void musicScaleGetDisplayVal(char* buffer, int buf_len);

struct setting
{
   char name[20];
   uint16_t icode;
   uint16_t dcode;
   void (*getDisplayVal)(char*, int);
};

const struct setting settings_data[] = {
   {
      .name = "Value",
      .icode = RGB_VAI,
      .dcode = RGB_VAD,
      .getDisplayVal = valueGetDisplayVal
   },
   {
      .name = "Saturation",
      .icode = RGB_SAI,
      .dcode = RGB_SAD,
      .getDisplayVal = satGetDisplayVal
   },
   {
      .name = "Hue",
      .icode = RGB_HUI,
      .dcode = RGB_HUD,
      .getDisplayVal = hueGetDisplayVal
   },
   {
      .name = "Speed",
      .icode = RGB_SPI,
      .dcode = RGB_SPD,
      .getDisplayVal = speedGetDisplayVal
   },
   {
      .name = "RGB Mode",
      .icode = RGB_MOD,
      .dcode = RGB_RMOD,
      .getDisplayVal = nameGetDisplayVal
   },
   {
      .name = "Toggle RGB",
      .icode = RGB_TOG,
      .dcode = RGB_TOG,
      .getDisplayVal = toggleRgbGetDisplayVal
   },
   {
      .name = "Toggle Music Mode",
      .icode = MU_TOG,
      .dcode = MU_TOG,
      .getDisplayVal = toggleMusicGetDisplayVal
   },
   {
      .name = "Music Scale",
      .icode = MU_MOD,
      .dcode = MU_MOD,
      .getDisplayVal = musicScaleGetDisplayVal
   }
};

uint8_t current_music_mode = 3; // starts on major

void advanceState(menu_state_t* state, enum menu_state_input input)
{
   if(INPUT_SELECT == input)
   {
      state->selected = (state->selected + 1) % 2;
   }
   else if(INPUT_INCREASE == input)
   {
      if(1 == state->selected)
      {
         // increase selected setting
         keyrecord_t keyrecord;
         keyrecord.event.pressed = true;
         process_rgb(settings_data[state->setting_index].icode, &keyrecord);
         process_music(settings_data[state->setting_index].icode, &keyrecord);

         // special thing for scale because there is no way to read it back
         if(MUSIC_SCALE == state->setting_index)
         {
            current_music_mode = (current_music_mode + 1) % 4;
         }
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
         process_rgb(settings_data[state->setting_index].dcode, &keyrecord);
         process_music(settings_data[state->setting_index].dcode, &keyrecord);

         // special thing for scale because there is no way to read it back
         if(MUSIC_SCALE == state->setting_index)
         {
            current_music_mode = (current_music_mode + 1) % 4;
         }
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
   int num_chars_to_fill = (fraction_of_indicator * (buffer_len-2)) + 0.5;

   // buffer = "[\0";
   buffer[0] = '[';
   buffer[1] = '\0';
   for (size_t i = 0; i < buffer_len - 2; ++i)
   {
      if (i < num_chars_to_fill)
      {
         strcat(buffer, "=");
      }
      else
      {
         strcat(buffer, " ");
      }
   }
   strcat(buffer, "]");
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


         strcat(writebuffer, settings_data[setting_to_display].name);
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
      strcat(writebuffer, settings_data[state.setting_index].name);
      strcat(writebuffer, "\n");
      oled_write_P(PSTR(writebuffer), false);

      // empty third line
      oled_write_P(PSTR("\n"), false);

      writebuffer[0] = '\0';

      (*(settings_data[state.setting_index].getDisplayVal))(writebuffer, 20);

      strcat(writebuffer, "\n");
      oled_write_P(PSTR(writebuffer), false);
   }
}

void valueGetDisplayVal(char* buffer, int buf_len)
{
   settingValToIndicator(rgb_matrix_get_val(), 255, buffer, buf_len);
}

void satGetDisplayVal(char* buffer, int buf_len)
{
   settingValToIndicator(rgb_matrix_get_sat(), 255, buffer, buf_len);
}

void hueGetDisplayVal(char* buffer, int buf_len)
{
   settingValToIndicator(rgb_matrix_get_hue(), 255, buffer, buf_len);
}

void speedGetDisplayVal(char* buffer, int buf_len)
{
   settingValToIndicator(rgb_matrix_get_speed(), 255, buffer, buf_len);
}

void nameGetDisplayVal(char* buffer, int buf_len)
{
   strncpy(buffer, rgbmatrix_anim_names[rgb_matrix_get_mode()], buf_len);
}

void toggleRgbGetDisplayVal(char* buffer, int buf_len)
{
   if(rgb_matrix_is_enabled())
   {
      strncpy(buffer, "On", buf_len);
   }
   else
   {
      strncpy(buffer, "Off", buf_len);
   }
}

void toggleMusicGetDisplayVal(char* buffer, int buf_len)
{
   if(is_music_on())
   {
      strncpy(buffer, "On", buf_len);
   }
   else
   {
      strncpy(buffer, "Off", buf_len);
   }
}


void musicScaleGetDisplayVal(char* buffer, int buf_len)
{
   switch (current_music_mode)
   {
   case 0:
      strncpy(buffer, "Chromatic", buf_len);
      break;
   case 1:
      strncpy(buffer, "Guitar", buf_len);
      break;
   case 2:
      strncpy(buffer, "Violin", buf_len);
      break;
   case 3:
      strncpy(buffer, "Major", buf_len);
      break;
   default:
      break;
   }
}