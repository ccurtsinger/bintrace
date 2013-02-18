#if !defined(BINTRACE_TRIEMAP_HPP)
#define BINTRACE_TRIEMAP_HPP

#include <cstdio>
#include <cstdlib>

using namespace std;

namespace bintrace {
    constexpr size_t min(size_t x, size_t y) {
        return x > y ? y : x;
    }
    
	template<typename K, typename V, size_t Bits, size_t Stride> struct TrieMapBase;

	template<typename K, typename V, size_t Stride> struct TrieMapBase<K, V, 0, Stride> {
	private:
		V _value;

	public:
        inline bool contains(K x) {
            return true;    
        }
        
        inline V& getEntry(K x) {
            return _value;
        }
	};

	template<typename K, typename V, size_t Bits, size_t Stride> struct TrieMapBase {
	private:
		enum { 
			ChildCount = 1 << Stride,
			Mask = ChildCount - 1
		};
		
		typedef TrieMapBase<K, V, Bits-Stride, min(Stride, Bits-Stride)> ChildType;
		
		ChildType* children[ChildCount];
		
		inline size_t index(K x) {
			size_t i = (x >> (Bits - Stride)) & Mask;
			return i;
		}
		
		inline ChildType* child(size_t i) {
			if(!children[i]) {
				children[i] = new ChildType();
			}
			return children[i];
		}
		
		inline bool hasChild(size_t i) {
			return children[i] != NULL;
		}
		
	public:
		TrieMapBase() {
			for(size_t i=0; i<ChildCount; i++) {
				children[i] = NULL;
			}
		}
        
        inline bool contains(K x) {
            return hasChild(index(x)) && child(index(x))->contains(x);
        }
        
        inline V& getEntry(K x) {
            return child(index(x))->getEntry(x);
        }
	};

	template<typename K, typename V, size_t Stride=4>
	struct TrieMap : public TrieMapBase<K, V, sizeof(K)*8, Stride> {
        typedef TrieMapBase<K, V, sizeof(K)*8, Stride> Super;
    public:
        inline V& operator[](K x) {
            return Super::getEntry(x);
        }
    };
}

#endif
