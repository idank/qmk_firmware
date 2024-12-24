
#pragma once

#include "quantum.h"

enum hk_keycodes {
    POINTER_DEFAULT_DPI_FORWARD = QK_KB_0,
    POINTER_DEFAULT_DPI_REVERSE,
    POINTER_SNIPING_DPI_FORWARD,
    POINTER_SNIPING_DPI_REVERSE,
    POINTER_SCROLL_BUFFER_FORWARD,
    POINTER_SCROLL_BUFFER_REVERSE,
    SNIPING_MODE,
    SNIPING_MODE_TOGGLE,
    DRAGSCROLL_MODE,
    DRAGSCROLL_MODE_TOGGLE,
};

#define DPI_MOD POINTER_DEFAULT_DPI_FORWARD
#define DPI_RMOD POINTER_DEFAULT_DPI_REVERSE
#define S_D_MOD POINTER_SNIPING_DPI_FORWARD
#define S_D_RMOD POINTER_SNIPING_DPI_REVERSE
#define SBUF_MOD POINTER_SCROLL_BUFFER_FORWARD
#define SBUF_RMOD POINTER_SCROLL_BUFFER_REVERSE
#define SNIPING SNIPING_MODE
#define SNP_TOG SNIPING_MODE_TOGGLE
#define DRGSCRL DRAGSCROLL_MODE
#define DRG_TOG DRAGSCROLL_MODE_TOGGLE

uint16_t hk_get_pointer_default_dpi(void);

void hk_cycle_pointer_default_dpi(bool forward);

void hk_cycle_pointer_default_dpi_noeeprom(bool forward);

uint16_t hk_get_pointer_sniping_dpi(void);

void hk_cycle_pointer_sniping_dpi(bool forward);

void hk_cycle_pointer_sniping_dpi_noeeprom(bool forward);

uint16_t hk_get_pointer_scroll_buffer(void);

void hk_cycle_pointer_scroll_buffer(bool forward);


bool hk_get_pointer_sniping_enabled(void);

void hk_set_pointer_sniping_enabled(bool enable);

bool hk_get_pointer_dragscroll_enabled(void);

void hk_set_pointer_dragscroll_enabled(bool enable);
