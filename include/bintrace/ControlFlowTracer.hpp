#ifndef BINTRACE_CONTROLFLOWTRACER_HPP
#define BINTRACE_CONTROLFLOWTRACER_HPP

#include "bintrace/Context.hpp"
#include "bintrace/Instruction.hpp"
#include "bintrace/Driver.hpp"

namespace bintrace {
	class ControlFlowTracer {
	private:
		static void disassemble(Instruction* inst, Context* c) {
			inst->stream()->fork(c->pc());
		}
		
	public:
		void run(Interval<ControlFlowTracer>* interval) {
			while(Instruction* inst = interval->next()) {
				inst->print();
				if(inst->jumps()) {
					OperandBase* op = inst->target();

					if(!op->dynamic()) {
						if(op->pcRelative()) {
							interval->fork(op->pcRelativeValue(inst->successor()));
						} else {
							interval->fork(op->unsignedValue());
						}

					} else {
						// Emulate dynamic control flow instructions
						inst->trap(Instruction::emulate);
						
						// Continue disassembly at the target address
						inst->trap(ControlFlowTracer::disassemble);
					}
				}

				if(!inst->fallsThrough()) {
					interval->end();
				}
			}
		}
	};
}

#endif
