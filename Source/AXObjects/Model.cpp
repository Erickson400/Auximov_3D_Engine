#include "Model.h"

namespace ax {
	Model::Model(std::string filename) { LoadModelFromFile(filename); }

	bool Model::LoadModelFromFile(std::string filename) {
		verts.clear();
		std::ifstream file(filename);
		if (!file.is_open()) return false;
		while (!file.eof()) {
			char line[128];
			file.getline(line, 128);
			std::strstream s;
			s << line;
			char junk;
			if (line[0] == 'v' && line[1] == ' ') {
				sf::Vector3f v;
				s >> junk >> v.x >> v.y >> v.z;
				verts.push_back(v);
			}
		}
		return true;
	}

}

