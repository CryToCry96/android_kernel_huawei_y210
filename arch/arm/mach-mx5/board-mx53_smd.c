/*
 * Copyright (C) 2011 Freescale Semiconductor, Inc. All Rights Reserved.
 */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <linux/init.h>
#include <linux/clk.h>
#include <linux/fec.h>
#include <linux/delay.h>
#include <linux/gpio.h>

#include <mach/common.h>
#include <mach/hardware.h>
#include <mach/imx-uart.h>
#include <mach/iomux-mx53.h>

#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/time.h>

#include "crm_regs.h"
#include "devices-imx53.h"

#define SMD_FEC_PHY_RST		IMX_GPIO_NR(7, 6)

static iomux_v3_cfg_t mx53_smd_pads[] = {
	MX53_PAD_CSI0_D10__UART1_TXD,
	MX53_PAD_CSI0_D11__UART1_RXD,
	MX53_PAD_ATA_DIOW__UART1_TXD,
	MX53_PAD_ATA_DMACK__UART1_RXD,

	MX53_PAD_ATA_BUFFER_EN__UART2_RXD,
	MX53_PAD_ATA_DMARQ__UART2_TXD,
	MX53_PAD_ATA_DIOR__UART2_RTS,
	MX53_PAD_ATA_INTRQ__UART2_CTS,

	MX53_PAD_ATA_CS_0__UART3_TXD,
	MX53_PAD_ATA_CS_1__UART3_RXD,
	MX53_PAD_ATA_DA_1__UART3_CTS,
	MX53_PAD_ATA_DA_2__UART3_RTS,
};

static const struct imxuart_platform_data mx53_smd_uart_data __initconst = {
	.flags = IMXUART_HAVE_RTSCTS,
};

static inline void mx53_smd_init_uart(void)
{
	imx53_add_imx_uart(0, &mx53_smd_uart_data);
	imx53_add_imx_uart(1, &mx53_smd_uart_data);
	imx53_add_imx_uart(2, &mx53_smd_uart_data);
}

static inline void mx53_smd_fec_reset(void)
{
	int ret;

	/* reset FEC PHY */
	ret = gpio_request(SMD_FEC_PHY_RST, "fec-phy-reset");
	if (ret) {
		printk(KERN_ERR"failed to get GPIO_FEC_PHY_RESET: %d\n", ret);
		return;
	}
	gpio_direction_output(SMD_FEC_PHY_RST, 0);
	msleep(1);
	gpio_set_value(SMD_FEC_PHY_RST, 1);
}

static struct fec_platform_data mx53_smd_fec_data = {
	.phy = PHY_INTERFACE_MODE_RMII,
};

static void __init mx53_smd_board_init(void)
{
	mxc_iomux_v3_setup_multiple_pads(mx53_smd_pads,
					ARRAY_SIZE(mx53_smd_pads));
	mx53_smd_init_uart();
	mx53_smd_fec_reset();
	imx53_add_fec(&mx53_smd_fec_data);
}

static void __init mx53_smd_timer_init(void)
{
	mx53_clocks_init(32768, 24000000, 22579200, 0);
}

static struct sys_timer mx53_smd_timer = {
	.init	= mx53_smd_timer_init,
};

MACHINE_START(MX53_SMD, "Freescale MX53 SMD Board")
	.map_io = mx53_map_io,
	.init_irq = mx53_init_irq,
	.init_machine = mx53_smd_board_init,
	.timer = &mx53_smd_timer,
MACHINE_END
