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
/* ADO��װ�࣬���εײ����ϸ�ڣ����ٹ�����                              */
/************************************************************************/

CADOEx::CADOEx()									//���캯��
{
	CoInitialize(NULL);								//COM��ʼ��

	bState=FALSE;									//����״̬Ϊfalse
	m_pConn.CreateInstance(__uuidof(Connection));	//����COM����
	m_pRs.CreateInstance(__uuidof(Recordset));
	m_pCmd.CreateInstance(__uuidof(Command));
}

CADOEx::~CADOEx()									//��������
{
	if(m_pRs->State!=adStateClosed)					//�رռ�¼��
		m_pRs->Close();
	m_pRs.Release();								//�ͷŶ���
	m_pRs=NULL;

	if(m_pConn->State!=adStateClosed)				//�ر�����
		m_pConn->Close();
	m_pConn.Release();							
	m_pConn=NULL;

	m_pCmd.Release();
	m_pCmd=NULL;
}

//����strLinkDB�������ַ���
//����ֵ�����ӳɹ�����TRUE
BOOL CADOEx::Connect(CString strLinkDB)				//�������ݿ�
{
	HRESULT hr;
	_bstr_t bstrConn=(_bstr_t)strLinkDB;			//����ת��
	try
	{
		DisConnect();
		m_pConn->ConnectionTimeout=8;				//���ӳ�ʱʱ��
		hr=m_pConn->Open(bstrConn,"","",adModeUnknown);	//������
		if(FAILED(hr))								//������ʧ��
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

void CADOEx::DisConnect()							//�ر�����
{
	if(m_pConn->State!=adStateClosed)
		m_pConn->Close();
	bState=FALSE;
}

//strSelectSQL:��ѯSQL���
//����ֵ��ִ�гɹ�����TRUE
BOOL CADOEx::ExecuteSelSQL(CString strSelectSQL)	//��ѯ���ִ��
{
	try
	{
		CloseRecordset();							//�رռ�¼��
		m_pRs->CursorLocation=adUseClient;			//�����α�Ϊ�ͻ���
		m_pRs->Open(_variant_t(strSelectSQL),_variant_t((IDispatch*)m_pConn,true),adOpenDynamic,adLockOptimistic,adCmdText);
		//ִ�в�ѯ
		
		if(m_pRs->GetRecordCount()==0)				//�����ؼ�¼��Ϊ0
			return FALSE;
	}
	catch(_com_error& e)
	{
		AfxMessageBox(e.ErrorMessage());			//��ʾ������Ϣ
		return FALSE;
	}
	return TRUE;
}

//strSelectSQL����ѯSQL���
//strFieldName��Ҫ��ѯ�ĵ��ֶ���
//strResult����ѯ�����Ŵ���Ϊ�������
//����ֵ����ѯ�ɹ�����TRUE
BOOL CADOEx::ExecuteSelSQL(CString strSelectSQL,CString strFieldName, CStringArray &strResult)	//���ֶβ�ѯ����
{
	try
	{
		strResult.RemoveAll();							//��ս������

		if(ExecuteSelSQL(strSelectSQL)!=FALSE)			//��select���ִ�гɹ�
		{
			strResult.SetSize(m_pRs->GetRecordCount());	//���ý�������С
			
			for(int i=0;i<m_pRs->GetRecordCount();i++)	//��¼������
			{
				CString strValue;
				_variant_t var=m_pRs->GetCollect((_bstr_t)strFieldName);	//��ȡָ���ֶ�ֵ
				if(var.vt!=VT_NULL)						//���ֶ�ֵ��Ϊ��
					strValue=(char*)(_bstr_t)var;		//תΪ�ַ���
				else
					strValue=" ";						//��Ϊ�գ���Ϊ�ո�
				strResult.SetAtGrow(i,strValue);		//������������
				
				m_pRs->MoveNext();						//��¼������һ��
			}
			return TRUE;
		}
	}
	catch(_com_error& e) 
	{
		AfxMessageBox(e.ErrorMessage());				//��ʾ������ʾ
		return FALSE;
	}
	
	return FALSE;
}

//strNotSelSQL����select��ѯ��䣬��insert��delete��update
//����ֵ��ִ�гɹ�����TRUE
BOOL CADOEx::ExecuteNotSelSQL(CString strNotSelSQL)		//ִ�и��²���
{
	try
	{
		CloseRecordset();								//�رռ�¼��
		_variant_t vResult;
		vResult.vt=VT_ERROR;
		vResult.scode=DISP_E_PARAMNOTFOUND;

		m_pCmd->ActiveConnection=m_pConn;				
		m_pCmd->CommandText=(_bstr_t)strNotSelSQL;		//��������
		m_pRs=m_pCmd->Execute(&vResult,&vResult,adCmdText);	//ִ������
	}
	catch(_com_error& e)
	{
		AfxMessageBox(e.ErrorMessage());				//��ʾ������Ϣ
		return FALSE;
	}
	return TRUE;
}

void CADOEx::CloseRecordset()							//�رռ�¼��
{
	if(m_pRs->State!=adStateClosed)
		m_pRs->Close();
}

long CADOEx::GetRecordCount()							//��ȡ��¼������
{
	if(m_pRs->State==adStateClosed)						//����¼���رգ�����0
		return 0;
	
	m_pRs->MoveFirst();									//��������
	while(!m_pRs->adoEOF)
		m_pRs->MoveNext();								//����������β��
	long nCount=m_pRs->GetRecordCount();				//��ȡ��¼����
	m_pRs->MoveFirst();										
	return nCount;										//��������
}

long CADOEx::GetRecordColNum()							//��ȡ��¼������
{
	if(m_pRs->State==adStateClosed)
		return 0;

	long nCount=m_pRs->Fields->Count;				
	return nCount;										//�����ֶ���
}

BOOL CADOEx::GetConnectState()							//��ȡ����״̬
{
	return bState;
}

//strMulti����ָ����ַ��������� "a->b->c->d"
//strSplit���ָ��������� "->"	
//����ֵ���������ַ������������ϣ�����4
int CADOEx::GetSingleStringNum(CString strMulti, CString strSplit)		//��ȡ��ָ����ַ��������ַ�������
{
	if(!strMulti.IsEmpty())												//����Ϊ��
	{
		int nSplitCount=strMulti.Replace(strSplit,strSplit);			//��ȡ�ָ�������
		return nSplitCount+1;											//�������ַ�������
	}
	return 0;															
}

//strMulti����ָ����ַ��������� "a->b->c->d"
//nIndex�����ַ������(��1��ʼ)������ 3
//strSplit���ָ��������� "->"
//����ֵ���������ַ���ֵ�����ϣ����� "c"
CString CADOEx::GetSingleString(CString strMulti, int nIndex, CString strSplit)	//��ȡ��ָ����ַ�����ĳ�����ַ���
{
	CString strAim="";						
	if(!strMulti.IsEmpty())														//����Ϊ��
	{
		int nSplitCount=strMulti.Replace(strSplit,strSplit);					//��ȡ�ָ�������
		if(nIndex>nSplitCount+1 || nIndex<1 || nSplitCount==0)					//����Ŵ�������Ŀ�������С��1����ָ���Ϊ0
			return "";															//���ؿ�ֵ

		if(nIndex==1)															//�����Ϊ1
		{
			int nBegin=0;
			if((nBegin=strMulti.Find(strSplit,nBegin))!=-1)						//���ҵ�һ���ָ�����ߵ��ַ���
			{
				strAim=strMulti.Left(nBegin);
			}
		}
		else if(nIndex==nSplitCount+1)											//�����Ϊ���һ��
		{
			int nBegin=0,nPlace=0;
			while((nBegin=strMulti.Find(strSplit,nBegin))!=-1)					//�������һ���ָ���λ��
			{
				nPlace=nBegin++;
			}
			if(nPlace)															//��ȡ���һ���ָ����ұߵ��ַ���
			{
				strAim=strMulti.Right(strMulti.GetLength()-nPlace-strSplit.GetLength());
			}
		}
		else																	//��Ϊ�м����
		{
			int nBeginPlacePre=0,nSplitIndex=0,nBeginPlaceNext=0;
			while((nBeginPlacePre=strMulti.Find(strSplit,nBeginPlacePre))!=-1)	//��ǰ������ҷָ���
			{
				nSplitIndex++;													//�ָ�����Ŀ����	
				if(nSplitIndex==nIndex-1)										//����ָ�����
				{
					if((nBeginPlaceNext=strMulti.Find(strSplit,nBeginPlacePre+1))!=-1)	//������һ���ָ���λ��
					{
						strAim=strMulti.Mid(nBeginPlacePre+strSplit.GetLength(),nBeginPlaceNext-nBeginPlacePre-strSplit.GetLength());
						//��ȡ�����ָ���֮����ַ���

						return strAim;
					}
				}
				else															//��û��ָ����ţ���������	
					nBeginPlacePre++;
			}
		}
	}
	return strAim;		//�������ַ���ֵ
}

//strSelectSQL����ѯSQL���
//strFieldName��Ҫ��ѯ���ֶ��б����ֶβ�ѯ ע��CStringArray��Ϊ����Ҫ��������ʽ���ݣ�����ֵ����
//strResult���ֶν����Ŵ���Ϊ�������
//strSplit���ָ�����ÿ����¼�ж���ֶε�ֵ֮��ָ���������
//����ֵ������ѯ�ɹ�������TRUE
BOOL CADOEx::ExecuteSelSQL(CString strSelectSQL, CStringArray &strFieldName, CStringArray &strResult,CString strSplit)  //���ֶβ�ѯ
{
	try
	{
		strResult.RemoveAll();								//����������

		if(ExecuteSelSQL(strSelectSQL)!=FALSE)				//��ִ��sql�ɹ�
		{	
			strResult.SetSize(m_pRs->GetRecordCount());		//���������С
			for(int i=0;i<m_pRs->GetRecordCount();i++)		//��¼������
			{
				CString strValue;
				for(int j=0;j<strFieldName.GetSize();j++)	//Ҫ��ѯ���ֶα���
				{
					_variant_t var=m_pRs->GetCollect((_bstr_t)strFieldName.GetAt(j));	//��ȡ�ֶ�ֵ
					if(var.vt!=VT_NULL)						//��ֵ��Ϊ��
						strValue+=(char*)(_bstr_t)var;		//תΪ�ַ���
					else
						strValue+=" ";
					if(j!=strFieldName.GetSize()-1)			//����ǰ�ֶβ������һ��	
						strValue+=strSplit;					//�ֶ�ֵ����Ϸָ���
				}
				strResult.SetAtGrow(i,strValue);			//������������
				m_pRs->MoveNext();							//��¼��������һ��
			}
			return TRUE;
		}
	}
	catch(_com_error& e)
	{
		AfxMessageBox(e.ErrorMessage());					//��ʾ������Ϣ
		return FALSE;
	}
	return FALSE;
}

//strSource��Դ�ַ����������� "a->b->c->d"
//strFind��Ҫ���ҵ����ַ����������� "b"
//strSplit���ָ����������� "->"
//����ֵ�����ַ�����Դ�ַ�������ţ����ϣ�����2
int CADOEx::GetIndexOfString(CString strSource, CString strFind, CString strSplit)
{
/*	int nIndex=strSource.Find(strFind);	//ģ������
										
	if(nIndex==-1)						//ע������ strSourceΪ"ac->bd->fg"����strFindΪ"b"
		return 0;						//	  ��ģ�����ң��򷵻�2
	else								//	  ����ȷ���ң��򷵻�0
	{
		CString strLeft=strSource.Left(nIndex+1);
		int nCount=strLeft.Replace(strSplit,strSplit);
		
		return nCount+1;
	}*/

	CString strTemp;	//��ȷ����

	int nIndex;

	nIndex=strSource.Find(strSplit+strFind+strSplit);	//������ʽ���� "->aa->"
	if(nIndex!=-1)										//���ҵ�
	{
		CString strLeft=strSource.Left(nIndex+strSplit.GetLength()+1);	//��ȡҪ�����ַ�����ߵķָ�����Ŀ
		int nCount=strLeft.Replace(strSplit,strSplit);

		return nCount+1;								//�������
	}
	else												//��û�ҵ� "->aa->"
	{
		nIndex=strSource.Find(strSplit+strFind);	//������ʽ���� "->aa"����Ŀ���ַ����������������
		if(nIndex!=-1)								//���ҵ�
		{
			if((nIndex+strSplit.GetLength()+strFind.GetLength())==strSource.GetLength())	//��ȷʵ���������
			{
				int nCount=strSource.Replace(strSplit,strSplit);							//��ȡ���зָ�����Ŀ
				return nCount+1;															//�������
			}
		}
		else										//��Ҳû�ҵ� "->aa"
		{
			nIndex=strSource.Find(strFind+strSplit);	//������ʽ���� "aa->"����Ŀ���ַ���������ǰ������
			if(nIndex!=-1)								//���ҵ�
			{
				if(nIndex==0)							//��ȷʵ������ǰ��
					return 1;							//����1
				else									//��Ҳû�ҵ� "->aa"
				{
					if(strFind.GetLength()==strSource.GetLength())	//��Ŀ���ַ������ȵ���Դ
						return 1;									//����1
					return 0;
				}
			}
		}
		return 0;										//��û�ҵ�������0
	}
}
