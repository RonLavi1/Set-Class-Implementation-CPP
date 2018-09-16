
#ifndef EX3_MY_SET_H
#define EX3_MY_SET_H

#include <memory>

/**
 *
 * @tparam T
 */
template<class T>
class my_set
        {
public:

    /**
     * Node Class as part of the set implementation via BST
     */
    class Node
            {
    private:
        T _data;
        std::weak_ptr<Node> _parent;
        std::shared_ptr<Node> _left;
        std::shared_ptr<Node> _right;

    public:

        /**
         * default C'tor
         */
        inline Node() = default;

        /**
         * Copy C'tor
         * @param val
         */
        inline explicit Node(const T &val) : _data(val) {};

        /**
         * gets the data of the node
         * @return
         */
        inline const T &getData() const { return _data; };

        /**
         * sets the data of the node
         * @param val
         */
        inline void setDate(const T &val) { Node::_data = val; };

        /**
         * gets the parent
         * @return
         */
        inline const std::weak_ptr<Node> &getParent() const { return _parent; };

        /**
         * sets the parent
         * @param parent
         */
        inline void setParent(const std::weak_ptr<Node> &parent) { Node::_parent = parent; };

        /**
         * sets the parent
         * @param parent
         */
        inline void setParent(const std::shared_ptr<Node> &parent) { Node::_parent = parent; };

        /**
         * gets the left node
         * @return
         */
        inline std::shared_ptr<Node> &getLeft() { return _left; };

        /**
         * sets the left node
         * @param _left
         */
        inline void setLeft(const std::shared_ptr<Node> &_left) { Node::_left = _left; };

        /**
         * gets the right node
         * @return
         */
        inline const std::shared_ptr<Node> &getRight() const { return _right; }

        /**
         * sets the right node
         * @param _right
         */
        inline void setRight(const std::shared_ptr<Node> &_right) { Node::_right = _right; };
            };

    /**
     * Iterator Class as part of the set implementation in oreder to iterate over the set
     */
    class Iterator
            {
    private:

        std::shared_ptr<Node> iter_node;

        /**
         *
         * @param current
         */
        inline void _setIterNode(const std::shared_ptr<Node> &current) { iter_node = current; };


    public:

        /**
         * default C'tor
         */
        inline Iterator() = default;

        /**
         *
         * @param val
         */
        inline explicit Iterator(const std::shared_ptr<Node> &val) : iter_node(val) {};

        /**
         * returnts the current position of the iterator
         * @return
         */
        inline const std::shared_ptr<Node> &getIterator() const noexcept { return iter_node; };

        /**
         * gets the data of the current node
         * @return
         */
        inline const T operator*() const { return iter_node->getData(); }

        /**
         *
         * @return
         */
        inline my_set::Node *operator->() const { return &*iter_node; }

        /**
         * prefix ++ for the iterator
         * @return
         */
        const Iterator &operator++();

        /**
         * postfix ++ for the iterator
         * @return
         */
        const Iterator operator++(int);

        /**
         * prefix -- for the iterator
         * @return
         */
        const Iterator &operator--();

        /**
         * postfix -- for the iterator
         * @return
         */
        const Iterator operator--(int);

        /**
         * Evaluates two nodes
         * @param rhs
         * @return true if the nodes are the same
         */
        inline bool operator==(Iterator const &rhs) const { return iter_node == rhs.iter_node; }

        /**
         * Evaluates two nodes
         * @param rhs
         * @return true if the nodes are diffrent
         */
        inline bool operator!=(Iterator const &rhs) const { return iter_node != rhs.iter_node; }

            };


    /**
     * Reverse Iterator Class as part of the set implementation in oreder to iterate over the set
     */
    class ReverseIterator
            {
    private:
        std::shared_ptr<Node> iter_node;
    public:

        /**
         * default C'tor
         */
        ReverseIterator() = default;

        /**
         *
         * @param val
         */
        explicit ReverseIterator(std::shared_ptr<Node> &val) : iter_node(val) {};

        /**
         * prefix ++ for the iterator
         * @return
         */
        const ReverseIterator &operator++();

        /**
         * postfix ++ for the iterator
         * @return
         */
        const ReverseIterator operator++(int);


        /**
         * prefix -- for the iterator
         * @return
         */
        const ReverseIterator &operator--();

        /**
         * postfix -- for the iterator
         * @return
         */
        const ReverseIterator operator--(int);

        /**
         * de refernce the pointer
         * @return
         */
        inline const T operator*() const { return iter_node->getData(); };

        /**
         *
         * @return
         */
        inline my_set::Node *operator->() const { return &*iter_node; };

        /**
         * Evaluates two nodes
         * @param rhs
         * @return true if the nodes are the same
         */
        inline bool operator==(ReverseIterator const &rhs) const { return iter_node == rhs.iter_node; };

        /**
         * Evaluates two nodes
         * @param rhs
         * @return true if the nodes are diffrent
         */
        inline bool operator!=(ReverseIterator const &rhs) const { return iter_node != rhs.iter_node; };
            };

    typedef Iterator const_iterator;
    typedef ReverseIterator const_reverse_iterator;
    typedef T value_type;
    typedef size_t size_type;


    /**
     * Constructs an empty container, with no elements.
     */
    inline my_set() : _size(0) {};

    /**
     *
     * @param size
     * @param head
     */
    inline my_set(size_type size, std::shared_ptr<Node> head) : _size(size), _head(head) {};

    /**
     * copy C'tor
     * @param x
     */
    my_set(const my_set<T> &x);

    /**
     * move C'tor
     * Constructs a container that acquires the elements of x.
     * @param x
     */
    my_set(my_set<T> && x) noexcept;

    /**
     * interator C'tor, creates the new object with the values between first and last
     * @param first
     * @param last
     */
    my_set(const_iterator &first, const_iterator &last);

    /**
     * Constructs a container with as many elements as the range [first,last)
     * @tparam InputIterator
     * @param start
     * @param last
     */
    template<class InputIterator>
    my_set(InputIterator first, InputIterator last);

    /**
     * Set destructor
     */
    ~my_set();


    /**
     * Assigns new contents to the container, replacing its current content.
     * @param x
     * @return
     */
    my_set<T> &operator=(const my_set &x);

    /**
     * Assigns new contents to the container, replacing its current content.
     * @param x
     * @return
     */
    my_set<T> &operator=(my_set && x) noexcept;

    /**
     * Returns a const_iterator pointing to the first element in the container.
     * @return
     */
    const Iterator cbegin() const noexcept;


    /**
     * Returns a const_iterator pointing to the last element in the container.
     * @return
     */
    const Iterator cend() const noexcept;

    /**
    * @return a const_iterator pointing to the first element in the container.
    */
    const ReverseIterator crbegin() const noexcept;

    /**
     * @return A const_reverse_iterator to the reverse end of the sequence.
     */
    const ReverseIterator crend() const noexcept;

    /**
     * Test whether container is empty
     * @return true if empty. false o.w
     */
    inline bool empty() const noexcept { return this->_head == nullptr; };

    /**
     * Return container size
     * @return container size
     */
    inline size_type size() const noexcept { return this->_size; };

    /**
     * Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
     * @param val Value to be copied
     * @return a pair, with its member pair::first set to an iterator pointing to either the newly inserted element or to the equivalent element already in the set.
     */
    std::pair<const_iterator, bool> insert(const T &val);

    /**
     * Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
     * @param val Value to be moved
     * @return a pair, with its member pair::first set to an iterator pointing to either the newly inserted element or to the equivalent element already in the set.
     */
    inline std::pair<const_iterator, bool> insert(const T && val) { return insert(val); };

    /**
     * Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
     * @param position Hint for the position where the element can be inserted.
     * @param val Value to be copied
     * @return return an iterator pointing to either the newly inserted element or to the element that already had its same value in the set.
     */
    const_iterator insert(const_iterator position, const T &val);

    /**
     * Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
     * @param position Hint for the position where the element can be inserted.
     * @param val Value to be moved
     * @return return an iterator pointing to either the newly inserted element or to the element that already had its same value in the set.
     */
    inline const_iterator insert(const_iterator position, const T && val) { return insert(position, val); };

    /**
     *
     * @tparam InputIterator
     * @param first
     * @param last
     */
    template<class InputIterator>
    void insert(InputIterator first, InputIterator last);

    /**
     * Removes from the set container a single element
     * @param position
     * @return
     */
    const_iterator erase(const_iterator position);

    /**
     * Removes from the set container a single element
     * @param val
     * @return
     */
    size_type erase(const T &val);

    /**
     * Removes from the set container range of elements
     * @param first
     * @param last
     * @return
     */
    const_iterator erase(const_iterator first, const_iterator last);

    /**
     * Exchanges the content of the container by the content of x, which is another set of the same type. Sizes may differ.
     * @param set
     */
    void swap(my_set<T> &set) noexcept;

    /**
     * Exchanges the content of the container by the content of x, which is another set of the same type. Sizes may differ.
     */
    void clear() noexcept;

    /**
     * Searches the container for an element equivalent to val and returns an iterator to it if found, otherwise it returns an iterator to set::end
     * @param val
     * @return
     */
    const_iterator find(const T &val);

    /**
     *Searches the container for an element equivalent to val and returns an iterator to it if found, otherwise it returns an iterator to set::end
     * @param val
     * @return
     */
    const_iterator find(const T &val) const;

private:
    size_type _size;
    std::shared_ptr<Node> _head;

    /**
     * returns the head
     * @return
     */
    inline const std::shared_ptr<Node> _getHead() const noexcept { return _head; };

    /**
     * decrease size by one
     */
    inline void decreaseSize() noexcept { --_size; };

    /**
     * increase size by one
     */
    inline void increaseSize() noexcept { ++_size; };
        };

#include "my_set.hpp"

#endif //EX3_MY_SET_H
