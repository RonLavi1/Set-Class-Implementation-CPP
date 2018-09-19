#ifndef EX3_MY_SET_HPP
#define EX3_MY_SET_HPP

#include "my_set.h"

/**
 * copy C'tor
 * @param x
 */
template<class value_type>
my_set<value_type>::my_set(const my_set<value_type> &x):_size(0)
{

    if (x._getHead())
    {
        _head = nullptr;
        *this = my_set(x.cbegin(), x.cend());
    }
    else
    {
        _head = nullptr;
    }
}

/**
 * move C'tor
 * Constructs a container that acquires the elements of x.
 * @param x
 */
template<class value_type>
my_set<value_type>::my_set(my_set<value_type> && x) noexcept
{
    swap(x);
}

/**
 * interator C'tor, creates the new object with the values between first and last
 * @param first
 * @param last
 */
template<class value_type>
my_set<value_type>::my_set(my_set<value_type>::const_iterator &first, my_set<value_type>::const_iterator &last):_size(0)
{
    _head = nullptr;
    for (auto i = first ; i != last ; ++i)
    {
        Node cur(i->getData());
        insert(cur.getData());
    }
}

/**
 * Constructs a container with as many elements as the range [first,last)
 * @tparam InputIterator
 * @param start
 * @param last
 */
template<class value_type>
template<class InputIterator>
my_set<value_type>::my_set(InputIterator first, InputIterator last):_size(0)
{
    _head = nullptr;
    for (auto i = first ; i != last ; i++)
    {
        insert(*i);
    }
}

/**
 * Set destructor
 */
template<class value_type>
my_set<value_type>::~my_set<value_type>()
{
    clear();
    _size = 0;
}

/**
 * Assigns new contents to the container, replacing its current content.
 * @param x
 * @return
 */
template<class value_type>
my_set<value_type> &my_set<value_type>::operator=(const my_set<value_type> &x)
{
    my_set tempSet = my_set(x);
    swap(tempSet);
    return *this;
}

/**
 * Assigns new contents to the container, replacing its current content.
 * @param x
 * @return
 */
template<class value_type>
my_set<value_type> &my_set<value_type>::operator=(my_set<value_type> && x) noexcept
{
    swap(x);
    return *this;
}

/**
 * Returns a const_iterator pointing to the first element in the container.
 * @return
 */
template<class value_type>
const typename my_set<value_type>::const_iterator my_set<value_type>::cbegin() const noexcept
{
    if (_getHead())
    {
        std::shared_ptr<Node> cur = _getHead();
        while (cur->getLeft())
        {
            cur = cur->getLeft();
        }
        return const_iterator(cur);
    }
    return const_iterator();
}

/**
 * Returns a const_iterator pointing to the last element in the container.
 * @return
 */
template<class value_type>
const typename my_set<value_type>::const_iterator my_set<value_type>::cend() const noexcept
{
    return const_iterator();
}

/**
* @return a const_iterator pointing to the first element in the container.
*/
template<class value_type>
const typename my_set<value_type>::const_reverse_iterator my_set<value_type>::crbegin() const noexcept
{
    if (_getHead())
    {
        std::shared_ptr<Node> cur = _getHead();
        while (cur->getRight())
        {
            cur = cur->getRight();
        }
        return const_reverse_iterator(cur);
    }
    return const_reverse_iterator();
}

/**
 * @return A const_reverse_iterator to the reverse end of the sequence.
 */
template<class value_type>
const typename my_set<value_type>::const_reverse_iterator my_set<value_type>::crend() const noexcept
{
    return const_reverse_iterator();
}

/**
 * Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
 * @param val Value to be copied
 * @return a pair, with its member pair::first set to an iterator pointing to either the newly inserted element or to the equivalent element already in the set.
 */
template<class value_type>
std::pair<typename my_set<value_type>::const_iterator, bool>
my_set<value_type>::insert(const value_type &val)
{
    std::shared_ptr<Node> parent;
    std::shared_ptr<Node> cur = _getHead();
    if (_getHead())
    {
        while (cur)
        {
            parent = cur;
            if (cur->getData() == val)
            {
                return std::make_pair(const_iterator(cur), false);
            }
            cur->getData() < val ? cur = cur->getRight() : cur = cur->getLeft();
        }
    }
    increaseSize();
    cur = std::make_shared<Node>(val);
    cur->setParent(parent);
    if (!parent)
    {
        _head = cur;
    }
    else
    {
        cur->getData() < parent->getData() ? parent->setLeft(cur) : parent->setRight(cur);
    }

    const_iterator toInsert = const_iterator(cur);
    return std::make_pair(toInsert, true);
}

/**
 * Extends the container by inserting new elements, effectively increasing the container size by the number of elements inserted.
 * @param val Value to be copied
 * @return a pair, with its member pair::first set to an iterator pointing to either the newly inserted element or to the equivalent element already in the set.
 */
template<class value_type>
typename my_set<value_type>::const_iterator
my_set<value_type>::insert(my_set<value_type>::const_iterator position, const value_type &val)
{
    if (!position.getIterator())
    {
        std::pair<my_set<value_type>::const_iterator, bool> ans = insert(val);
        return ans.first;
    }
    my_set<value_type>::const_iterator positionPointer = position;
    my_set<value_type>::const_iterator positionPredecessor = position;
    if (positionPredecessor != cbegin())
    {
        positionPredecessor--;
    }
    if (positionPredecessor.getIterator()->getData() < val && positionPointer.getIterator()->getData() > val)
    {
        std::shared_ptr<Node> toInsert = std::make_shared<my_set<value_type>::Node>(val);
        if (positionPredecessor->getRight() != positionPointer.getIterator())
        {
            positionPredecessor->setRight(toInsert);
            toInsert->setParent(positionPredecessor.getIterator());
        }
        else
        {
            toInsert->setParent(position.getIterator());
            position.getIterator()->getLeft() = toInsert;
        }
        increaseSize();
        const_iterator retVal = const_iterator(toInsert);
        return retVal;
    }
    else
    {
        return insert(val).first;
    }
}

/**
 *
 * @tparam InputIterator
 * @param first
 * @param last
 */
template<class value_type>
template<class InputIterator>
void my_set<value_type>::insert(InputIterator first, InputIterator last)
{
    for (auto i = first ; i != last ; ++i)
    {
        insert(*i);
    }
}

/**
 * Removes from the set container a single element
 * @param position
 * @return
 */
template<class value_type>
typename my_set<value_type>::const_iterator
my_set<value_type>::erase(my_set<value_type>::const_iterator position)
{
    std::shared_ptr<Node> cur = position.getIterator();
    const_iterator successor = position;
    successor++;
    decreaseSize();
    if (cur->getRight() && cur->getLeft())
    {
        value_type temp = cur->getData();
        cur->setDate(successor.getIterator()->getData());
        successor.getIterator()->setDate(temp);
        increaseSize();
        erase(successor);
        return const_iterator(cur);
    }
    else if (!(cur->getRight() || cur->getLeft()))
    {
        if (cur == _getHead())
        {
            _size = 0;
            _head = nullptr;
            return const_iterator();
        }
        cur != cur->getParent().lock()->getLeft() ? cur->getParent().lock()->setRight
                (nullptr) : cur->getParent().lock()->setLeft(nullptr);
        return successor;
    }

    if (cur->getLeft())
    {
        if (cur == _getHead())
        {
            cur->getLeft()->setParent(std::make_shared<Node>());
            _head = cur->getLeft();
        }
        else if (cur == cur->getParent().lock()->getLeft())
        {
            cur->getParent().lock()->setLeft(cur->getLeft());
            cur->getLeft()->setParent(cur->getParent());
        }
        else
        {
            cur->getParent().lock()->setRight(cur->getLeft());
            cur->getLeft()->setParent(cur->getParent());
        }
        return successor;
    }
    if (cur == _getHead())
    {
        cur->getRight()->getParent().lock() = nullptr;
        _head = cur->getRight();
    }
    else if (cur == cur->getParent().lock()->getLeft())
    {
        cur->getParent().lock()->setLeft(cur->getRight());
        cur->getRight()->setParent(cur->getParent());
    }
    else
    {
        cur->getParent().lock()->setRight(cur->getRight());
        cur->getRight()->setParent(cur->getParent());
    }
    return successor;
}

/**
 * Removes from the set container a single element
 * @param val
 * @return
 */
template<class value_type>
size_t my_set<value_type>::erase(const value_type &val)
{
    const_iterator ans = find(val);
    if (ans.getIterator())
    {
        erase(ans);
        return 1;
    }
    return 0;
}

/**
 * Removes from the set container range of elements
 * @param first
 * @param last
 * @return
 */
template<class value_type>
typename my_set<value_type>::const_iterator
my_set<value_type>::erase(my_set<value_type>::const_iterator first, my_set<value_type>::const_iterator last)
{
    if (*first > *last)
    {
        return const_iterator();
    }
    my_set<value_type>::const_iterator cur = first;
    if (last != cend())
    {
        value_type lastVal = *last;
        cur = first;
        while (*cur != lastVal)
        {
            cur = erase(cur);
        }
    }
    else
    {
        while (cur != last)
        {
            cur = erase(cur);
        }
    }
    return cur;
}

/**
 * Exchanges the content of the container by the content of x, which is another set of the same type. Sizes may differ.
 * @param set
 */
template<class value_type>
void my_set<value_type>::swap(my_set<value_type> &set) noexcept
{
    std::swap(set._head, _head);
    _size = set.size();
    set._size = 0;
}

/**
 * Exchanges the content of the container by the content of x, which is another set of the same type. Sizes may differ.
 */
template<class value_type>
void my_set<value_type>::clear() noexcept
{
    for (auto i = cbegin() ; i != cend() ; i++)
    {
        erase(i);
    }
    _head = nullptr;
}

/**
 * Searches the container for an element equivalent to val and returns an iterator to it if found, otherwise it returns an iterator to set::end
 * @param val
 * @return
 */
template<class value_type>
typename my_set<value_type>::const_iterator my_set<value_type>::find(const value_type &val) const
{
    for (auto i = cbegin() ; i != cend() ; i++)
    {
        if (val == *i)
        {
            return i;
        }
    }
    return const_iterator();
}

/**
 *Searches the container for an element equivalent to val and returns an iterator to it if found, otherwise it returns an iterator to set::end
 * @param val
 * @return
 */
template<class value_type>
typename my_set<value_type>::const_iterator my_set<value_type>::find(const value_type &val)
{
    for (auto i = cbegin() ; i != cend() ; i++)
    {
        if (val == *i)
        {
            return i;
        }
    }
    return const_iterator();
}

/**
 * prefix ++ for the iterator
 * @return
 */
template<class value_type>
const typename my_set<value_type>::const_iterator &my_set<value_type>::const_iterator::operator++()
{
    if (!iter_node->getRight())
    {
        while (iter_node->getParent().lock() && iter_node == iter_node->getParent().lock()->getRight())
        {
            _setIterNode(iter_node->getParent().lock());
            iter_node->getParent().lock() = iter_node->getParent().lock();
        }
        _setIterNode(iter_node->getParent().lock());
        return *this;
    }
    _setIterNode(iter_node->getRight());
    while (iter_node->getLeft())
    {
        _setIterNode(iter_node->getLeft());
    }
    return *this;
}

/**
 * postfix ++ for the iterator
 * @return
 */
template<class value_type>
const typename my_set<value_type>::const_iterator my_set<value_type>::const_iterator::operator++(int)
{
    const_iterator temp = *this;
    operator++();
    return temp;
}

/**
 * prefix -- for the iterator
 * @return
 */
template<class value_type>
const typename my_set<value_type>::const_iterator &my_set<value_type>::const_iterator::operator--()
{
    if (!iter_node->getLeft())
    {
        while (iter_node->getParent().lock() && iter_node == iter_node->getParent().lock()->getLeft())
        {
            _setIterNode(iter_node->getParent().lock());
            iter_node->getParent().lock() = iter_node->getParent().lock();
        }
        _setIterNode(iter_node->getParent().lock());
        return *this;
    }
    _setIterNode(iter_node->getLeft());
    while (iter_node->getRight())
    {
        _setIterNode(iter_node->getRight());
    }
    return *this;
}

/**
 * postfix -- for the iterator
 * @return
 */
template<class value_type>
const typename my_set<value_type>::const_iterator my_set<value_type>::const_iterator::operator--(int)
{
    const_iterator temp = *this;
    operator--();
    return temp;
}

/**
 * prefix ++ for the iterator
 * @return
 */
template<class value_type>
const typename my_set<value_type>::const_reverse_iterator &my_set<value_type>::ReverseIterator::operator++()
{
    if (!iter_node->getLeft())
    {
        while (iter_node->getParent().lock() && iter_node == iter_node->getParent().lock()->getLeft())
        {
            iter_node = iter_node->getParent().lock();
            iter_node->getParent().lock() = iter_node->getParent().lock();
        }
        iter_node = iter_node->getParent().lock();
        return *this;
    }
    iter_node = iter_node->getLeft();
    while (iter_node->getRight())
    {
        iter_node = iter_node->getRight();
    }
    return *this;
}

/**
 * postfix ++ for the iterator
 * @return
 */
template<class value_type>
const typename my_set<value_type>::const_reverse_iterator
my_set<value_type>::ReverseIterator::operator++(int)
{
    const_reverse_iterator temp = *this;
    operator++();
    return temp;
}

/**
 * prefix -- for the iterator
 * @return
 */
template<class value_type>
const typename my_set<value_type>::const_reverse_iterator &
my_set<value_type>::ReverseIterator::operator--()
{
    if (!iter_node->getRight())
    {
        while (iter_node == iter_node->getParent().lock()->getRight() && iter_node->getParent().lock())
        {
            iter_node = iter_node->getParent().lock();
            iter_node->getParent().lock() = iter_node->getParent().lock();
        }
        iter_node = iter_node->getParent().lock();
        return *this;
    }
    iter_node = iter_node->getRight();
    while (iter_node->getLeft())
    {
        iter_node = iter_node->getLeft();
    }
    return *this;
}

/**
 * postfix -- for the iterator
 * @return
 */
template<class value_type>
const typename my_set<value_type>::const_reverse_iterator
my_set<value_type>::const_reverse_iterator::operator--(int)
{
    const_reverse_iterator temp = *this;
    operator--();
    return temp;
}

#endif