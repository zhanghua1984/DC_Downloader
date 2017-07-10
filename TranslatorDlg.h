// TranslatorDlg.h : header file
//

#if !defined(AFX_COMMTESTDLG_H__094EF006_CBE0_11D7_B4F9_00E04C74763F__INCLUDED_)
#define AFX_COMMTESTDLG_H__094EF006_CBE0_11D7_B4F9_00E04C74763F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <fstream.h>
#include <iostream>
#include "comdef.h"  
#include "excel.h"  
#include "winuser.h"
#include "windows.h"
#include "SerialPort.h"
#include "CnComm.h"
#define MAXBLOCK 2400
#define XON 0x11
#define XOFF 0x13
#define DATALENTH 960   //每帧发送60个字节，16位对齐便于人查看数据，共同配置数据为330字节，取最小公倍数为480
#define TIMETODEAL 500  //定时器设定处理时间
#define GEOCRCDATALENTH 126	//地理数据计算CRC需读取的数据长度
#define SLEEPTIME 1	//系统睡眠时间，等待串口数据操作
#define FRAMELAP 1
#define PACKAGELAP 10
/////////////////////////////////////////////////////////////////////////////
// CTranslatorDlg dialog

class CTranslatorDlg : public CDialog
{
// Construction
public:
	void WriteSendData(CString m_str);
	void SendCom();
	void ReceiveCom();
	void TimeCalculate();
	CString ComposeOverFrame(int framenume);
	unsigned int CStringAddresstoInt(CString m_address);
	void SendReadySignal();
	CString ComposeWaitingFrame(int numofframe);
	void WaittingDSPovertime();
	void CheckOnTime();
	void Allfuctionabled();
	void Allfuctiondiabled();
	void Resendframe();
	unsigned int Calculateaddall ( unsigned int m_addall , unsigned int m_currentadd, int m_addsize);
	void Writebinarydata(CString m_binfilefullpath, unsigned int data, int datasize);
	CString Resolvecommand(CString command);
	void Composeresendoverframe();
	void Sendframe(CString m_frame);
	CString CalculatestrCRC(CString strtocrc,int lenth);
	CString Readbinary(long int startadd,int lenth);
	CString Composeframe(int numofframe);
	CString Calculatenextaddress(CString prvaddress);
	void Overtime();
	void Sendbinarydata();
	CString Geosetbinarypath();
	void Closebinfile();
	void Openbinfile();
	CString Setbinarypath();
	BOOL Writebintofile(int inttowrite);
	int Cstringtobinary(CString str);
	int Counters();
	byte	m_rxbuffer[1000];
	int	m_intcounterdatanum;
	int m_intcounterdatanumup;
	int m_binfilelenthtocalulate;
	int m_nBaud;       //波特率
	int m_nCom;         //串口号
	char m_cParity;    //校验
	int m_nDatabits;    //数据位
	int m_nStopbits;    //停止位
	DWORD m_dwCommEvents;
	CSerialPort m_Port[4];  //CSerialPort类对象
	int m_nBaud2;       //波特率
	int m_nCom2;         //串口号
	char m_cParity2;    //校验
	int m_nDatabits2;    //数据位
	int m_nStopbits2;    //停止位
	long m_rxdatalenth;
	CString m_rxstrdata;
	CString m_rxstrtodisplay;
	CString m_return;
	long m_rxlen;
	long m_rxlenth;
	long m_txlen;
	long m_crclen;
	long m_counter;
	long m_lostframe;
	long m_countertodispatch;
	BOOL b_fileopen;
	BOOL m_cansend;
	CString m_binfilefullpath;
	BOOL m_firsttime;
	BOOL m_dealframe;
	unsigned int m_intstartaddress;
	unsigned int m_intwanttoreadaddress;
	void DispStatus();
	void CloseConnection();
	BOOL ProcessCOMMNotification (UINT wParam,long lParam);
	BOOL m_portstatu_but;
	BOOL m_bAutoSend;
	char ConvertHexData(char ch);
	int String2Hex(CString str, char *SendOut);
//	int WriteBlock(char *abOut,int MaxLength);
//	int ReadBlock(BYTE *abIn,int MaxLength);
	volatile int m_bConnected;
	BOOL OpenComm(int Num);
	BOOL SetCommParameter();
	HANDLE m_hCom;
	CWinThread *m_pThread;
	CFile getdatafile;
	CFile m_sendfile;
	BOOL  m_boolresend;
	unsigned short int Get_CRC16_Code(unsigned char* pchMsg, unsigned short int wDataLen);
	int crc16(unsigned char *puchMsg, unsigned int usDataLen);
	int		m_inttowrite;
	int	m_intmaxtimetowait;
	int	m_intmaxtimestowait;
	long int m_binfilelenth;
	CString  m_senddatastartaddress;
	int	m_Errorframecounter;
	int	m_counterofframe;
	CString m_frame1,m_frame2,m_frame3,m_frame4,m_resendframe,m_overframe;
	int m_binreadcounter;
	CString	m_framecommand;
	int	m_lefthour;
	int m_leftminute;
	int m_leftsecond;
	int m_counterhour;
	int m_counterminute;
	int m_countersecond;
	byte	m_rx[24];
	int m_rxnumber;
	BOOL m_bgeo;
	BOOL m_bsendbutten;
//	volatile HANDLE m_hPostMsgEvent;
//	volatile HWND hPostToWnd;
	OVERLAPPED m_osRead,m_osWrite; 
	CTranslatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTranslatorDlg)
	enum { IDD = IDD_COMMTEST_DIALOG };
	CEdit	m_cgeoaddallcheck;
	CStatic	m_cscountertime;
	CStatic	m_cslefttime;
	CButton	m_transfilelocation;
	CStatic	m_csrebackinfomation;
	CStatic	m_cscounterforcurrentsend;
	CStatic	m_cscounterforallbytesend;
	CStatic	m_cscounterforleftdata;
	CStatic	m_cscounterfordataall;
	CStatic	m_cscounterforframeindata;
	CStatic	m_cscounterforallsend;
	CStatic	m_csdowngeofilepath;
	CStatic	m_cssynthesizegeofilepath;
	CStatic	m_csupgeofilepath;
	CStatic	m_csframeheadexcelfilepath;
	CStatic	m_cscounterforcols;
	CStatic	m_cscounterforrows;
	CStatic	m_cscounterforsheets;
	CButton	m_ctlautosend;
	CStatic	m_cscounterforlefttosend;
	CEdit	m_editmaxtimestoresend;
	CEdit	m_editmaxtimetowait;
	CComboBox	m_combosenddistination;
	CEdit	m_ceditstartaddress;
	CStatic	m_sbinfilepath;
	CEdit	m_editbindata;
	CEdit	m_editexceldata;
	CButton	m_emptyrx;
	CStatic	m_filename;
	CButton	m_cHexSend;
	CButton	m_emptytx;
	CButton	m_transfile;
	CButton	m_sendbutten;
	CEdit	m_edittxdata;
	CStatic	m_sFilePath;
	CStatic	m_sEXCELFilePath;
	CStatic	m_cscounterforleft;
	CEdit	m_EditRXData;
	CButton	m_ctrlHexDisplay;
	CButton	m_judgesend;
	CComboBox	m_ComboStop;
	CComboBox	m_ComboJiaoyan;
	CComboBox	m_ComboData;
	CComboBox	m_ComboBaud;
	CComboBox	m_ComboSeriou;
	CString	m_SeriouStr;
	CString	m_BaudStr;
	CString	m_StopStr;
	CString	m_savefilename;
	CString m_savesendrecoder;
	CString	m_strTXData;
	CString	m_filepath;
	CString	m_strcounterforleft;
	CString	m_EXCELfilepath;
	CString m_frameheadexcelfilepath;
	CString m_upgeofilepath;
	CString m_downgeofilepath;
	CString	m_strRXData;
	CString	m_JiaoyanStr;
	CString	m_DataStr;
	CString m_NULL;
	CString m_strcrcData;
	CString m_senddateall;
	CString	m_Workerstatustr;
	CString m_Readdistancestr;
	CString	m_strexceldisplay;
	CString	m_strbindisplay;
	CString m_sendworkerstatustr;
	CString m_sendreaddistancestr;
	CString m_sendbuzzerstr;
	CString m_sendfruinfostr;
	CString m_sendpowerstr;
	INT		m_sendworks;
	INT		m_sendreadd;
	INT		m_sendbuzz;
	INT		m_sendfru;
	INT		m_sendpow;
	CString m_framehead;
	CString	m_framesequence;
	CString	m_framenull;
	int m_counters;
	CString	m_strbindata;
	CString	m_strexceldata;
	BOOL	m_fileopen;
	CString	m_strbinfilepath;
	CString	m_strstartaddress;
	CString	m_strsenddistination;
	CString	m_strmaxtimetowait;
	CString	m_strmaxtimetoresend;
	CString	m_strcounterforlefttosend;
	CString m_strsendaddress;
	CString	m_strcounterforsheets;
	CString	m_strcounterforrows;
	CString	m_strcounterforcols;
	CString	m_strframeheadexcelfilepath;
	CString	m_strupgeofilepath;
	CString	m_strsynthesizegeofilepath;
	CString	m_strdowngeofilepath;
	CString	m_strcounterforallsend;
	CString	m_strcounterforcurrentsend;
	CString	m_strcounterforframeindata;
	CString	m_strcounterfordataall;
	CString	m_strcounterforleftdata;
	CString	m_strcounterforallbytesend;
	CString	m_strrebackinfomation;
	CString	m_strlefttime;
	CString	m_strcountertime;
	CString	m_csgeoaddallcheck;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTranslatorDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	cnComm Rscom;
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTranslatorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LONG OnCommunication(WPARAM ch, LPARAM port);
	afx_msg void OnSelchangeComboSeriou();
	afx_msg void OnButtenMenualsend();
	afx_msg void OnButtonTransfile();
	afx_msg void OnCheckAutosend();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonEmptytext();
	afx_msg void OnCheckWritetofile();
	afx_msg void OnButtonFilename();
	afx_msg void OnButtonSaveedit();
	afx_msg void OnButtonEmptyrx();
	afx_msg void OnButtonPortstatu();
	afx_msg void OnButtonClose();
	afx_msg void OnSelchangeComboBaud();
	afx_msg void OnSelchangeComboData();
	afx_msg void OnSelchangeComboJiaoyan();
	afx_msg void OnSelchangeComboStop();
	afx_msg void OnSelchangeComboWorkstatus();
	afx_msg void OnSelchangeComboReaddistance();
	afx_msg void OnSelchangeComboBuzzer();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonReset();
	afx_msg void OnButtonExcelselect();
	afx_msg void OnButtonExceltobin();
	afx_msg void OnButtonExceltobinlocation();
	afx_msg void OnButtonTransfilelocation();
	afx_msg void OnEditchangeComboSenddistination();
	afx_msg void OnSelchangeComboSenddistination();
	afx_msg void OnButtonSelectframehead();
	afx_msg void OnButtonSelectupgeo();
	afx_msg void OnButtonSelectdowngeo();
	afx_msg void OnButtonSynthesizegeo();
	afx_msg void OnClearbutton();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void addall();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMTESTDLG_H__094EF006_CBE0_11D7_B4F9_00E04C74763F__INCLUDED_)
