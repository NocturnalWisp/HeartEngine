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

addEventListener("component_event", c_test._on_test_component)
addEventListener("component_event", c_test._on_test_component2)
addEventListener("component_event", c_test._on_test_component3)