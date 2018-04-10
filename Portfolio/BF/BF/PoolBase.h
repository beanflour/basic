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

		virtual void Enter() = 0;
		virtual void Apply() = 0;
		virtual void Exit() = 0;

		int GetTag() const {return mn_Tag;}
	private:
		int mn_Tag;
	};

}