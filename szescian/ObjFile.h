#pragma once
#include "Geom.h"
#include <fstream>
#include <sstream>
#include "Vec2.h"
using namespace std;

struct objFace
{
	int v1;
	int v2;
	int v3;
	int vt1;
	int vt2;
	int vt3;
	int vn1;
	int vn2;
	int vn3;

	objFace(int vv1,
		int vv2,
		int vv3,
		int vvt1,
		int vvt2,
		int vvt3,
		int vvn1,
		int vvn2,
		int vvn3)
	{
		v1 = vv2;
		v2 = vv2;
		v3 = vv3;
		vt1 = vvt1;
		vt2 = vvt2;
		vt3 = vvt3;
		vn1 = vvn1;
		vn2 = vvn2;
		vn3 = vvn3;
	}
};

class ObjFile : public Geom
{
public:
	ObjFile()
	{
		bool res = loadOBJ("cube.obj");
		this->Scale = Vec3::One() * 10;
	}

	bool loadOBJ(const char* path)
	{
		vector<Vec3> vertices;
		vector<Vec3> normals;
		vector<objFace> faces;

		ifstream in(path, ios::in);
		if (!in)
		{
			cerr << "Cannot open " << path << endl;
			exit(1);
		}
		string line;

		auto s1 = new Shape(Triangle, GREEN);
		while (getline(in, line))
		{
			if (line.substr(0, 2) == "v ")
			{
				istringstream s(line.substr(2));
				Vec3 v;
				s >> v.X;
				s >> v.Y;
				s >> v.Z;
				vertices.push_back(v);
			}
			if (line.substr(0, 3) == "vn ")
			{
				istringstream s(line.substr(3));
				Vec3 vn;
				s >> vn.X;
				s >> vn.Y;
				s >> vn.Z;
				normals.push_back(vn);
			}
			else if (line.substr(0, 2) == "f ")
			{
				istringstream s(line.substr(2));
				int vv[3], vt[3], vn[3];

				sscanf_s(s.str().c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d",
					&vv[0], &vt[0], &vn[0],
					&vv[1], &vt[1], &vn[1],
					&vv[2], &vt[2], &vn[2]);
				vv[0]--; vv[1]--; vv[2]--;
				vt[0]--; vt[1]--; vt[2]--;
				vn[0]--; vn[1]--; vn[2]--;

				faces.emplace_back(
					vv[0], vv[1], vv[2], 
					vt[0], vt[1], vt[2], 
					vn[0], vn[1], vn[2]);
			}
			else if (line[0] == '#')
			{
				/* ignoring this line */
			}
			else
			{
				/* ignoring this line */
			}
		}

		for (auto f : faces)
		{
			s1->AddPoint(vertices[f.v1], normals[f.vn1]);
			s1->AddPoint(vertices[f.v2], normals[f.vn2]);
			s1->AddPoint(vertices[f.v3], normals[f.vn3]);
		}
		this->Shapes.push_back(s1->WithScale(10));
	}

};