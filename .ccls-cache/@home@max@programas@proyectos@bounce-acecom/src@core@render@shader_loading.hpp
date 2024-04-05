#include <vector>

#include "../../utilities/render/shader_s.hpp"
#include "../../utilities/extra/singleton.hpp"

class ShaderLoader : public Singleton<ShaderLoader> {

private:
	std::vector<Shader> Shaders;

public:

	ShaderLoader(){
		Shaders = std::vector<Shader>(); 
	}

	void LoadShader(const char* vertexPath, const char* fragmentPath){
		Shader newShader = Shader(vertexPath, fragmentPath);

		Shaders.insert(Shaders.end(), newShader);
	}

	Shader GetShader(int index){
		return  Shaders.at(index);
	}
};

