#include "Collision.h"

//bool Collision::checkCollision(Mesh& MeshA, Mesh& MeshB)
//{
//
//    float Ax;
//    float Bx;
//    float Ay;
//    float By;
//    float Az;
//    float Bz;
//
//    ///Get Values from Vec3 coordinates
//    for (auto A : MeshA.vertices)
//    {
//        Ax = A.position.x;
//        Ay = A.position.y;
//        Az = A.position.z;
//        return Ax, Ay, Az;
//    }
//
//    for (auto B : MeshA.vertices)
//    {
//        Bx = B.position.x;
//        By = B.position.y;
//        Bz = B.position.z;
//    }
//
//    bool colX = Ax + MeshA.vertices.size() >= Bx && Bx + MeshB.vertices.size() >= Ax;
//
//    bool colY = Ay + MeshA.vertices.size() >= By && By + MeshB.vertices.size() >= Ay;
//
//    bool colZ = Az + MeshA.vertices.size() >= Bz && Bz + MeshB.vertices.size() >= Az;
//
//    return colX, colY, colZ;
//}