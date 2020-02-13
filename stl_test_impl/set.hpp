//
// Created by Сергей Бородин on 13.02.2020.
//

#ifndef STL_TEST_SAMPLE_SET_HPP
#define STL_TEST_SAMPLE_SET_HPP

#include "functional.hpp"

namespace t_std
{

template<typename T,
        typename Cmp = less<T>,
        typename = std::enable_if_t<!std::is_pointer_v<std::decay_t<T>>>
>
class set
{
public:
    using value_type = std::decay_t<T>;

private:
    struct Node
    {
        friend class set;

        value_type Value;

        std::unique_ptr<Node> Left{};
        std::unique_ptr<Node> Right{};
        Node* Parent{};

        Node(value_type&& value)
            : Value(std::forward<value_type>(value))
        {
        }

        template<typename... Args>
        Node(Args&&... args)
            : Value(std::forward<Args>(args)...)
        {
        }

        ~Node(){}

        template<typename... Args>
        void emplace(Args&&... args)
        {
            value_type value(std::forward<Args>(args)...);

            Node* parent = this;

            while(true)
            {
                if (Cmp()(value, parent->Value))
                {
                    if (parent->Left)
                    {
                        parent = parent->Left.get();
                        continue;
                    }

                    parent->Left = std::make_unique<Node>(std::move(value));
                    parent->Left->Parent = parent;
                }
                else if (Cmp()(parent->Value, value))
                {
                    if (parent->Right)
                    {
                        parent = parent->Right.get();
                        continue;
                    }

                    parent->Right = std::make_unique<Node>(std::move(value));
                    parent->Right->Parent = parent;
                }

                return;
            }
        }
    };

    std::unique_ptr<Node> m_root;

public:
    set() noexcept = default;
    set(const set<value_type>&) = delete;

    set(set<value_type>&& other)
    {
        m_root = std::move(other.m_root);
    }

    auto& operator=(set<T, Cmp>&& from)
    {
        this->m_root = std::move(from.m_root);
        return *this;
    }

    class iterator
    {
        Node* m_node{};

        friend class set;

    public:
        value_type const & operator*()
        {
            return m_node->Value;
        }

        bool operator!=(const iterator& it)
        {
            return m_node != it.m_node;
        }

        iterator& operator++()
        {
            if (m_node->Right)
            {
                m_node = m_node->Right.get();

                while (m_node->Left) { m_node = m_node->Left.get(); }

                return *this;
            }

            while (m_node->Parent)
            {
                if (m_node->Parent->Right.get() == m_node)
                {
                    m_node = m_node->Parent;
                    continue;
                }

                m_node = m_node->Parent;
                return *this;
            }

            if (!m_node->Parent)
            {
                m_node = nullptr;
            }

            return *this;
        }
    };

    iterator begin()
    {
        iterator it{};
        if (!m_root)
        {
            return it;
        }

        it.m_node = m_root.get();

        while (it.m_node->Left) { it.m_node = it.m_node->Left.get(); }

        return it;
    }

    iterator end()
    {
        return {};
    }

    template<typename... Args>
    void emplace(Args&&... args)
    {
        if (!m_root)
        {
            m_root = std::make_unique<Node>(std::forward<Args>(args)...);
        }
        else
        {
            m_root->emplace(std::forward<Args>(args)...);
        }
    }
};

}

#endif //STL_TEST_SAMPLE_SET_HPP
