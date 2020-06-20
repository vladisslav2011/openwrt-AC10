 /*
 *  8devices Komikan devboard support
 *
 *  Copyright (C) 2018 Mantas Pucka <mantas@8devices.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/leds.h>
#include <linux/platform_device.h>
#include <linux/string.h>
#include <generated/autoconf.h>

#include "gpio.h"
#include "bspchip.h"
#include "machtypes.h"
#include "dev_leds_gpio.h"
#include "dev-gpio-buttons.h"


#define AC10UV2_BUTTONS_POLL_INTERVAL		100
#define AC10UV2_BUTTONS_DEBOUNCE_INTERVAL	(3 * AC10UV2_BUTTONS_POLL_INTERVAL)
extern void rtl819x_gpio_pin_enable(u32 pin);
extern void rtl819x_gpio_pin_set_val(u32 pin, unsigned val);

#if defined(CONFIG_RTL_8367R_SUPPORT)
#define BSP_RESET_BTN_PIN		BSP_GPIO_PIN_G6
#define BSP_WPS_BTN_PIN			BSP_GPIO_PIN_H0
#define BSP_RESET_LED_PIN		BSP_GPIO_PIN_H1
#define BSP_WPS_LED_PIN			BSP_GPIO_PIN_H1
#define BSP_8367R_RST_PIN		BSP_GPIO_PIN_H2
#define BSP_8367R_I2C_PIN1		BSP_GPIO_PIN_C2
#define BSP_8367R_I2C_PIN2		BSP_GPIO_PIN_C3
#else
#define BSP_RESET_BTN_PIN		BSP_GPIO_PIN_C3
#define BSP_WPS_BTN_PIN			BSP_GPIO_PIN_C1
#define BSP_RESET_LED_PIN		BSP_GPIO_PIN_B7
#define BSP_WPS_LED_PIN			BSP_GPIO_PIN_B7
#endif

static struct gpio_led ac10uV2_leds_gpio[] __initdata = {
	{
		.name		= "rtl819x:green:sys",
		.gpio		= BSP_WPS_LED_PIN,
		.active_low	= 1,
	}
};

static struct gpio_keys_button ac10uV2_buttons[] __initdata = {
#if 0
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = AC10UV2_BUTTONS_DEBOUNCE_INTERVAL,
		.gpio		= BSP_RESET_BTN_PIN,		
		.active_low	= 1,
	}
	,
 	{
		.desc		= "wps",
		.type		= EV_KEY,
		.code		= KEY_WPS_BUTTON,
		.debounce_interval = AC10UV2_BUTTONS_DEBOUNCE_INTERVAL,
		.gpio		= BSP_WPS_BTN_PIN,
		.active_low	= 1,
	}
#endif
};

struct gpio ac10uV2_phy_reset_pin_data = {
	.gpio		= BSP_GPIO_PIN_H2,
	.flags          = GPIOF_ACTIVE_LOW,
	.label		= "GPIO_H2",
};

static struct platform_device __initdata *ac10uV2_devs[] = {
	&rtl819x_phy_reset_pin,
};

#define SET_PINMUX(reg, field, val)\
	REG32(reg) = (REG32(reg) & (~(0xF << field))) | (val << field)



static void __init ac10uV2_setup(void)
{
	int i;


	rtl819x_phy_reset_pin.dev.platform_data = &ac10uV2_phy_reset_pin_data;

	platform_add_devices(ac10uV2_devs, ARRAY_SIZE(ac10uV2_devs));
	
	rtl819x_register_leds_gpio(-1, ARRAY_SIZE(ac10uV2_leds_gpio),
		ac10uV2_leds_gpio);

	for (i=0; i<ARRAY_SIZE(ac10uV2_leds_gpio); i++) {
		rtl819x_gpio_pin_enable(ac10uV2_leds_gpio[i].gpio);
	}

	for (i=0; i<ARRAY_SIZE(ac10uV2_buttons); i++) {
		rtl819x_gpio_pin_enable(ac10uV2_buttons[i].gpio);
	}
	rtl819x_add_device_gpio_buttons(-1, AC10UV2_BUTTONS_POLL_INTERVAL,
				       ARRAY_SIZE(ac10uV2_buttons),
				       ac10uV2_buttons);

//	ac10u_set_sd_pinmux();
}

MIPS_MACHINE(RTL8197_MACH_AC10UV2, "AC10UV2", "TENDA AC10U V2",
			 ac10uV2_setup);
