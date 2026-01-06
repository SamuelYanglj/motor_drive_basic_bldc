/**
 * @file bsp_uart.h
 * @brief Driver bsp_uart Header
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

#ifndef __BSP_UART_H__
#define __BSP_UART_H__

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/* ============================ Include Headers ============================ */

#include "n32g43x.h"

/* ============================ Public Constants ============================ */

/* **************************** debug uart macro **************************** */
#define DEBUG_UART            					UART4
#define DEBUG_UART_CLK        					RCC_APB2_PERIPH_UART4

#define DEBUG_UART_TX_GPIO       				GPIOB
#define DEBUG_UART_TX_PIN      					GPIO_PIN_0
#define DEBUG_UART_TX_GPIO_CLK   				RCC_APB2_PERIPH_GPIOB
#define DEBUG_UART_TX_GPIO_AF 					GPIO_AF6_UART4

#define DEBUG_UART_RX_GPIO       				GPIOB
#define DEBUG_UART_RX_PIN      					GPIO_PIN_1
#define DEBUG_UART_RX_GPIO_CLK   				RCC_APB2_PERIPH_GPIOB
#define DEBUG_UART_RX_GPIO_AF 					GPIO_AF6_UART4


#define DEBUG_UART_TX_GPIO_CLK_CMD   			RCC_EnableAPB2PeriphClk
#define DEBUG_UART_RX_GPIO_CLK_CMD   			RCC_EnableAPB2PeriphClk
#define DEBUG_UART_CLK_CMD  					RCC_EnableAPB2PeriphClk

#define DEBUG_UART_IRQ      					UART4_IRQn

/* **************************** host computer uart macro **************************** */
#define HOST_COMPUTER_UART            			UART5
#define HOST_COMPUTER_UART_CLK        			RCC_APB2_PERIPH_UART5

#define HOST_COMPUTER_UART_TX_GPIO       		GPIOC
#define HOST_COMPUTER_UART_TX_PIN      			GPIO_PIN_12
#define HOST_COMPUTER_UART_TX_GPIO_CLK   		RCC_APB2_PERIPH_GPIOC
#define HOST_COMPUTER_UART_TX_GPIO_AF 			GPIO_AF6_UART5

#define HOST_COMPUTER_UART_RX_GPIO       		GPIOD
#define HOST_COMPUTER_UART_RX_PIN      			GPIO_PIN_2
#define HOST_COMPUTER_UART_RX_GPIO_CLK   		RCC_APB2_PERIPH_GPIOD
#define HOST_COMPUTER_UART_RX_GPIO_AF 			GPIO_AF6_UART5


#define HOST_COMPUTER_UART_TX_GPIO_CLK_CMD   	RCC_EnableAPB2PeriphClk
#define HOST_COMPUTER_UART_RX_GPIO_CLK_CMD   	RCC_EnableAPB2PeriphClk
#define HOST_COMPUTER_UART_CLK_CMD  			RCC_EnableAPB2PeriphClk

#define HOST_COMPUTER_UART_IRQ					UART5_IRQn

/* **************************** rs485 uart macro **************************** */
#define RS485_UART            					USART3
#define RS485_UART_CLK        					RCC_APB1_PERIPH_USART3  

#define RS485_UART_TX_GPIO       				GPIOB
#define RS485_UART_TX_PIN      					GPIO_PIN_10
#define RS485_UART_TX_GPIO_CLK   				RCC_APB2_PERIPH_GPIOB
#define RS485_UART_TX_GPIO_AF 					GPIO_AF0_USART3

#define RS485_UART_RX_GPIO       				GPIOB
#define RS485_UART_RX_PIN      					GPIO_PIN_11
#define RS485_UART_RX_GPIO_CLK   				RCC_APB2_PERIPH_GPIOB
#define RS485_UART_RX_GPIO_AF 					GPIO_AF5_USART3

#define RS485_EN_GPIO       					GPIOC
#define RS485_EN_PIN      						GPIO_PIN_8
#define RS485_EN_GPIO_CLK   					RCC_APB2_PERIPH_GPIOC

#define RS485_UART_TX_GPIO_CLK_CMD   			RCC_EnableAPB2PeriphClk
#define RS485_UART_RX_GPIO_CLK_CMD   			RCC_EnableAPB2PeriphClk
#define RS485_EN_GPIO_CLK_CMD   				RCC_EnableAPB2PeriphClk
#define RS485_UART_CLK_CMD  					RCC_EnableAPB1PeriphClk

#define RS485_UART_IRQ							USART3_IRQn

/* ============================ Code Enum Definitions ============================ */

typedef enum
{
    DEBUG_COM = 0,
    HOST_COMPUTER_COM,
    RS485_COM,
}uart_com_e;

/* ============================ Data Structure Definitions ============================ */

typedef struct 
{
    void (*debug_com_cb)(void);
    void (*host_computer_com_cb)(void);
    void (*rs485_com_cb)(void);
}com_irq_cb_t;


/* ============================ Callback Function Type Definitions ============================ */

/* ============================ Global Variable Declarations ============================ */

extern com_irq_cb_t com_irq_cb;

/* ============================ Macro Function Declarations ============================ */

#define RS485_COM_SEND_ENABLE()					GPIO_ResetBits(RS485_EN_GPIO, RS485_EN_PIN)     //RS485端口发送使能                
#define RS485_COM_RECV_ENABLE()					GPIO_SetBits(RS485_EN_GPIO, RS485_EN_PIN)       //RS485端口接收使能   

/* ============================ Function Declarations ============================ */

void bsp_uart_init(uart_com_e com, uint32_t baud, void(*irq_cb)(void));
void bsp_uart_send_data(uart_com_e com, uint8_t *data, uint32_t len);


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__BSP_UART_H__*/


/**
  * @}
  */
