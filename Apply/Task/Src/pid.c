#include "task_conf.h"

void PID_init(PID *pid,  const float PID[3])
{
    if (pid == NULL || PID == NULL)
    {
        return;
    }

    pid->Kp = PID[0];
    pid->Ki = PID[1];
    pid->Kd = PID[2];
    //pid->max_out = max_out;
    //pid->max_iout = max_iout;
    pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0.0f;
    pid->error[0] = pid->error[1] = pid->error[2] = pid->Pout = pid->Iout = pid->Dout = pid->ctrl_out = 0.0f;
}

void PID_calc(PID *pid,float ref,float set)
{
    int ctrl_delt_out; //PID输出增量
    if(pid == NULL) while(1);

    //设定期望值和当前值
    pid->set_value  = set;
    pid->curr_value = ref;
    
    pid->error[0] = set-ref;

    //增量式PID
    //以本次误差与上次误差的差值作为比例项的输入带入计算
    pid->Pout = pid->Kp * (pid->error[0] - pid->error[1]);
    //以本次误差作为积分项带入计算
    pid->Iout = pid->Ki * pid->error[0];
    //迭代微分项的数组
    pid->Dbuf[2] = pid->Dbuf[1];
    pid->Dbuf[1] = pid->Dbuf[0];
    //以本次误差与上次误差的差值减去上次误差与上上次误差的差值作为微分项的输入带入计算
    pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
    pid->Dout = pid->Kd * pid->Dbuf[0];
    
    ctrl_delt_out= (int)(pid->Pout + pid->Iout + pid->Dout); //计算增量输出
    pid->ctrl_out = pid->pre_value + ctrl_delt_out; //与前值累加
    pid->pre_value = pid->ctrl_out;//记录数值，为下次pid做准备

    //存放过去两次误差值
    pid->error[2] = pid->error[1];
    pid->error[1] = pid->error[0];
}

void PID_clear(PID *pid)
{
    if (pid == NULL)
    {
        return;
    }
	//当前误差清零
    pid->error[0] = pid->error[1] = pid->error[2] = 0.0f;
    //微分项清零
    pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0.0f;
    //输出清零
    pid->ctrl_out = pid->Pout = pid->Iout = pid->Dout = 0.0f;
    //目标值和当前值清零
    pid->curr_value = pid->set_value = 0.0f;
}
