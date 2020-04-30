// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "amj60.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DEF 0
#define _SPC 1

// dual-role shortcuts
# define SPACEDUAL LT(_SPC, KC_SPACE)

// arrow cluster duality bottom right corner
#define ARRLEFT  ALT_T(KC_LEFT)
#define ARRDOWN  GUI_T(KC_DOWN)
#define ARRUP    SFT_T(KC_UP)
#define ARRRIGHT CTL_T(KC_RIGHT)


// increase readability 
# define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _DEF: Default Layer
   * ,-----------------------------------------------------------.
   * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =| \ | ~ |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  F|  P|  G|  J|  L|  U|  Y|  :|  [|  ]| bspc|
   * |-----------------------------------------------------------|
   * |Ctrl   | A|  R|  S|  T|  D|  H|  N|  E|  I|  O|  '| Return |
   * |-----------------------------------------------------------|
   * |Sft       | Z|  X|  C|  V|  B|  K|  M|  ,|  .|  /|     Sft |
   * |-----------------------------------------------------------|
   * |    |Win |Alt |      Space/Fn0         |Alt |Win |     |   |
   * `-----------------------------------------------------------'
   */
  [_DEF] = KEYMAP_THILANGA(
    KC_ESC, 	KC_1,     KC_2, 	KC_3,   KC_4, 	KC_5, 	KC_6, 	KC_7, 	KC_8, 	KC_9, 		KC_0, 		KC_MINS, 	KC_EQL, 	KC_BSLS, 	KC_GRV, \
    KC_TAB, 	KC_Q, 		KC_W, 	KC_F, 	KC_P, 	KC_G, 	KC_J, 	KC_L, 	KC_U, 	KC_Y, 		KC_SCLN, 	KC_LBRC, 	KC_RBRC, 				    KC_BSPC, \
    KC_LCTRL, KC_A, 		KC_R, 	KC_S, 	KC_T, 	KC_D, 	KC_H, 	KC_N, 	KC_E, 	KC_I, 		KC_O, 		KC_QUOT, 							        KC_ENT, \
    KC_LSFT, 	KC_Z, 		KC_X, 	KC_C, 	KC_V, 	KC_B, 	KC_K, 	KC_M, 	KC_COMM,KC_DOT, 	KC_SLSH, 									   	          KC_RSFT, \
    KC_NO, 		KC_LGUI, 	KC_LALT, 									SPACEDUAL, 						ARRLEFT, ARRDOWN, ARRUP, ARRRIGHT	
    ),
   
  /* Keymap 1: F-and-vim Layer, modified with Space (by holding space)
   * ,-----------------------------------------------------------.
   * |Play| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12| |PrSc|
   * |-----------------------------------------------------------|
   * |Caps|  |Prev|Next|   |   |   |   |   |   |   |   |   | Del |
   * |-----------------------------------------------------------|
   * |   |   |Vol-|Vol+|Mute|Home|Left|Down|Right|Up|  |  |Return|
   * |-----------------------------------------------------------|
   * |    |   |   |   |   |   |   |   |   |    |   |   |    |    |
   * |-----------------------------------------------------------|
   * |    |Win |Alt |      Space/Fn0         | ML | MD | MU | MR |
   * `-----------------------------------------------------------'
   */
   
  [_SPC] = KEYMAP_THILANGA(
    KC_MPLY, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, KC_PSCR, \
    KC_CAPS, _______, KC_MPRV, KC_MNXT, _______, _______, _______, KC_PGUP,_______, KC_PGDOWN, _______, _______, _______, KC_DEL, \
    _______, _______, KC_VOLD, KC_VOLU, KC__MUTE, KC_HOME, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_END, _______, KC_ENT, \
    _______, _______, _______, _______, KC_SPACE, M(0), _______, _______, KC_MS_BTN1, KC_MS_BTN2, _______, _______, \
    _______, _______, _______, 								_______,KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT
    )
};
