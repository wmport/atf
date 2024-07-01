/*
 * Copyright (c) 2017-2024, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SDS_H
#define SDS_H

/* SDS Structure Identifier defines */
/* AP CPU INFO defines */
#define SDS_AP_CPU_INFO_STRUCT_ID		1
#define SDS_AP_CPU_INFO_PRIMARY_CPUID_OFFSET	0x0
#define SDS_AP_CPU_INFO_PRIMARY_CPUID_SIZE	0x4

/* ROM Firmware Version defines */
#define SDS_ROM_VERSION_STRUCT_ID		2
#define SDS_ROM_VERSION_OFFSET			0x0
#define SDS_ROM_VERSION_SIZE 			0x4

/* RAM Firmware version defines */
#define SDS_RAM_VERSION_STRUCT_ID		3
#define SDS_RAM_VERSION_OFFSET			0x0
#define SDS_RAM_VERSION_SIZE			0x4

/* Platform Identity defines */
#define SDS_PLATFORM_IDENTITY_STRUCT_ID		4
#define SDS_PLATFORM_IDENTITY_ID_OFFSET		0x0
#define SDS_PLATFORM_IDENTITY_ID_SIZE		0x4
#define SDS_PLATFORM_IDENTITY_ID_CONFIG_SHIFT	28
#define SDS_PLATFORM_IDENTITY_ID_CONFIG_WIDTH	4
#define SDS_PLATFORM_IDENTITY_ID_CONFIG_MASK	\
	((1 << SDS_PLATFORM_IDENTITY_ID_CONFIG_WIDTH) - 1)

#define SDS_PLATFORM_IDENTITY_PLAT_TYPE_OFFSET	0x4
#define SDS_PLATFORM_IDENTITY_PLAT_TYPE_SIZE	0x4

/* Reset Syndrome defines */
#define SDS_RESET_SYNDROME_STRUCT_ID		5
#define SDS_RESET_SYNDROME_OFFSET		0
#define SDS_RESET_SYNDROME_SIZE			4
#define SDS_RESET_SYNDROME_POW_ON_RESET_BIT	(1 << 0)
#define SDS_RESET_SYNDROME_SCP_WD_RESET_BIT	(1 << 1)
#define SDS_RESET_SYNDROME_AP_WD_RESET_BIT	(1 << 2)
#define SDS_RESET_SYNDROME_SYS_RESET_REQ_BIT	(1 << 3)
#define SDS_RESET_SYNDROME_M3_LOCKUP_BIT	(1 << 4)

/* SCP Firmware Feature Availability defines */
#define SDS_FEATURE_AVAIL_STRUCT_ID		6
#define SDS_FEATURE_AVAIL_OFFSET		0
#define SDS_FEATURE_AVAIL_SIZE			4
#define SDS_FEATURE_AVAIL_SCP_RAM_READY_BIT	(1 << 0)
#define SDS_FEATURE_AVAIL_DMC_READY_BIT		(1 << 1)
#define SDS_FEATURE_AVAIL_MSG_IF_READY_BIT	(1 << 2)

/* SCP BL2 Image Metadata defines */
#define SDS_SCP_IMG_STRUCT_ID			9
#define SDS_SCP_IMG_FLAG_OFFSET			0
#define SDS_SCP_IMG_FLAG_SIZE			4
#define SDS_SCP_IMG_VALID_FLAG_BIT		(1 << 0)
#define SDS_SCP_IMG_ADDR_OFFSET			4
#define SDS_SCP_IMG_ADDR_SIZE			4
#define SDS_SCP_IMG_SIZE_OFFSET			8
#define SDS_SCP_IMG_SIZE_SIZE			4

/* SDS Driver Error Codes */
#define SDS_OK				0
#define SDS_ERR_FAIL			-1
#define SDS_ERR_INVALID_PARAMS		-2
#define SDS_ERR_STRUCT_NOT_FOUND	-3
#define SDS_ERR_STRUCT_NOT_FINALIZED	-4

#ifndef __ASSEMBLER__
#include <stddef.h>
#include <stdint.h>

typedef enum {
	SDS_ACCESS_MODE_NON_CACHED,
	SDS_ACCESS_MODE_CACHED,
} sds_access_mode_t;

/*
 * The following structure describes a SDS memory region. Its items are used
 * to track and maintain the state of the memory region reserved for usage
 * by the SDS framework.
 *
 * The base address of the SDS memory region is platform specific. The
 * SDS description structure must already contain the address when it is
 * returned by the plat_sds_get_regions() platform API during SDS region
 * initialization.
 * The size of the SDS memory region is dynamically discovered during the
 * initialization of the region and written into the 'size' item of the
 * SDS description structure.
 */
typedef struct {
	uintptr_t base;	/* Pointer to the base of the SDS memory region */
	size_t size;	/* Size of the SDS memory region in bytes */
} sds_region_desc_t;

/* API to get the platform specific SDS region description(s) */
sds_region_desc_t *plat_sds_get_regions(unsigned int *region_count);

int sds_init(unsigned int region_id);
int sds_struct_exists(unsigned int region_id, unsigned int structure_id);
int sds_struct_read(unsigned int region_id, uint32_t structure_id,
	unsigned int fld_off, void *data, size_t size, sds_access_mode_t mode);
int sds_struct_write(unsigned int region_id, uint32_t structure_id,
	unsigned int fld_off, void *data, size_t size, sds_access_mode_t mode);
#endif /*__ASSEMBLER__ */

#endif /* SDS_H */
