transform = addComponent("Transform", "Transform")
other_test = addComponent("OtherTest", "OtherTest")
-- texture_rect = addComponent("EngineTextureRect", "TextureRect", "Texture")
-- addComponent("CustomTexture", "CustomTexture")

print("Bleg")
print(other_test.x)
other_test.x = 30
print(other_test.x)

-- addLuaComponent("assets/test_component.lua", "c_test")

GlobalDataTest.x = 200

-- runEvent("component_event", 6, 8)