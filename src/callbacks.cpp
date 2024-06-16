//Gestion des event handlers (=>Actions utilisateur sur interaction avec les widgets)
#include "callbacks.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <lvgl.h>
#include <RDA5807M.h>

extern RDA5807M radioFM;
extern float freqFM;
extern int volFM;
extern lv_obj_t *text_area;

//Gestion du débordement vers le haut et le bas de la fréquence FM
void freqInRange(float freq) {
    if (freq < 87500.0) {
        freq = 108000.0;
    } else if (freq > 108000.0) {
        freq = 87500.0;
    }
    radioFM.Frequency(freq / 1000);
}

void seekup_event_handler(lv_event_t *e) {
    printf("seek up\n");
    radioFM.SeekUp();
}

void seekdown_event_handler(lv_event_t *e) {
    printf("seek down\n");
    radioFM.SeekDown();
}

void volup_event_handler(lv_event_t *e) {
    printf("volume+ %d \n", volFM);
    volFM = std::min(volFM + 1, 15);
    radioFM.Volume(volFM);
}

void voldown_event_handler(lv_event_t *e) {
    printf("volume- %d \n", volFM);
    volFM = std::max(volFM - 1, 0);
    radioFM.Volume(volFM);
}

void statup_event_handler(lv_event_t *e) {
    freqInRange(radioFM.freq + 100.0);
}

void statdown_event_handler(lv_event_t *e) {
    freqInRange(radioFM.freq - 100.0);
}


void keypad_event_handler(lv_event_t *e) {
    lv_obj_t *btnm = lv_event_get_target(e);
    uint16_t btn_id = lv_btnmatrix_get_selected_btn(btnm);
    const char *txt = lv_btnmatrix_get_btn_text(btnm, btn_id);

    if (strcmp(txt, "OK") == 0) {
        const char *freq_str = lv_textarea_get_text(text_area);
        float freq = atof(freq_str);
        if (freq >= 87.5 && freq <= 108.5) {
            radioFM.Frequency(freq);
        } else {
            lv_textarea_set_text(text_area, "");
        }
        lv_textarea_set_text(text_area, "");
    } else {
        lv_textarea_add_text(text_area, txt);
    }
}
