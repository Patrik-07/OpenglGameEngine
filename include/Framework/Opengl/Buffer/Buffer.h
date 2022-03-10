#pragma once

class Buffer {
public:
    unsigned int ID = 0;

    virtual void unbind() const = 0;
    virtual void bind() const = 0;
};