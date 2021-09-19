// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// PlanetaryMotionGeneratorView.cpp : implementation of the CPlanetaryMotionGeneratorView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PlanetaryMotionGenerator.h"
#endif

#include "PlanetaryMotionGeneratorDoc.h"
#include "PlanetaryMotionGeneratorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlanetaryMotionGeneratorView

IMPLEMENT_DYNCREATE(CPlanetaryMotionGeneratorView, CView)

BEGIN_MESSAGE_MAP(CPlanetaryMotionGeneratorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPlanetaryMotionGeneratorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_Start, &CPlanetaryMotionGeneratorView::OnButtonStart)
	ON_COMMAND(ID_BUTTON_Suspend, &CPlanetaryMotionGeneratorView::OnButtonSuspend)
	ON_COMMAND(ID_BUTTON_Resume, &CPlanetaryMotionGeneratorView::OnButtonResume)
END_MESSAGE_MAP()

// CPlanetaryMotionGeneratorView construction/destruction

CPlanetaryMotionGeneratorView::CPlanetaryMotionGeneratorView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;
	m_fCounter = 0.00;

	x = 400;
	y = 400;

	a = 625;
	b = 400;

	a1 = 250;
	b1 = 400;

}

CPlanetaryMotionGeneratorView::~CPlanetaryMotionGeneratorView()
{
}

BOOL CPlanetaryMotionGeneratorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPlanetaryMotionGeneratorView drawing

void CPlanetaryMotionGeneratorView::OnDraw(CDC* pDC)
{
	CPlanetaryMotionGeneratorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CPen purplePen;
	purplePen.CreatePen(PS_SOLID, 2, RGB(128, 0, 128));
	CPen* pOldPen = pDC->SelectObject(&purplePen);

	pDC->Ellipse(175, 175, 625, 625);//outer circle
	pDC->Ellipse(250, 250, 550, 550);//inner circle
	pDC->Ellipse(350, 350, 450, 450);//center circular path
	

	pDC->Ellipse(a - 15, b - 15, a + 15, b + 15);
	pDC->Ellipse(a1 - 15, b1 - 15, a1 + 15, b1 + 15);
	pDC->SelectObject(pOldPen);
}


// CPlanetaryMotionGeneratorView printing


void CPlanetaryMotionGeneratorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPlanetaryMotionGeneratorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPlanetaryMotionGeneratorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPlanetaryMotionGeneratorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPlanetaryMotionGeneratorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPlanetaryMotionGeneratorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPlanetaryMotionGeneratorView diagnostics

#ifdef _DEBUG
void CPlanetaryMotionGeneratorView::AssertValid() const
{
	CView::AssertValid();
}

void CPlanetaryMotionGeneratorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlanetaryMotionGeneratorDoc* CPlanetaryMotionGeneratorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlanetaryMotionGeneratorDoc)));
	return (CPlanetaryMotionGeneratorDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlanetaryMotionGeneratorView message handlers


void CPlanetaryMotionGeneratorView::OnButtonStart()
{
	m_pCurrentThread = AfxBeginThread(CPlanetaryMotionGeneratorView::StartThread, this);
}


void CPlanetaryMotionGeneratorView::OnButtonSuspend()
{
	m_pCurrentThread->SuspendThread();
}


void CPlanetaryMotionGeneratorView::OnButtonResume()
{
	m_pCurrentThread->ResumeThread();
}


UINT CPlanetaryMotionGeneratorView::StartThread(LPVOID Param)
{
	CPlanetaryMotionGeneratorView* pView = (CPlanetaryMotionGeneratorView*)Param;
	// TODO: Add your implementation code here.
	while (1)
	{
		pView->a = pView->x + 225 * cos(pView->m_fCounter);
		pView->b = pView->y + 225 * sin(pView->m_fCounter);

		pView->a1 = pView->x + 150 * cos(pView->m_fCounter +180);
		pView->b1 = pView->y + 150 * sin(pView->m_fCounter +180);

		pView->m_fCounter = pView->m_fCounter + 0.1;

		pView->Invalidate();
		Sleep(250);


	}
	
	pView->Invalidate();
	pView->UpdateWindow();
	return 0;
}
