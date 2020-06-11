#pragma once

#define ISOTEE_GUEST_TASK_ENTRY    0xFFE00000U
#define ISOTEE_GUEST_TASK_PRIORITY TMAX_TPRI
#define ISOTEE_GUEST_TASK_STK_SIZE 4096U
#define ISOTEE_GUEST_TEST_SWINT    16 /* DUMMY */
#define ISOTEE_GUEST_TICK_MS       1U
#define ISOTEE_GUEST_ROM_BASE      0xFFE00000U
#define ISOTEE_GUEST_ROM_SIZE      0x100000U
#define ISOTEE_GUEST_RAM_BASE      0x00810000U
#define ISOTEE_GUEST_RAM_SIZE      0x50000U
#define ISOTEE_RX_ETHER_DESC_BASE  0x00800000U
#define ISOTEE_RX_ETHER_DESC_SIZE  0x0100U
#define ISOTEE_RX_ETHER_BUFF_BASE  0x00800100U
#define ISOTEE_RX_ETHER_BUFF_SIZE  0x1900U

extern void	main_task(intptr_t exinf);