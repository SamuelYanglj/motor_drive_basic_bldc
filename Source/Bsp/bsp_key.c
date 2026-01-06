/**
 * @file bsp_key.c
 * @brief Advanced User Management System Implementation
 * 
 * @ingroup user_management
 * 
 * @details
 * This file implements all functionalities of the user management system, including:
 * - System initialization and resource management
 * - User data CRUD operations
 * - User statistics and monitoring
 * - Event notification mechanism
 * 
 * Implementation Features:
 * - Uses dynamic arrays for user data storage with automatic expansion
 * - Implements LRU cache for frequently accessed users
 * - Uses reference counting for user object lifecycle management
 * 
 * @internal
 * Module internal implementation details:
 * - Uses red-black tree for user ID indexing
 * - Uses hash table for user name indexing
 * - Memory allocation uses custom memory pool
 * 
 * @note Performance consideration: Database backend recommended when user count exceeds 10000
 * @warning All exported functions include parameter validation, but internal functions do not
 * 
 * @author Developer Name
 * @email developer@company.com
 * @date 2024-01-01
 * @version 2.1.0
 * 
 * @copyright Copyright (c) 2024 Company Name. All rights reserved.
 */

/** @addtogroup BSP
  * @{
  */

/* ============================ Include Headers ============================ */

#include <stdio.h>
#include "bsp_key.h"
#include "bsp_systick.h"

/* ============================ Module Internal Constants ============================ */

#define FILTER_KEEP_TIME (10)

/* ============================ Module Internal Data Structures ============================ */

typedef struct 
{
    key_num_e     num;
    GPIO_Module*  GPIOx;
    GPIO_InitType GPIO_InitStructure;
}gpio_config_t;


/* ============================ Global Variables ============================ */

/* ============================ Static Global Variables ============================ */

static gpio_config_t key_config[] =
{
	START_STOP_KEY, GPIOC, {GPIO_PIN_6, GPIO_DC_2mA, GPIO_Slew_Rate_High, GPIO_Pull_Down, GPIO_Mode_Input, GPIO_NO_AF},
	CW_CCW_KEY    , GPIOC, {GPIO_PIN_7, GPIO_DC_2mA, GPIO_Slew_Rate_High, GPIO_Pull_Down, GPIO_Mode_Input, GPIO_NO_AF},
	KEY_MAX       , (GPIO_Module*)NULL , {(uint16_t)NULL, (GPIO_CurrentType)NULL, (GPIO_SpeedType)NULL, (GPIO_PuPdType)NULL, (GPIO_ModeType)NULL, (uint32_t)NULL}
};

static key_param_t key_scan[] = 
{
    {START_STOP_KEY, 0, 0, 0, 0},
    {CW_CCW_KEY    , 0, 0, 0, 0},
    {KEY_MAX       , 0, 0, 0, 0},
};

/* ============================ Static Function Declarations ============================ */

/* ============================ Public Function Implementations ============================ */

/**
 * @brief init key
 * 
 * @param[in] None
 * @return None
 */
void bsp_key_init(void)
{
    uint8_t i = 0;

    for(i = 0; i < (int)KEY_MAX; i++)
    {
        GPIO_InitPeripheral(key_config[i].GPIOx, &key_config[i].GPIO_InitStructure);
    }
}


/**
 * @brief print key neme
 * 
 * @param[in] None
 * @return None
 */
void bsp_key_print(key_param_t* key_param)
{
    switch (key_param->num)
    {
    case START_STOP_KEY:
        printf("Start/Stop Key Down\r\n");
        break;

    case CW_CCW_KEY:
        printf("CW/CCW Key Down\r\n");
        break;
    
    default:
        break;
    }
}


/**
 * @brief scan key
 * 
 * @param[in] None
 * @return None
 */
void bsp_key_scan(void)
{
    uint8_t i = 0;
    uint8_t key_val = 0;

    for(i = 0; i < (int)KEY_MAX; i++)
    {
        /*STEP1: Key press detection, to determine whether the key has been pressed*/
        key_val = GPIO_ReadInputDataBit(key_config[i].GPIOx, key_config[i].GPIO_InitStructure.Pin);
        if((key_val == KEY_DOWN_VALUE) && (key_scan[i].trigger == 0))
        {
            key_scan[i].trigger = FIRST_ACTIVATION;       // update the key trigger status to FIRST_ACTIVATION
            key_scan[i].time    = bsp_systick_time_get(); // recode the key first trigger time
        }

        /*STEP2: Press the button to perform software anti-shake filtering*/
        if(key_scan[i].trigger == FIRST_ACTIVATION)
        {
            /*Check whether the time for the two key presses is greater than 10 milliseconds.*/
            if((bsp_systick_time_get() - key_scan[i].time) > FILTER_KEEP_TIME)
            {
                /*10 milliseconds have elapsed: Re-read the key value to determine if it is in the pressed state*/
                key_val = GPIO_ReadInputDataBit(key_config[i].GPIOx, key_config[i].GPIO_InitStructure.Pin);
                if(key_val == KEY_DOWN_VALUE)
                {
                    key_scan[i].down_sign = KEY_DOWN_VALUE; // Pressed state: Set the key press mark to 1
                    bsp_key_print(&key_scan[i]);             // print key info
                }
                key_scan[i].trigger = REAL_ACTIVATION;      // update the key trigger status to REAL_ACTIVATION
            }
        }

        /*STEP3: If the button is in the raised state: then the trigger value is updated to 0, preparing for the next button press action.*/
        if((key_scan[i].trigger == REAL_ACTIVATION) && (key_val == KEY_UP_VALUE))
        {
            key_scan[i].trigger = NOT_ACTIVATION;
        }
    }
}

/* ============================ Static Function Implementations ============================ */

/* ============================ Unit Test Support ============================ */

#ifdef UNIT_TEST

#endif /* UNIT_TEST */

/**
  * @}
  */
