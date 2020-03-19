/*-----------------------------------------------
  名称：单个独立按键检测
  论坛：www.doflye.net
  编写：shifang
  日期：2009.5
  修改：无
  内容：用于时刻检测按键状态并输出指示
------------------------------------------------*/
#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义

sbit KEY=P2^0;  //定义按键输入端口
sbit SW1=P2^7;  //定义继电器1
sbit SW2=P2^6;  //定义继电器2
unsigned char flag=1;    //定义开关信号,默认为1,首次执行关操作
sfr WDT_CONTR=0xe1; //看门狗定义

//喂狗
void Rst_Watchdog( void )
{
	WDT_CONTR=0x35;
}

/*------------------------------------------------
                    主函数
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
 while(--t);
}
/*------------------------------------------------
 mS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编
------------------------------------------------*/
void DelayMs(unsigned char t)
{
     
 while(t--)
 {
     //大致延时1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}

//延时一秒
void DelayS(unsigned char t)
{
 while(t--)
  {
  Rst_Watchdog();	
   DelayMs(255);
   DelayMs(255);
   DelayMs(255);
   DelayMs(255);
  }
}



//延时开
void Sw1Delay()
{
SW1=0;
DelayS(10);
SW1=1;

}
void Sw2Delay()
{
SW2=0;
DelayS(10);
SW2=1;
}


//控制函数
void ON(){
	flag=1;
  	Sw1Delay();
	DelayS(1);
}

void OFF(){
	flag=0;
	Sw2Delay();
	DelayS(1);
}

void main (void)
{
                  
KEY=1; //按键输入端口电平置高
while (1)         //主循环
  {
  	Rst_Watchdog();//喂狗
  	if( KEY==0 && flag==0 )	{//按下按键时
	ON();
	}

	if( KEY==1 && flag==1 )	{//放开按键时
	OFF();
	}

	//while(1);//模拟死机,测试狗是不是正常,正常为不断重启
  }
}