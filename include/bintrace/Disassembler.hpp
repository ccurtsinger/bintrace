#if !defined(BINTRACE_DISASSEMBLER_HPP)
#define BINTRACE_DISASSEMBLER_HPP

#include <udis86.h>

namespace bintrace {
    struct Disassembler {
    private:
        ud_t _ud;
        size_t _sz;
        size_t _used;
        
    public:
        template<class T, class U>
        Disassembler(T* base, U* limit=(void*)(uintptr_t)-1) {
            _sz = (uintptr_t)limit - (uintptr_t)base;
            _used = 0;
            
            ud_init(&_ud);
            ud_set_input_buffer(&_ud, (uint8_t*)base, _sz);
            ud_set_mode(&_ud, 64);
            ud_set_syntax(&_ud, UD_SYN_INTEL);
        }
        
        bool done() {
            return _used < _sz;
        }
        
        ud_t* next() {
            ud_disassemble(&_ud);
            _used += ud_insn_len(&_ud);
            return &_ud;
        }
    };
};

#endif
