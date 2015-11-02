#define FILTER_IMP_VER 1 // 0: v0 = given implementation
                         // 1: v1 = more efficient implementation
#define POWER_CALC_VER 0 // 0: v0 = method used by TI implementation
                         // works with notebook speaker output level at about 15% and line-in to DSP-Kit
                         // 1: v1 = method described in DSVB script
						 // works with notebook speaker output level at about 25% and line-in to DSP-Kit

#define SAMPLES_PER_SECOND 8000L
#define GAIN_IN_dB         36

#define GOERTZEL_THRESHOLD 0x100 + (POWER_CALC_VER*256)

