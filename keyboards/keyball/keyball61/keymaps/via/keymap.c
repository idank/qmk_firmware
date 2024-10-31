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

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "options.inl"

enum custom_keycodes {
    PFX = SAFE_RANGE,
    INSPE,
    INSPP,
    COPY
};

#include "macros.inl"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // DEFAULT
  [0] = LAYOUT(
    KC_ESC   , KC_1    , KC_2     , KC_3     , KC_4        , KC_5         ,                                     KC_6   , KC_7    , KC_8     , KC_9     , KC_0     , KC_MINS  ,
    KC_GRV   , KC_Q    , KC_W     , KC_E     , KC_R        , KC_T         ,                                     KC_Y   , KC_U    , KC_I     , KC_O     , KC_P     , KC_BSLS  ,
    KC_CAPS  , KC_A    , KC_S     , KC_D     , KC_F        , KC_G         ,                                     KC_H   , KC_J    , KC_K     , KC_L     , KC_SCLN  , KC_QUOT  ,
    KC_LSFT  , KC_Z    , KC_X     , KC_C     , KC_V        , KC_B         , KC_LBRC ,        KC_RBRC     ,      KC_N   , KC_M    , KC_COMM  , KC_DOT   , KC_SLSH  , KC_DEL   ,
    KC_LCTL  , COPY    , KC_LWIN  , KC_LALT  , LT(2,KC_SPC), LT(3,KC_TAB) , QK_KB_7 ,        LT(4,KC_ENT),LT(5,KC_BSPC),                                 TG(1)    , KC_INS
  ),

  // MOUSE
  [1] = LAYOUT(
    XXXXXXX  , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   ,                                   KC_F6     , KC_F7      , KC_F8      , KC_F9      , KC_F10     , KC_F11   ,
    XXXXXXX  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                   C(KC_A)   , C(KC_C)    , C(KC_V)    , C(KC_X)    , C(KC_Z)    , KC_F12   ,
    XXXXXXX  , KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT , TG(1)   ,                                   KC_BTN3   , KC_BTN1    , KC_BTN2    , XXXXXXX    , QK_KB_7    , QK_KB_13 ,
    _______  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,               XXXXXXX , QK_KB_6   , KC_HOME    , KC_PGDN    , KC_PGUP    , KC_END     , QK_KB_15 ,
    _______  , _______ , _______ , _______ , _______ , _______ , _______ ,               _______ , _______   ,                                        _______    , _______
  ),

  // L NAVIGATION & SCREENSHOT, R 10 KEY
  [2] = LAYOUT(
    PFX      , _______    , _______   , _______  ,_______    , _______  ,                                     KC_PEQL  , KC_P7    , KC_P8    , KC_P9    , KC_PSLS  , _______  ,
    INSPE    , XXXXXXX    ,LCA(KC_END), KC_UP    ,LCA(KC_DEL), XXXXXXX  ,                                     KC_PAST  , KC_P4    , KC_P5    , KC_P6    , KC_PPLS  , _______  ,
    INSPP    , XXXXXXX    , KC_LEFT   , KC_DOWN  ,KC_RIGHT   , XXXXXXX  ,                                     KC_PCMM  , KC_P1    , KC_P2    , KC_P3    , KC_PMNS  , _______  ,
    _______  , XXXXXXX    , XXXXXXX   , XXXXXXX  ,XXXXXXX    , XXXXXXX  , A(KC_F4)    ,            QK_KB_10 , KC_P0    , KC_P0    , XXXXXXX  , KC_DOT   , KC_PENT  , _______  ,
    _______  , _______    , _______   , _______  ,_______    , _______  , _______     ,            _______  , _______  ,                                  _______  , _______
  ),

  // RGB & MOUSE SETTINGS, BOOTLOADER, EEPROM CLEAR
  [3] = LAYOUT(
    _______  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , LSG(KC_S), _______  , _______  , _______  , _______  ,                                  CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE , KBC_RST  ,
    XXXXXXX  , _______  , SCRL_DVD , SCRL_DVI , SCRL_MO  , SCRL_TO  , EE_CLR   ,            EE_CLR   , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , _______  , _______  ,
    QK_BOOT  , _______  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , _______  ,            _______  , KC_BSPC  ,                                  _______  , _______
  ),
};
