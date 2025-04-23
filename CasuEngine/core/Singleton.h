#pragma once


template<typename T>
class Singleton
{
public:

	~Singleton()
	{
		DestroyInstance();
	}

	static T* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new T();
		}
		return instance;
	}

	static void DestroyInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}
protected:
	static T* instance; // Pointer to the singleton instance
};

// Definition of the static member
template<typename T>
T* Singleton<T>::instance = nullptr;
