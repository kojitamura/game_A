#pragma once
#include <iostream>
#include <vector>
#include <windows.h>
#pragma comment(lib, "winmm.lib")

class Timer
{
public:
	Timer() { restart(); }
public:
	void  restart()
	{
		m_start = timeGetTime();        // 計測開始時間を保存
	}
	double  elapsed()    // リスタートからの秒数を返す
	{
		DWORD end = timeGetTime();
		return (double)(end - m_start) / 1000;
	}
private:
	DWORD    m_start;    //  計測開始時間
};


int main()
{
	std::cout << "timeGetTime():\n";
	for (int i = 0; i < 10; ++i)
	{
		std::vector<int> v;         // int 型動的配列
		DWORD start = timeGetTime();       // スタート時間
		const int N = 1000 * 1000;    //  100万回
		for (int i = 0; i < N; ++i)
		{
			v.push_back(i);              // 末尾に i を追加
		}
		DWORD end = timeGetTime();    // 終了時間
		std::cout << "duration = " << (double)(end - start) / 1000 << "sec.\n";
	}
	getchar();
	return 0;
}
