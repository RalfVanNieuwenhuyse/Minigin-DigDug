#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "Collision.h"

#include <algorithm>

#include <execution>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	//https://stackoverflow.com/questions/59458264/exception-thrown-read-access-violation-it-was-0xffffffffffffffff
	m_pendingObjects.emplace_back(std::move(object));
	m_WasGameObjectAdded = true;
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
{
	ReorderGameobjects();

	for(auto& object : m_objects)
	{
		if (!object->IsDestroyed())
		{
			object->Update();
		}
	}

	m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(), [&](std::shared_ptr<GameObject>& object)
		{
			return object->IsDestroyed();
		}
	), m_objects.end());

	if (!m_pendingObjects.empty())
	{
		m_objects.insert(m_objects.end(), std::make_move_iterator(m_pendingObjects.begin()), std::make_move_iterator(m_pendingObjects.end()));
		m_pendingObjects.clear();
		m_WasGameObjectAdded = true;
	}
}

void dae::Scene::ReorderGameobjects()
{
	if (!m_WasGameObjectAdded) return;

	std::sort(std::execution::par_unseq, m_objects.begin(), m_objects.end(),
		[](const std::shared_ptr<GameObject>& pObject1, const std::shared_ptr<GameObject>& pObject2)
		{
			auto object1z = pObject1->GetTransform().get()->GetPosition().z;
			auto object2z = pObject2->GetTransform().get()->GetPosition().z;

			return object1z < object2z;
		}
	);

	m_WasGameObjectAdded = false;
}

void dae::Scene::FixedUpdate()
{
	for (auto& object : m_objects)
	{
		if (!object->IsDestroyed())
		{
			object->FixedUpdate();
		}
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void dae::Scene::RenderImGui() const
{
	for (const auto& object : m_objects)
	{
		object->RenderImGui();
	}
}

void dae::Scene::AddCollision(Collision* collision)
{
	m_Collisions.emplace_back(collision);
}

void dae::Scene::RemoveCollision(Collision* collision)
{
	m_Collisions.erase(std::remove(m_Collisions.begin(), m_Collisions.end(), collision));
}

