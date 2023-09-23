-- print(GlobalDataTest.name)
-- GlobalDataTest.x = 990

var = 6

function _on_create()
    print("Creating!")
end

function _on_test_component(x, y)
    print("Working events! 1")
    print(x)
    print(y)
end
function _on_test_component2(x)
    print("Working events! 2")
    print(x)
end
function _on_test_component3()
    print("Working events! 3")
end

print(node.name)

v = node:addEventListener("component_event", _on_test_component)
node:addEventListener("component_event", _on_test_component2)
node:addEventListener("component_event", _on_test_component3)

node:removeEventListener("component_event", v)

node:runEvent("component_event", 8, 9)
--TODO: fix running event setup in c++
node.engine:getNode("TextureRect2"):runEvent("test", 8, 9)