#ifdef RGB_MATRIX_ENABLE

#define RGB_CyberYELLOW     0xFF, 0xE5, 0x00 // Cyberpunk 2077 yellow to match case RGB setup
#define RGB_CyberBLUE       RGB_CYAN         // Alias for myself to match case RGB setup

enum led_location_map {
    LED_ESC,  // 01, escape
    LED_F1,   // 02, f1
    LED_F2,   // 03, f2
    LED_F3,   // 04, f3
    LED_F4,   // 05, f4
    LED_F5,   // 06, f5
    LED_F6,   // 07, f6
    LED_F7,   // 08, f7
    LED_F8,   // 09, f8
    LED_F9,   // 10, f9
    LED_F10,  // 11, f10
    LED_F11,  // 12, f11
    LED_F12,  // 13, f12
    LED_PRT,  // 14, print screen
    LED_SCR,  // 15, scroll lock
    LED_PAU,  // 16, pause
    LED_GRV,  // 17, grave key
    LED_ONE,  // 18, 1
    LED_TWO,  // 19, 2
    LED_THR,  // 10, 3
    LED_FOU,  // 11, 4
    LED_FIV,  // 12, 5
    LED_SIX,  // 13, 6
    LED_SEV,  // 14, 7
    LED_EIG,  // 15, 8
    LED_NIN,  // 16, 9
    LED_ZER,  // 17, 0
    LED_HYP,  // 18, -
    LED_EQU,  // 19, =
    LED_BAK,  // 20, backspace
    LED_INS,  // 21, insert
    LED_HOM,  // 22, home
    LED_PGU,  // 23, page up
    LED_TAB,  // 24, tab
    LED_Q,    // 25
    LED_W,    // 26
    LED_E,    // 27
    LED_R,    // 28
    LED_T,    // 29
    LED_Y,    // 30
    LED_U,    // 31
    LED_I,    // 32
    LED_O,    // 33
    LED_P,    // 34
    LED_LBR,  // 35, left bracket
    LED_RBR,  // 46, right bracket
    LED_FSL,  // 47, forward slash/pipe
    LED_DEL,  // 48, delete
    LED_END,  // 49, end
    LED_PGD,  // 50, page down
    LED_CAP,  // 51, caps lock
    LED_A,    // 52
    LED_S,    // 53
    LED_D,    // 54
    LED_F,    // 55
    LED_G,    // 56
    LED_H,    // 57
    LED_J,    // 58
    LED_K,    // 59
    LED_L,    // 60
    LED_SEM,  // 61, semicolon
    LED_QUO,  // 62, quote
    LED_ENT,  // 63, enter
    LED_LSH,  // 64, left shift
    LED_Z,    // 65
    LED_X,    // 66
    LED_C,    // 67
    LED_V,    // 68
    LED_B,    // 69
    LED_N,    // 70
    LED_M,    // 71
    LED_COM,  // 72, comma
    LED_PER,  // 73, period
    LED_BSL,  // 74, back slash/question
    LED_RSH,  // 75, right shift
    LED_UAR,  // 76, up arrow
    LED_LCTR, // 77, left control
    LED_LWIN, // 78, left windows
    LED_LALT, // 79, left alt
    LED_SPAC, // 80, space bar
    LED_RALT, // 81, right alt
    LED_RFUN, // 82, right function key
    LED_RMEN, // 83, right menu key
    LED_RCTR, // 84, right control
    LED_LAR,  // 85, left arrow
    LED_DAR,  // 86, down arrow
    LED_RAR,  // 87, right arrow
    // outside LEDS - starts bottom right, goes clockwise outside
    LED_88,   // 88 -> next to right arrow
    LED_89,   // 89 -> below down arrow
    LED_90,   // 90 -> left of left arrow
    LED_91,   // 91 -> r ctrl/menu
    LED_92,   // 92 -> r fun/menu
    LED_93,   // 93 -> r alt
    LED_94,   // 94 -> out r space
    LED_95,   // 95 -> in r space
    LED_96,   // 96 -> in l space
    LED_97,   // 97 -> out l space
    LED_98,   // 98 -> l alt
    LED_99,   // 99 -> l windows
    LED_100,  // 100 -> l control
    LED_101,  // 101 -> l shift
    LED_102,  // 102 -> caps lock
    LED_103,  // 103 -> tab/grave
    LED_104,  // 104 -> escape
    LED_105,  // 105 -> esc/f1
    LED_106,  // 106 -> f1/f2
    LED_107,  // 107 -> f3
    LED_108,  // 108 -> f4/f5
    LED_109,  // 109 -> f5/f6
    LED_110,  // 110 -> f7
    LED_111,  // 111 -> f8/f9
    LED_112,  // 112 -> f10
    LED_113,  // 113 -> f11/f12
    LED_114,  // 114 -> f12/print screen
    LED_115,  // 115 -> scroll lock
    LED_116,  // 116 -> pause
    LED_117,  // 117 -> page up
    LED_118,  // 118 -> page down
    LED_119   // 119 -> up arrow
};

const uint8_t LED_LIST_OUTER[] = {
    LED_88,   // 88 -> next to right arrow
    LED_89,   // 89 -> below down arrow
    LED_90,   // 90 -> left of left arrow
    LED_91,   // 91 -> r ctrl/menu
    LED_92,   // 92 -> r fun/menu
    LED_93,   // 93 -> r alt
    LED_94,   // 94 -> out r space
    LED_95,   // 95 -> in r space
    LED_96,   // 96 -> in l space
    LED_97,   // 97 -> out l space
    LED_98,   // 98 -> l alt
    LED_99,   // 99 -> l windows
    LED_100,  // 100 -> l control
    LED_101,  // 101 -> l shift
    LED_102,  // 102 -> caps lock
    LED_103,  // 103 -> tab/grave
    LED_104,  // 104 -> escape
    LED_105,  // 105 -> esc/f1
    LED_106,  // 106 -> f1/f2
    LED_107,  // 107 -> f3
    LED_108,  // 108 -> f4/f5
    LED_109,  // 109 -> f5/f6
    LED_110,  // 110 -> f7
    LED_111,  // 111 -> f8/f9
    LED_112,  // 112 -> f10
    LED_113,  // 113 -> f11/f12
    LED_114,  // 114 -> f12/print screen
    LED_115,  // 115 -> scroll lock
    LED_116,  // 116 -> pause
    LED_117,  // 117 -> page up
    LED_118,  // 118 -> page down
    LED_119   // 119 -> up arrow
};

const uint8_t LED_FUNC_KEYS[] = {
    LED_ESC,  // 01, escape
    LED_F1,   // 02, f1
    LED_F2,   // 03, f2
    LED_F3,   // 04, f3
    LED_F4,   // 05, f4
    LED_F5,   // 06, f5
    LED_F6,   // 07, f6
    LED_F7,   // 08, f7
    LED_F8,   // 09, f8
    LED_F9,   // 10, f9
    LED_F10,  // 11, f10
    LED_F11,  // 12, f11
    LED_F12   // 13, f12
};

#endif
