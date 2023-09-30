transform = addComponent("Transform3D", "Transform", {200, 200, 0}, {0, 0, 0, 1}, {1, 1, 1})
texture_rect = addComponent("TextureRect", "TextureRect", "Texture")
addLuaComponent("test_component.lua", "TestComponent")

Input = RayLibInput

function _on_update()
    if IsMouseButtonPressed(MOUSE_BUTTON_LEFT) then
        print(GetMousePosition())
    end
end

engine.events["update"]:addListener(_on_update)