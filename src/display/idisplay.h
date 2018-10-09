#pragma once

class IDisplay {
public:
    virtual ~IDisplay() = default;

	virtual void* GetNativeWindowHandle() const = 0;
    virtual void Update() const = 0;
};
