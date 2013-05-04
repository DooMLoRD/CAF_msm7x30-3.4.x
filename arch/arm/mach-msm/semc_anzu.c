/* /kernel/arch/arm/mach-msm/semc_anzu.c
 *
 * Copyright (C) 2010 Sony Ericsson Mobile Communications AB.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2, as
 * published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 *
 * Changes by irii-soft
 * 
 */
#include <mach/board-semc_mogami.h>

/* Charger */

static struct ambient_temperature_limit limit_tbl = {
	{0,	42,	43,	127},	/* ambient temp: base */
	{4,	1,	37,	0},	/* ambient temp: hysteresis */
};

struct device_data device_data = {
	.limit_tbl = &limit_tbl,
	.battery_capacity_mah = 1500,
	.maximum_charging_current_ma = 1050,
};

/* GPIO */

struct msm_gpio qup_i2c_gpios_hw[] = {
	{ GPIO_CFG(16, 2, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_4MA),
		"qup_scl" },
	{ GPIO_CFG(17, 2, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_4MA),
		"qup_sda" },
};

int qup_i2c_gpios_hw_size = ARRAY_SIZE(qup_i2c_gpios_hw);

struct msm_gpio qup_i2c_gpios_io[] = {
	{ GPIO_CFG(16, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_4MA),
		"qup_scl" },
	{ GPIO_CFG(17, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_4MA),
		"qup_sda" },
};

struct msm_gpio qsd_spi_gpio_config_data[] = {
	{ GPIO_CFG(45, 1, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
		"spi_clk" },
	{ GPIO_CFG(46, 1, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
		"spi_cs0" },
	{ GPIO_CFG(47, 1, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA),
		"spi_mosi" },
	{ GPIO_CFG(48, 1, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA),
		"spi_miso" },
};

int qsd_spi_gpio_config_data_size = ARRAY_SIZE(qsd_spi_gpio_config_data);

struct msm_gpio msm_i2c_gpios_hw[] = {
	{ GPIO_CFG(70, 1, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_4MA),
		"i2c_scl" },
	{ GPIO_CFG(71, 1, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_4MA),
		"i2c_sda" },
};

int msm_i2c_gpios_hw_size = ARRAY_SIZE(msm_i2c_gpios_hw);

struct msm_gpio msm_i2c_gpios_io[] = {
	{ GPIO_CFG(70, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_4MA),
		"i2c_scl" },
	{ GPIO_CFG(71, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_4MA),
		"i2c_sda" },
};

/* Keymap */

static const unsigned int keymap[] = {
	KEY(0, 0, KEY_BACK),
	KEY(0, 1, KEY_HOME),
	KEY(0, 2, KEY_MENU),
	KEY(0, 3, KEY_VOLUMEUP),
	KEY(0, 4, KEY_VOLUMEDOWN),
	KEY(0, 5, KEY_CAMERA),
	KEY(0, 6, KEY_CAMERA_FOCUS),
};

static struct matrix_keymap_data keymap_data = {
	.keymap_size	= ARRAY_SIZE(keymap),
	.keymap		= keymap,
};

static struct pm8xxx_keypad_platform_data anzu_keypad_data = {
	.input_name		= PM8058_KEYPAD_DEV,
	.input_phys_device	= PM8058_KEYPAD_PHYS,
	.num_rows		= 5,
	.num_cols		= 7,
	.rows_gpio_start	= PM8058_GPIO_PM_TO_SYS(8),
	.cols_gpio_start	= PM8058_GPIO_PM_TO_SYS(0),
	.debounce_ms		= 10, //{8, 10},
	.scan_delay_ms		= 2,
	.row_hold_ns		= 122000,
	.wakeup			= 1,
	.keymap_data		= &keymap_data,
};

struct pm8xxx_keypad_platform_data *mogami_keypad_data(void)
{
	return &anzu_keypad_data;
}

/* Leds */

static struct as3676_platform_led as3676_leds_mapping[] = {
	{
		.name = "lcd-backlight",
		.sinks = BIT(AS3676_SINK_01),
		.flags = AS3676_FLAG_ALS | AS3676_FLAG_WAIT_RESUME,
		.max_current = 25000,
		.default_brightness = LED_FULL,
	},
	{
		.name = "button-backlight",
		.sinks = BIT(AS3676_SINK_RGB1) | BIT(AS3676_SINK_RGB2),
		.max_current = 25000,
	},
	{
		.name = "red",
		.sinks = BIT(AS3676_SINK_41),
		.flags = AS3676_FLAG_RGB | AS3676_FLAG_BLINK,
		.max_current = 25000,
	},
	{
		.name = "green",
		.sinks = BIT(AS3676_SINK_42),
		.flags = AS3676_FLAG_RGB | AS3676_FLAG_BLINK,
		.max_current = 25000,
	},
	{
		.name = "blue",
		.sinks = BIT(AS3676_SINK_43),
		.flags = AS3676_FLAG_RGB | AS3676_FLAG_BLINK,
		.max_current = 25000,
	},
};

struct as3676_platform_data as3676_platform_data = {
	.leds = as3676_leds_mapping,
	.num_leds = 5, //ARRAY_SIZE(as3676_leds_mapping),
	.als_connected = 1,
	.als_wait = 100,
	.dls_connected = false,
	.ldo_mV = 3300,
};
