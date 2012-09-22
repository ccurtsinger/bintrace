#ifndef BINTRACE_INSTRUCTIONSTREAM_HPP
#define BINTRACE_INSTRUCTIONSTREAM_HPP

#include <cstdlib>

#include "bintrace/Instruction.hpp"

namespace bintrace {
	class InstructionStream {
	public:
		/// Get the next instruction
		virtual Instruction* next() = 0;

		/// Skip the next byte
		virtual void skip() = 0;

		/// Start a new thread of disassembly
		virtual void fork(uintptr_t request) = 0;

		/// End this thread of disassembly
		virtual void end() = 0;
	};
}

#endif
