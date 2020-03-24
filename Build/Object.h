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
*/
public:
    // vn == vertices number
    // in == indices number
    int vn, in;

    float *vertices;                //��Ŷ������ݵ�����
    unsigned int *indices;          //��Ŷ���˳�������(EBO)

    unsigned int VAO, VBO, EBO;
    Object();

    void drawObject();
};

#endif // !OBJECT_H
