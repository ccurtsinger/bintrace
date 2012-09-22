#ifndef BINTRACE_TRAPHANDLER_HPP
#define BINTRACE_TRAPHANDLER_HPP

#include <cstdlib>
#include <cassert>
#include <signal.h>
#include <sys/mman.h>

#include <map>
#include <vector>

#include "bintrace/Context.hpp"

#define PAGESIZE 0x1000

using namespace std;

namespace bintrace {
	class Instruction;
	typedef void (*trap_fn_t)(Instruction*, Context*);
	
	struct TrapHandler {
	private:
		typedef map<uintptr_t, TrapHandler*> handler_map_t;
		
		static handler_map_t& handlers() {
			static handler_map_t _handlers;
			return _handlers;
		}
		
		static void install_signal_handler() {
			static bool installed = false;

			if(!installed) {
				struct sigaction act;
			    act.sa_sigaction = signal_handler;
			    act.sa_flags = SA_SIGINFO;
			    
			    if(sigaction(SIGILL, &act, NULL)) {
					perror("sigaction");
					abort();
			    }
			}
		}
		
		static bool& trapsEnabled() {
			static bool _enabled = false;
			return _enabled;
		}
		
		static void signal_handler(int signal, siginfo_t* info, void* c) {
			disableTraps();
			
			Context context((ucontext_t*)c);
			TrapHandler* h = handlers()[context.pc()];

			if(h != NULL) {
				context.pc() = context.pc() + h->length;
				h->run(&context);
			} else {
				printf("Illegal instruction encountered at %p\n", (void*)context.pc());
				abort();
			}
			
			enableTraps();
		}
		
		uintptr_t base;
		size_t length;
		bool unprotected = false;
		char saved_byte;
		
		Instruction* inst;
		vector<trap_fn_t> fns;
		
		void unprotect() {
			if(!unprotected) {
				if(mprotect((void*)(base & ~(PAGESIZE-1)), PAGESIZE, PROT_EXEC | PROT_READ | PROT_WRITE)) {
					perror("mprotect");
					abort();
				}
				unprotected = true;
			}
		}
		
		void enableTrap() {
			unprotect();
			*(char*)base = 0x06;
		}
		
		void disableTrap() {
			*(char*)base = saved_byte;
		}
		
		TrapHandler(uintptr_t base, size_t length, Instruction* inst) {
			this->base = base;
			this->length = length;
			this->inst = inst;
			saved_byte = *(char*)base;
		}

		void add(trap_fn_t fn) {
			fns.push_back(fn);
		}

		void run(Context* c) {
			for(trap_fn_t fn: fns) {
				fn(inst, c);
			}
		}
		
	public:
		static void trap(uintptr_t base, size_t length, Instruction* inst, trap_fn_t action) {
			if(handlers().find(base) == handlers().end()) {
				handlers()[base] = new TrapHandler(base, length, inst);
			}

			handlers()[base]->add(action);
		}
		
		static void enableTraps() {
			if(!trapsEnabled()) {
				install_signal_handler();
				
				for(auto p: handlers()) {
					p.second->enableTrap();
				}
				
				trapsEnabled() = true;
			}
		}
		
		static void disableTraps() {
			if(trapsEnabled()) {
				for(auto p: handlers()) {
					p.second->disableTrap();
				}
				
				trapsEnabled() = false;
			}
		}
	};
}

#endif
