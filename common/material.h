#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <ogles.h>
#include <program.h>
#include <texture.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>

namespace es
{
	class Material
	{
		struct PairHash
		{
			template<typename T1, typename T2>
			std::size_t operator() (const std::pair<T1, T2>& p) const
			{
				auto h1 = std::hash<T1>{}(p.first);
				auto h2 = std::hash<T2>{}(p.second);
				return h1 ^ h2;
			}
		};
	public:
		Material(const std::string& name, const std::vector<std::string>& shaderFiles, const std::unordered_map<std::string, std::string>& textureFiles);
		~Material();

		static std::shared_ptr<Material> createFromFiles(const std::string& name, const std::vector<std::string>& shaderFiles, const std::unordered_map<std::string, std::string>& textureFiles);

		void apply();
		void unapply();
	private:
		static std::unordered_map<std::string, std::shared_ptr<Material>> mMaterialCache;
	
		std::string mName;

		std::unique_ptr<Program> mProgram;
		std::unordered_map<std::pair<std::string, GLuint>, std::shared_ptr<Texture2D>, PairHash> mTextureMap;
	};
}

#endif