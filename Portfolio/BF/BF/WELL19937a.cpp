#include "stdafx.h"
#include "WELL19937a.h"
#include <time.h>

#define W 32
#define P 31
#define MASKU (0xffffffffU>>(W-P))
#define MASKL (~MASKU)
#define M1 70
#define M2 179
#define M3 449

#define MAT0POS(t,v) (v^(v>>t))
#define MAT0NEG(t,v) (v^(v<<(-(t))))
#define MAT1(v) v
#define MAT3POS(t,v) (v>>t)

/* To obtain the WELL19937c, uncomment the following line */
/* #define TEMPERING                                      */
#define TEMPERB 0xe46e1700U
#define TEMPERC 0x9b868000U

#define V0            STATE[state_i]
#define VM1Over       STATE[state_i+M1-R]
#define VM1           STATE[state_i+M1]
#define VM2Over       STATE[state_i+M2-R]
#define VM2           STATE[state_i+M2]
#define VM3Over       STATE[state_i+M3-R]
#define VM3           STATE[state_i+M3]
#define VRm1          STATE[state_i-1]
#define VRm1Under     STATE[state_i+R-1]
#define VRm2          STATE[state_i-2]
#define VRm2Under     STATE[state_i+R-2]

#define newV0         STATE[state_i-1]
#define newV0Under    STATE[state_i-1+R]
#define newV1         STATE[state_i]
#define newVRm1       STATE[state_i-2]
#define newVRm1Under  STATE[state_i-2+R]

#define FACT 2.32830643653869628906e-10

static unsigned int y;

namespace BF
{
	//int WELLRand::state_i = 0;
	WELLRand *WELLRand::mp_this = nullptr;

	double WELLRand::CallFunc()
	{
		return (this->*mf_Well)();
	}

	WELLRand::WELLRand()
		:	state_i(0)
	{
		unsigned int nArr[R] = { 0 };
		for(unsigned int &nVal : nArr)
		{
			static unsigned int s = static_cast<unsigned int>(time(NULL));
			nVal = s;
			s += s + 100;
		}
		InitWELLRNG19937a(nArr);
	}

	WELLRand::~WELLRand()
	{
		if(mp_this)
			delete mp_this;
	}
	int WELLRand::IntRand(int const &_max, int const & _min /*= 0*/)
	{
		return (int)((double)CallFunc() * (_max - _min + 1)) + _min;
	}
	double WELLRand::DoubleRand(double const & _max, double const & _min)
	{
		return ((double)CallFunc() * (_max - _min + 1)) + _min;
	}
	void WELLRand::InitWELLRNG19937a(unsigned int *init)
	{
		state_i = 0;
		mf_Well = &WELLRand::case_1;
		for (int j = 0; j < R; j++)
			STATE[j] = init[j];
	}
	double WELLRand::case_1(void)
	{
		// state_i == 0
		z0 = (VRm1Under & MASKL) | (VRm2Under & MASKU);
		z1 = MAT0NEG(-25, V0) ^ MAT0POS(27, VM1);
		z2 = MAT3POS(9, VM2) ^ MAT0POS(1, VM3);
		newV1 = z1 ^ z2;
		newV0Under = MAT1(z0) ^ MAT0NEG(-9, z1) ^ MAT0NEG(-21, z2) ^ MAT0POS(21, newV1);
		state_i = R - 1;
		mf_Well = &WELLRand::case_3;
#ifdef TEMPERING
		y = STATE[state_i] ^ ((STATE[state_i] << 7) & TEMPERB);
		y = y ^ ((y << 15) & TEMPERC);
		return ((double)y * FACT);
#else
		return ((double)STATE[state_i] * FACT);
#endif
	}
	double WELLRand::case_2(void)
	{
		// state_i == 1
		z0 = (VRm1 & MASKL) | (VRm2Under & MASKU);
		z1 = MAT0NEG(-25, V0) ^ MAT0POS(27, VM1);
		z2 = MAT3POS(9, VM2) ^ MAT0POS(1, VM3);
		newV1 = z1 ^ z2;
		newV0 = MAT1(z0) ^ MAT0NEG(-9, z1) ^ MAT0NEG(-21, z2) ^ MAT0POS(21, newV1);
		state_i = 0;
		mf_Well = &WELLRand::case_1;
#ifdef TEMPERING
		y = STATE[state_i] ^ ((STATE[state_i] << 7) & TEMPERB);
		y = y ^ ((y << 15) & TEMPERC);
		return ((double)y * FACT);
#else
		return ((double)STATE[state_i] * FACT);
#endif
	}
	double WELLRand::case_3(void)
	{
		// state_i+M1 >= R
		z0 = (VRm1 & MASKL) | (VRm2 & MASKU);
		z1 = MAT0NEG(-25, V0) ^ MAT0POS(27, VM1Over);
		z2 = MAT3POS(9, VM2Over) ^ MAT0POS(1, VM3Over);
		newV1 = z1 ^ z2;
		newV0 = MAT1(z0) ^ MAT0NEG(-9, z1) ^ MAT0NEG(-21, z2) ^ MAT0POS(21, newV1);
		state_i--;
		if (state_i + M1 < R)
			mf_Well = &WELLRand::case_5;
#ifdef TEMPERING
		y = STATE[state_i] ^ ((STATE[state_i] << 7) & TEMPERB);
		y = y ^ ((y << 15) & TEMPERC);
		return ((double)y * FACT);
#else
		return ((double)STATE[state_i] * FACT);
#endif
	}
	double WELLRand::case_4(void)
	{
		// state_i+M3 >= R
		z0 = (VRm1 & MASKL) | (VRm2 & MASKU);
		z1 = MAT0NEG(-25, V0) ^ MAT0POS(27, VM1);
		z2 = MAT3POS(9, VM2) ^ MAT0POS(1, VM3Over);
		newV1 = z1 ^ z2;
		newV0 = MAT1(z0) ^ MAT0NEG(-9, z1) ^ MAT0NEG(-21, z2) ^ MAT0POS(21, newV1);
		state_i--;
		if (state_i + M3 < R)
			mf_Well = &WELLRand::case_6;
#ifdef TEMPERING
		y = STATE[state_i] ^ ((STATE[state_i] << 7) & TEMPERB);
		y = y ^ ((y << 15) & TEMPERC);
		return ((double)y * FACT);
#else
		return ((double)STATE[state_i] * FACT);
#endif
	}
	double WELLRand::case_5(void)
	{
		// state_i+M2 >= R
		z0 = (VRm1 & MASKL) | (VRm2 & MASKU);
		z1 = MAT0NEG(-25, V0) ^ MAT0POS(27, VM1);
		z2 = MAT3POS(9, VM2Over) ^ MAT0POS(1, VM3Over);
		newV1 = z1 ^ z2;
		newV0 = MAT1(z0) ^ MAT0NEG(-9, z1) ^ MAT0NEG(-21, z2) ^ MAT0POS(21, newV1);
		state_i--;
		if (state_i + M2 < R)
			mf_Well = &WELLRand::case_4;
#ifdef TEMPERING
		y = STATE[state_i] ^ ((STATE[state_i] << 7) & TEMPERB);
		y = y ^ ((y << 15) & TEMPERC);
		return ((double)y * FACT);
#else
		return ((double)STATE[state_i] * FACT);
#endif
	}
	double WELLRand::case_6(void)
	{
		// 2 <= state_i <= (R - M3 - 1)
		z0 = (VRm1 & MASKL) | (VRm2 & MASKU);
		z1 = MAT0NEG(-25, V0) ^ MAT0POS(27, VM1);
		z2 = MAT3POS(9, VM2) ^ MAT0POS(1, VM3);
		newV1 = z1 ^ z2;
		newV0 = MAT1(z0) ^ MAT0NEG(-9, z1) ^ MAT0NEG(-21, z2) ^ MAT0POS(21, newV1);
		state_i--;
		if (state_i == 1)
			mf_Well = &WELLRand::case_2;
#ifdef TEMPERING
		y = STATE[state_i] ^ ((STATE[state_i] << 7) & TEMPERB);
		y = y ^ ((y << 15) & TEMPERC);
		return ((double)y * FACT);
#else
		return ((double)STATE[state_i] * FACT);
#endif
	}
}