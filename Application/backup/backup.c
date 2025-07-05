/*
 * backup_app.c
 *
 *  Created on: Oct 30, 2024
 *      Author: william.favaro
 */


#include "backup.h"

#if 0
extern lfs_t lfs;
extern const struct lfs_config lfs_cfg;
extern mono_app_t mono;
extern int32_t checksum(int32_t * buffer, int32_t buffer_size);
extern limited_int32_t backlight;
extern int32_t language;//era int8_t
extern limited_int32_t led_light_intensity;

static const char file_name[] = "mono_app_v1_0_2";
__attribute__((section(".ram_d2"), used)) int32_t app_buffer[64];

//sposta i dati da quad_app ad app_buffer
void app_backup()
{
	LFS_DEBUG("app_backup\r\n");

	// Assign values from app_buffer
	app_buffer[APP_BUF_BACKLIGHT] = backlight._value;
	app_buffer[APP_BUF_LANGUAGE] = language;
	app_buffer[APP_BUF_LED_INTENSITY] = led_light_intensity._value;

	// Factory settings
	app_buffer[APP_BUF_BLOWER_ANALOG_CONTROL_ENABLED] = mono.blower.analog_control_enabled;
	app_buffer[APP_BUF_BLOWER_BYPASS_ENABLED] = mono.blower.bypass_enabled;
	app_buffer[APP_BUF_FILTER_COMPRESS_AIR_ENABLED] = mono.filter.compress_air_enabled;
	app_buffer[APP_BUF_LINE_CLEANING_ENABLED] = mono._line_cleaning_enabled;
	app_buffer[APP_BUF_PROPORTIONAL_ENABLED] = mono._proportional_enabled;
	app_buffer[APP_BUF_BLOWER_INTERNAL_VENTILATOR_ENABLED] = mono.blower.internal_ventilator_enabled;
	app_buffer[APP_BUF_NO_AIR_PRESSURE_ENABLED] = mono.no_air_pressure_enabled;
	app_buffer[APP_BUF_FILTER_DUST_CONTAINER_ENABLED] = mono.filter.dust_container_enabled;
	app_buffer[APP_BUF_FILTER_CLOGGING_ENABLED] = mono.filter.clogging_enabled;
	app_buffer[APP_BUF_RGB_LED_CONTROL_ENABLED] = mono.rgb_led_control_enabled;

	// blower
	app_buffer[APP_BUF_BLOWER_SPEEDUP_TIME] = mono.blower.speedup_timer.preset_time._value;
	app_buffer[APP_BUF_BLOWER_BYPASS_ON_DELAY_TIME] = mono.blower.bypass_on_delay_timer.preset_time._value;
	app_buffer[APP_BUF_BLOWER_VACUUM_CHARGE_TIME] = mono.blower.vacuum_charge_timer.preset_time._value;
	app_buffer[APP_BUF_BLOWER_INTERNAL_VENTILATOR_TIME] = mono.blower.internal_ventilator_timer.preset_time._value;
	app_buffer[APP_BUF_BLOWER_UPTIME_QUARTER_HOUR] = mono.blower.uptime_quarter_hour_counter;
	app_buffer[APP_BUF_BLOWER_WARNING_UPTIME_HOUR] = mono.blower.warning_uptime_hour._value;
	app_buffer[APP_BUF_BLOWER_ALARM_UPTIME_HOUR] = mono.blower.alarm_uptime_hour._value;
	app_buffer[APP_BUF_BLOWER_ANALOG_OUTPUT_ACTUAL_MV] = mono.blower.analog_output_actual_mV._value;
	app_buffer[APP_BUF_BLOWER_ANALOG_OUTPUT_OFF_MV] = mono.blower.analog_output_off_mV._value;
	app_buffer[APP_BUF_BLOWER_ANALOG_OUTPUT_START_RAMP_MV] = mono.blower.analog_output_start_ramp_mV._value;
	app_buffer[APP_BUF_BLOWER_ANALOG_OUTPUT_END_RAMP_MV] = mono.blower.analog_output_end_ramp_mV._value;

	// receiver
	app_buffer[APP_BUF_RECEIVER_1_ENABLED_BY_USER] = mono.receiver[1].enabled_by_user;
	app_buffer[APP_BUF_RECEIVER_1_GRANULAR_LEVEL_ENABLED] = mono.receiver[1].granular_level_enabled;
	app_buffer[APP_BUF_RECEIVER_1_LOADING_TIMER] = mono.receiver[1].loading_timer.preset_time._value;
	app_buffer[APP_BUF_RECEIVER_1_DISCHARGING_TIMER] = mono.receiver[1].discharging_timer.preset_time._value;
	app_buffer[APP_BUF_RECEIVER_1_WAITING_TIMER] = mono.receiver[1].waiting_timer.preset_time._value;
	app_buffer[APP_BUF_RECEIVER_1_ATTEMPT] = mono.receiver[1]._attempt;
	app_buffer[APP_BUF_RECEIVER_1_ATTEMPT_BEFORE_AUTODISABLE] = mono.receiver[1]._attempt_before_autodisable._value;
	app_buffer[APP_BUF_RECEIVER_1_LINE_CLEANING_ENABLED] = mono.receiver[1].line_cleaning_enabled;
	app_buffer[APP_BUF_RECEIVER_1_LINE_CLEANING_TIMER] = mono.receiver[1].line_cleaning_timer.preset_time._value;
	app_buffer[APP_BUF_RECEIVER_1_PROPORTIONAL_ENABLED] = mono.receiver[1].proportional_enabled;
	app_buffer[APP_BUF_RECEIVER_1_PROPORTIONAL_PERCENTAGE] = mono.receiver[1]._proportional_percentage._value;

	// filter
	app_buffer[APP_BUF_FILTER_NUMBER_OF_CLEANING_PULSE] = mono.filter._number_of_cleaning_pulse._value;
	app_buffer[APP_BUF_FILTER_PULSE_ON_TIMER] = mono.filter.pulse_on_timer.preset_time._value;
	app_buffer[APP_BUF_FILTER_PULSE_OFF_TIMER] = mono.filter.pulse_off_timer.preset_time._value;
	app_buffer[APP_BUF_FILTER_PERIODIC_CLEANING_TIMER] = mono.filter.periodic_cleaning_timer.preset_time._value;
	app_buffer[APP_BUF_FILTER_UPTIME_QUARTER_HOUR] = mono.filter.uptime_quarter_hour_counter;

}

//sposta i dati da app_buffer a quad_app
void app_recovery()
{
	LFS_DEBUG("app_recovery\r\n");

	// Assign values from app_buffer
	backlight._value = app_buffer[APP_BUF_BACKLIGHT];
	language = app_buffer[APP_BUF_LANGUAGE];
	led_light_intensity._value = app_buffer[APP_BUF_LED_INTENSITY];

	// Factory settings
	mono.blower.analog_control_enabled = app_buffer[APP_BUF_BLOWER_ANALOG_CONTROL_ENABLED];
	mono.blower.bypass_enabled = app_buffer[APP_BUF_BLOWER_BYPASS_ENABLED];
	mono.filter.compress_air_enabled = app_buffer[APP_BUF_FILTER_COMPRESS_AIR_ENABLED];
	mono._line_cleaning_enabled = app_buffer[APP_BUF_LINE_CLEANING_ENABLED];
	mono._proportional_enabled = app_buffer[APP_BUF_PROPORTIONAL_ENABLED];
	mono.blower.internal_ventilator_enabled = app_buffer[APP_BUF_BLOWER_INTERNAL_VENTILATOR_ENABLED];
	mono.no_air_pressure_enabled = app_buffer[APP_BUF_NO_AIR_PRESSURE_ENABLED];
	mono.filter.dust_container_enabled = app_buffer[APP_BUF_FILTER_DUST_CONTAINER_ENABLED];
	mono.filter.clogging_enabled = app_buffer[APP_BUF_FILTER_CLOGGING_ENABLED];
	mono.rgb_led_control_enabled = app_buffer[APP_BUF_RGB_LED_CONTROL_ENABLED];

	//blower
	// Assign values to mono.blower structure
	mono.blower.speedup_timer.preset_time._value = app_buffer[APP_BUF_BLOWER_SPEEDUP_TIME];
	mono.blower.bypass_on_delay_timer.preset_time._value = app_buffer[APP_BUF_BLOWER_BYPASS_ON_DELAY_TIME];
	mono.blower.vacuum_charge_timer.preset_time._value = app_buffer[APP_BUF_BLOWER_VACUUM_CHARGE_TIME];
	mono.blower.internal_ventilator_timer.preset_time._value = app_buffer[APP_BUF_BLOWER_INTERNAL_VENTILATOR_TIME];
	mono.blower.uptime_quarter_hour_counter = app_buffer[APP_BUF_BLOWER_UPTIME_QUARTER_HOUR];
	mono.blower.warning_uptime_hour._value = app_buffer[APP_BUF_BLOWER_WARNING_UPTIME_HOUR];
	mono.blower.alarm_uptime_hour._value = app_buffer[APP_BUF_BLOWER_ALARM_UPTIME_HOUR];
	mono.blower.analog_output_actual_mV._value = app_buffer[APP_BUF_BLOWER_ANALOG_OUTPUT_ACTUAL_MV];
	mono.blower.analog_output_off_mV._value = app_buffer[APP_BUF_BLOWER_ANALOG_OUTPUT_OFF_MV];
	mono.blower.analog_output_start_ramp_mV._value = app_buffer[APP_BUF_BLOWER_ANALOG_OUTPUT_START_RAMP_MV];
	mono.blower.analog_output_end_ramp_mV._value = app_buffer[APP_BUF_BLOWER_ANALOG_OUTPUT_END_RAMP_MV];

	// receiver
	mono.receiver[1].enabled_by_user = app_buffer[APP_BUF_RECEIVER_1_ENABLED_BY_USER];
	mono.receiver[1].granular_level_enabled = app_buffer[APP_BUF_RECEIVER_1_GRANULAR_LEVEL_ENABLED];
	mono.receiver[1].loading_timer.preset_time._value = app_buffer[APP_BUF_RECEIVER_1_LOADING_TIMER];
	mono.receiver[1].discharging_timer.preset_time._value = app_buffer[APP_BUF_RECEIVER_1_DISCHARGING_TIMER];
	mono.receiver[1].waiting_timer.preset_time._value = app_buffer[APP_BUF_RECEIVER_1_WAITING_TIMER];
	mono.receiver[1]._attempt = app_buffer[APP_BUF_RECEIVER_1_ATTEMPT];
	mono.receiver[1]._attempt_before_autodisable._value = app_buffer[APP_BUF_RECEIVER_1_ATTEMPT_BEFORE_AUTODISABLE];
	mono.receiver[1].line_cleaning_enabled = app_buffer[APP_BUF_RECEIVER_1_LINE_CLEANING_ENABLED];
	mono.receiver[1].line_cleaning_timer.preset_time._value = app_buffer[APP_BUF_RECEIVER_1_LINE_CLEANING_TIMER];
	mono.receiver[1].proportional_enabled = app_buffer[APP_BUF_RECEIVER_1_PROPORTIONAL_ENABLED];
	mono.receiver[1]._proportional_percentage._value = app_buffer[APP_BUF_RECEIVER_1_PROPORTIONAL_PERCENTAGE];

	// filter
	mono.filter._number_of_cleaning_pulse._value = app_buffer[APP_BUF_FILTER_NUMBER_OF_CLEANING_PULSE];
	mono.filter.pulse_on_timer.preset_time._value = app_buffer[APP_BUF_FILTER_PULSE_ON_TIMER];
	mono.filter.pulse_off_timer.preset_time._value = app_buffer[APP_BUF_FILTER_PULSE_OFF_TIMER];
	mono.filter.periodic_cleaning_timer.preset_time._value = app_buffer[APP_BUF_FILTER_PERIODIC_CLEANING_TIMER];
	mono.filter.uptime_quarter_hour_counter = app_buffer[APP_BUF_FILTER_UPTIME_QUARTER_HOUR];

}

void app_backup_init()
{
	LFS_DEBUG("app_backup_init\r\n");
	int32_t app_checksum_1 = 0;
	int32_t app_checksum_2 = 0;
	memset(app_buffer, 0, sizeof(app_buffer));

	//checksum applicazione
	app_backup();
	app_checksum_1 = checksum(app_buffer, sizeof(app_buffer));

	//checksum dati salvati
	if(filesystem_recovery(file_name, app_buffer, sizeof(app_buffer)) == -1)
		return;
	app_checksum_2 = checksum(app_buffer, sizeof(app_buffer));

	//confronto
	if(app_checksum_1 == app_checksum_2)
		return;

	//recovery
	filesystem_recovery(file_name, app_buffer, sizeof(app_buffer));
	app_recovery();


}

void app_backup_handler()
{
	LFS_DEBUG("app_backup_handler\r\n");
	int32_t app_checksum_1 = 0;
	int32_t app_checksum_2 = 0;
	memset(app_buffer, 0, sizeof(app_buffer));

	//checksum dati salvati
	filesystem_recovery(file_name, app_buffer, sizeof(app_buffer));
	app_checksum_2 = checksum(app_buffer, sizeof(app_buffer));

	//checksum applciazione
	app_backup();
	app_checksum_1 = checksum(app_buffer, sizeof(app_buffer));

	//confronto
	if(app_checksum_1 == app_checksum_2)
		return;

	//backup
	app_backup();
	filesystem_backup(file_name, app_buffer, sizeof(app_buffer));
}

#endif
