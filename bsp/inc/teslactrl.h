/*
 * teslactrl.h
 *
 *  Created on: Nov 24, 2021
 *      Author: usr_tunnerk
 */

#ifndef TESLACTRL_H_
#define TESLACTRL_H_
#include <stdint.h>

/* macros for modbus base addresses*/
#define MB_CELLVOLT_BASE 0
#define MB_CELLTEMP_BASE 80
#define MB_CELLCAP_BASE 110
#define MB_STATREG_BASE 191

/* macros for secondary charger status */
#define SEC_STAT_STANDBY        0x0000
#define SEC_STAT_CLEAR_FAULT    0x1000
#define SEC_STAT_FAULT          0x2000
#define SEC_STAT_F025_VLINEUV   0x2019
#define SEC_STAT_F027_VOUTUV    0x201a
#define SEC_STAT_PRECHARGE      0x3000
#define SEC_STAT_EANBLE         0x4000
#define SEC_STAT_NODATA         0x8888
struct tesla_cellVoltages
{
  // CMU#1
  uint16_t cellVolt01; 
  uint16_t cellVolt02; 
  uint16_t cellVolt03; 
  uint16_t cellVolt04; 
  uint16_t cellVolt05; 
  uint16_t cellVolt06; 
  uint16_t cellVolt07; 
  uint16_t cellVolt08;     
  // CMU#2
  uint16_t cellVolt09; 
  uint16_t cellVolt10; 
  uint16_t cellVolt11; 
  uint16_t cellVolt12; 
  uint16_t cellVolt13; 
  uint16_t cellVolt14; 
  uint16_t cellVolt15; 
  uint16_t cellVolt16;     
  // CMU#3 
  uint16_t cellVolt17; 
  uint16_t cellVolt18; 
  uint16_t cellVolt19; 
  uint16_t cellVolt20; 
  uint16_t cellVolt21; 
  uint16_t cellVolt22; 
  uint16_t cellVolt23; 
  uint16_t cellVolt24;     
  // CMU#4 
  uint16_t cellVolt25; 
  uint16_t cellVolt26; 
  uint16_t cellVolt27; 
  uint16_t cellVolt28; 
  uint16_t cellVolt29; 
  uint16_t cellVolt30; 
  uint16_t cellVolt31; 
  uint16_t cellVolt32;     
  // CMU#6 
  uint16_t cellVolt33; 
  uint16_t cellVolt34; 
  uint16_t cellVolt35; 
  uint16_t cellVolt36; 
  uint16_t cellVolt37; 
  uint16_t cellVolt38; 
  uint16_t cellVolt39; 
  uint16_t cellVolt40;     
  // CMU#7
  uint16_t cellVolt41; 
  uint16_t cellVolt42; 
  uint16_t cellVolt43; 
  uint16_t cellVolt44; 
  uint16_t cellVolt45; 
  uint16_t cellVolt46; 
  uint16_t cellVolt47; 
  uint16_t cellVolt48;     
  // CMU#8 
  uint16_t cellVolt49; 
  uint16_t cellVolt50; 
  uint16_t cellVolt51; 
  uint16_t cellVolt52; 
  uint16_t cellVolt53; 
  uint16_t cellVolt54; 
  uint16_t cellVolt55; 
  uint16_t cellVolt56;     
  // CMU#9 
  uint16_t cellVolt57; 
  uint16_t cellVolt58; 
  uint16_t cellVolt59; 
  uint16_t cellVolt60; 
  uint16_t cellVolt61; 
  uint16_t cellVolt62; 
  uint16_t cellVolt63; 
  uint16_t cellVolt64;     
  // CMU#A 
  uint16_t cellVolt65; 
  uint16_t cellVolt66; 
  uint16_t cellVolt67; 
  uint16_t cellVolt68; 
  uint16_t cellVolt69; 
  uint16_t cellVolt70; 
  uint16_t cellVolt71; 
  uint16_t cellVolt72;     
  // CMU#B 
  uint16_t cellVolt73; 
  uint16_t cellVolt74; 
  uint16_t cellVolt75; 
  uint16_t cellVolt76; 
  uint16_t cellVolt77; 
  uint16_t cellVolt78; 
  uint16_t cellVolt79; 
  uint16_t cellVolt80;    
};

struct tesla_cellTemps
{
    // CMU#1
    uint8_t cellTemp1;
    uint8_t cellTemp3;
    uint8_t cellTemp5;
    uint8_t cellTemp7;
    uint8_t cellTemp8;
    // CMU#2
    uint8_t cellTemp9;
    uint8_t cellTemp11;
    uint8_t cellTemp13;
    uint8_t cellTemp15;
    uint8_t cellTemp16;
    // CMU#3
    uint8_t cellTemp17;
    uint8_t cellTemp19;
    uint8_t cellTemp21;
    uint8_t cellTemp23;
    uint8_t cellTemp24;
    // CMU#4
    uint8_t cellTemp25;
    uint8_t cellTemp29;
    uint8_t cellTemp31;
    uint8_t cellTemp32;
    // CMU#5
    uint8_t cellTemp33;
    uint8_t cellTemp35;
    uint8_t cellTemp37;
    uint8_t cellTemp39;
    uint8_t cellTemp40;
    // CMU#7
    uint8_t cellTemp41;
    uint8_t cellTemp45;
    uint8_t cellTemp47;
    uint8_t cellTemp48;
    // CMU#8
    uint8_t cellTemp49;
    uint8_t cellTemp51;
    uint8_t cellTemp53;
    uint8_t cellTemp55;
    uint8_t cellTemp56;
    // CMU#9
    uint8_t cellTemp57;
    uint8_t cellTemp59;
    uint8_t cellTemp61;
    uint8_t cellTemp63;
    uint8_t cellTemp64;
    // CMU#A
    uint8_t cellTemp65;
    uint8_t cellTemp67;
    uint8_t cellTemp69;
    uint8_t cellTemp71;
    uint8_t cellTemp72;
    // CMU#B
    uint8_t cellTemp73;
    uint8_t cellTemp75;
    uint8_t cellTemp77;
    uint8_t cellTemp79;
    uint8_t cellTemp80;
};

/* Not implemented in the Tesla Charger Controller arduino code*/
struct tesla_cellCapacities
{
    // CMU#1
    uint16_t cellCap01;
    uint16_t cellCap02;
    uint16_t cellCap03;
    uint16_t cellCap04;
    uint16_t cellCap05;
    uint16_t cellCap06;
    uint16_t cellCap07;
    uint16_t cellCap08;
    //CMU#2
    uint16_t cellCap09;
    uint16_t cellCap10;
    uint16_t cellCap11;
    uint16_t cellCap12;
    uint16_t cellCap13;
    uint16_t cellCap14;
    uint16_t cellCap15;
    uint16_t cellCap16;
    // CMU#3
    uint16_t cellCap17;
    uint16_t cellCap18;
    uint16_t cellCap19;
    uint16_t cellCap20;
    uint16_t cellCap21;
    uint16_t cellCap22;
    uint16_t cellCap23;
    uint16_t cellCap24;
    // CMU#4
    uint16_t cellCap25;
    uint16_t cellCap26;
    uint16_t cellCap27;
    uint16_t cellCap28;
    uint16_t cellCap29;
    uint16_t cellCap30;
    uint16_t cellCap31;
    uint16_t cellCap32;
    // CMU#5
    uint16_t cellCap33;
    uint16_t cellCap34;
    uint16_t cellCap35;
    uint16_t cellCap36;
    uint16_t cellCap37;
    uint16_t cellCap38;
    uint16_t cellCap39;
    uint16_t cellCap40;
    // CMU#7
    uint16_t cellCap41;
    uint16_t cellCap42;
    uint16_t cellCap43;
    uint16_t cellCap44;
    uint16_t cellCap45;
    uint16_t cellCap46;
    uint16_t cellCap47;
    uint16_t cellCap48;
    // CMU#8
    uint16_t cellCap49;
    uint16_t cellCap50;
    uint16_t cellCap51;
    uint16_t cellCap52;
    uint16_t cellCap53;
    uint16_t cellCap54;
    uint16_t cellCap55;
    uint16_t cellCap56;
    // CMU#9
    uint16_t cellCap57;
    uint16_t cellCap58;
    uint16_t cellCap59;
    uint16_t cellCap60;
    uint16_t cellCap61;
    uint16_t cellCap62;
    uint16_t cellCap63;
    uint16_t cellCap64;
    // CMU#A
    uint16_t cellCap65;
    uint16_t cellCap66;
    uint16_t cellCap67;
    uint16_t cellCap68;
    uint16_t cellCap69;
    uint16_t cellCap70;
    uint16_t cellCap71;
    uint16_t cellCap72;
    // CMU#B
    uint16_t cellCap73;
    uint16_t cellCap74;
    uint16_t cellCap75;
    uint16_t cellCap76;
    uint16_t cellCap77;
    uint16_t cellCap78;
    uint16_t cellCap79;
    uint16_t cellCap80;
};

struct telsa_chargerStats
{
    uint16_t priChargerStatus;
    uint16_t secChargerStatus;
    uint16_t priChargerAcVoltage;
    uint16_t secChargerAcVoltage;
    uint16_t priChargerAcCurr;
    uint16_t secChargerAcCurr;
    uint16_t priChargerDcVoltage;
    uint16_t secChargerDcVoltage;
    uint16_t priChargerDcCurr;
    uint16_t secChargerDcCurr;
    uint16_t priChargerHsTemp;
    uint16_t secChargerHsTemp;
    uint16_t commErrCnt;
    uint16_t auxInVoltage;
    uint16_t auxInCurr;
    uint16_t waterTemp;
};

int tesla_readCellVolts(uint16_t *data);
int tesla_readCellTemps(uint8_t *data);
int tesla_readCellCapacities(uint16_t *data);
int tesla_readChargerStatus(uint16_t *data);

#endif /* TESLACTRL_H_ */
