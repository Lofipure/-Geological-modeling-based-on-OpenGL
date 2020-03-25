#ifndef OBJECT_H
#define OBJECT_H

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <vector>
#include <cstdio>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object
{
/*
    �൱��һ���ز���

    �����������Vertex Array Object��VAO
    ���㻺�����Vertex Buffer Object��VBO
    �����������Element Buffer Object��EBO ��Index Buffer Object��IBO
*/
public:
    // vn == vertices number
    // in == indices number
    int vn, in;

    float *vertices;                //��Ŷ������ݵ�����
    unsigned int *indices;          //��Ŷ���˳�������(EBO)

    unsigned int VAO, VBO, EBO;
    std::vector<float> vTemp;
    std::vector<unsigned int> iTemp;

    void getInIndices(int n,int index);
    void getInVertices();

    void finalHandle();

    void drawObject();
    Object();
};

#endif // !OBJECT_H
