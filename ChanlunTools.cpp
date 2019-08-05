#include "stdafx.h"
#include "ChanlunTools.h"

//初始化静态成员 
ChanlunTools* ChanlunTools::instance = NULL;

const int ChanlunTools::cjunx[8] = {5, 13, 21, 34, 55, 89, 144, 233};

// 构造函数
ChanlunTools::ChanlunTools()
{
//nothing
}

ChanlunTools::~ChanlunTools()
{
	if(NULL != instance)
	{
		delete instance;
		instance = NULL;
	}
}

// 静态实例
ChanlunTools* ChanlunTools::GetInstance()
{
	if(NULL == instance)
	{
		instance = new ChanlunTools();
	}
	return instance;
}

float ChanlunTools::ma_close(CALCINFO* pData, int num, int zq)
{
	float ret = 0;
	for(int j=0;j<zq;j++)					//累加
		ret += pData->m_pData[num-j].m_fClose;
	
	return ret/zq;
}

int ChanlunTools::jxzt(CALCINFO* pData, int num)
{
	int ss = 1;
	float ma5 = ma_close(pData, num, 5);
	float ma13 = ma_close(pData, num, 13);
	float ma21 = ma_close(pData, num, 21);
	float ma34 = ma_close(pData, num, 34);
	float ma55 = ma_close(pData, num, 55);
	float ma89 = ma_close(pData, num, 89);
	float ma144 = ma_close(pData, num, 144);
	float ma233 = ma_close(pData, num, 233);

	float c = pData->m_pData[num].m_fClose;
	
	if(c>ma5) ss++;
	if(c>ma13) ss++;
	if(c>ma21) ss++;
	if(c>ma34) ss++;
	if(c>ma55) ss++;
	if(c>ma89) ss++;
	if(c>ma144) ss++;
	if(c>ma233) ss++;
	
	return ss;
}

int ChanlunTools::jxyl(CALCINFO* pData, int num)
{
	float ma5 = ma_close(pData, num, 5);
	float ma13 = ma_close(pData, num, 13);
	float ma21 = ma_close(pData, num, 21);
	float ma34 = ma_close(pData, num, 34);
	float ma55 = ma_close(pData, num, 55);
	float ma89 = ma_close(pData, num, 89);
	float ma144 = ma_close(pData, num, 144);
	float ma233 = ma_close(pData, num, 233);

	float c = pData->m_pData[num].m_fClose;
	
	float cz1 = c - ma5;
	float cz2 = c - ma13;
	float cz3 = c - ma21;
	float cz4 = c - ma34;
	float cz5 = c - ma55;
	float cz6 = c - ma89;
	float cz7 = c - ma144;
	float cz8 = c - ma233;
	float czs[] = {cz1, cz2, cz3, cz4, cz5, cz6, cz7, cz8};
	
	int flag = 1;
	float ylw = czs[0]; 
	if (ylw>0) {
		ylw = -99999;
		flag = 9;
	}
	for(int i=1; i<8; i++)
	{
		if(czs[i]<0 && czs[i] > ylw) {
			ylw = czs[i];
			flag = i+1;
		}
	}
	
	return flag;
}

int ChanlunTools::jxzc(CALCINFO* pData, int num)
{
	float ma5 = ma_close(pData, num, 5);
	float ma13 = ma_close(pData, num, 13);
	float ma21 = ma_close(pData, num, 21);
	float ma34 = ma_close(pData, num, 34);
	float ma55 = ma_close(pData, num, 55);
	float ma89 = ma_close(pData, num, 89);
	float ma144 = ma_close(pData, num, 144);
	float ma233 = ma_close(pData, num, 233);
	
	float c = pData->m_pData[num].m_fClose;
	
	float cz1 = c - ma5;
	float cz2 = c - ma13;
	float cz3 = c - ma21;
	float cz4 = c - ma34;
	float cz5 = c - ma55;
	float cz6 = c - ma89;
	float cz7 = c - ma144;
	float cz8 = c - ma233;
	float czs[] = {cz1, cz2, cz3, cz4, cz5, cz6, cz7, cz8};
	
	int flag = 1;
	float zcw = czs[0]; 
	if (zcw<0) 
	{
		zcw = 99999;
		flag = 0;
	}
	
	for(int i=1; i<8; i++)
	{
		if(czs[i]>0 && czs[i] < zcw) 
		{
			zcw = czs[i];
			flag = i+1;
		}
	}
	
	return flag;
}

int ChanlunTools::jxyl2(CALCINFO* pData, int num)
{
	int ret = 0;
	int i = jxyl(pData, num);
	if(9 != i)
	{
		ret = cjunx[i-1];
	}

	return ret;
}

int ChanlunTools::jxzc2(CALCINFO* pData, int num)
{
	int ret = 0;
	int i = jxzc(pData, num);
	if(0 != i)
	{
		ret = cjunx[i-1];
	}
	
	return ret;
}

