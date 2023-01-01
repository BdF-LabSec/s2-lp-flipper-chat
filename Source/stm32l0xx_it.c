/**
  ******************************************************************************
  * @file    stm32l1xx_it.c
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    21-March-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2019 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_it.h"
#include "cube_hal.h"

/** @addtogroup Template_Project
  * @{
  */

extern uint16_t counter;
extern uint8_t firstinterrupt;


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval : None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval : None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval : None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval : None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval : None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval : None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval : None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval : None
  */
void PendSV_Handler(void)
{
}



/*******************************************************************************
* Function Name  : USB_LP_IRQHandler
* Description    : This function handles USB Low Priority interrupts  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//void USB_LP_IRQHandler(void)
//{
//  HAL_PCD_IRQHandler(&hpcd);
//}

void EXTI0_1_IRQHandler(void)
{
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_0) != RESET)
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  }

  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_1) != RESET)
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  }
}

void EXTI2_3_IRQHandler(void)
{
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_2) != RESET)
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
  }

  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_3) != RESET)
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
  }
}
/**
  * @brief  This function handles External External line 9 to 5 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI4_15_IRQHandler(void)
{
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_4) != RESET)
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  }
  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_5) != RESET)
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
  }
  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_6) != RESET)
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
  }
  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_7) != RESET)
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
  }
  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_8) != RESET)
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
  }
  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_9) != RESET)
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
  }

  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_10) != RESET)
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
  }
  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_11) != RESET)
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
  }
  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_12) != RESET)
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
  }
  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13) != RESET)
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
  }
  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_14) != RESET)
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
  }
  else if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_15) != RESET)
  {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
  }

}



/******************************************************************************/
/*                 STM32L15x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l1xx_lp.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval : None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */


/******************* (C) COPYRIGHT 2019 STMicroelectronics *****END OF FILE****/
