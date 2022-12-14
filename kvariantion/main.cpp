#include <bits/stdc++.h>

using namespace std;

bool checkIsAP(int arr[], int n)
{
    if (n == 1)
        return true;

    // Sort array
    sort(arr, arr + n);

    // After sorting, difference between
    // consecutive elements must be same.
    int d = arr[1] - arr[0];
    for (int i = 2; i < n; i++)
        if (arr[i] - arr[i - 1] != d)
            return false;

    return true;
}

bool is_geometric(int arr[], int n)

{
    if (n == 1)
        return true;

    // Calculate ratio
    int ratio = arr[1] / (arr[0]);

    // Check the ratio of the remaining
    for (int i = 1; i < n; i++)
    {
        if ((arr[i] / (arr[i - 1])) != ratio)
        {
            return false;
        }
    }
    return true;
}

bool isPerfectSquare(int x)
{
    int s = sqrt(x);
    return (s * s == x);
}

bool isFibonacci(int n)
{
    // n is Fibonacci if one of 5*n*n + 4 or 5*n*n - 4 or
    // both is a perfect square
    return isPerfectSquare(5 * n * n + 4) || isPerfectSquare(5 * n * n - 4);
}

int Nth_of_AP(int a, int d, int N)
{
    // using formula to find the
    // Nth term t(n) = a(1) + (n-1)*d
    return (a + (N - 1) * d);
}

int calSumGP(float a, float r, int n)
{
    float sum = 0, temp = a;

    for (int i = 1; i < n; i++)
    {
        sum = sum + temp;
        temp = temp * r;
    }

    return temp;
}

int nextFibonacci(int n)
{
    double a = n * (1 + sqrt(5)) / 2.0;
    return round(a);
}

int GetNextSeriesElement(int input1, int input2[])
{

    if (checkIsAP(input2, input1))
    {
        int d = input2[1] - input2[0];
        return Nth_of_AP(input2[0], d, input1);
    }
    else if (is_geometric(input2, input1))
    {
        int ratio = input2[1] / (input2[0]);
        return calSumGP(input2[0], ratio, input1);
    }
    else
    {
        return nextFibonacci(input1);
    }
    return 0;
}

int main()
{
    int num1;
    int num2[]{};

    cin >> num1;
    int total = num1;
    int i = 0;
    while (--num1)
    {
        int temp;
        cin >> temp;

        cin >> num2[i];
        i++;
    }

    GetNextSeriesElement(total, num2);
}