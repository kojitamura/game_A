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
		m_start = timeGetTime();        // �v���J�n���Ԃ�ۑ�
	}
	double  elapsed()    // ���X�^�[�g����̕b����Ԃ�
	{
		DWORD end = timeGetTime();
		return (double)(end - m_start) / 1000;
	}
private:
	DWORD    m_start;    //  �v���J�n����
};


int main()
{
	std::cout << "timeGetTime():\n";
	for (int i = 0; i < 10; ++i)
	{
		std::vector<int> v;         // int �^���I�z��
		DWORD start = timeGetTime();       // �X�^�[�g����
		const int N = 1000 * 1000;    //  100����
		for (int i = 0; i < N; ++i)
		{
			v.push_back(i);              // ������ i ��ǉ�
		}
		DWORD end = timeGetTime();    // �I������
		std::cout << "duration = " << (double)(end - start) / 1000 << "sec.\n";
	}
	getchar();
	return 0;
}
