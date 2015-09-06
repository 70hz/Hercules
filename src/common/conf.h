// Copyright (c) Hercules Dev Team, licensed under GNU GPL.
// See the LICENSE file
// Portions Copyright (c) Athena Dev Teams

#ifndef COMMON_CONF_H
#define COMMON_CONF_H

#include "common/hercules.h"

#include <libconfig/libconfig.h>

/**
 * The libconfig interface -- specially for plugins, but we enforce it throughout the core to be consistent
 **/
struct libconfig_interface {
	int (*read) (config_t *config, FILE *stream);
	void (*write) (const config_t *config, FILE *stream);
	/* */
	void (*set_auto_convert) (config_t *config, int flag);
	int (*get_auto_convert) (const config_t *config);
	/* */
	int (*read_string) (config_t *config, const char *str);
	int (*read_file_src) (config_t *config, const char *filename);
	int (*write_file) (config_t *config, const char *filename);

	void (*set_destructor) (config_t *config, void (*destructor)(void *));
	void (*set_include_dir) (config_t *config, const char *include_dir);

	void (*init) (config_t *config);
	void (*destroy) (config_t *config);

	int (*setting_get_int) (const config_setting_t *setting);
	long long (*setting_get_int64) (const config_setting_t *setting);
	double (*setting_get_float) (const config_setting_t *setting);

	int (*setting_get_bool) (const config_setting_t *setting);

	const char * (*setting_get_string) (const config_setting_t *setting);

	int (*setting_lookup_int) (const config_setting_t *setting, const char *name, int *value);
	int (*setting_lookup_int64) (const config_setting_t *setting, const char *name, long long *value);
	int (*setting_lookup_float) (const config_setting_t *setting, const char *name, double *value);
	int (*setting_lookup_bool) (const config_setting_t *setting, const char *name, int *value);
	int (*setting_lookup_string) (const config_setting_t *setting, const char *name, const char **value);
	int (*setting_set_int) (config_setting_t *setting ,int value);
	int (*setting_set_int64) (config_setting_t *setting, long long value);
	int (*setting_set_float) (config_setting_t *setting, double value);
	int (*setting_set_bool) (config_setting_t *setting, int value);
	int (*setting_set_string) (config_setting_t *setting, const char *value);

	int (*setting_set_format) (config_setting_t *setting, short format);
	short (*setting_get_format) (const config_setting_t *setting);

	int (*setting_get_int_elem) (const config_setting_t *setting, int idx);
	long long (*setting_get_int64_elem) (const config_setting_t *setting, int idx);
	double (*setting_get_float_elem) (const config_setting_t *setting, int idx);
	int (*setting_get_bool_elem) (const config_setting_t *setting, int idx);
	const char * (*setting_get_string_elem) (const config_setting_t *setting, int idx);
	config_setting_t * (*setting_set_int_elem) (config_setting_t *setting, int idx, int value);
	config_setting_t * (*setting_set_int64_elem) (config_setting_t *setting, int idx, long long value);
	config_setting_t * (*setting_set_float_elem) (config_setting_t *setting, int idx, double value);
	config_setting_t * (*setting_set_bool_elem) (config_setting_t *setting, int idx, int value);
	config_setting_t * (*setting_set_string_elem) (config_setting_t *setting, int idx, const char *value);

	int (*setting_index) (const config_setting_t *setting);
	int (*setting_length) (const config_setting_t *setting);

	config_setting_t * (*setting_get_elem) (const config_setting_t *setting, unsigned int idx);
	config_setting_t * (*setting_get_member) (const config_setting_t *setting, const char *name);

	config_setting_t * (*setting_add) (config_setting_t *parent, const char *name, int type);
	int (*setting_remove) (config_setting_t *parent, const char *name);

	int (*setting_remove_elem) (config_setting_t *parent, unsigned int idx);
	void (*setting_set_hook) (config_setting_t *setting, void *hook);

	config_setting_t * (*lookup) (const config_t *config, const char *filepath);
	config_setting_t * (*lookup_from) (config_setting_t *setting, const char *filepath);
	int (*lookup_int) (const config_t *config, const char *filepath, int *value);
	int (*lookup_int64) (const config_t *config, const char *filepath, long long *value);
	int (*lookup_float) (const config_t *config, const char *filepath, double *value);
	int (*lookup_bool) (const config_t *config, const char *filepath, int *value);
	int (*lookup_string) (const config_t *config, const char *filepath, const char **value);

	/* those are custom and are from src/common/conf.c */
	/* Functions to copy settings from libconfig/contrib */
	int (*read_file) (config_t *config, const char *config_filename);
	void (*setting_copy_simple) (config_setting_t *parent, const config_setting_t *src);
	void (*setting_copy_elem) (config_setting_t *parent, const config_setting_t *src);
	void (*setting_copy_aggregate) (config_setting_t *parent, const config_setting_t *src);
	int (*setting_copy) (config_setting_t *parent, const config_setting_t *src);
	/* Functions to get other types */
	bool (*setting_get_bool_real) (const config_setting_t *setting);
	uint32 (*setting_get_uint32) (config_setting_t *setting);
	uint16 (*setting_get_uint16) (config_setting_t *setting);
	int16 (*setting_get_int16) (config_setting_t *setting);

	int (*setting_lookup_bool_real) (const config_setting_t *setting, const char *name, bool *value);
	int (*setting_lookup_uint32) (const config_setting_t *setting, const char *name, uint32 *value);
	int (*setting_lookup_uint16) (const config_setting_t *setting, const char *name, uint16 *value);
	int (*setting_lookup_int16) (const config_setting_t *setting, const char *name, int16 *value);
	int (*setting_lookup_mutable_string) (config_setting_t *setting, const char *name, char *out, size_t out_size);
	int (*lookup_mutable_string) (config_t *config, const char *name, char *out, size_t out_size);
};

#ifdef HERCULES_CORE
void libconfig_defaults(void);
#endif // HERCULES_CORE

HPShared struct libconfig_interface *libconfig;

#endif // COMMON_CONF_H
