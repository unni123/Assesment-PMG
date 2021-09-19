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

// PlanetaryMotionGeneratorView.h : interface of the CPlanetaryMotionGeneratorView class
//

#pragma once


class CPlanetaryMotionGeneratorView : public CView
{
	CWinThread* m_pCurrentThread;
protected: // create from serialization only
	CPlanetaryMotionGeneratorView() noexcept;
	DECLARE_DYNCREATE(CPlanetaryMotionGeneratorView)

// Attributes
public:
	float m_fCounter;
	int a, b, x, y, a1, b1;
	CPlanetaryMotionGeneratorDoc* GetDocument() const;


// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPlanetaryMotionGeneratorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonStart();
	afx_msg void OnButtonSuspend();
	afx_msg void OnButtonResume();
	static UINT StartThread(LPVOID Param);
};

#ifndef _DEBUG  // debug version in PlanetaryMotionGeneratorView.cpp
inline CPlanetaryMotionGeneratorDoc* CPlanetaryMotionGeneratorView::GetDocument() const
   { return reinterpret_cast<CPlanetaryMotionGeneratorDoc*>(m_pDocument); }
#endif

