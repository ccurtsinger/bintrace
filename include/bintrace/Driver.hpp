#ifndef BINTRACE_INTERVALQUEUE_HPP
#define BINTRACE_INTERVALQUEUE_HPP

#include <cstdlib>
#include <cassert>
#include <set>
#include <map>

#include <udis86.h>

#include "bintrace/Interval.hpp"
#include "bintrace/TrapHandler.hpp"

using namespace std;

namespace bintrace {
	template<class T> struct Driver {
	private:
		Interval<T> root;
		
	public:
		Driver() : root(this, 0, 0) {}
		
		template<typename Ret, typename... Args> Ret execute(Ret (*fn)(Args...), Args... args) {
			root.run((uintptr_t)fn);
			TrapHandler::enableTraps();
			Ret r = fn(args...);
			TrapHandler::disableTraps();
			return r;
		}
		
		template<typename U> void run(U request) {
			uintptr_t p = (uintptr_t)request;
			root.run(p);
		}
	};
}

#endif
