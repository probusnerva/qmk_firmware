 /* Copyright 2020 gtips
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



/*Begin Default code

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_reviung41(
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,      KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  RSFT_T(KC_ENT),
                                            KC_LALT,   LOWER,    KC_SPC,   RAISE,    KC_RGUI
  ),
  
  [_LOWER] = LAYOUT_reviung41(
    _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,    KC_PERC,            KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_DEL,
    _______,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,   KC_PIPE,            KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_GRV,   KC_TILD,
    _______,  KC_ESC,   KC_LGUI,  KC_LALT,  KC_CAPS,   KC_DQUO,            KC_HOME,  KC_END,   KC_PGUP,  KC_PGDN,  KC_PSCR,  RSFT_T(KC_SPC),
                                            _______,   _______,  KC_ENT,   _______,  _______
  ),
  
  [_RAISE] = LAYOUT_reviung41(
    _______,  KC_1,     KC_2,     KC_3,     KC_4,      KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_DEL,
    _______,  KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,   KC_BSLS,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,
    _______,  KC_ESC,   KC_RGUI,  KC_RALT,  KC_CAPS,   KC_QUOT,            KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
                                            _______,   _______,  KC_BSPC,  _______,  _______
  ),
  
  [_ADJUST] = LAYOUT_reviung41(
    RGB_VAI,   RGB_SAI, RGB_HUI,  RGB_MOD,  XXXXXXX,   RGB_TOG,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            RESET,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                            _______,   _______,  XXXXXXX,  _______,  _______
  ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


//  END DEFAULT CODE...
*/ 






/*

8/15/2020 NEEED TO MODIFY NAVIGATION LAYER to add missing function keys (CAPSLOCK, insert/delete, home/end, print screen/insert...user defined function keys!!!!...) to left hand side
   TODO:
      MOD NAVIGATION LAYER
      MOD ADJUST LAYER
      
8/14/2020 Revuing Status... import crkbd keymap and attempt to utilize functionality from the crkbd backlighting and layout without major modifications... 
currently only update removed the left hand space bar and will test for functionality.

Note on past Notes: nav
11/04/2019 Status:
---Navigation layer redefined while chasing down problem with layer titling... ERROR found in read_layer_state.c and corrected. Attempts were made to work around readlayerstate, but were unsuccessful.
------Navigation layer is now functional, and displays properly whilst switching between layers.
---Next progect will be to implement dual layer update with layout on oled screens... while this might be pointless with the slave oled... it is worth a shot. we will see..... wish me luck.

10/24/2019 Status:
Nav layer functional with space bar mod.
Left layer key for numbers and right handed function key... but It seems it would be better to have either one layer for single handed modes... IE Nav Left/Nav right
Right alt layer holds function keys on q-t:a-g and b with f12 on n, and undo, cut, copy, and paste on z,x,c,v respectively.


Current Issues:
1. Nav layer is not title is not sent to display during toggle. Unknown condition creating, but assume it must be outside of keymap.c
2. Explore hand defined layers, instead of the shifted 'raise' and 'lower' as standard.  
3. explore num pad layer for right hand with symbols/functions on the left///
4. One thought, combine left/right (raise/lower), and place Nav on Raise... this would allow for the title to be sent to display during toggle. 
5. right thumb cluster::::::: NAV/space:Raise:Number(toggle on/off)
6. missing windows call key.... ulg...gqQ     

*/


#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
//  #include "split_util.h"
#endif

// adding oled functionality.. not needed at this moment, but might add eveentually.. if determinied appropriate.
// #ifdef SSD1306OLED
//  #include "ssd1306.h"
//#endif
             
extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _NAVIGATE 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST,
  NAVIGATE
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//User defined variables for ease of viewing
#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_NAVIGATE  LT(_NAVIGATE,KC_SPC)
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD

//Custom Modifier Definitions:
#define KC_CTLESC LCTL_T(KC_ESC)
#define KC_SFTUP  LSFT_T(KC_PGUP)
#define KC_SFTDN  RSFT_T(KC_PGDN)
#define KC_CTLQT  RCTL_T(KC_QUOT)
#define KC_SHENT  RSFT_T(KC_ENT)
//Thumb Cluster Definitions:
//#define KC_SPAV   LT(_NAVIGATE,KC_SPC)
#define KC_SPAD   LT(KC_SPC, KC_BSPC)
//Special Mod combo Definitions:
#define KC_SHCTL  RCTL(KC_RSFT)
#define KC_AMEN   ALT_T(KC_APP)
#define KC_FUNDO  LCTL(KC_Z)
#define KC_FUCT   LCTL(KC_X)
#define KC_FUST   LCTL(KC_V)
#define KC_FUPY   LCTL(KC_C)
//Unused definitions:remnants of keymaps once forgotten..
#define KC_GUIEI  GUI_T(KC_LANG2)
#define KC_ALTKN  ALT_T(KC_LANG1)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_reviung41( \
  //,-----------------------------------------.                ,-----------------------------------------.
        KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  KC_BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     KC_CTLESC,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                      KC_H,     KC_J,     KC_K,     KC_L,  KC_SCLN, KC_CTLQT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      KC_SFTUP,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                      KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH, KC_SHENT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   KC_AMEN, KC_LOWER , KC_NAVIGATE, KC_RAISE, KC_LGUI \
                              //`--------------------'  `--------------------'   
  ),

  [_RAISE] = LAYOUT_reviung41( \
  //,-----------------------------------------.                ,-----------------------------------------.
        KC_TAB,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,  KC_BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     KC_CTLESC,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                     KC_F6,  KC_MINS,  KC_EQL ,  KC_LBRC,  KC_RBRC,  KC_BSLS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       KC_SFTUP,   KC_F7,   KC_F8 ,   KC_F9 ,   KC_F10 ,  KC_F11,                    KC_F12,  KC_BSLS,  KC_BSLS, KC_PGUP ,  KC_PGDN, _______,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   KC_AMEN, KC_LOWER, KC_NAVIGATE, KC_RAISE,  _______ \
                              //`--------------------'  `--------------------'}
  ),

  [_LOWER] = LAYOUT_reviung41( \
  //,-----------------------------------------.                ,-----------------------------------------.
        KC_TAB,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                   KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        KC_DEL,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,                     KC_F6,  KC_MINS,   KC_EQL,  KC_LCBR,  KC_RCBR,  KC_BSLS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      KC_SFTUP, KC_FUNDO,  KC_FUCT,  KC_FUPY,  KC_FUST,   KC_F11,                    KC_F12,  KC_BSLS,  KC_BSLS,  KC_HOME,   KC_END, KC_SHENT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   KC_AMEN, KC_LOWER, KC_NAVIGATE, KC_RAISE,  _______ \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_reviung41( \
  //,-----------------------------------------.                ,-----------------------------------------.
        KC_RST,  KC_LRST, KC_XXXXX, KC_XXXXX, KC_XXXXX, KC_XXXXX,                  KC_7, KC_8, KC_9, KC_MINS, _______, _______,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       KC_LTOG,  KC_LHUI,  KC_LSAI,  KC_LVAI, KC_XXXXX, KC_XXXXX,                  KC_4, KC_5, KC_6, KC_PLUS, _______, _______,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       KC_LMOD,  KC_LHUD,  KC_LSAD,  KC_LVAD, KC_XXXXX, KC_XXXXX,                  KC_1, KC_2, KC_3, KC_ASTR, _______, _______,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   KC_AMEN, KC_LOWER, KC_ENT, KC_0, KC_DOT \
                              //`--------------------'  `--------------------'
  ),

    [_NAVIGATE] = LAYOUT_reviung41( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _______, _______, _______, _______, _______, _______,                  KC_HOME , KC_PGUP , KC_PGDN , KC_END  , KC_MENU ,  KC_BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _______, _______, _______, _______, _______, _______,                  KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , KC_SHCTL, _______,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _______, _______, _______, _______, _______, _______,                  KC_FUNDO, KC_FUPY , KC_FUST , KC_FUNDO,  KC_LGUI, _______,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   KC_AMEN, KC_LOWER, KC_NAVIGATE, KC_RAISE, _______ \
                              //`--------------------'  `--------------------'
  )

};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
          break;
    case NAVIGATE:
      if (record->event.pressed) {
          layer_on(_NAVIGATE);
        } else {
          layer_off(_NAVIGATE);
        }
      return false;
          break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}





//.json import for update and ease of viewing
//[0] = LAYOUT(
//KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, 
//LCTL_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, RCTL_T(KC_QUOT), 
//LSFT_T(KC_PGUP), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_ENT), 
//KC_LALT, LT(_LOWER,KC_LGUI), KC_SPC, LT(_NAV,KC_SPC), LT(_RAISE,KC_APP), LALT_T(KC_LANG1)
//),
//  [1] = LAYOUT(
//KC_TAB, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, 
//LCTL_T(KC_ESC), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, 
//KC_LSFT, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_BSLS, KC_BSLS, KC_PGUP, KC_PGDN, KC_TRNS, 
//KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
//),
//  [2] = LAYOUT(
//KC_TAB, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL, 
//LCTL_T(KC_ESC), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, 
//KC_LSFT, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NUHS, KC_BSLS, KC_PGUP, KC_PGDN, KC_TRNS, 
//KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
//),
//  [3] = LAYOUT(
//RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_PWR, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
//RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
//RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
//KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
//),
//  [4] = LAYOUT(
//KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGUP, KC_PGDN, KC_END, KC_MENU, KC_BSPC, 
//KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, RCTL(KC_RSFT), KC_TRNS, 
//KC_TRNS, KC_TRNS, KC_MAIL, KC_CALC, KC_TRNS, KC_MAIL, KC_COPY, KC_PSTE, KC_CUT, KC_UNDO, LALT(KC_TAB), KC_TRNS, 
//KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
//)klkjkkkkkkk