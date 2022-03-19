#pragma once

class UniformValue {
public:
    virtual void set(int location) const = 0;
    virtual ~UniformValue() = default;
    virtual void print() const = 0;
};

template<typename T>
class TemplatedUniformValue : public UniformValue {
public:
    virtual void set(int location) const = 0;
    virtual void print() const = 0;
};
