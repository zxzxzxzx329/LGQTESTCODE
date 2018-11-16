/////////////////////////////////////////////////////////////////////////
///@system 联合风控
///@company 上海蜂虎铭创
///@file fohooURCStruct.h
///@brief 定义了客户端接口使用的业务数据结构
///@history 
///20170815	卫英杰	创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef URCIStruct_H
#define URCIStruct_H

//TFurcOrderValid
//TFurcOrderMatch
//TFurcOrderConfirm
//TFurcRspInfo
//TFurcOrderValidRspInfo

#include <string>

#define _WIN32_WINNT 0x0501

class TFurcOrderValid
{
private:

	std::string orderBatchRef; // 批量委托""
	std::string orderRef; // 明细委托
	std::string orderRef2; // 明细委托号2，保留字段，可不用 ""
	std::string acctCode; // 资金账户 产品代码
	std::string prodCellCode;   //产品单元代码
	std::string secuAccCode; // 股东账: B123456789
	std::string exchCode; // 交易所：
	std::string secuCode; // 证劵代码
	long orderQty; // 买卖数量
	double orderPrice; // 买卖价格
	std::string secuTradeType; // 买卖方向
	std::string tradeType; // 交易类型
	std::string priceType; // 报价类型:"0"
	std::string lsFlag; // 多空标识"D","K"
	std::string hedgeFlag; // 投保标识"S"
	std::string synFlag; // 同步标志 ""
	std::string resend; // 重发委托标志 ""
	std::string bizDate;// 业务日期：初始化日期""
	std::string dataSourceTypeCode;// 数据来源
	std::string orderType; //委托类型。0委托，1撤单
	std::string orderTime;    //委托时间
	std::string secuType; //证券类别
	
public:


	std::string getOrderBatchRef(void) { return orderBatchRef; }

	void setOrderBatchRef(std::string orderBatchRef) { this->orderBatchRef = orderBatchRef; }

	std::string getOrderRef(void) { return orderRef; }

	void setOrderRef(std::string orderRef) { this->orderRef = orderRef; }

	std::string getOrderRef2(void) { return orderRef2; }

	void setOrderRef2(std::string orderRef2) { this->orderRef2 = orderRef2; }

	std::string getAcctCode(void) { return acctCode; }

	void setAcctCode(std::string acctCode) { this->acctCode = acctCode; }

	std::string getProdCellCode(void){ return prodCellCode; }

	void setProdCellCode(std::string prodCellCode){ this->prodCellCode = prodCellCode; }

	std::string getSecuAccCode(void) { return secuAccCode; }

	void setSecuAccCode(std::string secuAccCode) { this->secuAccCode = secuAccCode; }

	std::string getExchCode(void) { return exchCode; }

	void setExchCode(std::string exchCode) { this->exchCode = exchCode; }

	std::string getSecuCode(void) { return secuCode; }

	void setSecuCode(std::string secuCode) { this->secuCode = secuCode; }

	long getOrderQty(void) { return orderQty; }

	void setOrderQty(long orderQty) { this->orderQty = orderQty; }

	double getOrderPrice(void) { return orderPrice; }

	void setOrderPrice(double orderPrice) { this->orderPrice = orderPrice; }

	std::string getSecuTradeType(void) { return secuTradeType; }

	void setSecuTradeType(std::string secuTradeType) { this->secuTradeType = secuTradeType; }

	std::string getTradeType(void) { return tradeType; }

	void setTradeType(std::string tradeType) { this->tradeType = tradeType; }

	std::string getPriceType(void) { return priceType; }

	void setPriceType(std::string priceType) { this->priceType = priceType; }

	std::string getLsFlag(void) { return lsFlag; }

	void setLsFlag(std::string lsFlag) { this->lsFlag = lsFlag; }

	std::string getHedgeFlag(void) { return hedgeFlag; }

	void setHedgeFlag(std::string hedgeFlag) { this->hedgeFlag = hedgeFlag; }

	std::string getSynFlag(void) { return synFlag; }

	void setSynFlag(std::string synFlag) { this->synFlag = synFlag; }

	std::string getResend(void){ return resend; }

	void setResend(std::string resend){ this->resend = resend; }

	std::string getBizDate(void) { return bizDate; }

	void setBizDate(std::string bizDate) { this->bizDate = bizDate; }

	std::string getDataSourceTypeCode(void) { return dataSourceTypeCode; }

	void setDataSourceTypeCode(std::string dataSourceTypeCode) { this->dataSourceTypeCode = dataSourceTypeCode; }

	std::string getOrderType(void) { return orderType; }

	void setOrderType(std::string orderType) { this->orderType = orderType; }

	std::string getOrderTime(void) { return orderTime; }

	void setOrderTime(std::string orderTime) { this->orderTime = orderTime; }

	std::string getSecuType(void) { return secuType; }

	void setSecuType(std::string secuType){ this->secuType = secuType; }

	
		
		TFurcOrderValid & operator = (const TFurcOrderValid & other)
		{
				this->orderBatchRef       = other.orderBatchRef;
				this->orderRef            = other.orderRef;
				this->orderRef2           = other.orderRef2;
				this->acctCode            = other.acctCode;
				this->prodCellCode        = other.prodCellCode;
				this->secuAccCode         = other.secuAccCode;
				this->exchCode            = other.exchCode;
				this->secuCode            = other.secuCode;
				this->orderQty            = other.orderQty;
				this->orderPrice          = other.orderPrice;
				this->secuTradeType       = other.secuTradeType;
				this->tradeType           = other.tradeType;
				this->priceType           = other.priceType;
				this->lsFlag              = other.lsFlag;
				this->hedgeFlag           = other.hedgeFlag;
				this->synFlag             = other.synFlag;
				this->resend              = other.resend;
				this->bizDate             = other.bizDate;
				this->dataSourceTypeCode  = other.dataSourceTypeCode;
				this->orderType           = other.orderType;
				this->orderTime           = other.orderTime;
				this->secuType            = other.secuType;
				
				return *this;
		}

public:
	TFurcOrderValid(void){}
	~TFurcOrderValid(void){}
};


class TFurcOrderMatch
{
private:

	std::string  acctCode; //资金账户 产品代码
	std::string  exchCode; //交易所代码
	std::string  secuAccCode; //证券账户 股东代码 
	std::string  secuCode; //证劵代码
	std::string  secuTradeType; //买卖方向
	long         matchQty; //成交数量
	double       matchPrice; //成交价格
	double       matchFee;//成交费用
	std::string  matchCode; //成交号码
	std::string  orderSno; //营业部合同序号
	std::string  orderSno2;//
	std::string  lsFlag; //多空标识"D","K
	std::string  hedgeFlag;//投保标识"S"  
	std::string  handFlag;//股手标志（G：股 S：手）
	std::string  matchTime;//成交时间，默认："" Format yyyy/MM/dd HH:mm:ss
	std::string  matchType; //成交类型   正常成交："0"或者 :""，组合成交："4"

public:


	std::string getAcctCode(void) { return acctCode; }

	void setAcctCode(std::string acctCode) { this->acctCode = acctCode; }

	std::string getExchCode(void) { return exchCode; }

	void setExchCode(std::string exchCode) { this->exchCode = exchCode; }

	std::string getSecuAccCode(void) { return secuAccCode; }

	void setSecuAccCode(std::string secuAccCode) { this->secuAccCode = secuAccCode; }

	std::string getSecuCode(void) { return secuCode; }

	void setSecuCode(std::string secuCode) { this->secuCode = secuCode; }

	std::string getSecuTradeType(void) { return secuTradeType; }

	void setSecuTradeType(std::string secuTradeType) { this->secuTradeType = secuTradeType; }

	std::string getOrderSno(void) { return orderSno; }

	void setOrderSno(std::string orderSno) { this->orderSno = orderSno; }

	std::string getOrderSno2(void) { return orderSno2; }

	void setOrderSno2(std::string orderSno2) { this->orderSno2 = orderSno2; }

	long getMatchQty(void) { return matchQty; }

	void setMatchQty(long matchQty) { this->matchQty = matchQty; }

	double getMatchPrice(void) { return matchPrice; }

	void setMatchPrice(double matchPrice) { this->matchPrice = matchPrice; }

	double getMatchFee(void) { return matchFee; }

	void setMatchFee(double matchFee) { this->matchFee = matchFee; }

	std::string getMatchCode(void) { return matchCode; }

	void setMatchCode(std::string matchCode) { this->matchCode = matchCode; }

	std::string getLsFlag(void) { return lsFlag; }

	void setLsFlag(std::string lsFlag) { this->lsFlag = lsFlag; }

	std::string getHedgeFlag(void) { return hedgeFlag; }

	void setHedgeFlag(std::string hedgeFlag) { this->hedgeFlag = hedgeFlag; }

	std::string getHandFlag(void) { return handFlag; }

	void setHandFlag(std::string handFlag) { this->handFlag = handFlag; }

	std::string getMatchTime(void){ return matchTime; }

	void setMatchTime(std::string matchTime){ this->matchTime = matchTime; }

	std::string getMatchType(void){return matchType;}
	void setMatchType(std::string matchType){this->matchType = matchType;}
	TFurcOrderMatch & operator = (const TFurcOrderMatch & other)
	{
			this->acctCode         = other.acctCode;
			this->exchCode         = other.exchCode;
			this->secuAccCode      = other.secuAccCode;
			this->secuCode         = other.secuCode;
			this->secuTradeType    = other.secuTradeType;
			this->matchQty         = other.matchQty;
			this->matchPrice       = other.matchPrice;
			this->matchFee         = other.matchFee;
			this->matchCode        = other.matchCode;
			this->orderSno         = other.orderSno;
			this->orderSno2        = other.orderSno2;
			this->lsFlag           = other.lsFlag;
			this->hedgeFlag        = other.hedgeFlag;
			this->handFlag         = other.handFlag;
			this->matchTime        = other.matchTime;
            this->matchType        = other.matchType;
			return *this;
	}
public:
	TFurcOrderMatch(void){}
	~TFurcOrderMatch(void){}
};


class TFurcOrderConfirm
{
private:

	std::string  orderRef;	//明细委托
	std::string  orderRef2;	//明细委托号 2，保留字段，默认为空
	std::string  orderBatchRef;	//批量委托
	std::string  orderSno;	//营业部合同序号
	std::string  orderSno2;	//营业部合同序号
	std::string  successFlag;	//合法标志，"0"成功 "1"失败
	std::string  confirmMsg;//营业部确认信息
public:

	std::string  getOrderRef(void) { return orderRef; }

	void setOrderRef(std::string  orderRef) { this->orderRef = orderRef; }

	std::string  getOrderRef2(void) { return orderRef2; }

	void setOrderRef2(std::string  orderRef2) { this->orderRef2 = orderRef2; }

	std::string  getOrderBatchRef(void) { return orderBatchRef; }

	void setOrderBatchRef(std::string  orderBatchRef) { this->orderBatchRef = orderBatchRef; }

	std::string  getOrderSno(void) { return orderSno; }

	void setOrderSno(std::string  orderSno) { this->orderSno = orderSno; }

	std::string  getOrderSno2(void) { return orderSno2; }

	void setOrderSno2(std::string  orderSno2) { this->orderSno2 = orderSno2; }

	std::string  getSuccessFlag(void) { return successFlag; }

	void setSuccessFlag(std::string  successFlag) { this->successFlag = successFlag; }

	std::string  getConfirmMsg(void) { return confirmMsg; }

	void setConfirmMsg(std::string  confirmMsg) { this->confirmMsg = confirmMsg; }

	TFurcOrderConfirm & operator = (const TFurcOrderConfirm & other)
	{
		this->orderRef       = other.orderRef;
		this->orderRef2      = other.orderRef2;
		this->orderBatchRef  = other.orderBatchRef;
		this->orderSno       = other.orderSno;
		this->orderSno2      = other.orderSno2;
		this->successFlag    = other.successFlag;
		this->confirmMsg     = other.confirmMsg;
		return *this;
	}

public:
	TFurcOrderConfirm(void){}
	~TFurcOrderConfirm(void){}
};

class TFurcRspInfo
{
public:
	int  errorCode; // 错误代码
	std::string errorMsg;// 错误信息
}; 


class TFurcOrderValidRspInfo
{
public:
	std::string orderRef; //明细委托
	std::string	orderRef2; //明细委托号 2，保留字段，默认："" 
	std::string orderBatchRef; //批量委托 默认："" 
	int  errorCode; // 错误代码
	std::string errorMsg;// 错误信息
};
#endif
