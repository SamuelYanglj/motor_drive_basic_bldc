/**
 * @file bsp_key.h
 * @brief Driver bsp_io Header
 * 
 * @defgroup user_management User Management Module
 * @brief Provides complete user management functionality including create, delete, query, and statistics
 * 
 * @details
 * This module implements efficient user data management with support for dynamic memory allocation 
 * and multiple query methods. Uses object-oriented design principles and provides comprehensive 
 * error handling mechanisms.(this is not real details)
 * 
 * @note This module is not thread-safe. External synchronization is required in multi-threaded environments.
 * @warning Initialization function must be called before use, cleanup function must be called after use.
 * @bug Known issue: May not handle errors properly under extreme memory shortage conditions.
 * @todo Add thread safety support
 * @todo Implement user data persistence storage
 * 
 * @author  SamuelYang
 * @email samuelyang615@163.com
 * @date 2025-11-15
 * @version 0.1.0
 * 
 * @copyright Copyright (c) 2024 Company Name. All rights reserved.
 * 
 * @license
 * This project is licensed under the MIT License:
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software...
 * 
 * @par History:
 * <table>
 * <tr><th>Date         <th>Version    <th>Author        <th>Description
 * <tr><td>2024-01-01  <td>2.1.0  <td>Developer Name  <td>Added batch operations
 * <tr><td>2023-12-15  <td>2.0.0  <td>Developer Name  <td>Refactored to modular design
 * <tr><td>2023-11-01  <td>1.5.0  <td>Developer Name  <td>Added statistics functionality
 * </table>
 */

/** @addtogroup BSP
  * @{
  */

#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/* ============================ Include Headers ============================ */

#include "n32g43x.h"

/* ============================ Public Constants ============================ */

#define KEY_DOWN_VALUE  0x01  /*the value of key pressed*/
#define KEY_UP_VALUE    0x00  /*the value of key released*/

#if 0
#define KEY_TRIGGER_NOT_ACTIVATION    0x00
#define KEY_TRIGGER_FIRST_ACTIVATION  0x01
#define KEY_TRIGGER_REAL_ACTIVATION   0x02
#endif

/* ============================ Error Code Enum Definitions ============================ */

typedef enum
{
    START_STOP_KEY = 0,
    CW_CCW_KEY,
    KEY_MAX
}key_num_e;

typedef enum
{
    NOT_ACTIVATION   = 0x00,
    FIRST_ACTIVATION = 0x01,
    REAL_ACTIVATION  = 0x02,
}key_trigger_status_e;

/* ============================ Data Structure Definitions ============================ */

typedef struct 
{
    key_num_e num;
    uint32_t  time;           /*time recording*/
    uint8_t   trigger;        /*trigger tag*/
    uint8_t   down_sign;      /*the tag of key pressed*/
    uint32_t  key_down_cnt;   /*the count of key pressed*/
}key_param_t;


/* ============================ Callback Function Type Definitions ============================ */

/* ============================ Global Variable Declarations ============================ */

extern key_param_t key_scan[];

/* ============================ Macro Function Declarations ============================ */

/* ============================ Function Declarations ============================ */

void bsp_key_init(void);
void bsp_key_scan(void);


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__BSP_KEY_H__*/


/**
  * @}
  */
