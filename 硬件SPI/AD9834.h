/*-----------------------------------------------------

                    AD9834��������
                    STM32HAL��
                    2019.10.16
-------------------------------------------------------*/
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//AD9834��������	   
//���ߣ�����
//��������:2019/10/16
//�汾��V1.0
//��Ȩ���У�����ؾ���									  
//////////////////////////////////////////////////////////////////////////////////
#ifndef __AD9834_H
#define __AD9834_H

//#include "sys.h"
#include "spi.h"
#define Triangle_Wave    0x2002
#define Sine_Wave  0x2000

/* AD9834����Ƶ�� */
#define AD9834_SYSTEM_COLCK     75000000UL

/* AD9834 �������� */
#define AD9834_Control_Port     GPIOA
#define AD9834_FSYNC            GPIO_PIN_8
//#define AD9834_RESET_SET            0x2100
//#define AD9834_RESET_CLR            0x2000

#define AD9834_FSYNC_SET   HAL_GPIO_WritePin(AD9834_Control_Port ,AD9834_FSYNC,GPIO_PIN_SET)
#define AD9834_FSYNC_CLR   HAL_GPIO_WritePin(AD9834_Control_Port ,AD9834_FSYNC,GPIO_PIN_RESET)
#define AD9834_RESET_SET   HAL_GPIO_WritePin(AD9834_Control_Port ,GPIO_PIN_4,GPIO_PIN_SET) 

#define AD9834_RESET_CLR   HAL_GPIO_WritePin(AD9834_Control_Port ,GPIO_PIN_4,GPIO_PIN_RESET) 


#define FREQ_0      0
#define FREQ_1      1

/* AD9834�������� */
void AD9834_Write_16Bits(unsigned int data) ;
void AD9834_Select_Wave(unsigned int initdata) ;
void Init_AD9834(void) ;
void AD9834_Set_Freq(unsigned char freq_number, unsigned long freq) ;

#endif /* AD9834_H */
