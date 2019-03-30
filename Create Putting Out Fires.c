#include <kipr/botball.h>

//variables
int LIGHT_SENSOR = 0;
int SHOULDER_SERVO = 2;
int ELBOW_SERVO = 3;
int CLAW_SERVO = 1;

//function declarations
void drive_forward(int power, int time);
void drive_backward(int power, int time);
void turn_left(int power, int time);
void turn_right(int power, int time);
void turn_left_with_angle(int angle);
void turn_right_with_angle(int angle);
void set_claw(int position);
void set_shoulder(int position);
void set_elbow(int postion);
void move_servo(int servo_port,int position);

int main()
{
    //wait for light
    //wait_for_light();
    //extend elbow
    set_elbow(1250);
    
    //open claw
    set_claw(1400);
    
    //drive towards blue water cube
    drive_forward(50, 1000);

    //slightly turn left
    turn_left_with_angle(-30);
    
    //close claw to pick up blue water cube
    set_claw(400);
    
    //turn slightly to the right
    turn_right_with_angle(30);
    
    //reverse back to starting box
    drive_backward(-50, 1000);
    
    //turn towards burning skyscraper
    turn_right(50,500);
    
    //use camera to detect burning skyscraper
    //drive towards skyscrapers
    //place blue cube on burning skyscraper
    //grab botguy off of skyscraper
    //drive back to starting box
    //drop botguy in starting box
    //drive back towards skyscraper
    //grab the mayor
    //drive back to starting box
    //drop mayor in starting box
    //stop in starting box
    return 0;
}

//function definitions
void drive_forward(int power, int time)
{
    create_drive_direct(power,power);
    msleep(time);
    create_stop();
}

void drive_backward(int power, int time)
{
    create_drive_direct(power,power);
    msleep(time);
    create_stop();
}

void turn_left(int power, int time)
{
    create_drive_direct(-power,power);
    msleep(time);
    create_stop();
}

void turn_left_with_angle(int angle)
{
    set_create_total_angle(0);
    while (get_create_total_angle()> angle)
    { 
       turn_left(50,0);
    }  
}

void turn_right(int power, int time)
{
    create_drive_direct(power,-power);
    msleep(time);
    create_stop();
}

void turn_right_with_angle(int angle)
{
    set_create_total_angle(0);
    while (get_create_total_angle()< angle)
    { 
        turn_right(50,0);
    }
    
}

void set_claw(int position)
{
    move_servo(CLAW_SERVO, position);
}

void set_shoulder(int position)
{
    move_servo(SHOULDER_SERVO, position);
}

void set_elbow(int position)
{
    move_servo(ELBOW_SERVO, position);
}

void move_servo(int servo_port, int position)
{
    // gradually increase servo position to desired position
    if(get_servo_position(servo_port) < position)
    {
        while (get_servo_position(servo_port) < position)
        {
            set_servo_position(servo_port, get_servo_position(servo_port)+50);
            msleep(500);
        }
    }
    // gradually decrease servo position to desired position
    else if (get_servo_position(servo_port) > position)
    {
        while (get_servo_position(servo_port) > position)
        { 
            set_servo_position(servo_port, get_servo_position(servo_port)-50);
            msleep(500);
        }
    }
}   
