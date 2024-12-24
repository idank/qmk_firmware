#include "aztec42.h"

enum keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
};

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif // CONSOLE_ENABLE

#    ifndef HK_MINIMUM_DEFAULT_DPI
#        define HK_MINIMUM_DEFAULT_DPI 400
#    endif // HK_MINIMUM_DEFAULT_DPI

#    ifndef HK_DEFAULT_DPI_CONFIG_STEP
#        define HK_DEFAULT_DPI_CONFIG_STEP 200
#    endif // HK_DEFAULT_DPI_CONFIG_STEP

#    ifndef HK_MINIMUM_SNIPING_DPI
#        define HK_MINIMUM_SNIPING_DPI 200
#    endif // HK_MINIMUM_SNIPING_DPI

#    ifndef HK_SNIPING_DPI_CONFIG_STEP
#        define HK_SNIPING_DPI_CONFIG_STEP 100
#    endif // HK_SNIPING_DPI_CONFIG_STEP

// Fixed DPI for drag-scroll.
#    ifndef HK_DRAGSCROLL_DPI
#        define HK_DRAGSCROLL_DPI 100
#    endif // HK_DRAGSCROLL_DPI

typedef union {
    uint32_t raw;
    struct {
        uint8_t pointer_default_dpi : 4; // 16 steps available.
        uint8_t pointer_sniping_dpi : 2; // 4 steps available.
        bool    is_dragscroll_enabled : 1;
        bool    is_sniping_enabled : 1;
        uint8_t pointer_scroll_buffer : 4; // 16 steps available.
    } __attribute__((packed));
} hk_config_t;

static hk_config_t g_hk_config = {0};

typedef struct {
    int pointing_device_last_x;
    int pointing_device_last_y;
    int pointing_device_last_v;
    int pointing_device_last_h;
} hk_state_t;

static hk_state_t g_hk_state = {0};

static void read_hk_config_from_eeprom(hk_config_t* config) {
    config->raw                   = eeconfig_read_kb();
    config->is_dragscroll_enabled = false;
    config->is_sniping_enabled    = false;
}

static void write_hk_config_to_eeprom(hk_config_t* config) {
    eeconfig_update_kb(config->raw);
}

static uint16_t get_pointer_default_dpi(hk_config_t* config) {
    return (uint16_t)config->pointer_default_dpi * HK_DEFAULT_DPI_CONFIG_STEP + HK_MINIMUM_DEFAULT_DPI;
}

static uint16_t get_pointer_sniping_dpi(hk_config_t* config) {
    return (uint16_t)config->pointer_sniping_dpi * HK_SNIPING_DPI_CONFIG_STEP + HK_MINIMUM_SNIPING_DPI;
}

static uint16_t get_pointer_scroll_buffer(hk_config_t* config) {
    const uint16_t v = (uint16_t)config->pointer_scroll_buffer * 8;
    return v > 0 ? v : 0;
}

static bool maybe_update_pointing_device_cpi(hk_config_t* config) {
    uint16_t desired_cpi = 0;
    if (config->is_dragscroll_enabled) {
        desired_cpi = HK_DRAGSCROLL_DPI;
        pointing_device_set_cpi(HK_DRAGSCROLL_DPI);
    } else if (config->is_sniping_enabled) {
        desired_cpi = get_pointer_sniping_dpi(config);
        pointing_device_set_cpi(desired_cpi);
    } else {
        desired_cpi = get_pointer_default_dpi(config);
        pointing_device_set_cpi(desired_cpi);
    }
    return true;
}

static void step_pointer_default_dpi(hk_config_t* config, bool forward) {
    const uint16_t old_dpi = config->pointer_default_dpi;
    config->pointer_default_dpi += forward ? 1 : -1;
    if (!maybe_update_pointing_device_cpi(config)) {
        config->pointer_default_dpi = old_dpi;
    }
}

static void step_pointer_sniping_dpi(hk_config_t* config, bool forward) {
    const uint16_t old_dpi = config->pointer_sniping_dpi;
    config->pointer_sniping_dpi += forward ? 1 : -1;
    if (!maybe_update_pointing_device_cpi(config)) {
        config->pointer_sniping_dpi = old_dpi;
    }
}

static void step_pointer_scroll_buffer(hk_config_t* config, bool forward) {
    if (config->pointer_scroll_buffer == 0 && !forward) {
        return;
    }
    config->pointer_scroll_buffer += forward ? 1 : -1;
}

uint16_t hk_get_pointer_default_dpi(void) {
    return get_pointer_default_dpi(&g_hk_config);
}

uint16_t hk_get_pointer_sniping_dpi(void) {
    return get_pointer_sniping_dpi(&g_hk_config);
}

uint16_t hk_get_pointer_scroll_buffer(void) {
    return get_pointer_scroll_buffer(&g_hk_config);
}

void hk_cycle_pointer_default_dpi_noeeprom(bool forward) {
    step_pointer_default_dpi(&g_hk_config, forward);
}

void hk_cycle_pointer_default_dpi(bool forward) {
    step_pointer_default_dpi(&g_hk_config, forward);
    write_hk_config_to_eeprom(&g_hk_config);
}

void hk_cycle_pointer_sniping_dpi_noeeprom(bool forward) {
    step_pointer_sniping_dpi(&g_hk_config, forward);
}

void hk_cycle_pointer_sniping_dpi(bool forward) {
    step_pointer_sniping_dpi(&g_hk_config, forward);
    write_hk_config_to_eeprom(&g_hk_config);
}

void hk_cycle_pointer_scroll_buffer(bool forward) {
    step_pointer_scroll_buffer(&g_hk_config, forward);
    write_hk_config_to_eeprom(&g_hk_config);
}

bool hk_get_pointer_sniping_enabled(void) {
    return g_hk_config.is_sniping_enabled;
}

void hk_set_pointer_sniping_enabled(bool enable) {
    g_hk_config.is_sniping_enabled = enable;
    maybe_update_pointing_device_cpi(&g_hk_config);
}

bool hk_get_pointer_dragscroll_enabled(void) {
    return g_hk_config.is_dragscroll_enabled;
}

void hk_set_pointer_dragscroll_enabled(bool enable) {
    g_hk_config.is_dragscroll_enabled = enable;
    maybe_update_pointing_device_cpi(&g_hk_config);
}

void pointing_device_init_kb(void) {
    maybe_update_pointing_device_cpi(&g_hk_config);
    pointing_device_init_user();
}

static void pointing_device_task_hk(report_mouse_t* mouse_report) {
    static int16_t scroll_buffer_x = 0;
    static int16_t scroll_buffer_y = 0;
    if (g_hk_config.is_dragscroll_enabled) {
#    ifdef HK_DRAGSCROLL_REVERSE_X
        scroll_buffer_x -= mouse_report->x;
#    else
        scroll_buffer_x += mouse_report->x;
#    endif // HK_DRAGSCROLL_REVERSE_X
#    ifdef HK_DRAGSCROLL_REVERSE_Y
        scroll_buffer_y -= mouse_report->y;
#    else
        scroll_buffer_y += mouse_report->y;
#    endif // HK_DRAGSCROLL_REVERSE_Y
        mouse_report->x = 0;
        mouse_report->y = 0;
        if (abs(scroll_buffer_x) > hk_get_pointer_scroll_buffer()) {
            mouse_report->h = scroll_buffer_x > 0 ? 1 : -1;
            scroll_buffer_x = 0;
        }
        if (abs(scroll_buffer_y) > hk_get_pointer_scroll_buffer()) {
            mouse_report->v = scroll_buffer_y > 0 ? 1 : -1;
            scroll_buffer_y = 0;
        }
    }
    else if (mouse_report->v != 0 || mouse_report->h != 0) {
        scroll_buffer_x += mouse_report->h;
        scroll_buffer_y += mouse_report->v;
        mouse_report->h = 0;
        mouse_report->v = 0;
        if (abs(scroll_buffer_x) > hk_get_pointer_scroll_buffer()) {
            mouse_report->h = scroll_buffer_x > 0 ? 1 : -1;
            scroll_buffer_x = 0;
        }
        if (abs(scroll_buffer_y) > hk_get_pointer_scroll_buffer()) {
            mouse_report->v = scroll_buffer_y > 0 ? 1 : -1;
            scroll_buffer_y = 0;
        }
    }
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    if (is_keyboard_master()) {
        pointing_device_task_hk(&mouse_report);
        mouse_report = pointing_device_task_user(mouse_report);
        if (mouse_report.x != 0 || mouse_report.y != 0 || mouse_report.v != 0 || mouse_report.h != 0) {
            g_hk_state.pointing_device_last_x = mouse_report.x;
            g_hk_state.pointing_device_last_y = mouse_report.y;
            g_hk_state.pointing_device_last_v = mouse_report.v;
            g_hk_state.pointing_device_last_h = mouse_report.h;
        }
    }
    return mouse_report;
}

static bool has_shift_mod(void) {
#        ifdef NO_ACTION_ONESHOT
    return mod_config(get_mods()) & MOD_MASK_SHIFT;
#        else
    return mod_config(get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;
#        endif // NO_ACTION_ONESHOT
}

static void debug_hk_config_to_console(hk_config_t* config) {
#    ifdef CONSOLE_ENABLE
    dprintf("(debug_hk) process_record_kb: config = {\n"
            "\traw = %ld,\n"
            "\t{\n"
            "\t\tis_dragscroll_enabled=%u\n"
            "\t\tis_sniping_enabled=%u\n"
            "\t\tdefault_dpi=%u\n"
            "\t\tsniping_dpi=%u\n"
            "\t}\n"
            "}\n",
            config->raw, config->is_dragscroll_enabled, config->is_sniping_enabled, config->pointer_default_dpi, config->pointer_sniping_dpi);
#    endif // CONSOLE_ENABLE
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_user(keycode, record)) {
        debug_hk_config_to_console(&g_hk_config);
        return false;
    }
    switch (keycode) {
        case POINTER_DEFAULT_DPI_FORWARD:
            if (record->event.pressed) {
                // Step backward if shifted, forward otherwise.
                hk_cycle_pointer_default_dpi(/* forward= */ !has_shift_mod());
            }
            break;
        case POINTER_DEFAULT_DPI_REVERSE:
            if (record->event.pressed) {
                // Step forward if shifted, backward otherwise.
                hk_cycle_pointer_default_dpi(/* forward= */ has_shift_mod());
            }
            break;
        case POINTER_SNIPING_DPI_FORWARD:
            if (record->event.pressed) {
                // Step backward if shifted, forward otherwise.
                hk_cycle_pointer_sniping_dpi(/* forward= */ !has_shift_mod());
            }
            break;
        case POINTER_SNIPING_DPI_REVERSE:
            if (record->event.pressed) {
                // Step forward if shifted, backward otherwise.
                hk_cycle_pointer_sniping_dpi(/* forward= */ has_shift_mod());
            }
            break;
        case POINTER_SCROLL_BUFFER_FORWARD:
            if (record->event.pressed) {
                // Step backward if shifted, forward otherwise.
                hk_cycle_pointer_scroll_buffer(/* forward= */ !has_shift_mod());
            }
            break;
        case POINTER_SCROLL_BUFFER_REVERSE:
            if (record->event.pressed) {
                // Step forward if shifted, backward otherwise.
                hk_cycle_pointer_scroll_buffer(/* forward= */ has_shift_mod());
            }
            break;
        case SNIPING_MODE:
            hk_set_pointer_sniping_enabled(record->event.pressed);
            break;
        case SNIPING_MODE_TOGGLE:
            if (record->event.pressed) {
                hk_set_pointer_sniping_enabled(!hk_get_pointer_sniping_enabled());
            }
            break;
        case DRAGSCROLL_MODE:
            hk_set_pointer_dragscroll_enabled(record->event.pressed);
            break;
        case DRAGSCROLL_MODE_TOGGLE:
            if (record->event.pressed) {
                hk_set_pointer_dragscroll_enabled(!hk_get_pointer_dragscroll_enabled());
            }
            break;
    }
    debug_hk_config_to_console(&g_hk_config);
    if (IS_QK_KB(keycode) || IS_MOUSEKEY(keycode)) {
        debug_hk_config_to_console(&g_hk_config);
    }
    return true;
}

void eeconfig_init_kb(void) {
    g_hk_config.raw                 = 0;
    g_hk_config.pointer_default_dpi = 3;
    g_hk_config.pointer_scroll_buffer = 0;
    write_hk_config_to_eeprom(&g_hk_config);
    maybe_update_pointing_device_cpi(&g_hk_config);
    eeconfig_init_user();
}

void matrix_init_kb(void) {
    read_hk_config_from_eeprom(&g_hk_config);
    matrix_init_user();
}

#ifdef OLED_ENABLE
static void oled_render_mouse_state(void) {
    oled_write_ln_P(PSTR(" "), false);
    char coordinates[100];
    sprintf(coordinates, "   x%+02d y%+02d v%+02d h%+02d", g_hk_state.pointing_device_last_x, g_hk_state.pointing_device_last_y, g_hk_state.pointing_device_last_v, g_hk_state.pointing_device_last_h);
    oled_write_ln(coordinates, false);
}

static void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case LAYER_BASE:
            oled_write_ln_P(PSTR("BASE"), false);
            break;
        case LAYER_LOWER:
            oled_write_ln_P(PSTR("LOWER"), false);
            break;
        case LAYER_RAISE:
            oled_write_ln_P(PSTR("RAISE"), false);
            break;
        case LAYER_POINTER:
            oled_write_ln_P(PSTR("POINTER"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
            break;
    }
    oled_write_P(PSTR("Mouse: "), false);
    char num[100];
    sprintf(num, "%04d", hk_get_pointer_default_dpi());
    oled_write(num, !hk_get_pointer_sniping_enabled());
    oled_write_char('/', false);
    sprintf(num, "%03d", hk_get_pointer_sniping_dpi());
    oled_write(num, hk_get_pointer_sniping_enabled());
    oled_write_char('/', false);
    sprintf(num, "%d", hk_get_pointer_scroll_buffer());
    oled_write_ln(num, false);
    oled_render_mouse_state();
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
     oled_render_layer_state();
    return false;
}
#endif // OLED_ENABLE
