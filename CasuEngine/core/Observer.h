#pragma once
#include <vector>
#include <string>

class EventInfo
{
public:
	EventInfo(std::string name = "NONE") : m_name(name) {}
	std::string GetName() const { return m_name; }

private:
	std::string m_name;
};



class Observer
{
public:
	virtual ~Observer() {}
	virtual void OnNotify(const Subject& entity) = 0;

private:

};


class Subject
{
public:  
	void addObserver(Observer* observer)
	{
		m_observers.push_back(observer);
	}

	void removeObserver(Observer* observer)
	{
		m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
	}

protected:
    void Notify(const Observer& entity, EventInfo event)
    {
		for (auto observer : m_observers)
		{
			observer->OnNotify(*this);
		}
    }

private:
    std::vector<Observer*> m_observers;
};