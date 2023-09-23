#ifndef CLINKEDMAP_HPP
#define CLINKEDMAP_HPP

#include <map>
#include <list>
#include <cassert>
#include <unordered_map>

template <typename KeyType, class MappedType,
          typename Compare = std::less<KeyType>>
class CLinkedMap
{
public:
    /**
     * @brief 保存的entry的类型
     *
     **/
    typedef std::pair<const KeyType, MappedType> EntryType;

    /**
     * @brief list中的非const迭代器类型
     *
     **/
    typedef typename std::list<EntryType>::iterator iterator;

    /**
     * @brief list中的const迭代器类型
     *
     **/
    typedef typename std::list<EntryType>::const_iterator const_iterator;

    /**
     * @brief 在map中插入一个新entry
     *
     * @param [in] new_entry : 待添加的entry
     **/
    std::pair<iterator, bool> insert(const EntryType &new_entry)
    {
        _map_itr pIt = _map_key2entry.find(new_entry.first);
        if (pIt != _map_key2entry.end())
        {
            _values.erase(pIt->second);
            pIt->second = _values.insert(_values.end(), new_entry);
            return std::pair<iterator, bool>(pIt->second, true);
        }
        else
        {
            MappedType valueType = _values.insert(_values.end(), new_entry);
            _map_key2entry.insert(std::pair<KeyType, iterator>(new_entry.first, valueType));
            ++_size;
            return std::pair<iterator, bool>(valueType, true);
        }
    }

    /**
     * @brief 在map中插入一个新entry
     *
     * @param [in] key   : 待添加的key
     * @param [in] value : 待添加的value
     * @note Since C++11
     **/
    std::pair<iterator, bool> emplace(const KeyType &key, const MappedType &value)
    {
        EntryType new_entry = std::make_pair(key, value);
        _map_itr pIt = _map_key2entry.find(new_entry.first);
        if (pIt != _map_key2entry.end())
        {
            _values.erase(pIt->second);
            pIt->second = _values.emplace(_values.end(), new_entry);
            return std::pair<iterator, bool>(pIt->second, true);
        }
        else
        {
            MappedType valueType = _values.emplace(_values.end(), new_entry);
            _map_key2entry.emplace(new_entry.first, valueType);
            ++_size;
            return std::pair<iterator, bool>(valueType, true);
        }
    }

    /**
     * @brief 在map中指定位置插入一个新entry
     *
     * @param [in] new_entry : 待添加的entry
     * @note Since C++11
     **/
    iterator insert(const_iterator it, const EntryType &new_entry)
    {
        _map_itr pIt = _map_key2entry.find(new_entry.first);
        if (pIt != _map_key2entry.end())
        {
            _values.erase(pIt->second);
            --_size;
        }
        iterator _it = _values.insert(it, new_entry);
        _map_key2entry.insert(std::pair<KeyType, iterator>(new_entry.first, _it));
        ++_size;
        return _it;
    }

    /**
     * @brief 在map中指定位置插入一个新entry
     *
     * @param [in] it        : 待添加的迭代器
     * @param [in] new_entry : 待添加的entry
     * @param [in] key       : 待添加的key
     * @param [in] value     : 待添加的value
     * @note Since C++11
     **/
    iterator emplace(const_iterator it, const KeyType &key, const MappedType &value)
    {
        EntryType new_entry = std::make_pair(key, value);
        _map_itr pIt = _map_key2entry.find(new_entry.first);
        if (pIt != _map_key2entry.end())
        {
            _values.erase(pIt->second);
            --_size;
        }
        iterator _it = _values.emplace(it, new_entry);
        _map_key2entry.emplace(std::pair<KeyType, iterator>(new_entry.first, _it));
        ++_size;
        return _it;
    }

    /**
     * @brief 访问value
     *
     * @param [in] key : 待访问的key
     **/
    MappedType &at(const KeyType &key)
    {
        _map_itr pIt = _map_key2entry.find(key);
        if (pIt == _map_key2entry.end())
        {
            throw std::out_of_range("Key not found");
        }
        return pIt->second->second;
    }

    /**
     * @brief 访问value
     *
     * @param [in] key : 待访问的key
     **/
    MappedType &operator[](const KeyType &key)
    {
        _map_itr pIt = _map_key2entry.find(key);
        // EntryType new_entry = std::make_pair(key, HashMap::value_type());
        if (pIt != _map_key2entry.end())
        {
            return pIt->second->second;
        }
        else
        {
            EntryType new_entry = std::make_pair(key, MappedType());
            iterator valueType = _values.insert(_values.end(), new_entry);
            _map_key2entry.insert(std::pair<KeyType, iterator>(new_entry.first, valueType));
            ++_size;
            return valueType->second;
        }
    }

    /**
     * @brief 获取首元素的迭代器
     *
     * @param [in] null
     **/
    inline iterator begin()
    {
        return _values.begin();
    }

    /**
     * @brief 获取首元素的const迭代器
     *
     * @param [in] null
     **/
    inline const_iterator begin() const
    {
        return _values.begin();
    }

    /**
     * @brief 获取尾元素的迭代器
     *
     * @param [in] null
     **/
    inline iterator end()
    {
        return _values.end();
    }

    /**
     * @brief 获取尾元素的const迭代器
     *
     * @param [in] null
     **/
    inline const_iterator end() const
    {
        return _values.end();
    }

    /**
     * @brief 在map中查找元素，如存在则返回其迭代器，否则返回end()
     *
     * @param [in] key : 指定的键值
     **/
    iterator find(const KeyType &key)
    {
        if (_size > 0)
        {
            _map_itr it = _map_key2entry.find(key);
            if (it == _map_key2entry.end())
            {
                return _values.end();
            }
            return it->second;
        }
        return _values.end();
    }

    /**
     * @brief find()的const版本
     *
     * @param [in] key : 指定的键值
     **/
    const_iterator find(const KeyType &key) const
    {
        if (_size > 0)
        {
            _map_citr it = _map_key2entry.find(key);
            if (it == _map_key2entry.end())
            {
                return _values.end();
            }
            return it->second;
        }
        return _values.end();
    }

    /**
     * @brief 移除位于pos处的entry
     *
     * @param [in] pos : 指定位置的迭代器
     **/
    void erase(iterator pos)
    {
        assert(pos != _values.end());
        assert(_size != 0);

        _values.erase(pos);
        _map_key2entry.erase(pos->first);
        --_size;
    }

    /**
     * @brief 移除指定键值的entry
     *
     * @param [in] key : 指定的键值
     **/
    void erase(const KeyType &key)
    {
        iterator it = find(key);
        if (it != _values.end())
        {
            erase(it);
        }
    }

    /**
     * @brief 清空所有entry
     *
     * @param [in] null
     **/
    void clear()
    {
        _values.clear();
        _map_key2entry.clear();
        _size = 0;
    }

    /**
     * @brief 返回entries的数量
     *
     * @param [in] null
     **/
    inline size_t size()
    {
        return _size;
    }

    /**
     * @brief 获取该map是否为空
     *
     * @param [in] null
     **/
    inline bool empty() const
    {
        return _values.empty();
    }

private:
    typedef std::map<KeyType, iterator, Compare> HashMap;

    typedef typename HashMap::iterator _map_itr;

    typedef typename HashMap::const_iterator _map_citr;

    /**
     * @brief entry的数量
     *
     **/
    size_t _size;

    /**
     * @brief 实际存放entry的双向链表
     *
     **/
    std::list<EntryType> _values;

    /**
     * @brief 保存key到entry的hashmap
     *
     **/
    HashMap _map_key2entry;
};

#endif // CLINKEDMAP_HPP
