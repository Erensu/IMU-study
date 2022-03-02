double  KalmanFilter_x(const double ResrcData,double ProcessNiose_Q,double MeasureNoise_R) //��һ��������1~20���ڶ�������0.01����
{
    double R = MeasureNoise_R;
    double Q = ProcessNiose_Q;
    static double x_last;
    double x_mid = x_last;
    double x_now;
    static double p_last;
    double p_mid ;
    double p_now;
    double kg;        
    x_mid=x_last; //x_last=x(k-1|k-1),x_mid=x(k|k-1)
    p_mid=p_last+Q; //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=??����
    kg=p_mid/(p_mid+R); //kg?akalman filter��?R?a??����
    x_now=x_mid+kg*(ResrcData-x_mid);//1��??3?��?��?��??��
    p_now=(1-kg)*p_mid;//��?��??��??��|��?covariance       
    p_last = p_now; //?��D?covariance?��
    x_last = x_now; //?��D??�̨�3���䨬??��
    return x_now;                
}




//*
//-------------------------------------------------------
//Kalman�˲���8MHz�Ĵ���ʱ��Լ1.8ms��
//-------------------------------------------------------
static float angle, angle_dot; 		//�ⲿ��Ҫ���õı���
//-------------------------------------------------------
static const float Q_angle=0.001, Q_gyro=0.003, R_angle=0.5, dt=0.01;
			//ע�⣺dt��ȡֵΪkalman�˲�������ʱ��;
static float P[2][2] = {
							{ 1, 0 },
							{ 0, 1 }
						};
	
static float Pdot[4] ={0,0,0,0};

static const char C_0 = 1;

static float q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;
//-------------------------------------------------------
void Kalman_Filter(float angle_m,float gyro_m)			//gyro_m:gyro_measure
{
	angle+=(gyro_m-q_bias) * dt;
	
	Pdot[0]=Q_angle - P[0][1] - P[1][0];
	Pdot[1]=- P[1][1];
	Pdot[2]=- P[1][1];
	Pdot[3]=Q_gyro;
	
	P[0][0] += Pdot[0] * dt;
	P[0][1] += Pdot[1] * dt;
	P[1][0] += Pdot[2] * dt;
	P[1][1] += Pdot[3] * dt;
	
	
	angle_err = angle_m - angle;
	
	
	PCt_0 = C_0 * P[0][0];
	PCt_1 = C_0 * P[1][0];
	
	E = R_angle + C_0 * PCt_0;
	
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;
	
	t_0 = PCt_0;
	t_1 = C_0 * P[0][1];

	P[0][0] -= K_0 * t_0;
	P[0][1] -= K_0 * t_1;
	P[1][0] -= K_1 * t_0;
	P[1][1] -= K_1 * t_1;
	
	
	angle	+= K_0 * angle_err;
	q_bias	+= K_1 * angle_err;
	angle_dot = gyro_m-q_bias;
}
//*/

/*
//-------------------------------------------------------
//�����˲�
//-------------------------------------------------------
static float angle,angle_dot; 		//�ⲿ��Ҫ���õı���
//-------------------------------------------------------	
static float bias_cf;
static const float dt=0.01;
//-------------------------------------------------------
void complement_filter(float angle_m_cf,float gyro_m_cf)
{
	bias_cf*=0.998;			//��������Ʈ��ͨ�˲���500�ξ�ֵ��
	bias_cf+=gyro_m_cf*0.002;
	angle_dot=gyro_m_cf-bias_cf;
	angle=(angle+angle_dot*dt)*0.90+angle_m_cf*0.05;	
	//���ٶȵ�ͨ�˲���20�ξ�ֵ����100��ÿ����㣬��ͨ5Hz��
}
*/	