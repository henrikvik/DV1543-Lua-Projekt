dofile("Assets/Lua/Blob.lua")

this = Blob:New()
enemies = {}
foods = {}

function update(delta)

	this:Move(delta, delta);
end