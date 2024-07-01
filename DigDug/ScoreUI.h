#pragma once
#include "Component.h"
#include "Event.h"

namespace dae
{
	class Text;

    class ScoreUI : public Component
    {
	public:
		ScoreUI(GameObject* owner);
		~ScoreUI() = default;
		ScoreUI(const ScoreUI& other) = delete;
		ScoreUI(ScoreUI&& other) = delete;
		ScoreUI& operator=(const ScoreUI& other) = delete;
		ScoreUI& operator=(ScoreUI&& other) = delete;

		void SetObjectToCheck(GameObject* object) { m_Object = object; };

	private:
		void UpdateScore(const dae::Event* e);

		std::shared_ptr<Text> m_Text;
		GameObject* m_Object{ nullptr };
    };
}