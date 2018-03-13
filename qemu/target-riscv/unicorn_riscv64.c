/* Unicorn Emulator Engine */
/* By Akira Moroo <retrage01@gmail.com>, 2018 */

#include "hw/boards.h"
#include "hw/riscv/riscv.h"
#include "sysemu/cpus.h"
#include "unicorn.h"
#include "cpu.h"
#include "unicorn_common.h"
#include "uc_priv.h"


const int RISCV_REGS_STORAGE_SIZE = offsetof(CPURISCVState, tlb_table);

static void riscv64_set_pc(struct uc_struct *uc, uint64_t address)
{
    ((CPURISCVState *)uc->current_cpu->env_ptr)->pc = address;
}

void riscv64_release(void *ctx);
void riscv64_release(void *ctx)
{
    struct uc_struct *uc;
    RISCVCPU *cpu;
    TCGContext *tcg_ctx = (TCGContext *) ctx;
    int i;

    g_free(tcg_ctx->tb_ctx.tbs);
    uc = tcg_ctx->uc;
    cpu = (RISCVCPU *) uc->cpu;
    for (i = 0; i < 32; i++) {
        g_free(cpu->env->gpr[i]);
        g_free(cpu->env->fpr[i]);
    }

    release_common(ctx);
}

void riscv64_reg_reset(struct uc_struct *uc)
{
    CPUArchState *env = uc->cpu->env_ptr;

    memset(env->gpr, 0, sizeof(env->gpr));
    memset(env->fpr, 0, sizeof(env->fpr));

    env->pc = 0;
}

int riscv64_reg_read(struct uc_struct *uc, unsigned int *regs, void **vals, int count)
{
    CPUState *mycpu = uc->cpu;
    int i;

    for (int i = 0; i < count; i++) {
        unsigned int regid = regs[i];
        void *value = vals[i];
        if (regid >= UC_RISCV_REG_X0 && regid <= UC_RISCV_REG_X31)
            *(uint64_t *)value = RISCV_CPU(uc, mycpu)->env.gpr[regid - UC_RISCV_REG_X0];
        else if (regid >= UC_RISCV_REG_F0 && regid <= UC_RISCV_REG_F31)
            *(uint64_t *)value = RISCV_CPU(uc, mycpu)->env.fpr[regid - UC_RISCV_REG_F0];
        else {
            switch(regid) {
                default: break;
                case UC_RISCV_REG_PC:
                         *(uint64_t *)value = RISCV_CPU(uc, mycpu)->env.pc;
                         break;
            }
        }
    }

    return 0;
}

int riscv64_reg_write(struct uc_struct *uc, unsigned int regs, void *const *vals, int count)
{
    CPUState *mycpu = uc->cpu;
    int i;

    for (i = 0; i < count; i++) {
        unsigned int regid = regs[i];
        const void *value = vals[i];
        if (regid >= UC_RISCV_REG_X0 && regid <= UC_RISCV_REG_X31)
            RISCV_CPU(uc, mycpu)->env.gpr[regid - UC_RISCV_REG_X0] = *(uint64_t *)value;
        else if (regid >= UC_RISCV_REG_F0 && regid <= UC_RISCV_REG_F31)
            RISCV_CPU(uc, mycpu)->env.fpr[regid - UC_RISCV_REG_F0] = *(uint64_t *)value;
        else {
            switch(regid) {
                default: break;
                case UC_RISCV_REG_PC:
                         RISCV_CPU(uc, mycpu)->env.pc = *(uint64_t *)value;
                         uc->quit_request = true;
                         uc_emu_stop(uc);
                         break;
            }
        }
    }

    return 0;
}

DEFAULT_VISIBILITY
void riscv64_uc_init(struct uc_struct *uc)
{
    register_accel_types(uc);
    riscv64_cpu_register_types(uc);
    uc->reg_read = riscv64_reg_read;
    uc->reg_write = riscv64_reg_write;
    uc->reg_reset = riscv64_reg_reset;
    uc->set_pc = riscv64_set_pc;
    uc->release = riscv64_release;
    uc_common_init(uc);
}
