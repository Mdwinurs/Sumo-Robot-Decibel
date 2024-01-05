#include <Wire.h>
#include <VL53L0X.h>

#define sensorLL_newAddress 41
#define sensorRR_newAddress 42
#define sensorFL_newAddress 43
#define sensorFR_newAddress 44

#define kiri 0x01
#define kanan 0x02
#define kanan_depan 0x03
#define kiri_depan 0x04     
#define depan_depan 0x05

VL53L0X sensorLL;
VL53L0X sensorRR;
VL53L0X sensorFL;
VL53L0X sensorFR;

void setup()
{
  Wire.begin();
  sensorLL.setAddress(sensorLL_newAddress);
  delay(10);
  sensorRR.setAddress(sensorRR_newAddress);
  delay(10);
  sensorFL.setAddress(sensorFL_newAddress);
  delay(10);
  sensorFR.setAddress(sensorFR_newAddress);
  delay(10);

  sensorLL.init();
  sensorRR.init();
  sensorFL.init();
  sensorFR.init();
  
  sensorLL.setTimeout(500);
  sensorRR.setTimeout(500);
  sensorFL.setTimeout(500);
  sensorFR.setTimeout(500);  

  sensorLL.startContinuous();
  sensorRR.startContinuous();
  sensorFL.startContinuous();
  sensorFR.startContinuous();
}
void loop(){
 cekMusuh();
}

int cekMusuh()
{
 int sensorVal_LL = sensorLL.readRangeContinuousMillimeters();
 int sensorVal_RR = sensorRR.readRangeContinuousMillimeters(); 
 int sensorVal_FR = sensorFR.readRangeContinuousMillimeters();
 int sensorVal_FL = sensorFL.readRangeContinuousMillimeters();
 if (sensorVal_LL <= 1000){
   return kiri;
 }
 else if (sensorVal_RR <= 1000){
   return kanan;
 }
 else if (sensorVal_FR <= 1000 && sensorVal_FL >= 1000){
   return kanan_depan;
 }
 else if (sensorVal_FR >= 1000 && sensorVal_FL <= 1000) {
   return kiri_depan;
 }
 else if (sensorVal_FR <= 1000 && sensorVal_FL <= 1000) {
   return depan_depan;
 }
 else {
   return 0;
 }
}