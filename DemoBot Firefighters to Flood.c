#include <kipr/botball.h>
int front_right = 0;
int back_right = 1;
int front_left = 2;
int back_left = 3;
int front_sensor = 1;
int light_sensor = 5;
int back_sensor = 0;
int Claw = 3;

int drive_forward(int power,int time);
int drive_forward_until_touch(int power);
int drive_backward(int power,int time);
int drive_backward_until_touch(int power);
int turn_right(int power,int time);
int turn_left(int power,int time);
int open_claw(int position,int time);
int close_claw(int position,int time);

int main()
{
    //Wait for light
    wait_for_light(light_sensor); 

    //Shut down after 120 seconds
    shut_down_in(120);

    //enable servos
    enable_servos();

    //GO forward until touching PVC
    drive_forward_until_touch(60);

    //Release claw
    open_claw(1300,1000);

    //reverse until rear sensor touches PVC
    drive_backward_until_touch(60);

    //GO forward
    drive_forward(100,500);

    //Turn left
    turn_left(100,250);

    //GO forward until touching the fire pole
    drive_forward_until_touch(60);

    //Grab a firefighter
    close_claw(550,1000);

    //Reverse
    drive_backward(100,500);

    //Turn right
    turn_right(100,250);

    //GO forward until touching the PVC
    drive_forward_until_touch(60);

    //Release claw
    open_claw(1300,1000); 

    //Repeat steps 3-11 4 times

    //disable servos
    disable_servos();

    return 0;
}

int drive_forward(int power,int time){
    mav(front_right,power);
    mav(front_left,power);
    mav(back_left,power);
    mav(back_right,power);
    msleep(time);
    ao();
    return 0; 
}

int drive_backward(int power,int time){
    mav(front_right,power);
    mav(front_left,power);
    mav(back_left,power);
    mav(back_right,power);
    msleep(time);
    ao();
    return 0; 
}

int turn_right(int power,int time){
    mav(front_left,power);
    mav(back_left,power);
    msleep(time);
    ao();
    return 0; 
}

int turn_left(int power,int time){
    mav(front_right,power);
    mav(back_right,power);
    msleep(time);
    ao();
    return 0; 
}

int drive_forward_until_touch(int power){
    while (analog(front_sensor)==0){
        mav(front_right,power);
        mav(front_left,power);
        mav(back_left,power);
        mav(back_right,power);
    }
    ao();
    return 0; 
}

int drive_backward_until_touch(int power){
    while (analog(back_sensor)==0){
        mav(front_right,power);
        mav(front_left,power);
        mav(back_left,power);
        mav(back_right,power);
    }
    ao();
    return 0; 
}

int open_claw(int position,int time){
    set_servo_position(3,250);
    msleep(1000);
    return 0;
}

int close_claw(int position,int time){
    set_servo_position(3,700);
    msleep(1000);
    return 0;
}
