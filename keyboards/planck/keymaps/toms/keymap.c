/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "muse.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[_QWERTY] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,       KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,       KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,       KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_BSPC,  S(KC_SPC),  RAISE,   KC_RGUI, KC_RALT, KC_RCTL, XXXXXXX
),

[_COLEMAK] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,     KC_J,       KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    KC_TAB,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,     KC_H,       KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_K,       KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT,
    XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_BSPC,  S(KC_SPC),  RAISE,   KC_RGUI, KC_RALT, KC_RCTL, XXXXXXX
),

[_LOWER] = LAYOUT_planck_grid(
    _______, G(KC_Q),  G(KC_W), G(KC_F), G(KC_R), G(KC_T), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_MINS, KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_EQL,
    XXXXXXX, KC_UNDO,  KC_CUT,  KC_COPY, KC_PSTE, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______,
    _______, _______,  _______, _______, _______, _______, KC_UNDS, _______, _______, _______, _______, _______
),


[_RAISE] = LAYOUT_planck_grid(
    _______, XXXXXXX, XXXXXXX, S(KC_LBRC), KC_LBRC, S(KC_0), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, S(KC_RBRC), KC_RBRC, S(KC_9), XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
    XXXXXXX, _______, _______,    _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______,    _______, _______, KC_DEL,  _______, _______, _______, _______, _______, _______
),

[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   DEBUG,   _______, _______, _______, _______, _______, _______,  _______, _______, _______,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK,  _______, _______, _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_DOWN);
        unregister_code(KC_MS_WH_DOWN);
      #else
        register_code(KC_PGDN);
        unregister_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_UP);
        unregister_code(KC_MS_WH_UP);
      #else
        register_code(KC_PGUP);
        unregister_code(KC_PGUP);
      #endif
    }
  }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_song);
        #endif
        layer_on(_ADJUST);
      } else {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_ADJUST);
      }
      break;
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
        #ifdef AUDIO_ENABLE
          stop_all_notes();
        #endif
      }
   }
}

void matrix_scan_user(void) {
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}