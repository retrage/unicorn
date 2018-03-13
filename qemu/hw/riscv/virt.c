/*
 * QEMU RISC-V VirtIO Board
 *
 * Copyright (c) 2017 SiFive, Inc.
 *
 * RISC-V machine with 16550a UART and VirtIO MMIO
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2 or later, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Unicorn engine */
/* By Akira Moroo, 2018 */

#include "hw/hw.h"
#include "hw/riscv/virt.h"
#include "sysemu/sysemu.h"
#include "hw/boards.h"
#include "exec/address-spaces.h"


static int riscv_virt_init(struct uc_struct *uc, MachineState *machine)
{
    const char *cpu_model = machine->cpu_model;

    /* init CPUs */
    if (cpu_model == NULL) {
#ifdef TARGET_RISCV64
        cpu_model = "RISCV64";
#else
        cpu_model = "RISCV32";
#endif
    }

    uc->cpu = (void *) cpu_riscv_init(uc, cpu_model);
    if (uc->cpu == NULL) {
        fprintf(stderr, "Unable to find CPU definition\n");
        return -1;
    }

    return 0;
}

void riscv_machine_init(struct uc_struct *uc)
{
    static QEMUMachine riscv_machine = {
        NULL,
        "riscv",
        riscv_virt_init,
        NULL,
        0,
        1,
        UC_ARCH_RISCV,
    };

    qemu_register_machine(uc, &riscv_machine, TYPE_MACHINE, NULL);
}
