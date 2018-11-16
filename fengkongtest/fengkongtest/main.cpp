
#include "fohooURCI.h"
#include "XBuffer.h"
#include "SysNanoSecond.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x0600

#ifdef _DEBUG
#pragma comment(lib, "fohooURCID.lib")
#else
#pragma comment(lib, "fohooURCI.lib")
#endif

using namespace std;

struct XTask
{
	unsigned functionNum;	
	unsigned sleepTime;
	union taskUnion
	{
		TFurcOrderValid * pclOrderValid;
		TFurcOrderMatch * pclOrderMatch;
		TFurcOrderConfirm * pclOrderConfirm;
	}Task;

};

typedef vector<XTask> TTaskList;

class CUrcSpi : public CFohooUrcSpi
{
private:	
	int m_iOnRspCount;
	HANDLE hOnEvent;
	NNTIME beginTime;
	double useTime;
public:

	int GetRspCount(void) { return m_iOnRspCount; }

	//联合风控平台连接成功
	virtual void OnUrcConnected(void)
	{
		cout << "风控服务连接成功" << endl;
	}

	//联合风控平台连接断开
	virtual void OnUrcDisconnected(void)
	{
		cout << "风控服务断开连接" << endl;
	}

	//订单检查响应
	virtual void OnRspOrderCheck(unsigned uRequestID, TFurcOrderValidRspInfo * pRspInfo)
	{
		NNTIME endTime = CSysNanoSecond::GetInstance()->GetSysNanoTime();
		useTime = CSysNanoSecond::GetInstance()->UseNanoTime(endTime, beginTime);
		cout << "请求号:" << uRequestID << "订单号:" << pRspInfo->orderRef << " 检查结果:" << pRspInfo->errorMsg << " 检查用时（毫秒）" << useTime << endl;
		
		m_iOnRspCount++;

		if (hOnEvent)
		SetEvent(hOnEvent);
	}

	//订单确认响应
	virtual void OnRspOrderConfirm(unsigned uRequestID, TFurcRspInfo * pRspInfo)
	{
		NNTIME endTime = CSysNanoSecond::GetInstance()->GetSysNanoTime();
		useTime = CSysNanoSecond::GetInstance()->UseNanoTime(endTime, beginTime);
		cout << "请求号:" << uRequestID << "确认处理代码:" << pRspInfo->errorCode << " 确认处理结果:" << pRspInfo->errorMsg << " 确认处理用时（毫秒）" << useTime << endl;
		m_iOnRspCount++;
		if (hOnEvent)
			SetEvent(hOnEvent);
	}

	//订单成交响应
	virtual void OnRspOrderMatch(unsigned uRequestID, TFurcRspInfo * pRspInfo)
	{
		NNTIME endTime = CSysNanoSecond::GetInstance()->GetSysNanoTime();
		useTime = CSysNanoSecond::GetInstance()->UseNanoTime(endTime, beginTime);
		cout << "请求号:" << uRequestID << "成交处理代码:" << pRspInfo->errorCode << " 成交处理结果:" << pRspInfo->errorMsg << " 成交处理用时（毫秒）" << useTime << endl;
		m_iOnRspCount++;
		if (hOnEvent)
			SetEvent(hOnEvent);
	}

	//错误
	virtual void OnError(const char * Error)
	{
		cout << Error << endl;
	}
public:
	CUrcSpi(){ m_iOnRspCount = 0; hOnEvent = NULL; beginTime = 0; useTime = 0; }
	~CUrcSpi(){}
	void SetOnEvent(HANDLE pHandle){ hOnEvent = pHandle; }
	void SetBeginTime(void){ beginTime = CSysNanoSecond::GetInstance()->GetSysNanoTime(); }
	double GetUseTime(void){ return useTime; }
};

static unsigned uRequestNo = 0;

HANDLE onEvent = NULL;

unsigned GetRequestNo(void)
{
	return uRequestNo += 1;
}

void ExecOrder(CFohooUrcApi * pclUrcApi, CUrcSpi * pclUrsSpi, TTaskList &stTaskList, int iSleep);

void GetLastReqNum(void);
void SaveLastReqNum(void);
bool MySleep(unsigned uSleep);
//ip,port,file
int main(int Argc, char * * Argv)
{
	if (Argc < 4)
		return -1;

	std::string strParm1, strParm2, strParm3, strParm4, strParm5, strParm6;
	unsigned uiSleep = 0;

	strParm5 = "V85";
	strParm6 = "v85-zg";

	strParm1 = Argv[1]; //IP
	strParm2 = Argv[2]; //Port
	strParm3 = Argv[3]; //Exec File

	if (Argc > 4)
	{
		strParm4 = Argv[4]; //Sleep Time
		try
		{
			uiSleep = atoi(strParm4.c_str());
		}
		catch (...)
		{
			uiSleep = 0;
		}		
	}

	if (Argc > 6)
	{
		strParm5 = Argv[5];
		strParm6 = Argv[6];
	}

	unsigned Port = atoi(strParm2.c_str());

	cout << "开始加载资源" << endl;
	ifstream taskStream(strParm3.c_str(), ios::out|ios::binary);
	if (!taskStream)
	{
		cout << "加载资源失败，按任意键退出" << endl;
		cin.get();
		return -2;
	}


	vector<string> lines;
	while (!taskStream.eof())
	{
		string tmp;
		taskStream >> tmp;
		lines.push_back(tmp);
	}
	taskStream.close();

	TTaskList myTaskList;
	XBuffer clBufferEx;
	clBufferEx.SetSplitChar(',');
	

	for (unsigned i = 0; i < lines.size(); i++)
	{
		std::cout << lines[i] << endl;

		clBufferEx.Clear();
		clBufferEx.Set(lines[i]);	

		if (clBufferEx.GetItemCount() < 1)
			continue;

		if (strlen(clBufferEx.GetItem(0)) < 1)
			continue;

		
		unsigned char uiFunctionNum = clBufferEx.GetItem(0)[0];		
		
		XTask stTask;
		
		stTask.sleepTime = atoi(clBufferEx.GetItem(1));
		
		

		switch (uiFunctionNum)
		{
			case 'V':
				{
					if (clBufferEx.GetItemCount() != 14)
						continue;

					stTask.functionNum = 80000;
					stTask.Task.pclOrderValid = new TFurcOrderValid();
					//stTask.Task.pclOrderValid->setOriginSystemCode(strParm5);
					//stTask.Task.pclOrderValid->setAccessPointCode(strParm6);
					stTask.Task.pclOrderValid->setOrderBatchRef("");
					
					stTask.Task.pclOrderValid->setOrderRef(clBufferEx.GetItem(2));
					stTask.Task.pclOrderValid->setOrderRef2("");					
					stTask.Task.pclOrderValid->setAcctCode(clBufferEx.GetItem(3));
					stTask.Task.pclOrderValid->setProdCellCode("");							
					stTask.Task.pclOrderValid->setSecuAccCode(clBufferEx.GetItem(4));
					stTask.Task.pclOrderValid->setExchCode(clBufferEx.GetItem(5));						
					stTask.Task.pclOrderValid->setSecuCode(clBufferEx.GetItem(6));					
					stTask.Task.pclOrderValid->setOrderQty(atoi(clBufferEx.GetItem(7)));	
					stTask.Task.pclOrderValid->setOrderPrice(atof(clBufferEx.GetItem(8)));
					stTask.Task.pclOrderValid->setSecuTradeType(clBufferEx.GetItem(9));
					stTask.Task.pclOrderValid->setTradeType("PT");
					stTask.Task.pclOrderValid->setPriceType(clBufferEx.GetItem(10));
					stTask.Task.pclOrderValid->setLsFlag(clBufferEx.GetItem(11));
					stTask.Task.pclOrderValid->setHedgeFlag("S");
					stTask.Task.pclOrderValid->setSynFlag("");
					stTask.Task.pclOrderValid->setResend("");
					stTask.Task.pclOrderValid->setBizDate("");
					stTask.Task.pclOrderValid->setDataSourceTypeCode("");
					stTask.Task.pclOrderValid->setOrderType(clBufferEx.GetItem(12)); //委托0，撤单1
					stTask.Task.pclOrderValid->setOrderTime("");
					stTask.Task.pclOrderValid->setSecuType(clBufferEx.GetItem(13));//"ES"

				}
				break;
			case 'C':
				{
					if (clBufferEx.GetItemCount() != 6)
						continue;
					stTask.functionNum = 80001;
					stTask.Task.pclOrderConfirm = new TFurcOrderConfirm();

					//stTask.Task.pclOrderConfirm->setOriginSystemCode(strParm5);
					//stTask.Task.pclOrderConfirm->setAccessPointCode(strParm6);
					
					stTask.Task.pclOrderConfirm->setOrderRef(clBufferEx.GetItem(2));

					stTask.Task.pclOrderConfirm->setOrderRef2("");

					stTask.Task.pclOrderConfirm->setOrderBatchRef("");

					stTask.Task.pclOrderConfirm->setOrderSno(clBufferEx.GetItem(3));

					stTask.Task.pclOrderConfirm->setOrderSno2("");

					stTask.Task.pclOrderConfirm->setSuccessFlag(clBufferEx.GetItem(4));

					stTask.Task.pclOrderConfirm->setConfirmMsg(clBufferEx.GetItem(5));

				}
				break;
			case 'M':
				{
					if (clBufferEx.GetItemCount() != 14)
						continue;
					stTask.functionNum = 80002;
					stTask.Task.pclOrderMatch = new TFurcOrderMatch();
					//stTask.Task.pclOrderMatch->setOriginSystemCode(strParm5);
					//stTask.Task.pclOrderMatch->setAccessPointCode(strParm6);

					stTask.Task.pclOrderMatch->setAcctCode(clBufferEx.GetItem(2));

					stTask.Task.pclOrderMatch->setExchCode(clBufferEx.GetItem(3));

					stTask.Task.pclOrderMatch->setSecuAccCode(clBufferEx.GetItem(4));

					stTask.Task.pclOrderMatch->setSecuCode(clBufferEx.GetItem(5));

					stTask.Task.pclOrderMatch->setSecuTradeType(clBufferEx.GetItem(6));

					stTask.Task.pclOrderMatch->setMatchQty(atoi(clBufferEx.GetItem(7)));

					stTask.Task.pclOrderMatch->setMatchPrice(atof(clBufferEx.GetItem(8)));

					stTask.Task.pclOrderMatch->setMatchFee(atof(clBufferEx.GetItem(9)));

					stTask.Task.pclOrderMatch->setMatchCode(clBufferEx.GetItem(10));

					stTask.Task.pclOrderMatch->setOrderSno(clBufferEx.GetItem(11));

					stTask.Task.pclOrderMatch->setOrderSno2("");
					stTask.Task.pclOrderMatch->setLsFlag(clBufferEx.GetItem(12));
					stTask.Task.pclOrderMatch->setHedgeFlag("S");

					stTask.Task.pclOrderMatch->setHandFlag(clBufferEx.GetItem(13));

					//stTask.Task.pclOrderMatch->setClinchDealTime("");

				}
				break;
			default:
				continue;				
		}

		myTaskList.push_back(stTask);
	}
	
	cout << "资源加载完成，开始初始化API" << endl;

	GetLastReqNum();
	if (NULL == onEvent)
	onEvent = CreateEvent(NULL, true, false, NULL);

	CFohooUrcApi * pclUrcApi = CFohooUrcApi::CreateFohooUrcApi();


	CUrcSpi * pclUrsSpi = new CUrcSpi();	

	pclUrsSpi->SetOnEvent(onEvent);

	pclUrcApi->RegUrcSpi(pclUrsSpi);

	pclUrcApi->RegUrcMasteAddress(strParm1.c_str(), Port);

	pclUrcApi->Init();

	unsigned uiTaskCount = myTaskList.size();
	cout << "生成数据：" << uiTaskCount << "条，开始执行......" << endl;
;
	ExecOrder(pclUrcApi, pclUrsSpi, myTaskList, uiSleep);

	SaveLastReqNum();


	cout << "收到应答数量" << pclUrsSpi->GetRspCount() << endl;

	pclUrcApi->Join();
	pclUrcApi->Release();

	CloseHandle(onEvent);
	onEvent = NULL;
	delete pclUrsSpi;
	pclUrsSpi = NULL;
	cout << "按任意键退出" << endl;
	cin.get();
	return 0;
}

void ExecOrder(CFohooUrcApi * pclUrcApi, CUrcSpi * pclUrsSpi, TTaskList &stTaskList, int iSleep)
{
	if (stTaskList.empty())
		return;

	unsigned iCount = stTaskList.size();

	ResetEvent(onEvent);
	double allUseTime = 0;
	for (unsigned i = 0; i < iCount; i++)
	{
		if (stTaskList[i].sleepTime > 0)
		{
			cout << "休眠" << stTaskList[i].sleepTime <<"秒后继续发送"<< endl;
			Sleep(1000 * stTaskList[i].sleepTime);
		}

		unsigned uiReqNum = GetRequestNo();
		pclUrsSpi->SetBeginTime();
		switch (stTaskList[i].functionNum)
		{
		case 80000:
			pclUrcApi->OrderCheck(stTaskList[i].Task.pclOrderValid, uiReqNum);
			break;
		case 80001:
			pclUrcApi->OrderConfirm(stTaskList[i].Task.pclOrderConfirm, uiReqNum);
			break;
		case 80002:
			pclUrcApi->OrderMatch(stTaskList[i].Task.pclOrderMatch, uiReqNum);
			break;
		default:
			break;
		}
		
		std::cout << "发送订单请求号" << uiReqNum << " 功能号：" << stTaskList[i].functionNum << endl;

		if (!MySleep(5000))
			std::cout << "等待响应超时5秒" << endl;
		allUseTime += pclUrsSpi->GetUseTime();
		ResetEvent(onEvent);

		if (iSleep > 0 && iSleep < INT_MAX)
			Sleep(iSleep);

		//cout << "按任意键下一笔" << endl;
		//cin.get();
	}

	std::cout << "发送订单" << iCount << "笔，总耗时" << allUseTime << "毫秒，平均单笔耗时"<<(allUseTime / iCount)<<"毫秒"<< endl;
}

void GetLastReqNum(void)
{
	FILE * fHandle = fopen("reqnum.dat", "rb+");
	if (fHandle == NULL)
		return;

	char buff[32];
	memset(buff, 0, 32);
	fread(buff, 32, 1, fHandle);
	uRequestNo = atol(buff);
	fclose(fHandle);

}

void SaveLastReqNum(void)
{
	remove("reqnum.dat");
	FILE * fHandle = fopen("reqnum.dat", "wb+");
	if (fHandle == NULL)
		return;
	char buff[32];
	memset(buff, 0, 32);

	_ltoa(uRequestNo, buff, 10);
	fwrite(buff, strlen(buff), 1, fHandle);
	fclose(fHandle);
}

bool MySleep(unsigned uSleep)
{
	unsigned uCount = 0;
	while (WaitForSingleObject(onEvent, 0) != WAIT_OBJECT_0)
	{
		uCount++;
		Sleep(1);
		if (uCount >= uSleep)
			return false;
	}
	return true;
}