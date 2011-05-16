#pragma once


// GtOpenDialog ��ȭ �����Դϴ�.

class GtOpenDialog : public CFileDialog
{
	DECLARE_DYNAMIC(GtOpenDialog)
protected:
	static CString mLastPath;
	CString mFilter;

public:
	GtOpenDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL,
		DWORD dwSize = 0,
		BOOL bVistaStyle = TRUE);   // ǥ�� �������Դϴ�.
	virtual ~GtOpenDialog();
	
protected:
	

	DECLARE_MESSAGE_MAP()
public:	
	static CString& GetLastOpenPath();
	INT_PTR DoFileDialog();
	INT_PTR DoFolderDialog();
	LPCTSTR GetFilter()
	{
		return mFilter.GetBuffer();
	}	

protected:
	static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
};
