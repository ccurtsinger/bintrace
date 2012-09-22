#ifndef BINTRACE_INSTRUCTION_HPP
#define BINTRACE_INSTRUCTION_HPP

#include <cstdlib>
#include <cassert>
#include <udis86.h>

#include <map>
#include <vector>

#include "bintrace/Context.hpp"
#include "bintrace/Operand.hpp"
#include "bintrace/TrapHandler.hpp"

using namespace std;

namespace bintrace {
	class InstructionStream;

	class Instruction {
	private:
		ud_t* ud;
		bool preserved = false;
		InstructionStream* source;

		void preserve() {
			if(!preserved) {
				ud_t* saved_ud = new ud_t;
				*saved_ud = *ud;
				ud = saved_ud;
				preserved = true;
			}
		}

	public:
		Instruction(InstructionStream* source, ud_t* ud) {
			this->source = source;
			this->ud = ud;
		}

		~Instruction() {
			if(preserved) {
				delete ud;
			}
		}

		uintptr_t base() {
			return ud_insn_off(ud);
		}

		size_t length() {
			return ud_insn_len(ud);
		}

		uintptr_t successor() {
			return base() + length();
		}
		
		int mnemonic() {
			return ud->mnemonic;
		}

		void print() {
			printf("%p: %s\n", (void*)base(), ud_insn_asm(ud));
		}

		InstructionStream* stream() {
			return source;
		}

		bool fallsThrough() {
			switch(ud->mnemonic) {
				case UD_Iret:
				case UD_Ijmp:
				case UD_Iinvalid:
					return false;
				default:
					return true;
			};
		}

		bool jumps() {
			switch(ud->mnemonic) {
				case UD_Icall:
				case UD_Ijmp:
				case UD_Ija:
				case UD_Ijae:
	            case UD_Ijb:
	            case UD_Ijbe:
	            case UD_Ijcxz:
	            case UD_Ijecxz:
	            case UD_Ijg:
	            case UD_Ijge:
	            case UD_Ijl:
	            case UD_Ijle:
	            case UD_Ijno:
	            case UD_Ijnp:
	            case UD_Ijns:
	            case UD_Ijnz:
	            case UD_Ijo:
	            case UD_Ijp:
	            case UD_Ijrcxz:
	            case UD_Ijs:
	            case UD_Ijz:
	            	return true;
            	default:
            		return false;
            }
		}

		OperandBase* target() {
			assert(jumps() && "Instruction does not have a jump target");

			switch(ud->operand[0].type) {
				case UD_OP_MEM:
					return new Operand<UD_OP_MEM>(ud->operand[0]);
				case UD_OP_JIMM:
					return new Operand<UD_OP_JIMM>(ud->operand[0]);
				case UD_OP_REG:
					return new Operand<UD_OP_REG>(ud->operand[0]);
				default:
					assert(false && "Unhandled operand type");
			}
		}

		void trap(void (*action)(Instruction*, Context*)) {
			preserve();
			TrapHandler::trap(base(), length(), this, action);
		}

		static void emulate(Instruction* inst, Context* c) {
			switch(inst->ud->mnemonic) {
				case UD_Ijmp:
					if(inst->target()->pcRelative()) {
						c->pc() = inst->target()->pcRelativeValue(c);
					} else {
						c->pc() = inst->target()->unsignedValue(c);
					}
					return;
					
				case UD_Icall:
					c->push(c->pc());
					if(inst->target()->pcRelative()) {
						c->pc() = inst->target()->pcRelativeValue(c);
					} else {
						c->pc() = inst->target()->unsignedValue(c);
					}
					return;
					
				case UD_Iret:
					c->pc() = c->pop();
					return;
					
				default:
					printf("Unhandled trap: ");
					inst->print();
					abort();
			}
		}
	};
}

#endif
