/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 */

#ifndef __MTK_CHARGER_H
#define __MTK_CHARGER_H

#include <linux/alarmtimer.h>
#include "charger_class.h"
#include "adapter_class.h"
#include "mtk_charger_algorithm_class.h"
/*TabA7 Lite code for OT8-89 add USB temp protection by wenyaqi at 20201213 start*/
#include "vbus_ctrl.h"
/*TabA7 Lite code for OT8-89 add USB temp protection by wenyaqi at 20201213 end*/
/*TabA7 Lite code for OT8-106 add afc charger driver by wenyaqi at 20201210 start*/
#ifdef CONFIG_AFC_CHARGER
#include "afc_charger_intf.h"
#endif
/*TabA7 Lite code for OT8-106 add afc charger driver by wenyaqi at 20201210 end*/

#define CHARGING_INTERVAL 10
#define CHARGING_FULL_INTERVAL 20

#define CHRLOG_ERROR_LEVEL	1
#define CHRLOG_INFO_LEVEL	2
#define CHRLOG_DEBUG_LEVEL	3

extern int chr_get_debug_level(void);

#define chr_err(fmt, args...)					\
do {								\
	if (chr_get_debug_level() >= CHRLOG_ERROR_LEVEL) {	\
		pr_notice(fmt, ##args);				\
	}							\
} while (0)

#define chr_info(fmt, args...)					\
do {								\
	if (chr_get_debug_level() >= CHRLOG_INFO_LEVEL) {	\
		pr_notice_ratelimited(fmt, ##args);		\
	}							\
} while (0)

#define chr_debug(fmt, args...)					\
do {								\
	if (chr_get_debug_level() >= CHRLOG_DEBUG_LEVEL) {	\
		pr_notice(fmt, ##args);				\
	}							\
} while (0)

struct mtk_charger;
/*TabA7 Lite code for SR-AX3565-01-181 config charge parameter by wenyaqi at 20201203 start*/
#define BATTERY_CV 4400000
/*TabA7 Lite code for SR-AX3565-01-181 config charge parameter by wenyaqi at 20201203 end*/
/*TabA7 Lite code for OT8-602 modify sw_ovp function by wenyaqi at 20210107 start*/
//#define V_CHARGER_MAX 6500000 /* 6.5 V */
#define V_CHARGER_MAX 10400000 /* 10.4 V */
/*TabA7 Lite code for OT8-602 modify sw_ovp function by wenyaqi at 20210107 end*/
#define V_CHARGER_MIN 4600000 /* 4.6 V */

#define USB_CHARGER_CURRENT_SUSPEND		0 /* def CONFIG_USB_IF */
#define USB_CHARGER_CURRENT_UNCONFIGURED	70000 /* 70mA */
#define USB_CHARGER_CURRENT_CONFIGURED		500000 /* 500mA */
#define USB_CHARGER_CURRENT			500000 /* 500mA */
/*TabA7 Lite code for SR-AX3565-01-181 modify AICR for Charging certification by wenyaqi at 20210201 start*/
#define AC_CHARGER_CURRENT			2000000
#define AC_CHARGER_INPUT_CURRENT		1550000
/*TabA7 Lite code for SR-AX3565-01-181 modify AICR for Charging certification by wenyaqi at 20210201 end*/
#define NON_STD_AC_CHARGER_CURRENT		500000
#define CHARGING_HOST_CHARGER_CURRENT		650000

/* dynamic mivr */
#define V_CHARGER_MIN_1 4400000 /* 4.4 V */
#define V_CHARGER_MIN_2 4200000 /* 4.2 V */
#define MAX_DMIVR_CHARGER_CURRENT 1800000 /* 1.8 A */

/* battery warning */
#define BATTERY_NOTIFY_CASE_0001_VCHARGER
#define BATTERY_NOTIFY_CASE_0002_VBATTEMP

/* charging abnormal status */
#define CHG_VBUS_OV_STATUS	(1 << 0)
#define CHG_BAT_OT_STATUS	(1 << 1)
#define CHG_OC_STATUS		(1 << 2)
#define CHG_BAT_OV_STATUS	(1 << 3)
#define CHG_ST_TMO_STATUS	(1 << 4)
#define CHG_BAT_LT_STATUS	(1 << 5)
#define CHG_TYPEC_WD_STATUS	(1 << 6)

/* Battery Temperature Protection */
#define MIN_CHARGE_TEMP  0
#define MIN_CHARGE_TEMP_PLUS_X_DEGREE	6
#define MAX_CHARGE_TEMP  50
#define MAX_CHARGE_TEMP_MINUS_X_DEGREE	47

#define MAX_ALG_NO 10

/*TabA7 Lite code for OT8-3638 import D85 policy by wenyaqi at 20210301 start*/
/*D85 setting */
#ifdef HQ_D85_BUILD
#define D85_BATTERY_CV 4000000
#define D85_JEITA_TEMP_CV 4000000
#endif
/*TabA7 Lite code for OT8-3638 import D85 policy by wenyaqi at 20210301 end*/

enum bat_temp_state_enum {
	BAT_TEMP_LOW = 0,
	BAT_TEMP_NORMAL,
	BAT_TEMP_HIGH
};

enum chg_dev_notifier_events {
	EVENT_FULL,
	EVENT_RECHARGE,
	EVENT_DISCHARGE,
};

struct battery_thermal_protection_data {
	int sm;
	bool enable_min_charge_temp;
	int min_charge_temp;
	int min_charge_temp_plus_x_degree;
	int max_charge_temp;
	int max_charge_temp_minus_x_degree;
};

/*TabA7 Lite code for SR-AX3565-01-124 Import battery aging by wenyaqi at 20201221 start*/
#ifndef HQ_FACTORY_BUILD	//ss version
#define MAX_CV_ENTRIES	8
#define MAX_CYCLE_COUNT	0xFFFF
#define is_between(left, right, value) \
		(((left) >= (right) && (left) >= (value) \
			&& (value) >= (right)) \
		|| ((left) <= (right) && (left) <= (value) \
			&& (value) <= (right)))

struct range_data {
	u32 low_threshold;
	u32 high_threshold;
	u32 value;
};
#endif
/*TabA7 Lite code for SR-AX3565-01-124 Import battery aging by wenyaqi at 20201221 end*/

/* sw jeita */
/*TabA7 Lite code for SR-AX3565-01-194 config jeita by wenyaqi at 20201204 start*/
/*TabA7 Lite code for OT8-604 modify jeita by wenyaqi at 20201230 start*/
#define JEITA_TEMP_ABOVE_T4_CV       4100000
#define JEITA_TEMP_T3_TO_T4_CV       4100000
#define JEITA_TEMP_T2_TO_T3_CV       4400000
#define JEITA_TEMP_T1_TO_T2_CV       4400000
#define JEITA_TEMP_T0_TO_T1_CV       4400000
#define JEITA_TEMP_BELOW_T0_CV       4400000
#define JEITA_TEMP_ABOVE_T4_CUR      0
#define JEITA_TEMP_T3_TO_T4_CUR      1750000
#define JEITA_TEMP_T2_TO_T3_CUR      2000000
#define JEITA_TEMP_T1_TO_T2_CUR      1500000
#define JEITA_TEMP_T0_TO_T1_CUR      500000
#define JEITA_TEMP_BELOW_T0_CUR      0
#define TEMP_T4_THRES                50
#define TEMP_T4_THRES_MINUS_X_DEGREE 48
#define TEMP_T3_THRES                45
#define TEMP_T3_THRES_MINUS_X_DEGREE 43
#define TEMP_T2_THRES                20
#define TEMP_T2_THRES_PLUS_X_DEGREE  22
#define TEMP_T1_THRES                10
#define TEMP_T1_THRES_PLUS_X_DEGREE  12
#define TEMP_T0_THRES                0
#define TEMP_T0_THRES_PLUS_X_DEGREE  2
#define TEMP_NEG_10_THRES	         0
/*TabA7 Lite code for OT8-604 modify jeita by wenyaqi at 20201230 end*/
/*TabA7 Lite code for SR-AX3565-01-194 config jeita by wenyaqi at 20201204 end*/

/*
 * Software JEITA
 * T0: -10 degree Celsius
 * T1: 0 degree Celsius
 * T2: 10 degree Celsius
 * T3: 45 degree Celsius
 * T4: 50 degree Celsius
 */
enum sw_jeita_state_enum {
	TEMP_BELOW_T0 = 0,
	TEMP_T0_TO_T1,
	TEMP_T1_TO_T2,
	TEMP_T2_TO_T3,
	TEMP_T3_TO_T4,
	TEMP_ABOVE_T4
};

struct sw_jeita_data {
	int sm;
	int pre_sm;
	int cv;
	bool charging;
	bool error_recovery_flag;
};

struct mtk_charger_algorithm {

	int (*do_algorithm)(struct mtk_charger *info);
	int (*enable_charging)(struct mtk_charger *info, bool en);
	int (*do_event)(struct notifier_block *nb, unsigned long ev, void *v);
	int (*change_current_setting)(struct mtk_charger *info);
	void *algo_data;
};

struct charger_custom_data {
	int battery_cv;	/* uv */
	int max_charger_voltage;
	int max_charger_voltage_setting;
	int min_charger_voltage;

	int usb_charger_current;
	int ac_charger_current;
	int ac_charger_input_current;
	int charging_host_charger_current;

	/* sw jeita */
	int jeita_temp_above_t4_cv;
	int jeita_temp_t3_to_t4_cv;
	int jeita_temp_t2_to_t3_cv;
	int jeita_temp_t1_to_t2_cv;
	int jeita_temp_t0_to_t1_cv;
	int jeita_temp_below_t0_cv;
	/*TabA7 Lite code for SR-AX3565-01-194 config jeita by wenyaqi at 20201204 start*/
	int jeita_temp_above_t4_cur;
	int jeita_temp_t3_to_t4_cur;
	int jeita_temp_t2_to_t3_cur;
	int jeita_temp_t1_to_t2_cur;
	int jeita_temp_t0_to_t1_cur;
	int jeita_temp_below_t0_cur;
	/*TabA7 Lite code for SR-AX3565-01-194 config jeita by wenyaqi at 20201204 end*/
	int temp_t4_thres;
	int temp_t4_thres_minus_x_degree;
	int temp_t3_thres;
	int temp_t3_thres_minus_x_degree;
	int temp_t2_thres;
	int temp_t2_thres_plus_x_degree;
	int temp_t1_thres;
	int temp_t1_thres_plus_x_degree;
	int temp_t0_thres;
	int temp_t0_thres_plus_x_degree;
	int temp_neg_10_thres;

	/* battery temperature protection */
	int mtk_temperature_recharge_support;
	int max_charge_temp;
	int max_charge_temp_minus_x_degree;
	int min_charge_temp;
	int min_charge_temp_plus_x_degree;

	/* dynamic mivr */
	int min_charger_voltage_1;
	int min_charger_voltage_2;
	int max_dmivr_charger_current;

	/*TabA7 Lite code for OT8-106 add afc charger driver by wenyaqi at 20201210 start*/
	#ifdef CONFIG_AFC_CHARGER
	int afc_start_battery_soc;
	int afc_stop_battery_soc;
	int afc_pre_input_current;
	int afc_charger_input_current;
	int afc_charger_current;
	int afc_ichg_level_threshold;
	int afc_min_charger_voltage;
	int afc_max_charger_voltage;
	#endif
	/*TabA7 Lite code for OT8-106 add afc charger driver by wenyaqi at 20201210 end*/

	/*TabA7 Lite code for SR-AX3565-01-124 Import battery aging by wenyaqi at 20201221 start*/
	#ifndef HQ_FACTORY_BUILD	//ss version
	bool ss_batt_aging_enable;
	int ss_batt_cycle;
	struct range_data batt_cv_data[MAX_CV_ENTRIES];
	#endif
	/*TabA7 Lite code for SR-AX3565-01-124 Import battery aging by wenyaqi at 20201221 start*/
};

struct charger_data {
	int input_current_limit;
	int charging_current_limit;

	int force_charging_current;
	int thermal_input_current_limit;
	int thermal_charging_current_limit;
	int disable_charging_count;
	int input_current_limit_by_aicl;
	int junction_temp_min;
	int junction_temp_max;
};

enum chg_data_idx_enum {
	CHG1_SETTING,
	CHG2_SETTING,
	CHGS_SETTING_MAX,
};

struct mtk_charger {
	struct platform_device *pdev;
	struct charger_device *chg1_dev;
	struct notifier_block chg1_nb;
	struct charger_device *chg2_dev;

	struct charger_data chg_data[CHGS_SETTING_MAX];
	struct chg_limit_setting setting;
	enum charger_configuration config;

	struct power_supply_desc psy_desc1;
	struct power_supply_config psy_cfg1;
	struct power_supply *psy1;

	struct power_supply_desc psy_desc2;
	struct power_supply_config psy_cfg2;
	struct power_supply *psy2;

	struct adapter_device *pd_adapter;
	struct notifier_block pd_nb;
	struct mutex pd_lock;
	int pd_type;
	bool pd_reset;

	u32 bootmode;
	u32 boottype;

	int chr_type;
	int usb_state;

	struct mutex cable_out_lock;
	int cable_out_cnt;

	/* system lock */
	spinlock_t slock;
	struct wakeup_source *charger_wakelock;
	struct mutex charger_lock;

	/* thread related */
	wait_queue_head_t  wait_que;
	bool charger_thread_timeout;
	unsigned int polling_interval;
	bool charger_thread_polling;

	/* alarm timer */
	struct alarm charger_timer;
	struct timespec endtime;
	bool is_suspend;
	struct notifier_block pm_notifier;

	/* notify charger user */
	struct srcu_notifier_head evt_nh;

	/* common info */
	int log_level;
	bool usb_unlimited;
	bool disable_charger;
	int battery_temp;
	bool can_charging;
	bool cmd_discharging;
	bool safety_timeout;
	bool vbusov_stat;
	bool is_chg_done;
	/*TabA7 Lite code for OT8-384 fix confliction between input_suspend and sw_ovp by wenyaqi at 20201224 start*/
	bool input_suspend;
	/*TabA7 Lite code for OT8-384 fix confliction between input_suspend and sw_ovp by wenyaqi at 20201224 end*/
	/*TabA7 Lite code for OT8-592 update battery/status when input_suspend or sw_ovp by wenyaqi at 20201231 start*/
	bool ovp_disable;
	/*TabA7 Lite code for OT8-592 update battery/status when input_suspend or sw_ovp by wenyaqi at 20201231 end*/
	/*TabA7 Lite code for OT8-739 discharging over 80 by wenyaqi at 20210104 start*/
	#ifdef HQ_FACTORY_BUILD //factory version
	bool batt_cap_control;
	#endif
	/*TabA7 Lite code for OT8-739 discharging over 80 by wenyaqi at 20210104 end*/
	/*TabA7 Lite code for P210330-05709 by wenyaqi at 20210401 start*/
	#ifndef HQ_FACTORY_BUILD	//ss version
	bool batt_store_mode;
	#endif
	/*TabA7 Lite code for P210330-05709 by wenyaqi at 20210401 end*/
	/* ATM */
	bool atm_enabled;
	/* AX3565 for SR-AX3565-01-737 add battery protect function by shixuanxuan at 2021/01/13 start */
	#if !defined(HQ_FACTORY_BUILD)
	/* AX3565 for P210308-05696 Modify battery protect function by shixuanxuan at 2021/05/10 start */
	int base_time;
	int current_time;
	int interval_time;
	int cap_hold_count;
	int recharge_count;
	int over_cap_count;
	/* AX3565 for P210308-05696 Modify battery protect function by shixuanxuan at 2021/05/10 end */
	int capacity;
	int en_batt_protect;
	bool batt_protect_flag;
	#endif
	/* AX3565 for SR-AX3565-01-737 add battery protect function by shixuanxuan at 2021/01/13 end */
	const char *algorithm_name;
	struct mtk_charger_algorithm algo;

	/* dtsi custom data */
	struct charger_custom_data data;

	/* battery warning */
	unsigned int notify_code;
	unsigned int notify_test_mode;

	/* sw safety timer */
	bool enable_sw_safety_timer;
	bool sw_safety_timer_setting;
	struct timespec charging_begin_time;

	/* sw jeita */
	bool enable_sw_jeita;
	struct sw_jeita_data sw_jeita;

	/* battery thermal protection */
	struct battery_thermal_protection_data thermal;

	struct chg_alg_device *alg[MAX_ALG_NO];
	struct notifier_block chg_alg_nb;
	bool enable_hv_charging;

	/* water detection */
	bool water_detected;

	bool enable_dynamic_mivr;
	/*TabA7 Lite code for USBIF Current-Measurement by qiaodan at 2020/05/18 start */
	#if IS_ENABLED(CONFIG_USBIF_CV_TEST)
	struct notifier_block usb_nb;
	#endif
	/*TabA7 Lite code for USBIF Current-Measurement by qiaodan at 2020/05/18 end */
	/*TabA7 Lite  code for SR-AX3565-01-109 by gaoxugang at 20201124 start*/
	#if !defined(HQ_FACTORY_BUILD)
	struct wakeup_source *charger_wakelock_app;
	struct delayed_work retail_app_status_change_work;
	#endif
	/*TabA7 Lite  code for SR-AX3565-01-109 by gaoxugang at 20201124 end*/
	/* AX3565 for SR-AX3565-01-737 add battery protect function by shixuanxuan at 2021/01/13 start */
	#if !defined(HQ_FACTORY_BUILD)
	struct delayed_work charging_count_work;
	#endif
	/* AX3565 for SR-AX3565-01-737 add battery protect function by shixuanxuan at 2021/01/13 end */
	/*TabA7 Lite code for OT8-106 add afc charger driver by wenyaqi at 20201210 start*/
	#ifdef CONFIG_AFC_CHARGER
	struct afc_dev afc;
	bool enable_afc;
	int hv_disable;
	int afc_sts;
	#endif
	/*TabA7 Lite code for OT8-106 add afc charger driver by wenyaqi at 20201210 end*/
	/*TabA7 Lite code for OT8-602 modify sw_ovp function by wenyaqi at 20210111 start*/
	int ss_vchr;
	/*TabA7 Lite code for OT8-602 modify sw_ovp function by wenyaqi at 20210111 end*/
	/*TabA7 Lite code for P210511-00511 by wenyaqi at 20210518 start*/
	#ifndef HQ_FACTORY_BUILD
	int ss_chr_type_detect;
	#endif
	/*TabA7 Lite code for P210511-00511 by wenyaqi at 20210518 end*/
};

/* functions which framework needs*/
extern int mtk_basic_charger_init(struct mtk_charger *info);
extern int mtk_pulse_charger_init(struct mtk_charger *info);
extern int get_uisoc(struct mtk_charger *info);
extern int get_battery_voltage(struct mtk_charger *info);
extern int get_battery_temperature(struct mtk_charger *info);
extern int get_battery_current(struct mtk_charger *info);
extern int get_vbus(struct mtk_charger *info);
extern int get_ibus(struct mtk_charger *info);
extern bool is_battery_exist(struct mtk_charger *info);
extern int get_charger_type(struct mtk_charger *info);
extern int disable_hw_ovp(struct mtk_charger *info, int en);
extern bool is_charger_exist(struct mtk_charger *info);
extern int get_charger_temperature(struct mtk_charger *info,
	struct charger_device *chg);
extern int get_charger_charging_current(struct mtk_charger *info,
	struct charger_device *chg);
extern int get_charger_input_current(struct mtk_charger *info,
	struct charger_device *chg);
extern int get_charger_zcv(struct mtk_charger *info,
	struct charger_device *chg);
extern void _wake_up_charger(struct mtk_charger *info);
/*TabA7 Lite code for OT8-106 add afc charger driver by wenyaqi at 20201210 start*/
#ifdef CONFIG_AFC_CHARGER
/* functions for afc */
extern void afc_set_is_enable(struct mtk_charger *pinfo, bool enable);
extern int afc_check_charger(struct mtk_charger *pinfo);
extern int afc_charge_init(struct mtk_charger *pinfo);
extern int afc_plugout_reset(struct mtk_charger *pinfo);
extern int is_afc_result(struct mtk_charger *info,int result);
#endif
/*TabA7 Lite code for OT8-106 add afc charger driver by wenyaqi at 20201210 end*/

/* functions for other */
extern int mtk_chg_enable_vbus_ovp(bool enable);
/* AX3565 for SR-AX3565-01-737 add battery protect function by shixuanxuan at 2021/01/13 start */
#if !defined(HQ_FACTORY_BUILD)
int sum_get_prop_from_battery(struct mtk_charger *info,
		enum power_supply_property psp,
		union power_supply_propval *val);
#endif
/* AX3565 for SR-AX3565-01-737 add battery protect function by shixuanxuan at 2021/01/13 start */

#endif /* __MTK_CHARGER_H */
