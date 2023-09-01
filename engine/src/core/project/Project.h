#pragma once
#include "Engine.h"

#include "yaml-cpp/node/node.h"

namespace Paper
{

	struct ProjectConfig
	{
		std::string projectName = "New Project";
		std::filesystem::path projectPath;
		std::filesystem::path assetPath = "assets";
		std::filesystem::path scriptBinaryPath = "assets/scripts/bin";
	};

	class Project
	{
	public:
		Project() = default;
		Project(const ProjectConfig& config);
		~Project() = default;

		const ProjectConfig& GetConfig() const;

		static void SetActive(const Shr<Project>& project);
		static Shr<Project> GetActive();

		static std::string GetProjectName()
		{
			CORE_ASSERT(activeProject, "");
			return activeProject->GetConfig().projectName;
		}

		static std::filesystem::path GetProjectPath()
		{
			CORE_ASSERT(activeProject, "");
			return activeProject->GetConfig().projectPath;
		}

		static std::filesystem::path GetAssetPath()
		{
			CORE_ASSERT(activeProject, "");
			return activeProject->GetConfig().projectPath / activeProject->GetConfig().assetPath;
		}

		static std::filesystem::path GetScriptBinaryPath()
		{
			CORE_ASSERT(activeProject, "");
			return activeProject->GetConfig().projectPath / activeProject->GetConfig().scriptBinaryPath;
		}

		static std::filesystem::path GetScriptBinaryFilePath()
		{
			CORE_ASSERT(activeProject, "");
			return GetScriptBinaryPath() / std::format("{}.dll", GetProjectName());
		}

	private:
		ProjectConfig config;

		static inline Shr<Project> activeProject = nullptr;

		friend class ProjectSerializer;
	};
}

