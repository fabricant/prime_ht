#include <vector>
#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>
using namespace std;

bool isPrime(int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

class Timer
{
public:
    Timer()
    {
        start = chrono::high_resolution_clock::now();
    }
    ~Timer()
    {
        chrono::time_point<chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
        ;

        printf("Time %d\n", chrono::duration_cast<chrono::nanoseconds>(end - start));
    }

protected:
    chrono::time_point<chrono::high_resolution_clock> start;
};



int main()
{
    vector<int> primes(5000);
    {
        Timer t;
        for (int i = 0; i < 5000; ++i)
        {
            if (isPrime(i))
            {
                primes.push_back(i);

            }
        }
    }


    printf("done\n");
    return 0;
}