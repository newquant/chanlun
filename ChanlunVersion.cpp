#include "stdafx.h"
#include "ChanlunVersion.h"

// 静态变量
ChanlunVersion* ChanlunVersion::instance = NULL;

//版本信息
//{主版本号，次版本号（最大99），发行版本（最大9），内部版本号（不公布（最大99）），发行日期}
//1, 02, 1, 1, 20101228
//1, 02, 1, 2, 20110101
//2, 01, 1, 1, 20110102
const int ChanlunVersion::iVersion[5] = {2, 01, 1, 1, 20110101};

ChanlunVersion::ChanlunVersion()
{
	// nothing
}

ChanlunVersion::~ChanlunVersion()
{
	if(NULL != instance)
	{
		delete instance;
		instance = NULL;
	}
}

// 获取唯一实例
ChanlunVersion* ChanlunVersion::GetInstance()
{
	if(NULL == instance)
	{
		instance = new ChanlunVersion();
	}

	return instance;
}

float ChanlunVersion::GetVersion()
{
	return (float)iVersion[0] + (float)iVersion[1] / 100 + (float)iVersion[2] / 1000;
}

int ChanlunVersion::GetDate()
{
	return iVersion[4];
}

char* ChanlunVersion::GetAuthor()
{
	return "goodpp2012@gmail.com";
}

char* ChanlunVersion::GetEmail()
{
	return "goodpp2012@gmail.com";
}

char* ChanlunVersion::GetCopyRight()
{
	return "goodpp2012@gmail.com";
}