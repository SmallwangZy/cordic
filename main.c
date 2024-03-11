#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define  ITER_COUNT 16
#define TARGE_ANGLE M_PI/3

/*未定义表，直接在迭代中使用pow函数计算，也可以定义好一个表，但迭代次数会受到限制*/
void angle_to_sin_cos(double angle0);
void sin_cos_to_angle(double x,double y);



int main() {
    printf("This is my cordic!\n");
    angle_to_sin_cos(TARGE_ANGLE);
    sin_cos_to_angle(1,1);
    return 0;
}

//通过角度求出sin和cos值
void angle_to_sin_cos(double angle0){
    double xpos[ITER_COUNT + 1];    //存储X坐标
    double ypos[ITER_COUNT + 1];    //存储Y坐标
    double angle[ITER_COUNT + 1];   //存储每次旋转角度

    angle[0] = TARGE_ANGLE;
    xpos[0] = 0.607253;

    int8_t rotate_dir = 0;

    //开始迭代
    for(int i = 0;i < ITER_COUNT;i++)
    {
        if(angle[i] > 0)
            rotate_dir = 1;      //顺转
        else
            rotate_dir = -1;     //逆转
        //这里应该是非原位计算，因此只能使用数组代替了(伪旋转)
        xpos[i + 1] = xpos[i] - rotate_dir * ypos[i] * (pow(2,-i));
        ypos[i + 1] = ypos[i] + rotate_dir * xpos[i] * (pow(2,-i));
        angle[i + 1] = angle[i] - rotate_dir * atan(pow(2,-i));
    }
    printf("Cordic output:cos:%.10lf,sin:%.10lf\n",xpos[ITER_COUNT],ypos[ITER_COUNT]);
    printf("Actual Value:cos:%.10lf,sin:%.10lf\n",cos(TARGE_ANGLE),sin(TARGE_ANGLE));
}

//通过x,y坐标求出角度
void sin_cos_to_angle(double x,double y){
    double x_temp = x;
    double x_value = x;       //Cannot change x,but you can change x_value
    double y_temp = y;

    double angle_sum = 0;

    int8_t rotate_dir = 0;

    //开始迭代
    for(int i = 0;i < ITER_COUNT;i++)
    {
        x_temp = x_value;
        if(y_temp < 0)
            rotate_dir = 1;      //逆转
        else
            rotate_dir = -1;     //顺转
        //这里应该是非原位计算，因此只能使用数组代替了(伪旋转)
        x_value = x_temp - rotate_dir * y_temp * (pow(2,-i));
        y_temp = y_temp + rotate_dir * x_temp * (pow(2,-i));

        angle_sum -= rotate_dir * atan(pow(2,-i));
    }
    printf("angle:%lf",angle_sum);
}
