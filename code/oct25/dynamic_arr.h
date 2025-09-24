//
// Created by guan on 2025/9/24.
//

#ifndef CPP_LINUX_LEARNING_DYNAMIC_ARR_H
#define CPP_LINUX_LEARNING_DYNAMIC_ARR_H
#include <stdexcept>

template<typename T>
constexpr T expand_factor=T(1.5);

template<typename T>
class DynamicArr {
    T* data;
    size_t capacity_;
    size_t size_;
    void resize() {
        if (capacity_ == 0) {
            capacity_ = 1;
        }else {
            capacity_=static_cast<size_t>(capacity_ * expand_factor<T>)+1;
        }
        T* new_data=new T[capacity_];
        for (size_t i=0; i<size_; i++) {
            new_data[i]=data[i];
        }
        delete[] data;
        data=new_data;
    }
public:
    DynamicArr(size_t init_capacity=0) :capacity_(init_capacity),size_(0) {
        if (init_capacity>0) {
            data=new T[init_capacity];
        }else {
            data=nullptr;
        }
    }
    ~DynamicArr() {
        delete[] data;
    }
    DynamicArr(const DynamicArr&) = delete;
    DynamicArr& operator=(const DynamicArr&) = delete;

    DynamicArr(DynamicArr&& other) noexcept:capacity_(other.capacity_),size_(other.size_),data(other.data) {
        other.data=nullptr;
        other.capacity_=0;
        other.size_=0;
    }

    DynamicArr& operator=(DynamicArr&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    void push_back(const T& item) {
        if (size_>=capacity_) {
            resize();
        }
        data[size_++]=item;
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    T& operator[](size_t i) {
        if (i>=size_) {
            throw std::out_of_range("DynamicArr: index out of range");
        }
        return data[i];
    }

    template<typename Func>
    T calculate(Func func,T initial_value) const {
        T result = initial_value;
        for (size_t i=0; i<size_; i++) {
            result =func(result, data[i]);
        }
        return result;
    }

};



#endif //CPP_LINUX_LEARNING_DYNAMIC_ARR_H