#include  "buz.h"
#include "timemodu.h"

u8  buzz_on_time;      //����ʱ��
u8  buzz_off_time;     //���ʱ��
u8  buzz_on_cnt;	    // �������

u8  buzz_switch;   //����������


//������Ӧ�ò㺯��
//���   ����  ���ʱ��    ��������
void  BUZ_Application(u8 longcnt,u8  offcnt,u8  buzcnt)
{
	buzz_on_time=longcnt;
	buzz_off_time=offcnt;
	buzz_on_cnt=buzcnt;
}

//�������ϲ���������
//����10msʱ��Ƭ��
void BUZ_Drvpro(void)
{
	static u8  buz_ontime_temp;
	static u8  buz_ontime_cnttemp;
	if(fg10mscheck==1)
	{
		//��Ĵ���
		if(buzz_on_cnt)
		{
			if(buzz_switch)
			{
				//����д����ʱ��
				if(buz_ontime_temp>buzz_on_time)
				{
					buz_ontime_temp=0;
					buzz_switch=0;
					//�Ѿ�����
					if(buz_ontime_cnttemp>=buzz_on_cnt)
						buzz_on_cnt=0;
				}
				else
				{
					buz_ontime_temp++;
				}
			}
			else
			{
				//����д������ʱ��   �Լ��������
				if(buz_ontime_temp>buzz_off_time)
				{
					buz_ontime_temp=0;
					
					//����д���������
					buz_ontime_cnttemp++;
					buzz_switch=1;
							
				}
				else
				{
					buz_ontime_temp++;
				}
			}
		}
			
	}
}



//�������²���������
void BUZ_Drv(void)
{
	static u8 temp;
	if(buzz_switch)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_8);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
	}

}




