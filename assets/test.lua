transform = addComponent("Transform3D", "Transform", {200, 200, 0}, {0, 0, 0, 1}, {1, 1, 1})
texture_rect = addComponent("TextureRect", "TextureRect", "Texture")
addLuaComponent("test_component.lua", "TestComponent")

print(Vector2(10, 10) + Vector2(5, 6))