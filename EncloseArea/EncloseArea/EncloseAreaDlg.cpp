
// EncloseAreaDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EncloseArea.h"
#include "EncloseAreaDlg.h"
#include "afxdialogex.h"

#include "Line.h"
#include "Polyline.h"
#include "Point.h"
#include "Base.h"
#include <vector>
#include "InputAndOutput.h"
#include "ModalEntity.h"
#include "MinimumClosedArea.h"
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEncloseAreaDlg �Ի���



CEncloseAreaDlg::CEncloseAreaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEncloseAreaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEncloseAreaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEncloseAreaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INPUT, &CEncloseAreaDlg::OnBnClickedButtonInput)
	ON_BN_CLICKED(IDC_BUTTON_OPENDATA, &CEncloseAreaDlg::OnBnClickedButtonOpendata)
	ON_BN_CLICKED(IDC_BUTTON_SAVEDATA, &CEncloseAreaDlg::OnBnClickedButtonSavedata)
	ON_BN_CLICKED(IDC_BUTTON_OPENMODAL, &CEncloseAreaDlg::OnBnClickedButtonOpenmodal)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CEncloseAreaDlg::OnBnClickedButtonTest)
END_MESSAGE_MAP()


// CEncloseAreaDlg ��Ϣ�������

BOOL CEncloseAreaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_FilePath = '0';

	m_bFilePath = FALSE;

	CWnd* pOpenModal = GetDlgItem(IDC_BUTTON_OPENMODAL);
	pOpenModal->EnableWindow(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CEncloseAreaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CEncloseAreaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CEncloseAreaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//�����߶κͶ����
void CEncloseAreaDlg::OnBnClickedButtonInput()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	static TCHAR BASED_CODE szFilters[] = _T("�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("�ı��ļ�"), _T("*.txt"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

	if (dlg.DoModal() == IDOK)
	{
		m_bFilePath = TRUE;  //����Ѿ���������

		CString FileName = dlg.GetFileName();
		//��ȡ�ĵ��е�����   
		CInputAndOutput output;
		char *filename =FileName.GetBuffer(FileName.GetLength());
		output.InputData(filename,Entity);
		
		FileName.ReleaseBuffer();
	}
	CWnd* pOpenModal = GetDlgItem(IDC_BUTTON_OPENMODAL);
	pOpenModal->EnableWindow(TRUE);
}

//��ģ������
void CEncloseAreaDlg::OnBnClickedButtonOpendata()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_bFilePath == FALSE)
	{
		MessageBox(_T("�����ȵ�������!"));
		return;
	}
	UpdateData(); 
	CFile file;  
	file.Open(m_FilePath, CFile::modeWrite | CFile::modeCreate); 
	file.Close();  
}

//����ģ������
void CEncloseAreaDlg::OnBnClickedButtonSavedata()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_bFilePath == FALSE)
	{
		AfxMessageBox(_T("�����ȵ�������!"));
		return;

	}

	static TCHAR BASED_CODE szFilters[] = _T("�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");

	CFileDialog FileDlg(FALSE, _T("txt"), m_FilePath); 
	FileDlg.m_ofn.lpstrTitle = _T("Save File");
	FileDlg.m_ofn.lpstrFilter = szFilters;

	if (IDOK == FileDlg.DoModal())
	{
		CFile File(FileDlg.GetPathName(),CFile::modeCreate|CFile::modeReadWrite);

		char szBufData[100] = {"hello word!"};
		//д���ļ�����,������/0
		File.Write(szBufData, strlen(szBufData));
		//����д�룬������
		File.Flush();
		//�ļ����������ر�
		File.Close();
	}

}

//�ڶԻ����л��Ƴ�ģ��
void CEncloseAreaDlg::OnBnClickedButtonOpenmodal()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CWnd *pwnd = GetDlgItem(IDC_STATIC_OPENMODAL);
	CDC *pDC = pwnd->GetDC();
	pwnd->Invalidate();
	pwnd->UpdateWindow();

	pDC->Rectangle(0, 0, 400, 400);

	CPen *ppenRed = new CPen;

	ppenRed->CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	CGdiObject *pOldpen = pDC->SelectObject(ppenRed);

	//����ֱ��
	int nLineNum = Entity.getLineNum();
	for (int i=0;i<nLineNum;i++)
	{
		CLine line = Entity.GetLine(i);
		line.draw(pDC);
	}

	//���ƶ����
	vector<CPolyline> PolylineVector = Entity.GetPolylineVector();
	for (unsigned int i = 0;i < PolylineVector.size(); i++)
	{
		PolylineVector[i].draw(pDC);
	}

}


void CEncloseAreaDlg::OnBnClickedButtonTest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CWnd *pwnd = GetDlgItem(IDC_STATIC_TESTMODEL);
	CDC *pDC = pwnd->GetDC();
	pwnd->Invalidate();
	pwnd->UpdateWindow();
	pDC->Rectangle(0, 0, 380, 400);

	CPen *ppenRed = new CPen;
	ppenRed->CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CGdiObject *pOldpen = pDC->SelectObject(ppenRed);

	//������С�պ�����
	CMinimumClosedArea ClosedArea;
	//1.�õ�ȫ���߶μ���
	vector<CLine> AllLineSegment =  ClosedArea.get_line(Entity.GetLineVector(),Entity.GetPolylineVector());
	Point crossPoint = ClosedArea.getcrosspoint(AllLineSegment[0],AllLineSegment[1]);
	//2.�Ƴ��������߶Σ����˵ĵ㶼�ǹ����ģ�
	vector<CLine> nonisolatedLine = ClosedArea.remove_isolated_line(AllLineSegment);
 	//3.������е��߶Σ����ǽ����е��ཻ���߶β�ֿ����õ��µ��߶μ���S��
	vector<CLine> breaklines = ClosedArea.breaklines(nonisolatedLine);
	//4.�Ƴ�һ���˵�������߶Σ�һ���˵�������߶��ǲ����ɶ���εģ�
	vector<CLine> nonefieldlines = ClosedArea.removenonefieldlines(breaklines);
	for (unsigned int k = 0; k < nonefieldlines.size();k++ )
	{

		nonefieldlines[k].draw(pDC);
	}
/*
	vector<vector<CLine>> get_all_big_field = ClosedArea.get_all_big_field(nonefieldlines);

	//����
	for (unsigned int i= 0;i<get_all_big_field.size();i++)
	{
		vector<CLine> lines;
		for (auto j = get_all_big_field[i].begin();j != get_all_big_field[i].end(); j++)
		{
			lines.push_back(*j);

		}
		//pDC->BeginPath();
		for (unsigned int k = 0; k < lines.size();k++ )
		{

			lines[k].draw(pDC);
		}
		pDC->EndPath();
		CRgn rgn;
		rgn.CreateFromPath(pDC);
		pDC->InvertRgn(&rgn);

		CBrush brush(RGB(100, 150, 200));
		CBrush *pBrush = pDC->SelectObject(&brush);
		pDC->FillRgn(&rgn,pBrush);


	}

*/

}
