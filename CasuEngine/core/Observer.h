#pragma once
#include <vector>
#include <string>

template <typename T>
class Observer {
public:
	virtual void OnNotify(const T& subject) = 0;
	virtual ~Observer() = default;
};

template <typename T>
class Subject
{
public:  
	void AddObserver(Observer<T>* observer)
	{
		m_observers.push_back(observer);
	}

	void RemoveObserver(Observer<T>* observer)
	{
		m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
	}

protected:
    void Notify(T& data)
    {
		for (auto* observer : m_observers)
		{
			observer->OnNotify(data);
		}
    }

private:
    std::vector<Observer<T>*> m_observers;
};