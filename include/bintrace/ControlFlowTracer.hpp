#ifndef BINTRACE_CONTROLFLOWTRACER_HPP
#define BINTRACE_CONTROLFLOWTRACER_HPP

#include <udis86.h>
#include "bintrace.h"

namespace bintrace {
	class ControlFlowTracer {
	public:
		void run(Interval<ControlFlowTracer>* interval) {
			while(ud_t* inst = interval->next()) {
				intptr_t inst_base = ud_insn_off(inst);
				intptr_t pc = inst_base + ud_insn_len(inst);

				ud_operand_t& op = inst->operand[0];

				printf("%p: %s\n", (void*)inst_base, ud_insn_asm(inst));

				// A bunch of instructions jump to their first operand
				switch(inst->mnemonic) {
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
		            	switch(op.type) {
		            		case UD_OP_PTR:
		            			printf("PTR\n");
		            			break;

		            		case UD_OP_JIMM:
			            		switch(op.size) {
			            			case 8:
			            				printf("### JIMM to %p\n", (void*)(pc + op.lval.sbyte));
			            				interval->fork(pc + op.lval.sbyte);
			            				break;
			            			case 16:
			            				printf("### JIMM to %p\n", (void*)(pc + op.lval.sword));
			            				interval->fork(pc + op.lval.sword);
			            				break;
			            			case 32:
			            				printf("### JIMM to %p\n", (void*)(pc + op.lval.sdword));
			            				interval->fork(pc + op.lval.sdword);
				            			break;
			            			case 64:
			            				printf("### JIMM to %p\n", (void*)(pc + op.lval.sqword));
			            				interval->fork(pc + op.lval.sqword);
				            			break;
			            		}
			            		break;

			            	case UD_OP_REG:
			            		printf("REG\n");
			            		break;

			            	case UD_OP_MEM:
			            		if(op.base != UD_R_RIP || op.index != UD_NONE) {
			            			break;
			            		}

			            		int64_t offset;
			            		switch(op.offset) {
			            			case 8:
			            				offset = op.lval.sbyte;
			            				break;
			            			case 16:
			            				offset = op.lval.sword;
			            				break;
			            			case 32:
			            				offset = op.lval.sdword;
			            				break;
			            			case 64:
			            				offset = op.lval.sqword;
			            				break;
			            			default:
			            				offset = 0;
			            		}

			            		printf("#### going to %p\n", (void*)(pc + offset));
			            		interval->fork(*(intptr_t*)(pc + offset));

			            		break;

			            	default:
			            		printf("OTHER\n");
			            		break;
		            	}
		            
		            default:
		            break;
				}

				if(inst->mnemonic == UD_Iinvalid) {
					printf("Badness\n");
				}

				// Returns and jumps end the current sequence of instructions
				if(inst->mnemonic == UD_Iret || inst->mnemonic == UD_Ijmp || inst->mnemonic == UD_Iinvalid) {
					interval->finished();
					return;
				}
			}
		}
	};
}

#endif
