#ifndef _MAIN_H
#define _MAIN_H

/**
* @file    st_maing.h
* @author  AMG & HEA & RF BU
* @date    May, 2019
* @brief   S2-LP Examples Library
* @details
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* THIS SOURCE CODE IS PROTECTED BY A LICENSE.
* FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED
* IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
*
* <h2><center>&copy; COPYRIGHT 2019 STMicroelectronics</center></h2>
*/
/* Includes ------------------------------------------------------------------*/
#include "assert.h"
#include "stddef.h"
#include <stdio.h>
#include <string.h>
#include "stdarg.h"
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

/* ST Init */
#include "ST_Init.h"

/* Load all SDK layers */
#include "SDK_EVAL_Config.h"
#include "SDK_UTILS_Config.h"
#include "S2LP_Middleware_Config.h"

#define FW_VERSION      "2.3.0"

#if (defined(BLUENRG2_DEVICE) || defined(BLUENRG1_DEVICE))
    #define S2LP_Middleware_GpioInterruptCmd(pA, pB, pC, pD) S2LP_Middleware_GpioInterruptCmd(pA, pB, pC, pD, M2S_GPIO_EDGE_EVENT)
#endif


/* Fucntions Prototypes-------------------------------------------------------*/
extern uint8_t responsePrintf(const char * formatString, ...);
extern uint8_t responseHeaderPrintf(const char * formatString, ...);

/* Commands callbacks */
static void helpAction(void);
static void interactiveAction(void);
static void fwVersionAction(void);
static void rebootAction(void);
void Appli_Exti_CB(uint32_t GPIO_Pin, uint32_t timer);

#endif

