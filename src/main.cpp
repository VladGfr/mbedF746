#include <mbed.h>
#include <threadLvgl.h>
#include <RDA5807M.h>
#include "widgets.h"    //contient toutes les creation de widget
#include "callbacks.h" //contient tous les callbacks des widgets

ThreadLvgl threadLvgl(30);      //Initialisation du thread de MàJ et rendu LVGL
DigitalOut led(A0);             //led rouge
RDA5807M radioFM(D14, D15);     //on initialise radioFM sur les broches D14 et D15 (SDA/SCL)
float freqFM = 87.5;            //valeurs par défaut au démarrage
int volFM = 7;                  //

int main() {
    threadLvgl.lock();          //On lock et unlock le thread à chaque MàJ de l'interface sans concurrence de ressources
    createAllWidgets();         //Creation de tous les elements de l'écran
    threadLvgl.unlock();        //

    radioFM.Reset();            //On réinitialise le module au cas ou
    radioFM.Volume(volFM);      //Volume de départ
    radioFM.Frequency(freqFM);  //Frequence de départ
    radioFM.SeekUp();           //permet d'avoir une station au démarrage
    radioFM.SetThreshold(1);   //fonction pour la sensibilité du seek up/seek down (0-15)

    while (1) {
        radioFM.ProcessData();  //Traitement des données RDS

        threadLvgl.lock();
        lv_label_set_text_fmt(freq_label, "%.1fMHz\n\r", radioFM.freq / 1000); //Affichage numérique fréquence
        lv_label_set_text_fmt(station_label, "%s\n", radioFM.StationName);     //Affichage numérique station (RDS)
        lv_meter_set_indicator_value(meter, indic, radioFM.freq / 1000);       //Affichage "aiguille" fréquence
        lv_meter_set_indicator_value(meter_vol, indic_vol, volFM);             //Affichage "aiguille" volume 
        threadLvgl.unlock();
        ThisThread::sleep_for(10ms);                                          //Une trop grande rapidité perturbe la réception FM+comm. I2C
    }
}
