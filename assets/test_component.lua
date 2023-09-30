spin = 0.0

transform = node:getComponent("Transform")
textureRect = node:getComponent("TextureRect")

function _on_update()
    spin += 200.0
end

node.engine.events["update"]:addListener(_on_update)