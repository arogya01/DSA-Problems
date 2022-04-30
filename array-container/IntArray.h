#ifndef INTARRAY_H
#define INTARRAY_H

#include <cassert>

class IntArray
{
    int m_length{};
    int *m_data{};

public:
    IntArray() = default;

    IntArray(int length) : m_length{length}
    {
        assert(length >= 0);

        if (length > 0)
        {
            m_data = new int[length]{};
        }
    }

    ~IntArray()
    {
        delete[] m_data;
        // we don't need to set m_data to null or m_length to 0 here, since the obj will be destroyed after this function anyway.
    }

    void erase()
    {
        delete[] m_data;

        m_data = nullptr;
        m_length = 0;
    }

    int &operator[](int index)
    {
        assert(index >= 0 && index < m_length);

        return m_data[index];
    }

    int getLength() { return m_length; }

    // now, we want a function to resize the array at our disposal.

    void reallocate(int newLength)
    {
        erase();

        if (newLength <= 0)
            return;

        m_data = new int[newLength];
        m_length = newLength;
    }

    void resize(int newLength)
    {
        if (newLength == m_length)
            return;

        if (newLength <= 0)
        {
            erase();
            return;
        }

        int *newArr = new int[newLength];
        if (newLength > 0)
        {

            int elementsToCopy{(newLength > m_length ? m_length : newLength)};

            for (int i = 0; i < elementsToCopy; i++)
            {
                newArr[i] = m_data[i];
            }
        }

        m_length = newLength;
        m_data = newArr;
    }

    void insertBefore(int val, int index)
    {
        assert(index >= 0 && index <= m_length);

        int *newData{new int[m_length + 1]};

        for (int i = 0; i < index; i++)
        {
            newData[i] = m_data[i];
        }

        newData[index] = val;
        index++;
        for (; index < m_length + 1; index++)
        {
            newData[index] = m_data[index];
        }

        delete[] m_data;
        m_data = newData;
        ++m_length;
    }
};

#endif