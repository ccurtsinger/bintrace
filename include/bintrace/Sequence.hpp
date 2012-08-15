/**
 * \file Sequence.hpp
 */

#ifndef BINTRACE_SEQUENCE_HPP
#define BINTRACE_SEQUENCE_HPP

#include <stdint.h>
#include <udis86.h>
#include <set>

#include "SequenceControl.hpp"

using namespace std;

/**
 * \namespace bintrace
 */
namespace bintrace {
	/**
	 * \class Sequence
	 * \brief The main class used for disassembly.  A sequence scans a sequential set of instructions for matches.
	 * \tparam H One or more Handler classes, which must define the \a match and \a onMatch methods.
	 *
	 * \todo Track successors and predecessors
	 * \todo Add support for merging and splitting sequences
	 * \todo Write a proper implementation of the \a contains method
	 */
	template<class ...H> class Sequence : public SequenceControl {
	private:
		/// The starting address of the Sequence
		uint8_t* base;
		
		/// The current position of the disassembler
		uint8_t* pos;
		
		/// The total number of bytes disassembled
		size_t size;
	
		/// A pointer to the libudis86 handle
		ud_t *ud;
		
		/// The set of predecessors for this sequence
		set<Sequence<H...>*> predecessors;
	
		/**
		 * \brief Initialize a Sequence at a given address, with a given predecessor
		 * 
		 * \param base The starting address for this sequence
		 * \param predecessor The sequence that precedes this one (or NULL)
		 *
		 * Initialize the Sequence base, position, size, and libudis86 handle.
		 */
		Sequence(void* base, Sequence<H...>* predecessor) {
			// Initialize the base pointer, current position, and sequence size
			this->pos = (uint8_t*)base;
			this->base = (uint8_t*)base;
			this->size = 0;

			// Initialize the set of visited sequences
			if(predecessor != NULL) {
				this->predecessors.insert(predecessor);
			}

			// Initialize the libudis86 handle
			this->ud = new ud_t;
			ud_init(this->ud);
			ud_set_mode(this->ud, 64);
			ud_set_syntax(this->ud, UD_SYN_ATT);

			// Set up udis86 to get data through an input hook, and give it a reference to this stream
			ud_set_user_opaque_data(this->ud, this);
			ud_set_input_hook(this->ud, Sequence<H...>::ud_input_hook);
		}
		
		/**
		 * \brief Called by libudis86 to retrieve the next byte for disassembly
		 * \param ud The libudis86 handle requesting the next byte
		 *
		 * Retrieve a pointer to the sequence being disassembled from the libudis86 opaque data reference,
		 * cast it to a Sequence pointer, and return its next byte.
		 */
		static int ud_input_hook(ud_t *ud) {
			Sequence<H...> *s = (Sequence<H...>*)ud_get_user_opaque_data(ud);
			return s->nextByte();
		}
	
	public:
		/**
		 * \brief Initialize a new Sequence with no predecessors
		 * \param base The starting point for disassembly
		 */
		Sequence(void *base) : Sequence(base, NULL) {}
	
		/**
		 * \brief Get the next byte for disassembly, or return \a UD_EOI if the Sequence has terminated or run into an existing sequence.
		 *
		 * Check if the sequence has terminated (\a pos is NULL) or of it has run into another Sequence.
		 * If not, get the current byte, increment the position and size, then return.
		 */
		int nextByte() {
			if(this->pos == NULL || this->contains(this->pos)) {
				return UD_EOI;
			}

			uint8_t b = *this->pos;
			this->pos++;
			this->size++;
			return b;
		}
	
		/**
		 * Check if this or any reachable Sequences contain a given address.
		 * \param p The address to search for
		 */
		bool contains(void *p) {
			return this->contains(p, this);
		}
	
		/**
		 * Check if this or any reachable Sequencs contain a given address.
		 * \param p The address to search for
		 * \param init The starting point for the search
		 *
		 * Recursively search the predecessors and successors for the given pointer.  End the search when
		 * a Sequence has no unvisited predecessors or successors.
		 *
		 * \todo Need to track successors to scan these as well
		 * 
		 * \todo Bidirectional search may revisit Sequences unless a full visited list is kept.  May need to
		 * track visited addresses with a single shared data structure and not a graph of Sequences.
		 */
		bool contains(void *p, Sequence<H...>* init) {
			if((intptr_t)p > (intptr_t)this->base && (intptr_t)p < (intptr_t)this->base + this->size) {
				return true;

			} else {
				if(init == NULL) {
					init = this;
				}

				for(Sequence<H...>* s: this->predecessors) {
					if(s != init && s->contains(p, init)) {
						return true;
					}
				}

				return false;
			}
		}
	
		/**
		 * \brief Split a new Sequence off of this one and disassemble it
		 * \param p The starting address for the new Sequence
		 */
		virtual void fork(void* p) {
			printf("forking to %p\n", p);
		
			// Create a successor sequence and disassemble it
			Sequence<H...> *s = new Sequence<H...>(p, this);
			s->disassemble();
		}
	
		/**
		 * \brief Begin disassembly for this sequence.
		 *
		 * Disassemble the next instruction, run all matchers against it, and repeat.
		 *
		 * \todo Need to remove the terminator instruction checks from Sequence and move them to a Matcher
		 * \todo Possibly add support for disassembling a maximum number of instructions.
		 * \todo Instead of disassembling successor sequences eagerly, finish this sequence then move on to successors.
		 */
		void disassemble() {
			while(ud_disassemble(this->ud)) {
				uint8_t *current = this->pos - ud_insn_len(this->ud);

		        // Print the disassembled instruction
		        printf("%p\t%s\n", current, ud_insn_asm(this->ud));
	
				Matcher<H...>::match(this, this->ud);

				switch(this->ud->mnemonic) {
					case UD_Iret:
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
					this->pos = NULL;
					break;

					default:
					break;
				}
			}
		}
	};
}

#endif
