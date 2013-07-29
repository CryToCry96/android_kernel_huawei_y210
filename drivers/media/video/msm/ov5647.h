
/* Copyright (c) 2009, Code Aurora Forum. All rights reserved.

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#ifndef OV5647_H
#define OV5647_H

#include <linux/types.h>
#include <mach/camera.h>

struct ov5647_reg
{
    const struct register_address_value_pair *init_reg_settings;
    uint16_t                                  init_reg_settings_size;
    const struct register_address_value_pair *prev_reg_settings;
    uint16_t                                  prev_reg_settings_size;
    const struct register_address_value_pair *snap_reg_settings;
    uint16_t                                  snap_reg_settings_size;
};

#endif /* OV5647_H */

