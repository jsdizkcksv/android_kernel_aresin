/*
 * Copyright (C) 2019 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 */

#include <linux/kernel.h>
#include <mt-plat/mtk_devinfo.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <helio-dvfsrc-opp.h>
#include <helio-dvfsrc-qos.h>

#ifdef CONFIG_MTK_DRAMC
#include <mtk_dramc.h>
#endif
#define SOC_CPE_DETECT

#ifndef CONFIG_MTK_DRAMC
static int dram_steps_freq(unsigned int step)
{
	pr_info("get dram steps_freq fail\n");
	return 4266;
}
#endif

int ddr_level_to_step(int opp)
{
/* TODO check later  */
	return 0;
}

void dvfsrc_opp_level_mapping(void)
{
	set_vcore_opp(VCORE_DVFS_OPP_0, VCORE_OPP_0);
	set_vcore_opp(VCORE_DVFS_OPP_1, VCORE_OPP_0);
	set_vcore_opp(VCORE_DVFS_OPP_2, VCORE_OPP_1);
	set_vcore_opp(VCORE_DVFS_OPP_3, VCORE_OPP_0);
	set_vcore_opp(VCORE_DVFS_OPP_4, VCORE_OPP_1);
	set_vcore_opp(VCORE_DVFS_OPP_5, VCORE_OPP_2);
	set_vcore_opp(VCORE_DVFS_OPP_6, VCORE_OPP_0);
	set_vcore_opp(VCORE_DVFS_OPP_7, VCORE_OPP_1);
	set_vcore_opp(VCORE_DVFS_OPP_8, VCORE_OPP_2);
	set_vcore_opp(VCORE_DVFS_OPP_9, VCORE_OPP_3);
	set_vcore_opp(VCORE_DVFS_OPP_10, VCORE_OPP_0);
	set_vcore_opp(VCORE_DVFS_OPP_11, VCORE_OPP_1);
	set_vcore_opp(VCORE_DVFS_OPP_12, VCORE_OPP_2);
	set_vcore_opp(VCORE_DVFS_OPP_13, VCORE_OPP_3);
	set_vcore_opp(VCORE_DVFS_OPP_14, VCORE_OPP_0);
	set_vcore_opp(VCORE_DVFS_OPP_15, VCORE_OPP_1);
	set_vcore_opp(VCORE_DVFS_OPP_16, VCORE_OPP_2);
	set_vcore_opp(VCORE_DVFS_OPP_17, VCORE_OPP_3);
	set_vcore_opp(VCORE_DVFS_OPP_18, VCORE_OPP_0);
	set_vcore_opp(VCORE_DVFS_OPP_19, VCORE_OPP_1);
	set_vcore_opp(VCORE_DVFS_OPP_20, VCORE_OPP_2);
	set_vcore_opp(VCORE_DVFS_OPP_21, VCORE_OPP_3);


	set_ddr_opp(VCORE_DVFS_OPP_0, DDR_OPP_0);
	set_ddr_opp(VCORE_DVFS_OPP_1, DDR_OPP_1);
	set_ddr_opp(VCORE_DVFS_OPP_2, DDR_OPP_1);
	set_ddr_opp(VCORE_DVFS_OPP_3, DDR_OPP_2);
	set_ddr_opp(VCORE_DVFS_OPP_4, DDR_OPP_2);
	set_ddr_opp(VCORE_DVFS_OPP_5, DDR_OPP_2);
	set_ddr_opp(VCORE_DVFS_OPP_6, DDR_OPP_3);
	set_ddr_opp(VCORE_DVFS_OPP_7, DDR_OPP_3);
	set_ddr_opp(VCORE_DVFS_OPP_8, DDR_OPP_3);
	set_ddr_opp(VCORE_DVFS_OPP_9, DDR_OPP_3);
	set_ddr_opp(VCORE_DVFS_OPP_10, DDR_OPP_4);
	set_ddr_opp(VCORE_DVFS_OPP_11, DDR_OPP_4);
	set_ddr_opp(VCORE_DVFS_OPP_12, DDR_OPP_4);
	set_ddr_opp(VCORE_DVFS_OPP_13, DDR_OPP_4);
	set_ddr_opp(VCORE_DVFS_OPP_14, DDR_OPP_5);
	set_ddr_opp(VCORE_DVFS_OPP_15, DDR_OPP_5);
	set_ddr_opp(VCORE_DVFS_OPP_16, DDR_OPP_5);
	set_ddr_opp(VCORE_DVFS_OPP_17, DDR_OPP_5);
	set_ddr_opp(VCORE_DVFS_OPP_18, DDR_OPP_6);
	set_ddr_opp(VCORE_DVFS_OPP_19, DDR_OPP_6);
	set_ddr_opp(VCORE_DVFS_OPP_20, DDR_OPP_6);
	set_ddr_opp(VCORE_DVFS_OPP_21, DDR_OPP_6);
}

void dvfsrc_opp_table_init(void)
{
	int i;
	int vcore_opp, ddr_opp;

	for (i = 0; i < VCORE_DVFS_OPP_NUM; i++) {
		vcore_opp = get_vcore_opp(i);
		ddr_opp = get_ddr_opp(i);

		if (vcore_opp == VCORE_OPP_UNREQ || ddr_opp == DDR_OPP_UNREQ) {
			set_opp_table(i, 0, 0);
			continue;
		}
		set_opp_table(i, get_vcore_uv_table(vcore_opp),
		dram_steps_freq(ddr_level_to_step(ddr_opp)) * 1000);
	}
}

static int is_ct_support(void)
{
	int ret = 0;

	return ret;
}

static int is_aging_test(void)
{
	int ret = 0;

#if defined(CONFIG_ARM64) && \
	defined(CONFIG_BUILD_ARM64_DTB_OVERLAY_IMAGE_NAMES)

	pr_info("[VcoreFS] flavor name: %s\n",
		CONFIG_BUILD_ARM64_DTB_OVERLAY_IMAGE_NAMES);

	if ((strstr(CONFIG_BUILD_ARM64_DTB_OVERLAY_IMAGE_NAMES,
			"k85v1_64_aging") != NULL)) {
		pr_info("[VcoreFS]: AGING flavor !!!\n");
		return 1;
	}
#endif
	return ret;
}

static int is_qea_test(void)
{
	int ret = 0;

	return ret;
}

static int __init dvfsrc_opp_init(void)
{
	struct device_node *dvfsrc_node = NULL;
	int vcore_opp_0_uv, vcore_opp_1_uv, vcore_opp_2_uv, vcore_opp_3_uv;
	int i;
	int is_vcore_qea = is_qea_test();
	int is_vcore_ct = is_ct_support();
	int is_vcore_aging = is_aging_test();
	int doe_ct = 0;
	int doe_vcore_mode = 0;
	int dvfs_v_mode = 0;

	set_pwrap_cmd(VCORE_OPP_0, 0);
	set_pwrap_cmd(VCORE_OPP_1, 1);
	set_pwrap_cmd(VCORE_OPP_2, 2);
	set_pwrap_cmd(VCORE_OPP_3, 3);

	vcore_opp_0_uv = 725000;
	vcore_opp_1_uv = 650000;
	vcore_opp_2_uv = 600000;
	vcore_opp_3_uv = 550000;

	dvfsrc_node =
		of_find_compatible_node(NULL, NULL, "mediatek,dvfsrc");

	/* For Doe */
	if (dvfsrc_node) {
		if (of_property_read_u32(dvfsrc_node, "vcore_ct",
			(u32 *) &doe_ct) == 0) {
			is_vcore_ct = doe_ct;
			pr_info("%s: DOE CT = %d\n", __func__, doe_ct);
		}
		if (of_property_read_u32(dvfsrc_node, "dvfs_v_mode",
			(u32 *) &dvfs_v_mode) == 0)
			pr_info("%s: DOE DVFS_V_MODE = %d\n",
				__func__, dvfs_v_mode);

		if (of_property_read_u32(dvfsrc_node, "doe_vcore_mode",
			(u32 *) &doe_vcore_mode) == 0) {
			pr_info("%s: DOE DRAM_VCORE_MODE = %d\n",
				__func__, doe_vcore_mode);
#if 0 /* TODO: fill when LV/HV setting*/
			if (doe_vcore_mode == 1) {
				/*Doe HV */
				doe_vcore_mode = 1;
			} else if (doe_vcore_mode == 3)  {
				/*Doe LV */
				doe_vcore_mode = 3;
			} else {
				/*Doe NV */
				doe_vcore_mode = 0;
			}
#endif
		}
	}
#if 0 /* TODO: fill when LV/HV setting*/

	if (doe_vcore_mode == 0) {
		if (is_vcore_qea || (dvfs_v_mode == 3)) {
			/* LV */
			doe_vcore_mode = 3;
		} else if (dvfs_v_mode == 1) {
			/* HV */
			doe_vcore_mode = 1;
		} else if (is_vcore_aging) {
			/*Doe NV */
			doe_vcore_mode = 0;
		}
	}
#endif

	pr_info("%s: CT=%d, AGING=%d, QEA=%d, VMODE=%d\n",
		__func__,
		is_vcore_ct,
		is_vcore_aging,
		is_vcore_qea,
		dvfs_v_mode);

	pr_info("%s: FINAL vcore_opp_uv: %d, %d, %d %d\n",
		__func__,
		vcore_opp_0_uv,
		vcore_opp_1_uv,
		vcore_opp_2_uv,
		vcore_opp_3_uv);

	set_vcore_uv_table(VCORE_OPP_0, vcore_opp_0_uv);
	set_vcore_uv_table(VCORE_OPP_1, vcore_opp_1_uv);
	set_vcore_uv_table(VCORE_OPP_2, vcore_opp_2_uv);
	set_vcore_uv_table(VCORE_OPP_3, vcore_opp_3_uv);

	for (i = 0; i < DDR_OPP_NUM; i++) {
		set_opp_ddr_freq(i,
			dram_steps_freq(ddr_level_to_step(i)) * 1000);
	}

	return 0;
}

fs_initcall_sync(dvfsrc_opp_init)
