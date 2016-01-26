//       ____  ____     ____                        _____             _            
// __  _|___ \|  _ \   / ___| __ _ _ __ ___   ___  | ____|_ __   __ _(_)_ __   ___ 
// \ \/ / __) | | | | | |  _ / _  |  _   _ \ / _ \ |  _| |  _ \ / _  | |  _ \ / _ \
//  >  < / __/| |_| | | |_| | (_| | | | | | |  __/ | |___| | | | (_| | | | | |  __/
// /_/\_\_____|____/   \____|\__ _|_| |_| |_|\___| |_____|_| |_|\__, |_|_| |_|\___|
//                                                              |___/     
//				Originally written by Marcus Loo Vergara (aka. Bitsauce)
//									2011-2015 (C)

#include <CGF/Common.h>
#include <CGF/Graphics/Texture.h>

BEGIN_CGF_NAMESPACE

ResourceManager::ResourceManager(const string &resourceFile)
{
	// Load resource file
	if(util::fileExists(resourceFile))
	{
		tinyxml2::XMLDocument doc;
		doc.LoadFile(resourceFile.c_str());

		// Get root node
		tinyxml2::XMLNode *resourceNode = doc.FirstChildElement();
		if(!resourceNode)
		{
			LOG("Invalid resource file");
			return;
		}

		// For each context
		resourceNode = resourceNode->FirstChildElement();
		while(resourceNode)
		{
			// For each resource entry
			tinyxml2::XMLElement *name = resourceNode->FirstChildElement("name");
			tinyxml2::XMLElement *path = resourceNode->FirstChildElement("path");

			// Get name and path
			if(name && path)
			{
				string type = resourceNode->Value();
				if(type == "texture")
				{
					tinyxml2::XMLElement *premul = resourceNode->FirstChildElement("premultiplyAlpha");
					m_resourceDesc[name->GetText()] =
						new TextureResourceDesc(
							path->GetText(),
							premul && string(premul->GetText()) == "true"
							);
				}
				else if(type == "font")
				{
					m_resourceDesc[name->GetText()] = new ResourceDesc(RESOURCE_TYPE_FONT, path->GetText());
				}
			}

			// Next resource
			resourceNode = resourceNode->NextSibling();
		}
	}
}

/*template<typename T>
Resource<T> ResourceManager::get(string name)
{
	// Check if resource is already loaded
	{
		map<string, void*>::iterator itr;
		if((itr = m_resources.find(name)) != m_resources.end())
		{
			return *(Resource<T>*)itr->second;
		}
	}

	// The resource is not loaded, check if we have a resource descriptor
	{
		map<string, ResourceDesc*>::iterator itr;
		if((itr = m_resourceDesc.find(name)) != m_resourceDesc.end())
		{
			Resource<T> resource = T::loadResource(itr->second);
			if(resource)
			{
				m_resources[name] = resource;
			}
		}
	}

	// Resource was not found
	LOG("Resource '%s' was not found", name.c_str());
	return 0;
}*/

END_CGF_NAMESPACE