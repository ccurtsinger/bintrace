/**
 * \file Pattern.hpp
 */

#ifndef BINTRACE_PATTERN_HPP
#define BINTRACE_PATTERN_HPP

#include <udis86.h>

namespace bintrace {
    /**
     * Functions for matching specific registers or register groups.
     */
    namespace regs {
        typedef bool (*rmatch)(ud_type);

        template<ud_type U> inline bool _reg(ud_type r) {
            return r == U;
        }

        template<ud_type U, ud_type V, ud_type ...Rest> inline bool _reg(ud_type r) {
            return r == U || _reg<V, Rest...>(r);
        }

        inline bool _(ud_type r) { return true; }
        rmatch none = _reg<UD_NONE>;

        rmatch rip = _reg<UD_R_RIP>;

        rmatch rax = _reg<UD_R_RAX>;
        rmatch rbx = _reg<UD_R_RBX>;
        rmatch rcx = _reg<UD_R_RCX>;
        rmatch rdx = _reg<UD_R_RDX>;
        rmatch rsi = _reg<UD_R_RSI>;
        rmatch rdi = _reg<UD_R_RDI>;
        rmatch rbp = _reg<UD_R_RBP>;
        rmatch rsp = _reg<UD_R_RSP>;
        rmatch r8  = _reg<UD_R_R8>;
        rmatch r9  = _reg<UD_R_R9>;
        rmatch r10 = _reg<UD_R_R10>;
        rmatch r11 = _reg<UD_R_R11>;
        rmatch r12 = _reg<UD_R_R12>;
        rmatch r13 = _reg<UD_R_R13>;
        rmatch r14 = _reg<UD_R_R14>;
        rmatch r15 = _reg<UD_R_R15>;

        rmatch gpr64 = _reg<UD_R_RAX, UD_R_RBX, UD_R_RCX, UD_R_RDX, UD_R_RSI, UD_R_RDI, UD_R_RBP, UD_R_RSP, 
                            UD_R_R8,  UD_R_R9,  UD_R_R10, UD_R_R11, UD_R_R12, UD_R_R13, UD_R_R14, UD_R_R15>;

        rmatch eax = _reg<UD_R_EAX>;
        rmatch ebx = _reg<UD_R_EBX>;
        rmatch ecx = _reg<UD_R_ECX>;
        rmatch edx = _reg<UD_R_EDX>;
        rmatch esi = _reg<UD_R_ESI>;
        rmatch edi = _reg<UD_R_EDI>;
        rmatch ebp = _reg<UD_R_EBP>;
        rmatch esp = _reg<UD_R_ESP>;
        rmatch r8d = _reg<UD_R_R8D>;
        rmatch r9d = _reg<UD_R_R9D>;
        rmatch r10d = _reg<UD_R_R10D>;
        rmatch r11d = _reg<UD_R_R11D>;
        rmatch r12d = _reg<UD_R_R12D>;
        rmatch r13d = _reg<UD_R_R13D>;
        rmatch r14d = _reg<UD_R_R14D>;
        rmatch r15d = _reg<UD_R_R15D>;

        rmatch gpr32 = _reg<UD_R_EAX, UD_R_EBX, UD_R_ECX, UD_R_EDX, UD_R_ESI, UD_R_EDI, UD_R_EBP, UD_R_ESP,
                            UD_R_R8D, UD_R_R9D, UD_R_R10D, UD_R_R11D, UD_R_R12D, UD_R_R13D, UD_R_R14D, UD_R_R15D>;

        rmatch ax = _reg<UD_R_AX>;
        rmatch bx = _reg<UD_R_BX>;
        rmatch cx = _reg<UD_R_CX>;
        rmatch dx = _reg<UD_R_DX>;
        rmatch si = _reg<UD_R_SI>;
        rmatch di = _reg<UD_R_DI>;
        rmatch bp = _reg<UD_R_BP>;
        rmatch sp = _reg<UD_R_SP>;
        rmatch r8w = _reg<UD_R_R8W>;
        rmatch r9w = _reg<UD_R_R9W>;
        rmatch r10w = _reg<UD_R_R10W>;
        rmatch r11w = _reg<UD_R_R11W>;
        rmatch r12w = _reg<UD_R_R12W>;
        rmatch r13w = _reg<UD_R_R13W>;
        rmatch r14w = _reg<UD_R_R14W>;
        rmatch r15w = _reg<UD_R_R15W>;

        rmatch gpr16 = _reg<UD_R_AX, UD_R_BX, UD_R_CX, UD_R_DX, UD_R_SI, UD_R_DI, UD_R_BP, UD_R_SP,
                            UD_R_R8W, UD_R_R9W, UD_R_R10W, UD_R_R11W, UD_R_R12W, UD_R_R13W, UD_R_R14W, UD_R_R15W>;

        rmatch al = _reg<UD_R_AL>;
        rmatch ah = _reg<UD_R_AH>;
        rmatch bl = _reg<UD_R_BL>;
        rmatch bh = _reg<UD_R_BH>;
        rmatch cl = _reg<UD_R_CL>;
        rmatch ch = _reg<UD_R_CH>;
        rmatch dl = _reg<UD_R_DL>;
        rmatch dh = _reg<UD_R_DH>;
        rmatch sil = _reg<UD_R_SIL>;
        rmatch dil = _reg<UD_R_DIL>;
        rmatch bpl = _reg<UD_R_BPL>;
        rmatch spl = _reg<UD_R_SPL>;
        rmatch r8b = _reg<UD_R_R8B>;
        rmatch r9b = _reg<UD_R_R9B>;
        rmatch r10b = _reg<UD_R_R10B>;
        rmatch r11b = _reg<UD_R_R11B>;
        rmatch r12b = _reg<UD_R_R12B>;
        rmatch r13b = _reg<UD_R_R13B>;
        rmatch r14b = _reg<UD_R_R14B>;
        rmatch r15b = _reg<UD_R_R15B>;

        rmatch gpr8 =  _reg<UD_R_AL, UD_R_AH, UD_R_BL, UD_R_BH, UD_R_CL, UD_R_CH, UD_R_DL, UD_R_DH,
                            UD_R_SIL, UD_R_DIL, UD_R_BPL, UD_R_SPL, UD_R_R8B, UD_R_R9B,
                            UD_R_R10B, UD_R_R11B, UD_R_R12B, UD_R_R13B, UD_R_R14B, UD_R_R15B>;
    };
    
    /**
     * Functions for matching operand types
     */
    namespace ops {
        typedef bool (*opmatch)(ud_operand&);
        
        inline bool _(ud_operand &op) { return true; }
        
        inline bool none(ud_operand &op) { return false; }
        
        inline bool imm(ud_operand &op) {
            return op.type == UD_OP_IMM || op.type == UD_OP_CONST;
        }
        
        inline bool rel(ud_operand &op) {
            return op.type == UD_OP_JIMM;
        }
        
        inline bool ptr(ud_operand &op) {
            return op.type == UD_OP_PTR;
        }
        
        template<regs::rmatch R=regs::_> inline bool reg(ud_operand &op) {
            return op.type == UD_OP_REG && R(op.base);
        }
        
        template<regs::rmatch B=regs::_, regs::rmatch I=regs::_> inline bool mem(ud_operand &op) {
            return op.type == UD_OP_MEM && B(op.base) && I(op.index);
        }
    };
    
    /**
     * Functions for matching specific instructions or instruction groups.
     */
    namespace instrs {
        /**
         * \brief Handy template for building instruction patterns
         * \tparam M The instruction mnemonic to match
         * \tparam O0 The operand pattern for the instruction's first operand
         * \tparam O1 The operand pattern for the instruction's second operand
         * \tparam O2 The operand pattern for the instruction's third operand
         * 
         * Check if the given mnemonic matches the disassembled instruction, then
         * check all its operands.  By default, operands should all be UD_OP_NONE.
         * 
         * \todo Maybe default operand pattern should be 'any' instead of 'none'?
         */
        template<ud_mnemonic_code_t M, ops::opmatch O0=&ops::none, ops::opmatch O1=&ops::none, ops::opmatch O2=&ops::none>
        inline bool _inst(ud_t& ud) {
            return ud.mnemonic == M && O0(ud.operand[0]) && O1(ud.operand[1]) && O2(ud.operand[2]);
        }
        
        /// Match any instruction
        inline bool _(ud_t& ud) { return true; }
        
        /// Match no instructions
        inline bool none(ud_t& ud) { return false; }
        
        /* Control Flow */
        
        /// Match a call instruction
        template<ops::opmatch D> inline bool call(ud_t& ud) { return _inst<UD_Icall, D>(ud); }
        
        /// Match a return instruction
        inline bool ret(ud_t& ud) { return _inst<UD_Iret>(ud); }
        
        /// Match a jump instruction
        template<ops::opmatch D> inline bool jmp(ud_t& ud)   { return _inst<UD_Ijmp, D>(ud); }
        
        /// Match jump if above (CF=0 and ZF=0)
        template<ops::opmatch D> inline bool ja(ud_t& ud)    { return _inst<UD_Ija, D>(ud); }
        /// Match jump if not below or equal (alias for ja)
        template<ops::opmatch D> inline bool jnbe(ud_t& ud)  { return ja<D>(ud); }
        
        /// Match jump if above or equal (CF=0)
        template<ops::opmatch D> inline bool jae(ud_t& ud)   { return _inst<UD_Ijae, D>(ud); }
        /// Match jump if not below (alias for jae)
        template<ops::opmatch D> inline bool jnb(ud_t& ud)   { return jae<D>(ud); }
        /// Match jump if not carry (alias for jae)
        template<ops::opmatch D> inline bool jnc(ud_t& ud)   { return jnc<D>(ud); }
        
        /// Match jump if below (CF=1)
        template<ops::opmatch D> inline bool jb(ud_t& ud)    { return _inst<UD_Ijb, D>(ud); }
        /// Match jump if not above or equal (alias for jb)
        template<ops::opmatch D> inline bool jnae(ud_t& ud)  { return jb<D>(ud); }
        /// Match jump if carry (alias for jb)
        template<ops::opmatch D> inline bool jc(ud_t& ud)    { return jb<D>(ud); }
        
        /// Match jump if below or equal (CF=1, ZF=1)
        template<ops::opmatch D> inline bool jbe(ud_t& ud)   { return _inst<UD_Ijbe, D>(ud); }
        /// Match jump if not above (alias for jbe)
        template<ops::opmatch D> inline bool jna(ud_t& ud)   { return jbe<D>(ud); }
        
        /// Match jump if %cx == 0
        template<ops::opmatch D> inline bool jcxz(ud_t& ud)  { return _inst<UD_Ijcxz, D>(ud); }
        
        /// Match jump if %ecx == 0
        template<ops::opmatch D> inline bool jecxz(ud_t& ud) { return _inst<UD_Ijecxz, D>(ud); }
        
        /// Match jump if %rcx == 0
        template<ops::opmatch D> inline bool jrcxz(ud_t& ud) { return _inst<UD_Ijrcxz, D>(ud); }
        
        /// Match jump if greater than (ZF == 0 and SF == OF)
        template<ops::opmatch D> inline bool jg(ud_t& ud)    { return _inst<UD_Ijg, D>(ud); }
        /// Match jump if not less than or equal (alias for jg)
        template<ops::opmatch D> inline bool jnle(ud_t& ud)  { return jg<D>(ud); }
        
        /// Match jump if greater than or equal (SF == OF)
        template<ops::opmatch D> inline bool jge(ud_t& ud)   { return _inst<UD_Ijge, D>(ud); }
        /// Match jump if not less (alias for jge)
        template<ops::opmatch D> inline bool jnl(ud_t& ud)   { return jge<D>(ud); }
        
        /// Match jump if less than (SF != OF)
        template<ops::opmatch D> inline bool jl(ud_t& ud)    { return _inst<UD_Ijl, D>(ud); }
        /// Match jump if not greater than or equal (alias for jl)
        template<ops::opmatch D> inline bool jnge(ud_t& ud)  { return jl<D>(ud); }
        
        /// Match jump if less than or equal (ZF == 1 and SF != OF)
        template<ops::opmatch D> inline bool jle(ud_t& ud)   { return _inst<UD_Ijle, D>(ud); }
        /// Match jump if not greater (alias for jle)
        template<ops::opmatch D> inline bool jng(ud_t& ud)   { return jle<D>(ud); }
        
        /// Match jump if not overflow (OF == 0)
        template<ops::opmatch D> inline bool jno(ud_t& ud)   { return _inst<UD_Ijno, D>(ud); }
        
        /// Match jump if not parity (PF == 0)
        template<ops::opmatch D> inline bool jnp(ud_t& ud)   { return _inst<UD_Ijnp, D>(ud); }
        /// Match jump if parity odd (alias for jnp)
        template<ops::opmatch D> inline bool jpo(ud_t& ud)   { return jnp<D>(ud); }
        
        /// Match jump if not sign (SF == 0)
        template<ops::opmatch D> inline bool jns(ud_t& ud)   { return _inst<UD_Ijns, D>(ud); }
        
        /// Match jump if not zero (ZF == 0)
        template<ops::opmatch D> inline bool jnz(ud_t& ud)   { return _inst<UD_Ijnz, D>(ud); }
        /// Match jump if not equal (alias for jnz)
        template<ops::opmatch D> inline bool jne(ud_t& ud)   { return jnz<D>(ud); }
        
        /// Match jump if overflow (OF == 1)
        template<ops::opmatch D> inline bool jo(ud_t& ud)    { return _inst<UD_Ijo, D>(ud); }
        
        /// Match jump if parity (PF == 1)
        template<ops::opmatch D> inline bool jp(ud_t& ud)    { return _inst<UD_Ijp, D>(ud); }
        /// Match jump if parity even (alias for jp)
        template<ops::opmatch D> inline bool jpe(ud_t& ud)   { return jp<D>(ud); }
        
        /// Match jump if sign (SF == 1)
        template<ops::opmatch D> inline bool js(ud_t& ud)    { return _inst<UD_Ijs, D>(ud); }
        
        /// Match jump if zero (ZF == 0)
        template<ops::opmatch D> inline bool jz(ud_t& ud)    { return _inst<UD_Ijz, D>(ud); }
        /// Match jump if equal (alias for jz)
        template<ops::opmatch D> inline bool je(ud_t& ud)    { return jz<D>(ud); }
        
        /// Match any jump instruction
        template<ops::opmatch D> inline bool j_(ud_t& ud) {
            return jmp<D>(ud) || ja<D>(ud) || jae<D>(ud) || jb<D>(ud)
                    || jbe<D>(ud) || jcxz<D>(ud) || jecxz<D>(ud) || jg<D>(ud) 
                    || jge<D>(ud) || jl<D>(ud) || jle<D>(ud) || jno<D>(ud) 
                    || jnp<D>(ud) || jns<D>(ud) || jnz<D>(ud) || jo<D>(ud) 
                    || jp<D>(ud) || jrcxz<D>(ud) || js<D>(ud) || jz<D>(ud);
        }
        
        /// Match any jump instruction (alias for j_)
        template<ops::opmatch D> inline bool jcc(ud_t& ud) { return j_<D>(ud); }
    };
};
#endif
