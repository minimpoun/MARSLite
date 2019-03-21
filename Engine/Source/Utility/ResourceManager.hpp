#pragma once

#include "Common.h"

#include "NoCopy.h"
#include "NoMove.h"

template <typename T>
class ResourceManager
{
public:

	ResourceManager(const String& Folder, const String& InFileType)
	: EngineResFolder("/home/chris-desktop/Projects/MARS-Lite/Resources/" + Folder + "/")
	, ResFolder("../Game/Resource/" + Folder + "/")
	, FileType(InFileType.front() == '.' ? InFileType : "." + InFileType)
	{}
	
	T& operator[](const String& Name)
	{
		if (!DoesResourceExist(Name))
		{
			Create(Name);
		}
		
		return LoadedResources.at(Name);
	}
	
	const T& Get(const String& Name) const
	{
		if (!DoesResourceExist(Name))
		{
			Create(Name);
		}
		
		return LoadedResources.at(Name);
	}
	
	bool DoesResourceExist(const String& Name) const
	{
		return LoadedResources.find(Name) != LoadedResources.end();
	}
	
	void Create(const String& Name)
	{
		T _T;
		if (!_T.loadFromFile(GetFilename(Name)))
		{
			T _F;
			_F.loadFromFile(EngineResFolder + "Error" + FileType);
			LoadedResources.insert(std::make_pair(Name, _F));
		}
		else
		{
			LoadedResources.insert(std::make_pair(Name, _T));
		}
	}

private:
	
	String GetFilename(const String& Name)
	{
		return EngineResFolder + Name + FileType;
	}
	
	const String EngineResFolder;
	const String ResFolder;
	const String FileType;
	std::unordered_map<String, T> LoadedResources;
};