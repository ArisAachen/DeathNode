#ifndef __JJ_ALLOCATOR_H__
#define __JJ_ALLOCATOR_H__

#include <new>
#include <climits>
#include <cassert>
#include <cstddef>

template<typename T>
inline T* _allocator(ptrdiff_t size, T*) {
    std::set_new_handler(0);
    T* tmp = (T*)(::operator new(size * sizeof(T)));
    if (tmp == nullptr)
        assert(false);
    return tmp;
}

template<typename T>
inline void _deallocator(T* buffer) {
    ::operator delete(buffer);
}

template<typename T1, typename T2>
inline void _constructor(T1* ptr, const T2& value) {
    new (ptr) T1(value);
}

template<typename T>
inline void _destroy(T* ptr) {
    ptr->~T();
}

template<typename T>
class allocator {
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    pointer allocate(size_type n, const void* hint = 0) {
        return _allocator((difference_type)n, (pointer)0);
    }

    void deallocate(pointer p, size_type n) {
        _deallocator(p);
    }

    void construct(pointer p, const T& value) {
        _constructor(p, value);
    }

    void destroy(pointer p) {
        _destroy(p);
    }

    pointer address(reference x) {
        return (pointer)&x;
    }

    const_pointer const_address(const_reference x) {
        return (const_pointer)&x;
    }

    size_type max_size() const {
        return size_type(UINT_MAX/sizeof(T));
    }
};

#endif