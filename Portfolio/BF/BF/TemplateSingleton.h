#pragma once

namespace BF
{
	/*
		������� ��밡���� singleton.
		Ex > class name : public BF::CTemplateSingleton< name > ���� ��밡���ϴ�.
		��Ӹ� �ϸ� singleton�� ��(1��¥��)
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