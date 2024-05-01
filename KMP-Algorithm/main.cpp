#include <iostream>
#include <vector>
#include <string>

std::vector<int> computeLPSArray(const std::string &pattern)
{
    int m = pattern.length();
    std::vector<int> lps(m);
    int len = 0;
    lps[0] = 0;

    int i = 1;
    while (i < m)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
                len = lps[len - 1];
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

std::vector<size_t> findAllOccurrences(const std::string &text, const std::string &pattern)
{
    std::vector<size_t> indices;
    int n = text.length();
    int m = pattern.length();
    std::vector<int> lps = computeLPSArray(pattern);

    int i = 0, j = 0;
    while (i < n)
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            indices.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < n && text[i] != pattern[j])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    return indices;
}

int main()
{
    std::string text = "Hello, World! Hello, Universe!";
    std::string pattern = "Hello";

    std::vector<size_t> indices = findAllOccurrences(text, pattern);

    if (indices.empty())
    {
        std::cout << "Substring not found" << std::endl;
    }
    else
    {
        std::cout << "Substring found at positions: ";
        for (size_t index : indices)
        {
            std::cout << index << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}