/****************************************************************************
**
** This file is part of the QMiniNVMeDevice library.
** Copyright (C) 2024 Alexander E. <aekhv@vk.com>
** License: GNU GPL v2, see file LICENSE.
**
****************************************************************************/

#ifndef QMININVMECOMMON_H
#define QMININVMECOMMON_H

#include "stdint.h"

#pragma once

// Some useful NVME admin opcodes...
#define NVME_ADMIN_IDENTIFY             0x06
#define NVME_ADMIN_IDENTIFY_NAMESPACE   0x00
#define NVME_ADMIN_IDENTIFY_CONTROLLER  0x01

#define NVME_ADMIN_GET_LOG_PAGE                     0x02
#define NVME_ADMIN_GET_LOG_PAGE_ERROR_INFORMATION   0x01
#define NVME_ADMIN_GET_LOG_PAGE_HEALTH_INFORMATION  0x02

// Structures...
typedef struct {
    uint8_t data[32];
} nvme_power_state_descriptor_t;

typedef struct {
    uint16_t vid;       // PCI Vendor ID
    uint16_t ssvid;     // PCI Subsystem Vendor ID
    char sn[20];        // Serial Number
    char mn[40];        // Model Name
    char fr[8];         // Firmware Revision
    uint8_t rab;        // Recommended Arbitration Burst
    uint8_t ieee[3];    // IEEE OUI Identifier
    uint8_t cmic;       // Controller Multi-Path I/O and Namespace Sharing Capabilities
    uint8_t mdts;       // Maximum Data Transfer Size
    uint8_t rsvd0[178];
    uint16_t oacs;      // Optional Admin Command Support
    uint8_t acl;        // Abort Command Limit
    uint8_t aerl;       // Asynchronous Event Request Limit
    uint8_t frmw;       // Firmware Updates
    uint8_t lpa;        // Log Page Attributes
    uint8_t elpe;       // Error Log Page Entries
    uint8_t npss;       // Number of Power States Support
    uint8_t avscc;      // Admin Vendor Specific Command Configuration

    uint8_t apsta;      // Autonomous Power State Transition Attributes
    uint16_t wctemp;    // Warning Composite Temperature Threshold
    uint16_t cctemp;    // Critical Composite Temperature Threshold
    uint16_t mtfa;      // Maximum Time for Firmware Activation
    uint32_t hmpre;     // Host Memory Buffer Preferred Size
    uint32_t hmmin;     // Host Memory Buffer Minimum Size
    uint64_t tnvmcap_lo;    // Total NVM Capacity
    uint64_t tnvmcap_hi;
    uint64_t unvmcap_lo;    // Unallocated NVM Capacity
    uint64_t unvmcap_hi;
    uint8_t rsvd1[200];

    //uint8_t rsvd1[247];
    uint8_t sqes;       // Submission Queue Entry Size
    uint8_t cqes;       // Completion Queue Entry Size
    uint8_t rsvd2[2];
    uint32_t nn;        // Number of Namespaces
    uint16_t oncs;      // Optional NVM Command Support
    uint16_t fuses;     // Fused Operation Support
    uint8_t fna;        // Format NVM Attributes
    uint8_t vwc;        // Volatile Write Cache
    uint16_t awun;      // Atomic Write Unit Normal
    uint16_t awupf;     // Atomic Write Unit Power Fail
    uint8_t nvscc;      // NVM Vendor Specific Command Configuration
    uint8_t rsvd3[1517];
    nvme_power_state_descriptor_t psd[32];  // Power State Descriptors
    uint8_t vs[1024];   // Vendor Specific
} nvme_controller_info_t;

static_assert(sizeof(nvme_controller_info_t) == 4096, "Incorrect size!");

typedef struct {
    uint16_t ms;        // Metadata Size
    uint8_t lbads;      // LBA Data Size
    uint8_t rp : 2;     // Relative Performance
    uint8_t rsvd : 6;
} nvme_lba_format_t;

typedef struct {
    uint64_t nsze;      // Namespace Size
    uint64_t ncap;      // Namespace Capacity
    uint64_t nuse;      // Namespace Utilization
    uint8_t nsfeat;     // Namespace Features
    uint8_t nlbaf;      // Number of LBA Formats
    uint8_t flbas;      // Formatted LBA Size
    uint8_t mc;         // Metadata Capabilities
    uint8_t dpc;        // End-to-end Data Protection Capabilities
    uint8_t dps;        // End-to-end Data Protection Type Settings
    uint8_t rsvd0[98];
    nvme_lba_format_t lbaf[16]; // LBA Format Support
    uint8_t rsvd1[192];
    uint8_t vs[3712];   // Vendor Specific
} nvme_namespace_info_t;

static_assert(sizeof(nvme_namespace_info_t) == 4096, "Incorrect size!");

typedef struct {
    uint32_t lid : 8;   // Log Page Identifier
    uint32_t rsvd : 8;
    uint32_t numd : 16; // Number of Dwords
} nvme_log_page_cdw10_t;

static_assert(sizeof(nvme_log_page_cdw10_t) == 4, "Incorrect size!");

typedef struct {
    uint64_t ec;        // Error Count
    uint16_t sqid;      // Submission Queue ID
    uint16_t cid;       // Command ID
    uint16_t sf;        // Status Field
    uint16_t pel;       // Parameter Error Location
    uint64_t lba;       // LBA
    uint32_t nsid;      // Namespace ID
    uint8_t vsia;       // Vendor Specific Information Available
    uint8_t tt;         // Transport Type
    uint8_t rsvd0[2];
    uint64_t csi;       // Command Specific Information
    uint16_t ttsi;      // Transport Type Specific Information
    uint8_t rsvd1[22];
} nvme_log_page_error_information_entry_t;

static_assert(sizeof(nvme_log_page_error_information_entry_t) == 64, "Incorrect size!");

typedef struct {
    uint8_t cw;         // Critical Warning
    uint8_t ct[2];      // Composite Temperature
    uint8_t as;         // Available Spare
    uint8_t ast;        // Available Spare Threshold
    uint8_t pu;         // Percentage Used
    uint8_t egcws;      // Endurance Group Critical Warning Summary
    uint8_t rsvd0[25];
    uint64_t dur_lo;    // Data Units Read
    uint64_t dur_hi;
    uint64_t duw_lo;    // Data Units Written
    uint64_t duw_hi;
    uint64_t hrc_lo;    // Host Read Commands
    uint64_t hrc_hi;
    uint64_t hwc_lo;    // Host Write Commands
    uint64_t hwc_hi;
    uint64_t cbt_lo;    // Controller Busy Time
    uint64_t cbt_hi;
    uint64_t pc_lo;     // Power Cycles
    uint64_t pc_hi;
    uint64_t poh_lo;    // Power On Hours
    uint64_t poh_hi;
    uint64_t us_lo;     // Unsafe Shutdowns
    uint64_t us_hi;
    uint64_t mdie_lo;   // Media and Data Integrity Errors
    uint64_t mdie_hi;
    uint64_t neile_lo;  // Number of Error Information Log Entries
    uint64_t neile_hi;
    uint32_t wctt;      // Warning Composite Temperature Time
    uint32_t cctt;      // Critical Composite Temperature Time
    uint16_t ts[8];     // Temperature Sensors 1...8
    uint32_t tmt1tc;    // Thermal Management Temperature 1 Transition Count
    uint32_t tmt2tc;    // Thermal Management Temperature 2 Transition Count
    uint32_t tttmt1;    // Total Time For Thermal Management Temperature 1
    uint32_t tttmt2;    // Total Time For Thermal Management Temperature 2
    uint8_t rsvd1[280];
} nvme_log_page_health_information_t;

static_assert(sizeof(nvme_log_page_health_information_t) == 512, "Incorrect size!");

#endif // QMININVMECOMMON_H
