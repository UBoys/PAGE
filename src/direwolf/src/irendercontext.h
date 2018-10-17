#pragma once

namespace dwf {

class IRenderContext {
public:
    virtual ~IRenderContext() = default;
    virtual void SwapBuffers() const = 0;
};

}
