/**
 * @file bsp_uart.c
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
#include "bsp_uart.h"
#include "bsp_systick.h"

/* ============================ Module Internal Constants ============================ */

com_irq_cb_t com_irq_cb = {NULL, NULL, NULL};

/* ============================ Module Internal Data Structures ============================ */

/* ============================ Global Variables ============================ */

/* ============================ Static Global Variables ============================ */

/* ============================ Static Function Declarations ============================ */

/**
 * @brief uart relate the rcc clock config
 * 
 * @param[in] None
 * @return None
 */
static void bsp_uart_rcc_config(uart_com_e com)
{
    switch (com)
    {
    case DEBUG_COM:
        /* Enable debug uart GPIO clock */
        DEBUG_UART_TX_GPIO_CLK_CMD(DEBUG_UART_TX_GPIO_CLK, ENABLE);
        DEBUG_UART_RX_GPIO_CLK_CMD(DEBUG_UART_RX_GPIO_CLK, ENABLE);
        /* Enable debug uart Clock */
        DEBUG_UART_CLK_CMD(DEBUG_UART_CLK, ENABLE);
        break;

    case HOST_COMPUTER_COM:
        /* Enable host computer uart GPIO clock */
        HOST_COMPUTER_UART_TX_GPIO_CLK_CMD(HOST_COMPUTER_UART_TX_GPIO_CLK, ENABLE);
        HOST_COMPUTER_UART_RX_GPIO_CLK_CMD(HOST_COMPUTER_UART_RX_GPIO_CLK, ENABLE);
        /* Enable host computer uart Clock */
        HOST_COMPUTER_UART_CLK_CMD(HOST_COMPUTER_UART_CLK, ENABLE);
        break;

    case RS485_COM:
        /* Enable rs485 uart GPIO clock */
        RS485_UART_TX_GPIO_CLK_CMD(RS485_UART_TX_GPIO_CLK, ENABLE);
        RS485_UART_RX_GPIO_CLK_CMD(RS485_UART_RX_GPIO_CLK, ENABLE);
        /* Enable rs485 EN GPIO clock */
        RS485_EN_GPIO_CLK_CMD(RS485_EN_GPIO_CLK, ENABLE);
        /* Enable rs485 uart Clock */
        RS485_UART_CLK_CMD(RS485_UART_CLK, ENABLE);
        break;
    
    default:
        break;
    }
}


/**
 * @brief uart gpio config
 * 
 * @param[in] None
 * @return None
 */
void bsp_uart_gpio_config(uart_com_e com)
{
    GPIO_InitType GPIO_InitStructure = {0};

    /* Initialize GPIO_InitStructure */
    GPIO_InitStruct(&GPIO_InitStructure);

    switch (com)
    {
    case DEBUG_COM:
        /* Configure debug uart Tx as alternate function push-pull */
        GPIO_InitStructure.Pin            = DEBUG_UART_TX_PIN;
        GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Alternate = DEBUG_UART_TX_GPIO_AF;
        GPIO_InitPeripheral(DEBUG_UART_TX_GPIO, &GPIO_InitStructure);

        /* Configure debug uart Rx as alternate function push-pull */
        GPIO_InitStructure.Pin            = DEBUG_UART_RX_PIN;
        GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Alternate = DEBUG_UART_RX_GPIO_AF;
        GPIO_InitPeripheral(DEBUG_UART_RX_GPIO, &GPIO_InitStructure);
        break;

    case HOST_COMPUTER_COM:
        /* Configure host computer uart Tx as alternate function push-pull */
        GPIO_InitStructure.Pin            = HOST_COMPUTER_UART_TX_PIN;
        GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Alternate = HOST_COMPUTER_UART_TX_GPIO_AF;
        GPIO_InitPeripheral(HOST_COMPUTER_UART_TX_GPIO, &GPIO_InitStructure);
        
        /* Configure host computer uart Rx as alternate function push-pull and pull-up */
        GPIO_InitStructure.Pin            = HOST_COMPUTER_UART_RX_PIN;
        GPIO_InitStructure.GPIO_Pull      = GPIO_Pull_Up;
        GPIO_InitStructure.GPIO_Alternate = HOST_COMPUTER_UART_RX_GPIO_AF;
        GPIO_InitPeripheral(HOST_COMPUTER_UART_RX_GPIO, &GPIO_InitStructure);
        break;

    case RS485_COM:
        /* Configure rs485 uart Tx as alternate function push-pull */
        GPIO_InitStructure.Pin            = RS485_UART_TX_PIN;
        GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Alternate = RS485_UART_TX_GPIO_AF;
        GPIO_InitPeripheral(RS485_UART_TX_GPIO, &GPIO_InitStructure);
        
        /* Configure rs485 uart Rx as alternate function push-pull and pull-up */
        GPIO_InitStructure.Pin            = RS485_UART_RX_PIN;
        GPIO_InitStructure.GPIO_Pull      = GPIO_Pull_Up;
        GPIO_InitStructure.GPIO_Alternate = RS485_UART_RX_GPIO_AF;
        GPIO_InitPeripheral(RS485_UART_RX_GPIO, &GPIO_InitStructure);
    
        /* Configure rs485 EN as alternate function push-pull and pull-up */
        GPIO_InitStructure.Pin            = RS485_EN_PIN;
        GPIO_InitStructure.GPIO_Pull      = GPIO_Pull_Up;
        GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Alternate = RS485_UART_RX_GPIO_AF;
        GPIO_InitPeripheral(RS485_EN_GPIO, &GPIO_InitStructure);    
        
        /* Initial state set to receive enable */
        RS485_COM_RECV_ENABLE();
        break;
    
    default:
        break;
    }
}


/* ============================ Public Function Implementations ============================ */

/**
 * @brief initialize uart
 * 
 * @param[in] com: port number
 * @param[in] baud: baud rate
 * @param[in] irq_cb: interrupt callback function pointer
 * @return None
 */
void bsp_uart_init(uart_com_e com, uint32_t baud, void(*irq_cb)(void))
{
    USART_InitType USART_InitStructure = {0};
    NVIC_InitType NVIC_InitStructure = {0};

    USART_StructInit(&USART_InitStructure);
    bsp_uart_rcc_config(com);
    bsp_uart_gpio_config(com);

    if(irq_cb == NULL)
    {
        while (1);       
    }

    switch (com)
    {
    case DEBUG_COM:
        USART_InitStructure.BaudRate            = baud;
        USART_InitStructure.WordLength          = USART_WL_8B;
        USART_InitStructure.StopBits            = USART_STPB_1;
        USART_InitStructure.Parity              = USART_PE_NO;
        USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
        USART_InitStructure.Mode                = USART_MODE_RX|USART_MODE_TX;
        USART_Init(DEBUG_UART, &USART_InitStructure);

        NVIC_InitStructure.NVIC_IRQChannel                   = DEBUG_UART_IRQ;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        /* Assignment of callback function */
        com_irq_cb.debug_com_cb = irq_cb;

        /* Config the dubug uart interrupt */
        USART_ConfigInt(DEBUG_UART, USART_INT_RXDNE, ENABLE);

        /* Enable the debug uart */
        USART_Enable(DEBUG_UART, ENABLE);
        break;

    case HOST_COMPUTER_COM:
        USART_InitStructure.BaudRate            = baud;
        USART_InitStructure.WordLength          = USART_WL_8B;
        USART_InitStructure.StopBits            = USART_STPB_1;
        USART_InitStructure.Parity              = USART_PE_NO;
        USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
        USART_InitStructure.Mode                = USART_MODE_RX|USART_MODE_TX;
        USART_Init(HOST_COMPUTER_UART, &USART_InitStructure);

        NVIC_InitStructure.NVIC_IRQChannel                   = HOST_COMPUTER_UART_IRQ;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        /* Assignment of callback function */
        com_irq_cb.debug_com_cb = irq_cb;

        /* Config the dubug uart interrupt */
        USART_ConfigInt(HOST_COMPUTER_UART, USART_INT_RXDNE, ENABLE);

        /* Enable the debug uart */
        USART_Enable(HOST_COMPUTER_UART, ENABLE);
        break;

    case RS485_COM:
        USART_InitStructure.BaudRate            = baud;
        USART_InitStructure.WordLength          = USART_WL_8B;
        USART_InitStructure.StopBits            = USART_STPB_1;
        USART_InitStructure.Parity              = USART_PE_NO;
        USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
        USART_InitStructure.Mode                = USART_MODE_RX|USART_MODE_TX;
        USART_Init(RS485_UART, &USART_InitStructure);

        NVIC_InitStructure.NVIC_IRQChannel                   = RS485_UART_IRQ;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        /* Assignment of callback function */
        com_irq_cb.debug_com_cb = irq_cb;

        /* Config the dubug uart interrupt */
        USART_ConfigInt(RS485_UART, USART_INT_RXDNE, ENABLE);

        /* Enable the debug uart */
        USART_Enable(RS485_UART, ENABLE);
        break;
    
    default:
        break;
    }
}



/**
 * @brief send varicble-length data in blocking mode
 * 
 * @param[in] num: port number
 * @param[in] *data: data to send
 * @param[in] len: data length
 * @return None
 */
void bsp_uart_send_data(uart_com_e com, uint8_t *data, uint32_t len)
{
    int i = 0;
    USART_Module* uart = NULL;

    switch(com)
	{
    case DEBUG_COM:
        uart = DEBUG_UART;
        break;
    case HOST_COMPUTER_COM:
        uart = HOST_COMPUTER_UART;
        break;
    case RS485_COM:
        uart = RS485_UART;
        RS485_COM_SEND_ENABLE();     //Tx enable
        bsp_delay_ms(1);
        break;
	}

    if(uart == NULL)
	{
		while(1);
	}
	
	for(i = 0; i < len; i++)
	{
		USART_SendData(uart, data[i]);
		while (USART_GetFlagStatus(uart, USART_FLAG_TXDE) == RESET);
	}

    switch(com)
	{
    case DEBUG_COM:
        break;
    case HOST_COMPUTER_COM:
        break;
    case RS485_COM:
        bsp_delay_ms(1);
        RS485_COM_RECV_ENABLE();     //Rx enable
        break;
	}
}


/**
 * @brief retarget the C library printf function to the LPUARTx
 * 
 * @param[in] ch：send data
 * @param[in] f：flow
 * @return ch
 */
int fputc(int ch, FILE* f)
{
	USART_SendData(DEBUG_UART, (uint8_t)ch);
    while (USART_GetFlagStatus(DEBUG_UART, USART_FLAG_TXDE) == RESET);

    return (ch);
}


/* ============================ Static Function Implementations ============================ */

/* ============================ Unit Test Support ============================ */

#ifdef UNIT_TEST

#endif /* UNIT_TEST */

/**
  * @}
  */
