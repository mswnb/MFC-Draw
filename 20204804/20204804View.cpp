
// 20204804View.cpp: CMy20204804View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "20204804.h"
#endif

#include "20204804Doc.h"
#include "CSetPenSizeDialog.h"
#include "20204804View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy20204804View

IMPLEMENT_DYNCREATE(CMy20204804View, CView)

BEGIN_MESSAGE_MAP(CMy20204804View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32785, &CMy20204804View::OnSetPenSize)
	ON_COMMAND(ID_32786, &CMy20204804View::OnSetColor)
	ON_COMMAND(ID_32771, &CMy20204804View::OnDrawLine)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_32772, &CMy20204804View::OnDrawRectangle)
	ON_COMMAND(ID_32773, &CMy20204804View::OnDrawSquare)
	ON_COMMAND(ID_32782, &CMy20204804View::OnDrawTriangle)
	ON_COMMAND(ID_32783, &CMy20204804View::OnDrawPentagon)
	ON_COMMAND(ID_32784, &CMy20204804View::OnDrawHexagon)
	ON_COMMAND(ID_32775, &CMy20204804View::OnDrawCircle)
	ON_COMMAND(ID_32776, &CMy20204804View::OnDrawEllipse)
	ON_COMMAND(ID_32779, &CMy20204804View::OnText)
	ON_COMMAND(ID_32778, &CMy20204804View::OnFillColor)
END_MESSAGE_MAP()

// CMy20204804View 构造/析构

CMy20204804View::CMy20204804View() noexcept
{
	// TODO: 在此处添加构造代码
	Pen_Size = 1;//画笔粗细
	Pen_Color = RGB(0, 0, 0);//画笔颜色
	Brush_Color = RGB(0, 0, 0);//填充颜色
	BeginPoint = CPoint(0, 0);//图形起始点
	EndPoint = CPoint(0, 0);//图形终止点
	m_Shape = Shape::Line;//默认画线段

}

CMy20204804View::~CMy20204804View()
{
	if (m_Edit != nullptr) {
		delete m_Edit;
		m_Edit = nullptr;
	}
}

BOOL CMy20204804View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy20204804View 绘图

void CMy20204804View::OnDraw(CDC* /*pDC*/)
{
	CMy20204804Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMy20204804View 打印

BOOL CMy20204804View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy20204804View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy20204804View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMy20204804View 诊断

#ifdef _DEBUG
void CMy20204804View::AssertValid() const
{
	CView::AssertValid();
}

void CMy20204804View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy20204804Doc* CMy20204804View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy20204804Doc)));
	return (CMy20204804Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy20204804View 消息处理程序

//画笔粗细功能点击事件
void CMy20204804View::OnSetPenSize()
{
	// TODO: 在此添加命令处理程序代码
	CSetPenSizeDialog dlg;
	if (IDOK == dlg.DoModal()) {
		this->Pen_Size = dlg.Pen_Size;
	}
}

//颜色选择功能点击事件
void CMy20204804View::OnSetColor()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog dlg;
	if (IDOK == dlg.DoModal()) {
		if (m_Shape != Shape::Fill) {//未选择填充时默认选择的是画笔颜色
			Pen_Color = dlg.GetColor();
		}
		else {
			Brush_Color = dlg.GetColor();
		}
	}
}

//直线
void CMy20204804View::OnDrawLine()
{
	// TODO: 在此添加命令处理程序代码
	m_Shape = Shape::Line;
}


void CMy20204804View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	BeginPoint = EndPoint = point;
	Text_Pos = point;
	if (m_Shape == Shape::Fill) {
		CClientDC Dc(this);
		CBrush cBr(Brush_Color);
		Dc.SelectObject(&cBr);
		Dc.ExtFloodFill(BeginPoint.x, BeginPoint.y, RGB(255, 255, 255), FLOODFILLSURFACE);
	}
	CView::OnLButtonDown(nFlags, point);
}


void CMy20204804View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CView::OnRButtonDown(nFlags, point);
}


void CMy20204804View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	CPen newPen, choosePen, *oldPen;
	newPen.CreatePen(PS_SOLID, Pen_Size, Pen_Color);
	oldPen = dc.SelectObject(&newPen);
	switch (m_Shape) {
		case Shape::Line:
			dc.MoveTo(BeginPoint);
			dc.LineTo(point);
			break;
		case Shape::Rectangle: {
			dc.SelectStockObject(PS_NULL);
			CRect rectP2(BeginPoint, point);
			dc.Rectangle(rectP2);
			break;
		}
		case Shape::Square: {
			dc.SelectStockObject(PS_NULL);

			int len2 = point.y - BeginPoint.y;
			if (point.x < BeginPoint.x) {//终点在起点左边
				EndPoint.x = BeginPoint.x - abs(len2);
			}
			else {//终点在起点右边
				EndPoint.x = BeginPoint.x + abs(len2);
			}
			EndPoint.y = point.y;
			CRect rectP2(BeginPoint, EndPoint);
			dc.Rectangle(rectP2);
			EndPoint = point;
			break;
		}
		case Shape::Triangle: {
			dc.SelectStockObject(PS_NULL);
			int lenx2 = abs(point.x - BeginPoint.x);
			int leny2 = point.y - BeginPoint.y;
			CPoint pt[3] = { CPoint(BeginPoint.x,BeginPoint.y),
							 CPoint(BeginPoint.x + lenx2,BeginPoint.y + leny2),
							 CPoint(BeginPoint.x - lenx2,BeginPoint.y + leny2) };
			dc.Polygon(pt, 3);
			EndPoint = point;
			break;
		}
		case Shape::Pentagon: {
			dc.SelectStockObject(PS_NULL);
			int lenx2 = abs(point.x - BeginPoint.x);
			int leny2 = point.y - BeginPoint.y;
			int lenxx2 = lenx2 + lenx2 / 1.6;
			int lenyy2 = leny2 / 2.6;
			CPoint pt[5] = { CPoint(BeginPoint.x, BeginPoint.y),
							 CPoint(BeginPoint.x + lenxx2, BeginPoint.y + lenyy2),
							 CPoint(BeginPoint.x + lenx2, BeginPoint.y + leny2),
							 CPoint(BeginPoint.x - lenx2, BeginPoint.y + leny2),
							 CPoint(BeginPoint.x - lenxx2, BeginPoint.y + lenyy2) };
			dc.Polygon(pt, 5);
			EndPoint = point;
			break;
		}
		case Shape::Hexagon: {
			dc.SelectStockObject(PS_NULL);
			int lenx2 = abs(point.x - BeginPoint.x);
			int leny2 = point.y - BeginPoint.y;
			int lenyy2 = leny2 / 4;//大致比例
			CPoint pt[6] = { CPoint(BeginPoint.x,BeginPoint.y),
							 CPoint(BeginPoint.x + lenx2,BeginPoint.y + lenyy2),
							 CPoint(BeginPoint.x + lenx2,BeginPoint.y + leny2 - lenyy2),
							 CPoint(BeginPoint.x,BeginPoint.y + leny2),
							 CPoint(BeginPoint.x - lenx2,BeginPoint.y + leny2 - lenyy2),
							 CPoint(BeginPoint.x - lenx2,BeginPoint.y + lenyy2) };
			dc.Polygon(pt, 6);
			EndPoint = point;
			break;
		}
		case Shape::Ellipse: {
			dc.SelectStockObject(PS_NULL);
			CRect rectP2(BeginPoint, point);
			dc.Ellipse(rectP2);
			break;
		}
		case Shape::Circle: {
			dc.SelectStockObject(PS_NULL);

			int len2 = point.y - BeginPoint.y;
			if (point.x < BeginPoint.x) {//终点在起点左边
				EndPoint.x = BeginPoint.x - abs(len2);
			}
			else {//终点在起点右边
				EndPoint.x = BeginPoint.x + abs(len2);
			}
			EndPoint.y = point.y;
			CRect rectP2(BeginPoint, EndPoint);
			dc.Ellipse(rectP2);
			EndPoint = point;
			break;
		}
		case Shape::Text: {
			CEdit* m_edit = new CEdit();
			m_edit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(BeginPoint, point), this, Textid);
			m_edit->ShowWindow(SW_SHOW);

			if (nullptr != m_Edit) {
				delete m_Edit;
			}
			m_Edit = m_edit;

			break;
		}
		case Shape::Choose: {
			if (!Chosen) {
				CRect rectP2(BeginPoint, point);
				//ClearRect(rectP2);
				CRect rect;
				GetClientRect(&rect);
				HBITMAP hbitmap = CreateCompatibleBitmap(dc, rect.right - rect.left, rect.bottom - rect.top);//创建兼容位图
				bc_hdc = CreateCompatibleDC(dc);      //创建兼容DC，以便将图像保存为不同的格式
				SelectObject(bc_hdc, hbitmap);//将位图选入DC，并保存返回值 
				BitBlt(bc_hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, dc, 0, 0, SRCCOPY);//将屏幕DC图像复制到内存DC

				CBrush cBr(RGB(255, 255, 255));
				dc.FillRect(rectP2, &cBr);

				hbitmap = CreateCompatibleBitmap(dc, rect.right - rect.left, rect.bottom - rect.top);//创建兼容位图
				ac_hdc = CreateCompatibleDC(dc);
				SelectObject(ac_hdc, hbitmap);
				BitBlt(ac_hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, dc, 0, 0, SRCCOPY);
				StretchBlt(dc, BeginPoint.x, BeginPoint.y, rectP2.Width(), rectP2.Height(),
					bc_hdc, BeginPoint.x, BeginPoint.y, rectP2.Width(), rectP2.Height(), SRCCOPY);
				//FastRect(rectP2, false);
				EndPoint = point;
				Chosen = true;
				Chooselt = BeginPoint;
				Choosebr = point;
				Startlt = Chooselt;
				Startbr = Choosebr;
				Tempclt = Chooselt;
				Tempcbr = Choosebr;
			}
			else {
				Chooselt = Tempclt;
				Choosebr = Tempcbr;
				CRect rectP2(Chooselt, Choosebr);
				//FastRect(rectP2, false);
			}
			break;
		}
		default:
			break;
	}
	dc.SelectObject(oldPen);
	CView::OnLButtonUp(nFlags, point);
}


void CMy20204804View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnRButtonUp(nFlags, point);
}


void CMy20204804View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nFlags & MK_LBUTTON) {
		CClientDC dc(this);
		CPen newPen, choosePen, *oldPen;
		newPen.CreatePen(PS_SOLID, Pen_Size, Pen_Color);
		oldPen = dc.SelectObject(&newPen);
		switch (m_Shape) {
		case Shape::Line:
			dc.SetROP2(R2_NOTXORPEN);//画笔颜色与屏幕像素值的异或再反色，达到画笔移动的效果
			dc.MoveTo(BeginPoint);
			dc.LineTo(EndPoint);
			dc.MoveTo(BeginPoint);
			dc.LineTo(point);
			EndPoint = point;
			break;
		case Shape::Rectangle: {
			dc.SetROP2(R2_NOTXORPEN);//画笔颜色与屏幕像素值的异或再反色，达到画笔移动的效果
			dc.SelectStockObject(PS_NULL);
			CRect rectP(BeginPoint, EndPoint);
			dc.Rectangle(rectP);
			CRect rectP2(BeginPoint, point);
			dc.Rectangle(rectP2);
			EndPoint = point;
			break;
		}
		case Shape::Square: {
			dc.SetROP2(R2_NOTXORPEN);//画笔颜色与屏幕像素值的异或再反色，达到画笔移动的效果
			dc.SelectStockObject(PS_NULL);
			int len1 = EndPoint.y - BeginPoint.y;
			if (EndPoint.x < BeginPoint.x) {//终点在起点左边
				EndPoint.x = BeginPoint.x - abs(len1);
			}
			else {//终点在起点右边
				EndPoint.x = BeginPoint.x + abs(len1);
			}
			CRect rectP(BeginPoint, EndPoint);
			dc.Rectangle(rectP);

			int len2 = point.y - BeginPoint.y;
			if (point.x < BeginPoint.x) {//终点在起点左边
				EndPoint.x = BeginPoint.x - abs(len2);
			}
			else {//终点在起点右边
				EndPoint.x = BeginPoint.x + abs(len2);
			}
			EndPoint.y = point.y;
			CRect rectP2(BeginPoint, EndPoint);
			dc.Rectangle(rectP2);
			EndPoint = point;
			break;
		}
		case Shape::Triangle: {
			dc.SetROP2(R2_NOTXORPEN);//画笔颜色与屏幕像素值的异或再反色，达到画笔移动的效果
			dc.SelectStockObject(PS_NULL);
			int lenx = abs(EndPoint.x - BeginPoint.x);
			int leny = EndPoint.y - BeginPoint.y;
			CPoint pt[3] = { CPoint(BeginPoint.x,BeginPoint.y),
							 CPoint(BeginPoint.x + lenx,BeginPoint.y + leny),
							 CPoint(BeginPoint.x - lenx,BeginPoint.y + leny) };
			dc.Polygon(pt, 3);

			int lenx2 = abs(point.x - BeginPoint.x);
			int leny2 = point.y - BeginPoint.y;
			pt[0] = CPoint(BeginPoint.x, BeginPoint.y);
			pt[1] = CPoint(BeginPoint.x + lenx2, BeginPoint.y + leny2);
			pt[2] = CPoint(BeginPoint.x - lenx2, BeginPoint.y + leny2);
			dc.Polygon(pt, 3);
			EndPoint = point;
			break;
		}
		case Shape::Pentagon: {
			dc.SetROP2(R2_NOTXORPEN);//画笔颜色与屏幕像素值的异或再反色，达到画笔移动的效果
			dc.SelectStockObject(PS_NULL);
			int lenx = abs(EndPoint.x - BeginPoint.x);
			int leny = EndPoint.y - BeginPoint.y;
			int lenxx = lenx + lenx / 1.6;//大致比例
			int lenyy = leny / 2.6;//大致比例
			CPoint pt[5] = { CPoint(BeginPoint.x,BeginPoint.y),
							 CPoint(BeginPoint.x + lenxx,BeginPoint.y + lenyy),
							 CPoint(BeginPoint.x + lenx,BeginPoint.y + leny),
							 CPoint(BeginPoint.x - lenx,BeginPoint.y + leny),
							 CPoint(BeginPoint.x - lenxx,BeginPoint.y + lenyy) };
			dc.Polygon(pt, 5);

			int lenx2 = abs(point.x - BeginPoint.x);
			int leny2 = point.y - BeginPoint.y;
			int lenxx2 = lenx2 + lenx2 / 1.6;
			int lenyy2 = leny2 / 2.6;
			pt[0] = CPoint(BeginPoint.x, BeginPoint.y);
			pt[1] = CPoint(BeginPoint.x + lenxx2, BeginPoint.y + lenyy2);
			pt[2] = CPoint(BeginPoint.x + lenx2, BeginPoint.y + leny2);
			pt[3] = CPoint(BeginPoint.x - lenx2, BeginPoint.y + leny2);
			pt[4] = CPoint(BeginPoint.x - lenxx2, BeginPoint.y + lenyy2);
			dc.Polygon(pt, 5);
			EndPoint = point;
			break;
		}
		case Shape::Hexagon: {
			dc.SetROP2(R2_NOTXORPEN);//画笔颜色与屏幕像素值的异或再反色，达到画笔移动的效果
			dc.SelectStockObject(PS_NULL);
			int lenx = abs(EndPoint.x - BeginPoint.x);
			int leny = EndPoint.y - BeginPoint.y;
			int lenyy = leny / 4;//大致比例
			CPoint pt[6] = { CPoint(BeginPoint.x,BeginPoint.y),
							 CPoint(BeginPoint.x + lenx,BeginPoint.y + lenyy),
							 CPoint(BeginPoint.x + lenx,BeginPoint.y + leny - lenyy),
							 CPoint(BeginPoint.x,BeginPoint.y + leny),
							 CPoint(BeginPoint.x - lenx,BeginPoint.y + leny - lenyy),
							 CPoint(BeginPoint.x - lenx,BeginPoint.y + lenyy) };
			dc.Polygon(pt, 6);

			int lenx2 = abs(point.x - BeginPoint.x);
			int leny2 = point.y - BeginPoint.y;
			int lenyy2 = leny2 / 4;
			pt[0] = CPoint(BeginPoint.x, BeginPoint.y);
			pt[1] = CPoint(BeginPoint.x + lenx2, BeginPoint.y + lenyy2);
			pt[2] = CPoint(BeginPoint.x + lenx2, BeginPoint.y + leny2 - lenyy2);
			pt[3] = CPoint(BeginPoint.x, BeginPoint.y + leny2);
			pt[4] = CPoint(BeginPoint.x - lenx2, BeginPoint.y + leny2 - lenyy2);
			pt[5] = CPoint(BeginPoint.x - lenx2, BeginPoint.y + lenyy2);
			dc.Polygon(pt, 6);
			EndPoint = point;
			break;
		}
		case Shape::Ellipse: {
			dc.SetROP2(R2_NOTXORPEN);//画笔颜色与屏幕像素值的异或再反色，达到画笔移动的效果
			dc.SelectStockObject(PS_NULL);
			CRect rectP(BeginPoint, EndPoint);
			dc.Ellipse(rectP);
			CRect rectP2(BeginPoint, point);
			dc.Ellipse(rectP2);
			EndPoint = point;
			break;
		}
		case Shape::Circle: {
			dc.SetROP2(R2_NOTXORPEN);//画笔颜色与屏幕像素值的异或再反色，达到画笔移动的效果
			dc.SelectStockObject(PS_NULL);
			int len1 = EndPoint.y - BeginPoint.y;
			if (EndPoint.x < BeginPoint.x) {//终点在起点左边
				EndPoint.x = BeginPoint.x - abs(len1);
			}
			else {//终点在起点右边
				EndPoint.x = BeginPoint.x + abs(len1);
			}
			CRect rectP(BeginPoint, EndPoint);
			dc.Ellipse(rectP);

			int len2 = point.y - BeginPoint.y;
			if (point.x < BeginPoint.x) {//终点在起点左边
				EndPoint.x = BeginPoint.x - abs(len2);
			}
			else {//终点在起点右边
				EndPoint.x = BeginPoint.x + abs(len2);
			}
			EndPoint.y = point.y;
			CRect rectP2(BeginPoint, EndPoint);
			dc.Ellipse(rectP2);
			EndPoint = point;
			break;
		}
		case Shape::Text: {
			if (nullptr != m_Edit) {
				delete m_Edit;
			}

			CEdit* m_edit = new CEdit();
			m_edit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(BeginPoint, point), this, Textid);
			m_Edit = m_edit;
			m_edit->ShowWindow(SW_SHOW);

			break;
		}
		/*case Shape::Choose: {
			if (!Chosen) {
				CRect rectP(BeginPoint, EndPoint);
				FastRect(rectP, true);
				CRect rectP2(BeginPoint, point);
				FastRect(rectP2, true);
				EndPoint = point;
			}
			else {
				CRect area(Tempclt, Tempcbr);
				ClearRect(area);
				CRect rect;
				GetClientRect(&rect);
				StretchBlt(dc, 0, 0, rect.Width(), rect.Height(),
					ac_hdc, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
				int lenx = point.x - BeginPoint.x;
				int leny = point.y - BeginPoint.y;
				Tempclt = CPoint(Chooselt.x + lenx, Chooselt.y + leny);
				Tempcbr = CPoint(Choosebr.x + lenx, Choosebr.y + leny);
				CRect newarea(Tempclt, Tempcbr);
				StretchBlt(dc, Tempclt.x, Tempclt.y, newarea.Width(), newarea.Height(),
					bc_hdc, Startlt.x, Startlt.y, Startbr.x - Startlt.x, Startbr.y - Startlt.y, SRCCOPY);
				FastRect(newarea, true);
			}

			break;
		}*/
		case Shape::Pencil: {
			BeginPoint = EndPoint;//终点做新起点
			EndPoint = point;
			dc.MoveTo(BeginPoint);
			dc.LineTo(EndPoint);

			break;
		}
		case Shape::Eraser: {
			COLORREF pColor = dc.GetBkColor();
			CPen newPen(PS_SOLID, Pen_Size, pColor);
			dc.SelectObject(&newPen);

			BeginPoint = EndPoint;//终点做新起点
			EndPoint = point;
			dc.MoveTo(BeginPoint);
			dc.LineTo(EndPoint);

			break;
		}
		default:
			break;
		}
		dc.SelectObject(oldPen);
	}
	/*if (nFlags & MK_RBUTTON) {
		CClientDC dc(this);
		if (m_Shape == Shape::Choose && Chosen) {
			CRect area(Tempclt, Tempcbr);
			ClearRect(area);
			CRect rect;
			GetClientRect(&rect);
			StretchBlt(dc, 0, 0, rect.Width(), rect.Height(),
				ac_hdc, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
			int lenx = point.x - BeginPoint.x;
			int leny = point.y - BeginPoint.y;
			Tempcbr = CPoint(Choosebr.x + lenx, Choosebr.y + leny);
			CRect newarea(Tempclt, Tempcbr);
			StretchBlt(dc, Tempclt.x, Tempclt.y, newarea.Width(), newarea.Height(),
				bc_hdc, Startlt.x, Startlt.y, Startbr.x - Startlt.x, Startbr.y - Startlt.y, SRCCOPY);
			FastRect(newarea, true);
		}
	}*/
	CView::OnMouseMove(nFlags, point);
}

//矩形
void CMy20204804View::OnDrawRectangle()
{
	// TODO: 在此添加命令处理程序代码
	m_Shape = Shape::Rectangle;
}

//正方形
void CMy20204804View::OnDrawSquare()
{
	// TODO: 在此添加命令处理程序代码
	m_Shape = Shape::Square;
}

//三角形
void CMy20204804View::OnDrawTriangle()
{
	// TODO: 在此添加命令处理程序代码
	m_Shape = Shape::Triangle;
}

//五边形
void CMy20204804View::OnDrawPentagon()
{
	// TODO: 在此添加命令处理程序代码
	m_Shape = Shape::Pentagon;
}

//六边形
void CMy20204804View::OnDrawHexagon()
{
	// TODO: 在此添加命令处理程序代码
	m_Shape = Shape::Hexagon;
}

//圆
void CMy20204804View::OnDrawCircle()
{
	// TODO: 在此添加命令处理程序代码
	m_Shape = Shape::Circle;
}

//椭圆
void CMy20204804View::OnDrawEllipse()
{
	// TODO: 在此添加命令处理程序代码
	m_Shape = Shape::Ellipse;
}

//文本框
void CMy20204804View::OnText()
{
	// TODO: 在此添加命令处理程序代码
	m_Shape = Shape::Text;
}


BOOL CMy20204804View::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (m_Shape != Shape::Choose && Chosen) {//从选择切换到了其他模式
		CRect area(Chooselt, Choosebr);
		ClearRect(area);
		Chosen = false;
	}
	//if (m_Shape != Shape::Text && m_Edit != nullptr) {//从文本切换到了其他模式
	//	CString pStr;
	//	m_Edit->GetWindowTextW(pStr);
	//	delete m_Edit;
	//	m_Edit = nullptr;
	//	CClientDC dc(this);
	//	dc.TextOutW(Text_Pos.x, Text_Pos.y, pStr);
	//	return TRUE;
	//}
	if ((m_Shape != Shape::Text || (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN && m_Shape == Shape::Text)) && m_Edit != nullptr) {//按下回车
			CString pStr;
			m_Edit->GetWindowTextW(pStr);
			delete m_Edit;
			m_Edit = nullptr;
			CClientDC dc(this);
			dc.TextOutW(Text_Pos.x, Text_Pos.y, pStr);
			return TRUE;
	}
	/*if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_BACK) {//按下退格
		if (Chosen) {
			CClientDC dc(this);
			CRect rect;
			GetClientRect(&rect);
			StretchBlt(dc, 0, 0, rect.Width(), rect.Height(),
				       ac_hdc, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
			Chosen = false;
			return TRUE;
		}
	}*/
	return CView::PreTranslateMessage(pMsg);
}


void CMy20204804View::ClearRect(CRect rect)
{
	// TODO: 在此处添加实现代码.
	CClientDC dc(this);
	CPen choosePen, *oldPen;
	choosePen.CreatePen(PS_DASH, 1, RGB(255, 255, 255));
	oldPen = dc.SelectObject(&choosePen);
	dc.SetROP2(R2_COPYPEN);
	dc.SelectStockObject(PS_NULL);
	dc.Rectangle(rect);
}


void CMy20204804View::FastRect(CRect rect, bool notxor)
{
	// TODO: 在此处添加实现代码.
	CClientDC dc(this);
	CPen choosePen, *oldPen;
	choosePen.CreatePen(PS_DASH, 1, RGB(0, 0, 0));
	oldPen = dc.SelectObject(&choosePen);
	if (notxor) {
		dc.SetROP2(R2_NOTXORPEN);//画笔颜色与屏幕像素值的异或再反色，达到画笔移动的效果
	}
	dc.SelectStockObject(PS_NULL);
	dc.Rectangle(rect);
}


void CMy20204804View::OnFillColor()
{
	// TODO: 在此添加命令处理程序代码
	m_Shape = Shape::Fill;
}
