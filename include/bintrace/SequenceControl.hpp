#ifndef BINTRACE_SEQUENCE_CONTROL_HPP
#define BINTRACE_SEQUENCE_CONTROL_HPP

namespace bintrace {
	/**
	 * Every Sequence extends this class, which is passed to every Handler's onMatch method.
	 * The handler can use this class to control the behavior of the disassembly sequence.
	 */
	class SequenceControl {
	public:
		virtual void fork(void* p) = 0;
	};
}

#endif