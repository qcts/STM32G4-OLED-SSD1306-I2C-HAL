#ifndef __OLED_H
#define __OLED_H

#include "main.h"
#include <stdint.h>
#include "OLED_Data.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>

/************************************* ����Ϊ�����궨��*******************************************/

/**
 * FontSize����ȡֵ
 * �˲���ֵ���������жϣ��������ڼ�������ַ�ƫ�ƣ�Ĭ��ֵΪ�������ؿ��
 */
#define OLED_8X16               8
#define OLED_6X8                6

/*IsFilled������ֵ*/
#define OLED_UNFILLED           0
#define OLED_FILLED             1

/*******************��ֲ��Ҫ�޸ĵĺ궨��******************/
/* ����õ����ģ�����������ѡ����Ҫ�� --no-multibyte-chars (��AC6�������Ĳ��ü�) */

/**
 * ѡ��OLED������ʽ��Ĭ��ʹ��Ӳ��I2C��
 * ���Ҫ�����I2C�ͽ�Ӳ��I2C���еĺ궨��ע�͵��������I2C���е�ע��ȡ����
 * ����ͬʱ������ͬʱȡ��ע�ͣ�
 */
#define OLED_USE_HW_I2C                                /* Ӳ��I2C */
//#define OLED_USE_SW_I2C                              /* ���I2C */

#ifdef OLED_USE_HW_I2C
#define OLED_I2C                hi2c1                  /* ����OLED��ʹ��hi2cx�ӿ� */
extern  I2C_HandleTypeDef       hi2c1;                /* HAL��ʹ�ã�ָ��Ӳ��IIC�ӿ� */
#endif

/* STM32F103C8T6оƬ��Ӳ��I2C1: PB6 -- SCLPB7 -- SDA
 * ��Ҫ��stm32cubemx�����ʼ��ʱ��SCL��SDA���ŵ�"user lable"�ֱ�����Ϊ��Ӧ��I2Cx_SCL��I2Cx_SDA��
 */

#define OLED_SCL                I2C_SCL_Pin            /* I2Cx_SCL���� */
#define OLED_SDA                I2C_SDA_Pin            /* I2Cx_SDA���� */
#define OLED_SCL_GPIO_Port      I2C_SCL_GPIO_Port      /* I2Cx_SCL�˿� */
#define OLED_SDA_GPIO_Port      I2C_SDA_GPIO_Port      /* I2Cx_SDA�˿� */

/*******************��ֲ��Ҫ�޸ĵĺ궨��******************/

/**
 * OLED�ӻ���ַ
 * 0x3C��OLED��7λ��ַ������1λ���λ����дλ���0x78
 */
#define OLED_ADDRESS 0x3C << 1

/* I2C��ʱʱ�� */
#define OLED_I2C_TIMEOUT 10

/**
 * ���I2C�õ���ʱʱ��
 * ������ֵΪ170MHz��ƵҪ��ʱ��ֵ����������Ƶ��һ�������޸�һ��
 * 100MHz���ڵ���Ƶ�ĳ�0����
 */
#define Delay_time 0

/***************************************����Ϊ��������*******************************************/

/*��ʼ������*/
void OLED_Init(void);

/*���º���*/
void OLED_Update(void);
void OLED_UpdateArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);

/*�Դ���ƺ���*/
void OLED_Clear(void);
void OLED_ClearArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);
void OLED_Reverse(void);
void OLED_ReverseArea(int16_t X, int16_t Y, uint8_t Width, uint8_t Height);

/*��ʾ����*/
void OLED_ShowChar(int16_t X, int16_t Y, char Char, uint8_t FontSize);
void OLED_ShowString(int16_t X, int16_t Y, char *String, uint8_t FontSize);
void OLED_ShowNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowSignedNum(int16_t X, int16_t Y, int32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowHexNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowBinNum(int16_t X, int16_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowFloatNum(int16_t X, int16_t Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize);
void OLED_ShowImage(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image);
void OLED_Printf(int16_t X, int16_t Y, uint8_t FontSize, char *format, ...);

/*��ͼ����*/
void OLED_DrawPoint(int16_t X, int16_t Y);
uint8_t OLED_GetPoint(int16_t X, int16_t Y);
void OLED_DrawLine(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1);
void OLED_DrawRectangle(int16_t X, int16_t Y, uint8_t Width, uint8_t Height, uint8_t IsFilled);
void OLED_DrawTriangle(int16_t X0, int16_t Y0, int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint8_t IsFilled);
void OLED_DrawCircle(int16_t X, int16_t Y, uint8_t Radius, uint8_t IsFilled);
void OLED_DrawEllipse(int16_t X, int16_t Y, uint8_t A, uint8_t B, uint8_t IsFilled);
void OLED_DrawArc(int16_t X, int16_t Y, uint8_t Radius, int16_t StartAngle, int16_t EndAngle, uint8_t IsFilled);

#endif


/*****************��Э�Ƽ�|��Ȩ����****************/
/*****************jiangxiekeji.com*****************/
