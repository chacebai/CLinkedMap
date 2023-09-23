#ifndef CLINKEDLOWMAP_HPP
#define CLINKEDLOWMAP_HPP

#include <map>
#include <list>

template <typename Key, typename Value>
class CLinkedLowMap
{
public:
    bool insert(const Key &key, const Value &value)
    {
        if (m_data.find(key) == m_data.end())
        {
            m_data.insert(std::pair<Key, Value>(key, value));
            m_insertionOrder.push_back(key);
            return true;
        }
        return false;
    }
    bool emplace(const Key &key, const Value &value)
    {
        if (m_data.find(key) == m_data.end())
        {
            m_data.emplace(key, value);
            m_insertionOrder.emplace_back(key);
            return true;
        }
        return false;
    }

    Value &at(const Key &key)
    {
        typename std::map<Key, Value>::iterator it = m_data.find(key);
        if (it == m_data.end())
        {
            throw std::out_of_range("Key not found");
        }
        return it->second;
    }
    Value &operator[](const Key &key)
    {
        if (m_data.find(key) == m_data.end())
        {
            m_insertionOrder.emplace_back(key);
        }
        return m_data[key];
    }

    class iterator
    {
    public:
        // using iterator_category = std::forward_iterator_tag;
        // using value_type = std::pair<const Key, Value>;
        // using difference_type = std::ptrdiff_t;
        // using pointer = value_type *;
        // using reference = value_type &;

        iterator(typename std::map<Key, Value> &mapData, typename std::list<Key>::iterator orderIt)
            : m_mapData(mapData), m_orderIt(orderIt)
        {
        }

        typename std::map<Key, Value>::iterator operator*()
        {
            typename std::map<Key, Value>::iterator it = m_mapData.find(*m_orderIt);
            if (it == m_mapData.end())
            {
                throw std::out_of_range("Key not found");
            }
            return it;
        }

        typename std::map<Key, Value>::iterator operator->()
        {
            typename std::map<Key, Value>::iterator it = m_mapData.find(*m_orderIt);
            if (it == m_mapData.end())
            {
                throw std::out_of_range("Key not found");
            }
            return it;
        }

        iterator &operator++()
        {
            ++m_orderIt;
            return *this;
        }

        iterator operator++(int)
        {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const iterator &other) const
        {
            return this->m_orderIt == other.m_orderIt;
        }

        bool operator!=(const iterator &other) const
        {
            return this->m_orderIt != other.m_orderIt;
        }

    private:
        typename std::map<Key, Value> &m_mapData;
        typename std::list<Key>::iterator m_orderIt;
    };

    iterator begin()
    {
        return iterator(m_data, m_insertionOrder.begin());
    }

    iterator end()
    {
        return iterator(m_data, m_insertionOrder.end());
    }

    void printInInsertionOrder()
    {
        for (const Key &key : m_insertionOrder)
        {
            std::cout << "Key: " << key << ", Value: " << m_data[key] << std::endl;
        }
    }

    std::list<Key> keyList()
    {
        return m_insertionOrder;
    }

private:
    std::map<Key, Value> m_data;
    std::list<Key> m_insertionOrder;
};

#endif // CLINKEDLOWMAP_HPP
