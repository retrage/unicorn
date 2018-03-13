/*
 * SiFive VirtIO Board
 *
 * Copyright (c) 2017 SiFive, Inc.
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

#ifndef HW_RISCV_H
#define HW_RISCV_H

void riscv_machine_init(struct uc_struct *uc);
void riscv_cpu_register_types(void *opaque);

#endif
