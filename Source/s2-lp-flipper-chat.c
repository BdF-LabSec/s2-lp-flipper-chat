/*	Benjamin DELPY `gentilkiwi`
	LabSec - DGSI DIT ARCOS
	benjamin.delpy@banque-france.fr / benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "SDK_EVAL_Config.h"
#include "S2LP_Config.h"
#include "SDK_Configuration_Common.h"
#include "st_main.h"

#define USE_VCOM
#define FLIPPER_MAX_RECV	(64 - 2)
#define FLIPPER_DELAY		5
#define KIWI_DEVICE_NAME	"gentilkiwi"

const char KIWI_DISPLAY[] = "\x1b[0;92m" KIWI_DEVICE_NAME "\x1b[0m: ";
const char *KIWI_MSG_APPEAR[4] = {
	/* 0 */	"\r\n"
			"  .#####.\r\n",
	/* 1 */	" .## ^ ##.__ _    Wild \x1b[0;96m" KIWI_DEVICE_NAME "\x1b[0m\r\n",
	/* 2 */	" ## / \\ /   ('>-  appeared!\r\n"
			" ## \\ / | K  |\r\n"
			" '## v #\\____/\r\n",
	/* 3 */	"  '#####' L\\_     \x1b[0;95mHello Flipper Zero!\x1b[0m\r\n"
			"\r\n"
};
const char KIWI_BANNER[] = 	"\x1b[2J\x1b[3J\x1b[H\r\n"
	"  .#####.         S2-LP mimichat 0.1\r\n"
	" .## ^ ##.__ _    Edition LabSec! - (oe.eo)\r\n"
	" ## / \\ /   ('>-  /*** \r\n"
	" ## \\ / | K  |     DGSI - DIT - ARCOS | LABSEC ( benjamin.delpy@banque-france.fr )\r\n"
	" '## v #\\____/     Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com )\r\n"
	"  '#####' L\\_      ***/\r\n";
const char TOO_LONG_MSG[] = "\x1b[2K\r\x1b[0;91m< TOO LONG! >\x1b[0m\r";

volatile FlagStatus xTxDoneFlag = RESET;
static uint32_t M2S_GPIO_PIN_IRQ;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	S2LPIrqs xIrqStatus;
	uint8_t dataBuffer[FLIPPER_MAX_RECV], cbDataBuffer;
	
	if(GPIO_Pin == M2S_GPIO_PIN_IRQ)
	{
		S2LPGpioIrqGetStatus(&xIrqStatus);

		if(xIrqStatus.IRQ_TX_DATA_SENT)
		{
			xTxDoneFlag = SET;
		}

		if(xIrqStatus.IRQ_RX_DATA_READY)
		{
			SdkEvalLedOn(LED2);
			
			cbDataBuffer = S2LPFifoReadNumberBytesRxFifo();
			if(cbDataBuffer <= sizeof(dataBuffer))
			{
				S2LPSpiReadFifo(cbDataBuffer, dataBuffer);
			}
			else cbDataBuffer = 0;
			
			S2LPCmdStrobeFlushRxFifo();
			
			if(cbDataBuffer)
			{
				printf("\x1b[2K\r [%4i] %.*s%s", S2LPRadioGetRssidBm(), cbDataBuffer, (char*) dataBuffer, KIWI_DISPLAY);
			}
			S2LPCmdStrobeRx();
			
			SdkEvalLedOff(LED2);
		}
	}
}

void SendData(const uint8_t * pcbMessage, const uint16_t cbMessage)
{
	S2LPPktBasicSetPayloadLength(cbMessage);
	S2LPCmdStrobeFlushTxFifo();
	S2LPSpiWriteFifo(cbMessage, (uint8_t *) pcbMessage);

	S2LPGpioIrqConfig(RX_DATA_DISC, S_DISABLE);
	S2LPCmdStrobeSabort();
	S2LPGpioIrqClearStatus();
	S2LPGpioIrqConfig(RX_DATA_DISC, S_ENABLE);

	S2LPCmdStrobeTx();

	while(!xTxDoneFlag);
	xTxDoneFlag = RESET;

	SdkDelayMs(FLIPPER_DELAY);
}

const SRadioInit xRadioInit = {
	.lFrequencyBase = 433920000,
	.xModulationSelect = MOD_2GFSK_BT1,
	.lDatarate = 9995,
	.lFreqDev = 19025,
	.lBandwidth = 100000
};
const SRssiInit xSRssiInit = {
	.cRssiFlt = 14,
	.xRssiMode = RSSI_STATIC_MODE,
	.cRssiThreshdBm = -70,
};
const PktBasicInit xBasicInit= {
	.xPreambleLength = PREAMBLE_BYTE(4),
	.xSyncLength = SYNC_BYTE(2),
	.lSyncWords = 'FLIP', // only FL (0x464c0000) used ;)
	.xFixVarLength = S_ENABLE,
	.cExtendedPktLenField = S_DISABLE,
	.xCrcMode = PKT_CRC_MODE_16BITS_1,
	.xAddressField = S_DISABLE,
	.xFec = S_DISABLE,
	.xDataWhitening = S_DISABLE
};
const SGpioInit xGpioIRQ = {
	.xS2LPGpioPin = S2LP_GPIO_3,
	.xS2LPGpioMode = S2LP_GPIO_MODE_DIGITAL_OUTPUT_LP,
	.xS2LPGpioIO = S2LP_GPIO_DIG_OUT_IRQ
};

int main (void)
{
	uint8_t tmpBuffer, messageBuffer[FLIPPER_MAX_RECV - (sizeof(KIWI_DISPLAY) - 1) - 2 + 1], cbMessageBuffer, dataBuffer[FLIPPER_MAX_RECV + 1], cbDataBuffer;
	
	ST_Init();

	/* uC IRQ config */
	S2LP_Middleware_GpioInit(M2S_GPIO_3, M2S_MODE_EXTI_IN);
	M2S_GPIO_PIN_IRQ = S2LP_Middleware_GpioGetPin(M2S_GPIO_3);

	/* S2LP IRQ config */
	S2LPGpioInit((SGpioInit *) &xGpioIRQ);

	/* uC IRQ enable */
	S2LP_Middleware_GpioInterruptCmd(M2S_GPIO_3, 0x03, 0, ENABLE); // IRQ_PREEMPTION_PRIORITY

	S2LPRadioInit((SRadioInit *) &xRadioInit);
	S2LPRadioSetMaxPALevel(S_DISABLE);
	S2LPRadioSetPALeveldBm(7, POWER_DBM);
	S2LPRadioSetPALevelMaxIndex(7);
	S2LPPktBasicInit((PktBasicInit *) &xBasicInit);
	S2LPRadioRssiInit((SRssiInit *) &xSRssiInit);
	S2LPRadioCsBlanking(S_ENABLE);
	
	S2LPSpiReadRegisters(PCKTCTRL3_ADDR, 1, &tmpBuffer);
	MODIFY_REG(tmpBuffer, PREAMBLE_SEL_REGMASK, 0x01); // PREAMBLE_SEL 1010...
	S2LPSpiWriteRegisters(PCKTCTRL3_ADDR, 1, &tmpBuffer);

	S2LPGpioIrqDeInit(NULL);
	S2LPGpioIrqConfig(TX_DATA_SENT , S_ENABLE);
	S2LPGpioIrqConfig(RX_DATA_READY, S_ENABLE);
	S2LPGpioIrqClearStatus();

	puts(KIWI_BANNER);
	
	for(tmpBuffer = 0; tmpBuffer < (sizeof(KIWI_MSG_APPEAR) / sizeof(KIWI_MSG_APPEAR[0])); tmpBuffer++)
	{
		SendData((const uint8_t *) KIWI_MSG_APPEAR[tmpBuffer], strlen(KIWI_MSG_APPEAR[tmpBuffer]));
	}

	while (1)
	{
		fputs(KIWI_DISPLAY, stdout);
		while(__io_getcharNonBlocking(messageBuffer))
			;
		S2LPCmdStrobeRx();

		for(cbMessageBuffer = 0; cbMessageBuffer < sizeof(messageBuffer); cbMessageBuffer++)
		{
			while(!__io_getcharNonBlocking(messageBuffer + cbMessageBuffer));

			if((messageBuffer[cbMessageBuffer] != '\r') && (messageBuffer[cbMessageBuffer] != '\n'))
			{
				putchar(messageBuffer[cbMessageBuffer]);
			}
			else
			{
				puts("\r");
				break;
			}
		}
		
		if(cbMessageBuffer < sizeof(messageBuffer))
		{
			cbDataBuffer = sprintf((char *) dataBuffer, "%s%.*s\r\n",  KIWI_DISPLAY, cbMessageBuffer, messageBuffer);
			SendData(dataBuffer, cbDataBuffer);
		}
		else puts(TOO_LONG_MSG);
	}
}
