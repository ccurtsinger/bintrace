#ifndef _TRIESET_H_
#define _TRIESET_H_

#include <cstdio>
#include <cstdlib>

using namespace std;

namespace bintrace {
	template<typename K, typename V, V def, size_t Bits, size_t Stride=1> struct TrieMapBase;

	template<typename K, typename V, V def, size_t Stride> struct TrieMapBase<K, V, def, 0, Stride> {
	private:
		V value;

	public:
		inline void add(K x, V v) {
			value = v;
		}

		inline V lookup(K x) {
			return value;
		}

		inline void print(K x) {
			printf("%d\n", x);
		}
	};

	template<typename K, typename V, V def, size_t Bits, size_t Stride> struct TrieMapBase {
	private:
		enum { 
			ChildCount = 1 << Stride,
			Mask = ChildCount - 1
		};
		
		typedef TrieMapBase<K, V, def, Bits-Stride, Stride> ChildType;
		
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
		
		inline void add(K x, V v) {
			child(index(x))->add(x, v);
		}
		
		inline V lookup(K x) {
			size_t i = index(x);

			if(hasChild(i)) {
				return child(i)->lookup(x);
			} else {
				return def;
			}
		}
		
		inline void print() {
			print(0);
		}
		
		inline void print(K x) {
			for(size_t i=0; i<ChildCount; i++) {
				if(hasChild(i)) {
					child(i)->print((i << Bits-Stride) | x);
				}
			}
		}
	};

	template<typename K, typename V, V def=NULL, size_t Stride=4>
	struct TrieMap : public TrieMapBase<K, V, def, sizeof(K)*8, Stride> {};
}

#endif
