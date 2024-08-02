#ifndef SHARED_PTR
#define SHARED_PTR
#include <memory>

template <typename T>
class SharedPtr {
private:
    T* _p;
    std::size_t * ref_count;

public:
    explicit SharedPtr(T* p = nullptr) : _p(p), ref_count(new std::size_t(1)) {};

    ~SharedPtr() {
        if (ref_count && --(*ref_count) == 0) { // if the SharedPtr called destructor is the last one, free
            delete _p; _p = nullptr;
            delete ref_count; ref_count = nullptr;
        }
    }

    SharedPtr(const SharedPtr & other) : _p(other._p), ref_count(other.ref_count) {  // copy constructor
        (*ref_count)++;
    }

    SharedPtr(SharedPtr && other)  noexcept : _p(other._p), ref_count(other.ref_count) { // move constructor
        other._p = nullptr;
        other.ref_count = nullptr;
    }

    SharedPtr& operator=(const SharedPtr & other) { // copy assignment
        if (this != &other) {
            if (--(*ref_count) == 0) {
                delete _p; _p = nullptr;
                delete ref_count;
            }
            _p = other._p;
            ref_count =  other.ref_count;
            (*ref_count)++;
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other)  noexcept { // move assignment
        if (this != &other) {
            if (--(*ref_count) == 0) {
                delete _p; _p = nullptr;
                delete ref_count; ref_count = nullptr;
            }
            _p = other._p;
            ref_count = other.ref_count;
            other._p = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }

    std::size_t use_count() {
        if (ref_count) {
            return (*ref_count);
        } else {
            return 0;
        }
    }

    T* get() {
        return _p;
    }

    T& operator*() const {
        return *_p;
    }

    T* operator->() const {
        return _p;
    }

    explicit operator bool() const { return _p != nullptr; };

    void reset() {
        delete _p; _p = nullptr;
        (*ref_count) = 0;
    }

    void reset (T* p) {
        if (p != _p) {
            reset();
            _p = p; *(ref_count) = 1;
        }
    }
};

template <typename T, typename... Args>
SharedPtr<T> make_shared(Args&&... args) {
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

#endif //SHARED_PTR