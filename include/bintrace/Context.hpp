#ifndef BINTRACE_CONTEXT_HPP
#define BINTRACE_CONTEXT_HPP

#include <cstdlib>
#include <cassert>
#include <udis86.h>

namespace bintrace {
	class Context {
	private:
		ucontext_t& context;

		enum FlagBits {
			CF = 1<<0,
			PF = 1<<2,
			AF = 1<<4,
			ZF = 1<<6,
			SF = 1<<7,
			OF = 1<<11
		};

	public:
		Context(ucontext_t* context) : context(*context) {}

		uintptr_t& pc() {
			return reg(UD_R_RIP);
		}

		uintptr_t& sp() {
			return reg(UD_R_RSP);
		}

		void push(uintptr_t value) {
			sp() -= 8;
			//printf("Pushing onto stack at %p\n", (void*)sp());
			*(uintptr_t*)sp() = value;
		}

		uintptr_t pop() {
			//printf("Popping from stack at %p\n", (void*)sp());
			uintptr_t value = *(uintptr_t*)sp();
			sp() += 8;
			return value;
		}

		uintptr_t& reg(int reg) {
			switch(reg) {
				case UD_R_RIP:
					return *(uintptr_t*)&context.uc_mcontext->__ss.__rip;
				case UD_R_RSP:
					return *(uintptr_t*)&context.uc_mcontext->__ss.__rsp;
				case UD_R_RBP:
					return *(uintptr_t*)&context.uc_mcontext->__ss.__rbp;
				case UD_R_RAX:
					return *(uintptr_t*)&context.uc_mcontext->__ss.__rax;
				case UD_R_RBX:
					return *(uintptr_t*)&context.uc_mcontext->__ss.__rbx;
				case UD_R_RCX:
					return *(uintptr_t*)&context.uc_mcontext->__ss.__rcx;
				case UD_R_RDX:
					return *(uintptr_t*)&context.uc_mcontext->__ss.__rdx;
				case UD_R_RSI:
					return *(uintptr_t*)&context.uc_mcontext->__ss.__rsi;
				case UD_R_RDI:
					return *(uintptr_t*)&context.uc_mcontext->__ss.__rdi;
				case UD_R_R8:
					return *(uintptr_t*)&context.uc_mcontext->__ss.__r8;
				case UD_R_R9:
					return *(uintptr_t*)&context.uc_mcontext->__ss.__r9;
				case UD_R_R10:
					return *(uintptr_t*)&context.uc_mcontext->__ss.__r10;
				case UD_R_R11:
					return *(uintptr_t*)&context.uc_mcontext->__ss.__r11;
				case UD_R_R12:
					return *(uintptr_t*)&context.uc_mcontext->__ss.__r12;
				case UD_R_R13:
					return *(uintptr_t*)&context.uc_mcontext->__ss.__r13;
				case UD_R_R14:
					return *(uintptr_t*)&context.uc_mcontext->__ss.__r14;
				case UD_R_R15:
					return *(uintptr_t*)&context.uc_mcontext->__ss.__r15;
				default:
					assert(false && "Unhandled register");
			}
		}

		uintptr_t& flags() {
			return *(uintptr_t*)&context.uc_mcontext->__ss.__rflags;
		}

		bool cf() {
			return (flags() & CF) == CF;
		}

		bool pf() {
			return (flags() & PF) == PF;
		}

		bool af() {
			return (flags() & AF) == AF;
		}

		bool zf() {
			return (flags() & ZF) == ZF;
		}

		bool sf() {
			return (flags() & SF) == SF;
		}

		bool of() {
			return (flags() & OF) == OF;
		}
	};
}

#endif
