#include "./header/ObjMap.hpp"

#include <cmath>
#define PI 3.141519

float* returnProjMatrix(int xSizeScrean, int ySizeScrean, float FOV, float zNear, float zFar){
    float aspectRatio = (float)xSizeScrean / (float)ySizeScrean;
    float fovRad = 1.0f / tanf(FOV * 0.5f / 180.0f * PI);
    float zRange = zNear - zFar;

    float* projMatrix = (float*)malloc(4 * 4 * sizeof(float));
    projMatrix[0]  = fovRad / aspectRatio; projMatrix[1]  = 0;                    projMatrix[2]  = 0;                            projMatrix[3] = 0;
    projMatrix[4]  = 0;                    projMatrix[5]  = 1 / aspectRatio;      projMatrix[6]  = 0;                            projMatrix[7] = 0;
    projMatrix[8]  = 0;                    projMatrix[9]  = 0;                    projMatrix[10] = (zFar + zNear) / zRange;      projMatrix[11] = (2 * zFar * zNear) / zRange;
    projMatrix[12] = 0;                    projMatrix[13] = 0;                    projMatrix[14] = -1;                           projMatrix[15] = 0;

    return projMatrix;
}

ObjMap::ObjMap(int xScreenSize, int yScreenSize, float FOV, float zNear, float zFar){
    this->xScreenSize = xScreenSize;
    this->yScreenSize = yScreenSize;
    this->FOV = FOV;
    this->zNear = zNear;
    this->projMatrix = returnProjMatrix(xScreenSize, yScreenSize, FOV, zNear, zFar);
}

ObjMap::~ObjMap(){
    if (this->projMatrix != NULL){
        delete[] this->projMatrix;
        this->projMatrix = NULL;
    }
    for (std::map<const char*, ReadObj>::iterator item = objs.begin(); item !=objs.end(); ++item){
        (*item).second.~ReadObj();
        objs.erase(item);
    }
}


void ObjMap::openObj(const char* path){

    
}
