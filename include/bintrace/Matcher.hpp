#ifndef BINTRACE_MATCHER_HPP
#define BINTRACE_MATCHER_HPP

namespace bintrace {
	class SequenceControl;

	/**
	 * The Matcher class takes one or more handlers, each of which can examine instructions
	 * and modify the Sequence when a match is found.
	 */
	template<class ...H> class Matcher;

	/**
	 * Base case for the Matcher variadic template
	 */
	template<> class Matcher<> {
	public:
		static inline void match(SequenceControl* seq, ud_t* ud) {}
	};

	/**
	 * Check if the first handler matches, call its onMatch method, then recursively check the remaining handlers.
	 */
	template<class H, class ...Rest> class Matcher<H, Rest...> {
	public:
		static inline void match(SequenceControl* seq, ud_t* ud) {
			if(H::match(ud)) {
				H::onMatch(seq, ud);
			}
		
			Matcher<Rest...>::match(seq, ud);
		}
	};
}

#endif
