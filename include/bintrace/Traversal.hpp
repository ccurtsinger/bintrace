#if !defined(BINTRACE_TRAVERSAL_HPP)
#define BINTRACE_TRAVERSAL_HPP

#include <set>
#include <limits>

using namespace std;

template<class Super> struct Traversal {
public:
    struct TraversalNode : public Super {
    private:
        friend class Traversal;
        
        Traversal& _source;
        
        TraversalNode* _leftChild;
        TraversalNode* _rightChild;
        
        TraversalNode(Traversal& source, uintptr_t base, uintptr_t limit=numeric_limits<uintptr_t>::max()) :
            _source(source), _leftChild(NULL), _rightChild(NULL), Super(base, limit) {}
        
        TraversalNode* insert(uintptr_t x, uintptr_t upperBound=numeric_limits<uintptr_t>::max()) {
            if(x < Super::base()) {
                // The requested base is entirely to the left of this interval
                if(_leftChild == NULL) {
                    // There is no left child.  Make one
                    _leftChild = new TraversalNode(_source, x, min(Super::base(), upperBound));
                    return _leftChild;
                } else {
                    // Recurse left
                    return _leftChild->insert(x, min(Super::base(), upperBound));
                }

            } else if(x >= Super::limit()) {
                // The requested base is entirely to the right of this interval
                if(_rightChild == NULL) {
                    // There is no right child.  Make one
                    _rightChild = new TraversalNode(_source, x, upperBound);
                    return _rightChild;
                } else {
                    // Recurse right
                    return _rightChild->insert(x, upperBound);
                }

            } else {
                // The requested base falls within this interval.  Return NULL for failure.
                return NULL;
            }
        }
        
    public:
        void fork(uintptr_t target) { _source.add(target); }
        void jump(uintptr_t target) { fork(target); Super::end(); }
    };
    
private:
    friend class TraversalNode;
    
    set<uintptr_t> _workQueue;
    TraversalNode* _root;
    TraversalNode* _cached;
    
    void add(uintptr_t target) {
        _workQueue.insert(target);
    }
    
public:
    Traversal(uintptr_t entryPoint) {
        add(entryPoint);
        _root = NULL;
        _cached = NULL;
    }
    
    bool done() {
        _cached = next();
        return _cached == NULL;
    }
    
    TraversalNode* next() {
        if(_cached != NULL) {
            TraversalNode* i = _cached;
            _cached = NULL;
            return i;
            
        } else if(_root == NULL) {
            if(_workQueue.size() > 0) {
                uintptr_t x = *_workQueue.begin();
                _workQueue.erase(_workQueue.begin());
                _root = new TraversalNode(*this, x);
                
                return _root;
                
            } else {
                return NULL;
            }
            
        } else {
            for(set<uintptr_t>::iterator iter = _workQueue.begin(); iter != _workQueue.end(); iter++) {
                uintptr_t x = *iter;
                TraversalNode* i = _root->insert(x);
                if(i != NULL) {
                    _workQueue.erase(iter);
                    return i;
                }
            }
            
            return NULL;
        }
    }
};

#endif
