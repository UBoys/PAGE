#include "pgfx.h"
#include <iostream>

namespace pgfx {

MainRenderer::MainRenderer() {
    std::cout << "Creating renderer...\n";
}

void MainRenderer::Foo() {
    std::cout << "Bar\n";
}

}  // namespace pgfx
