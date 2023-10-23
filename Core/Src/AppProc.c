/*Minh Thien Technology
Logic gate driver file*/

#include "AppProc.h"

#define MAX_NUM_CHANNEL     (4)

FLASH_EraseInitTypeDef flTypeInit;
uint32_t FlError = 0;

typedef struct 
{
    uint8_t Channel;
    uint8_t data;
}strBackupData;

strBackupData DataSaver = {
    .Channel = 1,
    .data = 1,
};


/*Backup counter variable*/
uint16_t u8BackUpDataCounter = 0;


void StartingAnimation()
{
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin ,GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin ,GPIO_PIN_SET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin ,GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin ,GPIO_PIN_SET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin ,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin ,GPIO_PIN_RESET);


    
}
/*Write backup data to flash*/
void WriteBackupData(uint32_t address, uint16_t *u16Data)
{
  
   HAL_FLASH_Unlock();
   flTypeInit.TypeErase = FLASH_TYPEERASE_PAGES;
   flTypeInit.PageAddress = address;
   flTypeInit.NbPages = 1;
   
   if(HAL_FLASHEx_Erase(&flTypeInit, &FlError) != HAL_OK)
   {
      HAL_NVIC_SystemReset();
   }
   
   if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address, *u16Data) != HAL_OK)
   {
      HAL_NVIC_SystemReset();
   }
   HAL_FLASH_Lock();
}




/*Read data from flash*/
void ReadBackupData(uint32_t address, uint16_t* u16Data)
{
    *u16Data = (*(volatile uint32_t *)(address));
}




void ReadDataOption()
{
  strBackupData DataTemp = {0} ;
    ReadBackupData(ADD_PAGE_15_SECTOR_3_START, (uint16_t *)&DataTemp);
    /*If not have data in flash, write default data*/
    if ( DataTemp.Channel == 0 )
    {
        WriteBackupData(ADD_PAGE_15_SECTOR_3_START ,(uint16_t *)&DataSaver);
    }
    else
    {
        DataSaver = DataTemp;
    }
    GateDriver(CHANNEL_ALL_OFF);
    HAL_Delay(1);
    GateDriver((eChannel)DataSaver.Channel);
    
}




/*Process Button*/
uint8_t LockReadButton = 0;
void SetLockButton(uint8_t u8Data)
{
    LockReadButton = u8Data;
}


uint8_t GetLockReadButton()
 {
    return LockReadButton;
 }


void ButtonProcess()
{
    static uint8_t ModeChange = 0;
    static uint32_t u32Cnt = 0;
    if ((HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin) == GPIO_PIN_RESET) && (!GetLockReadButton()))
    {
        SetLockButton(1);
        HAL_Delay(100);
        if (HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin) == GPIO_PIN_RESET)
        {
            ModeChange++;
            if ((ModeChange > 0) && (ModeChange <= MAX_NUM_CHANNEL))
            {
                GateDriver(CHANNEL_ALL_OFF);
                GateDriver((eChannel)ModeChange);
                DataSaver.Channel = ModeChange;
            }
            else
            {
                ModeChange = 0;
                GateDriver((eChannel)ModeChange);
            }
            /*Clear Backup counter*/
            u8BackUpDataCounter = 0;
        }
        
    }
    else
    {
        if (HAL_GetTick() - u32Cnt >= 300)
        {
            u32Cnt = HAL_GetTick();
            SetLockButton(0);
        }
        
    }
}






void CheckTimeBackupData()
{

    static uint32_t u32TimerCnt = 0;
    if ((HAL_GetTick() - u32TimerCnt) >= 1000)
    {
        u32TimerCnt = HAL_GetTick();
        u8BackUpDataCounter++;
    }
    /*If system runtime >= 7 days (7*24)3600), then reset system*/
    if (u32TimerCnt >= 604800)
    {
        HAL_NVIC_SystemReset();
    }


    /*If system run after 5 minutes*/
    if (u8BackUpDataCounter >= 360)
    {
        strBackupData strTemp = {0}; 
        ReadBackupData(ADD_PAGE_15_SECTOR_3_START, (uint16_t *)&strTemp);
        if (strTemp.Channel != DataSaver.Channel)
        {
            WriteBackupData(ADD_PAGE_15_SECTOR_3_START ,(uint16_t *)&DataSaver);
        }
        /*Reset counter 5 minutes*/
        u8BackUpDataCounter = 0;
        
    }
    
}



void GateDriver(eChannel Channel)
{
    switch (Channel)
    {
    case CHANNEL_1:
        /*Select Pin Driver*/
        HAL_GPIO_WritePin(EN_A_GPIO_Port, EN_A_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SEC_A_GPIO_Port, SEC_A_Pin, GPIO_PIN_RESET);
        /*TDO pin driver*/
        HAL_GPIO_WritePin(BIT_A_GPIO_Port, BIT_A_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(BIT_B_GPIO_Port, BIT_B_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(BIT_C_GPIO_Port, BIT_C_Pin, GPIO_PIN_RESET);
        /*Turn on Led channel 1*/
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET);
        break;


    case CHANNEL_2:
        /*Select Pin Driver*/
        HAL_GPIO_WritePin(EN_A_GPIO_Port, EN_A_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SEC_A_GPIO_Port, SEC_A_Pin, GPIO_PIN_SET);
         /*TDO pin driver*/
        HAL_GPIO_WritePin(BIT_A_GPIO_Port, BIT_A_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(BIT_B_GPIO_Port, BIT_B_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(BIT_C_GPIO_Port, BIT_C_Pin, GPIO_PIN_RESET);
        /*Turn on Led channel 2*/
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_SET);
        break;


        case CHANNEL_3:
        /*Select Pin Driver*/
        HAL_GPIO_WritePin(EN_A_GPIO_Port, EN_A_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(EN_B_GPIO_Port, EN_B_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SEC_B_GPIO_Port, SEC_B_Pin, GPIO_PIN_RESET);
         /*TDO pin driver*/
        HAL_GPIO_WritePin(BIT_A_GPIO_Port, BIT_A_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(BIT_B_GPIO_Port, BIT_B_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(BIT_C_GPIO_Port, BIT_C_Pin, GPIO_PIN_RESET);
        /*Turn on Led channel 3*/
        HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, GPIO_PIN_SET);
        break;

        case CHANNEL_4:
        /*Select Pin Driver*/
        HAL_GPIO_WritePin(EN_A_GPIO_Port, EN_A_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(EN_B_GPIO_Port, EN_B_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SEC_B_GPIO_Port, SEC_B_Pin, GPIO_PIN_SET);
         /*TDO pin driver*/
        HAL_GPIO_WritePin(BIT_A_GPIO_Port, BIT_A_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(BIT_B_GPIO_Port, BIT_B_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(BIT_C_GPIO_Port, BIT_C_Pin, GPIO_PIN_SET);
        /*Turn on Led channel 1*/
        HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, GPIO_PIN_SET);
        break;

        case CHANNEL_ALL_OFF:
        /*Select Pin Driver*/
        HAL_GPIO_WritePin(EN_A_GPIO_Port, EN_A_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(EN_B_GPIO_Port, EN_B_Pin, GPIO_PIN_SET);
        /*Turn on Led channel 1*/
        HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, GPIO_PIN_RESET);
    default:
        break;
    }
}


