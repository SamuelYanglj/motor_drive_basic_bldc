/**
 * @file bsp_uart_cb.c
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

#include <string.h>
#include "bsp_uart.h"
#include "bsp_uart_cb.h"

/* ============================ Module Internal Constants ============================ */

/* ============================ Module Internal Data Structures ============================ */

/* ============================ Global Variables ============================ */

factory_func_check_t factory_func_check;

/* ============================ Static Global Variables ============================ */

static uint8_t rs485_recv_buf[1024];
static uint32_t findex = 0;

/* ============================ Static Function Declarations ============================ */

/**
 * @brief Factory parameter command detection
 * 
 * @param[in] data: recive seriel port data
 * @return None
 */
static void bsp_uart_factory_cmd_analyse(uint8_t data)
{
  static uint8_t len = 0;
  static uint8_t recv_buf[32] = {0};

  recv_buf[len++] = data;

  /* Determine the string termination character */
  if(recv_buf[len - 1] == '\n')
  {
    /*CAN functional test*/
    if(strncmp((char*)recv_buf, "CAN", 3) == 0)
    {
      factory_func_check.can_sign = 0xFF;
    }
    /*RS485 functional test*/
    if(strncmp((char*)recv_buf, "RS485", 5) == 0)
    {
      factory_func_check.rs485_sign = 0xFF;
    }
    /*PC_COM functional test*/
    if(strncmp((char*)recv_buf, "PC_COM", 6) == 0)
    {
      factory_func_check.pc_com_sign = 0xFF;
    }
    /*CURRENT functional test*/
    if(strncmp((char*)recv_buf, "CURRENT", 7) == 0)
    {
      factory_func_check.current_sign = 0xFF;
    }
    /*VOLTAGE functional test*/
    if(strncmp((char*)recv_buf, "VOLTAGE", 7) == 0)
    {
      factory_func_check.voltage_sign = 0xFF;
    }
    /*OVERFLOW functional test*/
    if(strncmp((char*)recv_buf, "OVERFLOW", 8) == 0)
    {
      factory_func_check.overflow_sign = 0xFF;
    }
    /*TEMPERATUR functional test*/
    if(strncmp((char*)recv_buf, "TEMPERATUR", 10) == 0)
    {
      factory_func_check.temperatur_sign = 0xFF;
    }

    len = 0;
  }

	if(sizeof(recv_buf) == len)
	{
		len = 0;
	}
}

/* ============================ Public Function Implementations ============================ */

/**
 * @brief init led
 * 
 * @param[in] None
 * @return None
 */
void bsp_uart_debug_com_irq_cb(void)
{
	uint8_t data = 0;
	
	if (USART_GetIntStatus(DEBUG_UART, USART_INT_RXDNE) != RESET)
    {
        /* Read one byte from the receive data register */
        data = USART_ReceiveData(DEBUG_UART);
		bsp_uart_factory_cmd_analyse(data);
//		bsp_uart_send_data(DEBUG_COM, &data, 1);
    }
    if (USART_GetIntStatus(DEBUG_UART, USART_INT_TXDE) != RESET)
    {
        /* Write one byte to the transmit data register */
//        USART_SendData(DEBUG_UART, xx);
    }
    if(USART_GetIntStatus(DEBUG_UART, USART_INT_OREF) != RESET)
    {
        /*Read the STS register first,and the read the DAT 
        register to clear the overflow interrupt*/
        (void)DEBUG_UART->STS;
        (void)DEBUG_UART->DAT;
    }
}


/**
 * @brief led ctrl
 * 
 * @param[in] num: the led index
 * @param[in] status: the led status (on or off)
 * @return None
 */
void bsp_uart_host_computer_com_irq_cb(void)
{
	uint8_t data = 0;
	
	if (USART_GetIntStatus(HOST_COMPUTER_UART, USART_INT_RXDNE) != RESET)
    {
        /* Read one byte from the receive data register */
        data = USART_ReceiveData(HOST_COMPUTER_UART);
		bsp_uart_send_data(HOST_COMPUTER_COM, &data, 1);
    }
    if (USART_GetIntStatus(HOST_COMPUTER_UART, USART_INT_TXDE) != RESET)
    {
        /* Write one byte to the transmit data register */
//        USART_SendData(HOST_COMPUTER_UART, xx);
    }
    if(USART_GetIntStatus(HOST_COMPUTER_UART, USART_INT_OREF) != RESET)
    {
        /*Read the STS register first,and the read the DAT 
        register to clear the overflow interrupt*/
        (void)HOST_COMPUTER_UART->STS;
        (void)HOST_COMPUTER_UART->DAT;
    }
}


/**
 * @brief led ctrl
 * 
 * @param[in] num: the led index
 * @param[in] status: the led status (on or off)
 * @return None
 */
void bsp_uart_rs485_com_irq_cb(void)
{
	uint8_t data = 0;
	
	if (USART_GetIntStatus(RS485_UART, USART_INT_RXDNE) != RESET)
    {
		/* Read one byte from the receive data register */
        data = USART_ReceiveData(RS485_UART);
		rs485_recv_buf[findex++] = data;
//		bsp_uart_send_data(RS485_COM, &data, 1);
    }
    if (USART_GetIntStatus(RS485_UART, USART_INT_TXDE) != RESET)
    {
        /* Write one byte to the transmit data register */
//        USART_SendData(RS485_UART, xx);
    }
    if(USART_GetIntStatus(RS485_UART, USART_INT_OREF) != RESET)
    {
        /*Read the STS register first,and the read the DAT 
        register to clear the overflow interrupt*/
        (void)RS485_UART->STS;
        (void)RS485_UART->DAT;
    }
}


/* ============================ Static Function Implementations ============================ */

/* ============================ Unit Test Support ============================ */

/**
 * @brief factory rs485 test
 * 
 * @param[in] None
 * @return None
 */
void bsp_uart_factory_rs485_check(void)
{
  /*Receive data with a length of 8 bytes*/
  if(findex == 8)
  {
    bsp_uart_send_data(RS485_COM, rs485_recv_buf, 8);
    findex = 0;
  }
}

#ifdef UNIT_TEST

#endif /* UNIT_TEST */

/**
  * @}
  */
