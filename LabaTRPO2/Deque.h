﻿#pragma once
#include <iterator>
#include <memory>

namespace fefu_laboratory_two {
    template <typename T>
    class Allocator {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;

        Allocator() noexcept = default;

        Allocator(const Allocator& other) noexcept = default;

        template <class U>
        Allocator(const Allocator<U>& other) noexcept;

        ~Allocator() = default;

        pointer allocate(size_type size)
        {
            return static_cast<pointer>(::operator new(size * sizeof(T))); 
        }

        void deallocate(pointer p, size_type n) noexcept
        {
            ::operator delete(p, n);
        }

        //[[nodiscard]] std::allocation_result<T*> allocate_at_least(
        // std::size_t n ); // TODO For extra points
    };

    template <typename ValueType>
    class Node
    {
    public:
        Node(const ValueType& value_) : value(value_) { }
        Node* next;
        Node* prev;
        ValueType value;
    };


    template <typename ValueType>
    class Deque_iterator {
    private:
        Node<ValueType>* point;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = ValueType;
        using difference_type = std::ptrdiff_t;
        using pointer = ValueType*;
        using reference = ValueType&;

        Deque_iterator() noexcept = default;

        Deque_iterator(const Deque_iterator& other) noexcept : point(other.point)
        { }

        Deque_iterator(Node<ValueType>* p) noexcept : point(p)
        { }

        Deque_iterator& operator=(const Deque_iterator& other)
        {
            this->point = other.point;
            return *this;
        }

        ~Deque_iterator() = default;

        friend void swap(Deque_iterator<ValueType>& a, Deque_iterator<ValueType>& b)
        {
            Node<ValueType>* point_a = a.point;
            a.point = b.point;
            b.point = point_a;
        }

        friend bool operator==(const Deque_iterator<ValueType>& a,
            const Deque_iterator<ValueType>& b)
        {
            if (a.point == b.point)
            {
                return true;
            }
            return false;
        }
        friend bool operator!=(const Deque_iterator<ValueType>& a,
            const Deque_iterator<ValueType>& b)
        {
            return !(a == b);
        }

        reference operator*() const
        {
            reference a = this->point->value;
            return a;
        }
        pointer operator->() const;

        Deque_iterator& operator++()
        {
            *this += 1;
            return *this;
        }
        Deque_iterator operator++(int)
        {
            *this += 1;
            return *this;
        }

        Deque_iterator& operator--()
        {
            *this -= 1;
            return *this;
        }
        Deque_iterator operator--(int)
        {
            *this -= 1;
            return *this;
        }

        Deque_iterator operator+(const difference_type& t) const
        {
            Deque_iterator it(*this);
            it += t;
            return it;
        }
        Deque_iterator& operator+=(const difference_type& t)
        {
            int i = 0;
            int b = static_cast<int>(t);
            while (i < b)
            {
                this->point = this->point->next;
                if (this->point == nullptr)
                {
                    break;
                }
                i++;
            }
            return *this;
        }

        Deque_iterator operator-(const difference_type& t) const
        {
            Deque_iterator it(*this);
            it -= t;
            return it;
        }
        Deque_iterator& operator-=(const difference_type& t)
        {
            int i = 0;
            int b = static_cast<int>(t);
            while (i < b)
            {
                this->point = this->point->prev;
                if (this->point == nullptr)
                {
                    break;
                }
                i++;
            }
            return *this;
        }

        difference_type operator-(const Deque_iterator&) const;

        reference operator[](const difference_type& t);

        friend bool operator<(const Deque_iterator<ValueType>& a,
            const Deque_iterator<ValueType>& b)
        {
            Node<ValueType>* node = a.point;
            if (node == b.point)
            {
                return false;
            }
            while (true)
            {
                node = node->next;
                if (node == b.point)
                {
                    return true;
                }
                else if(node == nullptr)
                {
                    return false;
                }
            }
        }
        friend bool operator<=(const Deque_iterator<ValueType>& a,
            const Deque_iterator<ValueType>& b)
        {
            Node<ValueType>* node = a.point;
            if (node == b.point)
            {
                return true;
            }
            while (true)
            {
                node = node->next;
                if (node == b.point)
                {
                    return true;
                }
                else if (node == nullptr)
                {
                    return false;
                }
            }
        }
        friend bool operator>(const Deque_iterator<ValueType>& a,
            const Deque_iterator<ValueType>& b)
        {
            bool h = false;
            Node<ValueType>* node = b.point;
            if (node == a.point)
            {
                return false;
            }
            while (!h)
            {
                node = node->next;
                if (node == a.point)
                {
                    return true;
                }
                else if (node == nullptr)
                {
                    return false;
                }
            }
        }
        friend bool operator>=(const Deque_iterator<ValueType>& a,
            const Deque_iterator<ValueType>& b)
        {
            bool h = false;
            Node<ValueType>* node = b.point;
            if (node == a.point)
            {
                return true;
            }
            while (!h)
            {
                node = node->next;
                if (node == a.point)
                {
                    return true;
                }
                else if (node == nullptr)
                {
                    return false;
                }
            }
        }
        // operator<=> will be handy
    };

    template <typename ValueType>
    class Deque_const_iterator {
        // Shouldn't give non const references on value
    private:
        Node<ValueType>* point;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = ValueType;
        using difference_type = std::ptrdiff_t;
        using pointer = const ValueType*;
        using reference = const ValueType&;

        Deque_const_iterator() noexcept = default;
        Deque_const_iterator(const Deque_const_iterator& other) noexcept : point(other.point)
        { }
        Deque_const_iterator(const Deque_iterator<ValueType>& other) noexcept : point(other.point)
        { }

        Deque_const_iterator(Node<ValueType>* p) noexcept : point(p)
        { }

        Deque_const_iterator& operator=(const Deque_const_iterator& other)
        {
            this->point = other.point;
            return *this;
        }
        Deque_const_iterator& operator=(const Deque_iterator<ValueType>& other)
        {
            this->point = other.point;
            return *this;
        }

        ~Deque_const_iterator() = default;

        friend void swap(Deque_const_iterator<ValueType>& a,
            Deque_const_iterator<ValueType>& b)
        {
            Node<ValueType>* point_a = a.point;
            a.point = b.point;
            b.point = point_a;
        }

        friend bool operator==(const Deque_const_iterator<ValueType>& a,
            const Deque_const_iterator<ValueType>& b)
        {
            return a.point == b.point;
        }
        friend bool operator!=(const Deque_const_iterator<ValueType>& a,
            const Deque_const_iterator<ValueType>& b)
        {
            return !(a == b);
        }

        reference operator*() const
        {
            reference constValue = this->point->value;
            return constValue;
        }
        pointer operator->() const
        {
            pointer constRef = static_cast<pointer>(&(this->point->value));
            return constRef;
        }

        Deque_const_iterator& operator++()
        {
            *this += 1;
            return *this;
        }
        Deque_const_iterator operator++(int)
        {
            *this += 1;
            return *this;
        }

        Deque_const_iterator& operator--()
        {
            *this -= 1;
            return *this;
        }
        Deque_const_iterator operator--(int)
        {
            *this -= 1;
            return *this;
        }

        Deque_const_iterator operator+(const difference_type& t) const
        {
            Deque_const_iterator it(*this);
            it += t;
            return it;
        }
        Deque_const_iterator& operator+=(const difference_type& t)
        {
            int i = 0;
            int b = static_cast<int>(t);
            while (i < b)
            {
                this->point = this->point->next;
                if (this->point == nullptr)
                {
                    break;
                }
                i++;
            }
            return *this;
        }

        Deque_const_iterator operator-(const difference_type& t) const
        {
            Deque_const_iterator it(*this);
            it -= t;
            return it;
        }
        Deque_const_iterator& operator-=(const difference_type& t)
        {
            int i = 0;
            int b = static_cast<int>(t);
            while (i < b)
            {
                this->point = this->point->prev;
                if (this->point == nullptr)
                {
                    break;
                }
                i++;
            }
            return *this;
        }

        difference_type operator-(const Deque_const_iterator& t) const;

        reference operator[](const difference_type& t);

        friend bool operator<(const Deque_const_iterator<ValueType>& a,
            const Deque_const_iterator<ValueType>& b)
        {
            Node<ValueType>* node = a.point;
            if (node == b.point)
            {
                return false;
            }
            while (true)
            {
                node = node->next;
                if (node == b.point)
                {
                    return true;
                }
                else if (node == nullptr)
                {
                    return false;
                }
            }
        }
        friend bool operator<=(const Deque_const_iterator<ValueType>& a,
            const Deque_const_iterator<ValueType>& b)
        {
            Node<ValueType>*node = a.point;
            if (node == b.point)
            {
                return true;
            }
            while (true)
            {
                node = node->next;
                if (node == b.point)
                {
                    return true;
                }
                else if (node == nullptr)
                {
                    return false;
                }
            }
        }
        friend bool operator>(const Deque_const_iterator<ValueType>& a,
            const Deque_const_iterator<ValueType>& b)
        {
            Node<ValueType>* node = b.point;
            if (node == a.point)
            {
                return false;
            }
            while (true)
            {
                node = node->next;
                if (node == a.point)
                {
                    return true;
                }
                else if (node == nullptr)
                {
                    return false;
                }
            }
        }
        friend bool operator>=(const Deque_const_iterator<ValueType>& a,
            const Deque_const_iterator<ValueType>& b)
        {
            Node<ValueType>* node = b.point;
            if (node == a.point)
            {
                return true;
            }
            while (true)
            {
                node = node->next;
                if (node == a.point)
                {
                    return true;
                }
                else if (node == nullptr)
                {
                    return false;
                }
            }
        }
        // operator<=> will be handy
    };

    template <class Iter>
    class Deque_reverse_iterator {
    private:
        Node<Iter>* point;
    public:
        using iterator_type = Iter;
        using iterator_category =
            typename std::iterator_traits<Iter>::iterator_category;
        using value_type = typename std::iterator_traits<Iter>::value_type;
        using difference_type = typename std::iterator_traits<Iter>::difference_type;
        using pointer = typename std::iterator_traits<Iter>::pointer;
        using reference = typename std::iterator_traits<Iter>::reference;

        constexpr Deque_reverse_iterator() = default;

        constexpr explicit Deque_reverse_iterator(iterator_type x)
        {
            this->point = new Node<iterator_type>(x);
        }

        constexpr explicit Deque_reverse_iterator(Node<Iter>* p) : point(p) { }

        template <class U>
        constexpr Deque_reverse_iterator(const Deque_reverse_iterator<U>& other) : point(other.point) { }

        template <class U>
        Deque_reverse_iterator& operator=(const Deque_reverse_iterator<U>& other)
        {
            this->point = other.point;
        }

        iterator_type base() const
        {
            return Iter;
        }

        reference operator*() const
        {
            reference ref = *(this->point->value);
            return ref;
        }

        pointer operator->() const
        {
            pointer p = static_cast<pointer>(&(this->point->value));
            return p;
        }

        reference operator[](difference_type n);

        Deque_reverse_iterator& operator++()
        {
            *this -= 1;
            return *this;
        }
        Deque_reverse_iterator operator++(int)
        {
            *this -= 1;
            return *this;
        }

        Deque_reverse_iterator& operator--()
        {
            *this += 1;
            return *this;
        }
        Deque_reverse_iterator operator--(int)
        {
            *this += 1;
            return *this;
        }

        Deque_reverse_iterator operator+(difference_type n) const
        {
            Deque_reverse_iterator a(*this);
            a -= n;
            return a;
        }

        Deque_reverse_iterator& operator+=(difference_type n)
        {
            int i = 0;
            int b = static_cast<int>(n);
            while (i < b)
            {
                this->point = this->point->prev;
                if (this->point == nullptr)
                {
                    break;
                }
                i++;
            }
            return *this;
        }

        Deque_reverse_iterator operator-(difference_type n) const
        {
            Deque_reverse_iterator a(*this);
            a += n;
            return a;
        }
        Deque_reverse_iterator& operator-=(difference_type n)
        {
            int i = 0;
            int b = static_cast<int>(n);
            while (i < b)
            {
                this->point = this->point->next;
                if (this->point == nullptr)
                {
                    break;
                }
                i++;
            }
            return *this;
        }

        template <class Iterator1, class Iterator2>
        friend bool operator==(const Deque_reverse_iterator<Iterator1>& lhs,
            const Deque_reverse_iterator<Iterator2>& rhs)
        {
            return lhs.point == rhs.point;
        }

        template <class Iterator1, class Iterator2>
        friend bool operator!=(const Deque_reverse_iterator<Iterator1>& lhs,
            const Deque_reverse_iterator<Iterator2>& rhs)
        {
            return !(lhs == rhs);
        }

        template <class Iterator1, class Iterator2>
        friend bool operator>(const Deque_reverse_iterator<Iterator1>& lhs,
            const Deque_reverse_iterator<Iterator2>& rhs)
        {
            Node<Iterator1> node = lhs.point;
            if (node == rhs.point)
            {
                return false;
            }
            else
            {
                while (true)
                {
                    node = node.next;
                    if (node == rhs.point)
                    {
                        return true;
                    }
                    else if(node == nullptr)
                    {
                        return false;
                    }
                }
            }
        }

        template <class Iterator1, class Iterator2>
        friend bool operator<(const Deque_reverse_iterator<Iterator1>& lhs,
            const Deque_reverse_iterator<Iterator2>& rhs)
        {
            Node<Iterator1> node = rhs.point;
            if (node == lhs.point)
            {
                return false;
            }
            else
            {
                while (true)
                {
                    node = node.next;
                    if (node == lhs.point)
                    {
                        return true;
                    }
                    else if (node == nullptr)
                    {
                        return false;
                    }
                }
            }
        }

        template <class Iterator1, class Iterator2>
        friend bool operator<=(const Deque_reverse_iterator<Iterator1>& lhs,
            const Deque_reverse_iterator<Iterator2>& rhs)
        {
            Node<Iterator1> node = rhs.point;
            if (node == lhs.point)
            {
                return true;
            }
            else
            {
                while (true)
                {
                    node = node.next;
                    if (node == lhs.point)
                    {
                        return true;
                    }
                    else if (node == nullptr)
                    {
                        return false;
                    }
                }
            }
        }

        template <class Iterator1, class Iterator2>
        friend bool operator>=(const Deque_reverse_iterator<Iterator1>& lhs,
            const Deque_reverse_iterator<Iterator2>& rhs)
        {
            Node<Iterator1> node = lhs.point;
            if (node == rhs.point)
            {
                return true;
            }
            else
            {
                while (true)
                {
                    node = node.next;
                    if (node == rhs.point)
                    {
                        return true;
                    }
                    else if (node == nullptr)
                    {
                        return false;
                    }
                }
            }
        }

        template <class IterT>
        friend Deque_reverse_iterator<IterT> operator+(
            typename Deque_reverse_iterator<IterT>::difference_type n,
            const Deque_reverse_iterator<IterT>& it);

        template <class Iterator>
        friend auto operator-(const Deque_reverse_iterator<Iterator>& lhs,
            const Deque_reverse_iterator<Iterator>& rhs);

        // operator <=> will be handy

        // friend constexpr std::iter_rvalue_reference_t<Iter> iter_move( const
        // std::reverse_iterator& i ); // For extra points

        // template<std::indirectly_swappable<Iter> Iter2>
        // friend constexpr void iter_swap(const reverse_iterator& x, const
        // std::reverse_iterator<Iter2>& y); // For extra points
    };

    template <class Iter>
    Deque_reverse_iterator<Iter> make_reverse_iterator(Iter i);

    template <typename T, typename Allocator = Allocator<T>>
    class Deque {
    public:
        using value_type = T;
        using allocator_type = Allocator;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = typename std::allocator_traits<Allocator>::pointer;
        using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
        using iterator = Deque_iterator<value_type>;
        using const_iterator = Deque_const_iterator<value_type>;
        using reverse_iterator = Deque_reverse_iterator<iterator>;
        using const_reverse_iterator = Deque_reverse_iterator<const_iterator>;

        /// @brief Default constructor. Constructs an empty container with a
        /// default-constructed allocator.
        Deque() = default;

        /// @brief Constructs an empty container with the given allocator
        /// @param alloc allocator to use for all memory allocations of this container
        explicit Deque(const Allocator& alloc) : allocator(alloc), count_elements(0) { }

        /// @brief Constructs the container with count copies of elements with value
        /// and with the given allocator
        /// @param count the size of the container
        /// @param value the value to initialize elements of the container with
        /// @param alloc allocator to use for all memory allocations of this container
        Deque(size_type count, const T& value, const Allocator& alloc = Allocator()) : count_elements(0), allocator(alloc)
        {
            for (int i = 0; i < static_cast<int>(count); i++)
            {
                this->push_back(value);
            }
        }

        /// @brief Constructs the container with count default-inserted instances of
        /// T. No copies are made.
        /// @param count the size of the container
        /// @param alloc allocator to use for all memory allocations of this container
        explicit Deque(size_type count, const Allocator& alloc = Allocator()) : count_elements(0), allocator(alloc)
        {
            for (int i = 0; i < static_cast<int>(count); i++)
            {
                this->push_back(T{});
            }
        }

        /// @brief Copy constructor. Constructs the container with the copy of the
        /// contents of other.
        /// @param other another container to be used as source to initialize the
        /// elements of the container with
        Deque(const Deque& other): count_elements(0)
        {
            for (auto it = other.begin(); it != other.end(); it++)
            {
                this->push_back(*it);
            }
        }

        /// @brief Constructs the container with the copy of the contents of other,
        /// using alloc as the allocator.
        /// @param other another container to be used as source to initialize the
        /// elements of the container with
        /// @param alloc allocator to use for all memory allocations of this container
        Deque(const Deque& other, const Allocator& alloc) : count_elements(0), allocator(alloc)
        {
            for (auto it = other.begin(); it != other.end(); it++)
            {
                this->push_back(*it);
            }
        }

        /**
         * @brief Move constructor.
         *
         * Constructs the container with the contents of other using move semantics.
         * Allocator is obtained by move-construction from the allocator belonging to
         * other.
         *
         * @param other another container to be used as source to initialize the
         * elements of the container with
         */
        Deque(Deque&& other)
        {
            swap(other);
        }

        /**
         * @brief Allocator-extended move constructor.
         * Using alloc as the allocator for the new container, moving the contents
         * from other; if alloc != other.get_allocator(), this results in an
         * element-wise move.
         *
         * @param other another container to be used as source to initialize the
         * elements of the container with
         * @param alloc allocator to use for all memory allocations of this container
         */
        Deque(Deque&& other, const Allocator& alloc): allocator(alloc)
        {
            swap(other);
        }

        /// @brief Constructs the container with the contents of the initializer list
        /// init.
        /// @param init initializer list to initialize the elements of the container
        /// with
        /// @param alloc allocator to use for all memory allocations of this container
        Deque(std::initializer_list<T> init, const Allocator& alloc = Allocator()) : count_elements(0), allocator(alloc)
        {
            for (auto it = init.begin(); it != init.end(); it++)
            {
                this->push_back(*it);
            }
        }

        /// @brief Destructs the deque.
        ~Deque()
        {
            Node<T>* firstNode = this->head;
            if (firstNode == nullptr)
            {
                return;
            }
            Node<T>* secondNode = firstNode->next;
            while (secondNode != nullptr)
            {
                delete firstNode;
                firstNode = secondNode;
                secondNode = secondNode->next;
            }
        }

        /// @brief Copy assignment operator. Replaces the contents with a copy of the
        /// contents of other.
        /// @param other another container to use as data source
        /// @return *this
        Deque& operator=(const Deque& other)
        {
            Deque temp{ other };
            std::swap(temp, *this);
            return *this;
        }

        /**
         * Move assignment operator.
         *
         * Replaces the contents with those of other using move semantics
         * (i.e. the data in other is moved from other into this container).
         * other is in a valid but unspecified state afterwards.
         *
         * @param other another container to use as data source
         * @return *this
         */
        Deque& operator=(Deque&& other)
        {
            Deque temp{std::move(other)};
            std::swap(temp, *this);
            return *this;
        }

        /// @brief Replaces the contents with those identified by initializer list
        /// ilist.
        /// @param ilist
        /// @return this
        Deque& operator=(std::initializer_list<T> ilist)
        {
            std::swap(this->head, ilist[0]);
            std::swap(this->last, ilist[ilist.size() - 1]);
            count_elements = ilist.size();
        }

        /// @brief Replaces the contents with count copies of value
        /// @param count
        /// @param value
        void assign(size_type count, const T& value);

        /// @brief Replaces the contents with copies of those in the range [first,
        /// last).
        /// @tparam InputIt
        /// @param first
        /// @param last
        template <class InputIt>
        void assign(InputIt first, InputIt last);

        /// @brief Replaces the contents with the elements from the initializer list
        /// ilis
        /// @param ilist
        void assign(std::initializer_list<T> ilist);

        /// @brief Returns the allocator associated with the container.
        /// @return The associated allocator.
        allocator_type get_allocator() const noexcept
        {
            return this->allocator;
        }

        /// ELEMENT ACCESS

        /// @brief Returns a reference to the element at specified location pos, with
        /// bounds checking. If pos is not within the range of the container, an
        /// exception of type std::out_of_range is thrown.
        /// @param pos position of the element to return
        /// @return Reference to the requested element.
        /// @throw std::out_of_range
        reference at(size_type pos)
        {
            reference it = *(this->begin() + (pos - 1));
            return it;
        }

        /// @brief Returns a const reference to the element at specified location pos,
        /// with bounds checking. If pos is not within the range of the container, an
        /// exception of type std::out_of_range is thrown.
        /// @param pos position of the element to return
        /// @return Const Reference to the requested element.
        /// @throw std::out_of_range
        const_reference at(size_type pos) const
        {
            const_reference it = *(this->begin() + (pos - 1));
            return it;
        }

        /// @brief Returns a reference to the element at specified location pos. No
        /// bounds checking is performed.
        /// @param pos position of the element to return
        /// @return Reference to the requested element.
        reference operator[](size_type pos);

        /// @brief Returns a const reference to the element at specified location pos.
        /// No bounds checking is performed.
        /// @param pos position of the element to return
        /// @return Const Reference to the requested element.
        const_reference operator[](size_type pos) const;

        /// @brief Returns a reference to the first element in the container.
        /// Calling front on an empty container is undefined.
        /// @return Reference to the first element
        reference front()
        {
            reference it = *(this->begin());
            return it;
        }

        /// @brief Returns a const reference to the first element in the container.
        /// Calling front on an empty container is undefined.
        /// @return Const reference to the first element
        const_reference front() const
        {
            const_reference it = *(this->begin());
            return it;
        }

        /// @brief Returns a reference to the last element in the container.
        /// Calling back on an empty container causes undefined behavior.
        /// @return Reference to the last element.
        reference back()
        {
            reference b = this->last->value;
            return b;
        }

        /// @brief Returns a const reference to the last element in the container.
        /// Calling back on an empty container causes undefined behavior.
        /// @return Const Reference to the last element.
        const_reference back() const
        {
            const_reference b = this->last->value;
            return b;
        }

        /// ITERATORS

        /// @brief Returns an iterator to the first element of the deque.
        /// If the deque is empty, the returned iterator will be equal to end().
        /// @return Iterator to the first element.
        iterator begin() noexcept
        {
            iterator b(head);
            return b;
        }

        /// @brief Returns an iterator to the first element of the deque.
        /// If the deque is empty, the returned iterator will be equal to end().
        /// @return Iterator to the first element.
        const_iterator begin() const noexcept
        {
            const_iterator b(head);
            return b;
        }

        /// @brief Same to begin()
        const_iterator cbegin() const noexcept
        {
            const_iterator b(head);
            return b;
        }

        /// @brief Returns an iterator to the element following the last element of
        /// the deque. This element acts as a placeholder; attempting to access it
        /// results in undefined behavior.
        /// @return Iterator to the element following the last element.
        iterator end() noexcept
        {
            iterator e(nullptr);
            return e;
        }

        /// @brief Returns an constant iterator to the element following the last
        /// element of the deque. This element acts as a placeholder; attempting to
        /// access it results in undefined behavior.
        /// @return Constant Iterator to the element following the last element.
        const_iterator end() const noexcept
        {
            const_iterator e(nullptr);
            return e;
        }

        /// @brief Same to end()
        const_iterator cend() const noexcept
        {
            const_iterator e(nullptr);
            return e;
        }

        /// @brief Returns a reverse iterator to the first element of the reversed
        /// deque. It corresponds to the last element of the non-reversed deque. If
        /// the deque is empty, the returned iterator is equal to rend().
        /// @return Reverse iterator to the first element.
        reverse_iterator rbegin() noexcept
        {
            reverse_iterator b(last);
            return b;
        }

        /// @brief Returns a const reverse iterator to the first element of the
        /// reversed deque. It corresponds to the last element of the non-reversed
        /// deque. If the deque is empty, the returned iterator is equal to rend().
        /// @return Const Reverse iterator to the first element.
        const_reverse_iterator rbegin() const noexcept
        {
            const_reverse_iterator b(last);
            return b;
        }

        /// @brief Same to rbegin()
        const_reverse_iterator crbegin() const noexcept
        {
            const_reverse_iterator b(last);
            return b;
        }

        /// @brief Returns a reverse iterator to the element following the last
        /// element of the reversed deque. It corresponds to the element preceding the
        /// first element of the non-reversed deque. This element acts as a
        /// placeholder, attempting to access it results in undefined behavior.
        /// @return Reverse iterator to the element following the last element.
        reverse_iterator rend() noexcept
        {
            reverse_iterator e(nullptr);
            return e;
        }

        /// @brief Returns a const reverse iterator to the element following the last
        /// element of the reversed deque. It corresponds to the element preceding the
        /// first element of the non-reversed deque. This element acts as a
        /// placeholder, attempting to access it results in undefined behavior.
        /// @return Const Reverse iterator to the element following the last element.
        const_reverse_iterator rend() const noexcept
        {
            const_reverse_iterator e(nullptr);
            return e;
        }

        /// @brief Same to rend()
        const_reverse_iterator crend() const noexcept
        {
            const_reverse_iterator e(nullptr);
            return e;
        }

        /// CAPACITY

        /// @brief Checks if the container has no elements
        /// @return true if the container is empty, false otherwise
        bool empty() const noexcept
        {
            return count_elements == 0;
        }

        /// @brief Returns the number of elements in the container
        /// @return The number of elements in the container.
        size_type size() const noexcept
        {
            return count_elements;
        }

        /// @brief Returns the maximum number of elements the container is able to
        /// hold due to system or library implementation limitations
        /// @return Maximum number of elements.
        size_type max_size() const noexcept;

        /// @brief Requests the removal of unused capacity.
        /// It is a non-binding request to reduce the memory usage without changing
        /// the size of the sequence. All iterators and references are invalidated.
        /// Past-the-end iterator is also invalidated.
        void shrink_to_fit();

        /// MODIFIERS

        /// @brief Erases all elements from the container.
        /// nvalidates any references, pointers, or iterators referring to contained
        /// elements. Any past-the-end iterators are also invalidated.
        void clear() noexcept
        {
            Node<T>* node1 = head;
            Node<T>* node2 = head->next;
            while (node2 != nullptr)
            {
                delete node1;
                node1 = nullptr;
                node1 = node2;
                node2 = node2->next;
            }
            delete node1;
            node1 = nullptr;
            count_elements = 0;
            head = nullptr;
            last = nullptr;
        }

        /// @brief Inserts value before pos.
        /// @param pos iterator before which the content will be inserted.
        /// @param value element value to insert
        /// @return Iterator pointing to the inserted value.
        iterator insert(const_iterator pos, const T& value);

        /// @brief Inserts value before pos.
        /// @param pos iterator before which the content will be inserted.
        /// @param value element value to insert
        /// @return Iterator pointing to the inserted value.
        iterator insert(const_iterator pos, T&& value);

        /// @brief Inserts count copies of the value before pos.
        /// @param pos iterator before which the content will be inserted.
        /// @param count number of elements to insert
        /// @param value element value to insert
        /// @return Iterator pointing to the first element inserted, or pos if count
        /// == 0.
        iterator insert(const_iterator pos, size_type count, const T& value);

        /// @brief Inserts elements from range [first, last) before pos.
        /// @tparam InputIt Input Iterator
        /// @param pos iterator before which the content will be inserted.
        /// @param first,last the range of elements to insert, can't be iterators into
        /// container for which insert is called
        /// @return Iterator pointing to the first element inserted, or pos if first
        /// == last.
        template <class InputIt>
        iterator insert(const_iterator pos, InputIt first, InputIt last);

        /// @brief Inserts elements from initializer list before pos.
        /// @param pos iterator before which the content will be inserted.
        /// @param ilist initializer list to insert the values from
        /// @return Iterator pointing to the first element inserted, or pos if ilist
        /// is empty.
        iterator insert(const_iterator pos, std::initializer_list<T> ilist);

        /// @brief Inserts a new element into the container directly before pos.
        /// @param pos iterator before which the new element will be constructed
        /// @param ...args arguments to forward to the constructor of the element
        /// @return terator pointing to the emplaced element.
        template <class... Args>
        iterator emplace(const_iterator pos, Args&&... args);

        /// @brief Removes the element at pos.
        /// @param pos iterator to the element to remove
        /// @return Iterator following the last removed element.
        iterator erase(const_iterator pos);

        /// @brief Removes the elements in the range [first, last).
        /// @param first,last range of elements to remove
        /// @return Iterator following the last removed element.
        iterator erase(const_iterator first, const_iterator last);

        /// @brief Appends the given element value to the end of the container.
        /// The new element is initialized as a copy of value.
        /// @param value the value of the element to append
        void push_back(const T& value)
        {
            Node<T>* node = new Node<T>(value);
            if (head == nullptr)
            {
                head = node;
                last = node;
            }
            else
            {
                node->prev = last;
                last->next = node;
                last = node;
            }
            count_elements++;
        }

        /// @brief Appends the given element value to the end of the container.
        /// Value is moved into the new element.
        /// @param value the value of the element to append
        void push_back(T&& value)
        {
            Node<T>* node = new Node<T>(value);
            if (head == nullptr)
            {
                head = node;
                last = node;
            }
            else
            {
                node->prev = last;
                last->next = node;
                last = node;
            }
            count_elements++;
        }

        /// @brief Appends a new element to the end of the container.
        /// @param ...args arguments to forward to the constructor of the element
        /// @return A reference to the inserted element.
        template <class... Args>
        reference emplace_back(Args&&... args);

        /// @brief Removes the last element of the container.
        void pop_back()
        {
            if (count_elements > 1)
            {
                Node<T>* node = last;
                last = last->prev;
                last->next = nullptr;
                delete node;
                count_elements--;
            }
            else if (count_elements == 1)
            {
                delete last;
                last = nullptr;
                count_elements--;
            }
        }

        /// @brief Prepends the given element value to the beginning of the container.
        /// @param value the value of the element to prepend
        void push_front(const T& value)
        {
            Node<T>* node = new Node<T>(value);
            if (count_elements == 0)
            {
                head = node;
                last = node;
            }
            else
            {
                node->next = head;
                head->prev = node;
                head = node;
            }
            count_elements++;
        }

        /// @brief Prepends the given element value to the beginning of the container.
        /// @param value moved value of the element to prepend
        void push_front(T&& value)
        {
            Node<T>* node = new Node<T>(value);
            if (count_elements == 0)
            {
                head = node;
                last = node;
            }
            else
            {
                node->next = head;
                head->prev = node;
                head = node;
            }
            count_elements++;
        }

        /// @brief Inserts a new element to the beginning of the container.
        /// @param ...args arguments to forward to the constructor of the element
        /// @return A reference to the inserted element.
        template <class... Args>
        reference emplace_front(Args&&... args);

        /// @brief Removes the first element of the container.
        void pop_front()
        {
            if (count_elements > 1)
            {
                head = head->next;
                delete head->prev;
                head->prev = nullptr;
                count_elements--;
            }
            else if (count_elements == 1)
            {
                delete head;
                head = nullptr;
                count_elements--;
            }
        }

        /// @brief Resizes the container to contain count elements.
        /// If the current size is greater than count, the container is reduced to its
        /// first count elements. If the current size is less than count, additional
        /// default-inserted elements are appended
        /// @param count new size of the container
        void resize(size_type count)
        {
            if (this->size() > count)
            {
                while (this->size() != count)
                {
                    this->pop_back;
                }
            }
            else if(this->size < count)
            {
                while (this->size() != count)
                {
                    this->push_back(T{});
                }
            }
        }

        /// @brief Resizes the container to contain count elements.
        /// If the current size is greater than count, the container is reduced to its
        /// first count elements. If the current size is less than count, additional
        /// copies of value are appended.
        /// @param count new size of the container
        /// @param value the value to initialize the new elements with
        void resize(size_type count, const value_type& value)
        {
            if (this->size() > count)
            {
                while (this->size() != count)
                {
                    this->pop_back;
                }
            }
            else if (this->size < count)
            {
                while (this->size() != count)
                {
                    this->push_back(value);
                }
            }
        }

        /// @brief Exchanges the contents of the container with those of other.
        /// Does not invoke any move, copy, or swap operations on individual elements.
        /// All iterators and references remain valid. The past-the-end iterator is
        /// invalidated.
        /// @param other container to exchange the contents with
        void swap(Deque& other)
        {
            std::swap(this->count_elements, other.count_elements);
            std::swap(this->head, other.head);
            std::swap(this->last, other.last);
        }

        /// COMPARISIONS

        /// @brief Checks if the contents of lhs and rhs are equal
        /// @param lhs,rhs deques whose contents to compare
        template <class U, class Alloc>
        friend bool operator==(const Deque<U, Alloc>& lhs,
            const Deque<U, Alloc>& rhs);

        /// @brief Checks if the contents of lhs and rhs are not equal
        /// @param lhs,rhs deques whose contents to compare
        template <class U, class Alloc>
        friend bool operator!=(const Deque<U, Alloc>& lhs,
            const Deque<U, Alloc>& rhs);

        /// @brief Compares the contents of lhs and rhs lexicographically.
        /// @param lhs,rhs deques whose contents to compare
        template <class U, class Alloc>
        friend bool operator>(const Deque<U, Alloc>& lhs, const Deque<U, Alloc>& rhs);

        /// @brief Compares the contents of lhs and rhs lexicographically.
        /// @param lhs,rhs deques whose contents to compare
        template <class U, class Alloc>
        friend bool operator<(const Deque<U, Alloc>& lhs, const Deque<U, Alloc>& rhs);

        /// @brief Compares the contents of lhs and rhs lexicographically.
        /// @param lhs,rhs deques whose contents to compare
        template <class U, class Alloc>
        friend bool operator>=(const Deque<U, Alloc>& lhs,
            const Deque<U, Alloc>& rhs);

        /// @brief Compares the contents of lhs and rhs lexicographically.
        /// @param lhs,rhs deques whose contents to compare
        template <class U, class Alloc>
        friend bool operator<=(const Deque<U, Alloc>& lhs,
            const Deque<U, Alloc>& rhs);

        // operator <=> will be handy
    private:
        Node<T>* head = nullptr;
        Node<T>* last = nullptr;
        allocator_type allocator;
        size_type count_elements;
    };

    /// NON-MEMBER FUNCTIONS

    /// @brief  Swaps the contents of lhs and rhs.
    /// @param lhs,rhs containers whose contents to swap
    template <class T, class Alloc>
    void swap(Deque<T, Alloc>& lhs, Deque<T, Alloc>& rhs)
    {
        std::swap(lhs->count_elements, rhs.count_elements);
        std::swap(lhs->head, rhs.head);
        std::swap(lhs->last, rhs.last);
        std::swap(lhs.allocator, rhs.allocator);
    }

    /// @brief Erases all elements that compare equal to value from the container.
    /// @param c container from which to erase
    /// @param value value to be removed
    /// @return The number of erased elements.
    template <class T, class Alloc, class U>
    typename Deque<T, Alloc>::size_type erase(Deque<T, Alloc>& c, const U& value);

    /// @brief Erases all elements that compare equal to value from the container.
    /// @param c container from which to erase
    /// @param pred unary predicate which returns ​true if the element should be
    /// erased.
    /// @return The number of erased elements.
    template <class T, class Alloc, class Pred>
    typename Deque<T, Alloc>::size_type erase_if(Deque<T, Alloc>& c, Pred pred);

}  // namespace fefu_laboratory_two

