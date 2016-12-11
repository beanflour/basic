#pragma once

//////////////////////////////////////////////////////////////////////////
//	for �������� ���Ǵ� �Լ�. ex> for( int i : range(0, 4) printf("%d\n", i); ��.
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
		range�� stl�� ����Ҷ� �߰��� iterator�� �����ϴ����� ����� ��.
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