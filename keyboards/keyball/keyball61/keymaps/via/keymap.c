/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

Keyball Keycodes -- https://github.com/Yowkees/keyball/blob/main/qmk_firmware/keyboards/keyball/lib/keyball/keycodes.md#english
QMK Basic Keycodes -- https://docs.qmk.fm/keycodes_basic
QMK Advanced Keycodes -- https://docs.qmk.fm/feature_advanced_keycodes
*/

// qmk compile -kb keyball/keyball61 -km via
// qmk flash -kb keyball/keyball61 -km via

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "rgblight.h"

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

enum custom_keycodes {
    PFX = SAFE_RANGE,
    INSPE,
    INSPP,
    COPY
};

// Creating layer aliases
#define DEFAULT_LAYER 0
#define MOUSE_LAYER 1
#define TENKEY_LAYER 2
#define FUNCTION_LAYER 3

// Creating HSV color aliases
#define HSV_CyberYELLOW     25, 255, 255
#define HSV_CyberBLUE       HSV_CYAN

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [DEFAULT_LAYER] = LAYOUT(
    KC_ESC   , KC_1    , KC_2     , KC_3     , KC_4        , KC_5         ,                                     KC_6   , KC_7    , KC_8     , KC_9     , KC_0     , KC_MINS  ,
    KC_GRV   , KC_Q    , KC_W     , KC_E     , KC_R        , KC_T         ,                                     KC_Y   , KC_U    , KC_I     , KC_O     , KC_P     , KC_BSLS  ,
    KC_CAPS  , KC_A    , KC_S     , KC_D     , KC_F        , KC_G         ,                                     KC_H   , KC_J    , KC_K     , KC_L     , KC_SCLN  , KC_QUOT  ,
    KC_LSFT  , KC_Z    , KC_X     , KC_C     , KC_V        , KC_B         , KC_LBRC ,        KC_RBRC     ,      KC_N   , KC_M    , KC_COMM  , KC_DOT   , KC_SLSH  , KC_DEL   ,
    KC_LCTL  , COPY    , KC_LWIN  , KC_LALT  , LT(2,KC_SPC), LT(3,KC_TAB) , SCRL_MO ,        LT(4,KC_ENT),LT(5,KC_BSPC),                                 TG(1)    , KC_INS
  ),

  [MOUSE_LAYER] = LAYOUT(
    XXXXXXX  , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   ,                                   KC_F6     , KC_F7      , KC_F8      , KC_F9      , KC_F10     , KC_F11   ,
    XXXXXXX  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                   C(KC_A)   , C(KC_C)    , C(KC_V)    , C(KC_X)    , C(KC_Z)    , KC_F12   ,
    XXXXXXX  , KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT , XXXXXXX ,                                   KC_BTN3   , KC_BTN1    , KC_BTN2    , XXXXXXX    , QK_KB_7    , QK_KB_13 ,
    _______  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,               XXXXXXX , QK_KB_6   , KC_HOME    , KC_PGDN    , KC_PGUP    , KC_END     , QK_KB_15 ,
    _______  , _______ , _______ , _______ , _______ , _______ , _______ ,               _______ , _______   ,                                        _______    , _______
  ),

  [TENKEY_LAYER] = LAYOUT(
    PFX      , _______    , _______   , _______  ,_______    , _______  ,                                     KC_PEQL  , KC_P7    , KC_P8    , KC_P9    , KC_PSLS  , _______  ,
    INSPE    , XXXXXXX    ,LCA(KC_END), KC_UP    ,LCA(KC_DEL), XXXXXXX  ,                                     KC_PAST  , KC_P4    , KC_P5    , KC_P6    , KC_PPLS  , _______  ,
    INSPP    , XXXXXXX    , KC_LEFT   , KC_DOWN  ,KC_RIGHT   , XXXXXXX  ,                                     KC_PCMM  , KC_P1    , KC_P2    , KC_P3    , KC_PMNS  , _______  ,
    _______  , XXXXXXX    , XXXXXXX   , XXXXXXX  ,XXXXXXX    , XXXXXXX  , A(KC_F4)    ,            QK_KB_10 , KC_P0    , KC_P0    , XXXXXXX  , KC_DOT   , KC_PENT  , _______  ,
    _______  , _______    , _______   , _______  ,_______    , _______  , _______     ,            _______  , _______  ,                                  _______  , _______
  ),

  [FUNCTION_LAYER] = LAYOUT(
    _______  , AML_TO   , AML_I50  , AML_D50  , _______  , KBC_SAVE ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , LSG(KC_S), _______  , _______  , _______  , _______  ,                                  CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE , KBC_RST  ,
    XXXXXXX  , _______  , SCRL_DVD , SCRL_DVI , SCRL_MO  , SCRL_TO  , EE_CLR   ,            EE_CLR   , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , _______  , _______  ,
    QK_BOOT  , _______  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , _______  ,            _______  , KC_BSPC  ,                                  _______  , _______
  ),
};

void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
    set_auto_mouse_layer(MOUSE_LAYER);
}

void keyboard_post_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
    rgblight_sethsv(HSV_RED);
    rgblight_mode(1);
    #endif
}

// clang-format on
layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);

    uint8_t layer = biton32(state);

    #ifdef RGBLIGHT_ENABLE
    switch(layer) {
        case DEFAULT_LAYER:
            rgblight_sethsv(HSV_RED);
            break;
        case MOUSE_LAYER:
            rgblight_sethsv(HSV_WHITE);
            break;
        case TENKEY_LAYER:
            rgblight_sethsv(HSV_CyberBLUE);
            break;
        case FUNCTION_LAYER:
            rgblight_sethsv(HSV_CyberYELLOW);
            break;
    }
    #endif

    return state;
}

// ***************** RGB TIMEOUT *****************

#ifdef RGBLIGHT_ENABLE
static uint32_t key_timer;           // timer for last keyboard activity, use 32bit value and function to make longer idle time possible
static void refresh_rgb(void);       // refreshes the activity timer and RGB, invoke whenever any activity happens
static void check_rgb_timeout(void); // checks if enough time has passed for RGB to timeout
bool is_rgb_timeout = false;         // store if RGB has timed out or not in a boolean

void refresh_rgb(void) {
    key_timer = timer_read32(); // store time of last refresh
    if (is_rgb_timeout)
    {
        is_rgb_timeout = false;
        rgblight_wakeup();
    }
}

void check_rgb_timeout(void) {
    if (!is_rgb_timeout && timer_elapsed32(key_timer) > RGBLIGHT_TIMEOUT) // check if RGB has already timeout and if enough time has passed
    {
        rgblight_suspend();
        is_rgb_timeout = true;
    }
}

/* Then, call the above functions from QMK's built in post processing functions like so */
/* Runs at the end of each scan loop, check if RGB timeout has occured or not */
void housekeeping_task_user(void) {
#ifdef RGBLIGHT_TIMEOUT
    check_rgb_timeout();
#endif
}

/* Runs after each key press, check if activity occurred */
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef RGBLIGHT_TIMEOUT
    if (record->event.pressed)
        refresh_rgb();
#endif
}

/* Runs after each encoder tick, check if activity occurred */
void post_encoder_update_user(uint8_t index, bool clockwise) {
#ifdef RGBLIGHT_TIMEOUT
    refresh_rgb();
#endif
}
#endif
