#pragma once

namespace BF
{
	/*
		상속으로 사용가능한 singleton.
		Ex > class name : public BF::CTemplateSingleton< name > 으로 사용가능하다.
		상속만 하면 singleton이 됨(1개짜리)
	*/
	template<typename T>
	class CTemplateSingleton
	{
	public:
		virtual ~CTemplateSingleton()
		{
		}

		static T * GetInstance()
		{
			if(nullptr == mp_Instance)
				mp_Instance = new T;
			return mp_Instance;
		}
		static void DestroyInstance()
		{
			if(mp_Instance)
			{
				delete mp_Instance;
				mp_Instance = nullptr;
			}
		}
	protected:
		CTemplateSingleton()
		{
		}
		CTemplateSingleton(CTemplateSingleton const &_Copy)
		{
		}
	private:
		static T * mp_Instance;
	};

	template <typename T>
	T* CTemplateSingleton::mp_Instance = nullptr;
}