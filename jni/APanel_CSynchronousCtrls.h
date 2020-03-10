/******************************************
**		�ļ���APanel_CSynchronousCtrls.h
**		���ߣ�������
**		ʱ�䣺12��10��24��
**		����޸ģ���
*******************************************/
#ifndef _APANEL_TYPE_H
#define _APANEL_TYPE_H
#include "APanel_Type.h"
#endif

//#ifndef _APANEL_CDRAWCONTROL_H
//#define _APANEL_CDRAWCONTROL_H
#include "APanel_CDrawControl.h"
//#endif

namespace APanel
{
	/***************************************************************
	**
	**			CSynchronousCtrlsͬ��Ԫ������
	**
	****************************************************************/
	class CSynchronousCtrls
	{
		//���졢��������
	public:
		CSynchronousCtrls();
		CSynchronousCtrls(const CSynchronousCtrls& objectSrc);
		~CSynchronousCtrls();

		//�ӿ�
	public:
		//���һ��Ԫ�ص�����
		int				AppendCtrlToMutex(CDrawControl*  pAdd);

		//������Ż��һ������Ԫ��
		CDrawControl*	GetCtrlByIndex(UINT nIndex);

		//��ÿؼ�����
		UINT			GetCtrlNum();

		//���������
		void operator=(const CSynchronousCtrls& objectSrc);

		//����
	protected:

		//���ԣ�
	protected:
		vector<CDrawControl*> m_DrawCtrls;
	};

}
