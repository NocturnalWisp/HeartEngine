c_test = {
    var = 6,

    _on_create = function()
        print("Creating!")
    end,

    _on_test_component = function(x, y)
        print("Working events! 1")
        print(x)
        print(y)
    end,
    _on_test_component2 = function(x)
        print("Working events! 2")
        print(x)
    end,
    _on_test_component3 = function()
        print("Working events! 3")
    end,
}

print(node.name)

v = node:addEventListener("component_event", c_test._on_test_component)
node:addEventListener("component_event", c_test._on_test_component2)
node:addEventListener("component_event", c_test._on_test_component3)

node:removeEventListener("component_event", v)

getComponent("c_transform")

print(c_transform.position.x)
c_transform.position.x = 40

node:runEvent("component_event", 8, 9)