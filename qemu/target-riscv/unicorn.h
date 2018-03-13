/* Unicorn Emulator Engine */
/* By Nguyen Anh Quynh <aquynh@gmail.com>, 2015 */

#ifndef UC_QEMU_TARGET_RISCV_H
#define UC_QEMU_TARGET_RISCV_H

// functions to read & write registers
int riscv32_reg_read(struct uc_struct *uc, unsigned int *regs, void **vals, int count);
int riscv32_reg_write(struct uc_struct *uc, unsigned int *regs, void *const *vals, int count);
int riscv64_reg_read(struct uc_struct *uc, unsigned int *regs, void **vals, int count);
int riscv64_reg_write(struct uc_struct *uc, unsigned int *regs, void *const *vals, int count);

void riscv32_reg_reset(struct uc_struct *uc);
void riscv64_reg_reset(struct uc_struct *uc);

void riscv32_uc_init(struct uc_struct* uc);
void riscv64_uc_init(struct uc_struct* uc);

extern const int RISCV32_REGS_STORAGE_SIZE;
extern const int RISCV64_REGS_STORAGE_SIZE;

#endif
