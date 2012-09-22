#ifndef BINTRACE_INTERVAL_HPP
#define BINTRACE_INTERVAL_HPP

#include <cstdlib>
#include <set>

#include "bintrace/Instruction.hpp"
#include "bintrace/InstructionStream.hpp"

using namespace std;

namespace bintrace {
	template<class T> struct Driver;
	
	template<class T> class Interval : public InstructionStream {
		template<class TT> friend struct Driver;

	private:
		Driver<T>* driver;

		uintptr_t pos;
		uintptr_t base;
		uintptr_t limit;

		bool unbounded;

		set<uintptr_t> queue;

		Interval* left = NULL;
		Interval* right = NULL;

		ud_t* ud;

		Interval(Driver<T>* driver, intptr_t base, intptr_t limit) {
			this->driver = driver;
			this->base = base;
			this->limit = limit;
			this->pos = base;
			this->unbounded = false;

			this->ud = new ud_t;
			ud_init(this->ud);
			ud_set_mode(this->ud, 64);
			ud_set_syntax(this->ud, UD_SYN_ATT);
			ud_set_user_opaque_data(this->ud, this);
			ud_set_input_hook(this->ud, Interval<T>::ud_input_hook);
			ud_set_pc(this->ud, base);
		}

		Interval(Driver<T>* driver, uintptr_t base) : Interval(driver, base, 0) {
			unbounded = true;
		}

		virtual void run(uintptr_t request) {
			if(request < base) {
				// Requested point is left of this interval
				if(left == NULL) {
					left = new Interval<T>(driver, request, base);
					T handler;
					handler.run(left);
				} else {
					left->run(request);
				}

			} else if(request >= base && (unbounded || request < limit)) {
				// Requested point falls in this interval
				queue.insert(request);

			} else {
				// Requested point is right of this interval
				if(right == NULL) {
					right = new Interval<T>(driver, request);
					T handler;
					handler.run(right);
				} else {
					right->run(request);
				}
			}
		}

		int nextByte() {
			if(unbounded || pos < limit) {
				uint8_t byte = *(uint8_t*)pos;
				pos++;
				return byte;
			} else {
				return UD_EOI;
			}
		}

		static int ud_input_hook(ud_t* ud) {
			Interval<T>* interval = (Interval<T>*)ud_get_user_opaque_data(ud);
			return interval->nextByte();
		}

	public:
		virtual Instruction* next() {
			if(ud_disassemble(this->ud)) {
				return new Instruction(this, this->ud);
			} else {
				return NULL;
			}
		}

		virtual void skip() {
			if(unbounded || pos < limit) {
				pos++;
			}
		}

		virtual void fork(uintptr_t request) {
			driver->run(request);
		}

		uintptr_t position() {
			return pos;
		}

		virtual void end() {
			unbounded = false;
			limit = pos;
			for(intptr_t w: queue) {
				if(w >= limit) {
					driver->run(w);
				}
			}
		}
	};
}

#endif
