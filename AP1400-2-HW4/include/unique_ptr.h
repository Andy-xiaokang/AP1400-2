#ifndef UNIQUE_PTR
#define UNIQUE_PTR

#include <memory>
template <typename T>
class UniquePtr {
public:
    explicit UniquePtr(T* p = nullptr) : _p(p) {};
    ~UniquePtr() {
        delete _p; _p = nullptr;
    }
    UniquePtr(const UniquePtr & other) = delete;
    UniquePtr& operator=(const UniquePtr& other) = delete;
    UniquePtr(UniquePtr&& other)  noexcept : _p(other._p) {  // move constructor
        other._p = nullptr;
    }
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete _p;
            _p = other._p;
            other._p = nullptr;
        }
        return *this;
    }
    T* get() {
        return _p;
    };
    T& operator*() const {
        return *_p;
    };
    T* operator->() const {
        return _p;
    };
    explicit operator bool() const {return _p != nullptr;};
    void reset() {
        delete _p; _p = nullptr;
    };
    void reset(T* p) {
        if (p != _p) {
            delete _p; _p = p;
        }
    };
    T* release() {
        T* tmp = _p;
        _p = nullptr;
        return tmp;
    };
private:
    T* _p;
};

template<typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
    // 使用完美转发将参数传递给 T 的构造函数
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}


#endif //UNIQUE_PTR