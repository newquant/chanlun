/************************************************************************/
/* 
缠论版本信息
单例模式                                                                   
 */
/************************************************************************/
#ifndef __CHANLUNVERSION_H_INCLUDE
#define __CHANLUNVERSION_H_INCLUDE

/*
#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus
*/
class ChanlunVersion
{
private:
	ChanlunVersion(); // 构造函数
	~ChanlunVersion(); // 析构函数
	static ChanlunVersion* instance; // 唯一实例
	static const int iVersion[5]; // 版本信息

public:
	static ChanlunVersion* GetInstance(); // 获取实例 
	
	/*
	 *	版本信息
	 *  如 1.013 1主版本号 01 小版本号 
	 *  第三位小数 1 alpha(内测版) 2 beta(公测版) 3 standard标准版 4-5标准修正版 6 限时版 7 注册版 8 特别版 9 release最终版
	 */
	float GetVersion();
	
	/*
	 *	发布日期
	 */
	int GetDate();
	
	/*
	 *	作者
	 */
	char* GetAuthor();
	
	/*
	 *	Email
	 */
	char* GetEmail();
	
	/*
	 *	版权
	 */
	char* GetCopyRight();
};

/*	
#ifdef __cplusplus
}
#endif //__cplusplus
*/
#endif // __CHANLUNTOOLS_H_INCLUDE