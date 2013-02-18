#if !defined(BINTRACE_DISASSEMBLER_HPP)
#define BINTRACE_DISASSEMBLER_HPP

#include <udis86.h>

namespace bintrace {
    struct Disassembler {
    private:
        ud_t _ud;
        bool _done;
        
    public:
        template<class T, class U> Disassembler(T* base, U* limit=(void*)(uintptr_t)-1) : _done(false) {
            ud_init(&_ud);
            ud_set_input_buffer(&_ud, (uint8_t*)base, (uintptr_t)limit - (uintptr_t)base);
            ud_set_mode(&_ud, 64);
            ud_set_syntax(&_ud, UD_SYN_INTEL);
        }
        
        bool done() {
            return _done;
        }
        
        ud_t* next() {
            _done |= !ud_disassemble(&_ud);
            return &_ud;
        }
    };
};

#endif
