/*-----------------------------------------------
  ���ƣ����������������
  ��̳��www.doflye.net
  ��д��shifang
  ���ڣ�2009.5
  �޸ģ���
  ���ݣ�����ʱ�̼�ⰴ��״̬�����ָʾ
------------------------------------------------*/
#include<reg52.h> //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���

sbit KEY=P2^0;  //���尴������˿�
sbit SW1=P2^7;  //����̵���1
sbit SW2=P2^6;  //����̵���2
unsigned char flag=1;    //���忪���ź�,Ĭ��Ϊ1,�״�ִ�йز���
sfr WDT_CONTR=0xe1; //���Ź�����

//ι��
void Rst_Watchdog( void )
{
	WDT_CONTR=0x35;
}

/*------------------------------------------------
                    ������
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
 while(--t);
}
/*------------------------------------------------
 mS��ʱ����������������� unsigned char t���޷���ֵ
 unsigned char �Ƕ����޷����ַ���������ֵ�ķ�Χ��
 0~255 ����ʹ�þ���12M����ȷ��ʱ��ʹ�û��
------------------------------------------------*/
void DelayMs(unsigned char t)
{
     
 while(t--)
 {
     //������ʱ1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}

//��ʱһ��
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



//��ʱ��
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


//���ƺ���
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
                  
KEY=1; //��������˿ڵ�ƽ�ø�
while (1)         //��ѭ��
  {
  	Rst_Watchdog();//ι��
  	if( KEY==0 && flag==0 )	{//���°���ʱ
	ON();
	}

	if( KEY==1 && flag==1 )	{//�ſ�����ʱ
	OFF();
	}

	//while(1);//ģ������,���Թ��ǲ�������,����Ϊ��������
  }
}