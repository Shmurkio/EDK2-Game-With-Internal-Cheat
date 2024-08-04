#pragma once

#include "new.hpp"
#include "stdexcept.hpp"

namespace std
{
    /* Swap function to interchange the values of two variables. */
    template <typename T> class initializer_list
    {
    public:
        using iterator = const T*;
        using const_iterator = const T*;

        /* Default constructor. */
        constexpr initializer_list() noexcept : begin_(nullptr), end_(nullptr) {}

        /* Constructor to initialize from a list of values. */
        constexpr initializer_list(const T* begin, const T* end) noexcept : begin_(begin), end_(end) {}

        /* Access the beginning of the list. */
        constexpr const T* begin() const noexcept { return begin_; }

        /* Access one past the end of the list. */
        constexpr const T* end() const noexcept { return end_; }

        /* Get the number of elements in the list. */
        constexpr size_t size() const noexcept { return end_ - begin_; }

    private:
        const T* begin_;
        const T* end_;
    };

    template <typename InputIt, typename OutputIt> OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
    {
        while (first != last)
        {
            *d_first++ = *first++;
        }

        return d_first;
    }

    /* Implementation of a dynamic array */
    template <typename T> class vector
    {
    public:
        /* Default constructor initializes an empty vector. */
        vector() : data_(nullptr), size_(0), capacity_(0) {}

        /* Constructor initializes the vector with a specific size and value. */
        vector(size_t size, T value = T()) : size_(size), capacity_(size)
        {
            data_ = new T[capacity_];

            for (size_t i = 0; i < size_; i++)
            {
                data_[i] = value;
            }
        }

        /* Destructor cleans up the allocated memory. */
        ~vector()
        {
            clear();
            deallocate();
        }

        /* Copy constructor. */
        vector(const vector& other) : data_(nullptr), size_(0), capacity_(0)
        {
            if (other.size_ > 0)
            {
                reserve(other.size_);
                for (size_t i = 0; i < other.size_; i++)
                {
                    data_[i] = other.data_[i];
                }

                size_ = other.size_;
            }
        }

        /* Move constructor. */
        vector(vector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_)
        {
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }

        vector(initializer_list<T> init)
            : size_(init.size()), capacity_(init.size())
        {
            data_ = new T[capacity_];
            copy(init.begin(), init.end(), data_);
        }

        // Constructor from an initializer_list of vector<T>
        vector(initializer_list<vector<T>> init)
            : size_(init.size()), capacity_(init.size())
        {
            data_ = new vector<T>[capacity_];
            copy(init.begin(), init.end(), data_);
        }

        /* Copy assignment operator. */
        vector& operator=(const vector& other)
        {
            if (this != &other)
            {
                clear();

                if (other.size_ > 0)
                {
                    reserve(other.size_);

                    for (size_t i = 0; i < other.size_; i++)
                    {
                        data_[i] = other.data_[i];
                    }

                    size_ = other.size_;
                }
            }

            return *this;
        }

        /* Move assignment operator. */
        vector& operator=(vector&& other) noexcept
        {
            if (this != &other)
            {
                clear();
                deallocate();
                data_ = other.data_;
                size_ = other.size_;
                capacity_ = other.capacity_;
                other.data_ = nullptr;
                other.size_ = 0;
                other.capacity_ = 0;
            }

            return *this;
        }

        /* Add an element to the end of the vector. */
        void push_back(const T& value)
        {
            if (size_ >= capacity_)
            {
                size_t new_capacity;

                if (capacity_ == 0)
                {
                    new_capacity = 1;
                }
                else
                {
                    new_capacity = 2 *capacity_;
                }

                reserve(new_capacity);
            }

            data_[size_++] = value;
        }

        /* Remove the last element from the vector. */
        void pop_back()
        {
            if (size_ > 0)
            {
                size_--;
            }
        }

        /* Access element at a specific index. */
        T& operator[](size_t index) {
            return data_[index];
        }

        /* Return the number of elements in the vector. */
        size_t size() const {
            return size_;
        }

        /* Clear the vector, but do not deallocate memory. */
        void clear() {
            size_ = 0;
        }

        /* Find the index of the first occurrence of a value. */
        size_t find(const T& value) const
        {
            for (size_t i = 0; i < size_; i++)
            {
                if (data_[i] == value)
                {
                    return i;
                }
            }

            return npos;
        }

        /* Constant indicating the end of the vector. */
        static const size_t npos;

        /* Insert a value at a specific index. */
        void insert(size_t index, const T& value)
        {
            if (index > size_)
            {
                throw out_of_range("Index out of range");
            }

            if (size_ >= capacity_)
            {
                size_t new_capacity;
                
                if (capacity_ == 0)
                {
                    new_capacity = 1;
                }
                else
                {
                    new_capacity = 2 *capacity_;
                }

                reserve(new_capacity);
            }

            for (size_t i = size_; i > index; i--)
            {
                data_[i] = data_[i - 1];
            }

            data_[index] = value;
            size_++;
        }

        /* Access element at a specific index with bounds checking. */
        T& at(size_t index) {
            if (index >= size_)
            {
                throw out_of_range("Index out of range");
            }

            return data_[index];
        }

        /* Access element at a specific index with bounds checking (const version). */
        const T& at(size_t index) const
        {
            if (index >= size_)
            {
                throw out_of_range("Index out of range");
            }

            return data_[index];
        }

        /* Access the last element. */
        T& back()
        {
            if (size_ == 0)
            {
                throw std::out_of_range("Vector is empty");
            }

            return data_[size_ - 1];
        }

        /* Access the last element (const version). */
        const T& back() const
        {
            if (size_ == 0)
            {
                throw std::out_of_range("Vector is empty");
            }

            return data_[size_ - 1];
        }

        /* Remove an element at a specific index. */
        void erase(size_t index)
        {
            if (index >= size_)
            {
                throw out_of_range("Index out of range");
            }

            for (size_t i = index; i < size_ - 1; i++)
            {
                data_[i] = data_[i + 1];
            }

            size_--;
        }

        /* Remove a range of elements from the vector. */
        void erase(size_t first_index, size_t last_index)
            {
            if (first_index >= size_ || last_index > size_ || first_index > last_index)
            {
                throw out_of_range("Index out of range");
            }

            for (size_t i = first_index; i < size_ - (last_index - first_index); i++)
            {
                data_[i] = data_[i + (last_index - first_index)];
            }

            size_ -= (last_index - first_index);
        }

        /* Resize the vector to a new size with a specific value for new elements. */
        void resize(size_t new_size, T value = T()) // Requires #pragma optimize("", off)
        {
            if (new_size < size_)
            {
                size_ = new_size;
            }
            else if (new_size > size_)
            {
                if (new_size > capacity_)
                {
                    reserve(new_size);
                }

                for (size_t i = size_; i < new_size; i++)
                {
                    data_[i] = value;
                }

                size_ = new_size;
            }
        }

        /* Check if the vector is empty. */
        bool empty() const
        {
            return size_ == 0;
        }

        /* Return the current capacity of the vector. */
        size_t capacity() const
        {
            return capacity_;
        }

        /* Shrink the capacity of the vector to fit its size. */
        void shrink_to_fit()
        {
            if (size_ < capacity_)
            {
                reserve(size_);
            }
        }

        /* Return a pointer to the first element. */
        T *begin()
        {
            return data_;
        }

        /* Return a pointer to the first element (const version). */
        const T *begin() const
        {
            return data_;
        }

        /* Return a pointer to one past the last element. */
        T *end()
        {
            return data_ + size_;
        }

        /* Return a pointer to one past the last element (const version). */
        const T *end() const
        {
            return data_ + size_;
        }

        /* Swap the contents of this vector with another vector. */
        void swap(vector& other) noexcept
        {
            std::swap(data_, other.data_);
            std::swap(size_, other.size_);
            std::swap(capacity_, other.capacity_);
        }

        /* Return a pointer to the underlying array of elements. */
        T *data() {
            return data_;
        }

        /* Return a pointer to the underlying array of elements (const version). */
        const T *data() const {
            return data_;
        }

    private:
        T *data_;
        size_t size_;
        size_t capacity_;

        /* Reserve memory for a new capacity. */
        void reserve(size_t new_capacity)
        {
            T *new_data = new T[new_capacity];

            for (size_t i = 0; i < size_; i++)
            {
                new_data[i] = data_[i];
            }

            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }

        /* Deallocate the memory. */
        void deallocate()
        {
            delete[] data_;
        }
    };

    template <typename T> const size_t vector<T>::npos = static_cast<size_t>(-1);
}