#pragma once

class ModelLoader {
public:
    virtual const Model load() const = 0;
};