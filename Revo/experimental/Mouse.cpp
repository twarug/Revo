#include <Revo/System/Mouse.hpp>

namespace rv
{
    int32_t Mouse::GetInternalCode(CodeType value)
    {
        switch (value)
        {
            case Button1: return GLFW_MOUSE_BUTTON_1;
            case Button2: return GLFW_MOUSE_BUTTON_2;
            case Button3: return GLFW_MOUSE_BUTTON_3;
            case Button4: return GLFW_MOUSE_BUTTON_4;
            case Button5: return GLFW_MOUSE_BUTTON_5;
            case Button6: return GLFW_MOUSE_BUTTON_6;
            case Button7: return GLFW_MOUSE_BUTTON_7;
            case Button8: return GLFW_MOUSE_BUTTON_8;
            case Count:   [[fallthrough]]
            case Unknown: [[fallthrough]]
            default:      return -1;
        }
    }
}
