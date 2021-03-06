#pragma once

#include "Stdafx.h"
#include "ControlWnd.h"
#include "CardControl.h"
#include "ScoreControl.h"
#include "DrawSiceWnd.h"

//////////////////////////////////////////////////////////////////////////
//消息定义

#define IDM_START					(WM_USER+100)						//开始消息
#define IDM_OUT_CARD				(WM_USER+101)						//出牌消息
#define IDM_TRUSTEE_CONTROL			(WM_USER+102)						//托管控制
#define IDI_DISC_EFFECT					102								//丢弃效果

//////////////////////////////////////////////////////////////////////////

//游戏视图
class CGameClientView : public CGameFrameViewGDI
{
	//标志变量
protected:
	bool							m_bOutCard;							//出牌标志
	bool							m_bWaitOther;						//等待标志
	bool							m_bTrustee[GAME_PLAYER];			//是否托管
	LONGLONG						m_lGangScore[GAME_PLAYER];			//

	//游戏属性
protected:
	LONGLONG						m_lCellScore;						//基础积分
	WORD							m_wBankerUser;						//庄家用户
	WORD							m_wCurrentUser;						//当前用户
	BYTE							m_cbWinOrder[GAME_PLAYER];			//

	//动作动画
protected:
	bool							m_bBombEffect;						//动作效果
	BYTE							m_cbBombFrameIndex;					//帧数索引

	//丢弃效果
	WORD							m_wDiscUser;						//丢弃用户
	BYTE							m_cbDiscFrameIndex;					//帧数索引	

	//杠牌动画
	int								m_nYGangStep;						//
	BYTE							m_cbXiaYu;							//
	WORD							m_wGangChairId;						//
	BYTE							m_cbGangIndex;						//

	//用户状态
protected:
	BYTE							m_cbCardData;						//出牌扑克
	WORD							m_wOutCardUser;						//出牌用户
	BYTE							m_cbUserAction[4];					//用户动作

	//位置变量
protected:
	CPoint							m_UserFlagPos[4];					//标志位置
	CPoint							m_PointTrustee[GAME_PLAYER];		//托管位置
	CPoint							m_ptWinOrder[GAME_PLAYER];			//
	CPoint							m_ptGangScore[GAME_PLAYER];			//

	//位图变量
protected:
	CBitImage						m_ImageBack;						//背景图案
	CBitImage						m_ImageCenter;						//LOGO图
	CBitImage						m_ImageWait;						//等待提示
	CBitImage						m_ImageOutCard;						//出牌提示
	CBitImage						m_ImageUserFlag;					//用户标志
	CBitImage						m_ImageUserAction;					//用户动作
	CBitImage						m_ImageActionBack;					//动作背景
	CPngImage						m_ImageTrustee;						//托管标志
	CPngImage						m_ImageActionAni;					//吃牌动画资源
	CPngImage						m_ImageDisc;						//丢弃效果
	CPngImage						m_ImageArrow;						//定时器箭头	
	CBitImage						m_ImageWinOrder;					//
	CPngImage						m_ImageCellScore;					//
	CPngImage						m_PngNumWin;						//
	CPngImage						m_PngNumLost;						//
	CPngImage						m_PngXiaYu;							//
	CPngImage						m_PngGuaFeng;						//

	//扑克控件
public:
	CHeapCard						m_HeapCard[4];						//堆立扑克
	CUserCard						m_UserCard[3];						//用户扑克
	CTableCard						m_TableCard[4];						//桌面扑克
	CWeaveCard						m_WeaveCard[4][4];					//组合扑克
	CDiscardCard					m_DiscardCard[4];					//丢弃扑克
	CCardControl					m_HandCardControl;					//手上扑克

	//控件变量
public:
	CSkinButton						m_btStart;							//开始按钮
	CSkinButton						m_btStusteeControl;					//拖管控制
	CControlWnd						m_ControlWnd;						//控制窗口
	CScoreControl					m_ScoreControl[GAME_PLAYER];		//积分控件
	CDrawSiceWnd					m_DrawSiceWnd;						//色子控件

	//函数定义
public:
	//构造函数
	CGameClientView();
	//析构函数
	virtual ~CGameClientView();

	//继承函数
private:
	//重置界面
	virtual void ResetGameView();
	//调整控件
	virtual void RectifyControl(int nWidth, int nHeight);
	//绘画界面
	virtual void DrawGameView(CDC * pDC, int nWidth, int nHeight);

	//功能函数
public:
	//基础积分
	void SetCellScore(LONGLONG lCellScore);
	//庄家用户
	void SetBankerUser(WORD wBankerUser);
	//状态标志
	void SetStatusFlag(bool bOutCard, bool bWaitOther);
	//出牌信息
	void SetOutCardInfo(WORD wViewChairID, BYTE cbCardData);
	//动作信息
	void SetUserAction(WORD wViewChairID, BYTE bUserAction);
	//设置动作
	bool SetBombEffect(bool bBombEffect);
	//丢弃用户
	void SetDiscUser(WORD wDiscUser);
	//定时玩家
	void SetCurrentUser(WORD wCurrentUser);
	//设置托管
	void SetTrustee(WORD wTrusteeUser,bool bTrustee);
	//
	void SetWinOrder( WORD wChairId, BYTE cbWinOrder );
	//
	void SetGangScore( WORD wChairId, BYTE cbXiaYu, LONGLONG lGangScore[GAME_PLAYER] );

	//辅助函数
protected:
	//艺术字体
	void DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, int nXPos, int nYPos, bool bDrawCenter);
	//绘画数字
	void DrawNumberString( CDC *pDC, CPngImage &PngNumber, int nXPos, int nYPos, LONGLONG lNumber, bool bDrawCenter, bool bDrawSign);

	//消息映射
protected:
	//开始按钮
	afx_msg void OnStart();
	//拖管控制
	afx_msg void OnStusteeControl();
	//建立函数
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//鼠标消息
	afx_msg void OnLButtonDown(UINT nFlags, CPoint Point);
	//光标消息
	afx_msg BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTimer(UINT nIDEvent);
};

//////////////////////////////////////////////////////////////////////////
