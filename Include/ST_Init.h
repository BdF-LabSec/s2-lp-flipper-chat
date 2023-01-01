/* Load all SDK layers */
#include "SDK_EVAL_Config.h"
#include "SDK_UTILS_Config.h"
#include "S2LP_Middleware_Config.h"

#define USE_VCOM

/**
* @brief  System main initialization.
* @param  None
* @retval 0 if OK
*/
int ST_Init(void);

/**
* @brief  PUSH BUTTON initialization.
* @param  None
* @retval 1 if PUSH BUTTON is pressed while init
*/
uint8_t ButtonInit(void);

/**
* @brief  PUSH BUTTON IRQ initialization.
* @param  None
* @retval None
*/
void ButtonSetIRQ(void);

