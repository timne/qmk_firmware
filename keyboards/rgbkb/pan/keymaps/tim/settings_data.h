#pragma once

#include QMK_KEYBOARD_H
#include "quantum.h"

#include "string.h"

#include "animation_names.h"

void valueGetDisplayVal(char* buffer, int buf_len);
void satGetDisplayVal(char* buffer, int buf_len);
void hueGetDisplayVal(char* buffer, int buf_len);
void speedGetDisplayVal(char* buffer, int buf_len);
void nameGetDisplayVal(char* buffer, int buf_len);
void toggleRgbGetDisplayVal(char* buffer, int buf_len);
void toggleMusicGetDisplayVal(char* buffer, int buf_len);
void musicScaleGetDisplayVal(char* buffer, int buf_len);

void settingValToIndicator(int val, int max_val, char* buffer, int buffer_len);

enum settings
{
   VALUE = 0,
   SATURATION,
   HUE,
   SPEED,
   MODE,
   TOGGLE_RGB,
   TOGGLE_MUSIC_MODE,
   MUSIC_SCALE,
   NUM_SETTINGS
};

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
   buffer[buf_len-1] = '\0';
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

uint8_t current_music_mode = 3; // starts on major
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

void settingValToIndicator(int val, int max_val, char* buffer, int buffer_len)
{
   double fraction_of_indicator = (double)val/max_val;
   int num_chars_to_fill = (fraction_of_indicator * (buffer_len-2)) + 0.5;

   strncpy(buffer, "[", buffer_len);
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