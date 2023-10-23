/*Minh Thien Technology
Logic gate driver file*/

#ifndef __APPPROC_H
#define __APPPROC_H
#endif


#include "main.h"

#define ADD_PAGE_15_SECTOR_3_START ((uint32_t)0x08004000)
#define ADD_PAGE_15_SECTOR_3_END   ((uint32_t)0x080043FF) //Stm32F4P6 has 16kb, 4 sector, 16 page/1kb, Sector 3 start from 0x8004000
#define SIZE_PAGE 1024


typedef enum{
    CHANNEL_ALL_OFF = 0,
    CHANNEL_1,
    CHANNEL_2,
    CHANNEL_3,
    CHANNEL_4,
}eChannel;

void StartingAnimation();
void GateDriver(eChannel Channel);
void ButtonProcess();

void WriteBackupData(uint32_t address, uint16_t *u16Data);
void ReadBackupData(uint32_t address, uint16_t* u16Data);
void ReadDataOption();
void CheckTimeBackupData();

void SetLockButton(uint8_t u8data);
uint8_t GetLockReadButton();


