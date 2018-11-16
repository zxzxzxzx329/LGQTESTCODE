/////////////////////////////////////////////////////////////////////////
///@system 联合风控
///@company 上海蜂虎铭创
///@file fohooURCI.h
///@brief 定义了客户端接口
///@history 
///20170815	卫英杰	创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef fohooURCI_H
#define fohooURCI_H

#ifdef EXPORTDLL
#define URCIAPI __declspec(dllexport)
#else
#define URCIAPI __declspec(dllimport)
#endif

#define _WIN32_WINNT 0x0501

#include "URCIStruct.h"

class CFohooUrcSpi
{
public:
	//联合风控平台连接成功
	virtual void OnUrcConnected(const char * ip){};

	//联合风控平台连接断开
	virtual void OnUrcDisconnected(const char * ip){};

	//订单检查响应
	virtual void OnRspOrderCheck(unsigned uRequestID, TFurcOrderValidRspInfo * pRspInfo){};

	//订单确认响应
	virtual void OnRspOrderConfirm(unsigned uRequestID, TFurcRspInfo * pRspInfo){};

	//订单成交响应
	virtual void OnRspOrderMatch(unsigned uRequestID, TFurcRspInfo * pRspInfo){};

	//错误
	virtual void OnError(const char * Error){};

};

class URCIAPI CFohooUrcApi
{
public:

	//创建联合风控接口实例 
	//Stall 处理线程运行档位默认为1档，最高为3档
	static CFohooUrcApi * CreateFohooUrcApi(short Stall = 1);

	//销毁实例接口
	virtual void Release(void) = 0;

	//注册回掉类
	virtual void RegUrcSpi(CFohooUrcSpi * pclURCISpi) = 0;

	//注册联合主风控平台地址
	virtual bool RegUrcMasteAddress(const char * Ip, unsigned Port) = 0;

	//注册联合备风控平台地址
	virtual bool RegUrcSlaveAddress(const char * Ip, unsigned Port) = 0;

	//注册CA证书
	virtual void RegCAInfo(const char * CAPath) = 0;

	//注册完成信息后执行此函数，系统开始工作
	virtual void Init(void) = 0;

	//等待主线程结束
	virtual void Join(void) = 0;

    //设置风控设备
	virtual void SetOriginSystemCode(const char * originSystemCode) = 0;

    //设置风控节点
	virtual void setAccessPointCode(const char * accessPointCode) = 0;


	//检查订单
	virtual int OrderCheck(TFurcOrderValid * pOrderValid, unsigned uRequestID) = 0;

	//订单确认
	virtual int OrderConfirm(TFurcOrderConfirm * pOrderConfirm, unsigned uRequestID) = 0;

	//订单成交
	virtual int OrderMatch(TFurcOrderMatch * pOrderMatch, unsigned uRequestID) = 0;
};

#endif
