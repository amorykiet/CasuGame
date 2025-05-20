#pragma once
#include <vector>
#include <string>
#include <algorithm>

template <typename T>
class Subject;

template <typename T>
class Observer {
public:
	virtual ~Observer() = default;
	
private:
	friend class Subject<T>;
};

template <typename T>
class Subject
{
public:
	Subject();
	virtual ~Subject() = default;

public:
	void AddObserver(T* observer);
	void RemoveObserver(T* observer);

protected:
	void CleanUp();

	void StartNotifying();
	void EndNotifying();

protected:
	mutable std::vector<T*> m_observers;

private:
	mutable bool m_isPendingRemove;
	mutable bool m_isNotifying;
};

template<typename T>
inline Subject<T>::Subject()
	: m_isPendingRemove(false), m_isNotifying(false)
{
}

template<typename T>
inline void Subject<T>::AddObserver(T* observer)
{
	typename std::vector<T*>::iterator it = std::find(m_observers.begin(), m_observers.end(), observer);
	if (it == m_observers.end())
	{
		m_observers.push_back(observer);
	}
}

template<typename T>
inline void Subject<T>::RemoveObserver(T* observer)
{
	typename std::vector<T*>::iterator it = std::find(m_observers.begin(), m_observers.end(), observer);
	if (it != m_observers.end())
	{
		if (m_isNotifying)
		{
			(*it) = 0;
			m_isPendingRemove = true;
		}
		else
		{
			m_observers.erase(it);
		}
	}
}

template<typename T>
inline void Subject<T>::CleanUp()
{
	if (m_isPendingRemove)
	{
		typename std::vector<T*>::iterator it = m_observers.begin();
		while (it != m_observers.end())
		{
			if ((*it) == 0)
			{
				it = (m_observers).erase(it);
			}
			else
			{
				++it;
			}
		}
		m_isPendingRemove = false;
	}
}

template<typename T>
inline void Subject<T>::StartNotifying()
{
	m_isNotifying = true;
}

template<typename T>
inline void Subject<T>::EndNotifying()
{
	m_isNotifying = false;
	CleanUp();
}

#define NOTIFY_OBSERVERS(Observer, ObserverMethod) \
{ \
	Subject<Observer>::StartNotifying(); \
	for (std::size_t i = 0, sz = (Subject<Observer>::m_observers).size(); i < sz; ++i) \
	{ \
		Observer* observer = (Subject<Observer>::m_observers)[i]; \
		if (observer) \
		{ \
			observer->ObserverMethod; \
		} \
	} \
	Subject<Observer>::EndNotifying(); \
}