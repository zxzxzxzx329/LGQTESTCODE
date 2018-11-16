/////////////////////////////////////////////////////////////////////////
///@system ���Ϸ��
///@company �Ϻ��仢����
///@file fohooURCI.h
///@brief �����˿ͻ��˽ӿ�
///@history 
///20170815	��Ӣ��	�������ļ�
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
	//���Ϸ��ƽ̨���ӳɹ�
	virtual void OnUrcConnected(const char * ip){};

	//���Ϸ��ƽ̨���ӶϿ�
	virtual void OnUrcDisconnected(const char * ip){};

	//���������Ӧ
	virtual void OnRspOrderCheck(unsigned uRequestID, TFurcOrderValidRspInfo * pRspInfo){};

	//����ȷ����Ӧ
	virtual void OnRspOrderConfirm(unsigned uRequestID, TFurcRspInfo * pRspInfo){};

	//�����ɽ���Ӧ
	virtual void OnRspOrderMatch(unsigned uRequestID, TFurcRspInfo * pRspInfo){};

	//����
	virtual void OnError(const char * Error){};

};

class URCIAPI CFohooUrcApi
{
public:

	//�������Ϸ�ؽӿ�ʵ�� 
	//Stall �����߳����е�λĬ��Ϊ1�������Ϊ3��
	static CFohooUrcApi * CreateFohooUrcApi(short Stall = 1);

	//����ʵ���ӿ�
	virtual void Release(void) = 0;

	//ע��ص���
	virtual void RegUrcSpi(CFohooUrcSpi * pclURCISpi) = 0;

	//ע�����������ƽ̨��ַ
	virtual bool RegUrcMasteAddress(const char * Ip, unsigned Port) = 0;

	//ע�����ϱ����ƽ̨��ַ
	virtual bool RegUrcSlaveAddress(const char * Ip, unsigned Port) = 0;

	//ע��CA֤��
	virtual void RegCAInfo(const char * CAPath) = 0;

	//ע�������Ϣ��ִ�д˺�����ϵͳ��ʼ����
	virtual void Init(void) = 0;

	//�ȴ����߳̽���
	virtual void Join(void) = 0;

    //���÷���豸
	virtual void SetOriginSystemCode(const char * originSystemCode) = 0;

    //���÷�ؽڵ�
	virtual void setAccessPointCode(const char * accessPointCode) = 0;


	//��鶩��
	virtual int OrderCheck(TFurcOrderValid * pOrderValid, unsigned uRequestID) = 0;

	//����ȷ��
	virtual int OrderConfirm(TFurcOrderConfirm * pOrderConfirm, unsigned uRequestID) = 0;

	//�����ɽ�
	virtual int OrderMatch(TFurcOrderMatch * pOrderMatch, unsigned uRequestID) = 0;
};

#endif
