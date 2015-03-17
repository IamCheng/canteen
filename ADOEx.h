// ADOEx.h: interface for the CADOEx class.
// ADO封装类

//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADOEX_H__447C7707_7CA7_4B96_BAF5_389F7E09437D__INCLUDED_)
#define AFX_ADOEX_H__447C7707_7CA7_4B96_BAF5_389F7E09437D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4146)																		//屏蔽警告
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")	//导入ADO DLL

class CADOEx  
{
public:
	int GetSingleStringNum(CString strMulti,CString strSplit);
	int GetIndexOfString(CString strSource,CString strFind,CString strSplit="->");
	BOOL GetConnectState();							//获取连接状态
	long GetRecordColNum();							//获取记录列数
	long GetRecordCount();							//获取记录行数
	void CloseRecordset();							//关闭记录集	

	BOOL ExecuteNotSelSQL(CString strNotSelSQL);	//执行非select语句

	BOOL ExecuteSelSQL(CString strSelectSQL);		//执行select语句
	BOOL ExecuteSelSQL(CString strSelectSQL,CString strFieldName,CStringArray& strResult);

	BOOL ExecuteSelSQL(CString strSelectSQL,CStringArray& strFieldName,CStringArray& strResult,CString strSplit="*@#$*");
	CString GetSingleString(CString strMulti,int nIndex,CString strSplit="*@#$*");	
	
	void DisConnect();								//关闭连接
	BOOL Connect(CString strLinkDB);				//连接数据库

	CADOEx();										//构造函数
	virtual ~CADOEx();								//析构函数

protected:
	BOOL bState;				//连接状态
	_RecordsetPtr m_pRs;		//记录集对象
	_CommandPtr m_pCmd;			//命令对象
	_ConnectionPtr m_pConn;		//连接对象
};

#endif // !defined(AFX_ADOEX_H__447C7707_7CA7_4B96_BAF5_389F7E09437D__INCLUDED_)
