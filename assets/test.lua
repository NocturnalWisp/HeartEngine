
print("Working!")

addComponent("Transform", "c_transform")
addLuaComponent("assets/test_component.lua", "c_test")

c_transform.position.x = 20

print(c_test.var)