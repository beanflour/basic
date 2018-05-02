#pragma once

/* ***************************************************************************** */
/* Copyright:      Francois Panneton and Pierre L'Ecuyer, University of Montreal */
/*                 Makoto Matsumoto, Hiroshima University                        */
/* Notice:         This code can be used freely for personal, academic,          */
/*                 or non-commercial purposes. For commercial purposes,          */
/*                 please contact P. L'Ecuyer at: lecuyer@iro.UMontreal.ca       */
/* ***************************************************************************** */

namespace BF
{
#define R 624

	class WELLRand
	{
	public:
		typedef double(WELLRand::*WELLRNG19937a) (void);

		~WELLRand();
		static WELLRand& getInstance()
		{
			if(nullptr == mp_this)
			{
				mp_this = new WELLRand;
			}
			return *mp_this;
		}

		int IntRand(int const &_max, int const &_min = 0);
	private:
		WELLRand();
		
		double CallFunc();

		void InitWELLRNG19937a(unsigned int *init);
		double case_1(void);
		double case_2(void);
		double case_3(void);
		double case_4(void);
		double case_5(void);
		double case_6(void);

		WELLRNG19937a mf_Well;

		int state_i;
		unsigned int STATE[R];
		unsigned int z0, z1, z2;
		static WELLRand *mp_this;
	};
}

/*
	WELL19937a를 사용한 랜덤 클래스.
	BF_RAND.IntRand(int max, int min)으로 사용 가능하다. 
	max는 받고자하는 최대값, min은 최저값이다.
*/
#define BF_RAND BF::WELLRand::getInstance()