#include QMK_KEYBOARD_H


/* THIS FILE WAS GENERATED!
 *
 * This file was generated by qmk json2c. You may or may not want to
 * edit it directly.
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x6_3(
        KC_NO, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_BSPC, KC_NO, 
        KC_NO, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_NO,
        KC_NO, LSFT_T(KC_Z), LCTL_T(KC_X), LALT_T(KC_C), LGUI_T(KC_Vt), KC_B, KC_K, RGUI_T(KC_M), RALT_T(KC_COMM), RCTL_T(KC_DOT), RSFT_T(KC_SLSH), KC_NO, 
        KC_NO, KC_NO, LT(1,KC_SPC), LT(2,KC_TAB), KC_NO, KC_NO
    ),
	[1] = LAYOUT_split_3x6_3(
        KC_NO, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_BSPC, KC_NO,
        KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO, 
        KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, MO(3), KC_ESC, KC_RGUI, RALT_T(KC_COMM), RCTL_T(KC_DOT), RSFT_T(KC_SLSH), KC_NO,
        KC_NO, KC_NO, KC_SPC, KC_ENT, KC_NO, KC_NO
    ),
	[2] = LAYOUT_split_3x6_3(
        KC_NO, KC_UNDS, KC_MINS, KC_PLUS, KC_EQL, KC_COLN, KC_GRV, KC_MRWD, KC_MPLY, KC_MFFD, KC_DEL,
        KC_NO, KC_NO, KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_BSLS, KC_ESC, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, KC_NO,
        KC_NO, LSFT_T(KC_LBRC), LCTL_T(KC_QUOT), LALT_T(KC_SCLN), LGUI_T(KC_RBRC), KC_DQUO, KC_NO, RGUI_T(KC_VOLD), RALT_T(KC_MUTE), RCTL_T(KC_VOLU), RSFT_T(KC_CAPS), KC_NO,
        KC_NO, KC_NO, KC_SPC, KC_NO, KC_NO, KC_NO
    ),
	[3] = LAYOUT_split_3x6_3(
        KC_NO, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_SPC, KC_NO, KC_NO, KC_NO
    )
};
