#if !defined(BINTRACE_INTERVAL_HPP)
#define BINTRACE_INTERVAL_HPP

struct Interval {
private:
    uintptr_t _base;
    uintptr_t _limit;
    uintptr_t _pos;
    
public:
    Interval(uintptr_t base, uintptr_t limit) : 
        _base(base), _limit(limit), _pos(base) {}
    
    uintptr_t base() {
        return _base;
    }
    
    uintptr_t limit() {
        return _limit;
    }
    
    size_t size() {
        return _limit - _base;
    }
    
    bool done() {
        return _pos >= _limit;
    }
    
    uintptr_t next() {
        return _pos++;
    }
    
    void skip(size_t n) {
        _pos += n;
    }
    
    void end() {
        _limit = _pos;
    }
};

#endif
