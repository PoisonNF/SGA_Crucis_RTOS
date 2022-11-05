/****************************************************************************

* Sigma团队

* 文件名: ocd_ps2.c

* 内容简述：PS2手柄驱动模块文件

* 文件历史：

* 版本号		日期		作者		说明
* 1.1.9		2022-10-27	  鲍程璐	 创建该文件

****************************************************************************/
#include "ocd_ps2.h"

uint16_t Handkey;	// 按键值读取，零时存储。
uint8_t Comd[2]={0x01,0x42};	//开始命令。请求数据
uint8_t PS2Data[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //数据存储数组
                    /*PS2Data[0]    空 
                      PS2Data[1]    0x73 红灯模式 0x41 灭灯模式
                      PS2Data[2]    0x5A 返回数据预告
                      PS2Data[3]    低8位按键状态 0按下
                      PS2Data[4]    高8位按键状态 0按下
                      PS2Data[5]    PSS_RX
                      PS2Data[6]    PSS_RY
                      PS2Data[7]    PSS_LX
                      PS2Data[8]    PSS_LY
                    */
uint16_t MASK[]={
    PSB_SELECT,
    PSB_L3,
    PSB_R3 ,
    PSB_START,
    PSB_PAD_UP,
    PSB_PAD_RIGHT,
    PSB_PAD_DOWN,
    PSB_PAD_LEFT,
    PSB_L2,
    PSB_R2,
    PSB_L1,
    PSB_R1 ,
    PSB_GREEN,
    PSB_RED,
    PSB_BLUE,
    PSB_PINK
};

/**
 * @brief 向手柄发送指令函数
 * @param *_tPS2-PS2句柄指针
 * @param CMD 发送的指令，十六进制
 * @retval Null
*/
static void PS2_Cmd(tagPS2_T *_tPS2,uint8_t CMD)
{
	volatile uint16_t ref=0x01;
	PS2Data[1] = 0;
	for(ref=0x01;ref<0x0100;ref<<=1)
	{
		if(ref&CMD)
		{
			DO_H;                   //输出一位控制位
		}
		else DO_L;

		CLK_H;                      //时钟拉高
		DELAY_TIME;
		CLK_L;
		DELAY_TIME;
		CLK_H;
		if(DI)
			PS2Data[1] = ref|PS2Data[1];
	}
	Drv_Delay_Us(16);
}

/**
 * @brief 从手柄处接收数据函数
 * @param *_tPS2-PS2句柄指针
 * @note 单独使用时需提前调用PS2_ClearData
 * @retval Null
*/
void PS2_ReadData(tagPS2_T *_tPS2)
{
	volatile uint8_t byte=0;
	volatile uint16_t ref=0x01;
	CS_L;
	PS2_Cmd(_tPS2,Comd[0]);  //开始命令
	PS2_Cmd(_tPS2,Comd[1]);  //请求数据
	for(byte=2;byte<9;byte++)         //开始接受数据
	{
		for(ref=0x01;ref<0x100;ref<<=1)
		{
			CLK_H;
			DELAY_TIME;
			CLK_L;
			DELAY_TIME;
			CLK_H;
		    if(DI)
		    PS2Data[byte] = ref|PS2Data[byte];
		}
        Drv_Delay_Us(16);
	}
	CS_H;
}

/**
 * @brief 对读出来的PS2的数据进行处理,返回按键状态
 * @param *_tPS2-PS2句柄指针
 * @retval 按键的序号
*/
uint8_t PS2_DataKey(tagPS2_T *_tPS2)
{
	uint8_t index;

	PS2_ClearData();
	PS2_ReadData(_tPS2);

	Handkey=(PS2Data[4]<<8)|PS2Data[3];     //这是16个按键  按下为0， 未按下为1
	for(index=0;index<16;index++)
	{	    
		if((Handkey&(1<<(MASK[index]-1)))==0)
		return index+1;	//按键的序号
	}
	return 0;           //没有任何按键按下
}

//得到一个摇杆的模拟量	 范围0~256
uint8_t PS2_AnologData(uint8_t button)
{
	return PS2Data[button];
}

//清除数据缓冲区
static void PS2_ClearData(void)
{
	uint8_t a;
	for(a=0;a<9;a++)
		PS2Data[a]=0x00;
}

//判断是否为红灯模式,0x41=模拟绿灯，0x73=模拟红灯
//返回值；0，红灯模式
//		  其他，其他模式
uint8_t PS2_RedLight(tagPS2_T *_tPS2)
{
	CS_L;
	PS2_Cmd(_tPS2,Comd[0]);  //开始命令
	PS2_Cmd(_tPS2,Comd[1]);  //请求数据
	CS_H;
	if( PS2Data[1] == 0X73)   return 0 ;
	else return 1;

}

/******************************************************
Function:    void PS2_Vibration(u8 motor1, u8 motor2)
Description: 手柄震动函数，
Calls:		 void PS2_Cmd(u8 CMD);
Input: motor1:右侧小震动电机 0x00关，其他开
	   motor2:左侧大震动电机 0x40~0xFF 电机开，值越大 震动越大
******************************************************/
void PS2_Vibration(tagPS2_T *_tPS2,uint8_t motor1, uint8_t motor2)
{
	CS_L;
	Drv_Delay_Us(16);
    PS2_Cmd(_tPS2,Comd[0]);  //开始命令
	PS2_Cmd(_tPS2,Comd[1]);  //请求数据
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,motor1);
	PS2_Cmd(_tPS2,motor2);
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0X00);
	CS_H;
	Drv_Delay_Us(16);  
}
//short poll
static void PS2_ShortPoll(tagPS2_T *_tPS2)
{
	CS_L;
	Drv_Delay_Us(16);
	PS2_Cmd(_tPS2,Comd[0]);  
	PS2_Cmd(_tPS2,Comd[1]);  
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0x00);
	PS2_Cmd(_tPS2,0x00);
	CS_H;
	Drv_Delay_Us(16);	
}
//进入配置
static void PS2_EnterConfing(tagPS2_T *_tPS2)
{
    CS_L;
	Drv_Delay_Us(16);
	PS2_Cmd(_tPS2,0x01);  
	PS2_Cmd(_tPS2,0x43);  
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0x01);
	PS2_Cmd(_tPS2,0x00);
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0X00);
	CS_H;
	Drv_Delay_Us(16);
}
//发送模式设置
static void PS2_TurnOnAnalogMode(tagPS2_T *_tPS2)
{
	CS_L;
	PS2_Cmd(_tPS2,0x01);  
	PS2_Cmd(_tPS2,0x44);  
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0x01); //analog=0x01;digital=0x00  软件设置发送模式
	PS2_Cmd(_tPS2,0x03); //Ox03锁存设置，即不可通过按键“MODE”设置模式。
				         //0xEE不锁存软件设置，可通过按键“MODE”设置模式。
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0X00);
	CS_H;
	Drv_Delay_Us(16);
}
//振动设置
void PS2_VibrationMode(tagPS2_T *_tPS2)
{
	CS_L;
	Drv_Delay_Us(16);
	PS2_Cmd(_tPS2,0x01);  
	PS2_Cmd(_tPS2,0x4D);  
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0x00);
	PS2_Cmd(_tPS2,0X01);
	CS_H;
	Drv_Delay_Us(16);	
}
//完成并保存配置
static void PS2_ExitConfing(tagPS2_T *_tPS2)
{
    CS_L;
	Drv_Delay_Us(16);
	PS2_Cmd(_tPS2,0x01);  
	PS2_Cmd(_tPS2,0x43);  
	PS2_Cmd(_tPS2,0X00);
	PS2_Cmd(_tPS2,0x00);
	PS2_Cmd(_tPS2,0x5A);
	PS2_Cmd(_tPS2,0x5A);
	PS2_Cmd(_tPS2,0x5A);
	PS2_Cmd(_tPS2,0x5A);
	PS2_Cmd(_tPS2,0x5A);
	CS_H;
	Drv_Delay_Us(16);
}
//手柄配置初始化
void PS2_SetInit(tagPS2_T *_tPS2)
{
	PS2_ShortPoll(_tPS2);
	PS2_ShortPoll(_tPS2);
	PS2_ShortPoll(_tPS2);
	PS2_EnterConfing(_tPS2);		//进入配置模式
	PS2_TurnOnAnalogMode(_tPS2);	//“红绿灯”配置模式，并选择是否保存
	//PS2_VibrationMode();			//开启震动模式
	PS2_ExitConfing(_tPS2);			//完成并保存配置
}


void PS2_Init(tagPS2_T *_tPS2)
{
    Drv_GPIO_Init(_tPS2->tGPIO,4);
    PS2_SetInit(_tPS2);
}
