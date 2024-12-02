#include "task_motorsys.h"

/**
 * @brief ���ϵͳ��ʼ������
 * @param Null
 */
void Task_MotorSys_Init(void)
{
    Drv_PWM_Init(PWM,11);   /* ��ʼ��PWM */
    Drv_Delay_Ms(10000);
}

/* �ƽ����ߵ�ƽʱ��1.5msͣת */
#define STOP_PWM_HIGHTIME 1500

/**
 * @brief �ƽ���ת�������Ӻ���
 * @param index ѡ�񼸺��ƽ���
 * @param _highTime �ߵ�ƽʱ���С	_highTime������Ϊ500-2500,1500ֹͣ
							500-1500 ��ʱ����ת 1500-2500˳ʱ����ת
 * @retval null
*/
void Task_MotorSys_Thruster_SpeedSet(uint8_t index,uint16_t _highTime)
{
	Drv_PWM_HighLvTimeSet(&PWM[index], _highTime);
}

/**
 * @brief �����ƽ�����ͬת�����ú���
 * @param _highTime �ߵ�ƽʱ���С	_highTime������Ϊ500-2500,1500ֹͣ
							500-1500 ��ʱ����ת 1500-2500˳ʱ����ת
 * @retval null
*/
void Task_MotorSys_AllThruster_SpeedSet(uint16_t _highTime)
{
	Drv_PWM_HighLvTimeSet(&PWM[A_1], _highTime);
	Drv_PWM_HighLvTimeSet(&PWM[B_1], _highTime);
	Drv_PWM_HighLvTimeSet(&PWM[C_1], _highTime);
	Drv_PWM_HighLvTimeSet(&PWM[D_1], _highTime);
}	

/**
 * @brief �ƽ�����ʼ����
 * @param index ѡ�񼸺��ƽ���
 * @param _highTime �ߵ�ƽʱ���С
 * @retval null
*/
void Task_MotorSys_Thruster_Start(uint8_t index,uint16_t _highTime)
{
	/* �ƽ��������ٶ����� */
	Task_MotorSys_Thruster_SpeedSet(index,_highTime);
}

/**
 * @brief �����ƽ�����ʼ����
 * @param *adress ����ĸ��ƽ����ķ���������׵�ַ
 * @retval null
*/
void Task_MotorSys_AllThruster_Start(float *adress)
{
	Task_MotorSys_Thruster_Start(A_1,*adress+STOP_PWM_HIGHTIME);
	Task_MotorSys_Thruster_Start(B_1,*(adress+1)+STOP_PWM_HIGHTIME);
	Task_MotorSys_Thruster_Start(C_1,*(adress+2)+STOP_PWM_HIGHTIME);
	Task_MotorSys_Thruster_Start(D_1,*(adress+3)+STOP_PWM_HIGHTIME);
}

/**
 * @brief �ƽ���ֹͣ����
 * @param index ѡ�񼸺��ƽ���
 * @param _fVal ռ�ձȴ�С
 * @retval null
*/
void Task_MotorSys_Thruster_Stop(uint8_t index)
{
	/* �ƽ��������ٶ����� */
	Drv_PWM_HighLvTimeSet(&PWM[index], STOP_PWM_HIGHTIME);
}

/**
 * @brief �����ƽ���ֹͣ����
 * @param null
 * @retval null
*/
void Task_MotorSys_AllThruster_Stop(void)
{
	Task_MotorSys_Thruster_Stop(A_1);
	Task_MotorSys_Thruster_Stop(B_1);
	Task_MotorSys_Thruster_Stop(C_1);
	Task_MotorSys_Thruster_Stop(D_1);
}

/*180����
    0.5ms----------------0�ȣ�          2.5%
    1ms -----------------45�ȣ�         5%
    1.5ms----------------90�ȣ�         7.5%
    2ms -----------------135�ȣ�        10%
    2.5ms ---------------180��          12.5% */

#define ANGLE_0_PWM_HIGHTIME        500
#define ANGLE_90_PWM_HIGHTIME       1500
#define ANGLE_180_PWM_HIGHTIME      2500

/**
 * @brief ���ת�Ǻ���
 * @param index ѡ�񼸺Ŷ�� 
 * @param ang �Ƕȣ�0�ȡ���180�ȣ�
 * @retval null
*/
void Task_MotorSys_Steer_Angle_Set(uint8_t index,uint8_t ang)
{
    Drv_PWM_HighLvTimeSet(&PWM[index],ang/180*2000+500);
}

/**
 * @brief �����0�Ⱥ���
 * @param index ѡ�񼸺Ŷ�� 
 * @retval null
*/
void Task_MotorSys_Steer_0Angle(uint8_t index)
{
    Drv_PWM_HighLvTimeSet(&PWM[index],ANGLE_0_PWM_HIGHTIME);
}

/**
 * @brief ���ж����0�Ⱥ���
 * @param NULL
 * @retval null
*/
void Task_MotorSys_AllSteer_0Angle(void)
{
    Task_MotorSys_Steer_0Angle(A_2);
    Task_MotorSys_Steer_0Angle(B_2);
    Task_MotorSys_Steer_0Angle(C_2);
    Task_MotorSys_Steer_0Angle(D_2);
    //Drv_Delay_Ms(500);//��ʱ500ms���ת��,��ʱʱ�������
}

/**
 * @brief �����90�Ⱥ���
 * @param index ѡ�񼸺Ŷ�� 
 * @retval null
*/
void Task_MotorSys_Steer_90Angle(uint8_t index)
{
    Drv_PWM_HighLvTimeSet(&PWM[index],ANGLE_90_PWM_HIGHTIME);
}

/**
 * @brief ���ж����90�Ⱥ���
 * @param NULL
 * @retval null
*/
void Task_MotorSys_AllSteer_90Angle(void)
{
    Task_MotorSys_Steer_90Angle(A_2);
    Task_MotorSys_Steer_90Angle(B_2);
    Task_MotorSys_Steer_90Angle(C_2);
    Task_MotorSys_Steer_90Angle(D_2);
    //Drv_Delay_Ms(500);//��ʱ500ms���ת��
}

/**
 * @brief �����180�Ⱥ���
 * @param index ѡ�񼸺Ŷ�� 
 * @retval null
*/
void Task_MotorSys_Steer_180Angle(uint8_t index)
{
    Drv_PWM_HighLvTimeSet(&PWM[index],ANGLE_180_PWM_HIGHTIME);
}

/**
 * @brief ���ж����180�Ⱥ���
 * @param NULL
 * @retval null
*/
void Task_MotorSys_AllSteer_180Angle(void)
{
    Task_MotorSys_Steer_180Angle(A_2);
    Task_MotorSys_Steer_180Angle(B_2);
    Task_MotorSys_Steer_180Angle(C_2);
    Task_MotorSys_Steer_180Angle(D_2);
    //Drv_Delay_Ms(500);//��ʱ500ms���ת��
}



