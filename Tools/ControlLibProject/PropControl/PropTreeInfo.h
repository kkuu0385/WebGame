 #if !defined(AFX_PROPTREEINFO_H__22BD9C18_A68C_4BB8_B7FC_C4A7DA0E1EBF__INCLUDED_)
#define AFX_PROPTREEINFO_H__22BD9C18_A68C_4BB8_B7FC_C4A7DA0E1EBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropTreeInfo.h : header file
//
//
//  Copyright (C) 1998-2001 Scott Ramsay
//	sramsay@gonavi.com
//	http://www.gonavi.com
//
//  This material is provided "as is", with absolutely no warranty expressed
//  or implied. Any use is at your own risk.
// 
//  Permission to use or copy this software for any purpose is hereby granted 
//  without fee, provided the above notices are retained on all copies.
//  Permission to modify the code and to distribute modified code is granted,
//  provided the above notices are retained, and a notice that the code was
//  modified is included with the above copyright notice.
// 
//	If you use this code, drop me an email.  I'd like to know if you find the code
//	useful.

class CPropTree;

/////////////////////////////////////////////////////////////////////////////
// CPropTreeInfo window

class CPropTreeInfo : public CStatic
{
	// Attributes
public:
	// CPropTree class that this class belongs
	void SetPropOwner(CPropTree* pProp)
	{
		m_pProp = pProp;
	}
	CDialog*		m_pInfo;
	
protected:
	CPropTree*		m_pProp;

public:
	CPropTreeInfo();
	virtual ~CPropTreeInfo();	

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropTreeInfo)
	//}}AFX_VIRTUAL

	
	// Generated message map functions
protected:
	//{{AFX_MSG(CPropTreeInfo)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

class CPropTreeStaticInfo : public CPropTreeInfo
{
	// Construction
public:
	CPropTreeStaticInfo();

	// Operations
public:


	// Implementation
public:
	virtual ~CPropTreeStaticInfo();


};

class CPropTreeDlgInfo : public CPropTreeInfo
{
public:
	CPropTreeDlgInfo();
	~CPropTreeDlgInfo(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPTREEINFO_H__22BD9C18_A68C_4BB8_B7FC_C4A7DA0E1EBF__INCLUDED_)
