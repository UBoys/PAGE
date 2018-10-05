VULKAN VALIDATION LAYER SETUP

ON WINDOWS:
    1.  Run the bat script to set environment variable for validation layers.

    2.  Place the vk_layer_settings.txt file in the same folder as the Engines executable to run with validation layers



ON LINUX:
    1.    Add the validation layer environment variable by entering the following command in the terminal:
            export VK_INSTANCE_LAYERS=VK_LAYER_LUNARG_standard_validation

    2.  Place the vk_layer_settings.txt file in the same folder as the Engines executable to run with validation layers


















EXTRA INFO ABOUT VALIDATION LAYERS WITH EXAMPLES:

To use multiple layers can be at the same time, assign the names of the layers
you to the VK_INSTANCE_LAYERS environment variable.

ON WINDOWS:
setx VK_INSTANCE_LAYERS
VK_LAYER_LUNARG_api_dump;VK_LAYER_LUNARG_core_validation

ON LINUX:
export VK_INSTANCE_LAYERS=VK_LAYER_LUNARG_api_dump:VK_LAYER_LUNARG_core_validation
