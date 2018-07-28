//we only need move and turn right lol

#define WHEEL 18
#define AXLE 13
#define FIELDX 116.5
#define FIELDY 98.5

float speed;

void turn(float angle, float radius);
void moveRob(float distance);

task main()
{
	speed = 60;
	turn(90,0);
	moveRob(FIELDX/2);

}

void turn(float angle, float radius){
	float outer = angle*2*PI*(radius+AXLE)/WHEEL;
	float inner = angle*2*PI*(radius)/WHEEL;
	float ospeed = speed;
	float ispeed = speed * inner / outer;
	moveMotorTarget(motorD, outer, ospeed);
	moveMotorTarget(motorA, inner, ispeed);
	while(!getMotorSpeed(motorD) || !getMotorSpeed(motorA)){}
}

void moveRob(float distance){
	int encoder[2];
	encoder[0] = getMotorEncoder(motorA);
	encoder[1] = getMotorEncoder(motorD);
	setMotorSpeed(motorA, speed*sgn(distance));
	setMotorSpeed(motorD, speed*sgn(distance));
	distance = distance * (360 / WHEEL);
	encoder[0] += distance;
	encoder[1] += distance;
	int flag = sgn(encoder[0]-getMotorEncoder(motorA));
	while(flag+sgn(encoder[0]-getMotorEncoder(motorA)) && flag+sgn(encoder[1]-getMotorEncoder(motorD))){}
	setMotorSpeed(motorA,0);
	setMotorSpeed(motorD,0);
}
