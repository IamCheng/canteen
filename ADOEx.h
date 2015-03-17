// ADOEx.h: interface for the CADOEx class.
// ADO��װ��

//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADOEX_H__447C7707_7CA7_4B96_BAF5_389F7E09437D__INCLUDED_)
#define AFX_ADOEX_H__447C7707_7CA7_4B96_BAF5_389F7E09437D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4146)																		//���ξ���
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")	//����ADO DLL

class CADOEx  
{
public:
	int GetSingleStringNum(CString strMulti,CString strSplit);
	int GetIndexOfString(CString strSource,CString strFind,CString strSplit="->");
	BOOL GetConnectState();							//��ȡ����״̬
	long GetRecordColNum();							//��ȡ��¼����
	long GetRecordCount();							//��ȡ��¼����
	void CloseRecordset();							//�رռ�¼��	

	BOOL ExecuteNotSelSQL(CString strNotSelSQL);	//ִ�з�select���

	BOOL ExecuteSelSQL(CString strSelectSQL);		//ִ��select���
	BOOL ExecuteSelSQL(CString strSelectSQL,CString strFieldName,CStringArray& strResult);

	BOOL ExecuteSelSQL(CString strSelectSQL,CStringArray& strFieldName,CStringArray& strResult,CString strSplit="*@#$*");
	CString GetSingleString(CString strMulti,int nIndex,CString strSplit="*@#$*");	
	
	void DisConnect();								//�ر�����
	BOOL Connect(CString strLinkDB);				//�������ݿ�

	CADOEx();										//���캯��
	virtual ~CADOEx();								//��������

protected:
	BOOL bState;				//����״̬
	_RecordsetPtr m_pRs;		//��¼������
	_CommandPtr m_pCmd;			//�������
	_ConnectionPtr m_pConn;		//���Ӷ���
};

#endif // !defined(AFX_ADOEX_H__447C7707_7CA7_4B96_BAF5_389F7E09437D__INCLUDED_)
