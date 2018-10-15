#include "key.h"
#include "led.h"
#include "stm32f10x_gpio.h"
#include "timemodu.h"
#include "lcd1602.h"

enum key_value
{
	nokey =0,
	key0 ,
	key1,
	key2,
	key01,
	key02,
	key12,
};
enum key_charatic
{
	shortpress =0,
	longpress,
	nostate,
};

//===============ȫ�ֱ���==================
u8 ucKeyValue;
u8 ucKeycharatic; ///��ֵ����

//---------------------------------------
u8 key_scan(void)
{
	u8 keyvaluetemp;
	if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)==0)
	{
		keyvaluetemp=key2;
	}
	if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)==0)
	{
		keyvaluetemp=key1;
	}
	 if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)==0)
	{
		keyvaluetemp=key0;
	}
	if((GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)==0)&&(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)==0))
	{
		keyvaluetemp=key12;
	}
	if((GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)==0)&&(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)==0))
	{
		keyvaluetemp=key02;
	}
	if((GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)==0)&&(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)==0))
	{
		keyvaluetemp=key01;
	}
	if((GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)==1)&&(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)==1)&&(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)==1))
	{
		keyvaluetemp=nokey;
	}
	return keyvaluetemp;
}
void key_sure(void)
{
	static u8 delay_cnt; 
	static u8 ucKeyValueBak;
	//��ʱ500ms�����жϼ�ֵ�Ƿ�ı�
	if(ucKeyValue==ucKeyValueBak)
	{
		if(delay_cnt++>keydeley200ms)
		{
			ucKeyValue=ucKeyValueBak;
		}
	}
	else  //�ް����������ʱ������0
	{
		delay_cnt=0;
		ucKeyValueBak=ucKeyValue;
		ucKeycharatic=nostate;
	}
}
//��Ҫ�ж����̰���  �Լ�������Ӧ����̧����Ӧ
//��Ҫ��̧��ʱ��
static u8 presstime;

u8 key_valuedefine(void)
{	
	static u8 ucKeyValuebak;
	//�Ѿ����°���
	if(ucKeyValue) ////
	{
		//��ʼͳ�ư��¼�ʱ
		presstime++;
		ucKeyValuebak=ucKeyValue;		
	}
	else  //�Ѿ�̧��
	{
		if(presstime>longkeytime)
		{
			//�ж�������
			ucKeycharatic=longpress;
			ucKeyValue=ucKeyValuebak;
		}
		//�ж��̰���
		//if((presstime<longkeytime)&&(ucKeycharatic!=longpress))
		else if(presstime>0)
		{
			ucKeycharatic=shortpress;
			ucKeyValue=ucKeyValuebak;
		}	
		presstime=0;
	}
	
}



void key_deal(void)
{
	switch(ucKeyValue)
	{
		case key0:
			if(ucKeycharatic==longpress)
			{
				LCD1602_Show_Str(2, 1, "key0    longpress");
				
			}
			else if(ucKeycharatic==shortpress)
			{
				LCD1602_Show_Str(2, 1, "key0    shortpress");
				
			}
		break;
		case key1:
			if(ucKeycharatic==longpress)
			{
				LCD1602_Show_Str(2, 1, "key1    longpress");
				
			}
			else if(ucKeycharatic==shortpress)
			{
				LCD1602_Show_Str(2, 1, "key1    shortpress");
				
			}
		break;
		case key2:
			if(ucKeycharatic==longpress)
			{
				LCD1602_Show_Str(2, 1, "key2    longpress");
				
			}
			else if(ucKeycharatic==shortpress)
			{
				LCD1602_Show_Str(2, 1, "key2    shortpress");
				
			}
		break;
		case key01:
			if(ucKeycharatic==longpress)
			{
				LCD1602_Show_Str(2, 1, "key01   longpress");
				
			}
			else if(ucKeycharatic==shortpress)
			{
				LCD1602_Show_Str(2, 1, "key01   shortpress");
				
			}
		break;
		case key02:
			if(ucKeycharatic==longpress)
			{
				LCD1602_Show_Str(2, 1, "key02   longpress");
				
			}
			else if(ucKeycharatic==shortpress)
			{
				LCD1602_Show_Str(2, 1, "key02   shortpress");
				
			}
		break;
		case key12:
			if(ucKeycharatic==longpress)
			{
				LCD1602_Show_Str(2, 1, "key12    longpress");
				
			}
			else if(ucKeycharatic==shortpress)
			{
				LCD1602_Show_Str(2, 1, "key12    shortpress");
				
			}
		break;
		default:
			LCD1602_Show_Str(2, 1, "nokey");
		break;
	}
	//�ж����ֵ��Ҫ�����ֵ���
	ucKeyValue=nokey;
	
}
void key_pro(void)
{
	if(fg100mscheck==1)
	{
		//����ɨ��
		ucKeyValue=key_scan();
		//������ʱ
		key_sure();
		//��������	
		key_valuedefine();
	}
	key_deal();
}








