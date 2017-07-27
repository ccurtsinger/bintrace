#if !defined(BINTRACE_DISASSEMBLER_HPP)
#define BINTRACE_DISASSEMBLER_HPP

#include <bintrace.h>
#include <udis86.h>

namespace bintrace {
    struct Disassembler : public Interval {
    private:
        ud_t _ud;
        uintptr_t _pos;
        uintptr_t _limit;
        
    public:
        Disassembler(uintptr_t base, uintptr_t limit) : Interval(base, limit) {
            ud_init(&_ud);
            ud_set_input_buffer(&_ud, (uint8_t*)Interval::base(), Interval::size());
            ud_set_mode(&_ud, 0b1000000);
            ud_set_syntax(&_ud, UD_SYN_INTEL);
        }
        
        ud_t* next() {
            ud_disassemble(&_ud);
            Interval::skip(ud_insn_len(&_ud));
            return &_ud;
        }
    };
};

#endif
