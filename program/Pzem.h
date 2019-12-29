#include "ModbusMaster.h"


class Pzem{
  public:
    Pzem(uint8_t addr,Stream &com);
    void baca();
    double getTegangan();
    double getArus();
    double getWatt();
    double getKwh();
    double getFrekuensi();
    double getPowerFaktor();
    double getAlarm();
    void resetEnergy(uint8_t slaveAddr);

   private:
    ModbusMaster node;
    double tegangan;
    double arus;
    double watt;
    double kwh;
    double frekuensi;
    double powerFaktor;
    double alarm;
    Stream* _serial; 
};
