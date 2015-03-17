// ADOEx.cpp: implementation of the CADOEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADOEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/************************************************************************/
/* ADO封装类，屏蔽底层操作细节，减少工作量                              */
/************************************************************************/

CADOEx::CADOEx()									//构造函数
{
	CoInitialize(NULL);								//COM初始化

	bState=FALSE;									//连接状态为false
	m_pConn.CreateInstance(__uuidof(Connection));	//创建COM对象
	m_pRs.CreateInstance(__uuidof(Recordset));
	m_pCmd.CreateInstance(__uuidof(Command));
}

CADOEx::~CADOEx()									//析构函数
{
	if(m_pRs->State!=adStateClosed)					//关闭记录集
		m_pRs->Close();
	m_pRs.Release();								//释放对象
	m_pRs=NULL;

	if(m_pConn->State!=adStateClosed)				//关闭连接
		m_pConn->Close();
	m_pConn.Release();							
	m_pConn=NULL;

	m_pCmd.Release();
	m_pCmd=NULL;
}

//参数strLinkDB：连接字符串
//返回值：连接成功返回TRUE
BOOL CADOEx::Connect(CString strLinkDB)				//连接数据库
{
	HRESULT hr;
	_bstr_t bstrConn=(_bstr_t)strLinkDB;			//类型转换
	try
	{
		DisConnect();
		m_pConn->ConnectionTimeout=8;				//连接超时时间
		hr=m_pConn->Open(bstrConn,"","",adModeUnknown);	//打开连接
		if(FAILED(hr))								//若连接失败
		{
			bState=FALSE;
			return FALSE;
		}
	}
	catch(_com_error& e)
	{
		e.ErrorMessage();
		bState=FALSE;
		return FALSE;
	}
	bState=TRUE;
	return TRUE;
}

void CADOEx::DisConnect()							//关闭连接
{
	if(m_pConn->State!=adStateClosed)
		m_pConn->Close();
	bState=FALSE;
}

//strSelectSQL:查询SQL语句
//返回值：执行成功返回TRUE
BOOL CADOEx::ExecuteSelSQL(CString strSelectSQL)	//查询语句执行
{
	try
	{
		CloseRecordset();							//关闭记录集
		m_pRs->CursorLocation=adUseClient;			//设置游标为客户端
		m_pRs->Open(_variant_t(strSelectSQL),_variant_t((IDispatch*)m_pConn,true),adOpenDynamic,adLockOptimistic,adCmdText);
		//执行查询
		
		if(m_pRs->GetRecordCount()==0)				//若返回记录数为0
			return FALSE;
	}
	catch(_com_error& e)
	{
		AfxMessageBox(e.ErrorMessage());			//显示错误信息
		return FALSE;
	}
	return TRUE;
}

//strSelectSQL：查询SQL语句
//strFieldName：要查询的单字段名
//strResult：查询结果存放处，为输出变量
//返回值：查询成功返回TRUE
BOOL CADOEx::ExecuteSelSQL(CString strSelectSQL,CString strFieldName, CStringArray &strResult)	//单字段查询函数
{
	try
	{
		strResult.RemoveAll();							//清空结果数组

		if(ExecuteSelSQL(strSelectSQL)!=FALSE)			//若select语句执行成功
		{
			strResult.SetSize(m_pRs->GetRecordCount());	//设置结果数组大小
			
			for(int i=0;i<m_pRs->GetRecordCount();i++)	//记录集遍历
			{
				CString strValue;
				_variant_t var=m_pRs->GetCollect((_bstr_t)strFieldName);	//获取指定字段值
				if(var.vt!=VT_NULL)						//若字段值不为空
					strValue=(char*)(_bstr_t)var;		//转为字符串
				else
					strValue=" ";						//若为空，设为空格
				strResult.SetAtGrow(i,strValue);		//加入结果数组中
				
				m_pRs->MoveNext();						//记录移至下一行
			}
			return TRUE;
		}
	}
	catch(_com_error& e) 
	{
		AfxMessageBox(e.ErrorMessage());				//显示错误提示
		return FALSE;
	}
	
	return FALSE;
}

//strNotSelSQL：非select查询语句，如insert、delete、update
//返回值：执行成功返回TRUE
BOOL CADOEx::ExecuteNotSelSQL(CString strNotSelSQL)		//执行更新操作
{
	try
	{
		CloseRecordset();								//关闭记录集
		_variant_t vResult;
		vResult.vt=VT_ERROR;
		vResult.scode=DISP_E_PARAMNOTFOUND;

		m_pCmd->ActiveConnection=m_pConn;				
		m_pCmd->CommandText=(_bstr_t)strNotSelSQL;		//命令内容
		m_pRs=m_pCmd->Execute(&vResult,&vResult,adCmdText);	//执行命令
	}
	catch(_com_error& e)
	{
		AfxMessageBox(e.ErrorMessage());				//显示错误信息
		return FALSE;
	}
	return TRUE;
}

void CADOEx::CloseRecordset()							//关闭记录集
{
	if(m_pRs->State!=adStateClosed)
		m_pRs->Close();
}

long CADOEx::GetRecordCount()							//获取记录集行数
{
	if(m_pRs->State==adStateClosed)						//若记录集关闭，返回0
		return 0;
	
	m_pRs->MoveFirst();									//移至首行
	while(!m_pRs->adoEOF)
		m_pRs->MoveNext();								//从首行移至尾行
	long nCount=m_pRs->GetRecordCount();				//获取记录行数
	m_pRs->MoveFirst();										
	return nCount;										//返回行数
}

long CADOEx::GetRecordColNum()							//获取记录集列数
{
	if(m_pRs->State==adStateClosed)
		return 0;

	long nCount=m_pRs->Fields->Count;				
	return nCount;										//返回字段数
}

BOOL CADOEx::GetConnectState()							//获取连接状态
{
	return bState;
}

//strMulti：多分隔符字符串，类似 "a->b->c->d"
//strSplit：分隔符，类似 "->"	
//返回值：返回子字符串个数，如上，返回4
int CADOEx::GetSingleStringNum(CString strMulti, CString strSplit)		//获取多分隔符字符串中子字符串个数
{
	if(!strMulti.IsEmpty())												//若不为空
	{
		int nSplitCount=strMulti.Replace(strSplit,strSplit);			//获取分隔符个数
		return nSplitCount+1;											//返回子字符串个数
	}
	return 0;															
}

//strMulti：多分隔符字符串，类似 "a->b->c->d"
//nIndex：子字符串序号(从1开始)，类似 3
//strSplit：分隔符，类似 "->"
//返回值：返回子字符串值，如上，返回 "c"
CString CADOEx::GetSingleString(CString strMulti, int nIndex, CString strSplit)	//获取多分隔符字符串中某个子字符串
{
	CString strAim="";						
	if(!strMulti.IsEmpty())														//若不为空
	{
		int nSplitCount=strMulti.Replace(strSplit,strSplit);					//获取分隔符个数
		if(nIndex>nSplitCount+1 || nIndex<1 || nSplitCount==0)					//若序号大于总数目，或序号小于1，或分隔符为0
			return "";															//返回空值

		if(nIndex==1)															//若序号为1
		{
			int nBegin=0;
			if((nBegin=strMulti.Find(strSplit,nBegin))!=-1)						//查找第一个分隔符左边的字符串
			{
				strAim=strMulti.Left(nBegin);
			}
		}
		else if(nIndex==nSplitCount+1)											//若序号为最后一个
		{
			int nBegin=0,nPlace=0;
			while((nBegin=strMulti.Find(strSplit,nBegin))!=-1)					//查找最后一个分隔符位置
			{
				nPlace=nBegin++;
			}
			if(nPlace)															//获取最后一个分隔符右边的字符串
			{
				strAim=strMulti.Right(strMulti.GetLength()-nPlace-strSplit.GetLength());
			}
		}
		else																	//若为中间序号
		{
			int nBeginPlacePre=0,nSplitIndex=0,nBeginPlaceNext=0;
			while((nBeginPlacePre=strMulti.Find(strSplit,nBeginPlacePre))!=-1)	//从前往后查找分隔符
			{
				nSplitIndex++;													//分隔符数目递增	
				if(nSplitIndex==nIndex-1)										//若到指定序号
				{
					if((nBeginPlaceNext=strMulti.Find(strSplit,nBeginPlacePre+1))!=-1)	//查找下一个分隔符位置
					{
						strAim=strMulti.Mid(nBeginPlacePre+strSplit.GetLength(),nBeginPlaceNext-nBeginPlacePre-strSplit.GetLength());
						//获取两个分隔符之间的字符串

						return strAim;
					}
				}
				else															//若没到指定序号，继续查找	
					nBeginPlacePre++;
			}
		}
	}
	return strAim;		//返回子字符串值
}

//strSelectSQL：查询SQL语句
//strFieldName：要查询的字段列表，多字段查询 注：CStringArray作为参数要以引用形式传递，不可值传递
//strResult：字段结果存放处，为输出变量
//strSplit：分隔符，每条记录中多个字段的值之间分隔以作区分
//返回值：若查询成功，返回TRUE
BOOL CADOEx::ExecuteSelSQL(CString strSelectSQL, CStringArray &strFieldName, CStringArray &strResult,CString strSplit)  //多字段查询
{
	try
	{
		strResult.RemoveAll();								//结果数组清空

		if(ExecuteSelSQL(strSelectSQL)!=FALSE)				//若执行sql成功
		{	
			strResult.SetSize(m_pRs->GetRecordCount());		//设置数组大小
			for(int i=0;i<m_pRs->GetRecordCount();i++)		//记录集遍历
			{
				CString strValue;
				for(int j=0;j<strFieldName.GetSize();j++)	//要查询的字段遍历
				{
					_variant_t var=m_pRs->GetCollect((_bstr_t)strFieldName.GetAt(j));	//获取字段值
					if(var.vt!=VT_NULL)						//若值不为空
						strValue+=(char*)(_bstr_t)var;		//转为字符串
					else
						strValue+=" ";
					if(j!=strFieldName.GetSize()-1)			//若当前字段不是最后一个	
						strValue+=strSplit;					//字段值后加上分隔符
				}
				strResult.SetAtGrow(i,strValue);			//添加至结果数组
				m_pRs->MoveNext();							//记录集移至下一行
			}
			return TRUE;
		}
	}
	catch(_com_error& e)
	{
		AfxMessageBox(e.ErrorMessage());					//显示错误信息
		return FALSE;
	}
	return FALSE;
}

//strSource：源字符串，类似于 "a->b->c->d"
//strFind：要查找的子字符串，类似于 "b"
//strSplit：分隔符，类似于 "->"
//返回值：子字符串在源字符串的序号，如上，返回2
int CADOEx::GetIndexOfString(CString strSource, CString strFind, CString strSplit)
{
/*	int nIndex=strSource.Find(strFind);	//模糊查找
										
	if(nIndex==-1)						//注：假设 strSource为"ac->bd->fg"，而strFind为"b"
		return 0;						//	  若模糊查找，则返回2
	else								//	  若精确查找，则返回0
	{
		CString strLeft=strSource.Left(nIndex+1);
		int nCount=strLeft.Replace(strSplit,strSplit);
		
		return nCount+1;
	}*/

	CString strTemp;	//精确查找

	int nIndex;

	nIndex=strSource.Find(strSplit+strFind+strSplit);	//查找形式类似 "->aa->"
	if(nIndex!=-1)										//若找到
	{
		CString strLeft=strSource.Left(nIndex+strSplit.GetLength()+1);	//获取要查找字符串左边的分隔符数目
		int nCount=strLeft.Replace(strSplit,strSplit);

		return nCount+1;								//返回序号
	}
	else												//若没找到 "->aa->"
	{
		nIndex=strSource.Find(strSplit+strFind);	//查找形式类似 "->aa"，即目标字符串处于最后面的情况
		if(nIndex!=-1)								//若找到
		{
			if((nIndex+strSplit.GetLength()+strFind.GetLength())==strSource.GetLength())	//若确实处于最后面
			{
				int nCount=strSource.Replace(strSplit,strSplit);							//获取所有分隔符数目
				return nCount+1;															//返回序号
			}
		}
		else										//若也没找到 "->aa"
		{
			nIndex=strSource.Find(strFind+strSplit);	//查找形式类似 "aa->"，即目标字符串处于最前面的情况
			if(nIndex!=-1)								//若找到
			{
				if(nIndex==0)							//若确实处于最前面
					return 1;							//返回1
				else									//若也没找到 "->aa"
				{
					if(strFind.GetLength()==strSource.GetLength())	//若目标字符串长度等于源
						return 1;									//返回1
					return 0;
				}
			}
		}
		return 0;										//若没找到，返回0
	}
}
