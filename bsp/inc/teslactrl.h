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

enum tesla_cellVoltages
{
  // CMU#1
  cellVolt01, 
  cellVolt02, 
  cellVolt03, 
  cellVolt04, 
  cellVolt05, 
  cellVolt06, 
  cellVolt07, 
  cellVolt08,     
  // CMU#2
  cellVolt09, 
  cellVolt10, 
  cellVolt11, 
  cellVolt12, 
  cellVolt13, 
  cellVolt14, 
  cellVolt15, 
  cellVolt16,     
  // CMU#3 
  cellVolt17, 
  cellVolt18, 
  cellVolt19, 
  cellVolt20, 
  cellVolt21, 
  cellVolt22, 
  cellVolt23, 
  cellVolt24,     
  // CMU#4 
  cellVolt25, 
  cellVolt26, 
  cellVolt27, 
  cellVolt28, 
  cellVolt29, 
  cellVolt30, 
  cellVolt31, 
  cellVolt32,     
  // CMU#6 
  cellVolt33, 
  cellVolt34, 
  cellVolt35, 
  cellVolt36, 
  cellVolt37, 
  cellVolt38, 
  cellVolt39, 
  cellVolt40,     
  // CMU#7
  cellVolt41, 
  cellVolt42, 
  cellVolt43, 
  cellVolt44, 
  cellVolt45, 
  cellVolt46, 
  cellVolt47, 
  cellVolt48,     
  // CMU#8 
  cellVolt49, 
  cellVolt50, 
  cellVolt51, 
  cellVolt52, 
  cellVolt53, 
  cellVolt54, 
  cellVolt55, 
  cellVolt56,     
  // CMU#9 
  cellVolt57, 
  cellVolt58, 
  cellVolt59, 
  cellVolt60, 
  cellVolt61, 
  cellVolt62, 
  cellVolt63, 
  cellVolt64,     
  // CMU#A 
  cellVolt65, 
  cellVolt66, 
  cellVolt67, 
  cellVolt68, 
  cellVolt69, 
  cellVolt70, 
  cellVolt71, 
  cellVolt72,     
  // CMU#B 
  cellVolt73, 
  cellVolt74, 
  cellVolt75, 
  cellVolt76, 
  cellVolt77, 
  cellVolt78, 
  cellVolt79, 
  cellVolt80,    
};

enum tesla_cellTemps
{
    // CMU#1
    cellTemp1,
    cellTemp3,
    cellTemp5,
    cellTemp7,
    cellTemp8,
    // CMU#2
    cellTemp9,
    cellTemp11,
    cellTemp13,
    cellTemp15,
    cellTemp16,
    // CMU#3
    cellTemp17,
    cellTemp19,
    cellTemp21,
    cellTemp23,
    cellTemp24,
    // CMU#4
    cellTemp25,
    cellTemp29,
    cellTemp31,
    cellTemp32,
    // CMU#5
    cellTemp33,
    cellTemp35,
    cellTemp37,
    cellTemp39,
    cellTemp40,
    // CMU#7
    cellTemp41,
    cellTemp45,
    cellTemp47,
    cellTemp48,
    // CMU#8
    cellTemp49,
    cellTemp51,
    cellTemp53,
    cellTemp55,
    cellTemp56,
    // CMU#9
    cellTemp57,
    cellTemp59,
    cellTemp61,
    cellTemp63,
    cellTemp64,
    // CMU#A
    cellTemp65,
    cellTemp67,
    cellTemp69,
    cellTemp71,
    cellTemp72,
    // CMU#B
    cellTemp73,
    cellTemp75,
    cellTemp77,
    cellTemp79,
    cellTemp80,
};

/* Not implemented in the Tesla Charger Controller arduino code*/
enum tesla_cellCapacities
{
    // CMU#1
    cellCap01,
    cellCap02,
    cellCap03,
    cellCap04,
    cellCap05,
    cellCap06,
    cellCap07,
    cellCap08,
    //CMU#2
    cellCap09,
    cellCap10,
    cellCap11,
    cellCap12,
    cellCap13,
    cellCap14,
    cellCap15,
    cellCap16,
    // CMU#3
    cellCap17,
    cellCap18,
    cellCap19,
    cellCap20,
    cellCap21,
    cellCap22,
    cellCap23,
    cellCap24,
    // CMU#4
    cellCap25,
    cellCap26,
    cellCap27,
    cellCap28,
    cellCap29,
    cellCap30,
    cellCap31,
    cellCap32,
    // CMU#5
    cellCap33,
    cellCap34,
    cellCap35,
    cellCap36,
    cellCap37,
    cellCap38,
    cellCap39,
    cellCap40,
    // CMU#7
    cellCap41,
    cellCap42,
    cellCap43,
    cellCap44,
    cellCap45,
    cellCap46,
    cellCap47,
    cellCap48,
    // CMU#8
    cellCap49,
    cellCap50,
    cellCap51,
    cellCap52,
    cellCap53,
    cellCap54,
    cellCap55,
    cellCap56,
    // CMU#9
    cellCap57,
    cellCap58,
    cellCap59,
    cellCap60,
    cellCap61,
    cellCap62,
    cellCap63,
    cellCap64,
    // CMU#A
    cellCap65,
    cellCap66,
    cellCap67,
    cellCap68,
    cellCap69,
    cellCap70,
    cellCap71,
    cellCap72,
    // CMU#B
    cellCap73,
    cellCap74,
    cellCap75,
    cellCap76,
    cellCap77,
    cellCap78,
    cellCap79,
    cellCap80,
};

enum telsa_chargerStats
{
    priChargerStatus,
    secChargerStatus,
    priChargerAcVoltage,
    secChargerAcVoltage,
    priChargerAcCurr,
    secChargerAcCurr,
    priChargerDcVoltage,
    secChargerDcVoltage,
    priChargerDcCurr,
    secChargerDcCurr,
    priChargerHsTemp,
    secChargerHsTemp,
    commErrCnt,
    auxInVoltage,
    auxInCurr,
    waterTemp,
};

typedef enum{
    TESLA_START,
    TESLA_STOP
}tesla_chargerStatus;

typedef struct {
	uint16_t cellCapacities[80];
	uint8_t cellTemps[30];
	uint16_t cellVoltages[80];
    uint16_t chargerStats[15];
    uint16_t chargingCurrent;
}tesla_handler;

tesla_handler *tHandler;

void tesla_init(tesla_handler *handler);
int tesla_readCellVolts();
int tesla_readCellTemps();
int tesla_readCellCapacities();
int tesla_readChargerStatus(uint16_t *data);
int tesla_setChargeCurrent(uint16_t data);

#endif /* TESLACTRL_H_ */
