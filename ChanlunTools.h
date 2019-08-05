/************************************************************************/
/* 
缠论可单独调用的函数在此实现
单例模式   
所有Chanlun接口中可单独调用的函数在此实现                                                                 
 */
/************************************************************************/
#ifndef __CHANLUNTOOLS_H_INCLUDE
#define __CHANLUNTOOLS_H_INCLUDE
/*
#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus
*/
#include "FxjFunc.h"

class ChanlunTools
{
private:
	ChanlunTools(); // 构造函数
	virtual ~ChanlunTools(); // 析构函数
	static ChanlunTools* instance; // 单例实例
	
	static const int cjunx[8]; // 缠论均线1-8类

public:
	static ChanlunTools* GetInstance(); // 获取单例实例
	
	/*
	 *	收盘价均线 
	 */
	float ma_close(CALCINFO* pData, int num, int zq); 

	/*
	 *	均线评分 1-9类 1为全在均线之下 9为全在均线之上
	 */
	int jxzt(CALCINFO* pData, int num); 

	/*
	 *	均线压力 9为无压制均线 多头排列 返回1-8类均线
	 */
	int jxyl(CALCINFO* pData, int num);

	/*
	 *	均线支撑 0为无任何支撑 空头排列 返回1-8类均线
	 */
	int jxzc(CALCINFO* pData, int num); 

	/*
	 *	均线压力 0为无压制均线 多头排列 返回5 13 21 34 55 89 144 233
	 */
	int jxyl2(CALCINFO* pData, int num);

	/*
	 *	均线支撑 0为无任何支撑 空头排列  返回5 13 21 34 55 89 144 233
	 */
	int jxzc2(CALCINFO* pData, int num); 

};

/*
#ifdef __cplusplus
}
#endif //__cplusplus
*/
#endif // __CHANLUNTOOLS_H_INCLUDE
