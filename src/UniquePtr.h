#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include <utility>

// Your implementation here

template <typename T>

class UniquePtr {
    T* m_ptr;
    public:
    UniquePtr(T* ptr = nullptr) : m_ptr(ptr) {}
    ~UniquePtr() {
        if (m_ptr) delete m_ptr;
    } 

    UniquePtr(const UniquePtr<T>& ) = delete; 
    UniquePtr& operator=(const UniquePtr<T>&) = delete; // no copying allowed 

    UniquePtr(UniquePtr<T>&& r_value) {
        m_ptr = r_value.m_ptr;
        r_value.m_ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr<T>&& r_value) {
        const auto old_ptr = m_ptr;
        m_ptr = r_value.m_ptr;
        r_value.m_ptr = old_ptr; // r_value will go out of scope and destroy itself. Might as well feed it our old data so it destroys it for us.
        return *this;
    }

    T& operator*() const {return *m_ptr;} 
    T* operator->() const {return m_ptr;}
    T* get() const {return m_ptr;}

    bool operator==(const UniquePtr<T>& other) const {
        return get() == other.get();
    }

    T* release() {
        const auto ptr = m_ptr;
        m_ptr = nullptr;
        return ptr;
    }


    void reset(T* newPtr = nullptr) {
        if (m_ptr) delete m_ptr;
        m_ptr = newPtr;
    }

    void swap(UniquePtr<T>& other) {
        auto temp = std::move(*this); // (*this) is now invalid.
        *this = std::move(other); // other is now invalid. *this is valid again
        other = std::move(temp); // other is valid again and temp is now invalid
    }

    inline operator bool() const {
        return m_ptr != nullptr;
    }

    template <typename U>
    UniquePtr(UniquePtr<U>&& other) {
        (*this) = other; // just calling the move constructor
    }









} ; 


template <typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args)
{
    const auto* raw_ptr = new T(std::forward<Args>(args)...); // ... to specify that its arguments??
    return UniquePtr<T>(raw_ptr);
}

#endif
