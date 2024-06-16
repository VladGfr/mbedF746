//Création et configuration de tous les widgets présent sur l'écran LCD
#include "widgets.h"
#include "callbacks.h"
#include "bg_wood.c"
#include <lvgl.h>

lv_obj_t *freq_label_bg;
lv_obj_t *station_label_bg;
lv_obj_t *freq_label;
lv_obj_t *station_label;
lv_obj_t *meter;
lv_obj_t *meter_vol;
lv_meter_indicator_t *indic_vol;
lv_meter_indicator_t *indic;
lv_obj_t *text_area;

void createAllWidgets() {
       //Creation fond image
    lv_obj_t *fond = lv_img_create(lv_scr_act());
    lv_img_set_src(fond, &bg_wood);
    lv_obj_set_size(fond, LV_HOR_RES, LV_VER_RES);
    lv_obj_align(fond, LV_ALIGN_CENTER, 0, 0);
    lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_SCROLLABLE); //fond non défilable

    //Creation style pour fond LCD
    static lv_style_t style_lcd_bg;
    lv_style_init(&style_lcd_bg);

    //Creation style pour label frequence
    static lv_style_t style_lcd_rouge;
    lv_style_init(&style_lcd_rouge);
    lv_style_set_text_font(&style_lcd_rouge, &lcdfont_32);
    lv_style_set_text_color(&style_lcd_rouge, lv_color_hex(0xFF0000));

    //Creation boutons +/-100khz
    lv_obj_t * statup_btn = lv_btn_create(lv_scr_act());
    lv_obj_align(statup_btn, LV_ALIGN_BOTTOM_LEFT, 75, -60);
    lv_obj_t * statup_label = lv_label_create(statup_btn);
    lv_label_set_text(statup_label, LV_SYMBOL_RIGHT);
    lv_obj_center(statup_label);
    lv_obj_add_event_cb(statup_btn, statup_event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t * statdown_btn = lv_btn_create(lv_scr_act());
    lv_obj_align(statdown_btn, LV_ALIGN_BOTTOM_LEFT, 25, -60);
    lv_obj_t * statdown_label = lv_label_create(statdown_btn);
    lv_label_set_text(statdown_label, LV_SYMBOL_LEFT);
    lv_obj_center(statdown_label);
    lv_obj_add_event_cb(statdown_btn, statdown_event_handler, LV_EVENT_CLICKED, NULL);

    //Creation boutons seekup/down
    lv_obj_t * seekup_btn = lv_btn_create(lv_scr_act());
    lv_obj_align(seekup_btn, LV_ALIGN_BOTTOM_LEFT, 75, -20);
    lv_obj_t * seekup_label = lv_label_create(seekup_btn);
    lv_label_set_text(seekup_label, LV_SYMBOL_NEXT);
    lv_obj_center(seekup_label);
    lv_obj_add_event_cb(seekup_btn, seekup_event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t * seekdown_btn = lv_btn_create(lv_scr_act());
    lv_obj_align(seekdown_btn, LV_ALIGN_BOTTOM_LEFT, 22, -20);
    lv_obj_t * seekdown_label = lv_label_create(seekdown_btn);
    lv_label_set_text(seekdown_label, LV_SYMBOL_PREV);
    lv_obj_center(seekdown_label);
    lv_obj_add_event_cb(seekdown_btn, seekdown_event_handler, LV_EVENT_CLICKED, NULL);

    //Creation boutons volup/down
    lv_obj_t * volup_btn = lv_btn_create(lv_scr_act());
    lv_obj_align(volup_btn, LV_ALIGN_TOP_RIGHT, -20, 10);
    lv_obj_t * volup_label = lv_label_create(volup_btn);
    lv_label_set_text(volup_label, LV_SYMBOL_VOLUME_MAX);
    lv_obj_center(volup_label);
    lv_obj_add_event_cb(volup_btn, volup_event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t * voldown_btn = lv_btn_create(lv_scr_act());
    lv_obj_align(voldown_btn, LV_ALIGN_TOP_RIGHT, -20, 120);
    lv_obj_t * voldown_label = lv_label_create(voldown_btn);
    lv_label_set_text(voldown_label, LV_SYMBOL_VOLUME_MID);
    lv_obj_center(voldown_label);
    lv_obj_add_event_cb(voldown_btn, voldown_event_handler, LV_EVENT_CLICKED, NULL);


    //Creation meter frequence
    meter = lv_meter_create(lv_scr_act());
    lv_obj_set_size(meter, 300, 300);
    lv_obj_align(meter, LV_ALIGN_TOP_LEFT, -143, -143);
    // Scale frequency
    lv_meter_scale_t * scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_range(meter, scale, 108, 87, 90, 0);
    lv_meter_set_scale_ticks(meter, scale, 21, 2, 10, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(meter, scale, 5, 2, 20, lv_color_black(), 10);
    // Needle frequency
    indic = lv_meter_add_needle_line(meter, scale, 2, lv_palette_main(LV_PALETTE_RED), -10);

// Creation meter volume
    meter_vol = lv_meter_create(lv_scr_act());
    lv_obj_set_size(meter_vol, 200, 200);
    lv_obj_align(meter_vol, LV_ALIGN_BOTTOM_RIGHT, 95, 95);
    // Scale volume
    lv_meter_scale_t *scale_vol = lv_meter_add_scale(meter_vol);
    lv_meter_set_scale_range(meter_vol, scale_vol, 0, 15, 90, 180);
    lv_meter_set_scale_ticks(meter_vol, scale_vol, 16, 2, 10, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(meter_vol, scale_vol, 4, 2, 20, lv_color_black(), 10);
    // Needle volume
    indic_vol = lv_meter_add_needle_line(meter_vol, scale_vol, 2, lv_palette_main(LV_PALETTE_RED), -10);
    

    // Creation fond lcd frequence
    freq_label_bg = lv_obj_create(lv_scr_act());
    lv_obj_set_size(freq_label_bg, 200, 90); 
    lv_obj_align(freq_label_bg, LV_ALIGN_TOP_MID, 20, 0);
    lv_obj_set_style_bg_color(freq_label_bg, lv_color_hex(0x873a41), 0);

    // Creation fond lcd station
    station_label_bg = lv_obj_create(lv_scr_act());
    lv_obj_set_size(station_label_bg, 200, 45); 
    lv_obj_align(station_label_bg, LV_ALIGN_BOTTOM_MID, 20, 0);
    lv_obj_set_style_bg_color(station_label_bg, lv_color_hex(0x873a41), 0);

    // Creation texte frequence
    freq_label = lv_label_create(lv_scr_act());
    lv_obj_align_to(freq_label, freq_label_bg, LV_ALIGN_TOP_MID, -85, -5);
    lv_obj_add_style(freq_label, &style_lcd_rouge, 0);

    // Creation texte station
    station_label = lv_label_create(lv_scr_act());
    lv_obj_align(station_label, LV_ALIGN_BOTTOM_MID, 15, 20);
    lv_obj_add_style(station_label, &style_lcd_rouge, 0);

    // Creation keypad text area
    text_area = lv_textarea_create(lv_scr_act());
    lv_obj_set_width(text_area, 200);
    lv_textarea_set_one_line(text_area, true);
    lv_obj_align(text_area, LV_ALIGN_TOP_MID, 9, 40);
    lv_obj_add_style(text_area, &style_lcd_rouge, 0);
    lv_obj_set_style_border_width(text_area, 0, 0);
    lv_obj_set_style_bg_opa(text_area, LV_OPA_TRANSP, 0);
    

    // Creation Keypad
    static const char * btn_map[] = {"1", "2", "3", "\n",
                                     "4", "5", "6", "\n",
                                     "7", "8", "9", "\n",
                                     ".", "0", "OK", ""};

    lv_obj_t * keypad = lv_btnmatrix_create(lv_scr_act());
    lv_btnmatrix_set_map(keypad, btn_map);
    lv_obj_set_width(keypad, 200);
    lv_obj_set_height(keypad, 120);
    lv_obj_set_style_bg_opa(keypad, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(keypad, 0, 0);
    lv_obj_align(keypad, LV_ALIGN_CENTER, 17, 3);
    lv_obj_add_event_cb(keypad, keypad_event_handler, LV_EVENT_CLICKED, NULL);
}
