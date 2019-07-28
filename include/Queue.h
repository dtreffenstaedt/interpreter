#ifndef QUEUE_H
#define QUEUE_H

#include <mutex>
#include <memory>

template <typename T>
class Queue
{
public:
    Queue() :
        first(nullptr),
        last(nullptr),
        len(0)
    {}

    Queue& operator<<(T &value)
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        if (last)
        {
            last->append(value);
            last = last->next;
        }
        else
        {
            first = std::make_shared<Node>(value);
            last = first;
        }
        len++;
        return *this;
    }

    T get()
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        if (first)
        {
            T val = first->value;
            if (first == last)
            {
                first = nullptr;
                last = nullptr;
            }
            else
            {
                std::shared_ptr<Node> buf = first;
                first = buf->next;
            }
            len--;
            return val;
        }
        else
        {
            return T();
        }
    }

    T peek()
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        if (first)
        {
            return first->value;
        }
        else
        {
            return T();
        }
    }

    bool empty()
    {
        return len == 0;
    }

    int length()
    {
        return len;
    }

private:
    class Node
    {
    public:
        explicit Node(T v) :
            next(nullptr),
            value(v)
        {}

        std::shared_ptr<Node> next = nullptr;
        T value;

        void append(T v)
        {
            if (next)
            {
                next->append(v);
            }
            else
            {
                next = std::make_shared<Node>(v);
            }
        }
    };

    std::shared_ptr<Node> first;
    std::shared_ptr<Node> last;
    int len;
    std::mutex m_mutex;
};

#endif // QUEUE_H
