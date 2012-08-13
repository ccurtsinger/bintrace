#ifndef _TRIESET_H_
#define _TRIESET_H_

#include <cstdio>
#include <cstdlib>

using namespace std;

template<typename T, size_t Bits, size_t Stride=1> struct TrieSetBase;

template<typename T, size_t Stride> struct TrieSetBase<T, 0, Stride> {
public:
	inline void add(T x) {}
	inline void addAll() {}
	inline void addRange(T base, T limit) {}
	inline bool lookup(T x) {
		return true;
	}
	inline int next(T x) {
		return x;
	}
	inline void print(T x) {
		printf("%d\n", x);
	}
};

template<typename T, size_t Bits, size_t Stride> struct TrieSetBase {
private:
	enum { 
		ChildCount = 1 << Stride,
		Mask = ChildCount - 1
	};
	
	typedef TrieSetBase<T, Bits-Stride, Stride> ChildType;
	
	ChildType* children[ChildCount];
	
	inline size_t index(T x) {
		size_t i = (x >> (Bits - Stride)) & Mask;
		return i;
	}
	
	inline TrieSetBase<T, Bits-Stride, Stride>* child(size_t i) {
		if(!children[i]) {
			children[i] = new ChildType();
		}
		return children[i];
	}
	
	inline bool hasChild(size_t i) {
		return children[i] != NULL;
	}
	
public:
	TrieSetBase() {
		for(size_t i=0; i<ChildCount; i++) {
			children[i] = NULL;
		}
	}
	
	inline void add(T x) {
		child(index(x))->add(x);
	}
	
	inline void addAll() {
		for(size_t i=0; i<ChildCount; i++) {
			child(i)->addAll();
		}
	}
	
	inline void addRange(T base, T limit) {
		size_t base_i = index(base);
		size_t limit_i = index(limit);
		
		if(base_i == limit_i) {
			child(base_i)->addRange(base, limit);
			
		} else {
			child(base_i)->addRange(base, (base_i + 1 << Bits - Stride)-1);
			
			for(size_t i = base_i+1; i < limit_i; i++) {
				child(i)->addAll();
			}
			
			child(limit_i)->addRange(limit_i << Bits - Stride, limit);
		}
	}
	
	inline bool lookup(T x) {
		size_t i = index(x);
		return hasChild(i) && child(i)->lookup(x);
	}
	
	inline int next(T x) {
		for(size_t i = index(x); i < ChildCount; i++) {
			if(hasChild(i)) {
				int y = child(i)->next(x);
				if(y != 0) {
					return y | (i << Bits - Stride);
				}
			}
			x = i + 1 << Bits - Stride;
		}
		
		return 0;
	}
	
	inline void print() {
		print(0);
	}
	
	inline void print(T x) {
		for(size_t i=0; i<ChildCount; i++) {
			if(hasChild(i)) {
				child(i)->print((i << Bits-Stride) | x);
			}
		}
	}
};

template<typename T, size_t Stride=4>
struct TrieSet : public TrieSetBase<T, sizeof(T)*8, Stride> {};

#endif
