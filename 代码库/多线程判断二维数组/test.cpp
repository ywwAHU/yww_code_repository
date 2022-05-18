#include <thread>
#include <vector>
#include <iostream>

using namespace std;

void thread_1(vector<vector<int>> &a, int size, int j)
{

    for (int i = 0; i < size; i++)
    {
        a[i][j] = (i + 1) * (j + 1);
    }
}

void thread_1()
{

    for (int i = 0; i < size; i++)
    {
        a[i][j] = (i + 1) * (j + 1);
    }
}

int main(int argc, char **argv)
{
    vector<vector<int>> a;
    vector<vector<int>> b;
    for (int i = 0; i < 750; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            a[i][j] = (i + 1) * (j + 1);
        }
    }

    std::thread first(thread_1(b, 750, 0));
    std::thread second(thread_1(b, 750, 1));

    first.join();
    second.join();

    for (int i = 0; i < 750; i++)
        cout << b[i][0] << ":" << a[i][0] << endl;

    return 0;
}
// 编译：g++ main.cpp -std=c++11 -o mythread -lpthread
// 报错是因为没有初始化


// 