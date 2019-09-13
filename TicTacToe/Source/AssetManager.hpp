#pragma once
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

namespace TTT {
	class AssetManager {
	public:
		AssetManager() {}
		~AssetManager() {}
		
		void LoadTexture(string name, string fileName);
		Texture &GetTexture(string name);
		
		void LoadFont(string name, string fileName);
		Font &GetFont(string name);
		
	private:
		map<string, Texture> _textures;
		map<string, Font> _fonts;
	};
}
