#ifndef BINTRACE_INTERVALQUEUE_HPP
#define BINTRACE_INTERVALQUEUE_HPP

#include <cstdlib>
#include <cassert>
#include <set>

#include <udis86.h>

using namespace std;

namespace bintrace {
	template<class T> class Driver;

	template<class T> class Interval {
		template<class TT> friend class Driver;

	private:
		Driver<T>* driver;

		intptr_t pos;
		intptr_t base;
		intptr_t limit;

		bool unbounded;

		set<intptr_t> queue;

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

		Interval(Driver<T>* driver, intptr_t base) : Interval(driver, base, 0) {
			unbounded = true;
		}

		void run(intptr_t request) {
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

		static int ud_input_hook(ud_t* ud) {
			Interval<T>* interval = (Interval<T>*)ud_get_user_opaque_data(ud);
			return interval->nextByte();
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

	public:
		ud_t* next() {
			if(ud_disassemble(this->ud)) {
				return this->ud;
			} else {
				return NULL;
			}
		}

		void skip() {
			if(unbounded || pos < limit) {
				pos++;
			}
		}

		void fork(intptr_t request) {
			driver->run(request);
		}

		intptr_t position() {
			return pos;
		}

		void finished() {
			unbounded = false;
			limit = pos;
			for(intptr_t w: queue) {
				if(w >= limit) {
					driver->run(w);
				}
			}
		}
	};

	template<class T> class Driver {
	private:
		Interval<T>* tree = NULL;

	public:	
		void run(intptr_t request) {
			if(tree == NULL) {
				tree = new Interval<T>(this, request);
				T handler;
				handler.run(tree);
			} else {
				tree->run(request);
			}
		}
	};
}

#endif
