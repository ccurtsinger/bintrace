#ifndef BINTRACE_OPERAND_HPP
#define BINTRACE_OPERAND_HPP

#include <cassert>
#include <udis86.h>

#include "bintrace/Context.hpp"

namespace bintrace {
	intptr_t read_signed(int size, ud_operand_t& op) {
		switch(size) {
			case 8:
				return op.lval.sbyte;
			case 16:
				return op.lval.sword;
			case 32:
				return op.lval.sdword;
			case 64:
				return op.lval.sqword;
			default:
				return 0;
		}
	}

	uintptr_t read_unsigned(int size, ud_operand_t& op) {
		switch(size) {
			case 8:
				return op.lval.ubyte;
			case 16:
				return op.lval.uword;
			case 32:
				return op.lval.udword;
			case 64:
				return op.lval.uqword;
			default:
				return 0;
		}
	}

	class OperandBase {
	protected:
		ud_operand_t& op;

	public:
		OperandBase(ud_operand_t& op, int required_type) : op(op) {
			assert(op.type == required_type);
		}
		
		virtual void print() = 0;

		virtual bool dynamic() = 0;

		virtual bool pcRelative() {
			return false;
		}

		virtual intptr_t signedValue() {
			assert(false && "Operand does not implement a static signedValue method");
		}

		virtual intptr_t signedValue(Context* c) {
			return signedValue();
		}

		virtual uintptr_t unsignedValue() {
			assert(false && "Operand does not implement a static unsignedValue method");
		}

		virtual uintptr_t unsignedValue(Context* c) {
			return unsignedValue();
		}

		virtual uintptr_t pcRelativeValue(uintptr_t pc) {
			assert(pcRelative() && "Operand is not PC-relative");
			return pc + signedValue();
		}

		virtual uintptr_t pcRelativeValue(Context* c) {
			assert(pcRelative() && "Operand is not PC-relative");
			return c->pc() + signedValue(c);
		}
	};

	template<int Type> class Operand;

	template<> class Operand<UD_OP_MEM> : public OperandBase {
	public:
		Operand(ud_operand_t& op) : OperandBase(op, UD_OP_MEM) {}
		
		virtual void print() {
			printf("MEM\n");
		}

		virtual bool dynamic() {
			return true;
		}

		void* ptr(Context* c) {
			intptr_t offset = read_signed(OperandBase::op.offset, OperandBase::op);
			intptr_t base = OperandBase::op.base == UD_NONE ? 0 : c->reg(OperandBase::op.base);
			intptr_t index = OperandBase::op.index == UD_NONE ? 0 : c->reg(OperandBase::op.index);
			uintptr_t scale = OperandBase::op.scale;
			return (void*)(offset + base + index * scale);
		}

		virtual uintptr_t unsignedValue(Context* c) {
			uintptr_t r = *(uintptr_t*)ptr(c);
			return r;
		}

		virtual intptr_t signedValue(Context* c) {
			return *(intptr_t*)ptr(c);
		}
	};

	template<> class Operand<UD_OP_PTR> : public OperandBase {
	public:
		Operand(ud_operand_t& op) : OperandBase(op, UD_OP_PTR) {}

		virtual void print() {
			printf("PTR\n");
		}

		virtual bool dynamic() {
			return false;
		}
	};

	template<> class Operand<UD_OP_IMM> : public OperandBase {
	public:
		Operand(ud_operand_t& op) : OperandBase(op, UD_OP_IMM) {}

		virtual void print() {
			printf("IMM\n");
		}

		virtual bool dynamic() {
			return false;
		}

		virtual uintptr_t unsignedValue() {
			return read_unsigned(OperandBase::op.size, OperandBase::op);
		}

		virtual intptr_t signedValue() {
			return read_signed(OperandBase::op.size, OperandBase::op);
		}
	};

	template<> class Operand<UD_OP_JIMM> : public OperandBase {
	public:
		Operand(ud_operand_t& op) : OperandBase(op, UD_OP_JIMM) {}

		virtual void print() {
			printf("JIMM\n");
		}

		virtual bool dynamic() {
			return false;
		}

		virtual bool pcRelative() {
			return true;
		}

		virtual uintptr_t unsignedValue() {
			return read_unsigned(OperandBase::op.size, OperandBase::op);
		}

		virtual intptr_t signedValue() {
			return read_signed(OperandBase::op.size, OperandBase::op);
		}
	};

	template<> class Operand<UD_OP_CONST> : public OperandBase {
	public:
		Operand(ud_operand_t& op) : OperandBase(op, UD_OP_CONST) {}

		virtual void print() {
			printf("CONST\n");
		}

		virtual bool dynamic() {
			return false;
		}

		virtual uintptr_t unsignedValue() {
			return read_unsigned(OperandBase::op.size, OperandBase::op);
		}

		virtual intptr_t signedValue() {
			return read_signed(OperandBase::op.size, OperandBase::op);
		}
	};

	template<> class Operand<UD_OP_REG> : public OperandBase {
	public:
		Operand(ud_operand_t& op) : OperandBase(op, UD_OP_REG) {}

		virtual void print() {
			printf("REG\n");
		}

		virtual bool dynamic() {
			return true;
		}

		virtual uintptr_t unsignedValue(Context* c) {
			return c->reg(OperandBase::op.base);
		}

		virtual intptr_t signedValue(Context* c) {
			return (intptr_t)unsignedValue(c);
		}
	};
}

#endif
