#include "Engine.h"

#include "generic/Entity.h"

#include "Application.h"
#include "generic/Component.h"
#include "component/DataComponent.h"
#include "layer/Layer.h"

#include "event/Input.h"
#include "event/KeyCodes.h"

#include "imgui/ImGuiLayer.h"
#include "utils/Core.h"


namespace engine {

	Entity::Entity(std::string name, const Shr<Scene>& scene)
		: scene(scene)
	{
        AddComponent<DataComponent>(name);
	}

	Entity::Entity(uuid id, std::string name, const Shr<Scene>& scene)
		: scene(scene)
	{
        AddComponent<DataComponent>(id, name);
	}

	Entity::~Entity() { }

    Entity* Entity::AddTag(std::string tag)
    {
        auto& tagList = GetComponent<DataComponent>().tags;
        std::transform(tag.begin(), tag.end(), tag.begin(), ::toupper);
        if (std::find(tagList.begin(), tagList.end(), tag) != tagList.end())
        {
            LOG_CORE_WARN("Adding a tag to a Entity which it already has: '" + tag + "'");
            return this;
        }
        tagList.emplace_back(tag);
        return this;
    }

    Entity* Entity::AddTag(std::initializer_list<std::string> tags)
    {
        for (std::string tag : tags) {
            std::transform(tag.begin(), tag.end(), tag.begin(), ::toupper);
            AddTag(tag);
        }
        return this;
    }

    bool Entity::RemoveTag(std::string tag)
    {
        auto& tagList = GetComponent<DataComponent>().tags;
        std::transform(tag.begin(), tag.end(), tag.begin(), ::toupper);
        std::vector<std::string>::iterator it = std::find(tagList.begin(), tagList.end(), tag);
        if (it == tagList.end())
        {
            LOG_CORE_WARN("Removing a tag from a Entity which it doesn't have: '" + tag + "'");
            return false;
        }
        tagList.erase(it);
        return true;
    }

    bool Entity::HasTag(std::string tag)
    {
        auto& tagList = GetComponent<DataComponent>().tags;
        std::transform(tag.begin(), tag.end(), tag.begin(), ::toupper);
        std::vector<std::string>::iterator it = std::find(tagList.begin(), tagList.end(), tag);
        return it != tagList.end();
    }


	void Entity::Imgui(float dt) {
		ImGui::Text("Transform:");
        float speed = 0.5f;
        if (Input::IsKeyPressed(KEY_LEFT_SHIFT) && Input::IsKeyPressed(KEY_LEFT_CONTROL))
            speed = 0.001f;
        else if (Input::IsKeyPressed(KEY_LEFT_SHIFT))
            speed = 0.01f;
        
		ImGui::DragFloat(std::string("X:").c_str(), &this->transform.position.x, speed);
		ImGui::DragFloat(std::string("Y:").c_str(), &this->transform.position.y, speed);
		ImGui::DragFloat(std::string("Z:").c_str(), &this->transform.position.z, speed);
		ImGui::DragFloat(std::string("Scale X:").c_str(), &this->transform.scale.x, speed);
		ImGui::DragFloat(std::string("Scale Y:").c_str(), &this->transform.scale.y, speed);
		ImGui::DragFloat(std::string("Scale Z:").c_str(), &this->transform.scale.z, speed);
        float rot[]{ this->transform.rotation.x, this->transform.rotation.y, this->transform.rotation.z };
        ImGui::DragFloat3(std::string("Rotation:").c_str(), rot, speed);
        this->transform.rotation = glm::vec3(rot[0], rot[1], rot[2]);
        

		for (auto component : components) {
		    component->OnImgui(dt);
		}
    }

    

    

}