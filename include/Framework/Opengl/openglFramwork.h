#pragma once

#include "Buffer/VertexAttribute.h"
#include "Buffer/VertexBuffer.h"

#include "Buffer/ElementBuffer.h"

#include "Buffer/VertexArray.h"

void initGlew() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("GLEW initialization failed.\n");
    }
}