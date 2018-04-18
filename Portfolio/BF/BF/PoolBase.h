#pragma once

namespace BF
{
	class CPoolBase
	{
	public:
		CPoolBase(int _n_Tag = 0)
			:	mn_Tag(_n_Tag)
		{};
		virtual ~CPoolBase() {};

		virtual bool Enter(LPVOID _p = nullptr) = 0;	//	매개변수로 관련 데이터를 받아올 수 있음.
		virtual void Apply(LPVOID _p = nullptr) = 0;
		virtual void Exit() = 0;

		void setTag(int const &_Tag)
		{
			mn_Tag = _Tag;
		}
		int GetTag() const {return mn_Tag;}
	private:
		int mn_Tag;
	};

}