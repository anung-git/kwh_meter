# include "Pzem.h"
Pzem::Pzem(uint8_t addr,Stream &com){
    _serial= &com;; 
    node.begin(addr, com);
};
void Pzem::baca(){
    uint8_t result1;
    ESP.wdtDisable();     //disable watchdog during modbus read or else ESP crashes when no slave connected                                               
    result1 = node.readInputRegisters(0x0000, 10);
    ESP.wdtEnable(1);    //enable watchdog during modbus read  
    if (result1 == node.ku8MBSuccess){
      tegangan      = (node.getResponseBuffer(0x00) / 10.0f);
      arus          = (node.getResponseBuffer(0x01) / 1000.000f);
      watt          = (node.getResponseBuffer(0x03) / 10.0f);
      kwh           = (node.getResponseBuffer(0x05) / 1000.0f);
      frekuensi     = (node.getResponseBuffer(0x07) / 10.0f);
      powerFaktor   = (node.getResponseBuffer(0x08) / 100.0f);
      alarm         = (node.getResponseBuffer(0x09));
    }
//    else {
//      Serial.println("Failed to read modbus 1");
//    }
  }
void Pzem::resetEnergy(uint8_t slaveAddr) {
  //The command to reset the slave's energy is (total 4 bytes):
  //Slave address + 0x42 + CRC check high byte + CRC check low byte.
  uint16_t u16CRC = 0xFFFF;
  static uint8_t resetCommand = 0x42;
  u16CRC = crc16_update(u16CRC, slaveAddr);
  u16CRC = crc16_update(u16CRC, resetCommand);
//  Serial.println("Resetting Energy");
  _serial->write(slaveAddr);
  _serial->write(resetCommand);
  _serial->write(lowByte(u16CRC));
  _serial->write(highByte(u16CRC));
//  delay(1000);
}
  double Pzem::getTegangan(){
    return tegangan;
  }
  double Pzem::getArus(){
    return arus;
  }
  double Pzem::getWatt(){
    return  watt;
  }
  double Pzem::getKwh(){
    return  kwh;
  }
  double Pzem::getFrekuensi(){
    return  frekuensi;
  }
  double Pzem::getPowerFaktor(){
    return  powerFaktor;
  }
  double Pzem::getAlarm(){
    return  alarm;
  }
