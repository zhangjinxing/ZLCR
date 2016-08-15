#include "BSP.h"
//#include "math.h"


int16_t I2S_ADCBuf[2048];
int16_t I2S_DACBuf[2048];
int16_t fifo[4][1024];

float freq = 0; 	//freq
uint32_t Wave_tick1 = 0;
uint32_t Wave_sum1 = 0;	//phase

extern I2C_HandleTypeDef hi2c1;
extern I2S_HandleTypeDef hi2s3;
extern void DSP_I2S_Callback(int16_t* pt1, int16_t* pt2, int16_t* pt3, int16_t* pt4, uint16_t offset);

const int16_t SinWave[] = {
0,184,368,552,736,920,1104,1288,1472,1656,1840,2023,2207,2390,2574,2757,2941,3124,3307,3490,3672,3855,4037,4220,4402,4584,4766,4947,5129,5310,5491,5672,5853,6033,6213,6393,6573,6753,6932,7111,7289,7468,7646,7824,8001,8179,8356,8532,8709,8885,9060,9235,9410,9585,9759,9933,10107,10280,10453,10625,10797,10968,11140,11310,11481,11650,11820,11989,12157,12325,12493,12660,12827,12993,13158,13324,13488,13653,13816,13979,14142,14304,14466,14627,14787,14947,15106,15265,15423,15581,15738,15894,16050,16205,16360,16514,16667,16820,16972,17123,17274,17424,17574,17723,17871,18018,18165,18311,18457,18602,18746,18889,19032,19174,19315,19455,19595,19734,19872,20010,20147,20283,20418,20553,20686,20819,20951,21083,21213,21343,21472,21600,21727,21854,21980,22104,22229,22352,22474,22596,22716,22836,22955,23073,23190,23307,23422,23537,23650,23763,23875,23986,24096,24205,24314,24421,24528,24633,24738,24841,24944,25046,25147,25247,25346,25444,25541,25637,25732,25826,25919,26011,26103,26193,26282,26370,26458,26544,26629,26713,26797,26879,26960,27040,27120,27198,27275,27351,27426,27500,27573,27645,27716,27786,27855,27923,27990,28056,28120,28184,28246,28308,28368,28428,28486,28543,28599,28654,28708,28761,28813,28864,28913,28962,29009,29056,29101,29145,29188,29230,29271,29311,29350,29387,29424,29459,29493,29526,29558,29589,29619,29648,29675,29702,29727,29751,29774,29796,29817,29837,29856,29873,29889,29905,29919,29932,29944,29954,29964,29972,29980,29986,29991,29995,29998,29999,30000,29999,29998,29995,29991,29986,29980,29972,29964,29954,29944,29932,29919,29905,29889,29873,29856,29837,29817,29796,29774,29751,29727,29702,29675,29648,29619,29589,29558,29526,29493,29459,29424,29387,29350,29311,29271,29230,29188,29145,29101,29056,29009,28962,28913,28864,28813,28761,28708,28654,28599,28543,28486,28428,28368,28308,28246,28184,28120,28056,27990,27923,27855,27786,27716,27645,27573,27500,27426,27351,27275,27198,27120,27040,26960,26879,26797,26713,26629,26544,26458,26370,26282,26193,26103,26011,25919,25826,25732,25637,25541,25444,25346,25247,25147,25046,24944,24841,24738,24633,24528,24421,24314,24205,24096,23986,23875,23763,23650,23537,23422,23307,23190,23073,22955,22836,22716,22596,22474,22352,22229,22104,21980,21854,21727,21600,21472,21343,21213,21083,20951,20819,20686,20553,20418,20283,20147,20010,19872,19734,19595,19455,19315,19174,19032,18889,18746,18602,18457,18311,18165,18018,17871,17723,17574,17424,17274,17123,16972,16820,16667,16514,16360,16205,16050,15894,15738,15581,15423,15265,15106,14947,14787,14627,14466,14304,14142,13979,13816,13653,13488,13324,13158,12993,12827,12660,12493,12325,12157,11989,11820,11650,11481,11310,11140,10968,10797,10625,10453,10280,10107,9933,9759,9585,9410,9235,9060,8885,8709,8532,8356,8179,8001,7824,7646,7468,7289,7111,6932,6753,6573,6393,6213,6033,5853,5672,5491,5310,5129,4947,4766,4584,4402,4220,4037,3855,3672,3490,3307,3124,2941,2757,2574,2390,2207,2023,1840,1656,1472,1288,1104,920,736,552,368,184,0,-184,-368,-552,-736,-920,-1104,-1288,-1472,-1656,-1840,-2023,-2207,-2390,-2574,-2757,-2941,-3124,-3307,-3490,-3672,-3855,-4037,-4220,-4402,-4584,-4766,-4947,-5129,-5310,-5491,-5672,-5853,-6033,-6213,-6393,-6573,-6753,-6932,-7111,-7289,-7468,-7646,-7824,-8001,-8179,-8356,-8532,-8709,-8885,-9060,-9235,-9410,-9585,-9759,-9933,-10107,-10280,-10453,-10625,-10797,-10968,-11140,-11310,-11481,-11650,-11820,-11989,-12157,-12325,-12493,-12660,-12827,-12993,-13158,-13324,-13488,-13653,-13816,-13979,-14142,-14304,-14466,-14627,-14787,-14947,-15106,-15265,-15423,-15581,-15738,-15894,-16050,-16205,-16360,-16514,-16667,-16820,-16972,-17123,-17274,-17424,-17574,-17723,-17871,-18018,-18165,-18311,-18457,-18602,-18746,-18889,-19032,-19174,-19315,-19455,-19595,-19734,-19872,-20010,-20147,-20283,-20418,-20553,-20686,-20819,-20951,-21083,-21213,-21343,-21472,-21600,-21727,-21854,-21980,-22104,-22229,-22352,-22474,-22596,-22716,-22836,-22955,-23073,-23190,-23307,-23422,-23537,-23650,-23763,-23875,-23986,-24096,-24205,-24314,-24421,-24528,-24633,-24738,-24841,-24944,-25046,-25147,-25247,-25346,-25444,-25541,-25637,-25732,-25826,-25919,-26011,-26103,-26193,-26282,-26370,-26458,-26544,-26629,-26713,-26797,-26879,-26960,-27040,-27120,-27198,-27275,-27351,-27426,-27500,-27573,-27645,-27716,-27786,-27855,-27923,-27990,-28056,-28120,-28184,-28246,-28308,-28368,-28428,-28486,-28543,-28599,-28654,-28708,-28761,-28813,-28864,-28913,-28962,-29009,-29056,-29101,-29145,-29188,-29230,-29271,-29311,-29350,-29387,-29424,-29459,-29493,-29526,-29558,-29589,-29619,-29648,-29675,-29702,-29727,-29751,-29774,-29796,-29817,-29837,-29856,-29873,-29889,-29905,-29919,-29932,-29944,-29954,-29964,-29972,-29980,-29986,-29991,-29995,-29998,-29999,-30000,-29999,-29998,-29995,-29991,-29986,-29980,-29972,-29964,-29954,-29944,-29932,-29919,-29905,-29889,-29873,-29856,-29837,-29817,-29796,-29774,-29751,-29727,-29702,-29675,-29648,-29619,-29589,-29558,-29526,-29493,-29459,-29424,-29387,-29350,-29311,-29271,-29230,-29188,-29145,-29101,-29056,-29009,-28962,-28913,-28864,-28813,-28761,-28708,-28654,-28599,-28543,-28486,-28428,-28368,-28308,-28246,-28184,-28120,-28056,-27990,-27923,-27855,-27786,-27716,-27645,-27573,-27500,-27426,-27351,-27275,-27198,-27120,-27040,-26960,-26879,-26797,-26713,-26629,-26544,-26458,-26370,-26282,-26193,-26103,-26011,-25919,-25826,-25732,-25637,-25541,-25444,-25346,-25247,-25147,-25046,-24944,-24841,-24738,-24633,-24528,-24421,-24314,-24205,-24096,-23986,-23875,-23763,-23650,-23537,-23422,-23307,-23190,-23073,-22955,-22836,-22716,-22596,-22474,-22352,-22229,-22104,-21980,-21854,-21727,-21600,-21472,-21343,-21213,-21083,-20951,-20819,-20686,-20553,-20418,-20283,-20147,-20010,-19872,-19734,-19595,-19455,-19315,-19174,-19032,-18889,-18746,-18602,-18457,-18311,-18165,-18018,-17871,-17723,-17574,-17424,-17274,-17123,-16972,-16820,-16667,-16514,-16360,-16205,-16050,-15894,-15738,-15581,-15423,-15265,-15106,-14947,-14787,-14627,-14466,-14304,-14142,-13979,-13816,-13653,-13488,-13324,-13158,-12993,-12827,-12660,-12493,-12325,-12157,-11989,-11820,-11650,-11481,-11310,-11140,-10968,-10797,-10625,-10453,-10280,-10107,-9933,-9759,-9585,-9410,-9235,-9060,-8885,-8709,-8532,-8356,-8179,-8001,-7824,-7646,-7468,-7289,-7111,-6932,-6753,-6573,-6393,-6213,-6033,-5853,-5672,-5491,-5310,-5129,-4947,-4766,-4584,-4402,-4220,-4037,-3855,-3672,-3490,-3307,-3124,-2941,-2757,-2574,-2390,-2207,-2023,-1840,-1656,-1472,-1288,-1104,-920,-736,-552,-368,-184
};

void BSP_Setfreq(float f)
{
	if(f>40000.0f)
		f = 40000.0f;
	if(f<20.0f)
		f = 20.0f;
	freq = f;
	Wave_tick1 = 85900 * f;
}

void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
	uint16_t i,tmp;
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
	for(i=1;i<=1024;i+=2)
	{
		tmp = Wave_sum1>>22;	//10bit
		Wave_sum1 += Wave_tick1;
		
		I2S_DACBuf[i] = SinWave[tmp];
		fifo[0][i>>1] = I2S_ADCBuf[i-1];
		fifo[1][i>>1] = I2S_ADCBuf[i];
		fifo[2][i>>1] = SinWave[tmp];
		fifo[3][i>>1] = SinWave[(tmp+768)&0x3ff];		//2^10=1024
	}
	
	DSP_I2S_Callback(fifo[0], fifo[1], fifo[2], fifo[3], 0);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
}

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
	uint16_t i,tmp;
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
	for(i=1024+1;i<=2048;i+=2)
	{
		tmp = Wave_sum1>>22;
		Wave_sum1 += Wave_tick1;
		
		I2S_DACBuf[i] = SinWave[tmp];
		fifo[0][i>>1] = I2S_ADCBuf[i-1];
		fifo[1][i>>1] = I2S_ADCBuf[i];
		fifo[2][i>>1] = SinWave[tmp];
		fifo[3][i>>1] = SinWave[(tmp+768)&0x3ff];		//2^10=1024
	}
	
	DSP_I2S_Callback(fifo[0], fifo[1], fifo[2], fifo[3], 512);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
}

const uint8_t CodecInit[][2] = 
{
	/* DAC Step */
	{0x00,0x00},	//Select Page 0
	{0x0b,0x81},	//NDAC = 1,Power up
	{0x0c,0x82},	//MDAC = 2,Power up
	{0x0d,0x00},	//DOSR = 128
	{0x0e,0x80},	//DOSR LSB
	//{0x3c,0x08},	//PRB_P8
	
	/* ADC Step */
	{0x12,0x81},	//NADC = 1,Power up
	{0x13,0x82},	//MADC = 2,Power up
	{0x14,0x80},	//AOSR = 128
	{0x3d,0x01},	//PRB_R1
	
	/* Audio Interface */
	{0x1b,0x00},	//16bit,PTM_P4
	
	/* Power Step */
	{0x00,0x01},	//Select Page 1
	{0x01,0x08},	//Disabled weak connection of AVDD with DVDD
	{0x02,0x01},	//Analog Block Power up,AVDD LDO Power up
	//{0x0a,0x3b},	//Input Vcom = 0.9v,Output Vcom = 1.65v
	{0x0a,0x03},
	
	{0x03,0x00},	//DAC PTM mode		to PTM_P3/4
	{0x04,0x00},
	{0x3d,0x00},	//ADC PTM mode		to PTM_R4
	
//	{0x7b,0x01},	//REF settime			to 40ms
//	{0x14,0x25},	//HP settime			to	
	
	/* Input Step */
	{0x34,0x20},	//Route IN2L to LEFT_P with 20k
	{0x36,0x20},	//Route IN2R to LEFT_M with 20k
	{0x37,0x80},	//Route IN1R to RIGHT_P with 20k
	{0x39,0x20},	//Route IN1L to RIGHT_M with 20k
	
	{0x3b,0x00},	//Left  MicPGA not mute,gain to 0dB
	{0x3c,0x00},	//Right MicPGA not mute,gain to 0dB
	
	/* Output Step */
	{0x0c,0x08},	//Route Left  DAC to HPL
	{0x0d,0x08},	//Route Right DAC to HPR
	{0x0e,0x08},	//Route Left  DAC to LOL
	{0x0f,0x08},	//Route Right DAC to LOR
	
	{0x10,0x00},	//HPL gain	to 0dB
	{0x11,0x00},	//HPR gain	to 0dB
	{0x12,0x08},	//LOL gain	to 0dB
	{0x13,0x08},	//LOR gain	to 0dB
	
	{0x16,0x75},
	{0x17,0x75},
	
	{0x09,0x3c},	//LOL,LOR,HPL,HPR,Power up
	
	/* Initial ok */
	{0x00,0x00},	//Select Page 0
	{0x3f,0xd6},	//L&R DAC Power up
	{0x40,0x00},	//L&R DAC not mute
	{0x51,0xc0},	//L&R ADC Power up
	{0x52,0x00},	//L&R ADC not mute
};

void BSP_CODEC_Init(void)
{
	uint16_t size = sizeof(CodecInit)/sizeof(CodecInit[0][0])/2;
	uint16_t i;

	/* TLV320AIC3204 reset */	
	for(i=0;i<size;i++)
			Single_WriteI2C(CodecInit[i][0],CodecInit[i][1]);
}

void BSP_CODEC_Start(void)
{
	hi2s3.Instance->I2SPR = 0x0205;
	BSP_Setfreq(1000.0);
	HAL_I2SEx_TransmitReceive_DMA(&hi2s3,(uint16_t *)&I2S_DACBuf,(uint16_t *)&I2S_ADCBuf,2048);
}

void Single_WriteI2C(uint8_t REG_Address,uint8_t REG_data)
{
    uint8_t txData[2] = {REG_Address,REG_data};
    while(HAL_I2C_Master_Transmit(&hi2c1,I2C_ADDRESS,txData,2,100) != HAL_OK)
    {
        if(HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
        {}
    }
}
uint8_t Single_ReadI2C(uint8_t REG_Address)
{
    uint8_t REG_data;
    while(HAL_I2C_Master_Transmit(&hi2c1,I2C_ADDRESS,&REG_Address,1,100) != HAL_OK)
    {
        if(HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
        {}
    }
    
    if(HAL_I2C_Master_Receive(&hi2c1,I2C_ADDRESS+1,&REG_data,1,100) != HAL_OK)
    {
        if(HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
        {}
    }
    return REG_data;
}
