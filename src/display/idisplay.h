#pragma once

class IDisplay {
public:
    virtual ~IDisplay() = default;

    virtual void Update() const = 0;
};
