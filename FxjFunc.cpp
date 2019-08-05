// FxjFunc.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "FxjFunc.h"
#include "ChanlunCore.h"
#include "ChanlunTools.h"
#include "ChanlunVersion.h"


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{ 
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

//计算收盘价的均价,一个常数参数,表示计算周期
//调用方法:
//	MYMACLOSE(5)

__declspec(dllexport) int WINAPI MYMACLOSE(CALCINFO* pData)
{
	float f,fTotal;
	int nPeriod,i,j;
	if(pData->m_pfParam1 &&					//参数1有效
		pData->m_nParam1Start<0 &&			//参数1为常数
		pData->m_pfParam2==NULL)			//仅有一个参数
	{
		f = *pData->m_pfParam1;
		nPeriod = (int)f;					//参数1
		if(nPeriod>0)
		{
			for(i=nPeriod-1;i<pData->m_nNumData;i++)	//计算nPeriod周期的均线,数据从nPeriod-1开始有效
			{
				fTotal = 0.0f;
				for(j=0;j<nPeriod;j++)					//累加
					fTotal += pData->m_pData[i-j].m_fClose;
				pData->m_pResultBuf[i] = fTotal/nPeriod;						//平均
			}
			return nPeriod-1;
		}
	}
	return -1;
}

__declspec(dllexport) int WINAPI MYMACLOSE_CALC_PREV(CALCINFO* pData)
{
	if(pData->m_pfParam1 && pData->m_nParam1Start<0)
	{
		float f = *pData->m_pfParam1;
		return ((int)f) - 1;
	}
	return 0;
}

//计算均价,2个参数,参数1为待求均线的数据,参数2表示计算周期
//调用方法:
//	MYMAVAR(CLOSE-OPEN,5)

__declspec(dllexport) int WINAPI MYMAVAR(CALCINFO* pData)
{
	float f,fTotal;
	const float* pValue;
	int nPeriod,nFirst,i,j;
	if(pData->m_pfParam1 && pData->m_pfParam2 && 	//参数1,2有效
		pData->m_nParam1Start>=0 &&					//参数1为序列数
		pData->m_pfParam3==NULL)					//有2个参数
	{
		pValue = pData->m_pfParam1;					//参数1
		nFirst = pData->m_nParam1Start;				//有效值
		f = *pData->m_pfParam2;
		nPeriod = (int)f;							//参数2
		if(nFirst>=0 && nPeriod>0)
		{
			for(i=nFirst+nPeriod-1;i<pData->m_nNumData;i++)
			{
				fTotal = 0.0f;
				for(j=0;j<nPeriod;j++)					//累加
					fTotal += pData->m_pData[i-j].m_fClose;
				pData->m_pResultBuf[i] = fTotal/nPeriod;						//平均
			}
			return nFirst+nPeriod-1;
		}
	}
	return -1;
}

__declspec(dllexport) int WINAPI MYMAVAR_CALC_PREV(CALCINFO* pData)
{
	if(pData->m_pfParam1 && pData->m_nParam1Start<0)
	{
		float f = *pData->m_pfParam1;
		return ((int)f) - 1;
	}
	return 0;
}

///  added by pp
__declspec(dllexport) int WINAPI TT(CALCINFO* pData)
{
	if(pData->m_nNumData>0)
	{

		KXDATA data = ChanlunCore::GetInstance()->getCkxData();	
		int num = pData->m_nNumData - 1;
		pData->m_pResultBuf[num] = data.size();
	}
	return -1;
}

__declspec(dllexport) int WINAPI VERSION(CALCINFO* pData)
{
	if(pData->m_nNumData>0)
	{
		int i = pData->m_nNumData-1;
		pData->m_pResultBuf[i] = ChanlunVersion::GetInstance()->GetVersion();
		return i;
	}
	return -1;
}

__declspec(dllexport) int WINAPI DATE(CALCINFO* pData)
{
	if(pData->m_nNumData>0)
	{

		int i = pData->m_nNumData-1;
		pData->m_pResultBuf[i] = ChanlunVersion::GetInstance()->GetDate();
		return i;
	}
	return -1;
}

__declspec(dllexport) int WINAPI JXZT(CALCINFO* pData) 
{
	int i, ss, nPeriod;
	nPeriod = 233; // 从233线算起
	if (pData->m_nNumData>=nPeriod)
	{
		for(i=nPeriod-1; i<pData->m_nNumData; i++)
		{
			ss = ChanlunTools::GetInstance()->jxzt(pData, i);
			pData->m_pResultBuf[i] = (float) ss;
		}
		return nPeriod-1;
	}
	return -1;
}

__declspec(dllexport) int WINAPI JXYL(CALCINFO* pData)
{
	int i, ss, nPeriod;
	nPeriod = 233; // 从233线算起
	if (pData->m_nNumData>=nPeriod)
	{
		for(i=nPeriod-1; i<pData->m_nNumData; i++)
		{
			ss = ChanlunTools::GetInstance()->jxyl(pData, i);
			pData->m_pResultBuf[i] = (float) ss;
		}
		return nPeriod-1;
	}

	return -1;
}

__declspec(dllexport) int WINAPI JXZC(CALCINFO* pData)
{
	int i, ss, nPeriod;
	nPeriod = 233; // 从233线算起
	if (pData->m_nNumData>=nPeriod)
	{
		for(i=nPeriod-1; i<pData->m_nNumData; i++)
		{
			ss = ChanlunTools::GetInstance()->jxzc(pData, i);
			pData->m_pResultBuf[i] = (float) ss;
		}
		return nPeriod-1;
	}
	
	return -1;
}

__declspec(dllexport) int WINAPI JXYL2(CALCINFO* pData)
{
	int i, ss, nPeriod;
	nPeriod = 233; // 从233线算起
	if (pData->m_nNumData>=nPeriod)
	{
		for(i=nPeriod-1; i<pData->m_nNumData; i++)
		{
			ss = ChanlunTools::GetInstance()->jxyl2(pData, i);
			pData->m_pResultBuf[i] = (float) ss;
		}
		return nPeriod-1;
	}
	
	return -1;
}

__declspec(dllexport) int WINAPI JXZC2(CALCINFO* pData)
{
	int i, ss, nPeriod;
	nPeriod = 233; // 从233线算起
	if (pData->m_nNumData>=nPeriod)
	{
		for(i=nPeriod-1; i<pData->m_nNumData; i++)
		{
			ss = ChanlunTools::GetInstance()->jxzc2(pData, i);
			pData->m_pResultBuf[i] = (float) ss;
		}
		return nPeriod-1;
	}
	
	return -1;
}

__declspec(dllexport) int WINAPI kxian(CALCINFO* pData)
{
	if(pData->m_nNumData>0)
	{		
		ChanlunCore::GetInstance()->initKx(pData);
		ChanlunCore::GetInstance()->initFX();

		// 返回结果集
		int i=0;
		KXDATA data = ChanlunCore::GetInstance()->getCkxData();
		for(C_CKXIT it = data.begin(); it != data.end(); it++)
		{
			pData->m_pResultBuf[i] = it->flag;
			i++;
		}
		
		return 0;	
	}
	return -1;
}

__declspec(dllexport) int WINAPI kxg(CALCINFO* pData)
{

	int i=0;
	KXDATA data = ChanlunCore::GetInstance()->getCkxData();
	for(C_CKXIT it = data.begin(); it != data.end(); it++)
	{
		pData->m_pResultBuf[i] = it->high;
		i++;
	}
	
	return 0;
}

__declspec(dllexport) int WINAPI kxd(CALCINFO* pData)
{
	int i=0;
	KXDATA data = ChanlunCore::GetInstance()->getCkxData();
	for(C_CKXIT it = data.begin(); it != data.end(); it++)
	{
		pData->m_pResultBuf[i] = it->low;
		i++;
	}
	
	return 0;
}

__declspec(dllexport) int WINAPI kxfx(CALCINFO* pData)
{
	int i=0;
	KXDATA data = ChanlunCore::GetInstance()->getCkxData();
	for(C_CKXIT it = data.begin(); it != data.end(); it++)
	{
		pData->m_pResultBuf[i] = it->dir;
		i++;
	}
	
	return 0;
}

__declspec(dllexport) int WINAPI bi(CALCINFO* pData)
{
	if (pData->m_nNumData > 0) 
	{
		ChanlunCore::GetInstance()->initBi();
		
		int i=0;
		KXDATA data = ChanlunCore::GetInstance()->getCkxData();
		for(C_CKXIT it = data.begin(); it != data.end(); it++)
		{
			pData->m_pResultBuf[i] = it->bi;
			i++;
		}
		
		return 0;
	}
	
	return -1;
}

__declspec(dllexport) int WINAPI bilast(CALCINFO* pData)
{
	if (pData->m_nNumData > 0) 
	{		
		int i = 0, binum = 0, zq = 0, lastN = 0;
		
		KXDATA data = ChanlunCore::GetInstance()->getCkxData();
		for(C_CKXIT it = data.begin(); it != data.end(); it++)
		{
			if(0 == lastN)
			{
				pData->m_pResultBuf[i] = -1;	
			}
			else
			{
				zq = it->no - lastN;
				pData->m_pResultBuf[i] = zq;	
			}
					
			if (ChanlunCore::DIR_UP == it->bi || ChanlunCore::DIR_DN == it->bi)
			{
				lastN = it->no;
			}
			i++;
		}
		
		return 0;
	}
	
	return -1;
}

__declspec(dllexport) int WINAPI bigglast(CALCINFO* pData)
{
	if (pData->m_nNumData > 0) 
	{		
		int i = 0, binum = 0, zq = 0, lastN = 0;
		
		KXDATA data = ChanlunCore::GetInstance()->getCkxData();
		for(C_CKXIT it = data.begin(); it != data.end(); it++)
		{
			if(0 == lastN)
			{
				pData->m_pResultBuf[i] = -1;	
			}
			else
			{
				zq = it->no - lastN;
				pData->m_pResultBuf[i] = zq;	
			}			

			if (ChanlunCore::DIR_UP == it->bi)
			{
				lastN = it->no;
			}
			i++;
		}
		
		return 0;
	}
	
	return -1;
}

__declspec(dllexport) int WINAPI biddlast(CALCINFO* pData)
{
	if (pData->m_nNumData > 0) 
	{		
		int i = 0, binum = 0, zq = 0, lastN = 0;
		
		KXDATA data = ChanlunCore::GetInstance()->getCkxData();
		for(C_CKXIT it = data.begin(); it != data.end(); it++)
		{
			if(0 == lastN)
			{
				pData->m_pResultBuf[i] = -1;	
			}
			else
			{
				zq = it->no - lastN;
				pData->m_pResultBuf[i] = zq;	
			}
			
			if (ChanlunCore::DIR_DN == it->bi)
			{
				lastN = it->no;
			}
			i++;
		}
		
		return 0;
	}
	
	return -1;
}



__declspec(dllexport) int WINAPI duan(CALCINFO* pData)
{
	if (pData->m_nNumData > 0) 
	{
		ChanlunCore::GetInstance()->initDuan();
		
		int i=0;
		KXDATA data = ChanlunCore::GetInstance()->getCkxData();
		for(C_CKXIT it = data.begin(); it != data.end(); it++)
		{
			pData->m_pResultBuf[i] = it->duan;
			i++;
		}
		
		return 0;
	}
	
	return -1;
}

__declspec(dllexport) int WINAPI duanlast(CALCINFO* pData)
{
	if (pData->m_nNumData > 0) 
	{		
		int i = 0, binum = 0, zq = 0, lastN = 0;
		
		KXDATA data = ChanlunCore::GetInstance()->getCkxData();
		for(C_CKXIT it = data.begin(); it != data.end(); it++)
		{
			if(0 == lastN)
			{
				pData->m_pResultBuf[i] = -1;	
			}
			else
			{
				zq = it->no - lastN;
				pData->m_pResultBuf[i] = zq;	
			}
			
			if (ChanlunCore::DIR_UP == it->duan || ChanlunCore::DIR_DN == it->duan)
			{
				lastN = it->no;
			}
			i++;
		}
		
		return 0;
	}
	
	return -1;
}

__declspec(dllexport) int WINAPI duangglast(CALCINFO* pData)
{
	if (pData->m_nNumData > 0) 
	{		
		int i = 0, binum = 0, zq = 0, lastN = 0;
		
		KXDATA data = ChanlunCore::GetInstance()->getCkxData();
		for(C_CKXIT it = data.begin(); it != data.end(); it++)
		{
			if(0 == lastN)
			{
				pData->m_pResultBuf[i] = -1;	
			}
			else
			{
				zq = it->no - lastN;
				pData->m_pResultBuf[i] = zq;	
			}
			
			if (ChanlunCore::DIR_UP == it->duan)
			{
				lastN = it->no;
			}
			i++;
		}
		
		return 0;
	}
	
	return -1;
}

__declspec(dllexport) int WINAPI duanddlast(CALCINFO* pData)
{
	if (pData->m_nNumData > 0) 
	{		
		int i = 0, binum = 0, zq = 0, lastN = 0;
		
		KXDATA data = ChanlunCore::GetInstance()->getCkxData();
		for(C_CKXIT it = data.begin(); it != data.end(); it++)
		{
			if(0 == lastN)
			{
				pData->m_pResultBuf[i] = -1;	
			}
			else
			{
				zq = it->no - lastN;
				pData->m_pResultBuf[i] = zq;	
			}
			
			if (ChanlunCore::DIR_DN == it->duan)
			{
				lastN = it->no;
			}
			i++;
		}
		
		return 0;
	}
	
	return -1;
}

__declspec(dllexport) int WINAPI zs(CALCINFO* pData)
{
	if (pData->m_nNumData > 21) 
	{		
		ChanlunCore::GetInstance()->initZhongshu();
	}
	
	return -1;
}

__declspec(dllexport) int WINAPI zszg(CALCINFO* pData)
{
	int i;
	for(i=0; i<pData->m_nNumData;i++)
	{
		pData->m_pResultBuf[i] = 0;
	}

	ZSDATA data = ChanlunCore::GetInstance()->getZsData();
	if(data.size() > 0)
	{
		C_ZSIT zsit;
		int b =0, e=0;
		for(zsit = data.begin(); zsit != data.end(); zsit++)
		{
			b = zsit->ksno - 1;
			e = zsit->jsno - 1;

			for (i = b; i<=e; i++)
			{
				pData->m_pResultBuf[i] = zsit->zg;
			}
			
		}
	}

	return 0;
}

__declspec(dllexport) int WINAPI zszd(CALCINFO* pData)
{
	int i;
	for(i=0; i<pData->m_nNumData;i++)
	{
		pData->m_pResultBuf[i] = 0;
	}

	ZSDATA data = ChanlunCore::GetInstance()->getZsData();
	if(data.size() > 0)
	{
		C_ZSIT zsit;
		int b =0, e=0;
		for(zsit = data.begin(); zsit != data.end(); zsit++)
		{
			b = zsit->ksno - 1;
			e = zsit->jsno - 1;
			
			for (i = b; i<=e; i++)
			{
				pData->m_pResultBuf[i] = zsit->zd;
			}
			
		}
	}
	
	return 0;
}

__declspec(dllexport) int WINAPI zsgg(CALCINFO* pData)
{
	int i;
	for(i=0; i<pData->m_nNumData;i++)
	{
		pData->m_pResultBuf[i] = 0;
	}
	
	ZSDATA data = ChanlunCore::GetInstance()->getZsData();
	if(data.size() > 0)
	{
		C_ZSIT zsit;
		int b =0, e=0;
		for(zsit = data.begin(); zsit != data.end(); zsit++)
		{
			b = zsit->ksno - 1;
			e = zsit->jsno - 1;
			
			for (i = b; i<=e; i++)
			{
				pData->m_pResultBuf[i] = zsit->gg;
			}
			
		}
	}
	
	return 0;
}

__declspec(dllexport) int WINAPI zszz(CALCINFO* pData)
{
	int i;
	for(i=0; i<pData->m_nNumData;i++)
	{
		pData->m_pResultBuf[i] = 0;
	}
	
	ZSDATA data = ChanlunCore::GetInstance()->getZsData();
	if(data.size() > 0)
	{
		C_ZSIT zsit;
		int b =0, e=0;
		for(zsit = data.begin(); zsit != data.end(); zsit++)
		{
			b = zsit->ksno - 1;
			e = zsit->jsno - 1;
			
			for (i = b; i<=e; i++)
			{
				pData->m_pResultBuf[i] = zsit->zz;
			}
			
		}
	}
	
	return 0;
}

__declspec(dllexport) int WINAPI zsdd(CALCINFO* pData)
{
	int i;
	for(i=0; i<pData->m_nNumData;i++)
	{
		pData->m_pResultBuf[i] = 0;
	}
	
	ZSDATA data = ChanlunCore::GetInstance()->getZsData();
	if(data.size() > 0)
	{
		C_ZSIT zsit;
		int b =0, e=0;
		for(zsit = data.begin(); zsit != data.end(); zsit++)
		{
			b = zsit->ksno - 1;
			e = zsit->jsno - 1;
			
			for (i = b; i<=e; i++)
			{
				pData->m_pResultBuf[i] = zsit->dd;
			}
			
		}
	}
	
	return 0;
}

__declspec(dllexport) int WINAPI zskslast(CALCINFO* pData)
{
	if (pData->m_nNumData > 0) 
	{		
		for(int i = 0; i < pData->m_nNumData; i++)
		{
			pData->m_pResultBuf[i] = -1;
		}
		
		int num = 0;
		ZSDATA data = ChanlunCore::GetInstance()->getZsData();
		for(ZSIT it = data.begin(); it != data.end(); it++)
		{
			num = it->ksno - 1;
			pData->m_pResultBuf[num] = 1;
		}
		
		return 0;
	}
	
	return -1;
}

__declspec(dllexport) int WINAPI zsjslast(CALCINFO* pData)
{
	if (pData->m_nNumData > 0) 
	{		
		for(int i = 0; i < pData->m_nNumData; i++)
		{
			pData->m_pResultBuf[i] = -1;
		}
		
		int num = 0;
		ZSDATA data = ChanlunCore::GetInstance()->getZsData();
		for(ZSIT it = data.begin(); it != data.end(); it++)
		{
			num = it->jsno - 1;
			pData->m_pResultBuf[num] = 1;
		}
		
		return 0;
	}
	
	return -1;
}