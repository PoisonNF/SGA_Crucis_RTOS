#ifndef __PID_H__
#define __PID_H__

typedef struct pid
{
    float Kp;
    float Ki;
    float Kd;

    float max_out;  //PID最大输出
    float max_iout; //PID最大积分输出

    float set_value; //设定的期望值
    float pre_value; //前一次pid值
    float curr_value;//当前pid值

    float ctrl_out; //三项叠加输出值
    float Pout;
    float Iout;
    float Dout;

    float Dbuf[3];  //微分项最近三个值 0为最新 1上一次 2上上次
    float error[3]; //误差项最近三个值 0为最新 1上一次 2上上次

}PID;

void PID_init(PID *pid,  const float PID[3]);
void PID_calc(PID *pid,float ref,float set);
void PID_clear(PID *pid);


#endif

