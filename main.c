#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define  ITER_COUNT 16
#define TARGE_ANGLE M_PI/3

int main() {
    printf("This is my cordic!\n");
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
        //这里应该是非原位计算，因此只能使用数组代替了
        xpos[i + 1] = xpos[i] - rotate_dir * ypos[i] * (pow(2,-i));
        ypos[i + 1] = ypos[i] + rotate_dir * xpos[i] * (pow(2,-i));
        angle[i + 1] = angle[i] - rotate_dir * atan(pow(2,-i));
    }
    printf("Cordic output:cos:%.10lf,sin:%.10lf\n",xpos[ITER_COUNT],ypos[ITER_COUNT]);
    printf("Actual Value:cos:%.10lf,sin:%.10lf\n",cos(TARGE_ANGLE),sin(TARGE_ANGLE));

    return 0;
}
