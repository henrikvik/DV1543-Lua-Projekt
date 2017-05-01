dofile("Assets/Lua/Blob.lua")

this = Blob:New()

function update(delta)

	this:Move(delta, delta);
end