#include <ros.h>
#include <geometry_msgs/Twist.h>

#define enA 6
#define IN1 26
#define IN2 28
#define IN3 30
#define IN4 32
#define enB 7

void onTwist(const geometry_msgs::Twist& msg) {
  
  // forward (i)
  if (msg.linear.x > 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
 }

  // STOP (,/.)
else if (msg.linear.x < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  //LEFT (j/u)
  else if (msg.angular.z > 0) {
   digitalWrite(IN1, LOW);
   digitalWrite(IN2, HIGH);
   digitalWrite(IN3, LOW);
   digitalWrite(IN4, LOW);
  }
  
  // RIGHT (L/O)
  else if (msg.angular.z < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  // stop both motors
  //else {
   // digitalWrite(IN1, LOW);
   /// digitalWrite(IN2, LOW);
   // digitalWrite(IN3, LOW);
   // digitalWrite(IN4, LOW);
 // }

  // Set motors to maximum speed
  analogWrite(enA, 255);
  analogWrite(enB, 255);
}


ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", onTwist);

ros::NodeHandle nh;

void setup() {
  // put your setup code here, to run once:
  pinMode(enA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(enB, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce();
}