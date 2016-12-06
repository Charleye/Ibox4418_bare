#ifndef __S5P4418_RSTCON_H__
#define __S5P4418_RSTCON_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/types.h>
#include <linux/stddef.h>
#include <linux/malloc.h>
#include <linux/stdlib.h>
#include <io.h>
#include <linux/list.h>

enum {
	RESET_ID_AC97			= 0,
	RESET_ID_CPU1			= 1,
	RESET_ID_CPU2			= 2,
	RESET_ID_CPU3			= 3,
	RESET_ID_WD1 			= 4,
	RESET_ID_WD2 			= 5,
	RESET_ID_WD3 			= 6,
	RESET_ID_CRYPTO 		= 7,
	RESET_ID_DEINTERLACE 	= 8,
	RESET_ID_DISP_TOP		= 9,
	RESET_ID_DISPLAY		= 10,
	RESET_ID_RESCONV		= 11,
	RESET_ID_LCDIF			= 12,
	RESET_ID_HDMI			= 13,
	RESET_ID_HDMI_VIDEO		= 14,
	RESET_ID_HDMI_SPDIF		= 15,
	RESET_ID_HDMI_TMDS		= 16,
	RESET_ID_HDMI_PHY		= 17,
	RESET_ID_LVDS			= 18,
	RESET_ID_ECID			= 19,
	RESET_ID_I2C0			= 20,
	RESET_ID_I2C1			= 21,
	RESET_ID_I2C2			= 22,
	RESET_ID_I2S0			= 23,
	RESET_ID_I2S1			= 24,
	RESET_ID_I2S2			= 25,
	RESET_ID_DREX_C			= 26,
	RESET_ID_DREX_A			= 27,
	RESET_ID_DREX			= 28,
	RESET_ID_MIPI			= 29,
	RESET_ID_MIPI_DSI		= 30,
	RESET_ID_MIPI_CSI		= 31,

	RESET_ID_MIPI_PHY_S		= 32,
	RESET_ID_MIPI_PHY_M		= 33,
	RESET_ID_MPEGTSI		= 34,
	RESET_ID_PDM			= 35,
	RESET_ID_TIMER			= 36,
	RESET_ID_PWM			= 37,
	RESET_ID_SCALER			= 38,
	RESET_ID_SDMMC0			= 39,
	RESET_ID_SDMMC1			= 40,
	RESET_ID_SDMMC2			= 41,
	RESET_ID_SPDIFRX		= 42,
	RESET_ID_SPDIFTX		= 43,
	RESET_ID_SSP0_P			= 44,
	RESET_ID_SSP0			= 45,
	RESET_ID_SSP1_P			= 46,
	RESET_ID_SSP1			= 47,
	RESET_ID_SSP2_P			= 48,
	RESET_ID_SSP2			= 49,
	RESET_ID_UART0			= 50,
	RESET_ID_UART1			= 51,
	RESET_ID_UART2			= 52,
	RESET_ID_UART3			= 53,
	RESET_ID_UART4			= 54,
	RESET_ID_UART5			= 55,
	RESET_ID_USB20HOST		= 56,
	RESET_ID_USB20OTG		= 57,
	RESET_ID_WDT			= 58,
	RESET_ID_WDT_POR		= 59,
	RESET_ID_ADC			= 60,
	RESET_ID_CODA_A			= 61,
	RESET_ID_CODA_P			= 62,
	RESET_ID_CODA_C			= 63,

	RESET_ID_DWC_GMAC		= 64,
	RESET_ID_VR				= 65,
	RESET_ID_PPM			= 66,
	RESET_ID_VIP0			= 67,
	RESET_ID_VIP1			= 68,
};

void s5p4418_ip_reset(int id, int force);

#ifdef __cplusplus
}
#endif

#endif /* __S5P4418_RSTCON_H__ */
