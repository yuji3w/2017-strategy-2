#pragma config(Motor,  motorA,          Left,          tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorD,          Right,         tmotorEV3_Medium, PIDControl, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define FIELDX 120.5
#define FIELDY 120
#define SPEED 50

#define WHEEL 18
#define AXLE 26.4

void moveRob(float distance, int speed);
void rotateRob(float angle, int speed);

task main()
{
	sleep(1000);
	moveRob(FIELDY-AXLE/2,SPEED);
	rotateRob(-90,SPEED);
	moveRob(FIELDX-AXLE/2,SPEED);
	rotateRob(-90,SPEED);
	moveRob(FIELDY-AXLE/2,SPEED);
	rotateRob(-90,SPEED);
	moveRob(((FIELDX/2)-10)-(AXLE/2),SPEED);
	rotateRob(-90,SPEED);
}

void moveRob(float distance, int speed){
	int encoder[2];
	encoder[0] = getMotorEncoder(Left);
	encoder[1] = getMotorEncoder(Right);
	setMotorSpeed(Left,speed*sgn(distance));
	setMotorSpeed(Right,speed*sgn(distance));
	distance = distance * (360 / WHEEL);
	encoder[0] += distance;
	encoder[1] += distance;
	int flag = sgn(encoder[0]-getMotorEncoder(Left));
	while(flag+sgn(encoder[0]-getMotorEncoder(Left)) && flag+sgn(encoder[1]-getMotorEncoder(Right))){}
	setMotorSpeed(Left,0);
	setMotorSpeed(Right,0);
	resetMotorEncoder(Left);
	resetMotorEncoder(Right);
}

void rotateRob(float angle, int speed){
	int encoder[2];
	encoder[0] = getMotorEncoder(Left);
	encoder[1] = getMotorEncoder(Right);
	setMotorSpeed(Left,speed*sgn(angle));
	setMotorSpeed(Right,speed*-sgn(angle));
	float distance = angle * (AXLE * PI * (360.0 / WHEEL)) / 360.0;
	encoder[0] += distance;
	encoder[1] -= distance;
	int flag[2];
	flag[0] = sgn(encoder[0]-getMotorEncoder(Left));
	flag[1] = sgn(encoder[1]-getMotorEncoder(Left));
	while(flag[0]+sgn(encoder[0]-getMotorEncoder(Left)) && flag[1]+sgn(encoder[1]-getMotorEncoder(motorB))){}
	setMotorSpeed(Left,0);
	setMotorSpeed(Right,0);
}
