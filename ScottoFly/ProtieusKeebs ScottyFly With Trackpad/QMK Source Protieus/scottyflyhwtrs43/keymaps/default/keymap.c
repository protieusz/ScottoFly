/*
Copyright 2022 Joe Scotto

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "drivers/haptic/DRV2605L.h"
#include <stdio.h>
#include "iqs5xx.h"

typedef union {
  uint32_t raw;
  struct {
    int  hf_mode : 10;
    bool tap : 1;
    bool layer_hf : 1;
  };
} user_config_t;
user_config_t user_config;

bool is_layer_hf;

enum combo_events {
  COMBO_DEL,
  COMBO_ESC,
 };
 
#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_del[] = {KC_Y, KC_H, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_Q, KC_A, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [COMBO_DEL] = COMBO(combo_del,KC_DEL),
  [COMBO_ESC] = COMBO(combo_esc,KC_ESC),
};
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, 1, 2, 3);
} 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_Q,         KC_W, KC_E,    KC_R,    KC_T,                                           KC_Y,          KC_U,          KC_I,     KC_O,   KC_P,
        KC_A,         KC_S, KC_D,    KC_F,    KC_G,                                           KC_H,          KC_J,          KC_K,     KC_L,   KC_SCLN,
        LSFT_T(KC_Z), KC_X, KC_C,    KC_V,    KC_B,                                           KC_N,          KC_M,          KC_COMMA, KC_DOT, RSFT_T(KC_SLSH),
                            KC_LCTL, KC_LGUI, LT(1,KC_BSPC),   KC_MS_BTN1,    KC_MS_BTN2,     LT(2,KC_SPC),   (KC_ENT),      KC_LALT
    ),
    [1] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                            KC_6,     KC_7,    KC_8,    KC_9,    KC_0,
        KC_TAB,  _______, _______, _______, _______,                         KC_MINS,  KC_EQL,  KC_LBRC, KC_RBRC, KC_QUOT,
        _______, _______, _______, _______, _______,                         KC_TILD,  KC_GRV,  _______, _______, KC_BSLS,
                          _______, _______, _______,     _______, _______,   _______,  _______, _______
    ),
    [2] = LAYOUT(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        RGB_VAI,  RGB_SAI,    RGB_HUI,    RGB_SPI,   RGB_MOD,                RGB_TOG,  DT_PRNT,  DT_UP,   DT_DOWN, _______,
        RGB_VAD,  RGB_SAD,    RGB_HUD,    RGB_SPD,   RGB_RMOD,               _______,  _______, _______, _______, _______,
                          _______, _______, _______,     _______, _______,   _______,  _______, _______
    ),
    [3] = LAYOUT(
        _______, KC_UP, _______, _______, _______,                         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_PSCR,
        KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,                      KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,
        _______, _______, _______, _______, _______,                       KC_F10,  KC_F11,  KC_F12,  _______, _______,
                          _______, _______, _______,     _______, _______,   _______, _______, _______
    )
};

void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user();
  hf_mode = user_config.hf_mode ? user_config.hf_mode : 60;
  tap_mode = user_config.tap ? user_config.tap : 1;
  is_layer_hf = user_config.layer_hf ? user_config.layer_hf : 1;
}

void hf_DRV_pulse(bool ee2_up) {
  if (ee2_up) {
    user_config.hf_mode = hf_mode;  
    eeconfig_update_user(user_config.raw); 
    hf_mode = user_config.hf_mode;
  }
  DRV_pulse(hf_mode);
  char buf[12]; 
  snprintf(buf, sizeof(buf), "%d", hf_mode);
  const char *s = buf;
  send_string(s);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {  
      case KC_BTN1 ... KC_BTN5:
        if (record->event.pressed) {
          pointing_device_set_button(1 << (keycode - KC_BTN1));
        } else {
          pointing_device_clear_button(1 << (keycode - KC_BTN1));
        }
        return false;
     case KC_F19: 
        if (record->event.pressed) {
          user_config.layer_hf = !user_config.layer_hf;  
          eeconfig_update_user(user_config.raw); 
          is_layer_hf = user_config.layer_hf;        
        }
        return false;         
      case KC_F20: 
        if (record->event.pressed) {
            hf_DRV_pulse(false);
        }
        return false;
      case KC_F21: 
        if (record->event.pressed) {
            hf_mode--;
            if(hf_mode == -1) {
              hf_mode = 123;
            }
            hf_DRV_pulse(true);
        }
        return false;
      case KC_F22: 
        if (record->event.pressed) {
            hf_mode++;
            if(hf_mode == 124) {
              hf_mode = 0;
            }
            hf_DRV_pulse(true);
        }
        return false;
      case KC_F23:
        if (record->event.pressed) {    
          user_config.tap = !user_config.tap;  
          eeconfig_update_user(user_config.raw); 
          tap_mode = user_config.tap;
        } 
        return false;  

    default:
      return true;
  }
};

int layer = 0;

void matrix_scan_user(void) {
  int current_layer = get_highest_layer(layer_state|default_layer_state); 
  if(is_layer_hf && layer != current_layer){
    DRV_pulse(hf_mode);
    layer = current_layer;
  }
}

bool get_haptic_enabled_key(uint16_t keycode, keyrecord_t *record) {
    return false;
}





