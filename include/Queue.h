#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class Queue
{
public:
    Queue() :
        first(0),
        last(0),
        len(0)
    {}

    Queue& operator<<(T &value)
    {
        if (last)
        {
            last->append(value);
            last = last->next;
        }
        else
        {
            first = new Node(value);
            last = first;
        }
        len++;
        return *this;
    }

    T get()
    {
        if (first)
        {
            T val = first->value;
            if (first == last)
            {
                delete first;
                first = 0;
                last = 0;
            }
            else
            {
                Node* buf = first;
                first = buf->next;
                delete buf;
            }
            len--;
            return val;
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
        Node(T v) :
            next(0),
            value(v)
        {}

        Node* next = 0;
        T value;

        void append(T v)
        {
            if (next)
            {
                next->append(v);
            }
            else
            {
                next = new Node(v);
            }
        }
    };

    Node* first;
    Node* last;
    int len;
};

#endif // QUEUE_H
