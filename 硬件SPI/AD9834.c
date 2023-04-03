
#include "AD9834.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//AD9834��������	   
//���ߣ�����
//��������:2019/10/16
//�汾��V1.0
//��Ȩ���У�����ؾ���									  
//////////////////////////////////////////////////////////////////////////////////

/****************************************************************
��������: AD9834_Write_16Bits
��    ��: ��AD9834д��16Ϊ����
��    ��: data --  Ҫд���16λ����
����ֵ  : ��
*****************************************************************/
void AD9834_Write_16Bits(unsigned int data)
{

    unsigned int temp;
		temp=data&0x00ff;
		data>>=8;
    AD9834_FSYNC_CLR ;
		SPI1_ReadWriteByte(data);
		SPI1_ReadWriteByte(temp);
    AD9834_FSYNC_SET ;
}

/***********************************************************************************
�������ƣ�AD9834_Select_Wave
��    �ܣ����Ϊ���ƣ�
    --------------------------------------------------
    IOUT���Ҳ� ��SIGNBITOUT���� ��дFREQREG0 ��дPHASE0
    ad9834_write_16bit(0x2038)   һ����дFREQREG0
    ad9834_write_16bit(0x0038)   ������дFREQREG0��LSB
    ad9834_write_16bit(0x1038)   ������дFREQREG0��MSB
    --------------------------------------------------
    IOUT���ǲ� ��дPHASE0
    ad9834_write_16bit(0x2002)   һ����дFREQREG0
    ad9834_write_16bit(0x0002)   ������дFREQREG0��LSB
    ad9834_write_16bit(0x1008)   ������дFREQREG0��MSB
��    ����initdata -- Ҫ���������
����ֵ  ����
************************************************************************************/
void AD9834_Select_Wave(unsigned int initdata)
{
    AD9834_Write_16Bits(initdata);
}

/****************************************************************
��������: Init_AD9834
��    ��: ��ʼ��AD9834��������
��    ��: ��
����ֵ  : ��
*****************************************************************/
void Init_AD9834()
{
	  MX_SPI1_Init();
//    AD9834_Write_16Bits(AD9834_RESET_SET);
		AD9834_Write_16Bits(0x2100);
		AD9834_Write_16Bits(0x2038);
		AD9834_Write_16Bits(0XC000);
		AD9834_Write_16Bits(0x2100);

}

/****************************************************************
��������: AD9834_Set_Freq
��    ��: ����Ƶ��ֵ
��    ��: freq_number -- Ҫд���ƽ�ʼĴ���
          freq -- Ƶ��ֵ (Freq_value(value)=Freq_data(data)*FCLK/2^28)
����ֵ  : ��
*****************************************************************/
void AD9834_Set_Freq(unsigned char freq_number, unsigned long freq)
{
    unsigned long FREQREG = (unsigned long)(268435456.0/AD9834_SYSTEM_COLCK*freq);
   
    unsigned int FREQREG_LSB_14BIT = (unsigned int)FREQREG;
    unsigned int FREQREG_MSB_14BIT = (unsigned int)(FREQREG>>14);
    
    if(freq_number == FREQ_0)
    {
        FREQREG_LSB_14BIT &= ~(1U<<15);
        FREQREG_LSB_14BIT |= 1<<14;
        FREQREG_MSB_14BIT &= ~(1U<<15);
        FREQREG_MSB_14BIT |= 1<<14;
    }
    else
    {
        FREQREG_LSB_14BIT &= ~(1<<14);
        FREQREG_LSB_14BIT |= 1U<<15;
        FREQREG_MSB_14BIT &= ~(1<<14);
        FREQREG_MSB_14BIT |= 1U<<15;
    }
    
    AD9834_Write_16Bits(FREQREG_LSB_14BIT);
    AD9834_Write_16Bits(FREQREG_MSB_14BIT);
//    AD9834_Write_16Bits(AD9834_RESET_CLR);
}


