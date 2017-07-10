/********************************************************
* * Copyright (c) 2012, �������ͨ�Ź����ͨ�豸���޹�˾
* * All rights reserved.
* 
* �ļ����ƣ�TranslatorDlg.cpp
* ����������Ӧ�ó���
* 
* ��ǰ�汾��	V1.0
* ��    �ߣ�	�Ż�
* ������ڣ�	2012.03.28
* 
* ���ļ�¼����
*********************************************************/

#include "stdafx.h"
#include "Translator.h"
#include "TranslatorDlg.h"
#include "direct.h"
#include "ATP_ATO_MACRO.h"
#include "CnComm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


long baudrate[]={300,600,1200,2400,4800,9600,19200,38400,43000,56000,57600,115200};
int databit[]={8,7,6};

UINT ComProce(LPVOID pParam);

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTranslatorDlg dialog

BEGIN_MESSAGE_MAP(CTranslatorDlg, CDialog)
	//{{AFX_MSG_MAP(CTranslatorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_COMM_RXCHAR, OnCommunication)
	ON_CBN_SELCHANGE(IDC_COMBO_SERIOU, OnSelchangeComboSeriou)
	ON_BN_CLICKED(IDC_BUTTEN_MENUALSEND, OnButtenMenualsend)
	ON_BN_CLICKED(IDC_BUTTON_TRANSFILE, OnButtonTransfile)
	ON_BN_CLICKED(IDC_CHECK_AUTOSEND, OnCheckAutosend)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_EMPTYTEXT, OnButtonEmptytext)
	ON_BN_CLICKED(IDC_CHECK_WRITETOFILE, OnCheckWritetofile)
	ON_BN_CLICKED(IDC_BUTTON_FILENAME, OnButtonFilename)
	ON_BN_CLICKED(IDC_BUTTON_SAVEEDIT, OnButtonSaveedit)
	ON_BN_CLICKED(IDC_BUTTON_EMPTYRX, OnButtonEmptyrx)
	ON_BN_CLICKED(IDC_BUTTON_PORTSTATU, OnButtonPortstatu)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_CBN_SELCHANGE(IDC_COMBO_BAUD, OnSelchangeComboBaud)
	ON_CBN_SELCHANGE(IDC_COMBO_DATA, OnSelchangeComboData)
	ON_CBN_SELCHANGE(IDC_COMBO_JIAOYAN, OnSelchangeComboJiaoyan)
	ON_CBN_SELCHANGE(IDC_COMBO_STOP, OnSelchangeComboStop)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_EXCELSELECT, OnButtonExcelselect)
	ON_BN_CLICKED(IDC_BUTTON_EXCELTOBIN, OnButtonExceltobin)
	ON_BN_CLICKED(IDC_BUTTON_EXCELTOBINLOCATION, OnButtonExceltobinlocation)
	ON_BN_CLICKED(IDC_BUTTON_TRANSFILELOCATION, OnButtonTransfilelocation)
	ON_CBN_EDITCHANGE(IDC_COMBO_SENDDISTINATION, OnEditchangeComboSenddistination)
	ON_CBN_SELCHANGE(IDC_COMBO_SENDDISTINATION, OnSelchangeComboSenddistination)
	ON_BN_CLICKED(IDC_BUTTON_SELECTFRAMEHEAD, OnButtonSelectframehead)
	ON_BN_CLICKED(IDC_BUTTON_SELECTUPGEO, OnButtonSelectupgeo)
	ON_BN_CLICKED(IDC_BUTTON_SELECTDOWNGEO, OnButtonSelectdowngeo)
	ON_BN_CLICKED(IDC_BUTTON_SYNTHESIZEGEO, OnButtonSynthesizegeo)
	ON_BN_CLICKED(IDC_CLEARBUTTON, OnClearbutton)
	//}}AFX_MSG_MAP
//	ON_MESSAGE(WM_COMMNOTIFY,ProcessCOMMNotification)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTranslatorDlg message handlers
CTranslatorDlg::CTranslatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTranslatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTranslatorDlg)
	m_SeriouStr = _T("");
	m_BaudStr = _T("");
	m_StopStr = _T("");
	m_savefilename = _T("");
	m_savesendrecoder = _T("");
	m_strTXData = _T("");
	m_filepath = _T("");
	m_strRXData = _T("");
	m_JiaoyanStr = _T("");
	m_DataStr = _T("");
	m_strbindata = _T("");
	m_strexceldata = _T("");
	m_strbinfilepath = _T("");
	m_strstartaddress = _T("");
	m_strsenddistination = _T("");
	m_strmaxtimetowait = _T("");
	m_strmaxtimetoresend = _T("");
	m_strcounterforlefttosend = _T("");
	m_strcounterforsheets = _T("");
	m_strcounterforrows = _T("");
	m_strcounterforcols = _T("");
	m_strframeheadexcelfilepath = _T("");
	m_strupgeofilepath = _T("");
	m_strsynthesizegeofilepath = _T("");
	m_strdowngeofilepath = _T("");
	m_strcounterforallsend = _T("");
	m_strcounterforcurrentsend = _T("");
	m_strcounterforframeindata = _T("");
	m_strcounterfordataall = _T("");
	m_strcounterforleftdata = _T("");
	m_strcounterforallbytesend = _T("");
	m_strrebackinfomation = _T("");
	m_strlefttime = _T("");
	m_strcountertime = _T("");
	m_csgeoaddallcheck = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_txlen=0;
	m_rxlen=0;
	m_bConnected=0;
	m_bAutoSend=FALSE;
	m_portstatu_but=TRUE;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTranslatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTranslatorDlg)
	DDX_Control(pDX, IDC_GEOADDALLCHECK, m_cgeoaddallcheck);
	DDX_Control(pDX, IDC_STATIC_COUNTERTIME, m_cscountertime);
	DDX_Control(pDX, IDC_STATIC_LEFTTIME, m_cslefttime);
	DDX_Control(pDX, IDC_BUTTON_TRANSFILELOCATION, m_transfilelocation);
	DDX_Control(pDX, IDC_STATIC_REBACKINFOMATION, m_csrebackinfomation);
	DDX_Control(pDX, IDC_STATIC_COUNTERFORCURRENTSEND, m_cscounterforcurrentsend);
	DDX_Control(pDX, IDC_STATIC_COUNTERFORALLBYTESEND, m_cscounterforallbytesend);
	DDX_Control(pDX, IDC_STATIC_COUNTERFORLEFTDATA, m_cscounterforleftdata);
	DDX_Control(pDX, IDC_STATIC_COUNTERFORDATAALL, m_cscounterfordataall);
	DDX_Control(pDX, IDC_STATIC_COUNTERFORFRAMEINDATA, m_cscounterforframeindata);
	DDX_Control(pDX, IDC_STATIC_DOWNGEOEXCELFILEPAHT, m_csdowngeofilepath);
	DDX_Control(pDX, IDC_STATIC_SYNTHESIZEGEOEXCELFILEPAHT, m_cssynthesizegeofilepath);
	DDX_Control(pDX, IDC_STATIC_UPGEOEXCELFILEPAHT, m_csupgeofilepath);
	DDX_Control(pDX, IDC_STATIC_FRAMEHEADEXCELFILEPAHT, m_csframeheadexcelfilepath);
	DDX_Control(pDX, IDC_STATIC_COUNTERFORCOLS, m_cscounterforcols);
	DDX_Control(pDX, IDC_STATIC_COUNTERFORROWS, m_cscounterforrows);
	DDX_Control(pDX, IDC_STATIC_COUNTERFORSHEETS, m_cscounterforsheets);
	DDX_Control(pDX, IDC_CHECK_AUTOSEND, m_ctlautosend);
	DDX_Control(pDX, IDC_STATIC_COUNTERFORLEFTTOSEND, m_cscounterforlefttosend);
	DDX_Control(pDX, IDC_EDIT_MAXTIMESTORESEND, m_editmaxtimestoresend);
	DDX_Control(pDX, IDC_EDIT_MAXTIMETOWAIT, m_editmaxtimetowait);
	DDX_Control(pDX, IDC_COMBO_SENDDISTINATION, m_combosenddistination);
	DDX_Control(pDX, IDC_EDIT_BINDATAADDRESS, m_ceditstartaddress);
	DDX_Control(pDX, IDC_STATIC_BINFILEPAHT, m_sbinfilepath);
	DDX_Control(pDX, IDC_EDIT_EXCELDATA, m_editexceldata);
	DDX_Control(pDX, IDC_BUTTON_EMPTYRX, m_emptyrx);
	DDX_Control(pDX, IDC_STATIC_FILENAME, m_filename);
	DDX_Control(pDX, IDC_CHECK_HEXSEND, m_cHexSend);
	DDX_Control(pDX, IDC_BUTTON_EMPTYTEXT, m_emptytx);
	DDX_Control(pDX, IDC_BUTTON_TRANSFILE, m_transfile);
	DDX_Control(pDX, IDC_BUTTEN_MENUALSEND, m_sendbutten);
	DDX_Control(pDX, IDC_EDIT_TXDATA, m_edittxdata);
	DDX_Control(pDX, IDC_STATIC_FILEPAHT, m_sFilePath);
	DDX_Control(pDX, IDC_STATIC_EXCELFILEPAHT, m_sEXCELFilePath);
	DDX_Control(pDX, IDC_STATIC_COUNTERFORLEFT, m_cscounterforleft);
	DDX_Control(pDX, IDC_CHECK_HEXDISPLAY, m_ctrlHexDisplay);
	DDX_Control(pDX, IDC_CHECK_WRITETOFILE, m_judgesend);
	DDX_Control(pDX, IDC_COMBO_STOP, m_ComboStop);
	DDX_Control(pDX, IDC_COMBO_JIAOYAN, m_ComboJiaoyan);
	DDX_Control(pDX, IDC_COMBO_DATA, m_ComboData);
	DDX_Control(pDX, IDC_COMBO_BAUD, m_ComboBaud);
	DDX_Control(pDX, IDC_COMBO_SERIOU, m_ComboSeriou);
	DDX_CBString(pDX, IDC_COMBO_SERIOU, m_SeriouStr);
	DDX_CBString(pDX, IDC_COMBO_BAUD, m_BaudStr);
	DDX_CBString(pDX, IDC_COMBO_STOP, m_StopStr);
	DDX_Text(pDX, IDC_STATIC_FILENAME, m_savefilename);
	DDX_Text(pDX, IDC_EDIT_TXDATA, m_strTXData);
	DDX_Text(pDX, IDC_STATIC_FILEPAHT, m_filepath);
	DDX_Text(pDX, IDC_STATIC_COUNTERFORLEFT, m_strcounterforleft);
	DDX_Text(pDX, IDC_STATIC_EXCELFILEPAHT, m_EXCELfilepath);
	DDX_Text(pDX, IDC_EDIT_RXDATA, m_strRXData);
	DDX_CBString(pDX, IDC_COMBO_JIAOYAN, m_JiaoyanStr);
	DDX_CBString(pDX, IDC_COMBO_DATA, m_DataStr);
	DDX_Text(pDX, IDC_EDIT_EXCELDATA, m_strexceldata);
	DDX_Text(pDX, IDC_STATIC_BINFILEPAHT, m_strbinfilepath);
	DDX_Text(pDX, IDC_EDIT_BINDATAADDRESS, m_strstartaddress);
	DDX_CBString(pDX, IDC_COMBO_SENDDISTINATION, m_strsenddistination);
	DDX_Text(pDX, IDC_EDIT_MAXTIMETOWAIT, m_strmaxtimetowait);
	DDX_Text(pDX, IDC_EDIT_MAXTIMESTORESEND, m_strmaxtimetoresend);
	DDX_Text(pDX, IDC_STATIC_COUNTERFORLEFTTOSEND, m_strcounterforlefttosend);
	DDX_Text(pDX, IDC_STATIC_COUNTERFORSHEETS, m_strcounterforsheets);
	DDX_Text(pDX, IDC_STATIC_COUNTERFORROWS, m_strcounterforrows);
	DDX_Text(pDX, IDC_STATIC_COUNTERFORCOLS, m_strcounterforcols);
	DDX_Text(pDX, IDC_STATIC_FRAMEHEADEXCELFILEPAHT, m_strframeheadexcelfilepath);
	DDX_Text(pDX, IDC_STATIC_UPGEOEXCELFILEPAHT, m_strupgeofilepath);
	DDX_Text(pDX, IDC_STATIC_SYNTHESIZEGEOEXCELFILEPAHT, m_strsynthesizegeofilepath);
	DDX_Text(pDX, IDC_STATIC_DOWNGEOEXCELFILEPAHT, m_strdowngeofilepath);
	DDX_Text(pDX, IDC_STATIC_COUNTERFORCURRENTSEND, m_strcounterforcurrentsend);
	DDX_Text(pDX, IDC_STATIC_COUNTERFORFRAMEINDATA, m_strcounterforframeindata);
	DDX_Text(pDX, IDC_STATIC_COUNTERFORDATAALL, m_strcounterfordataall);
	DDX_Text(pDX, IDC_STATIC_COUNTERFORLEFTDATA, m_strcounterforleftdata);
	DDX_Text(pDX, IDC_STATIC_COUNTERFORALLBYTESEND, m_strcounterforallbytesend);
	DDX_Text(pDX, IDC_STATIC_REBACKINFOMATION, m_strrebackinfomation);
	DDX_Text(pDX, IDC_STATIC_LEFTTIME, m_strlefttime);
	DDX_Text(pDX, IDC_STATIC_COUNTERTIME, m_strcountertime);
	DDX_Text(pDX, IDC_GEOADDALLCHECK, m_csgeoaddallcheck);
	//}}AFX_DATA_MAP
}

using namespace std;

BOOL CTranslatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	addall();
//	OnSelchangeComboSeriou();
//	OpenComm(0);
	//��ʼ���ص����¼����ص�д�¼�

	memset(&m_osRead,0,sizeof(OVERLAPPED));
	memset(&m_osWrite,0,sizeof(OVERLAPPED));
	m_osRead.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	if(m_osRead.hEvent==NULL)
	{
		AfxMessageBox("wrong2");
		return FALSE;
	}
	m_osWrite.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	if(m_osWrite.hEvent==NULL)
	{
		AfxMessageBox("wrong3");
		return FALSE;
	}

	//�ؼ�Ĭ��״̬�ͱ�����ʼ��
	m_ctrlHexDisplay.SetCheck(1);
	m_judgesend.SetCheck(1);
	m_judgesend.SetState(FALSE);
	m_cHexSend.SetCheck(1);
	m_ctlautosend.SetCheck(1);
	mkdir("d:\\commandrecoder");
	mkdir("d:\\sendrecoder");
	m_savesendrecoder="d:\\sendrecoder\\sendrecoder.txt";
	m_savefilename="d:\\commandrecoder\\recoder.txt";
	m_intcounterdatanumup=1;
	m_NULL=" ";
	m_crclen=0;
	m_counter=0;
	m_lostframe=0;
	m_intcounterdatanum=0;
	m_binfilelenthtocalulate=0;
	b_fileopen=FALSE;
	m_sendworks=0x80;
	m_sendreadd=0x30;
	m_sendbuzz=0x00;
	m_framehead="fc0c02";  //�̶�ͷ
	m_counters=255;
	m_framesequence="11";    //Ĭ��֡Ƶ��
	m_framenull="0102030405060708090a0b0c0d";  //�м�հײ�ֵ
	m_EXCELfilepath="";
	m_strbinfilepath="";
	m_strcounterforleft="0";
	m_fileopen=FALSE;
	m_filepath="";
	m_strsendaddress="93";	//����Ŀ���ַĬ��ΪATP_MPM_A��ַ��0x93;
	m_intmaxtimetowait=0;	//���ȴ�ʱ��
	m_intmaxtimestowait=0;	//���ȴ�����
	m_binfilelenth=0;		//�������ļ��ܳ���
	m_senddatastartaddress=""; //�˹�������ʼ��ַ
	m_Errorframecounter=0;		//����֡����
	m_counterofframe=1;		//֡�м�������������ÿһ�����ݰ��еĵڼ���֡��ȡֵ1-4
	m_cansend=FALSE;		//�Ƿ���Է������ݣ��ȴ���λ���ź�
	m_resendframe="";		//�ϳɺ���ط���֡
	m_overframe="";			//�ϳɺ�Ľ���֡
	m_binreadcounter=0;		//��ȡ�������ļ�ָ��
	m_framecommand="";		//ȫ��ָ֡��
	m_frameheadexcelfilepath="";	//֡ͷ�ļ�·��
	m_upgeofilepath="";				//���е��������ļ�
	m_downgeofilepath="";			//���е��������ļ�
	/*
	**���÷���Ĭ��ֵ
	*/
	m_return="\r\n";
	m_strmaxtimetoresend="3";
	m_editmaxtimestoresend.SetWindowText(m_strmaxtimetoresend);
	m_strmaxtimetowait="2000";
	m_editmaxtimetowait.SetWindowText(m_strmaxtimetowait);
	m_strstartaddress="0x00000000";
	m_ceditstartaddress.SetWindowText(m_strstartaddress);
	m_firsttime=TRUE;
	m_bgeo=TRUE;
	/*
	//����1 CRTͨ��
	m_nCom=2;
	m_nBaud=115200;
	m_cParity='N';
	m_nDatabits=8;
	m_nStopbits=1;
	
	//����״̬��ʾ
	m_SeriouStr.Format("%d",m_nCom);
	m_BaudStr.Format("%d",m_nBaud);
	m_JiaoyanStr.Format("%c",m_cParity);
	m_DataStr.Format("%d",m_nDatabits);
	m_StopStr.Format("%d",m_nStopbits);

	m_dwCommEvents = EV_RXFLAG | EV_RXCHAR;
	CString strStatus;
	
	//�򿪴���1
	if (m_Port[0].InitPort(this, m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits,m_dwCommEvents,51200))
	{
		m_Port[0].StartMonitoring();
		strStatus.Format(" STATUS��COM%d is connected,%d,%c,%d,%d",m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits);
		//m_ctrlPortStatus.SetWindowText(strStatus);
		//m_ctrlIconOpenoff.SetIcon(m_hIconRed);
		//"��ǰ״̬�����ڴ򿪣�����żУ�飬8����λ��1ֹͣλ");
		m_bConnected=1;
	}
	else
	{
		strStatus.Format(" STATUS��COM%d Lost or Occupied!",m_nCom);
		//m_ctrlPortStatus.SetWindowText(strStatus);
		//m_ctrlIconOpenoff.SetIcon(m_hIconOff);
		AfxMessageBox(strStatus);
		m_bConnected=0;
	}
	*/

	bool yy =Rscom.SetState(115200,8,0,1);
	bool ww = Rscom.Open(1,115200);
	
	if(ww)
	{
		SetTimer(5,1,NULL);
		SetTimer(6,1,NULL);
	}
	else
	{
		MessageBox("���ڴ�ʧ��!");
	}

	m_rxdatalenth=0;
	m_rxstrdata="";
	m_rxstrtodisplay="";
	m_dealframe=TRUE;
	m_intstartaddress=0;
	m_intwanttoreadaddress=0;
	m_boolresend=FALSE;	//�Ƿ����ط���־λ
	m_lefthour=0;
	m_leftminute=0;
	m_leftsecond=0;
	m_counterhour=0;
	m_counterminute=0;
	m_countersecond=0;
	m_bsendbutten=FALSE;
	DispStatus();
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTranslatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTranslatorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTranslatorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTranslatorDlg::addall()
{
	//�貨��������б��
	TCHAR baudbuffer[][7]={"300","600","1200","2400","4800","9600","19200","38400","43000","56000","57600","115200"};

    for(int i=0;i<12;i++)
	{
		int judge_tf=m_ComboBaud.AddString(baudbuffer[i]);

		if((judge_tf==CB_ERR)||(judge_tf==CB_ERRSPACE))

           MessageBox("build baud error!");
	}

	m_ComboBaud.SetCurSel(11);

    //�贮������б��
	TCHAR seriou[][5]={"COM1","COM2","COM3","COM4"};

	for(i=0;i<4;i++)
	{
		m_ComboSeriou.AddString(seriou[i]);
	}

	m_ComboSeriou.SetCurSel(0);

	//��У��λ����б��
	TCHAR jiaoyan[][7]={"N","O","E"};

	for(i=0;i<3;i++)
	{
		m_ComboJiaoyan.AddString(jiaoyan[i]);
	}

	m_ComboJiaoyan.SetCurSel(0);

	//������λ����б��
	TCHAR data[][2]={"8","7","6"};

	for(i=0;i<3;i++)
	{
		m_ComboData.AddString(data[i]);
	}

	m_ComboData.SetCurSel(0);

	//��ֹͣλ����б��
	TCHAR stop[][2]={"1","2"};

	for(i=0;i<2;i++)
	{
		m_ComboStop.AddString(stop[i]);
	}

	m_ComboStop.SetCurSel(0);

	//����Ŀ�ĵ��б��
// 		ATP_MPM_A��ַ��0x93;
//		ATP_MPM_B��ַ��0xA3
// 		ATP_MPM_C��ַ��0xB3
// 		ATP_MPM_D��ַ��0xC3
// 		ATO_MPM��ַ��  0xD3

	 	TCHAR senddistination[][10]={"ATP_MPM_A","ATP_MPM_B","ATP_MPM_C","ATP_MPM_D","ATO_MPM"};
	 
	 	for(i=0;i<5;i++)
	 	{
			m_combosenddistination.AddString(senddistination[i]);
	 	}
	
		m_combosenddistination.SetCurSel(0);

		m_rxnumber=0;
}

void CTranslatorDlg::OnSelchangeComboSeriou() 
{
	// TODO: Add your control notification handler code here

	m_nCom=m_ComboSeriou.GetCurSel()+1;
	
	bool yy =Rscom.SetState(115200,8,0,1);
	bool ww = Rscom.Open(m_nCom,115200);
	
	if(ww)
	{
		SetTimer(5,1,NULL);
		SetTimer(6,1,NULL);
	}
	else
	{
		MessageBox("���ڴ�ʧ��!");
	}

	/*
	if (m_bConnected)
	{
		CloseConnection();
	}

	if(m_portstatu_but)
	{
		m_nCom=m_ComboSeriou.GetCurSel()+1;

		//OpenComm(i);

		CString strStatus;
		
		//�򿪴���1
		if (m_Port[0].InitPort(this, m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits,m_dwCommEvents,51200))
		{
			m_Port[0].StartMonitoring();
			strStatus.Format(" STATUS��COM%d is connected,%d,%c,%d,%d",m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits);
			//m_ctrlPortStatus.SetWindowText(strStatus);
			//m_ctrlIconOpenoff.SetIcon(m_hIconRed);
			//"��ǰ״̬�����ڴ򿪣�����żУ�飬8����λ��1ֹͣλ");
			m_bConnected=1;
		}
		else
		{
			strStatus.Format(" STATUS��COM%d Lost or Occupied!",m_nCom);
			//m_ctrlPortStatus.SetWindowText(strStatus);
			//m_ctrlIconOpenoff.SetIcon(m_hIconOff);
			AfxMessageBox(strStatus);
			m_bConnected=0;
		}
	}

	DispStatus();
	*/
}

BOOL CTranslatorDlg::SetCommParameter()
{
	DCB dcb;

	if(!GetCommState(m_hCom,&dcb))
	{
		return FALSE;
	}

	//���û�������
	int baudindex=m_ComboBaud.GetCurSel();

	m_ComboBaud.GetLBText(baudindex,m_BaudStr);

	dcb.BaudRate=baudrate[baudindex];

	int dataindex=m_ComboData.GetCurSel();

	m_ComboData.GetLBText(dataindex,m_DataStr);

	dcb.ByteSize=databit[dataindex];

	int jiaoyanindex=m_ComboJiaoyan.GetCurSel();

	m_ComboJiaoyan.GetLBText(jiaoyanindex,m_JiaoyanStr);

	switch(jiaoyanindex)
	{
		case 0:
			dcb.Parity=NOPARITY;
			break;
		case 1:
			dcb.Parity=ODDPARITY;
			break;
		case 2:
			dcb.Parity=EVENPARITY;
			break;
		default:;
	}

	int stopindex=m_ComboStop.GetCurSel();

	m_ComboStop.GetLBText(stopindex,m_StopStr);

	switch(stopindex)
	{
		case 0:
			dcb.StopBits=ONESTOPBIT;
			break;
		case 1:
			dcb.StopBits=TWOSTOPBITS;
			break;
		default:;
	}

	//������
	dcb.fInX=FALSE;
	dcb.fOutX=FALSE;
	dcb.XonChar=XON;
	dcb.XoffChar=XOFF;
	dcb.XonLim=10;
	dcb.XoffLim=10;

	//����Ӳ���������Ϊ��������ͨ��
	dcb.fBinary=TRUE;
	dcb.fNull=FALSE;
	
	//��������forDSP
//	dcb.fDtrControl=2;
//	dcb.fDsrSensitivity=1;
//	dcb.fRtsControl=2;


	return(SetCommState(m_hCom,&dcb));
}

BOOL CTranslatorDlg::OpenComm(int Num)
{
	/*
	COMMTIMEOUTS TimeOuts;

	m_ComboSeriou.GetLBText(Num,m_SeriouStr);

	m_hCom=CreateFile(m_SeriouStr,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,NULL);

	if(m_hCom==INVALID_HANDLE_VALUE)
	{
		AfxMessageBox("�򿪴���ʧ��!");

		m_bConnected=0;

		return FALSE;
	}

	//���ù������߳���Ӧ���¼�
	SetCommMask(m_hCom,EV_RXCHAR);

	//���ö�д������
	SetupComm(m_hCom,MAXBLOCK,MAXBLOCK);

	//���ó�ʱ
	TimeOuts.ReadIntervalTimeout=MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier=0;
	TimeOuts.ReadTotalTimeoutConstant=0;
	TimeOuts.WriteTotalTimeoutMultiplier=0;
	SetCommTimeouts(m_hCom,&TimeOuts);

	//�����������߳�
	if(SetCommParameter())
	{
		m_pThread=AfxBeginThread(ComProce,this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED,NULL);

		if(m_pThread==NULL)
		{
			CloseHandle(m_hCom);

			AfxMessageBox("�̴߳���ʧ��!");

			m_bConnected=0;

			return FALSE;
		}
		else
		{
			m_pThread->ResumeThread();
		}
	}
	else
	{
		CloseHandle(m_hCom);

		AfxMessageBox("��������ʧ��!");

		m_bConnected=0;

		return FALSE;
	}

	m_bConnected=1;

	return TRUE;

  */
	
	return TRUE;
}
UINT ComProce(LPVOID pParam)
{

	OVERLAPPED os;
	DWORD dwMask,dwTrans;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	
	CTranslatorDlg *pDlg=(CTranslatorDlg *)pParam;

	memset(&os,0,sizeof(OVERLAPPED));

	os.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	
	if(os.hEvent==NULL)
	{
		AfxMessageBox("���ܽ����¼�����!");

		return (UINT)-1;
	}

	while(pDlg->m_bConnected)
	{
		ClearCommError(pDlg->m_hCom,&dwErrorFlags,&ComStat);

		if(ComStat.cbInQue)
		{
//			pDlg->ProcessCOMMNotification(EV_RXCHAR,0);
		}

		dwMask=0;

		if(!WaitCommEvent(pDlg->m_hCom,&dwMask,&os))
		{
			if(GetLastError()==ERROR_IO_PENDING)
			{
				GetOverlappedResult(pDlg->m_hCom,&os,&dwTrans,TRUE);
			}
			else
			{
				CloseHandle(os.hEvent);

				return(UINT)-1;
			}
		}
	}
	CloseHandle(os.hEvent);
	return 0;
}

LONG CTranslatorDlg::OnCommunication(WPARAM ch, LPARAM port)
{

	m_rx[m_rxnumber]=ch;
	m_rxnumber++;

	int m_nframe=0;
	CString m_str10;
	CFileException e;
	
	m_strcrcData="";
	
	BOOL judgefile=m_judgesend.GetCheck();
	
	//�жϴ����Ƿ��ѹر�
	if(!m_bConnected)
	{
		return FALSE;
	}

	m_rxlen++;
	//�ַ��ϲ�
	CString m_temprxdata;
	CString m_space=" ";
	m_temprxdata.Format("%02X",ch);
	m_rxstrdata+=m_temprxdata;
	m_rxstrtodisplay+=m_temprxdata;
	m_rxstrtodisplay+=m_space;
	
	//һ֡���ݿ�ʼ����
	if (m_rxnumber==24)
	{

		m_rxnumber=0;
		m_str10=m_rxstrdata.GetAt(10);
		m_nframe=atoi(m_str10);
		if (m_nframe!=7)
		{
			return 0;
		}


		m_rxlen=0;
		m_rxdatalenth+=24;

		if (m_filepath!="")
		{
			m_rxstrtodisplay+=m_return;
			
			
			m_editexceldata.SetWindowText(m_rxstrtodisplay);
			
			int   nLen   =   m_editexceldata.SendMessage(WM_GETTEXTLENGTH);
			
			m_editexceldata.SetSel(nLen,   nLen,   FALSE); 
			
			m_rxlen=0;
			
			m_strcrcData=m_rxstrdata;


			//����CRC16
			CString	  m_crcrx;
			m_crcrx=m_strcrcData.Right(4);
			//ȡ����5���ֽڣ�����֡������
			CString	  m_strcounter,m_strcounter1,m_strcounter2;
			int Cframecounter;
			char strtocounter[2];
			char * str;

			m_strcounter1=m_strcrcData.GetAt(8);

			m_strcounter2=m_strcrcData.GetAt(9);

			m_strcounter=m_strcounter1+m_strcounter2;

			::strcpy(strtocounter,m_strcounter);

			Cframecounter=(int)strtoul(strtocounter,&str,16);

			m_counter=Cframecounter;
			
			CString m_strcrc16;
			CString  m_strcrc44;
			
			m_strcrc44=m_strcrcData.Left(44);

			
			//��λ������ָ���
			
			//����CRC16

			m_strcrc16=CalculatestrCRC(m_strcrc44, 22);
			
			m_crcrx.MakeUpper();
			CString m_uppercrc=m_crcrx;
			m_crcrx.MakeLower();
			CString m_lowwercrc=m_crcrx;

			

			//֡У����ȷ
			if ((m_strcrc16==m_crcrx)||(m_strcrc16==m_uppercrc)||(m_strcrc16==m_lowwercrc))
			{
				CString m_command,m_strat12,m_strat13,m_strat14,m_strat15;
				m_strat12=m_strcrcData.GetAt(12);
				m_strat13=m_strcrcData.GetAt(13);
				m_strat14=m_strcrcData.GetAt(14);
				m_strat15=m_strcrcData.GetAt(15);

				m_command=m_strat12+m_strat13+m_strat14+m_strat15;

				
				//����CRCУ�����ж��Ƿ����ָ��
				

				if (m_command=="AAAA")
				{
					m_strrebackinfomation="��һ֡";
					
					m_csrebackinfomation.SetWindowText(m_strrebackinfomation);
				}
				else if (m_command=="BBBB")
				{
					m_strrebackinfomation="��ʱ";
					
					m_csrebackinfomation.SetWindowText(m_strrebackinfomation);

				}
				else if (m_command=="CCCC")
				{
					m_boolresend=TRUE;
					
					KillTimer(2);
					
					CString m_erroraddress=m_strcrcData.Mid(20,8);
					
					CString m_addresshead="0x";
					
					m_addresshead+=m_erroraddress;
					
					m_intwanttoreadaddress=CStringAddresstoInt(m_addresshead);
					
					//�ж���λ��������ַ��Ϣ�Ƿ񳬳���ȡ��Χ
					
					if (m_intwanttoreadaddress>m_binfilelenthtocalulate)
					{
						AfxMessageBox("��λ��������ַ���ڷ����ļ���ַ���޷���ȡ����!");
						return 0;
					}
					
					m_strrebackinfomation="���Ͱ�����,���ݵ�ַ�ط�!";
					
					m_csrebackinfomation.SetWindowText(m_strrebackinfomation);
					
					m_binreadcounter=m_intwanttoreadaddress-m_intstartaddress;
					
					m_senddatastartaddress=m_addresshead;
					
					//�������Ͷ�ʱ��
					SetTimer(2,PACKAGELAP,NULL);

				}
				else if (m_command=="DDDD")
				{
					m_strrebackinfomation="����У��ɹ�";
					
					m_csrebackinfomation.SetWindowText(m_strrebackinfomation);
					
					AfxMessageBox("����У��ɹ�");

				}
				//���ݴ���������λ�����أ���Ϣ��ʽΪ��ַΪEEEE���������Ǵ������ݵ�ַ
				else if (m_command=="EEEE")
				{
					m_boolresend=TRUE;

					KillTimer(2);
					
					CString m_erroraddress=m_strcrcData.Mid(20,8);

					CString m_addresshead="0x";

					m_addresshead+=m_erroraddress;

					m_intwanttoreadaddress=CStringAddresstoInt(m_addresshead);

					//�ж���λ��������ַ��Ϣ�Ƿ񳬳���ȡ��Χ

					if (m_intwanttoreadaddress>m_binfilelenthtocalulate)
					{
						AfxMessageBox("��λ��������ַ���ڷ����ļ���ַ���޷���ȡ����!");
						return 0;
					}


					m_strrebackinfomation="���Ͱ�����,���ݵ�ַ�ط�!";
					
					m_csrebackinfomation.SetWindowText(m_strrebackinfomation);
					
					m_binreadcounter=m_intwanttoreadaddress-m_intstartaddress;

					m_senddatastartaddress=m_addresshead;

					//Resendframe();
					//�������Ͷ�ʱ��
					SetTimer(2,PACKAGELAP,NULL);

				}
				else if (m_command=="EEFF")
				{
					//�����ı䣬�ٴε��÷��͹���
					m_cansend=TRUE;

					KillTimer(1);	//ֹͣ����ready�ź�

					m_strrebackinfomation="Ԥ��";

					SetTimer(3,100,NULL); //�˶�ʱ��ֻ��һ�飬��ʱд����

					m_dealframe=TRUE;

					m_csrebackinfomation.SetWindowText(m_strrebackinfomation);
					
				}
				else if (m_command=="7777")
				{
					
					m_strrebackinfomation="����У��ʧ��";
					
					m_csrebackinfomation.SetWindowText(m_strrebackinfomation);

					AfxMessageBox("��λ��У��ʧ��!");
					
				}

				else
				{
					m_strrebackinfomation="����ʶ��ķ�������";
					
					m_csrebackinfomation.SetWindowText(m_strrebackinfomation);
				}
			}


			//������д�뵽�ı��ļ�
			if(judgefile)
			{
				//�ж��Ƿ�д���ļ�,�����ļ�,��ָ�붨���ļ�ĩβ
				if (b_fileopen==FALSE)
				{
					m_countertodispatch=Cframecounter;

					getdatafile.Open(m_savefilename,CFile::modeCreate+CFile::modeNoTruncate+CFile::modeWrite,&e);

					b_fileopen=TRUE;
				}

 				CString enter="\r\n";
				CString testall;
				int charlength;

 				getdatafile.SeekToEnd();   //��д��λ�ö�λ���ı�ĩβ

				testall=m_strcrcData+enter;

				charlength=testall.GetLength();

				getdatafile.Write(m_strcrcData+enter,50);
				
			}
			
			//֡���м���
			
			int lostframecounter;

			Cframecounter++;

			lostframecounter=Cframecounter-m_countertodispatch;

			if (1!=lostframecounter)
			{
				int m_resault; //ģ�����

				if (0==lostframecounter)
				{
					m_resault=256;
				}
				else
				{
					m_resault=lostframecounter % 255;
				}
				
				m_lostframe+=m_resault;
			}

			m_countertodispatch=Cframecounter;

			m_rxstrdata="";
		}
		else
		{
			m_rxstrtodisplay+=m_return;
			
			m_editexceldata.SetWindowText(m_rxstrtodisplay);
			
			int   nLen   =   m_editexceldata.SendMessage(WM_GETTEXTLENGTH);
			
			m_editexceldata.SetSel(nLen,   nLen,   FALSE); 
		}

		m_rxstrdata="";
	}


	DispStatus();
	
	return 0;
}


/*
BOOL CTranslatorDlg::ProcessCOMMNotification (UINT wParam,long lParam)
{
	CFileException e;

	m_strcrcData="";

	BOOL judgefile=m_judgesend.GetCheck();

	//�жϴ����Ƿ��ѹر�
	if(!m_bConnected)
	{
		return FALSE;
	}

	//�ж��յ����Ƿ��������Ϣ
	if((EV_RXCHAR&wParam)!=EV_RXCHAR)
	{
		return FALSE;
	}

	//�����ݶ���CString������
	CString StrTemp;

	BYTE abIn[MAXBLOCK];

	int len=0;

//	AcceptRead.Empty();//���CString����,�����¶�����ַ�

//	len=ReadBlock(abIn,MAXBLOCK);
	
	if(!len)
	{
		AfxMessageBox("���ַ��������顣");

		return FALSE;
	}

	if(len!=24)
	{
		CString m_said="����֡���ȴ���,���ݳ���Ϊ:";
		CString m_framelenth;
		m_framelenth.Format("%d",len);
		m_said+=m_framelenth;
		AfxMessageBox(m_said);
		return FALSE;
	}
	for(int i=0;i<len;i++)
	{
		BYTE bt=abIn[i];

		if(m_ctrlHexDisplay.GetCheck())
		{
			StrTemp.Format("%02X",bt);
		}
		else
		{
		    StrTemp.Format("%c",bt);
		}
		m_strRXData+=StrTemp+m_NULL;
		m_strcrcData+=StrTemp;

	}

	m_rxlen+=len;   //������ʾ�������ݳ���

	//����CRC16
	CString	  m_crcrx;
	m_crcrx=m_strcrcData.Right(4);
	//ȡ����5���ֽڣ�����֡������
	CString	  m_strcounter,m_strcounter1,m_strcounter2;
	int Cframecounter;
	char strtocounter[2];
	char * str;

	m_strcounter1=m_strcrcData.GetAt(8);

	m_strcounter2=m_strcrcData.GetAt(9);

	m_strcounter=m_strcounter1+m_strcounter2;

	::strcpy(strtocounter,m_strcounter);

	Cframecounter=(int)strtoul(strtocounter,&str,16);

	m_counter=Cframecounter;

	
	CString m_strcrc16;
	CString  m_strcrc44;
	
	m_strcrc44=m_strcrcData.Left(44);

	
	//��λ������ָ���
	
	//����CRC16

	m_strcrc16=CalculatestrCRC(m_strcrc44, 22);
	
	m_crcrx.MakeUpper();
	CString m_uppercrc=m_crcrx;
	m_crcrx.MakeLower();
	CString m_lowwercrc=m_crcrx;

	//֡У����ȷ
	if ((m_strcrc16==m_crcrx)||(m_strcrc16=m_uppercrc)||(m_strcrc16==m_lowwercrc))
	{
		CString m_command,m_strat12,m_strat13,m_strat14,m_strat15;
		m_strat12=m_strcrcData.GetAt(12);
		m_strat13=m_strcrcData.GetAt(13);
		m_strat14=m_strcrcData.GetAt(14);
		m_strat15=m_strcrcData.GetAt(15);

		m_command=m_strat12+m_strat13+m_strat14+m_strat15;

		
		//����CRCУ�����ж��Ƿ����ָ��
		

		if (m_command=="AAAA")
		{
			m_strrebackinfomation="��һ֡";
			
			m_csrebackinfomation.SetWindowText(m_strrebackinfomation);
		}
		else if (m_command=="BBBB")
		{
			m_strrebackinfomation="�ȴ�";
			
			m_csrebackinfomation.SetWindowText(m_strrebackinfomation);

		//	Sleep(60000);

			KillTimer(3);
			KillTimer(1);
			SetTimer(4,600000,NULL);
		}
		else if (m_command=="CCCC")
		{
			m_strrebackinfomation="��һ֡";
			
			m_csrebackinfomation.SetWindowText(m_strrebackinfomation);

			KillTimer(3);
			KillTimer(4);

			if (m_binfilelenthtocalulate>=m_binreadcounter)
			{
				Sendbinarydata();
			}
			else
			{
				//�ϳɲ����ͽ���֡
				Composeresendoverframe();
				m_txlen+=24;
				Allfuctionabled();
				AfxMessageBox("���ݷ������!");
			}

			
		}
		else if (m_command=="DDDD")
		{
			m_strrebackinfomation="��һ֡";
			
			m_csrebackinfomation.SetWindowText(m_strrebackinfomation);
		}
		else if (m_command=="EEEE")
		{
			m_strrebackinfomation="�ط�";
			
			m_csrebackinfomation.SetWindowText(m_strrebackinfomation);
			KillTimer(3);
			KillTimer(4);

			Resendframe();
			
		}
		else if (m_command=="FFEE")
		{
			
			m_cansend=TRUE;

			m_strrebackinfomation="Ԥ��";
			
			m_csrebackinfomation.SetWindowText(m_strrebackinfomation);
			
		}
		else if (m_command=="7777")
		{
			
			m_strrebackinfomation="У��ʧ��";
			
			m_csrebackinfomation.SetWindowText(m_strrebackinfomation);

			AfxMessageBox("��λ��У��ʧ��!");
			
		}

		else
		{
			m_strrebackinfomation="����ʶ��ķ�������";
			
			m_csrebackinfomation.SetWindowText(m_strrebackinfomation);
		}
	}




	DispStatus();

	//������д�뵽�ı��ļ�
	if(judgefile)
	{
		//�ж��Ƿ�д���ļ�,�����ļ�,��ָ�붨���ļ�ĩβ
		if (b_fileopen==FALSE)
		{
			m_countertodispatch=Cframecounter;

			getdatafile.Open(m_savefilename,CFile::modeCreate+CFile::modeNoTruncate+CFile::modeWrite,&e);

			b_fileopen=TRUE;
		}

 		CString enter="\r\n";
		CString testall;
		int charlength;

 		getdatafile.SeekToEnd();   //��д��λ�ö�λ���ı�ĩβ

		testall=m_strcrcData+enter;

		charlength=testall.GetLength();

		getdatafile.Write(m_strcrcData+enter,50);
		
	}
	
	
	//֡���м���
	


	int lostframecounter;

	Cframecounter++;

	lostframecounter=Cframecounter-m_countertodispatch;

	if (1!=lostframecounter)
	{
		int m_resault; //ģ�����

		if (0==lostframecounter)
		{
			m_resault=256;
		}
		else
		{
			m_resault=lostframecounter % 255;
		}
		
		m_lostframe+=m_resault;
	}

	m_countertodispatch=Cframecounter;

//	SetEvent(hPostToWnd);//�����ٴη����¼�
	return TRUE;
}

*/
/*
int CTranslatorDlg::ReadBlock(BYTE *abIn, int MaxLength)
{
	BOOL JudgeRead;
	COMSTAT ComStat;
	DWORD dwErrorFlags,dwLength;

	ClearCommError(m_hCom,&dwErrorFlags,&ComStat);

	if(dwErrorFlags>0)
	{
		AfxMessageBox("�����ڴ�����������á�");

		PurgeComm(m_hCom,PURGE_RXABORT|PURGE_RXCLEAR);

		return 0;
	}

	dwLength=((DWORD)MaxLength<ComStat.cbInQue?MaxLength:ComStat.cbInQue);

	memset(abIn,0,MaxLength);

	//������ַ�������
	if(dwLength)
	{
		JudgeRead=ReadFile(m_hCom,abIn,dwLength,&dwLength,&m_osRead);//�����ַ���abIn��

		if(!JudgeRead)
		{
			//����ص�����δ���,�ȴ�ֱ���������
			if(GetLastError()==ERROR_IO_PENDING)
			{
				GetOverlappedResult(m_hCom,&m_osRead,&dwLength,TRUE);

				m_osRead.Offset=0;
			}
			else
			{
				dwLength=0;
			}
		}
	}

	return dwLength;
}
*/
/*
int CTranslatorDlg::WriteBlock(char *abOut, int MaxLength)
{
	BOOL JudgeWrite;
	COMSTAT ComStat;
	DWORD dwErrorFlags,dwLength,lentest;
	m_osWrite.Offset=0;

	ClearCommError(m_hCom,&dwErrorFlags,&ComStat);

	if(dwErrorFlags>0)
	{
		AfxMessageBox("д���ڴ�����������á�");
		AfxMessageBox("dwErrorFlags");
		PurgeComm(m_hCom,PURGE_TXABORT|PURGE_TXCLEAR);
		
		return 0;
	}

	dwLength=MaxLength;
	lentest=0;

	JudgeWrite=WriteFile(m_hCom,abOut,dwLength,&lentest,&m_osWrite);

	if(!JudgeWrite)
	{

		if(GetLastError()==ERROR_IO_PENDING)
		{
			GetOverlappedResult(m_hCom,&m_osWrite,&lentest,TRUE);
		}
		else
		{
			lentest=0;
		}
	}

	return lentest;
}
*/
void CTranslatorDlg::OnButtenMenualsend() 
{
	/*
	** �õ��˹��趨����д����ʼλ��,���������ַ���м��
	*/
	
	//�ȴ���λ��Ԥ���ź�
	CFileException e;

	m_bsendbutten=TRUE;

	
	if (m_filepath=="")
	{
		AfxMessageBox("����ѡ��������ļ�");
		return;
	}

	if (m_cansend==FALSE)
	{


		SetTimer(1,1000,NULL);
		return;
	}
	else
	{

		CString	m_sendstartaddresscheck="";
		int		m_intsendaddcheck=0;
		
		//GetDlgItem(IDC_EDIT_BINDATAADDRESS)->GetWindowText(m_senddatastartaddress);
		
		m_ceditstartaddress.GetWindowText(m_senddatastartaddress);
		
		if (""==m_senddatastartaddress)    //�յ�ַ���
		{
			
			AfxMessageBox("��������ʼ��ַ!");
			
			return;
			
			m_senddatastartaddress="0x00000000";
		}
		
		m_sendstartaddresscheck=m_senddatastartaddress.Left(2);	  //��ͷ���		
		
		if (m_sendstartaddresscheck!="0x")
		{
			AfxMessageBox("��ַ�����ԡ�0x����ͷ!");
			return;
		}
		
		m_intsendaddcheck=m_senddatastartaddress.GetLength();	//���ȼ��
		
		if (m_intsendaddcheck!=10)
		{
			AfxMessageBox("�����ַ���Ȳ����ϱ�׼!");
			return;
		}
		
		//��ʼ��ַ���䣬��ת��Ϊint�ͣ����ڵ�ַ����
		
		m_intstartaddress=CStringAddresstoInt(m_senddatastartaddress);

		KillTimer(1);
		KillTimer(3);
	}



	/*
	**��ȡ�˹��趨���ȴ�ʱ��
	*/

	GetDlgItem(IDC_EDIT_MAXTIMETOWAIT)->GetWindowText(m_strmaxtimetowait);
	m_intmaxtimetowait=atoi(m_strmaxtimetowait);

	/*
	**����˹��趨���ȴ�����
	*/

	GetDlgItem(IDC_EDIT_MAXTIMESTORESEND)->GetWindowText(m_strmaxtimetoresend);
	m_intmaxtimestowait=atoi(m_strmaxtimetoresend);
	
	//��ʼ���������ݼ�¼�ļ����ȴ�����ʱд��

	m_sendfile.Open(m_savesendrecoder,CFile::modeCreate+CFile::modeNoTruncate+CFile::modeWrite,&e);

	//��ʱ��4��ÿ����㷢��ʣ��ʱ�䲢��ʾ

	SetTimer(4,1000,NULL);

	Sendbinarydata();

	//���͹��������а�ťʧЧ״̬
	Allfuctiondiabled();
	SetTimer(2,PACKAGELAP,NULL); //��ʼ�Զ����ͣ������20ms
	m_dealframe=TRUE;
	m_firsttime=FALSE;
	return;

}

//�ַ�ת��Ϊ16������ʾ��ʽ
int CTranslatorDlg::String2Hex(CString str, char *SendOut)
{
	int hexdata,lowhexdata; 
	int hexdatalen=0;
	int len=str.GetLength();
	for(int i=0;i<len;)
	{
		char lstr,hstr=str[i];
		if(hstr==' '||hstr=='\r'||hstr=='\n')
		{
			i++;

			continue;
		}
		i++;
		if (i>=len)
		{
			break;
		}
		lstr=str[i];
		hexdata=ConvertHexData(hstr);

		lowhexdata=ConvertHexData(lstr);

		if((hexdata==16)||(lowhexdata==16))
		{
			break;
		}
		else
		{
			hexdata=hexdata*16+lowhexdata;
		}

		i++;

		SendOut[hexdatalen]=(char)hexdata;

		hexdatalen++;
	}

	return hexdatalen;
}

void CTranslatorDlg::OnButtonTransfile() //ѡ���ļ���ť�¼�����
{
	m_strstartaddress="0x00000000";
	m_ceditstartaddress.SetWindowText(m_strstartaddress);
	m_bgeo=FALSE;
	CFileDialog mFileDlg(TRUE, NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , "CON�ļ�(*.con)|*.con|All Files (*.*)|*.*|", AfxGetMainWnd());

    if(mFileDlg.DoModal()==IDOK)
	{

        m_strTXData.Empty();//��ʼ����ʾ�ļ�����

        m_edittxdata.SetWindowText(m_strTXData);

	    m_filepath=mFileDlg.GetPathName();//������ʾ·������

		CString m_strxie="\\";
		CString m_strxiexie="\\\\";
		
		m_filepath.Replace(m_strxie,m_strxiexie);	//��һ����б���滻Ϊ˫б��
		
		m_sFilePath.SetWindowText(m_filepath);

		if (m_filepath=="")
		{
			AfxMessageBox("�ļ�·��Ϊ�գ���ȡ�ļ�·��ʧ��!");

			return;
		}

		

		FILE * m_bfilep=fopen(m_filepath,"ab+");
		
		if (m_bfilep==NULL)
		{
			AfxMessageBox("���ļ�ʧ��!");
		}

		long int m_filepos = ftell(m_bfilep);
		
		fseek(m_bfilep,0,SEEK_END);
		
		m_filepos = ftell(m_bfilep);

		m_binfilelenth=m_filepos;

		m_binfilelenthtocalulate=m_binfilelenth;

		fseek(m_bfilep,0,SEEK_SET);
		
		m_strcounterforlefttosend.Format("%d",m_filepos);
		
		m_cscounterforlefttosend.SetWindowText(m_strcounterforlefttosend);

		m_strcounterforallbytesend.Format("%d",m_filepos);
		
		m_cscounterforallbytesend.SetWindowText(m_strcounterforallbytesend);

		if ((m_filepos%DATALENTH)!=0)
		{
			AfxMessageBox("�ļ���С�����Ϸ����ļ���ʽ,�ļ��ֽ�������Ϊ960��������!");
		}

			/*
		**�������ݰ�����
		*/

		//����

		if (m_filepos%60==0)
		{
			m_strcounterfordataall.Format("%d",m_filepos/60);
			m_intcounterdatanum=m_filepos/60;
			m_strcounterfordataall.Format("%d",m_intcounterdatanum);
		}
		//������
		else
		{
			int	m_dataresidu=0;
			int m_datatoadd=0;
			int	m_datanum=0;
			m_dataresidu=m_filepos%60;
			m_datatoadd=60-m_dataresidu;
			m_datanum=m_filepos+m_datatoadd;
			m_intcounterdatanum=m_datanum/60;
			m_strcounterfordataall.Format("%d",m_intcounterdatanum);
		}
	
		m_cscounterfordataall.SetWindowText(m_strcounterfordataall);


		m_cscounterforleftdata.SetWindowText(m_strcounterfordataall);

		m_cscounterforframeindata.SetWindowText("0");
		
		m_cscounterforcurrentsend.SetWindowText("0");

		fclose(m_bfilep);

		
	}


}

void CTranslatorDlg::OnCheckAutosend() 
{
	m_bAutoSend=!m_bAutoSend;

	if(m_bAutoSend)
	{
		SetTimer(1,1000,NULL);
	}
	else
	{
		KillTimer(1);
	}
}

void CTranslatorDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	switch(nIDEvent)
	{
		case 1:
			//����ready�źţ��ȴ���λ������
			SendReadySignal();
			break;
		case 2:
			Sendbinarydata();
			//KillTimer(2);
			break;
		case 3:
			OnButtenMenualsend();
			KillTimer(3);
			break;
		case 4:
			//��������ʱ����ʾ�����
			TimeCalculate();
			break;
		case 5:
			{
				ReceiveCom();
				break;
			}
		case 6:
			{
				SendCom();
				break;
			}

		default:
			AfxMessageBox("�޷��ҵ��Ķ�ʱ��!");

	}


	

	CDialog::OnTimer(nIDEvent);
}

void CTranslatorDlg::OnButtonEmptytext() 
{
	// TODO: Add your control notification handler code here
	/*
	m_strTXData.Empty();

	m_edittxdata.SetWindowText(m_strTXData);	
	*/

	if (m_binfilelenthtocalulate<=m_binreadcounter)
	{
		//�ϳɲ����ͽ���֡
		Sleep(200);
		Composeresendoverframe();
		KillTimer(2);
		AfxMessageBox("���ݷ������!");
		Allfuctionabled();
	}
}

void CTranslatorDlg::OnCheckWritetofile() 
{
	// TODO: Add your control notification handler code here
	AfxMessageBox("�˹����ѽ���!");
// 	if(m_judgesend.GetCheck())
// 	{
//         mkdir("d:\\readertest");
// 	   	m_savefilename="d:\\readertest\\reader.txt";
// 	}
// 	else
// 	{
// 		m_savefilename.Empty();
// 	}

//	GetDlgItem(IDC_STATIC_FILENAME)->SetWindowText(m_savefilename);
}

void CTranslatorDlg::OnButtonFilename() 
{
	// TODO: Add your control notification handler code here
	if(!m_judgesend.GetCheck())
	{
	   AfxMessageBox("��δָ��д�뵽�ļ��");
	}
	else
	{
       CFileDialog savefiledlg(FALSE,"txt",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , "�ı��ļ�(*.txt)|*.txt| |", AfxGetMainWnd());

       if(savefiledlg.DoModal()==IDOK)
	   {
		   m_savefilename=savefiledlg.GetPathName();

		   GetDlgItem(IDC_STATIC_FILENAME)->SetWindowText(m_savefilename);
	   }
	}	
}

void CTranslatorDlg::OnButtonSaveedit() 
{
	// TODO: Add your control notification handler code here
    CFile getdatafile;
    CFileException e;

	m_EditRXData.GetWindowText(m_strRXData);

	if(m_savefilename.IsEmpty())
	{
		AfxMessageBox("��ѡ�����ļ�����");
	}
	else
	{
		getdatafile.Open(m_savefilename,CFile::modeCreate+CFile::modeNoTruncate+CFile::modeWrite,&e);

		getdatafile.Write(m_strRXData,m_strRXData.GetLength());

		getdatafile.Close();
	}	
}

void CTranslatorDlg::OnButtonEmptyrx() 
{
	// TODO: Add your control notification handler code here
	m_strexceldisplay.Empty();
	m_editexceldata.SetWindowText(m_strexceldisplay);

}

void CTranslatorDlg::OnButtonPortstatu() 
{
	// TODO: Add your control notification handler code here
/*
	m_portstatu_but=!m_portstatu_but;

	if(!m_portstatu_but)
	{
		GetDlgItem(IDC_BUTTON_PORTSTATU)->SetWindowText("���ڴ�");
		m_bConnected=1;

		CString strStatus;
		
		//�򿪴���1
		if (m_Port[0].InitPort(this, m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits,m_dwCommEvents,51200))
		{
			m_Port[0].StartMonitoring();
			strStatus.Format(" STATUS��COM%d is connected,%d,%c,%d,%d",m_nCom, m_nBaud,m_cParity,m_nDatabits,m_nStopbits);
			//m_ctrlPortStatus.SetWindowText(strStatus);
			//m_ctrlIconOpenoff.SetIcon(m_hIconRed);
			//"��ǰ״̬�����ڴ򿪣�����żУ�飬8����λ��1ֹͣλ");
			m_bConnected=1;
		}
		else
		{
			strStatus.Format(" STATUS��COM%d Lost or Occupied!",m_nCom);
			//m_ctrlPortStatus.SetWindowText(strStatus);
			//m_ctrlIconOpenoff.SetIcon(m_hIconOff);
			AfxMessageBox(strStatus);
			m_bConnected=0;
		}
	}
	else
	{
		GetDlgItem(IDC_BUTTON_PORTSTATU)->SetWindowText("���ڹر�");
		//m_Port[0].StartMonitoring();
		m_bConnected=0;
		//m_Port[0].StopMonitoring();
		m_Port[0].ClosePort();
	}
    //OnSelchangeComboSeriou();

	DispStatus();
*/
	return;
}

void CTranslatorDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	//CloseConnection();
	OnButtenMenualsend(); 
	//CDialog::OnOK();	
}

void CTranslatorDlg::CloseConnection()
{
	if(!m_bConnected)
		return;
	m_bConnected=FALSE;
	/*
//	SetEvent(m_hPostMsgEvent);
//	SetEvent(m_osRead.hEvent);
	SetCommMask(m_hCom,0);
//	SetEvent(m_osRead.hEvent);
//	AfxMessageBox("out");
	WaitForSingleObject(m_pThread->m_hThread,INFINITE);
//	AfxMessageBox("yes");
	m_pThread=NULL;
	CloseHandle(m_hCom);

	*/
//	m_Port[0].StopMonitoring();
	m_Port[0].ClosePort();
	DispStatus();
}

void CTranslatorDlg::DispStatus()
{
	CWnd *static_status=GetDlgItem(IDC_STATIC_PORTSTATU);
	CWnd *static_txlen=GetDlgItem(IDC_STATIC_TXLEN);
	CWnd *static_rxlen=GetDlgItem(IDC_STATIC_RXLEN);
	CWnd *static_crclen=GetDlgItem(IDC_STATIC_CRCFAILD);
	CWnd *static_counterlen=GetDlgItem(IDC_STATIC_COUNTER);
	CWnd *static_lostframelen=GetDlgItem(IDC_STATIC_LOSTFRAME);
    CString status_str,txlen_str,rxlen_str,crclen_str,counter_str,lostframe_str;
	if(m_bConnected)
	{
	    status_str="STATUS:"+m_SeriouStr+" OPENED,"+m_BaudStr+','+m_JiaoyanStr+','+m_DataStr+','+m_StopStr;
	}
    else
	{
        status_str="STATUS:"+m_SeriouStr+" CLOSED,"+m_BaudStr+','+m_JiaoyanStr+','+m_DataStr+','+m_StopStr;
	}
    static_status->SetWindowText(status_str);

	txlen_str.Format("TX:%ld",m_txlen);

	static_txlen->SetWindowText(txlen_str);

	rxlen_str.Format("RX:%ld",m_rxdatalenth);

	static_rxlen->SetWindowText(rxlen_str);

	crclen_str.Format("У��ʧ��:%ld",m_crclen);

	static_crclen->SetWindowText(crclen_str);

	counter_str.Format("������:%ld",m_counter);

	static_counterlen->SetWindowText(counter_str);

	lostframe_str.Format("��֡��:%ld",m_lostframe);

	static_lostframelen->SetWindowText(lostframe_str);

}

void CTranslatorDlg::OnSelchangeComboBaud() 
{
	// TODO: Add your control notification handler code here
	int baudindex;
	baudindex=m_ComboBaud.GetCurSel();

	if(baudindex!=CB_ERR)
	{
		SetCommParameter();

		m_ComboBaud.GetLBText(baudindex,m_BaudStr);

		DispStatus();
	}
}

void CTranslatorDlg::OnSelchangeComboData() 
{
	// TODO: Add your control notification handler code here
	int dataindex;
	dataindex=m_ComboData.GetCurSel();

	if(dataindex!=CB_ERR)
	{
		SetCommParameter();

		m_ComboData.GetLBText(dataindex,m_DataStr);

		DispStatus();
	}
}

char CTranslatorDlg::ConvertHexData(char ch)
{
	if((ch>='0')&&(ch<='9'))
		return ch-0x30; //1��ASCIIΪ0x31
	if((ch>='A')&&(ch<='F'))
		return ch-'A'+10;
	if((ch>='a')&&(ch<='f'))
		return ch-'a'+10;
    else return(-1);
}

void CTranslatorDlg::OnSelchangeComboJiaoyan() 
{
	// TODO: Add your control notification handler code here
	int jiaoyanindex;
	jiaoyanindex=m_ComboJiaoyan.GetCurSel();

	if(jiaoyanindex!=CB_ERR)
	{
		SetCommParameter();

		m_ComboJiaoyan.GetLBText(jiaoyanindex,m_JiaoyanStr);

		DispStatus();
	}
}

void CTranslatorDlg::OnSelchangeComboStop() 
{
	// TODO: Add your control notification handler code here
	int stopindex;
	stopindex=m_ComboStop.GetCurSel();

	if(stopindex!=CB_ERR)
	{
		SetCommParameter();

		m_ComboStop.GetLBText(stopindex,m_StopStr);

		DispStatus();
	}
}

void CTranslatorDlg::OnSelchangeComboWorkstatus() 
{
	// TODO: Add your control notification handler code here
//	int workstatusindex=0;
//	workstatusindex=m_ComboWorkerstatus.GetCurSel();

// 	if(workstatusindex!=CB_ERR)
// 	{
// 		m_ComboWorkerstatus.GetLBText(workstatusindex,m_Workerstatustr);
// 
// 		if (workstatusindex==0&&m_Workerstatustr=="��������")
// 		{
// 			m_sendworks=0x80;
// 		}
// 		else if (workstatusindex==1&&m_Workerstatustr=="����״̬")
// 		{
// 			m_sendworks=0x40;
// 		}
// 		else if (workstatusindex==2&&m_Workerstatustr=="����֡")
// 		{
// 			m_sendworks=0xc0;
// 		}
// 		
// 	}
}

void CTranslatorDlg::OnSelchangeComboReaddistance() 
{
	// TODO: Add your control notification handler code here
// 	int readdistanceindex;
// 	readdistanceindex=m_ComboReaddistance.GetCurSel();
// 
// 	if(readdistanceindex!=CB_ERR)
// 	{
// 		m_ComboReaddistance.GetLBText(readdistanceindex,m_Readdistancestr);
// 
// 		if ((readdistanceindex==0)&&(m_Readdistancestr=="���"))
// 		{
// 			m_sendreadd=0x30;
// 		}
// 		else if (readdistanceindex==1&&m_Readdistancestr=="��")
// 		{
// 			m_sendreadd=0x20;
// 		}
// 		else if (readdistanceindex==2&&m_Readdistancestr=="С")
// 		{
// 			m_sendreadd=0x10;
// 		}
// 		else if (readdistanceindex==3&&m_Readdistancestr=="��С")
// 		{
// 			m_sendreadd=0x00;
// 		}
// 	}

	
}

void CTranslatorDlg::OnSelchangeComboBuzzer() 
{
	// TODO: Add your control notification handler code here
//	int buzzerindex;
//	buzzerindex=m_ComboBuzzer.GetCurSel();

// 	if(buzzerindex!=CB_ERR)
// 	{
// 		m_ComboBuzzer.GetLBText(buzzerindex,m_Buzzerstr);
// 		
// 		if (buzzerindex==0&&m_Buzzerstr=="��������")
// 		{
// 			m_sendbuzz=0x01;
// 		}
// 		else if (buzzerindex==1&&m_Buzzerstr=="������")
// 		{
// 			m_sendbuzz=0x00;
// 		}
// 	}
}

void CTranslatorDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

void CTranslatorDlg::OnButtonReset() 
{
	// TODO: Add your control notification handler code here
	
	m_rxlen=0;
	m_txlen=0;
	m_crclen=0;
	m_counter=0;
	m_lostframe=0;

	DispStatus();
	
	//SetTimer(2,2000,NULL);
	//Sendbinarydata();
}
unsigned short int CTranslatorDlg::Get_CRC16_Code(unsigned char* pchMsg, unsigned short int wDataLen)
{
	unsigned int CRC;
	unsigned char m_crc[22];
	BYTE m_low,m_high;
	BYTE m_word;
	//ת���ַ�����
	for (int i=0,j=0;i<44,j<22;i++,j++)
	{
		m_high=ConvertHexData(pchMsg[i++]);
		m_low=ConvertHexData(pchMsg[i]);
		m_word=m_high<<4;
		m_word+=m_low;
		m_crc[j]=m_word;
	}

	CRC  = crc16(m_crc, wDataLen);
	
	return CRC;
}
//������ѭ��0-255
int CTranslatorDlg::Counters()
{
	if (255!=m_counters)
	{
		m_counters++;
	}
	else
	{
		m_counters=0;
	}

	return m_counters;
}


int CTranslatorDlg::crc16(unsigned char *pchMsg,unsigned int wDataLen)
{
 unsigned  int wCRCTalbeAbs[] =
	{
		0x0000, 0xCC01, 0xD801, 0x1400, 0xF001, 
		0x3C00, 0x2800, 0xE401, 0xA001, 0x6C00, 
		0x7800, 0xB401, 0x5000, 0x9C01, 0x8801, 
		0x4400
	};
	unsigned  int wCRC = 0xFFFF;
	unsigned  int i = 0;
	unsigned char chChar = 0;
	
	for (i = 0; i < wDataLen; i++)
	{
		chChar = *pchMsg++;
		wCRC = wCRCTalbeAbs[(chChar ^ wCRC) & 15] ^ (wCRC >> 4);
		wCRC = wCRCTalbeAbs[((chChar >> 4) ^ wCRC) & 15] ^ (wCRC >> 4);
	}
	
	return wCRC;

}


void CTranslatorDlg::OnButtonExcelselect() 
{
	// TODO: Add your control notification handler code here
	
	
	CFileDialog mFileDlg(TRUE, NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , "EXCEL�ļ�(*.xls)|*.xls|EXCEL2007�ļ�(*.xlsx)|*.xlsx|All Files (*.*)|*.*|", AfxGetMainWnd());
	
    if(mFileDlg.DoModal()==IDOK)
	{

		m_EXCELfilepath=mFileDlg.GetPathName();//������ʾ·������
		
		m_sEXCELFilePath.SetWindowText(m_EXCELfilepath);

	}
}

/*
**	�˺�����ʼ������������
*/

void CTranslatorDlg::OnButtonExceltobin() 
{
	// TODO: Add your control notification handler code here
	// �û�����д���ļ�·�����ļ�����
	
	if (m_EXCELfilepath=="")
	{
		AfxMessageBox("����ѡ��EXCEL��ʽ�����ļ�!");
		return;
	}
	//���ö������ļ�·��
	long m_lbinpstart;
	long m_lbinpend;
	long m_lbinpcur;
	long m_lbinpoffset=0;
	CString m_pathforwrite;
	CString m_blank="    ";
	m_pathforwrite=Setbinarypath();
	if (m_pathforwrite=="")
	{
		return;
	}
	//����·�������������ļ�
	CString m_strxie="\\";
	CString m_strxiexie="\\\\";
	m_pathforwrite.Replace(m_strxie,m_strxiexie);	//��һ����б���滻Ϊ˫б��
	m_strbinfilepath=m_pathforwrite;
	m_sbinfilepath.SetWindowText(m_strbinfilepath);
	//��ʼд������ǰ�����ȴ򿪶������ļ�
	//����·�������������ļ�,
	FILE * m_filepfirst;
	m_filepfirst=fopen(m_pathforwrite,"wb+");
	fclose(m_filepfirst);
	if (m_fileopen==FALSE)
	{
		m_fileopen=TRUE;
	}
	//�û����ȡ���󣬺���ֱ�ӷ���
	if (m_EXCELfilepath=="")
	{
		AfxMessageBox("����ѡ���ļ�!");
		return ;
	}
	else
	{
		//ϵͳʱ������д���ļ�����ʱ��
		//д���ļ�����ʱ��10-17�ֽ�
		WORD m_wordtime=0;
		WORD m_wordadd=0;
		
		SYSTEMTIME  m_systime;
		GetLocalTime(&m_systime);



		//EXCEL ����
		_Application ExcelApp;  // EXCEL Ӧ�ó���
		Workbooks m_wbsBooks;  
		_Workbook m_wbBook;  
		Worksheets m_wsssheets;  
		_Worksheet m_wssheet;  
		Range m_rgRge;  
		//		VARIANT m_vexceldate;
		COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		if (!ExcelApp.CreateDispatch("Excel.Application",NULL))  
		{  
			AfxMessageBox("����Excel����ʧ��!");  
			exit(1);  
		}  
		//		ExcelApp.SetVisible(TRUE);          //ʹExcel�ɼ�,���Զ��򿪴�EXCEL�ļ�
		ExcelApp.SetUserControl(TRUE);      //���������û�����Excel
		// 		���Ѵ��ڵ�Excel�ļ���Sheet
		m_wbsBooks=ExcelApp.GetWorkbooks();
		m_wbBook=m_wbsBooks.Open(m_EXCELfilepath,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional);
		m_wsssheets=m_wbBook.GetWorksheets();
		//����������ѡ���һ��������һ�㶨��Ϊ��һ����ΪATP�������ݣ��ڶ�����ΪATO�������ݣ���������Ϊ��������
		WORD	m_sheet1addall=0;
		WORD	m_sheet2addall=0;
		WORD	m_sheet3addall=0;
		for (int nSheetNumber=1;nSheetNumber<=3;nSheetNumber++)
		{
			//��ʾ��ǰ�ڼ��ű�
			m_strcounterforsheets.Format("%d",nSheetNumber);
			m_cscounterforsheets.SetWindowText(m_strcounterforsheets);
			//���ö������ļ�ָ��λ�ã�����ñ�д����ٸ��ֽ�����
			FILE * m_filep;
			m_filep=fopen(m_pathforwrite,"ab+");
			fseek(m_filep,0,SEEK_END);			//���ļ�ָ�붨λ���ļ���β
			m_lbinpstart=ftell(m_filep);
			//��ȡ�Ѿ�ʹ���������Ϣ�������Ѿ�ʹ�õ���������������ʼ�С���ʼ��
			m_wssheet=m_wsssheets.GetItem(COleVariant((short)nSheetNumber));
			Range usedRange;
			usedRange.AttachDispatch(m_wssheet.GetUsedRange());
			m_rgRge.AttachDispatch(usedRange.GetRows());
			long iRowNum=m_rgRge.GetCount();                   //�Ѿ�ʹ�õ�����
			m_rgRge.AttachDispatch(usedRange.GetColumns());
			long iColNum=m_rgRge.GetCount();                   //�Ѿ�ʹ�õ�����
			long iStartRow=usedRange.GetRow();               //��ʹ���������ʼ�У���1��ʼ
			long iStartCol=usedRange.GetColumn();            //��ʹ���������ʼ�У���1��ʼ
			//�����ܱ��С
			long m_longcounterforleft=3*(iRowNum-1);
			m_strcounterforleft.Format("%d",m_longcounterforleft);
			m_cscounterforleft.SetWindowText(m_strcounterforleft);
			//�Ա��С�����жϣ��Ƿ���Ϸ���Ϊ�������ݵı���ʽ
			//ѭ����ȡEXCEL�е�ֵ����ת����ʽΪ�������ļ�����д�뵽�������ļ��У��ӵڶ��к͵ڶ��п�ʼ��ȡ��ֻ��ȡ��������
			for (iStartRow=2;iStartRow<=iRowNum;iStartRow++)
			{
				//��ʾ��ǰ�ڼ���
				m_strcounterforrows.Format("%d",iStartRow);
				m_cscounterforrows.SetWindowText(m_strcounterforrows);
				//�ж��Ƿ���д���ļ�����ʱ��λ�ã�λ��Ϊ�����ű�ĵ�17��
				//����
				if ((nSheetNumber==3)&&(iStartRow==17))
				{
					//����
					m_wordtime=m_systime.wMinute;
					m_wordtime=m_wordtime<<8;
					m_wordtime+=m_systime.wSecond;
					m_wordadd=m_wordtime;
					fseek(m_filep,0x079E,SEEK_SET);
					fwrite(&m_wordtime,1,2,m_filep);
					m_sheet3addall=Calculateaddall(m_sheet3addall,m_wordtime,2);
					continue;
				}
				//��ʱ
				if ((nSheetNumber==3)&&(iStartRow==18))
				{
					//��ʱ
					m_wordtime=m_systime.wDay;
					m_wordtime=m_wordtime<<8;
					m_wordtime+=m_systime.wHour;
					m_wordadd+=m_wordtime;
					fseek(m_filep,0x07A0,SEEK_SET);
					fwrite(&m_wordtime,1,2,m_filep);
					m_sheet3addall=Calculateaddall(m_sheet3addall,m_wordtime,2);
					continue;
				}
				//����
				if ((nSheetNumber==3)&&(iStartRow==19))
				{
					//����
					m_wordtime=m_systime.wYear-2000;
					m_wordtime=m_wordtime<<8;
					m_wordtime+=m_systime.wMonth;
					m_wordadd+=m_wordtime;
					fseek(m_filep,0x07A2,SEEK_SET);
					fwrite(&m_wordtime,1,2,m_filep);
					m_sheet3addall=Calculateaddall(m_sheet3addall,m_wordtime,2);
					continue;
				}
				//У���
				if ((nSheetNumber==3)&&(iStartRow==20))
				{
					fseek(m_filep,0x07A4,SEEK_SET);
					fwrite(&m_wordadd,1,2,m_filep);
					m_sheet3addall=Calculateaddall(m_sheet3addall,m_wordadd,2);
					continue;
				}
				//ÿ�п�ʼ��ȡʱ��ʼ������
				CString str="";			//��Ԫ������
				CString m_str;
				DOUBLE		m_double=0;		
				DOUBLE		m_dvalue=0;			//��ֵ	
				short int m_size=0;		//ռ���ֽ���
				int		m_multiple=0;		//�Ŵ���
				for (iStartCol=2;iStartCol<=5;iStartCol++)
				{
					//��ʾ��ǰ�ڼ���
					m_strcounterforcols.Format("%d",iStartCol);
					m_cscounterforcols.SetWindowText(m_strcounterforcols);
					//������Ϊ����Ҫ��ֵ��ֱ������
					if (iStartCol==4)
					{
						continue;
					}
					m_rgRge.AttachDispatch(m_wssheet.GetCells()); 
					m_rgRge.AttachDispatch(m_rgRge.GetItem (COleVariant((long)iStartRow),COleVariant((long)iStartCol)).pdispVal );
					COleVariant vResult =m_rgRge.GetValue2();
					if(vResult.vt == VT_BSTR)       //�ַ���
					{
						//�ַ�������Ϊ�汾�ţ����汾�ŵ�ĩβ��λ����ת��Ϊ�����Ʋ�����
						if (nSheetNumber!=3)
						{
							CString m_strversion;
							str=vResult.bstrVal;
							m_strversion=str.Right(2);
							m_double=strtoul((LPCTSTR)m_strversion,NULL,16);
						} 
						else
						{
							str=vResult.bstrVal;
							m_str=str;
						}
						//����������б�������
						if (2==iStartCol)
						{
							m_dvalue=m_double;
						}
						else if (3==iStartCol)
						{
							m_size=m_double;
						}
						else if (5==iStartCol)
						{
							m_multiple=m_double;
						}
						//��ʾ
						m_strexceldisplay+=str;
						m_strexceldisplay+=m_blank;
					}
					else if (vResult.vt==VT_R8)     //8�ֽڵ����� 
					{
						m_double=vResult.dblVal;
						//����������б�������
						if (2==iStartCol)
						{
							m_dvalue=m_double;
						}
						else if (3==iStartCol)
						{
							m_size=m_double;
						}
						else if (5==iStartCol)
						{
							m_multiple=m_double;
						}
						str.Format("%f",vResult.dblVal);
						m_strexceldisplay+=str;
						m_strexceldisplay+=m_blank;
					}
					else if(vResult.vt==VT_DATE)    //ʱ���ʽ
					{
						SYSTEMTIME st;
						VariantTimeToSystemTime(vResult.date, &st);
					}
					else if(vResult.vt==VT_EMPTY)   //��Ԫ��յ�
					{
						str="";
					}  
					//��ʾʣ�෭��������
					m_longcounterforleft--; 
					m_strcounterforleft.Format("%d",m_longcounterforleft);
					m_cscounterforleft.SetWindowText(m_strcounterforleft);
				}
				//��ȡһ���еı��������󣬿�ʼ����洢�ռ�
				int	m_inttostore;
				if ((nSheetNumber==3)&&(iStartRow>=154)&&(iStartRow<=203))
				{
					m_inttostore=strtoul(m_str,NULL,16);
				}
				else
				{
					m_inttostore=m_dvalue*m_multiple;         //����洢ʱ��ֵ
				}
				//д�������ֵ
				if (m_fileopen==TRUE)
				{
					switch (m_size)
					{
					case 0:
						{
							break;
						}
					case 1:
						{
							BYTE	m_bytetowritebin=0;
							m_bytetowritebin=m_inttostore;
							fwrite(&m_bytetowritebin,1,m_size,m_filep);
							fflush(m_filep);
							if(nSheetNumber==1)
							{
								m_sheet1addall=Calculateaddall(m_sheet1addall,m_bytetowritebin,1);
							}
							else if (nSheetNumber==2)
							{
								m_sheet2addall=Calculateaddall(m_sheet2addall,m_bytetowritebin,1);
							}
							else if (nSheetNumber==3)
							{
								m_sheet3addall=Calculateaddall(m_sheet3addall,m_bytetowritebin,1);
							}
							break;
						}
					case 2:
						{
							WORD	m_wordtowritebin=0;
							m_wordtowritebin=m_inttostore;
							if ((iStartRow==11)&&(nSheetNumber==1))
							{
								m_cgeoaddallcheck.GetWindowText(m_csgeoaddallcheck);
								if (m_csgeoaddallcheck!="")
								{
									m_inttostore=strtol(m_csgeoaddallcheck,0,16);
									m_wordtowritebin=m_inttostore;
								}
							}
							fwrite(&m_wordtowritebin,1,m_size,m_filep);
							fflush(m_filep);
							if(nSheetNumber==1)
							{
								m_sheet1addall=Calculateaddall(m_sheet1addall,m_wordtowritebin,2);
							}
							else if (nSheetNumber==2)
							{
								m_sheet2addall=Calculateaddall(m_sheet2addall,m_wordtowritebin,2);
							}
							else if (nSheetNumber==3)
							{
								m_sheet3addall=Calculateaddall(m_sheet3addall,m_wordtowritebin,2);
							}
							break;
						}
					case 4:
						{
							fwrite(&m_inttostore,1,m_size,m_filep);
							fflush(m_filep);
							if(nSheetNumber==1)
							{
								m_sheet1addall=Calculateaddall(m_sheet1addall,m_inttostore,4);
							}
							else if (nSheetNumber==2)
							{
								m_sheet2addall=Calculateaddall(m_sheet2addall,m_inttostore,4);
							}
							else if (nSheetNumber==3)
							{
								m_sheet3addall=Calculateaddall(m_sheet3addall,m_inttostore,4);
							}
							break;
						}
					default:
						AfxMessageBox("д�������ֽڳ��ȳ��ֲ���ʶ��ĳ���!");
					}
				}
				m_strexceldisplay+=m_return;
				m_editexceldata.SetWindowText(m_strexceldisplay);
				if (m_strexceldisplay.GetLength()>4096)
				{
					m_strexceldisplay.Empty();
				}
			}
			//���������е����ݺ��������ݳ���Ϊ960�ֽڣ������ֽں����������ֽ�Ϊ�������ݼӷ�У���
			fclose(m_filep);
			FILE * m_filep2;
			m_filep2=fopen(m_pathforwrite,"ab+");
			//���ļ�ָ��رպ�򿪣�����ָ�벻�ƶ�
			if(nSheetNumber==1)
			{
				fwrite(&m_sheet1addall,1,2,m_filep2);
			}
			else if (nSheetNumber==2)
			{
				fwrite(&m_sheet2addall,1,2,m_filep2);
			}
			else if (nSheetNumber==3)
			{
				fwrite(&m_sheet3addall,1,2,m_filep2);
				WORD m_sheetall=0;

				m_sheetall=Calculateaddall(m_sheetall,m_sheet1addall,2);
				m_sheetall=Calculateaddall(m_sheetall,m_sheet2addall,2);
				m_sheetall=Calculateaddall(m_sheetall,m_sheet3addall,2);
				fwrite(&m_sheetall,1,2,m_filep2);
			}
			fflush(m_filep2);
			//��ʼ������λ��
			WORD m_wordfillin=0xff;
			m_lbinpend=ftell(m_filep2);
			fseek(m_filep2,0,SEEK_END);
			m_lbinpend=ftell(m_filep2);
			m_lbinpcur=m_lbinpend-m_lbinpstart;
			int	m_looptimes=DATALENTH-m_lbinpcur;
			if (m_fileopen==TRUE)
			{
				while (m_looptimes>0)
				{
					fwrite(&m_wordfillin,1,1,m_filep2);
					fflush(m_filep2);
					m_looptimes--;
				}		
			}
			fclose(m_filep2);
		}
		//�ر��ļ�
		m_wbsBooks.Close();
		ExcelApp.Quit();
		//�ͷŶ���  
		m_rgRge.ReleaseDispatch();  
		m_wssheet.ReleaseDispatch();  
		m_wsssheets.ReleaseDispatch();  
		m_wbBook.ReleaseDispatch();  
		m_wbsBooks.ReleaseDispatch();  
		ExcelApp.ReleaseDispatch();  
	}
	if (m_fileopen==TRUE)
	{
		fcloseall();
		m_fileopen=FALSE;
	}
	AfxMessageBox("ת�����!");
}

int CTranslatorDlg::Cstringtobinary(CString str)
{
	/*
		�Ƚ���д�ļ��Ĳ��������һ�����ļ���û������ġ�
		��Ȼ��д�������ļ��������ļ���д��һ������ֵ��д�������ַ�ֻ��ʹ��write������
		����write������ԭ����write(const char * ch, int size)����һ��������char *���ͣ�������Ҫ�ѽ�Ҫд��
		�ļ���int����ת����char *���͡������ת���������Һü��죬��������Ū�����ˡ��������¡�
		int temp;
		file.write((char *)(&temp),sizeof(temp));
	*/
	int	m_iinttobin;
	m_iinttobin=atoi(str);

	return m_iinttobin;
}

BOOL CTranslatorDlg::Writebintofile(int inttowrite)
{

	
//	::fstream m_binfile(m_binfilefullpath,ios_base::in|ios_base::out|ios_base::app);
	
// 	if (m_fileopen==TRUE)
// 
// 	{
// 		m_binfile.seekg(ios_base::end);   // ��д��ָ�붨λ���ļ���β
// 
// 		m_binfile.write((char *)(&inttowrite),sizeof(inttowrite));
// 	}


	return TRUE;
}

CString CTranslatorDlg::Setbinarypath()
{
	//���û�ѡ��������ļ���ŵ�ַ

	BOOL kind = FALSE;
	CString typeName = "con",str = "con";
	char *pFilters = NULL;
	int rst = 0;
	
	char szfilters1[]="�������ݶ������ļ�(*.con)|";

	/*
	**�Զ����ɱ�������
	*/


	CString m_strsystemtime="";
	CString m_strfilename="";
	CTime t=CTime::GetCurrentTime();
	m_strsystemtime=t.Format("%Y-%m-%d.%H-%M-%S");
	

	str.Format("binary.%s",typeName);

	m_strfilename=m_strsystemtime+str;

	pFilters = szfilters1;

	CFileDialog dlgselectbinfilepath(kind,typeName,m_strfilename,OFN_HIDEREADONLY,pFilters);
	rst = dlgselectbinfilepath.DoModal();
	if(rst==IDOK)
	{
		m_binfilefullpath=dlgselectbinfilepath.GetPathName();
		
		m_strbinfilepath=m_binfilefullpath;
		
		m_sbinfilepath.SetWindowText(m_strbinfilepath);
	}
	else
	{
		// ����û���ָ��λ�ã���ô�ļ��Զ������ڳ���Ŀ¼��

		//m_binfilefullpath="C:\\Documents and Settings\\zhanghua\\����";
		
		return m_binfilefullpath="";
		
	}

	return m_binfilefullpath;
}

void CTranslatorDlg::Openbinfile()
{
// 	if (m_fileopen==FALSE)
// 	{
// 		::m_binfile(m_binfilefullpath,ios_base::in|ios_base::out|ios_base::app);
// 		m_fileopen=TRUE;
// 	}

}

void CTranslatorDlg::Closebinfile()
{
// 	if (m_fileopen==TRUE)
// 	{
// 		m_binfile.close();
// 		m_fileopen=FALSE;
// 	}

}

void CTranslatorDlg::OnButtonExceltobinlocation() 
{
	// TODO: Add your control notification handler code here
	if (m_EXCELfilepath=="")
	{
		AfxMessageBox("����ѡ��EXCEL��ʽ�����ļ�!");
		return;
	}

	/*
	**���ö������ļ�·��
	*/
	long m_lbinpstart;
//	long m_lbinpcur;
	long m_lbinpoffset=0;
	CString m_pathforwrite;
	CString m_blank="    ";
	m_pathforwrite=Geosetbinarypath();
		
	if (m_pathforwrite=="")
	{
		return;
	}

	/*
	**����·�������������ļ�
	*/

	CString m_strxie="\\";
	CString m_strxiexie="\\\\";


	m_pathforwrite.Replace(m_strxie,m_strxiexie);	//��һ����б���滻Ϊ˫б��

	m_strbinfilepath=m_pathforwrite;

	m_sbinfilepath.SetWindowText(m_strbinfilepath);


	FILE * m_filepfirst;
	
	m_filepfirst=fopen(m_pathforwrite,"wb+");
	
	fclose(m_filepfirst);
	
	if (m_fileopen==FALSE)
	{
		m_fileopen=TRUE;
	}



	/*
	**�û����ȡ���󣬺���ֱ�ӷ���
	*/

	if (m_EXCELfilepath=="")
	{
		AfxMessageBox("����ѡ���ļ�!");
		return ;
	}
	else
	{
		/*
		**EXCEL ����
		*/

		_Application ExcelApp;  // EXCEL Ӧ�ó���
		Workbooks m_wbsBooks;  
		_Workbook m_wbBook;  
		Worksheets m_wsssheets;  
		_Worksheet m_wssheet;  
		Range m_rgRge;  
		int		m_sheetsnumber;
		unsigned int m_uintaddall=0;
		CString m_sheetname;
		/*
		**д���־λ����ֹ����û�б�����д��
		*/

		BOOL m_Iswritein=FALSE;

		COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

		if (!ExcelApp.CreateDispatch("Excel.Application",NULL))  
		{  
			AfxMessageBox("����Excel����ʧ��!");  
			exit(1);  
		}  

//		ExcelApp.SetVisible(TRUE);          //ʹExcel�ɼ�,���Զ��򿪴�EXCEL�ļ�

		ExcelApp.SetUserControl(TRUE);      //���������û�����Excel

// 		���Ѵ��ڵ�Excel�ļ���Sheet

		m_wbsBooks=ExcelApp.GetWorkbooks();
			
		m_wbBook=m_wbsBooks.Open(m_EXCELfilepath,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional);
			
		m_wsssheets=m_wbBook.GetWorksheets();

		/*
		**�õ��ܱ�����ʾ��ѭ����ȡ
		*/

		m_sheetsnumber=m_wsssheets.GetCount();
		
		m_strcounterforsheets.Format("%d",m_sheetsnumber);

		m_cscounterforsheets.SetWindowText(m_strcounterforsheets);




		//����������ʼѡ���һ��������,�����������˵����

		for (int nSheetNumber=1;nSheetNumber<=(m_sheetsnumber-2);nSheetNumber++)
		{
			/*
			**��ʾ��ǰ�ڼ��ű�
			*/

			m_strcounterforsheets.Format("%d",nSheetNumber);
			
			m_cscounterforsheets.SetWindowText(m_strcounterforsheets);

			/*
			**���ö������ļ�ָ��λ�ã�����������ļ���С
			*/

			FILE * m_filep;
			
			m_filep=fopen(m_pathforwrite,"ab+");
			
			fseek(m_filep,0,SEEK_END);			//���ļ�ָ�붨λ���ļ���β
			
			m_lbinpstart=ftell(m_filep);


			//��ȡ�Ѿ�ʹ���������Ϣ�������Ѿ�ʹ�õ���������������ʼ�С���ʼ��

			m_wssheet=m_wsssheets.GetItem(COleVariant((short)nSheetNumber));

			m_sheetname=m_wssheet.GetName();

			Range usedRange;
			usedRange.AttachDispatch(m_wssheet.GetUsedRange());

			m_rgRge.AttachDispatch(usedRange.GetRows());
			long iRowNum=m_rgRge.GetCount();                   //�Ѿ�ʹ�õ�����
				
			m_rgRge.AttachDispatch(usedRange.GetColumns());
			long iColNum=m_rgRge.GetCount();                   //�Ѿ�ʹ�õ�����
				
			long iStartRow=usedRange.GetRow();               //��ʹ���������ʼ�У���1��ʼ
			long iStartCol=usedRange.GetColumn();            //��ʹ���������ʼ�У���1��ʼ

			/*
			**�����ܱ��С
			*/

			long m_longcounterforleft=53*(iRowNum-1);

			m_strcounterforleft.Format("%d",m_longcounterforleft);

			m_cscounterforleft.SetWindowText(m_strcounterforleft);

			long	m_counterforwriter=0;

			/*
			**�Ա��С�����жϣ��Ƿ���Ϸ���Ϊ�������ݵı���ʽ
			*/

			/*
			**ѭ����ȡEXCEL�е�ֵ����ת����ʽΪ�������ļ�����д�뵽�������ļ��У��ӵڶ��к͵ڶ��п�ʼ��ȡ��ֻ��ȡ��������
			*/

			for (iStartRow=2;iStartRow<=iRowNum;iStartRow++)
			{
				
				/*
				**��ʾ��ǰ�ڼ���
				*/
				m_strcounterforrows.Format("%d",iStartRow);

				m_cscounterforrows.SetWindowText(m_strcounterforrows);

				/*
				**	ÿ�п�ʼ��ȡʱ��ʼ������
				*/

				CString			m_strcontent="";		//��Ԫ������	
				unsigned int	m_uintcontentvalue=0;	//��ֵ	
				short int   	m_size=0;				//ռ���ֽ���
				

				m_uintaddall=0;


				for (iStartCol=2;iStartCol<=iColNum;iStartCol++)
				{

					/*
					**��ʾ��ǰ�ڼ���
					*/

					m_strcounterforcols.Format("%d",iStartCol);

					m_cscounterforcols.SetWindowText(m_strcounterforcols);


					/*
					**�������ʹ���ж���53�У�ֱ����������
					*/

					if (iStartCol>55)
					{
						continue;
					}


					/*
					**��ȡ��Ԫ������
					*/
	
					m_rgRge.AttachDispatch(m_wssheet.GetCells()); 

					m_rgRge.AttachDispatch(m_rgRge.GetItem (COleVariant((long)iStartRow),COleVariant((long)iStartCol)).pdispVal );

					COleVariant vResult =m_rgRge.GetValue2();

					m_Iswritein=FALSE;

					if(vResult.vt == VT_BSTR)       //�ַ���
					{

						/*
						**�ַ��������ÿ�е���Ϣ���д���
						*/
						
						m_strcontent=vResult.bstrVal;

						/*
						**��ʾ
						*/
						m_strexceldisplay+=m_strcontent;

					
						switch(iStartCol)
						{
							/*
							**������α��
							*/
							case 2:
							{
								unsigned int m_intrailwaynumber=0xffffffff;
								/*
								**16�������ַ���ת��Ϊ10��������
								*/
								m_intrailwaynumber=strtoul(m_strcontent,NULL,16);
								if ((0xffffffff==m_intrailwaynumber)|(m_strcontent.GetLength()!=10)|(m_strcontent.Left(2)!="0x"))
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								/*
								**ռ��4���ֽ�
								*/
								fwrite(&m_intrailwaynumber,1,4,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_intrailwaynumber,4);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**����λ
							*/
							case 3:
							{
								BYTE m_bytepoint=0xff;
								if (m_strcontent=="POINT_NOML")
								{
									m_bytepoint=POINT_NOML;
								}
								else if (m_strcontent=="POINT_REVES")
								{
									m_bytepoint=POINT_REVES;
								}
								if (m_bytepoint==0xff)
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								fwrite(&m_bytepoint,1,1,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_bytepoint,1);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**�����������
							*/
							case 4:
							{
								BYTE m_bytetracktype=0xff;
								if (m_strcontent=="TRACK_UP")
								{
									m_bytetracktype=TRACK_UP;
								}
								else if (m_strcontent=="TRACK_DOWN")
								{
									m_bytetracktype=TRACK_DOWN;
								}
								else if (m_strcontent=="TRACK_STATION_UP")
								{
									m_bytetracktype=TRACK_STATION_UP;
								}
								else if (m_strcontent=="TRACK_STATION_DOWN")
								{
									m_bytetracktype=TRACK_STATION_DOWN;
								}
								else if (m_strcontent=="TRACK_FERRY")
								{
									m_bytetracktype=TRACK_FERRY;
								}
								else if (m_strcontent=="TRACK_PARK")
								{
									m_bytetracktype=TRACK_PARK;
								}
								else if (m_strcontent=="TRACK_TURNBK")
								{
									m_bytetracktype=TRACK_TURNBK;
								}
								else if (m_strcontent=="TRACK_STATION")
								{
									m_bytetracktype=TRACK_STATION;
								}
								if (m_bytetracktype==0xff)
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								fwrite(&m_bytetracktype,1,1,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_bytetracktype,1);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**���������ͣ
							*/
							case 5:
							{
								BYTE m_byteskip=0xff;
								if (m_strcontent=="SKIP_INVALID")
								{
									m_byteskip=SKIP_INVALID;
								}
								else if (m_strcontent=="SKIP_VALID")
								{
									m_byteskip=SKIP_VALID;
								}
								else if (m_strcontent=="DATA_UNDEF")
								{
									m_byteskip=DATA_UNDEF;
								}
								if (m_byteskip==0xff)
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								fwrite(&m_byteskip,1,1,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_byteskip,1);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**��Ƶ
							*/
							case 12:
							{
								BYTE m_bytefrequency=0xff;
								/*
								**16�������ַ���ת��Ϊ10��������
								*/
								m_bytefrequency=strtoul(m_strcontent,NULL,16);
								if ((m_bytefrequency==0xff)|(m_strcontent.GetLength()!=4)|(m_strcontent.Left(2)!="0x"))
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								/*
								**ռ��1���ֽ�
								*/
								fwrite(&m_bytefrequency,1,1,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_bytefrequency,1);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**�����Ų�
							*/
							case 14:
							{
								BYTE m_byteopendoor=0xff;
								if (m_strcontent=="DOOR_FORBID")
								{
									m_byteopendoor=DOOR_FORBID;
								}
								else if (m_strcontent=="DOOR_ALL")
								{
									m_byteopendoor=DOOR_ALL;
								}
								else if (m_strcontent=="DOOR_RIGHT")
								{
									m_byteopendoor=DOOR_RIGHT;
								}
								else if (m_strcontent=="DOOR_LEFT")
								{
									m_byteopendoor=DOOR_LEFT;
								}
								else if (m_strcontent=="DATA_UNDEF")
								{
									m_byteopendoor=DATA_UNDEF;
								}
								if (m_byteopendoor==0xff)
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								fwrite(&m_byteopendoor,1,1,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_byteopendoor,1);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**�źŻ���Ч��
							*/
							case 16:
							{
								BYTE m_bytesignal=0xff;
								if (m_strcontent=="SIGLAMP_INVALID")
								{
									m_bytesignal=SIGLAMP_INVALID;
								}
								else if (m_strcontent=="SIGLAMP_VALID")
								{
									m_bytesignal=SIGLAMP_VALID;
								}
								if (m_bytesignal==0xff)
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								fwrite(&m_bytesignal,1,1,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_bytesignal,1);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**��Դ�ű���
							*/
							case 17:
							{
								unsigned int m_intnopowersignal=0xffffffff;
								/*
								**16�������ַ���ת��Ϊ10��������
								*/
								m_intnopowersignal=strtoul(m_strcontent,NULL,16);
								if ((m_intnopowersignal==0xffffffff)|(m_strcontent.GetLength()!=10)|(m_strcontent.Left(2)!="0x"))
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								/*
								**ռ��4���ֽ�
								*/
								fwrite(&m_intnopowersignal,1,4,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_intnopowersignal,4);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**19��Դ�ű���4
							*/
							case 19:
							{
								unsigned int m_intnopowersignal=0xffffffff;
								/*
								**16�������ַ���ת��Ϊ10��������
								*/
								m_intnopowersignal=strtoul(m_strcontent,NULL,16);
								if ((m_intnopowersignal==0xffffffff)|(m_strcontent.GetLength()!=10)|(m_strcontent.Left(2)!="0x"))
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								/*
								**ռ��4���ֽ�
								*/
								fwrite(&m_intnopowersignal,1,4,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_intnopowersignal,4);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**ǰ������������Դ�ű���
							*/
							case 21:
							{
								unsigned int m_uintdnopowersignalflag=0xffffffff;
								if ((m_strcontent=="")|(m_strcontent=="null")|(m_strcontent=="NULL"))
								{
									m_uintdnopowersignalflag=0x00;
								}			
								/*
								**16�������ַ���ת��Ϊ10��������
								*/
								m_uintdnopowersignalflag=strtoul(m_strcontent,NULL,16);
								if ((m_uintdnopowersignalflag==0xffffffff)|(m_strcontent.GetLength()!=10)|(m_strcontent.Left(2)!="0x"))
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								fwrite(&m_uintdnopowersignalflag,1,4,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_uintdnopowersignalflag,4);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**ǰ������������Դ�ű���
							*/
							case 22:
							{
								unsigned int m_uintrnopowersignalflag=0xffffffff;
								if ((m_strcontent=="")|(m_strcontent=="null")|(m_strcontent=="NULL"))
								{
									m_uintrnopowersignalflag=0x00;
								}
								/*
								**16�������ַ���ת��Ϊ10��������
								*/
								m_uintrnopowersignalflag=strtoul(m_strcontent,NULL,16);
								if ((m_uintrnopowersignalflag==0xffffffff)|(m_strcontent.GetLength()!=10)|(m_strcontent.Left(2)!="0x"))
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								fwrite(&m_uintrnopowersignalflag,1,4,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_uintrnopowersignalflag,4);
								m_uintaddall=m_uintforall;
								break;
							}

							/*
							**�󷽶���������Դ�ű���
							*/
							case 23:
							{
								unsigned int m_uintrnopowersignalflag=0xffffffff;
								if ((m_strcontent=="")|(m_strcontent=="null")|(m_strcontent=="NULL"))
								{
									m_uintrnopowersignalflag=0x00;
								}
								/*
								**16�������ַ���ת��Ϊ10��������
								*/
								m_uintrnopowersignalflag=strtoul(m_strcontent,NULL,16);
								if ((m_uintrnopowersignalflag==0xffffffff)|(m_strcontent.GetLength()!=10)|(m_strcontent.Left(2)!="0x"))
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								fwrite(&m_uintrnopowersignalflag,1,4,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_uintrnopowersignalflag,4);
								m_uintaddall=m_uintforall;
								break;
							}

							/*
							**�󷽷���������Դ�ű���
							*/
							case 24:
							{
								unsigned int m_uintrnopowersignalflag=0xffffffff;
								if ((m_strcontent=="")|(m_strcontent=="null")|(m_strcontent=="NULL"))
								{
									m_uintrnopowersignalflag=0x00;
								}
								/*
								**16�������ַ���ת��Ϊ10��������
								*/
								m_uintrnopowersignalflag=strtoul(m_strcontent,NULL,16);
								if ((m_uintrnopowersignalflag==0xffffffff)|(m_strcontent.GetLength()!=10)|(m_strcontent.Left(2)!="0x"))
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								fwrite(&m_uintrnopowersignalflag,1,4,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_uintrnopowersignalflag,4);
								m_uintaddall=m_uintforall;
								break;
							}
							//����TCE
							case 25:
								{
									BYTE m_bytetce=0xff;
									if (m_strcontent=="TCE")
									{
										m_bytetce=TCE;
									}
									else if (m_strcontent=="NOTCE")
									{
										m_bytetce=NOTCE;
									}
									if (m_bytetce==0xff)
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										fcloseall();
										return;
									}
									fwrite(&m_bytetce,1,1,m_filep);
									fflush(m_filep);
									/*
									**��ǰ��ȡ�ļ��Ѿ�д��
									*/
									m_Iswritein=TRUE;
									/*
									**����ӷ���
									*/
									unsigned int m_uintforall=0;
									m_uintforall=Calculateaddall(m_uintaddall,m_bytetce,1);
									m_uintaddall=m_uintforall;
									break;
								}
							/*
							**��Դ�ű���2
							*/
							case 26:
							{
								unsigned int m_intnopowersignal=0xffffffff;
								/*
								**16�������ַ���ת��Ϊ10��������
								*/
								m_intnopowersignal=strtoul(m_strcontent,NULL,16);
								if ((m_intnopowersignal==0xffffffff)|(m_strcontent.GetLength()!=10)|(m_strcontent.Left(2)!="0x"))
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								/*
								**ռ��4���ֽ�
								*/
								fwrite(&m_intnopowersignal,1,4,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_intnopowersignal,4);
								m_uintaddall=m_uintforall;
								break;
							}

							//Ԥ�����ִ��� 6�ֽ�
							/*
							case 26:
								{
									BYTE m_obligate=0xff;
									for (int loop=0;loop<6;loop++)
									{
										fwrite(&m_obligate,1,1,m_filep);
										fflush(m_filep);
										/*
										**��ǰ��ȡ�ļ��Ѿ�д��
										*/
										m_Iswritein=TRUE;
										/*
										**����ӷ���
										*/
										/*
										unsigned int m_uintforall=0;
										m_uintforall=Calculateaddall(m_uintaddall,m_obligate,1);
										m_uintaddall=m_uintforall;
									}
									break;
								}
							*/
							/*
							**74/73
							*/
							case 28:
							{
								BYTE m_byte=0xff;
								if ((m_strcontent=="")|(m_strcontent=="null")|(m_strcontent=="NULL"))
								{
									m_byte=0x00;
								}
								else if (m_strcontent=="74/73_4/4N")
								{
									m_byte=DTG4_4N;
								}
								else if (m_strcontent=="74/73_3/3N")
								{
									m_byte=DTG3_3N;
								}
								if (m_byte==0xff)
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;					
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);							
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";					
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  								
									fcloseall();
									return;
								}
								fwrite(&m_byte,1,1,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_byte,1);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**74/58
							*/
							case 29:
							{
								BYTE m_byte=0xff;
								if ((m_strcontent=="")|(m_strcontent=="null")|(m_strcontent=="NULL"))
								{
									m_byte=0x00;
								}
								else if (m_strcontent=="74/58_3/3N")
								{
									m_byte=DTG3_3N;
								}
								else if (m_strcontent=="74/58_2/2N")
								{
									m_byte=DTG2_2N;
								}
								else if (m_strcontent=="74/58_4/4N")
								{
									m_byte=DTG4_4N;
								}
								if (m_byte==0xff)
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								fwrite(&m_byte,1,1,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_byte,1);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**59/58
							*/
							case 30:
							{
								BYTE m_byte=0xff;
								if ((m_strcontent=="")|(m_strcontent=="null")|(m_strcontent=="NULL"))
								{
									m_byte=0x00;
								}
								else if (m_strcontent=="59/58_3/3N")
								{
									m_byte=DTG3_3N;
								}
								else if (m_strcontent=="59/58_4/4N")
								{
									m_byte=DTG4_4N;
								}
								else if (m_strcontent=="59/58_2/2N")
								{
									m_byte=DTG2_2N;
								}
								if (m_byte==0xff)
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;							
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);								
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";							
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  					
									fcloseall();
									return;
								}
								fwrite(&m_byte,1,1,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_byte,1);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**59/37
							*/
							case 31:
							{
								BYTE m_byte=0xff;
								if ((m_strcontent=="")|(m_strcontent=="null")|(m_strcontent=="NULL"))
								{
									m_byte=0x00;
								}
								else if (m_strcontent=="59/37_2/2N")
								{
									m_byte=DTG2_2N;
								}
								else if (m_strcontent=="59/37_2/1N")
								{
									m_byte=DTG2_1N;
								}
								else if (m_strcontent=="59/37_3/3N")
								{
									m_byte=DTG3_3N;
								}
								else if (m_strcontent=="59/37_4/4N")
								{
									m_byte=DTG4_4N;
								}
								else if (m_strcontent=="59/37_2/1R2")
								{
									m_byte=DTG2_1R2;
								}
								if (m_byte==0xff)
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;								
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);							
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";						
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  					
									fcloseall();
									return;
								}
								fwrite(&m_byte,1,1,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_byte,1);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**38/37
							*/
							case 32:
							{
								BYTE m_byte=0xff;
								if ((m_strcontent=="")|(m_strcontent=="null")|(m_strcontent=="NULL"))
								{
									m_byte=0x00;
								}
								else if (m_strcontent=="38/37_2/1N")
								{
									m_byte=DTG2_1N;
								}
								else if (m_strcontent=="38/37_2/1R2")
								{
									m_byte=DTG2_1R2;
								}
								else if (m_strcontent=="38/37_2/2N")
								{
									m_byte=DTG2_2N;
								}
								else if (m_strcontent=="38/37_2/2R1")
								{
									m_byte=DTG2_2R1;
								}
								else if (m_strcontent=="38/37_1/1N")
								{
									m_byte=DTG1_1N;
								}
								if (m_byte==0xff)
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;							
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);								
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";				
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch(); 							
									fcloseall();
									return;
								}
								fwrite(&m_byte,1,1,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_byte,1);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**38/27
							*/
							case 33:
							{
								BYTE m_byte=0xff;
								if ((m_strcontent=="")|(m_strcontent=="null")|(m_strcontent=="NULL"))
								{
									m_byte=0x00;
								}
								else if (m_strcontent=="38/27_2/1R2")
								{
									m_byte=DTG2_1R2;
								}
								else if (m_strcontent=="38/27_2/2NS")
								{
									m_byte=DTG2_2NS;
								}
								else if (m_strcontent=="38/27_2/1N")
								{
									m_byte=DTG2_1N;
								}
								else if (m_strcontent=="38/27_1/1N")
								{
									m_byte=DTG1_1N;
								}
								else if (m_strcontent=="38/27_2/2R1")
								{
									m_byte=DTG2_2R1;
								}
								else if (m_strcontent=="38/27_2/2N")
								{
									m_byte=DTG2_2N;
								}

								if (m_byte==0xff)
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;							
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);								
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";						
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  								
									fcloseall();
									return;
								}
								fwrite(&m_byte,1,1,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_byte,1);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**38/0
							*/
							case 34:
							{
								BYTE m_byte=0xff;
								if ((m_strcontent=="")|(m_strcontent=="null")|(m_strcontent=="NULL"))
								{
									m_byte=0x00;
								}
								else if (m_strcontent=="38/0_1/0N")
								{
									m_byte=DTG1_0N;
								}
								else if (m_strcontent=="38/0_1/1N")
								{
									m_byte=DTG1_1N;
								}
								else if (m_strcontent=="38/0_2/1N")
								{
									m_byte=DTG2_1N;
								}
								else if (m_strcontent=="38/0_2/2N")
								{
									m_byte=DTG2_2N;
								}
								else if (m_strcontent=="38/0_4/4N")
								{
									m_byte=DTG4_4N;
								}
								else if (m_strcontent=="38/0_3/3N")
								{
									m_byte=DTG3_3N;
								}
								if (m_byte==0xff)
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;								
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);						
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";							
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  							
									fcloseall();
									return;
								}
								fwrite(&m_byte,1,1,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_byte,1);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**28/27
							*/
							case 35:
							{
								BYTE m_byte=0xff;
								if ((m_strcontent=="")|(m_strcontent=="null")|(m_strcontent=="NULL"))
								{
									m_byte=0x00;
								}
								else if (m_strcontent=="28/27_1/1NS")
								{
									m_byte=DTG1_1NS;
								}
								else if (m_strcontent=="28/27_2/2NS")
								{
									m_byte=DTG2_2NS;
								}
								else if (m_strcontent=="28/27_2/1N")
								{
									m_byte=DTG2_1N;
								}
								else if (m_strcontent=="28/27_2/1R2")
								{
									m_byte=DTG2_1R2;
								}
								else if (m_strcontent=="28/27_2/2N")
								{
									m_byte=DTG2_2N;
								}
								else if (m_strcontent=="28/27_2/2R1")
								{
									m_byte=DTG2_2R1;
								}
								else if (m_strcontent=="28/27_3/3N")
								{
									m_byte=DTG3_3N;
								}
								else if (m_strcontent=="28/27_4/4N")
								{
									m_byte=DTG4_4N;
								}
								if (m_byte==0xff)
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;								
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);								
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";							
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								fwrite(&m_byte,1,1,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_byte,1);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**28/19
							*/
							case 36:
							{
								BYTE m_byte=0xff;
								if ((m_strcontent=="")|(m_strcontent=="null")|(m_strcontent=="NULL"))
								{
									m_byte=0x00;
								}
								else if (m_strcontent=="28/19_2/1N")
								{
									m_byte=DTG2_1N;
								}
								if (m_byte==0xff)
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;								
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);								
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
																		
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
																		
									fcloseall();
									return;
								}
								fwrite(&m_byte,1,1,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;

								m_uintforall=Calculateaddall(m_uintaddall,m_byte,1);
								
								m_uintaddall=m_uintforall;

								break;
							}
							/*
							**28/0
							*/

							case 37:
							{
								BYTE m_byte=0xff;
								
								if ((m_strcontent=="")|(m_strcontent=="null")|(m_strcontent=="NULL"))
								{
									m_byte=0x00;
								}
								else if (m_strcontent=="28/0_1/0N")
								{
									m_byte=DTG1_0N;
								}
								else if (m_strcontent=="28/0_1/0R1")
								{
									m_byte=DTG1_0R1;
								}
								else if (m_strcontent=="28/0_2/1N")
								{
									m_byte=DTG2_1N;
								}
								if (m_byte==0xff)
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
																		
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
																		
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
																		
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
																		
									fcloseall();
									return;
								}
								fwrite(&m_byte,1,1,m_filep);
								
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;

								m_uintforall=Calculateaddall(m_uintaddall,m_byte,1);
								
								m_uintaddall=m_uintforall;

								break;
							}
							/*
							**20/0
							*/
							case 38:
							{
								BYTE m_byte=0xff;
								
								if ((m_strcontent=="")|(m_strcontent=="null")|(m_strcontent=="NULL"))
								{
									m_byte=0x00;
								}
								else if (m_strcontent=="20/0_1/0N")
								{
									m_byte=DTG1_0N;
								}
								else if (m_strcontent=="20/0_1/1N")
								{
									m_byte=DTG1_1N;
								}
								if (m_byte==0xff)
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
																		
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
																		
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
																		
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
																		
									fcloseall();
									return;
								}
								fwrite(&m_byte,1,1,m_filep);
								
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;

								m_uintforall=Calculateaddall(m_uintaddall,m_byte,1);
								
								m_uintaddall=m_uintforall;

								break;
							}
							/*
							**0/0
							*/
							case 39:
							{
								BYTE m_byte=0xff;
								
								if ((m_strcontent=="")|(m_strcontent=="null")|(m_strcontent=="NULL"))
								{
									m_byte=0x00;
								}
								else if (m_strcontent=="0/0_0/0N")
								{
									m_byte=DTG0_0N;
								}
								else if (m_strcontent=="0/0_1/1N")
								{
									m_byte=DTG1_1N;
								}
								else if (m_strcontent=="0/0_3/3N")
								{
									m_byte=DTG1_1N;
								}
								else if (m_strcontent=="0/0_4/4N")
								{
									m_byte=DTG4_4N;
								}

								if (m_byte==0xff)
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
																		
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
																		
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
																		
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
																		
									fcloseall();
									return;
								}
								fwrite(&m_byte,1,1,m_filep);
								
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;

								m_uintforall=Calculateaddall(m_uintaddall,m_byte,1);
								
								m_uintaddall=m_uintforall;

								break;
							}
							/*
							**��Դ�ű���3
							*/
							case 40:
							{
								unsigned int m_intnopowersignal=0xffffffff;
								/*
								**16�������ַ���ת��Ϊ10��������
								*/
								m_intnopowersignal=strtoul(m_strcontent,NULL,16);
								if ((m_intnopowersignal==0xffffffff)|(m_strcontent.GetLength()!=10)|(m_strcontent.Left(2)!="0x"))
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								/*
								**ռ��4���ֽ�
								*/
								fwrite(&m_intnopowersignal,1,4,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_intnopowersignal,4);
								m_uintaddall=m_uintforall;
								break;
							}
							//Ԥ��
							case 42:
								{
									WORD m_obligate=0xffff;

										fwrite(&m_obligate,1,2,m_filep);
										fflush(m_filep);
										/*
										**��ǰ��ȡ�ļ��Ѿ�д��
										*/
										m_Iswritein=TRUE;
										/*
										**����ӷ���
										*/
										unsigned int m_uintforall=0;
										m_uintforall=Calculateaddall(m_uintaddall,m_obligate,2);
										m_uintaddall=m_uintforall;
									
									break;
								}
							/*
							**������Դ�ű���1
							*/
							case 43:
							{
								unsigned int m_intnopowersignal=0xffffffff;
								/*
								**16�������ַ���ת��Ϊ10��������
								*/
								m_intnopowersignal=strtoul(m_strcontent,NULL,16);
								if ((m_intnopowersignal==0xffffffff)|(m_strcontent.GetLength()!=10)|(m_strcontent.Left(2)!="0x"))
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								/*
								**ռ��4���ֽ�
								*/
								fwrite(&m_intnopowersignal,1,4,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_intnopowersignal,4);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**������Դ�ű���2
							*/
							case 45:
							{
								unsigned int m_intnopowersignal=0xffffffff;
								/*
								**16�������ַ���ת��Ϊ10��������
								*/
								m_intnopowersignal=strtoul(m_strcontent,NULL,16);
								if ((m_intnopowersignal==0xffffffff)|(m_strcontent.GetLength()!=10)|(m_strcontent.Left(2)!="0x"))
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								/*
								**ռ��4���ֽ�
								*/
								fwrite(&m_intnopowersignal,1,4,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_intnopowersignal,4);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**������Դ�ű���3
							*/
							case 47:
							{
								unsigned int m_intnopowersignal=0xffffffff;
								/*
								**16�������ַ���ת��Ϊ10��������
								*/
								m_intnopowersignal=strtoul(m_strcontent,NULL,16);
								if ((m_intnopowersignal==0xffffffff)|(m_strcontent.GetLength()!=10)|(m_strcontent.Left(2)!="0x"))
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								/*
								**ռ��4���ֽ�
								*/
								fwrite(&m_intnopowersignal,1,4,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_intnopowersignal,4);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**������Դ�ű���4
							*/
							case 49:
							{
								unsigned int m_intnopowersignal=0xffffffff;
								/*
								**16�������ַ���ת��Ϊ10��������
								*/
								m_intnopowersignal=strtoul(m_strcontent,NULL,16);
								if ((m_intnopowersignal==0xffffffff)|(m_strcontent.GetLength()!=10)|(m_strcontent.Left(2)!="0x"))
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								/*
								**ռ��4���ֽ�
								*/
								fwrite(&m_intnopowersignal,1,4,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_intnopowersignal,4);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**������Դ�ű���5
							*/
							case 51:
							{
								unsigned int m_intnopowersignal=0xffffffff;
								/*
								**16�������ַ���ת��Ϊ10��������
								*/
								m_intnopowersignal=strtoul(m_strcontent,NULL,16);
								if ((m_intnopowersignal==0xffffffff)|(m_strcontent.GetLength()!=10)|(m_strcontent.Left(2)!="0x"))
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								/*
								**ռ��4���ֽ�
								*/
								fwrite(&m_intnopowersignal,1,4,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_intnopowersignal,4);
								m_uintaddall=m_uintforall;
								break;
							}
							/*
							**ATO��·���
							*/
							case 53:
							{
								unsigned int m_intnopowersignal=0xffffffff;
								/*
								**16�������ַ���ת��Ϊ10��������
								*/
								m_intnopowersignal=strtoul(m_strcontent,NULL,16);
								if ((m_intnopowersignal==0xffffffff)|(m_strcontent.GetLength()!=10)|(m_strcontent.Left(2)!="0x"))
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									fcloseall();
									return;
								}
								/*
								**ռ��4���ֽ�
								*/
								fwrite(&m_intnopowersignal,1,4,m_filep);
								fflush(m_filep);
								/*
								**��ǰ��ȡ�ļ��Ѿ�д��
								*/
								m_Iswritein=TRUE;
								/*
								**����ӷ���
								*/
								unsigned int m_uintforall=0;
								m_uintforall=Calculateaddall(m_uintaddall,m_intnopowersignal,4);
								m_uintaddall=m_uintforall;
								break;
							}
							//Ԥ��10
							case 55:
								{
									WORD m_obligate=0xffff;
									for (int loop=0;loop<5;loop++)
									{
										fwrite(&m_obligate,1,2,m_filep);
										fflush(m_filep);
										/*
										**��ǰ��ȡ�ļ��Ѿ�д��
										*/
										m_Iswritein=TRUE;
										/*
										**����ӷ���
										*/
										unsigned int m_uintforall=0;
										m_uintforall=Calculateaddall(m_uintaddall,m_obligate,2);
										m_uintaddall=m_uintforall;
									}
									break;
								}
						}
	
					}
					else if (vResult.vt==VT_R8)     //8�ֽڵ����� 
					{
						m_uintcontentvalue=vResult.dblVal;
						/*
						**��ʾ
						*/

						CString m_uinttostr="";

						m_uinttostr.Format("%d",m_uintcontentvalue);

						m_strexceldisplay+=m_uinttostr;

						/*
						**����������б�������
						*/
						
						switch (iStartCol)
						{
							/*
							**���������꣨cm��
							*/
							case 6:
								{
									if ((m_uintcontentvalue>0xffffffff)|(m_uintcontentvalue<0))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										return;
									}
									fwrite(&m_uintcontentvalue,1,4,m_filep);
									fflush(m_filep);
									/*
									**��ǰ��ȡ�ļ��Ѿ�д��
									*/
									m_Iswritein=TRUE;

									/*
									**����ӷ���
									*/
									unsigned int m_uintforall=0;

									m_uintforall=Calculateaddall(m_uintaddall,m_uintcontentvalue,4);
									
									m_uintaddall=m_uintforall;

									break;
								}

								/*
								**���γ��ȣ�cm��
								*/
							case 7:
								{

									if ((m_uintcontentvalue>0xffff)|(m_uintcontentvalue<0))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										return;
									}



									WORD	m_wordcontendvalue=0;

									m_wordcontendvalue=m_uintcontentvalue;


									fwrite(&m_wordcontendvalue,1,2,m_filep);
									
									fflush(m_filep);

									
									/*
									**��ǰ��ȡ�ļ��Ѿ�д��
									*/
									m_Iswritein=TRUE;

									/*
									**����ӷ���
									*/
									unsigned int m_uintforall=0;

									m_uintforall=Calculateaddall(m_uintaddall,m_uintcontentvalue,2);
									
									m_uintaddall=m_uintforall;

									break;
								}

								/*
								**������㵽���ĳ��ȣ�cm��
								*/

							case 8:
								{
									if ((m_uintcontentvalue>0xffff)|(m_uintcontentvalue<0))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										return;
									}


									WORD	m_wordcontendvalue=0;
									
									m_wordcontendvalue=m_uintcontentvalue;
									
									
									fwrite(&m_wordcontendvalue,1,2,m_filep);
									
									fflush(m_filep);

									/*
									**��ǰ��ȡ�ļ��Ѿ�д��
									*/
									m_Iswritein=TRUE;

									/*
									**����ӷ���
									*/
									unsigned int m_uintforall=0;

									m_uintforall=Calculateaddall(m_uintaddall,m_uintcontentvalue,2);
									
									m_uintaddall=m_uintforall;
									break;
								}

								/*
								**ͣ�������꣨cm��
								*/	
							case 9:
								{
									if ((m_uintcontentvalue>0xffff)|(m_uintcontentvalue<0))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										return;
									}

									WORD	m_wordcontendvalue=0;
									
									m_wordcontendvalue=m_uintcontentvalue;
									
									
									fwrite(&m_wordcontendvalue,1,2,m_filep);
									
									fflush(m_filep);

									/*
									**��ǰ��ȡ�ļ��Ѿ�д��
									*/
									m_Iswritein=TRUE;

									/*
									**����ӷ���
									*/
									unsigned int m_uintforall=0;

									m_uintforall=Calculateaddall(m_uintaddall,m_uintcontentvalue,2);
									
									m_uintaddall=m_uintforall;

									break;
								}
								/*
								**����¶�������־
								*/	
							case 10:
								{
									if ((m_uintcontentvalue>0xff)|(m_uintcontentvalue<0))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										return;
									}
									BYTE	m_bytecontendvalue=0;
									m_bytecontendvalue=m_uintcontentvalue;
									fwrite(&m_bytecontendvalue,1,1,m_filep);
									
									fflush(m_filep);

									/*
									**��ǰ��ȡ�ļ��Ѿ�д��
									*/
									m_Iswritein=TRUE;

									/*
									**����ӷ���
									*/
									unsigned int m_uintforall=0;

									m_uintforall=Calculateaddall(m_uintaddall,m_uintcontentvalue,1);
									
									m_uintaddall=m_uintforall;

									break;
								}
								/*
								**����¶�
								*/	
							case 11:
								{
									if ((m_uintcontentvalue>0xff)|(m_uintcontentvalue<0))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										return;
									}

									BYTE	m_bytecontendvalue=0;
									
									m_bytecontendvalue=m_uintcontentvalue;
									
									
									fwrite(&m_bytecontendvalue,1,1,m_filep);
									
									fflush(m_filep);

									
									/*
									**��ǰ��ȡ�ļ��Ѿ�д��
									*/
									m_Iswritein=TRUE;
									/*
									**����ӷ���
									*/
									unsigned int m_uintforall=0;

									m_uintforall=Calculateaddall(m_uintaddall,m_uintcontentvalue,1);
									
									m_uintaddall=m_uintforall;

									break;
								}
								/*
								**�������٣�km/h��
								*/	
							case 13:
								{
									if ((m_uintcontentvalue>0xff)|(m_uintcontentvalue<0))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										fcloseall();
										return;
									}
									BYTE	m_bytecontendvalue=0;
									m_bytecontendvalue=m_uintcontentvalue;
									fwrite(&m_bytecontendvalue,1,1,m_filep);
									fflush(m_filep);
									/*
									**��ǰ��ȡ�ļ��Ѿ�д��
									*/
									m_Iswritein=TRUE;
									/*
									**����ӷ���
									*/
									unsigned int m_uintforall=0;
									m_uintforall=Calculateaddall(m_uintaddall,m_uintcontentvalue,1);
									m_uintaddall=m_uintforall;
									break;
								}
								/*
								**�źŻ����꣨cm��
								*/
							case 15:
								{			
									if ((m_uintcontentvalue>0xffff)|(m_uintcontentvalue<0))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										fcloseall();
										return;
									}
									WORD	m_wordcontendvalue=0;
									m_wordcontendvalue=m_uintcontentvalue;
									fwrite(&m_wordcontendvalue,1,2,m_filep);
									fflush(m_filep);
									/*
									**��ǰ��ȡ�ļ��Ѿ�д��
									*/
									m_Iswritein=TRUE;
									/*
									**����ӷ���
									*/
									unsigned int m_uintforall=0;
									m_uintforall=Calculateaddall(m_uintaddall,m_uintcontentvalue,2);
									m_uintaddall=m_uintforall;
									break;
								}
								/*
								**��Դ�ű����꣨cm��
								*/
							case 18:
								{

									if ((m_uintcontentvalue>0xffff)|(m_uintcontentvalue<0))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										return;
									}

									WORD	m_wordcontendvalue=0;
									
									m_wordcontendvalue=m_uintcontentvalue;
									
									
									fwrite(&m_wordcontendvalue,1,2,m_filep);
									
									fflush(m_filep);

									/*
									**��ǰ��ȡ�ļ��Ѿ�д��
									*/
									m_Iswritein=TRUE;
									/*
									**����ӷ���
									*/
									unsigned int m_uintforall=0;

									m_uintforall=Calculateaddall(m_uintaddall,m_uintcontentvalue,2);
									
									m_uintaddall=m_uintforall;
									break;
								}

								/*
								**��Դ�ű����꣨cm��
								*/
							case 20:
								{
									if ((m_uintcontentvalue>0xffff)|(m_uintcontentvalue<0))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										return;
									}


									WORD	m_wordcontendvalue=0;
									
									m_wordcontendvalue=m_uintcontentvalue;
									
									
									fwrite(&m_wordcontendvalue,1,2,m_filep);
									
									fflush(m_filep);
									/*
									**��ǰ��ȡ�ļ��Ѿ�д��
									*/
									m_Iswritein=TRUE;

									/*
									**����ӷ���
									*/
									unsigned int m_uintforall=0;

									m_uintforall=Calculateaddall(m_uintaddall,m_uintcontentvalue,2);
									
									m_uintaddall=m_uintforall;

									break;
								}
								//��ԴAPR2λ��
								case 27:
								{

									if ((m_uintcontentvalue>0xffff)|(m_uintcontentvalue<0))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										return;
									}

									WORD	m_wordcontendvalue=0;
									
									m_wordcontendvalue=m_uintcontentvalue;
									
									
									fwrite(&m_wordcontendvalue,1,2,m_filep);
									
									fflush(m_filep);

									/*
									**��ǰ��ȡ�ļ��Ѿ�д��
									*/
									m_Iswritein=TRUE;
									/*
									**����ӷ���
									*/
									unsigned int m_uintforall=0;

									m_uintforall=Calculateaddall(m_uintaddall,m_uintcontentvalue,2);
									
									m_uintaddall=m_uintforall;
									break;
								}
								//��ԴAPR3λ��
								case 41:
								{

									if ((m_uintcontentvalue>0xffff)|(m_uintcontentvalue<0))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										return;
									}

									WORD	m_wordcontendvalue=0;
									
									m_wordcontendvalue=m_uintcontentvalue;
									
									
									fwrite(&m_wordcontendvalue,1,2,m_filep);
									
									fflush(m_filep);

									/*
									**��ǰ��ȡ�ļ��Ѿ�д��
									*/
									m_Iswritein=TRUE;
									/*
									**����ӷ���
									*/
									unsigned int m_uintforall=0;

									m_uintforall=Calculateaddall(m_uintaddall,m_uintcontentvalue,2);
									
									m_uintaddall=m_uintforall;
									break;
								}
							
							//��һ��Ԥ�����ִ��� 8�ֽ�
							case 42:
								{
									BYTE m_obligate=0xff;
									for (int loop=0;loop<2;loop++)
									{
										fwrite(&m_obligate,1,1,m_filep);
										fflush(m_filep);
										/*
										**��ǰ��ȡ�ļ��Ѿ�д��
										*/
										m_Iswritein=TRUE;
										/*
										**����ӷ���
										*/
										unsigned int m_uintforall=0;
										m_uintforall=Calculateaddall(m_uintaddall,m_obligate,1);
										m_uintaddall=m_uintforall;
									}
									break;
								}

								//������ԴAPR1λ��
								case 44:
								{

									if ((m_uintcontentvalue>0xffff)|(m_uintcontentvalue<0))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										return;
									}

									WORD	m_wordcontendvalue=0;
									
									m_wordcontendvalue=m_uintcontentvalue;
									
									
									fwrite(&m_wordcontendvalue,1,2,m_filep);
									
									fflush(m_filep);

									/*
									**��ǰ��ȡ�ļ��Ѿ�д��
									*/
									m_Iswritein=TRUE;
									/*
									**����ӷ���
									*/
									unsigned int m_uintforall=0;

									m_uintforall=Calculateaddall(m_uintaddall,m_uintcontentvalue,2);
									
									m_uintaddall=m_uintforall;
									break;
								}

								//������ԴAPR2λ��
								case 46:
								{

									if ((m_uintcontentvalue>0xffff)|(m_uintcontentvalue<0))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										return;
									}

									WORD	m_wordcontendvalue=0;
									
									m_wordcontendvalue=m_uintcontentvalue;
									
									
									fwrite(&m_wordcontendvalue,1,2,m_filep);
									
									fflush(m_filep);

									/*
									**��ǰ��ȡ�ļ��Ѿ�д��
									*/
									m_Iswritein=TRUE;
									/*
									**����ӷ���
									*/
									unsigned int m_uintforall=0;

									m_uintforall=Calculateaddall(m_uintaddall,m_uintcontentvalue,2);
									
									m_uintaddall=m_uintforall;
									break;
								}

								//������ԴAPR3λ��
								case 48:
								{

									if ((m_uintcontentvalue>0xffff)|(m_uintcontentvalue<0))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										return;
									}

									WORD	m_wordcontendvalue=0;
									
									m_wordcontendvalue=m_uintcontentvalue;
									
									
									fwrite(&m_wordcontendvalue,1,2,m_filep);
									
									fflush(m_filep);

									/*
									**��ǰ��ȡ�ļ��Ѿ�д��
									*/
									m_Iswritein=TRUE;
									/*
									**����ӷ���
									*/
									unsigned int m_uintforall=0;

									m_uintforall=Calculateaddall(m_uintaddall,m_uintcontentvalue,2);
									
									m_uintaddall=m_uintforall;
									break;
								}
								//������ԴAPR4λ��
								case 50:
								{

									if ((m_uintcontentvalue>0xffff)|(m_uintcontentvalue<0))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										return;
									}

									WORD	m_wordcontendvalue=0;
									
									m_wordcontendvalue=m_uintcontentvalue;
									
									
									fwrite(&m_wordcontendvalue,1,2,m_filep);
									
									fflush(m_filep);

									/*
									**��ǰ��ȡ�ļ��Ѿ�д��
									*/
									m_Iswritein=TRUE;
									/*
									**����ӷ���
									*/
									unsigned int m_uintforall=0;

									m_uintforall=Calculateaddall(m_uintaddall,m_uintcontentvalue,2);
									
									m_uintaddall=m_uintforall;
									break;
								}
								//������ԴAPR5λ��
								case 52:
								{

									if ((m_uintcontentvalue>0xffff)|(m_uintcontentvalue<0))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										return;
									}

									WORD	m_wordcontendvalue=0;
									
									m_wordcontendvalue=m_uintcontentvalue;
									
									
									fwrite(&m_wordcontendvalue,1,2,m_filep);
									
									fflush(m_filep);

									/*
									**��ǰ��ȡ�ļ��Ѿ�д��
									*/
									m_Iswritein=TRUE;
									/*
									**����ӷ���
									*/
									unsigned int m_uintforall=0;

									m_uintforall=Calculateaddall(m_uintaddall,m_uintcontentvalue,2);
									
									m_uintaddall=m_uintforall;
									break;
								}
								//ATO��·λ��
								case 54:
								{

									if ((m_uintcontentvalue>0xffff)|(m_uintcontentvalue<0))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										return;
									}

									WORD	m_wordcontendvalue=0;
									
									m_wordcontendvalue=m_uintcontentvalue;
									
									
									fwrite(&m_wordcontendvalue,1,2,m_filep);
									
									fflush(m_filep);

									/*
									**��ǰ��ȡ�ļ��Ѿ�д��
									*/
									m_Iswritein=TRUE;
									/*
									**����ӷ���
									*/
									unsigned int m_uintforall=0;

									m_uintforall=Calculateaddall(m_uintaddall,m_uintcontentvalue,2);
									
									m_uintaddall=m_uintforall;
									break;
								}
							//�ڶ���Ԥ�����ִ��� 10�ֽ�
							case 55:
								{
									BYTE m_obligate=0xff;
									for (int loop=0;loop<10;loop++)
									{
										fwrite(&m_obligate,1,1,m_filep);
										fflush(m_filep);
										/*
										**��ǰ��ȡ�ļ��Ѿ�д��
										*/
										m_Iswritein=TRUE;
										/*
										**����ӷ���
										*/
										unsigned int m_uintforall=0;
										m_uintforall=Calculateaddall(m_uintaddall,m_obligate,1);
										m_uintaddall=m_uintforall;
									}
									break;
								}
						}
						
						m_strcontent.Format("%f",vResult.dblVal);

						m_strexceldisplay+=m_strcontent;

						if (m_strexceldisplay.GetLength()>1024)
						{
							m_strexceldisplay.Empty();
						}
						
					}
					else if(vResult.vt==VT_DATE)    //ʱ���ʽ
					{
						SYSTEMTIME st;
						VariantTimeToSystemTime(vResult.date, &st);
					}
					else if(vResult.vt==VT_EMPTY)   //��Ԫ��յ�
					{
						/*
						**�˲�������д��ȫ��Ϊ0���������ӷ���
						*/
						if (iStartCol>=25)
						{
							BYTE m_byte=0x00;
							fwrite(&m_byte,1,1,m_filep);
							fflush(m_filep);
							/*
							**��ǰ��ȡ�ļ��Ѿ�д��
							*/
							m_Iswritein=TRUE;
						}
						else 
						{
								CString m_warning="�����ļ�ʱ��������λ���ڵ� ";
								CString m_colnum;
								CString m_rownum;
								CString m_sheetnum;
								
								m_colnum.Format("%d",iStartCol);
								m_rownum.Format("%d",iStartRow);
								m_sheetnum.Format("%d",nSheetNumber);

								m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";

								AfxMessageBox(m_warning);

								//�ر��ļ�
								m_wbsBooks.Close();
								ExcelApp.Quit();
								//�ͷŶ���  
								m_rgRge.ReleaseDispatch();  
								m_wssheet.ReleaseDispatch();  
								m_wsssheets.ReleaseDispatch();  
								m_wbBook.ReleaseDispatch();  
								m_wbsBooks.ReleaseDispatch();  
								ExcelApp.ReleaseDispatch();  
								fcloseall();
								return;
						}
					}  

					if (m_Iswritein==FALSE)
					{
						AfxMessageBox("�����ļ�д�����û���ҵ����ʵ��ļ�����!����Ҫ������ļ������·���!");
						CString m_warning="�����ļ�ʱ��������λ���ڵ� ";
						CString m_colnum;
						CString m_rownum;
						CString m_sheetnum;
						
						m_colnum.Format("%d",iStartCol);
						m_rownum.Format("%d",iStartRow);
						m_sheetnum.Format("%d",nSheetNumber);
						
						m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
						
						AfxMessageBox(m_warning);
						
						//�ر��ļ�
						m_wbsBooks.Close();
						ExcelApp.Quit();
						//�ͷŶ���  
						m_rgRge.ReleaseDispatch();  
						m_wssheet.ReleaseDispatch();  
						m_wsssheets.ReleaseDispatch();  
						m_wbBook.ReleaseDispatch();  
						m_wbsBooks.ReleaseDispatch();  
						ExcelApp.ReleaseDispatch();  
						
						fcloseall();
						return;
					}

					/*
					**��ʾʣ�෭��������
					*/
					m_longcounterforleft--; 

					m_strcounterforleft.Format("%d",m_longcounterforleft);
					
					m_cscounterforleft.SetWindowText(m_strcounterforleft);
				
				}
			if (m_strexceldisplay!="")
			{
				m_editexceldata.SetWindowText(m_strexceldisplay);
			}
			
			/*
			**�ӷ���д�룬ʵ�ַ�ʽֱ�Ӽ���
			*/
			fwrite(&m_uintaddall,1,2,m_filep);
			fflush(m_filep);
			}
		}

	
			//�ر��ļ�
			m_wbsBooks.Close();
			ExcelApp.Quit();
			//�ͷŶ���  
			m_rgRge.ReleaseDispatch();  
			m_wssheet.ReleaseDispatch();  
			m_wsssheets.ReleaseDispatch();  
			m_wbBook.ReleaseDispatch();  
			m_wbsBooks.ReleaseDispatch();  
			ExcelApp.ReleaseDispatch();  
	}

	 	if (m_fileopen==TRUE)
	 	{
	 		fcloseall();
	 		m_fileopen=FALSE;
	 	}

	AfxMessageBox("ת�����!");

}

void CTranslatorDlg::OnButtonTransfilelocation() 
{
	// TODO: Add your control notification handler code here
	m_strstartaddress="0x00800000";
	m_ceditstartaddress.SetWindowText(m_strstartaddress);
	m_bgeo=TRUE;
	CFileDialog mFileDlg(TRUE, NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , "GEO�ļ�(*.geo)|*.geo|All Files (*.*)|*.*|", AfxGetMainWnd());

    if(mFileDlg.DoModal()==IDOK)
	{
		CFileException e;

        m_strTXData.Empty();//��ʼ����ʾ�ļ�����

        m_edittxdata.SetWindowText(m_strTXData);

	    m_filepath=mFileDlg.GetPathName();//������ʾ·������

		CString m_strxie="\\";
		CString m_strxiexie="\\\\";
		
		m_filepath.Replace(m_strxie,m_strxiexie);	//��һ����б���滻Ϊ˫б��
		
		m_sFilePath.SetWindowText(m_filepath);

		
		FILE * m_bfilep=fopen(m_filepath,"ab+");
		
		if (m_bfilep==NULL)
		{
			AfxMessageBox("���ļ�ʧ��!");
		}
		
		long int m_filepos = ftell(m_bfilep);
		
		fseek(m_bfilep,0,SEEK_END);
		
		m_filepos = ftell(m_bfilep);
		
		m_binfilelenth=m_filepos;

		m_binfilelenthtocalulate=m_binfilelenth;

		fseek(m_bfilep,0,SEEK_SET);
		
		m_strcounterforlefttosend.Format("%d",m_filepos);
		
		m_cscounterforlefttosend.SetWindowText(m_strcounterforlefttosend);
		
		m_strcounterforallbytesend.Format("%d",m_filepos);

		m_cscounterforallbytesend.SetWindowText(m_strcounterforallbytesend);

		/*
		**�������ݰ�����
		*/

		//����

		if (m_filepos%60==0)
		{
			m_strcounterfordataall.Format("%d",m_filepos/60);
			m_intcounterdatanum=m_filepos/60;
			m_strcounterfordataall.Format("%d",m_intcounterdatanum);
		}
		//������
		else
		{
			int	m_dataresidu=0;
			int m_datatoadd=0;
			int	m_datanum=0;
			m_dataresidu=m_filepos%60;
			m_datatoadd=60-m_dataresidu;
			m_datanum=m_filepos+m_datatoadd;
			m_intcounterdatanum=m_datanum/60;
			m_strcounterfordataall.Format("%d",m_intcounterdatanum);
		}
	
		m_cscounterfordataall.SetWindowText(m_strcounterfordataall);


		m_cscounterforleftdata.SetWindowText(m_strcounterfordataall);

		m_cscounterforframeindata.SetWindowText("0");
		
		m_cscounterforcurrentsend.SetWindowText("0");

		fclose(m_bfilep);
			        
	}
}

CString CTranslatorDlg::Geosetbinarypath()
{
	//���û�ѡ��������ļ���ŵ�ַ
	
	BOOL kind = FALSE;
	CString typeName = "geo",str = "geo";
	char *pFilters = NULL;
	int rst = 0;
	
	char szfilters1[]="�������ݶ������ļ�(*.geo)|";
	
		/*
	**�Զ����ɱ�������
	*/


	CString m_strsystemtime="";
	CString m_strfilename="";
	CTime t=CTime::GetCurrentTime();
	m_strsystemtime=t.Format("%Y-%m-%d.%H-%M-%S");
	

	str.Format("binary.%s",typeName);

	m_strfilename=m_strsystemtime+str;

	pFilters = szfilters1;
	
	
	CFileDialog dlgselectbinfilepath(kind,typeName,m_strfilename,OFN_HIDEREADONLY,pFilters);
	rst = dlgselectbinfilepath.DoModal();
	if(rst==IDOK)
	{
		m_binfilefullpath=dlgselectbinfilepath.GetPathName();
		
		m_strbinfilepath=m_binfilefullpath;
		
		m_sbinfilepath.SetWindowText(m_strbinfilepath);
	}
	else
	{
		// ����û���ָ��λ�ã���ô�ļ��Զ������ڳ���Ŀ¼��
		
		m_binfilefullpath="";	
		return m_binfilefullpath;
		
	}
	
	return m_binfilefullpath;
}

void CTranslatorDlg::OnEditchangeComboSenddistination() 
{
	// TODO: Add your control notification handler code here
	AfxMessageBox("�˴��ݲ�֧�ֱ༭����!");
}

void CTranslatorDlg::OnSelchangeComboSenddistination() 
{
	// TODO: Add your control notification handler code here
	int m_senddistinationindex;
	m_senddistinationindex=m_combosenddistination.GetCurSel();

	if(m_senddistinationindex!=CB_ERR)
	{
		
		m_combosenddistination.GetLBText(m_senddistinationindex,m_strsenddistination);
		
		if ((0==m_senddistinationindex)|(m_strsenddistination=="ATP_MPM_A"))
		{
			m_strsendaddress="93";
		}
		else if ((1==m_senddistinationindex)|(m_strsenddistination=="ATP_MPM_B"))
		{
			m_strsendaddress="A3";
		}
		else if ((2==m_senddistinationindex)|(m_strsenddistination=="ATP_MPM_C"))
		{
			m_strsendaddress="B3";
		}
		else if ((3==m_senddistinationindex)|(m_strsenddistination=="ATP_MPM_D"))
		{
			m_strsendaddress="C3";
		}
		else if ((4==m_senddistinationindex)|(m_strsenddistination=="ATO_MPM"))
		{
			m_strsendaddress="D3";
		}

	}

}


void CTranslatorDlg::Sendbinarydata()
{

//	SendReadySignal();

	int m_writefilelenth=0;

	CString m_strwritesendlog="";


	m_sendfile.SeekToEnd();   //��д��λ�ö�λ���ı�ĩβ
	
	/*
	**֡������Ҫ���棬�Ա���Ӧ��λ��Ҫ�����·���
	*/
	
//	m_dealframe=FALSE;
	m_strTXData.Empty();
	int m_framelenth=48;
	
	//�ϳ�֡,����֡���ݸ���ȫ�ֱ���
	
	Sleep(FRAMELAP);

	m_frame1=Composeframe(1);
	WriteSendData(m_frame1);
	//��ȡ֡����Ϣ,��д���ı�

//	m_strwritesendlog=m_frame1.Mid(12,12);
	
	m_strTXData+=m_frame1;

	m_strTXData+=m_return;
	Sendframe(m_frame1);

	Sleep(FRAMELAP);	//ϵͳ˯��300ms��������̫�죬����֡��ʧ

	if (m_frame1.GetLength()!=m_framelenth)
	{
		AfxMessageBox("�ϳ�֡����!");
	}
	
	
	//����֡
	
	m_strcounterforframeindata.Format("%d",1);

	m_cscounterforframeindata.SetWindowText(m_strcounterforframeindata);

	m_frame2=Composeframe(2);
		WriteSendData(m_frame2);
	if (m_frame1.GetLength()!=m_framelenth)
	{
		AfxMessageBox("�ϳ�֡����!");
	}

	Sendframe(m_frame2);
	m_strTXData+=m_frame2;
	m_strTXData+=m_return;
	Sleep(FRAMELAP);

	m_strcounterforframeindata.Format("%d",2);
	
	m_cscounterforframeindata.SetWindowText(m_strcounterforframeindata);


	m_frame3=Composeframe(3);
		WriteSendData(m_frame3);
	Sendframe(m_frame3);
	m_strTXData+=m_frame3;
	m_strTXData+=m_return;
	Sleep(FRAMELAP);
	if (m_frame1.GetLength()!=m_framelenth)
	{
		AfxMessageBox("�ϳ�֡����!");
	}

	
	m_strcounterforframeindata.Format("%d",3);
	
	m_cscounterforframeindata.SetWindowText(m_strcounterforframeindata);

	m_frame4=Composeframe(4);
	WriteSendData(m_frame4);
	Sendframe(m_frame4);
	m_strTXData+=m_frame4;
	m_strTXData+=m_return;
	Sleep(FRAMELAP);
	if (m_frame1.GetLength()!=m_framelenth)
	{
		AfxMessageBox("�ϳ�֡����!");
	}
	
	m_strcounterforframeindata.Format("%d",4);
	
	m_cscounterforframeindata.SetWindowText(m_strcounterforframeindata);


	m_txlen+=96;

	m_edittxdata.SetWindowText(m_strTXData);
						
	m_writefilelenth=m_strTXData.GetLength();
				
	m_sendfile.Write(m_strTXData,m_writefilelenth);
	

	//���ݰ�����
	
	m_intcounterdatanum--;

	m_strcounterforleftdata.Format("%d",m_intcounterdatanum);

	m_cscounterforleftdata.SetWindowText(m_strcounterforleftdata);



	m_strcounterforcurrentsend.Format("%d",m_intcounterdatanumup);

	m_cscounterforcurrentsend.SetWindowText(m_strcounterforcurrentsend);

	m_intcounterdatanumup++;
	

	if ((m_binfilelenthtocalulate<=m_binreadcounter)&&(m_boolresend!=TRUE))
	{
		//�ϳɲ����ͽ���֡
		Sleep(100);
		Composeresendoverframe();
		KillTimer(2);
		m_sendfile.Close();
	//	AfxMessageBox("���ݷ������!");
		Allfuctionabled();
		//����ʱ�����
		KillTimer(4);
	}
	m_boolresend=FALSE;

	//������ʱ��ʱ��
	
	
//	m_dealframe=TRUE;
	
//	KillTimer(2);
	/*
	m_intmaxtimetowait=100000;
	SetTimer(3,m_intmaxtimetowait,NULL);
	*/
}

void CTranslatorDlg::Overtime()
{
	/*
	**ɱ��ȫ����ʱ����������������Ϣ
	*/
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);

	AfxMessageBox("�ȴ�ʱ���Ѿ��������ʱ�ޣ�������Ӳ������!");

}

CString CTranslatorDlg::Calculatenextaddress(CString prvaddress)
{
	unsigned int m_address=0;  //�����ֵ����

	/*
	**ת��Ϊ16������
	*/


//	CString m_straddress=prvaddress.Right(8);

	CString m_straddhead="0x";

	m_address=strtoul(prvaddress,NULL,16);

	m_address+=60;

	prvaddress.Format("%02x",m_address);

	/*
	**ת����ĵ�ַ����λ��һ���λ��Ϊ0����ȫ��λ��
	*/

	int	m_addressbit=0;
	CString m_zero="0",m_allzero="";
	m_addressbit=prvaddress.GetLength();

	switch (m_addressbit)
	{
		case 1:
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			break;
		case 2:
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			break;
		case 3:
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			break;
		case 4:
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			break;
		case 5:
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			break;
		case 6:
			m_allzero+=m_zero;
			m_allzero+=m_zero;
			break;
		case 7:
			m_allzero+=m_zero;
			break;
		case 8:
			break;
		default:
			AfxMessageBox("֡��ַ�������!");	

	}

	m_allzero+=prvaddress;

	m_straddhead+=m_allzero;


	return m_straddhead;
}

CString CTranslatorDlg::Composeframe(int numofframe)
{

	CString m_frameall="";				//��֡
	m_frameall+=m_framehead;			//�̶�ͷ

	m_frameall+=m_strsendaddress;		//Ŀ�ĵ�ַ
	
	CString m_strcounter;
	char	m_charcounter;
	CString m_zero="0";

	/*
	**֡����
	*/

	m_strcounter=itoa(Counters(),&m_charcounter,16);
	
	if (m_counters<=15)
	{
		m_strcounter=m_zero+m_strcounter;
	}

	m_frameall+=m_strcounter;

	/*
	**���ݼ���ֵ�жϺϳɾ���֡
	*/
	CString m_frameserial="";
	switch(numofframe)
	{
		case 1:
			m_frameserial="70";
			break;
		case 2:
			m_frameserial="e0";
			break;
		case 3:
			m_frameserial="e1";
			break;
		case 4:
			m_frameserial="e2";
			break;
		default:
			AfxMessageBox("֡�м�������!");
			break;
	}

	m_frameall+=m_frameserial;
	
	CString m_readbinarydata="";



	if (1==numofframe)
	{
		/*
		**����֡��ַ��ֵ����������һ֡��ַ
		*/

		m_frameall+=m_senddatastartaddress.Right(8);

		CString m_temp=m_senddatastartaddress;

		m_senddatastartaddress=Calculatenextaddress(m_temp);

		/*
		**��ȡ12�ֽڵĶ���������
		*/
		m_readbinarydata=Readbinary(m_binreadcounter,12);
		
		m_binreadcounter+=12;

		m_binfilelenth-=12;
		m_strcounterforlefttosend.Format("%d",m_binfilelenth);

		m_cscounterforlefttosend.SetWindowText(m_strcounterforlefttosend);

	} 
	else
	{
		/*
		**�޵�ַ����ȡ16�ֽڶ���������
		*/
		m_readbinarydata=Readbinary(m_binreadcounter,16);

		m_binreadcounter+=16;

		m_binfilelenth-=16;
		m_strcounterforlefttosend.Format("%d",m_binfilelenth);
		m_cscounterforlefttosend.SetWindowText(m_strcounterforlefttosend);

	}

	m_frameall+=m_readbinarydata;

	
	/*
	**��ʼ����CRC
	*/
	CString m_strcrc16;
	m_strcrc16=CalculatestrCRC(m_frameall, 22);
	

	m_frameall+=m_strcrc16;

	return m_frameall;
}

CString CTranslatorDlg::Readbinary(long startadd, int lenth)
{
	int m_seepos=0;

	CString m_binarydata="";

	FILE * m_bfilep=fopen(m_filepath,"ab+");
		
	if (m_bfilep==NULL)
	{
		AfxMessageBox("���ļ�ʧ��!");
	}
	
	fseek(m_bfilep,startadd,SEEK_SET);

	m_seepos=ftell(m_bfilep);

	unsigned char m_readbin[16];
	
	//��ȡʱ�ж��Ƿ��ȡ���ļ�ĩβ

	if (startadd+lenth<m_binfilelenthtocalulate)
	{
		fread( m_readbin, sizeof(char), lenth, m_bfilep);
		m_seepos=ftell(m_bfilep);
	}
	
	//��������ļ�ĩβ����ʹ��0xff�����������

	else
	{
		int readlenth=0;
		readlenth=m_binfilelenthtocalulate-startadd;
		
		if (readlenth>0)
		{	
			fread( m_readbin, sizeof(char), readlenth, m_bfilep);
			m_seepos=ftell(m_bfilep);
			for (int fillloop=0;fillloop<lenth-readlenth;fillloop++)
			{
				m_readbin[readlenth+fillloop]=0xff;
			}
		}
		else
		{
			for (int fillinloop=0;fillinloop<16;fillinloop++)
			{
				m_readbin[fillinloop]=0xff;
			}
		}


	}
	
	CString			m_strreadbin;
	unsigned char	m_cbinary;

	for (int i=0;i<lenth;i++)
	{
		m_cbinary=m_readbin[i];
		m_strreadbin.Format("%02x",m_cbinary);
		m_binarydata+=m_strreadbin;
	}

	fclose(m_bfilep);

	return m_binarydata;
}

CString CTranslatorDlg::CalculatestrCRC(CString strtocrc, int lenth)
{
	CString m_crc16;
	//����CRC16
	char strtochar[45]; 
	unsigned char * strchar;  //����ת��ΪCRC16�����ɵ��õ�����
	unsigned short int  m_crc16result=0;      //CRC16 ���㷵�ؽ��
	
	::strcpy(strtochar,strtocrc);
	
	strchar=(unsigned char *)strtochar;
	
	m_crc16result=Get_CRC16_Code(strchar, lenth);

	char m_itochar[4];

	char * m_pitochar;		//�ַ��������޷�ֱ��ת��ΪCString��ʽ����ת��Ϊ�ַ���ָ���ֱ�Ӹ�ֵ����

	itoa(m_crc16result,m_itochar,16);
	
	m_pitochar=m_itochar;

	m_crc16=m_pitochar;

	CString m_zero="0";

	int m_crclenth=m_crc16.GetLength();

	if (m_crclenth!=4)
	{
		switch (m_crclenth)
		{
		case 3:
			{
				m_crc16=m_zero+m_crc16;
				break;
			}
		case 2:
			{
				m_crc16=m_zero+m_crc16;
				m_crc16=m_zero+m_crc16;
				break;
			}
		case 1:
			{
				m_crc16=m_zero+m_crc16;
				m_crc16=m_zero+m_crc16;
				m_crc16=m_zero+m_crc16;
				break;
			}
		case 0:
			{
				m_crc16=m_zero+m_crc16;
				m_crc16=m_zero+m_crc16;
				m_crc16=m_zero+m_crc16;
				m_crc16=m_zero+m_crc16;
				break;
			}
		default:
			{
				AfxMessageBox("CRC �������!");
			}
		}
	}

	CString m_highcrc;
	CString m_lowcrc;
	CString m_crc;
	m_highcrc=m_crc16.Left(2);
	m_lowcrc=m_crc16.Right(2);

	m_crc=m_lowcrc+m_highcrc;

	m_crc16=m_crc;

	return m_crc16;
}

void CTranslatorDlg::Sendframe(CString m_frame)
{
	int m_sendlenth;
	char SendOut[MAXBLOCK];
	int len;

	//��CStringת��Ϊʮ�������ַ���
 	m_sendlenth=m_frame.GetLength();
		
	if (m_sendlenth!=48)
	{
		AfxMessageBox("����֡����!");

	}
	len=String2Hex(m_frame,SendOut);

	Rscom.Write(SendOut,len);
//	m_Port[0].WriteToPort(SendOut,len);
}

void CTranslatorDlg::Composeresendoverframe()
{

	m_overframe=ComposeOverFrame(1);
	Sendframe(m_overframe);
	
	m_strTXData=m_overframe;
	m_strTXData+=m_return;
	m_edittxdata.SetWindowText(m_strTXData);
	
	Sleep(20);

	m_overframe=ComposeOverFrame(2);
	Sendframe(m_overframe);
	
	m_strTXData+=m_overframe;
	m_strTXData+=m_return;
	m_edittxdata.SetWindowText(m_strTXData);
	
	Sleep(20);

	m_overframe=ComposeOverFrame(3);
	Sendframe(m_overframe);
	
	m_strTXData+=m_overframe;
	m_strTXData+=m_return;
	m_edittxdata.SetWindowText(m_strTXData);
	
	Sleep(20);

	m_overframe=ComposeOverFrame(4);
	Sendframe(m_overframe);
	
	m_strTXData+=m_overframe;
//	m_strTXData+=m_return;
	m_edittxdata.SetWindowText(m_strTXData);
	
	Sleep(20);
	
	int   nLen   =   m_edittxdata.SendMessage(WM_GETTEXTLENGTH);
				
	m_edittxdata.SetSel(nLen,   nLen,   FALSE); 
	
	//m_strTXData.Empty();
	
}

CString CTranslatorDlg::Resolvecommand(CString command)
{
	CString m_command,m_strcommand1,m_strcommand2,m_strcommand3,m_strcommand4;
	
	m_strcommand1=command.GetAt(12);
	m_strcommand2=command.GetAt(13);
	m_strcommand3=command.GetAt(14);
	m_strcommand4=command.GetAt(15);

	m_strcommand1+=m_strcommand2;
	m_strcommand1+=m_strcommand3;
	m_strcommand1+=m_strcommand4;

	if (m_strcommand1=="CCCC")
	{
		m_command="NEXT";
	} 
	else if(m_strcommand1=="EEEE")
	{
		m_command="RESEND";
	}
	else if (m_strcommand1=="BBBB")
	{
		m_command="WAIT";
	}

	return m_command;
}

unsigned int CTranslatorDlg::Calculateaddall(unsigned int m_addall, unsigned int m_currentadd, int m_addsize)
{

	switch(m_addsize)
	{
		case 1:
			{
				m_addall+=m_currentadd;
				break;
			}
		case 2:
			{
				unsigned int m_uintforaddresult=0;
				unsigned int m_uintforaddmask=0x00ff;

				m_uintforaddresult=m_uintforaddmask&m_currentadd;	//�������ָ��ֽ���

				m_addall+=m_uintforaddresult;

				m_uintforaddresult=m_currentadd>>8;

				m_addall+=m_uintforaddresult;

				break;

			}
		case 4:
			{

				unsigned int m_uintforaddresult=0;
				unsigned int m_uintforaddmask=0x0000000ff;
				unsigned int m_uintforrightmove=0;

				m_uintforaddresult=m_uintforaddmask&m_currentadd;	//��һ�ֽ�

				m_addall+=m_uintforaddresult;

				m_uintforrightmove=m_currentadd>>8;
				m_uintforaddresult=m_uintforaddmask&m_uintforrightmove;	//�ڶ��ֽ�
				m_addall+=m_uintforaddresult;

				m_uintforrightmove=m_uintforrightmove>>8;

				m_uintforaddresult=m_uintforaddmask&m_uintforrightmove;	//�����ֽ�

				m_addall+=m_uintforaddresult;

				m_uintforrightmove=m_uintforrightmove>>8;

				m_uintforaddresult=m_uintforaddmask&m_uintforrightmove;	//�����ֽ�

				m_addall+=m_uintforaddresult;

				break;

			}

		default:
			AfxMessageBox("�ӷ��ͼ�����̳���!");
			break;
	}

	return m_addall;
}


void CTranslatorDlg::Writebinarydata(CString m_binfilefullpath, unsigned int data, int datasize)
{

		int m_toseeposg=0;
		int m_toseeposp=0;

		::fstream m_binfile(m_binfilefullpath, ios_base::out | ios_base::app | ios_base::binary);

  
	
//		m_binfile.seekg(0,ios::end);   // ��д��ָ�붨λ���ļ���β

		
//		m_binfile.clear();				//�����������д��λ�û��棬�粻���ô˺������ļ�д��2380λ�ú�ָ���޷��ƶ�	

			  
		m_binfile.write((char *)(&data),datasize);
				
					
		m_binfile.close();
					  
					
	/*
#include <stdio.h>
	
	void main( void )
	{
		FILE *stream;
		char list[30];
		int  i, numread, numwritten;
		
		/* Open file in text mode: */
	/*
		if( (stream = fopen( "fread.out", "w+t" )) != NULL )
		{
			for ( i = 0; i < 25; i++ )
				list[i] = (char)('z' - i);
			/* Write 25 characters to stream */
	/*
			numwritten = fwrite( list, sizeof( char ), 25, stream );
			printf( "Wrote %d items\n", numwritten );
			fclose( stream );
			
		}
		else
			printf( "Problem opening the file\n" );
		
		if( (stream = fopen( "fread.out", "r+t" )) != NULL )
		{
			/* Attempt to read in 25 characters */
	/*
			numread = fread( list, sizeof( char ), 25, stream );
			printf( "Number of items read = %d\n", numread );
			printf( "Contents of buffer = %.25s\n", list );
			fclose( stream );
		}
		else
			printf( "File could not be opened\n" );
	}

	*/



}

void CTranslatorDlg::OnButtonSelectframehead() 
{
	// TODO: Add your control notification handler code here
	CFileDialog mFileDlg(TRUE, NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , "EXCEL�ļ�(*.xls)|*.xls|EXCEL2007�ļ�(*.xlsx)|*.xlsx|All Files (*.*)|*.*|", AfxGetMainWnd());
	
    if(mFileDlg.DoModal()==IDOK)
	{
		
		m_strframeheadexcelfilepath=mFileDlg.GetPathName();//������ʾ·������
		
		m_csframeheadexcelfilepath.SetWindowText(m_strframeheadexcelfilepath);
		
	}
	
}

void CTranslatorDlg::OnButtonSelectupgeo() 
{
	// TODO: Add your control notification handler code here
	/*
	**�ȼ���Ƿ����֡ͷ�ļ�
	*/

	if (m_strframeheadexcelfilepath=="")
	{
		AfxMessageBox("����ѡ��֡ͷ�ļ�!");
		return;
	}

	CFileDialog mFileDlg(TRUE, NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , "GEO�ļ�(*.geo)|*.geo|All Files (*.*)|*.*|", AfxGetMainWnd());
	
    if(mFileDlg.DoModal()==IDOK)
	{
		
		m_strupgeofilepath=mFileDlg.GetPathName();//������ʾ·������
		
		m_csupgeofilepath.SetWindowText(m_strupgeofilepath);
		
	}

}

void CTranslatorDlg::OnButtonSelectdowngeo() 
{
	// TODO: Add your control notification handler code here
	/*
	**�ȼ���Ƿ�������������ļ�
	*/
	if (m_strupgeofilepath=="")
	{
		AfxMessageBox("����ѡ�����е��������ļ�!");
		return;
	}

	
	CFileDialog mFileDlg(TRUE, NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT , "GEO�ļ�(*.geo)|*.geo|All Files (*.*)|*.*|", AfxGetMainWnd());
	
    if(mFileDlg.DoModal()==IDOK)
	{
		
		m_strdowngeofilepath=mFileDlg.GetPathName();//������ʾ·������
		
		if (m_strdowngeofilepath==m_strupgeofilepath)
		{
			AfxMessageBox("�������ݺ����������ļ���������ͬһ���ļ�,������ѡ���ļ�!");
			return;
		}

		m_csdowngeofilepath.SetWindowText(m_strdowngeofilepath);
		
	}

}

void CTranslatorDlg::OnButtonSynthesizegeo() 
{
	// TODO: Add your control notification handler code here
	//�ȼ���Ƿ����֡ͷ�����������ļ������������ļ�
	if ((m_strframeheadexcelfilepath=="")|(m_strupgeofilepath=="")|(m_strdowngeofilepath==""))
	{
		AfxMessageBox("����ѡ�����������ļ�!");
		return;
	}
	CString m_strgeofilepath;
	CString m_strxie="\\";
	CString m_strxiexie="\\\\";
	m_strgeofilepath=Geosetbinarypath();
	m_strgeofilepath.Replace(m_strxie,m_strxiexie);	//��һ����б���滻Ϊ˫б��
	m_strsynthesizegeofilepath=m_strgeofilepath;
	m_cssynthesizegeofilepath.SetWindowText(m_strsynthesizegeofilepath);
	//��ʼд������ǰ�����ȴ򿪶������ļ�
	//����·�������������ļ�,
	FILE * m_filep;
	m_filep=fopen(m_strgeofilepath,"wb+");
	if (m_fileopen==FALSE)
	{
		m_fileopen=TRUE;
	}
	//���ɶ������ļ���д��������ݹ������ݣ���Ϊֻ��ȡexcel�е�һ����Ԫ�񣬺���������һ���ȡ��д�룬��ʱд16�ֽ�0xff
	long	m_filepostion=0;				//�������ļ�ָ��λ��
	long	m_filepostioncalculate=0;		//��������ʱλ��
	unsigned int m_uintaddress=0;			//��ַ����
	unsigned int m_uintgeoversion=0;		//��ǰ�汾�ţ��������ɺ�д��
	unsigned int m_fillinblank=0xff;
	BYTE m_bytearray[64];
	for (int m_geomanger=0;m_geomanger<64;m_geomanger++)
	{
		m_bytearray[m_geomanger]=m_fillinblank;
	}
	fwrite(&m_bytearray,1,64,m_filep);
	fflush(m_filep);
	//��ʼ��ȡEXCEL�ļ�
	if (m_fileopen==TRUE)
	{
		_Application ExcelApp;  // EXCEL Ӧ�ó���
		Workbooks m_wbsBooks;  
		_Workbook m_wbBook;  
		Worksheets m_wsssheets;  
		_Worksheet m_wssheet;  
		Range m_rgRge;  
		CString m_sheetname;
		COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		if (!ExcelApp.CreateDispatch("Excel.Application",NULL))  
		{  
			AfxMessageBox("����Excel����ʧ��!");  
			exit(1);  
		}  
		ExcelApp.SetUserControl(TRUE);      //���������û�����Excel
// 		���Ѵ��ڵ�Excel�ļ���Sheet
		m_wbsBooks=ExcelApp.GetWorkbooks();
		m_wbBook=m_wbsBooks.Open(m_strframeheadexcelfilepath,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional);
		m_wsssheets=m_wbBook.GetWorksheets();
		//����������ѡ���һ��������һ�㶨��Ϊ��һ����Ϊ�������ݹ������ݱ��ڶ�����Ϊ�������ݱ�
		for (int nSheetNumber=1;nSheetNumber<=2;nSheetNumber++)
		{
			//��ȡ�Ѿ�ʹ���������Ϣ�������Ѿ�ʹ�õ���������������ʼ�С���ʼ��
			m_wssheet=m_wsssheets.GetItem(COleVariant((short)nSheetNumber));
			m_sheetname=m_wssheet.GetName();
			Range usedRange;
			usedRange.AttachDispatch(m_wssheet.GetUsedRange());
			m_rgRge.AttachDispatch(usedRange.GetRows());
			long iRowNum=m_rgRge.GetCount();                   //�Ѿ�ʹ�õ�����
			m_rgRge.AttachDispatch(usedRange.GetColumns());
			long iColNum=m_rgRge.GetCount();                   //�Ѿ�ʹ�õ�����
			long iStartRow=usedRange.GetRow();               //��ʹ���������ʼ�У���1��ʼ
			long iStartCol=usedRange.GetColumn();            //��ʹ���������ʼ�У���1��ʼ
			//ѭ����ȡEXCEL�е�ֵ����ת����ʽΪ�������ļ�����д�뵽�������ļ��У��ӵڶ��к͵�һ�п�ʼ��ȡ��ֻ��ȡ��������
			for (iStartRow=2;iStartRow<=iRowNum;iStartRow++)
			{
				//ÿ�п�ʼ��ȡʱ��ʼ������
				CString m_strcontent="";			//��Ԫ������
				DOUBLE		m_double=0;		
				DOUBLE		m_dvalue=0;			//��ֵ	
				BYTE m_bytetowritebin=0;	//Ҫд��������ļ�����ֵ�ĳ��Ȳ�ͬ�ֱ������
				WORD	m_wordtowritebin=0;
				unsigned int m_uinttowritebin=0;
				unsigned int m_uintaddalldata=0;		//�ӷ���
				for (iStartCol=1;iStartCol<=iColNum;iStartCol++)
				{
					//�������ݹ��������е���Ч����ֱ������
					if ((nSheetNumber==1)&&(iStartRow==2)&&(iStartCol!=1))
					{
							continue;
					}
					//������������Ч��������
					if (iStartCol>6)
					{
							continue;
					}
					//��ȡ��Ԫ������
					m_rgRge.AttachDispatch(m_wssheet.GetCells()); 
					m_rgRge.AttachDispatch(m_rgRge.GetItem (COleVariant((long)iStartRow),COleVariant((long)iStartCol)).pdispVal );
					COleVariant vResult =m_rgRge.GetValue2();
					if(vResult.vt == VT_BSTR)       //�ַ���
					{
						//�������ݹ������ݰ汾��
						if ((nSheetNumber==1)&&(iStartRow==2)&&(iStartCol==1))
						{
							//�ַ�������Ϊ�汾�ţ����汾�ŵ�ĩβ��λ����ת��Ϊ�����Ʋ�����
							CString m_strversion;
							m_strcontent=vResult.bstrVal;
							m_strversion=m_strcontent.Right(2);
							m_double=strtoul((LPCTSTR)m_strversion,NULL,16);
							m_wordtowritebin=m_double;
							//д�������ֵ
							if (m_fileopen==TRUE)	
							{
								m_filepostion=ftell(m_filep);	//�����ļ�ָ��λ��
								rewind(m_filep);				//�ƶ�ָ�뵽�ļ���ʼλ��
								fwrite(&m_wordtowritebin,1,2,m_filep);
								fflush(m_filep);
								fseek(m_filep,m_filepostion,0);
								m_filepostion=ftell(m_filep);
							}
						}
						//����������������
						if (nSheetNumber==2)
						{
							//�ַ��������ÿ�е���Ϣ���д���
							m_strcontent=vResult.bstrVal;
							switch (iStartCol)
							{
								/*
								**��λAPR��ţ�4Byte��
								*/

								case 2:
								{
									unsigned int m_uintapr=0xffffffff;

									/*
									**16�������ַ���ת��Ϊ10��������
									*/
									m_uintapr=strtoul(m_strcontent,NULL,16);

									if ((0xffffffff==m_uintapr)|(m_strcontent.GetLength()!=10)|(m_strcontent.Left(2)!="0x"))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										
										return;
									}
									/*
									**ռ��4���ֽ�
									*/
									fwrite(&m_uintapr,1,4,m_filep);
									
									fflush(m_filep);
									/*
									**����ӷ���
									*/

									m_uintaddalldata=Calculateaddall(m_uintaddalldata,m_uintapr,4);
									
									break;
								}

								/*
								**����������ʼ��ַ��4Byte��
								*/

								case 3:
								{

									/*
									**��ȡ�û����ó�ʼ��ַ
									*/

									if ((iStartRow==2)&&(iStartCol==3)&&(m_uintaddress==0))
									{
										
										/*
										**16�������ַ���ת��Ϊ10��������
										*/
										m_uintaddress=strtoul(m_strcontent,NULL,16);

										if ((m_strcontent.GetLength()!=10)|(m_strcontent.Left(2)!="0x"))
										{
											CString m_warning="�����ļ�ʱ��������λ���ڵ�";
											CString m_colnum;
											CString m_rownum;
											CString m_sheetnum;
											
											m_colnum.Format("%d",iStartCol);
											m_rownum.Format("%d",iStartRow);
											m_sheetnum.Format("%d",nSheetNumber);
											
											m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
											
											AfxMessageBox(m_warning);
											//�ر��ļ�
											m_wbsBooks.Close();
											ExcelApp.Quit();
											//�ͷŶ���  
											m_rgRge.ReleaseDispatch();  
											m_wssheet.ReleaseDispatch();  
											m_wsssheets.ReleaseDispatch();  
											m_wbBook.ReleaseDispatch();  
											m_wbsBooks.ReleaseDispatch();  
											ExcelApp.ReleaseDispatch();  
											
											fcloseall();
											
											return;
										}
										/*
										**ռ��4���ֽ�
										*/
										fwrite(&m_uintaddress,1,4,m_filep);
										
										fflush(m_filep);

										/*
										**����ӷ���
										*/

										m_uintaddalldata=Calculateaddall(m_uintaddalldata,m_uintaddress,4);

										break;

									}
									
									else
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݱ�������!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										
											return;
									}


								}

								/*
								**������α�ţ�4Byte��
								*/

								case 1:
								{
										unsigned int m_uinttracknumber=0xffffffff;

										/*
										**16�������ַ���ת��Ϊ10��������
										*/
										m_uinttracknumber=strtoul(m_strcontent,NULL,16);

										if ((0==m_uinttracknumber)|(m_strcontent.GetLength()!=10)|(m_strcontent.Left(2)!="0x"))
										{
											CString m_warning="�����ļ�ʱ��������λ���ڵ�";
											CString m_colnum;
											CString m_rownum;
											CString m_sheetnum;
											
											m_colnum.Format("%d",iStartCol);
											m_rownum.Format("%d",iStartRow);
											m_sheetnum.Format("%d",nSheetNumber);
											
											m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
											
											AfxMessageBox(m_warning);
											//�ر��ļ�
											m_wbsBooks.Close();
											ExcelApp.Quit();
											//�ͷŶ���  
											m_rgRge.ReleaseDispatch();  
											m_wssheet.ReleaseDispatch();  
											m_wsssheets.ReleaseDispatch();  
											m_wbBook.ReleaseDispatch();  
											m_wbsBooks.ReleaseDispatch();  
											ExcelApp.ReleaseDispatch();  
											
											fcloseall();
											
											return;
										}

										fwrite(&m_uinttracknumber,1,4,m_filep);
										
										fflush(m_filep);

										/*
										**����ӷ���
										*/

										m_uintaddalldata=Calculateaddall(m_uintaddalldata,m_uinttracknumber,4);

										break;
								}

								/*
								**�����У�1Byte��
								*/

								case 4:
								{
										BYTE m_byteupdown=0xff;

										if (m_strcontent=="TRACK_UP")
										{
											m_byteupdown=TRACK_UP;
										}
										else if (m_strcontent=="TRACK_STATION_UP")
										{
											m_byteupdown=TRACK_UP;
										}
										
										else if (m_strcontent=="TRACK_DOWN")
										{
											m_byteupdown=TRACK_DOWN;
										}										
										
										else if (m_strcontent=="TRACK_STATION_DOWN")
										{
											m_byteupdown=TRACK_DOWN;
										}

										else if (m_strcontent=="TRACK_PARK")
										{
											m_byteupdown=TRACK_PARK;
										}

										else if (m_strcontent=="TRACK_FERRY")
										{
											m_byteupdown=TRACK_FERRY;
										}

										else if (m_strcontent=="TRACK_TURNBK")
										{
											m_byteupdown=TRACK_TURNBK;
										}
										

										if (0xff==m_byteupdown)
										{
											CString m_warning="�����ļ�ʱ��������λ���ڵ�";
											CString m_colnum;
											CString m_rownum;
											CString m_sheetnum;
											
											m_colnum.Format("%d",iStartCol);
											m_rownum.Format("%d",iStartRow);
											m_sheetnum.Format("%d",nSheetNumber);
											
											m_warning=m_sheetname+m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ����Ϸ���Ҫ��!";
											
											AfxMessageBox(m_warning);
											//�ر��ļ�
											m_wbsBooks.Close();
											ExcelApp.Quit();
											//�ͷŶ���  
											m_rgRge.ReleaseDispatch();  
											m_wssheet.ReleaseDispatch();  
											m_wsssheets.ReleaseDispatch();  
											m_wbBook.ReleaseDispatch();  
											m_wbsBooks.ReleaseDispatch();  
											ExcelApp.ReleaseDispatch();  
											
											fcloseall();
											
											return;
										}

										fwrite(&m_byteupdown,1,1,m_filep);
										
										fflush(m_filep);

										/*
										**����ӷ���
										*/

										m_uintaddalldata=Calculateaddall(m_uintaddalldata,m_byteupdown,1);

										break;
								}

								/*
								**�ӷ���(2Byte)
								*/
								case 6:
								{


										m_wordtowritebin=m_uintaddalldata;

										fwrite(&m_wordtowritebin,1,2,m_filep);
									
										fflush(m_filep);
										m_uintaddalldata=0;

										break;
								}

								/*
								**Ԥ��(1Byte)
								*/

								case 5:
								{
										m_bytetowritebin=m_fillinblank;

										fwrite(&m_bytetowritebin,1,1,m_filep);
									
										fflush(m_filep);
										/*
										**����ӷ���
										*/

										m_uintaddalldata=Calculateaddall(m_uintaddalldata,m_bytetowritebin,1);
										break;
								}
							}
							
						}

					}
					else if (vResult.vt==VT_R8)     //8�ֽڵ����� 
					{
						m_double=vResult.dblVal;	

						switch (iStartCol)
						{
							case 6:
								{
									m_bytetowritebin=m_fillinblank;
									
									fwrite(&m_bytetowritebin,1,1,m_filep);
									
									fflush(m_filep);
									
									break;
								}

						}

					}
					else if(vResult.vt==VT_DATE)    //ʱ���ʽ
					{
						SYSTEMTIME st;
						VariantTimeToSystemTime(vResult.date, &st);
					}
					else if(vResult.vt==VT_EMPTY)   //��Ԫ��յ�
					{
						
						if (nSheetNumber==2)
						{
							switch (iStartCol)
								
							{
							case 1:
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									
									m_warning=m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ�����Ϊ��!";
									
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									
									fcloseall();
									
									return;

									break;
								}

							case 3:
								{
									/*
									**���ݳ�ʼ��ַ���㵱ǰ��ַ
									*/

									m_uintaddress+=128;
									
									if ((m_uintaddress<0)|(m_uintaddress>0xffffffff))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ���㵽��λ�õ�ַ�Ѿ���������Χ!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										
										return;
									}

									fwrite(&m_uintaddress,1,4,m_filep);
									
									fflush(m_filep);
				
									/*
									**����ӷ���
									*/

									m_uintaddalldata=Calculateaddall(m_uintaddalldata,m_uintaddress,4);

									break;
								}
							case 2:
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									
									m_warning=m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ�����Ϊ��!";
									
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									
									fcloseall();
									
									return;
									
									break;
								}
								
							case 4:
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									
									m_warning=m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ�����Ϊ��!";
									
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									
									fcloseall();
									
									return;
									
									break;
								}

							case 6:
								{
									/*
									**�ӷ�����Ϊ��ֵ���Զ�����
									*/

									m_wordtowritebin=m_uintaddalldata;

									if ((m_wordtowritebin<0)|(m_wordtowritebin>0xffffffff))
									{
										CString m_warning="�����ļ�ʱ��������λ���ڵ�";
										CString m_colnum;
										CString m_rownum;
										CString m_sheetnum;
										
										m_colnum.Format("%d",iStartCol);
										m_rownum.Format("%d",iStartRow);
										m_sheetnum.Format("%d",nSheetNumber);
										
										m_warning=m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ���㵽��λ�õ�ַ�Ѿ���������Χ!";
										
										AfxMessageBox(m_warning);
										//�ر��ļ�
										m_wbsBooks.Close();
										ExcelApp.Quit();
										//�ͷŶ���  
										m_rgRge.ReleaseDispatch();  
										m_wssheet.ReleaseDispatch();  
										m_wsssheets.ReleaseDispatch();  
										m_wbBook.ReleaseDispatch();  
										m_wbsBooks.ReleaseDispatch();  
										ExcelApp.ReleaseDispatch();  
										
										fcloseall();
										
										return;
									}


									fwrite(&m_wordtowritebin,1,2,m_filep);
									
									fflush(m_filep);
									m_uintaddalldata=0;

									break;
								}

							case 5:
								{
									/*
									**Ԥ����Ϊ��ֵ���Զ����
									*/
			
									m_bytetowritebin=m_fillinblank;

									fwrite(&m_bytetowritebin,1,1,m_filep);
									
									fflush(m_filep);
									/*
									**����ӷ���
									*/

									m_uintaddalldata=Calculateaddall(m_uintaddalldata,m_bytetowritebin,1);
									break;
								}

							default:
								{
									CString m_warning="�����ļ�ʱ��������λ���ڵ�";
									CString m_colnum;
									CString m_rownum;
									CString m_sheetnum;
									
									m_colnum.Format("%d",iStartCol);
									m_rownum.Format("%d",iStartRow);
									m_sheetnum.Format("%d",nSheetNumber);
									
									m_warning=m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ���㵽��λ�õ�ַ�Ѿ���������Χ!";
									
									AfxMessageBox(m_warning);
									//�ر��ļ�
									m_wbsBooks.Close();
									ExcelApp.Quit();
									//�ͷŶ���  
									m_rgRge.ReleaseDispatch();  
									m_wssheet.ReleaseDispatch();  
									m_wsssheets.ReleaseDispatch();  
									m_wbBook.ReleaseDispatch();  
									m_wbsBooks.ReleaseDispatch();  
									ExcelApp.ReleaseDispatch();  
									
									fcloseall();
									
									return;
								}
							}
						}

						else
						{
							CString m_warning="�����ļ�ʱ��������λ���ڵ�";
							CString m_colnum;
							CString m_rownum;
							CString m_sheetnum;
							
							m_colnum.Format("%d",iStartCol);
							m_rownum.Format("%d",iStartRow);
							m_sheetnum.Format("%d",nSheetNumber);
							
							m_warning=m_warning+m_sheetnum+" �ű��"+"�� "+m_rownum+" ��"+"�� "+m_colnum+" ��"+", ��λ�����ݲ�����Ϊ��!";
							
							AfxMessageBox(m_warning);
							//�ر��ļ�
							m_wbsBooks.Close();
							ExcelApp.Quit();
							//�ͷŶ���  
							m_rgRge.ReleaseDispatch();  
							m_wssheet.ReleaseDispatch();  
							m_wsssheets.ReleaseDispatch();  
							m_wbBook.ReleaseDispatch();  
							m_wbsBooks.ReleaseDispatch();  
							ExcelApp.ReleaseDispatch();  
							
							fcloseall();
							
							return;
						}
						}
					}  
				}
			}
			//�ر��ļ�
			m_wbsBooks.Close();
			ExcelApp.Quit();
			//�ͷŶ���  
			m_rgRge.ReleaseDispatch();  
			m_wssheet.ReleaseDispatch();  
			m_wsssheets.ReleaseDispatch();  
			m_wbBook.ReleaseDispatch();  
			m_wbsBooks.ReleaseDispatch();  
			ExcelApp.ReleaseDispatch();  
		}
	/*
	**EXCEL�ļ���ȡ���
	*/

	/*
	**�������ݼӷ��͵ļӷ����Ѿ��߱���������
	*/
	WORD	m_wordaddall=0;
	WORD	m_wordread=0;

	m_filepostion=ftell(m_filep);	//�����ļ�ָ��λ��

	m_filepostioncalculate=0x4E;			//�����������ݼӷ��͵ļӷ��ͳ�ʼλ��

	fseek(m_filep,m_filepostioncalculate,0);	//�ļ�ָ����ת����һ���������ݼӷ���λ�ÿ�ʼ��ȡ����

	while(m_filepostion>m_filepostioncalculate)
	{
		fread(&m_wordread,1,2,m_filep);		

		m_wordaddall=Calculateaddall(m_wordaddall,m_wordread,2);
		
		m_filepostioncalculate+=16;
		
		fseek(m_filep,m_filepostioncalculate,0);

	}
	
	m_filepostioncalculate=4;

	fseek(m_filep,m_filepostioncalculate,0);

	fwrite(&m_wordaddall,1,2,m_filep);

	fseek(m_filep,m_filepostion,0);

	/*
	**�����е��������ļ�·������
	*/

	WORD m_word=0;
	WORD m_AddallAddall=0;
	int	 m_poscalculateup=126;
	int  m_poscalculatedown=126;
	m_strupgeofilepath.Replace(m_strxie,m_strxiexie);	//��һ����б���滻Ϊ˫б��
	m_strdowngeofilepath.Replace(m_strxie,m_strxiexie);	//��һ����б���滻Ϊ˫б��

	m_csupgeofilepath.SetWindowText(m_strupgeofilepath);
	m_csdowngeofilepath.SetWindowText(m_strdowngeofilepath);


	FILE * m_upfilep;
	
	m_upfilep=fopen(m_strupgeofilepath,"rb+");

	FILE * m_downfilep;
	
	m_downfilep=fopen(m_strdowngeofilepath,"rb+");


	/*
	**��ʼ��ȡ�������ݲ�д�뵽�ϲ��ļ���
	*/

	fseek(m_upfilep,0,SEEK_END);	//�Ƚ�ָ�붨λ���ļ���β

	m_filepostion=ftell(m_upfilep);

	fseek(m_upfilep,0,SEEK_SET);

	for (int m_upreadpos=0;m_upreadpos<m_filepostion;m_upreadpos+=2)
	{
		fread(&m_word,1,2,m_upfilep);
		fwrite(&m_word,1,2,m_filep);
		if ((m_upreadpos%m_poscalculateup==0)&(m_upreadpos!=0))
		{
			m_AddallAddall=Calculateaddall(m_AddallAddall,m_word,2);
			m_poscalculateup+=128;
		}
	}
	fclose(m_upfilep);
	/*
	**��ʼ��ȡ��������
	*/

	fseek(m_downfilep,0,SEEK_END);	//�Ƚ�ָ�붨λ���ļ���β
	
	m_filepostion=ftell(m_downfilep);
	
	fseek(m_downfilep,0,SEEK_SET);

//	m_poscalculate=126;

	for (int m_downreadpos=0;m_downreadpos<m_filepostion;m_downreadpos+=2)
	{
		fread(&m_word,1,2,m_downfilep);
		fwrite(&m_word,1,2,m_filep);

		if ((m_downreadpos%m_poscalculatedown==0)&(m_downreadpos!=0))
		{
			m_AddallAddall=Calculateaddall(m_AddallAddall,m_word,2);
			m_poscalculatedown+=128;
		}
	}
	fclose(m_downfilep);
	fseek(m_filep,2,SEEK_SET);	//��λ����ʼλ��
	fwrite(&m_AddallAddall,1,2,m_filep);
	m_csgeoaddallcheck.Format("%02X",m_AddallAddall);
	m_cgeoaddallcheck.SetWindowText(m_csgeoaddallcheck);
	//д���ļ�����ʱ��10-17�ֽ�
	WORD m_wordtime=0;
	WORD m_wordadd=0;

	SYSTEMTIME  m_systime;
	GetLocalTime(&m_systime);
	//����
	m_wordtime=m_systime.wMinute;
	m_wordtime=m_wordtime<<8;
	m_wordtime+=m_systime.wSecond;
	m_wordadd=m_wordtime;
	fseek(m_filep,10,SEEK_SET);
	fwrite(&m_wordtime,1,2,m_filep);

	//��ʱ
	m_wordtime=m_systime.wDay;
	m_wordtime=m_wordtime<<8;
	m_wordtime+=m_systime.wHour;
	m_wordadd+=m_wordtime;
	fseek(m_filep,12,SEEK_SET);
	fwrite(&m_wordtime,1,2,m_filep);

	//����
	m_wordtime=m_systime.wYear-2000;
	m_wordtime=m_wordtime<<8;
	m_wordtime+=m_systime.wMonth;
	m_wordadd+=m_wordtime;
	fseek(m_filep,14,SEEK_SET);
	fwrite(&m_wordtime,1,2,m_filep);

	fseek(m_filep,16,SEEK_SET);
	fwrite(&m_wordadd,1,2,m_filep);


	//�����������У���
	fseek(m_filep,0,SEEK_SET);
	m_filepostion=ftell(m_filep);
	m_AddallAddall=0;
	m_word=0;
	for (int m_manage=0;m_manage<31;m_manage++)
	{
		fread(&m_word,1,2,m_filep);
		m_filepostion=ftell(m_filep);
		m_AddallAddall=Calculateaddall(m_AddallAddall,m_word,2);
	}

	fseek(m_filep,62,SEEK_SET);

	fwrite(&m_AddallAddall,1,2,m_filep);


	fclose(m_filep);
	
	if (m_fileopen==TRUE)
	{
		m_fileopen=FALSE;
	}

	fcloseall();

	AfxMessageBox("�ϳɵ����������!");

}

void CTranslatorDlg::Resendframe()
{
		/*
	**ɱ������ʱ���������ظ����úʹ���ʱ�����
	*/
	
	KillTimer(1);

	/*
	**֡������Ҫ���棬�Ա���Ӧ��λ��Ҫ�����·���
	*/

	/*
	**����֡
	*/
	Sendframe(m_frame1);


	Sleep(SLEEPTIME);	//ϵͳ˯��300ms��������̫�죬����֡��ʧ


	Sendframe(m_frame2);


	Sleep(SLEEPTIME);


	Sendframe(m_frame3);

	Sleep(SLEEPTIME);


	Sendframe(m_frame4);
	m_txlen+=96;
	/*
	**������һ֡����֡��ַ
	*/
//	m_senddatastartaddress=Calculatenextaddress(m_senddatastartaddress);

	/*
	**������Ϣ�Զ�����
	*/

//	SetTimer(2,TIMETODEAL,NULL);

	/*
	**������ʱ��ʱ��
	*/

//	SetTimer(3,m_intmaxtimetowait,NULL);


}

void CTranslatorDlg::Allfuctiondiabled()
{
	m_transfile.EnableWindow(FALSE);
	m_transfilelocation.EnableWindow(FALSE);
	m_sendbutten.EnableWindow(FALSE);
	m_cHexSend.EnableWindow(FALSE);
	m_ctlautosend.EnableWindow(FALSE);
	m_ctrlHexDisplay.EnableWindow(FALSE);
	m_ceditstartaddress.EnableWindow(FALSE);
	m_combosenddistination.EnableWindow(FALSE);
	m_editmaxtimetowait.EnableWindow(FALSE);
	m_editmaxtimestoresend.EnableWindow(FALSE);

}

void CTranslatorDlg::Allfuctionabled()
{
	m_transfile.EnableWindow(TRUE);
	m_transfilelocation.EnableWindow(TRUE);
	m_sendbutten.EnableWindow(TRUE);
	m_cHexSend.EnableWindow(TRUE);
	m_ctlautosend.EnableWindow(TRUE);
	m_ctrlHexDisplay.EnableWindow(TRUE);
	m_ceditstartaddress.EnableWindow(TRUE);
	m_combosenddistination.EnableWindow(TRUE);
	m_editmaxtimetowait.EnableWindow(TRUE);
	m_editmaxtimestoresend.EnableWindow(TRUE);
	

}

void CTranslatorDlg::CheckOnTime()
{

//	SetTimer(2,1000,NULL);
	
}

void CTranslatorDlg::WaittingDSPovertime()
{
	KillTimer(1);
	KillTimer(5);
	AfxMessageBox("�ȴ���λ��Ԥ����Ϣ��ʱ��������Ӳ�������·���!");
}

CString CTranslatorDlg::ComposeWaitingFrame(int numofframe)
{
	CString m_frameall="";				//��֡

	m_frameall+=m_framehead;			//�̶�ͷ

	m_frameall+=m_strsendaddress;		//Ŀ�ĵ�ַ
	
	CString m_strcounter;
	char	m_charcounter;
	CString m_zero="0";

	/*
	**֡����
	*/

	m_strcounter=itoa(Counters(),&m_charcounter,16);
	
	if (m_counters<=15)
	{
		m_strcounter=m_zero+m_strcounter;
	}

	m_frameall+=m_strcounter;

	/*
	**���ݼ���ֵ�жϺϳɾ���֡
	*/
	CString m_frameserial="";

	switch(numofframe)
	{
		case 1:
			m_frameserial="70";
			break;
		case 2:
			m_frameserial="e0";
			break;
		case 3:
			m_frameserial="e1";
			break;
		case 4:
			m_frameserial="e2";
			break;
		default:
			AfxMessageBox("֡�м�������!");
			break;
	}

	m_frameall+=m_frameserial;
	
	CString m_readbinarydata="";
	CString m_waitingdata;
	if(m_bgeo==TRUE)
	{
		m_waitingdata="8899889988AA88AA88AA88AA";
	}
	else
	{
		m_waitingdata="8877887788AA88AA88AA88AA";
	}


	if (1==numofframe)
	{
		/*
		**����֡��ַ��ֵ����������һ֡��ַ
		*/
		CString m_waitingaddress="FFFFFFEE";

		m_frameall+=m_waitingaddress;
		
		/*
		**��ȡ12�ֽڵĶ���������
		*/
		
		m_frameall+=m_waitingdata;

	} 
	else
	{
		/*
		**�޵�ַ����ȡ16�ֽڶ���������
		*/
		CString m_waitingadddata;
		if (m_bgeo==TRUE)
		{
			m_waitingadddata="88AA8899";
		} 
		else
		{
			m_waitingadddata="88AA8877";
		}

		m_frameall+=m_waitingadddata;
		m_frameall+=m_waitingdata;

	}

	m_frameall+=m_readbinarydata;

	
	/*
	**��ʼ����CRC
	*/
	CString m_strcrc16;

	m_strcrc16=CalculatestrCRC(m_frameall, 22);
	

	m_frameall+=m_strcrc16;

	return m_frameall;

}

void CTranslatorDlg::SendReadySignal()
{
	CString m_waitingframe;
	m_waitingframe=ComposeWaitingFrame(1);
	Sendframe(m_waitingframe);
	m_strTXData=m_waitingframe;
	m_strTXData+=m_return;
	m_edittxdata.SetWindowText(m_strTXData);
	Sleep(20);
	m_waitingframe=ComposeWaitingFrame(2);
	Sendframe(m_waitingframe);
	m_strTXData+=m_waitingframe;
	m_strTXData+=m_return;
	m_edittxdata.SetWindowText(m_strTXData);
	Sleep(20);
	m_waitingframe=ComposeWaitingFrame(3);
	Sendframe(m_waitingframe);
	m_strTXData+=m_waitingframe;
	m_strTXData+=m_return;
	m_edittxdata.SetWindowText(m_strTXData);
	Sleep(20);
	m_waitingframe=ComposeWaitingFrame(4);
	Sendframe(m_waitingframe);
	m_strTXData+=m_waitingframe;
	m_strTXData+=m_return;
	m_edittxdata.SetWindowText(m_strTXData);
	Sleep(20);

	m_strTXData.Empty();

}

unsigned int CTranslatorDlg::CStringAddresstoInt(CString m_address)
{
	unsigned int m_uintaddress=0;  //�����ֵ����

	/*
	**ת��Ϊ16������
	*/

	m_uintaddress=strtoul(m_address,NULL,16);

	return m_uintaddress;
}

CString CTranslatorDlg::ComposeOverFrame(int framenume)
{
	CString m_frameall="";				//��֡

	m_frameall+=m_framehead;			//�̶�ͷ

	m_frameall+=m_strsendaddress;		//Ŀ�ĵ�ַ
	
	CString m_strcounter;
	char	m_charcounter;
	CString m_zero="0";

	/*
	**֡����
	*/

	m_strcounter=itoa(Counters(),&m_charcounter,16);
	
	if (m_counters<=15)
	{
		m_strcounter=m_zero+m_strcounter;
	}

	m_frameall+=m_strcounter;

	/*
	**���ݼ���ֵ�жϺϳɾ���֡
	*/
	CString m_frameserial="";

	switch(framenume)
	{
		case 1:
			m_frameserial="70";
			break;
		case 2:
			m_frameserial="e0";
			break;
		case 3:
			m_frameserial="e1";
			break;
		case 4:
			m_frameserial="e2";
			break;
		default:
			AfxMessageBox("֡�м�������!");
			break;
	}

	m_frameall+=m_frameserial;
	
	CString m_readbinarydata="";

	CString m_waitingdata="FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";

	m_frameall+=m_waitingdata;

	
	/*
	**��ʼ����CRC
	*/
	CString m_strcrc16;

	m_strcrc16=CalculatestrCRC(m_frameall, 22);
	

	m_frameall+=m_strcrc16;

	return m_frameall;

}

void CTranslatorDlg::TimeCalculate()
{
	CString m_strhour="";
	CString m_strminute="";
	CString m_strsecond="";
	CString m_strlefthour="";
	CString m_strleftminute="";
	CString m_strleftsecond="";
/*
	m_lefthour=0;
	m_leftminute=0;
	m_leftsecond=0;
	m_counterhour=0;
	m_counterminute=0;
	m_countersecond=0;
*/
	//��ȥʱ��
	m_countersecond++;
	if (m_countersecond>=60)
	{

		m_counterminute++;
		m_countersecond=0;
		if (m_counterminute>=60)
		{
			m_counterhour++;
			m_counterminute=0;
		}
	}

	if (m_counterhour!=0)
	{
		 m_strhour.Format("%d",m_counterhour);
		 m_strhour+=" Сʱ";
	}

	if (m_counterminute!=0)
	{
		m_strminute.Format("%d",m_counterminute);
		m_strminute+=" ��";
	}

	m_strsecond.Format("%d",m_countersecond);
	m_strsecond+=" ��";

	m_strcountertime=m_strhour+m_strminute+m_strsecond;
	
	m_cscountertime.SetWindowText(m_strcountertime);

	//ʣ��ʱ����㹫ʽΪ:ʣ�����*�����ݰ����ͼ��+5��֡���Ϊ5��sleep����

	m_leftsecond=m_intcounterdatanum*(FRAMELAP+PACKAGELAP+10)/1000;

	if (m_leftsecond>60)
	{
		m_leftminute=m_leftsecond/60;
		m_leftsecond=m_leftsecond%60;
	}

	m_strleftsecond.Format("%d",m_leftsecond);
	m_strleftsecond+=" ��";

	if (m_leftminute>60)
	{
		m_lefthour=m_leftminute/60;
		m_leftminute=m_leftminute%60;

		m_strleftminute.Format("%d",m_leftminute);
		m_strleftminute+=" ��";
		m_strlefthour.Format("%d",m_lefthour);
		m_strlefthour+=" Сʱ";
	}

	m_strlefttime=m_strlefthour+m_strleftminute+m_strleftsecond;

	m_cslefttime.SetWindowText(m_strlefttime);

}

void CTranslatorDlg::ReceiveCom()
{
	int datalenth;
	byte buffer[1000];
	CString m_str;
	datalenth = Rscom.GetInputSize();
	if(datalenth > 0)
	{
		Rscom.Read(buffer, datalenth , 10U);
		for(int i=0 ; i< datalenth ; i++)
		{
			m_rxbuffer[i] = buffer[i];
			m_str.Format("%02X",buffer[i]);
			m_strexceldata+=m_str;
		}
		m_strexceldata+="\n";

		if (m_strexceldata.GetLength()>4096)
		{
			m_strexceldata="";
		}

		m_editexceldata.SetWindowText(m_strexceldata);
		int   nLen   =   m_editexceldata.SendMessage(WM_GETTEXTLENGTH);
		m_editexceldata.SetSel(nLen,   nLen,   FALSE); 
		if ((m_rxbuffer[0]==0xfc)&&(m_rxbuffer[5]==0x70)&&(m_bsendbutten==TRUE))
		{
			if ((m_rxbuffer[6]==0xee)&&(m_rxbuffer[7]==0xff))
			{
				//�����ı䣬�ٴε��÷��͹���
				m_cansend=TRUE;
				
				KillTimer(1);	//ֹͣ����ready�ź�
				
				m_strrebackinfomation="Ԥ��";
				
				SetTimer(3,100,NULL); //�˶�ʱ��ֻ��һ�飬��ʱд����
				
				m_dealframe=TRUE;
				
				m_csrebackinfomation.SetWindowText(m_strrebackinfomation);
			}

			if ((m_rxbuffer[6]==0xdd)&&(m_rxbuffer[7]==0xdd))
			{
					m_strrebackinfomation="����У��ɹ�";
					
					m_csrebackinfomation.SetWindowText(m_strrebackinfomation);
			}

			if ((m_rxbuffer[6]==0x77)&&(m_rxbuffer[7]==0x77))
			{
				m_strrebackinfomation="����У��ʧ��";
				
				m_csrebackinfomation.SetWindowText(m_strrebackinfomation);
			}
		}
		
	}
}

void CTranslatorDlg::SendCom()
{

//	Rscom.Write(sendbuffer,24);
}

BOOL CTranslatorDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DestroyWindow();
}

void CTranslatorDlg::OnClearbutton() 
{
	// TODO: Add your control notification handler code here
		m_strexceldata="";

		m_editexceldata.SetWindowText(m_strexceldata);
}

void CTranslatorDlg::WriteSendData(CString m_str)
{
	CFile m_file;
	m_file.Open("RunningRecoder.txt",CFile::modeWrite|CFile::modeCreate|CFile::modeNoTruncate);
	m_str+="\r\n";
	m_file.SeekToEnd();
	m_file.Write(m_str,m_str.GetLength());
	m_file.Close();
}
