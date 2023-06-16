
// 20204804.h: 20204804 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // 主符号


// CMy20204804App:
// 有关此类的实现，请参阅 20204804.cpp
//

class CMy20204804App : public CWinApp
{
public:
	CMy20204804App() noexcept;


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy20204804App theApp;
