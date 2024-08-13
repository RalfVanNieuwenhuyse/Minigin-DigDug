#pragma once
#include "Singleton.h"
#include <vector>
#include <functional>
#include <memory>
#include <unordered_map>
#include "Event.h"
#include <deque>

#include <iostream>

namespace dae
{
	class EventManager final : public Singleton<EventManager>
	{
	public:

		template <typename T>
		void SendEventMessage(std::shared_ptr<T> e);
		void AddObserver(const Event& e, const std::function<void(const Event* e)>& observer);
		void RemoveObserver(const Event& e, const std::function<void(const Event* e)>& observer);
		void HandleEvents();

	private:

		bool PollEvents(Event*& e);

		const static unsigned BUFFER_SIZE{ 20 };

		unsigned m_BufferSize{ 20 };

		std::vector<std::shared_ptr<Event>> m_Queue{ BUFFER_SIZE };

		unsigned m_BufferStart{};
		unsigned m_NrQueued{};

		std::unordered_map<Event, std::vector<std::function<void(const Event* e)>>> m_Observers{};
	};

	template<typename T>
	inline void EventManager::SendEventMessage(std::shared_ptr<T> e)
	{
		static_assert(std::is_base_of<Event, T>::value && "T must inherit from Event");

		if (m_NrQueued >= BUFFER_SIZE) {
			// Handle overflow: log an error, resize the buffer, or handle it appropriately
			std::cout << "Queue overflow detected!" << std::endl;
			m_BufferSize = m_BufferSize * 2;
			m_Queue.resize(m_BufferSize);
		}

		const unsigned currentIndex = (m_BufferStart + m_NrQueued) % BUFFER_SIZE;
		m_Queue[currentIndex] = std::move(e);

		++m_NrQueued;
	}
}

