#include <kipr/botball.h>
int front_right = 0;
int back_right = 1;
int front_left = 2;
int back_left = 3;
int front_sensor = 0;
int light_sensor = 0;
int et_sensor = 1;
int back_sensor = 1;
int claw = 3;
int open_claw_position = 775;
int close_claw_position = 0;
int claw_change_time = 500;

int drive_forward(int power,int time);
int drive_forward_until_touch(int power);
int drive_forward_until_close(int power);
int drive_forward_until_close_firepole(int power);
int drive_backward(int power,int time);
int drive_backward_until_touch(int power);
int turn_right(int power,int time);
int turn_left(int power,int time);
int open_claw();
int close_claw();

int main()
{
    //Wait for light
    // wait_for_light(light_sensor); 

    //Shut down after 120 seconds
    shut_down_in(120000);

    //enable servos
    enable_servos();

    //open claw
    open_claw();
    
    //drive forward slightly
    drive_forward(1000,200);

    //close claw
    close_claw();
    
    //GO forward until touching PVC
    drive_forward_until_close(550);

    //Release claw
    open_claw();

    //reverse until rear sensor touches PVC
    drive_backward_until_touch(500);

    //GO forward
    drive_forward(1000,800);

    //Turn left
    turn_left(1000,2000);

    //GO forward until touching the fire pole
    drive_forward_until_close_firepole(500);
    
    //Grab a firefighter
    close_claw();
return 0;
    //Reverse
    drive_backward(1000,500);

    //Turn right
    turn_right(1000,250);

    //GO forward until touching the PVC
    drive_forward_until_touch(1000);

    //Release claw
    open_claw(); 

    //Repeat steps 3-11 4 times

    //disable servos
    disable_servos();

    return 0;
}

int drive_forward(int power,int time){
    mav(front_right,power);
    mav(front_left,power+(power*.1));
    mav(back_left,power+(power*.1));
    mav(back_right,power);
    msleep(time);
    ao();
    return 0; 
}

int drive_backward(int power,int time){
    mav(front_right,-power);
    mav(front_left,-power+(-power*.075));
    mav(back_left,-power+(-power*.075));
    mav(back_right,-power);
    msleep(time);
    ao();
    return 0; 
}

int turn_right(int power,int time){ao();
    mav(front_left,power);
    mav(back_left,power);
    msleep(time);
    ao();
    return 0; 
}

int turn_left(int power,int time){ao();
    mav(front_right,power);
    mav(back_right,power);
    msleep(time);
    ao();
    return 0; 
}

int drive_forward_until_touch(int power){
    while (digital(front_sensor)==0){
        drive_forward(power, 500);
    }

    ao();
    return 0; 
}

int drive_forward_until_close(int power){
    while (analog_et(et_sensor)<2900){
        drive_forward(power, 500);
    }
    drive_forward(500,200);
    ao();
    return 0; 
}
int drive_forward_until_close_firepole(int power){
    while (analog_et(et_sensor)<2250){
        drive_forward(power, 500);
    }
    drive_forward(500,200);
    ao();
    return 0; 
}
int drive_backward_until_touch(int power){
    while (digital(back_sensor)==0){
        drive_backward(power, 500);
    }
    ao();
    return 0; 
}

int open_claw(){
    set_servo_position(claw, open_claw_position);
    msleep(claw_change_time);
    return 0;
}

int close_claw(){
    set_servo_position(claw,close_claw_position);
    msleep(claw_change_time);
    return 0;
}
int drive_backward_until_close(int power){
    while (analog_et(et_sensor)<2900){
        drive_backward(power, 500);
    }
    ao();
    return 0; 
}
