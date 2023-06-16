// CSetPenSizeDialog.cpp: 实现文件
//

#include "pch.h"
#include "20204804.h"
#include "CSetPenSizeDialog.h"
#include "afxdialogex.h"


// CSetPenSizeDialog 对话框

IMPLEMENT_DYNAMIC(CSetPenSizeDialog, CDialogEx)

CSetPenSizeDialog::CSetPenSizeDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CSetPenSizeDialog::~CSetPenSizeDialog()
{
}

void CSetPenSizeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, Edit);
	CString str;
	Edit.GetWindowTextW(str);
	Pen_Size = _ttoi(str);
}


BEGIN_MESSAGE_MAP(CSetPenSizeDialog, CDialogEx)
END_MESSAGE_MAP()


// CSetPenSizeDialog 消息处理程序
