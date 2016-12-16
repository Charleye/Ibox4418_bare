#ifndef __S5P4418_RSTCON_H__
#define __S5P4418_RSTCON_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>
#include <stddef.h>
#include <malloc.h>
#include <stdlib.h>
#include <list.h>
#include <io.h>

enum {
    /* IP RESET REG0 */
	RESET_ID_AC97			= 0,
	RESET_ID_CPU1			= 1,
	RESET_ID_CPU2			= 2,
	RESET_ID_CPU3			= 3,
	RESET_ID_WD1 			= 4,    /* Watch Dog Timer1 Reset */
	RESET_ID_WD2 			= 5,
	RESET_ID_WD3 			= 6,
	RESET_ID_CRYPTO 		= 7,    /* Crypto Engine Reset */
	RESET_ID_DEINTERLACE 	= 8,    /* Deinterlace Reset */
	RESET_ID_DISP_TOP		= 9,    /* Display Block Total */
	RESET_ID_DISPLAY		= 10,   /* Dual Display (MLC & DPC) */

//	RESET_ID_RESCONV		= 11,
//	RESET_ID_LCDIF			= 12,
	RESET_ID_HDMI			= 13,   /* HDMI LINK & CEC */
	RESET_ID_HDMI_VIDEO		= 14,   /* HDMI LINK VIDEO Block */
	RESET_ID_HDMI_SPDIF		= 15,   /* HDMI LINK SPDIF Block */
	RESET_ID_HDMI_TMDS		= 16,   /* HDMI LINK TMDS Block */
	RESET_ID_HDMI_PHY		= 17,   /* HDMI PHY */
	RESET_ID_LVDS			= 18,   /* LVDS PHY */
	RESET_ID_I2C0			= 19,
	RESET_ID_I2C1			= 20,
	RESET_ID_I2C2			= 21,
	RESET_ID_I2S0			= 22,
	RESET_ID_I2S1			= 23,
	RESET_ID_I2S2			= 24,
	RESET_ID_MCUYZTOP_C		= 25,   /* Memory Controller APB Interface */
	RESET_ID_MCUYZTOP_A		= 26,   /* Memory Controller AXI Interface */
	RESET_ID_MCUYZTOP   	= 27,   /* Memory Controller Core */
	RESET_ID_MIPI			= 28,   /* MIPI Register Interface */
	RESET_ID_MIPI_DSI		= 29,   /* MIPI DSI Master */
	RESET_ID_MIPI_CSI		= 30,   /* MIPI CSI Slave */
    RESET_ID_MIPI_PHY_S     = 31,   /* MIPI D-PHY Slave Channel */

    /* IP RESET REG1 */
	RESET_ID_MIPI_PHY_M		= 32,   /* MIPI D-PHY Master Channel */
	RESET_ID_MPEGTSI		= 33,   /* MPEG-TSI */
	RESET_ID_PDM			= 34,
	RESET_ID_PWMTIMER0		= 35,   /* PWMTIMER0 */
	RESET_ID_PWMTIMER1		= 36,
	RESET_ID_SCALER			= 37,
	RESET_ID_SDMMC0			= 38,   /* SDMMC Controller 0 */
	RESET_ID_SDMMC1			= 39,
	RESET_ID_SDMMC2			= 40,
	RESET_ID_SPDIFRX		= 41,
	RESET_ID_SPDIFTX		= 42,
	RESET_ID_SSP0_P			= 43,   /* SSP0 APB Interface */
	RESET_ID_SSP0			= 44,   /* SSP0 Core */
	RESET_ID_SSP1_P			= 45,
	RESET_ID_SSP1			= 46,
	RESET_ID_SSP2_P			= 47,
	RESET_ID_SSP2			= 48,
	RESET_ID_UART0			= 49,
	RESET_ID_UART1			= 50,
	RESET_ID_UART2			= 51,
	RESET_ID_UART3			= 52,
	RESET_ID_UART4			= 53,

	RESET_ID_USB20HOST		= 55,   /* USB 2.0 Host */
	RESET_ID_USB20OTG		= 56,   /* USB 2.0 OTG */
	RESET_ID_WDT			= 57,   /* WDT APB */
	RESET_ID_WDT_POR		= 58,
	RESET_ID_ADC			= 59,
	RESET_ID_CODA_A			= 60,   /* Multi-Format Video Codec AXI Interface */
	RESET_ID_CODA_P			= 61,   /* Multi-Format Video Codec APB Interface */
	RESET_ID_CODA_C			= 62,   /* Multi-Format Video Codec Core */
    RESET_ID_DWC_GMAC		= 63,

    /* IP RESET REG2 */
    RESET_3DGPU             = 64,   /* 3D GPU */
	RESET_ID_PPM			= 65,
	RESET_ID_VIP0			= 66,   /* VIP Controller 0 */
	RESET_ID_VIP1			= 67,
};

void s5p4418_ip_reset(int id, int force);

#ifdef __cplusplus
}
#endif

#endif /* __S5P4418_RSTCON_H__ */
