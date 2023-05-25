#include <map>
template <typename K, typename V>
class interval_map

{
private:
    V default_value;
    std::map<K, V> m_map;

public:
    // constructor associates whole range of K with val
    interval_map(V const &val)
        : default_value(val)
    {
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    void assign(K const &keyBegin, K const &keyEnd, V const &val)
    {
        // note: we used insert everywhere instead of assignment
        // since it is O(1) when provided with an iterator

        if (!(keyBegin < keyEnd)) // checks if interval is empty
            return;

        auto lower_it = m_map.upper_bound(keyBegin);

        // initialize to avoid assuming that V is default constructible
        V cur_value = default_value;
        // compute cur_value = interval[keyBegin]
        if (lower_it == m_map.begin())
        {
            // cur_value is already default_value
            if (!(val == cur_value))
                // use insert as we are guaranteed that the key is not in the map
                m_map.insert(lower_it, {keyBegin, val});
        }
        else
        {
            auto prev_it = prev(lower_it);
            cur_value = prev_it->second;
            if (!(val == cur_value))
            {
                if (!(prev_it->first < keyBegin))
                {
                    // if new key is same as previous key, we can change it in place
                    // there are 3 cases to consider:
                    if (prev_it == m_map.begin() && val == default_value || prev_it != m_map.begin() && val == prev(prev_it)->second)
                        // 1. the new value would be default_value, so we erase the iterator
                        // 2. the new value would be the same as the value before it
                        // in both cases, we erase
                        // instead of erasing directly, we set lower_it
                        // we lose one iteration in the next loop but we call erase just once
                        lower_it = prev_it;
                    else
                        // 3. we can insert the new value
                        prev_it->second = val;
                }
                else if (!(prev_it->second == val))
                    // else we insert a new key just before lower_it
                    m_map.insert(lower_it, {keyBegin, val});
            }
        }

        // clean the map and find the position of keyEnd
        // amortized O(1)
        auto it = lower_it;
        while (it != m_map.end() && !(keyEnd < it->first))
            cur_value = (it++)->second;
        m_map.erase(lower_it, it);

        // insert keyEnd only if needed
        // note: insert_or_assign is useless here by the loop condition
        if (!(cur_value == val))
            m_map.insert(it, {keyEnd, cur_value});
    }

    // look-up of the value associated with key
    V const &
    operator[](K const &key) const
    {
        auto it = m_map.upper_bound(key);
        if (it == m_map.begin())
        {
            return default_value;
        }
        else
        {
            return (--it)->second;
        }
    }

    std::map<K, V> const &getMap() const
    {
        return m_map;
    }
    void debug() const
    {
        std::cerr << "default_value: " << default_value << std::endl;
        std::cerr << "m_map: ";
        if (m_map.empty())
        {
            std::cerr << "empty" << std::endl;
            return;
        }
        for (auto it = m_map.begin(); it != prev(m_map.end()); ++it)
        {
            std::cerr << it->first << ": " << it->second << ", ";
        }
        std::cerr << prev(m_map.end())->first << ": " << prev(m_map.end())->second << std::endl;
    }
};
