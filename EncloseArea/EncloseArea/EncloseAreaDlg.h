
// EncloseAreaDlg.h : ͷ�ļ�
//

#pragma once

#include "Line.h"
#include "Polyline.h"
#include "Point.h"
#include <vector>
#include "ModalEntity.h"
using namespace std;

// CEncloseAreaDlg �Ի���
class CEncloseAreaDlg : public CDialogEx
{
// ����
public:
	CEncloseAreaDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ENCLOSEAREA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonInput();
	afx_msg void OnBnClickedButtonOpendata();
	afx_msg void OnBnClickedButtonSavedata();

private:
	CString m_FilePath;
	//CString m_FileName;
	BOOL m_bFilePath;
	//CLine m_line;
	//vector<CLine> m_LineVector;
	//vector<vector<Point>> m_PolylineVector;
	CModalEntity Entity;
public:
	afx_msg void OnBnClickedButtonOpenmodal();
	afx_msg void OnBnClickedButtonTest();
};
