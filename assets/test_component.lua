spin = 0.0

transform = node:getComponent("Transform")
textureRect = node:getComponent("TextureRect")

function _on_update()
    spin = spin + 200.0 * RayLib:GetFrameTime()
    transform:setLocalRotation(RotationAxisAngle(0, 0, 1, deg2rad * spin))
end

node.engine.events["update"]:addListener(_on_update)