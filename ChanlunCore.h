/************************************************************************/
/* 
缠论核心模块实现
单例模式   
所有Chanlun接口中缠论核心函数在此实现                                                                 
 */
/************************************************************************/
#ifndef __CHANLUNCORE_H_INCLUDE
#define __CHANLUNCORE_H_INCLUDE

#include "FxjFunc.h"
#include <list>
	
using namespace std;

//定义基本数据
// 缠论K线结构 处理过包含关系的K线
typedef struct chankx
{
	int no;				// K线序号 从1开始是
	float rhigh;		// 高值
	float rlow;			// 低值
	float high;		//包含处理后的高值
	float low;		//包含处理后的低值
	int	flag;			//1顶 -1底 0 非顶底
	float fxqj;		// 分型区间 如果为顶底 记录区间边界
	int dir;            //K线方向 1上 -1下 2 上包含 -2 下包含
	int bi;				//笔 1上 -1下 2 上包含 -2 下包含
	int duan;			//段 1上 -1下 2 上包含 -2 下包含
} ckx;

// 笔 (特征序列)
typedef struct chanbi
{
	int no; // 序号
	int noh; // 高点K线编号
	int nol;  // 低点K线编号
	float high; // 高点
	float low; // 低点
	int dir; // 方向 方向 1上 -1下 2 上包含 -2 下包含
	int flag; // 1顶 -1底
	int qk; // 特征1 2 之间是否存在缺口 
} cbi;

// 段
typedef struct chanduan
{
	int no; // 序号
	int noh; // 高点K线编号
	int nol;  // 低点K线编号
	float high; // 高点
	float low; // 低点
	int flag; //  1顶 -1底
	int binum; // 包含几笔
} cduan;

// 走势中枢
typedef struct chanzhongshu
{
	int no; // 序号
	int duanno; // 段序号
	int flag; // 走势方向 1上 -1下
	int ksno; // zg所在K线NO (有zg必有zd)
	int jsno; // zd所在K线NO
	int znnum; // 包含zn数
	float zg; // ZG=min(g1、g2)
	float zd; // ZD=max(d1、d2)
	float gg; // GG=max(gn);
	float dd; // dd=min(dn);
	float zz; // 震荡中轴(监视器)
} czhongshu;
//定义基本数据 END

typedef list<ckx> KXDATA;
typedef list<cbi> BIDATA;
typedef list<cduan> DUANDATA;
typedef list<czhongshu> ZSDATA;

typedef list<ckx>::iterator CKXIT;
typedef list<cbi>::iterator BIIT;
typedef list<cduan>::iterator DUANIT;
typedef list<czhongshu>::iterator ZSIT;

typedef list<ckx>::const_iterator C_CKXIT;
typedef list<cbi>::const_iterator C_BIIT;
typedef list<cduan>::const_iterator C_DUANIT;
typedef list<czhongshu>::const_iterator C_ZSIT;

// 缠论核心实现
class ChanlunCore
{
private:
	ChanlunCore(); // 构造函数
	~ChanlunCore(); // 析构函数

	static ChanlunCore* instance;


	KXDATA kxData; // 根据缠论处理过的K线
	BIDATA xbData; // 向下笔 （向上笔开始的段的特征序列）
	BIDATA sbData; // 向上笔 （向下笔开始的段的特征序列）
	DUANDATA dData; // 段
	ZSDATA zsData; // 中枢
	
	float biQuekou;
	int firstDuanDir;

	void initBiQK(CALCINFO* pData); // 初始化缺口
	void initTZXL(); // 初始化特征分型
	void initDuanList(); //初始化段

	BIIT findTZG(int fromNo); // 查找特征序列的顶分型
	BIIT findTZD(int fromNo); // 查找特征序列的底分型
	
	void findFanTanZS(int duanno, int begin, int end, int high, int low); // 查找下跌段中枢
	void findHuiTiaoZS(int duanno, int begin, int end, int high, int low); // 查找上升段中枢

public:
	static ChanlunCore* GetInstance(); //获取 唯一实例
	
	void initKx(CALCINFO* pData); // 初始化缠论K线
	void initFX(); // 初始化分型
	void initBi();	// 初始化笔
	void initDuan(); // 初始化段
	void initZhongshu(); // 初始化中枢

	CKXIT getCKX(int num);

	// Getter
	KXDATA getCkxData();
	BIDATA getXbData();
	BIDATA getSbData(); 
	DUANDATA getDuanData();
	ZSDATA getZsData();

	// 自定义常量
	// 方向 1向上 -1向下
	static const int DIR_0;
	static const int DIR_UP;
	static const int DIR_DN;
	static const int DIR_SBH;
	static const int DIR_XBH;
	
	static const int QK_N; // 不存在缺口
	static const int QK_Y; // 存在缺口
};

#endif // __CHANLUNTOOLS_H_INCLUDE