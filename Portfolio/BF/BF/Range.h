#pragma once

//////////////////////////////////////////////////////////////////////////
//	for 루프에서 사용되는 함수. ex> for( int i : range(0, 4) printf("%d\n", i); 등.
//////////////////////////////////////////////////////////////////////////
namespace BF
{
	template<typename T>
	class range_iterator
	{
		T cur_;

	public:
		range_iterator(T init) : cur_(init){}

		range_iterator& operator++()
		{
			cur_ = ++cur_;
			return *this;
		}

		bool operator!=(range_iterator<T> const &rhs) const { return cur_ != rhs.cur_;}

		T operator*() const {return cur_;}

	};

	template<typename T>
	class CRange;


	/*
		range에 stl을 사용할땐 중간에 iterator를 변경하는일이 없어야 함.
	*/
	template<typename T>
	CRange<T> range(T const _start, T const _stop) {return CRange<T>(_start, _stop); }
	


	template<typename T>
	class CRange
	{
		T const start;
		T const stop;
		//public:
	private:
		CRange(T _start, T _stop) : start(_start), stop(_stop){}
	public:
		range_iterator<T> begin() const 
		{
			return range_iterator<T>(start);
		}
		range_iterator<T> end() const 
		{
			return range_iterator<T>(stop);
		}

		friend CRange<T> range<T>(T const _start, T const _stop);
	};
}