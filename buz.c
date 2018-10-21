#include  "buz.h"
#include "timemodu.h"

u8  buzz_on_time;      //鸣响时长
u8  buzz_off_time;     //间隔时长
u8  buzz_on_cnt;	    // 鸣响次数

u8  buzz_switch;   //蜂鸣器开关


//蜂鸣器应用层函数
//入口   鸣长  间隔时间    鸣声次数
void  BUZ_Application(u8 longcnt,u8  offcnt,u8  buzcnt)
{
	buzz_on_time=longcnt;
	buzz_off_time=offcnt;
	buzz_on_cnt=buzcnt;
}

//蜂鸣器上层驱动函数
//放在10ms时钟片上
void BUZ_Drvpro(void)
{
	static u8  buz_ontime_temp;
	static u8  buz_ontime_cnttemp;
	if(fg10mscheck==1)
	{
		//响的次数
		if(buzz_on_cnt)
		{
			if(buzz_switch)
			{
				//条件写入间隔时间
				if(buz_ontime_temp>buzz_on_time)
				{
					buz_ontime_temp=0;
					buzz_switch=0;
					//已经响完
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
				//条件写入鸣响时间   以及鸣响次数
				if(buz_ontime_temp>buzz_off_time)
				{
					buz_ontime_temp=0;
					
					//条件写入鸣响次数
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



//蜂鸣器下层驱动函数
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




