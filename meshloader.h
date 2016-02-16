#ifndef MESHLOADER
#define MESHLOADER

#include "tiny_obj_loader.h"
#include "mesh.h"
#include <qopengl.h>
#include <QVector>

#include <iostream>

class MeshLoader {

public:
    static Mesh *load(QString fpath) {
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;

        std::string err;
        bool ret = tinyobj::LoadObj(shapes, materials, err, fpath.toStdString().c_str());

        if (!err.empty()) { // `err` may contain warning message.
          std::cerr << err << std::endl;
        }

        tinyobj::shape_t shape = shapes[0];
        std::cout << "Loading: " << shape.name << std::endl;

        tinyobj::mesh_t mesh = shape.mesh;

        QVector<MeshVertex> data(mesh.indices.size());

        QVector4D defaultColor(0.49f, 0.85f, 1, 1);

        int count = 0;
        foreach(unsigned int idx, mesh.indices) {
            MeshVertex& p = data[count++];

            if(mesh.positions.size() != 0) {
                p.position.setX(mesh.positions[3*idx+0]);
                p.position.setY(mesh.positions[3*idx+1]);
                p.position.setZ(mesh.positions[3*idx+2]);
            }

            if(mesh.normals.size() != 0) {
                p.normal.setX(mesh.normals[3*idx+0]);
                p.normal.setY(mesh.normals[3*idx+1]);
                p.normal.setZ(mesh.normals[3*idx+2]);
            }

            if(mesh.texcoords.size() != 0) {
                p.texcoord.setX(mesh.texcoords[2*idx+0]);
                p.texcoord.setY(mesh.texcoords[2*idx+1]);
            }

            p.color = defaultColor;
        }

        std::cout << mesh.indices.size() << " " << data.size() << std::endl;

        return new Mesh(data);
    }

};

#endif // MESHLOADER

