#include <pebble.h>
#include "msg.h"
#include "../main.h"
#include "../config/cfg.h"

extern ClaySettings settings;

static void inbox_recieved_handler(DictionaryIterator *iter, void *ctx) {
    Tuple *hWidth_t = dict_find(iter, MESSAGE_KEY_HandWidthKey);
    if (hWidth_t) {
        settings.hand_width = hWidth_t->value->int32;
    }

    Tuple *sWidth_t = dict_find(iter, MESSAGE_KEY_SecondWidthKey);
    if (sWidth_t) {
        settings.second_width = sWidth_t->value->int32;
    }

    Tuple *bg_t = dict_find(iter, MESSAGE_KEY_BgBoolKey);
    if (bg_t) {
        settings.enable_bg = bg_t->value->int32 == 1;
    }

    Tuple *sec_t = dict_find(iter, MESSAGE_KEY_SecBoolKey);
    if (sec_t) {
        settings.enable_seconds = sec_t->value->int32 == 1;
    }

    Tuple *dotNum_t = dict_find(iter, MESSAGE_KEY_DotNumKey);
    if (dotNum_t) {
        settings.num_of_dots = atoi(dotNum_t->value->cstring);
    }

    Tuple *h_color_t = dict_find(iter, MESSAGE_KEY_HourColorKey);
    if (h_color_t) {
        settings.hour_color = GColorFromHEX(h_color_t->value->int32);
    }

    Tuple *m_color_t = dict_find(iter, MESSAGE_KEY_MinColorKey);
    if (m_color_t) {
        settings.min_color = GColorFromHEX(m_color_t->value->int32);
    }

    Tuple *dot_color_t = dict_find(iter, MESSAGE_KEY_DotColorKey);
    if (dot_color_t) {
        settings.dot_color = GColorFromHEX(dot_color_t->value->int32);
    }

    Tuple *s_color_t = dict_find(iter, MESSAGE_KEY_SecColorKey);
    if (s_color_t) {
        settings.sec_color = GColorFromHEX(s_color_t->value->int32);
    }

    Tuple *tick_color_t = dict_find(iter, MESSAGE_KEY_TickColorKey);
    if (tick_color_t) {
        settings.hour_tick_color = GColorFromHEX(tick_color_t->value->int32);
    }

    Tuple *dot_size_t = dict_find(iter, MESSAGE_KEY_HourTickSizeKey);
    if (dot_size_t) {
        settings.hour_tick_size = dot_size_t->value->int32;
    }
    Tuple *dot_type_t = dict_find(iter, MESSAGE_KEY_DotTypeKey);
    if (dot_type_t) {
        settings.dot_type = atoi(dot_type_t->value->cstring);
    }

    Tuple *flag_t = dict_find(iter, MESSAGE_KEY_FlagKey);
    if(flag_t) {
        settings.flag = atoi(flag_t->value->cstring);
    }

    save_settings();
    update_stuff();
}

void init_msg() {
    app_message_register_inbox_received(inbox_recieved_handler);
    app_message_open(256, 256);
}