dofile("Assets/Lua/Blob.lua")

this = Blob:New()
inputDir = Vector:New()

function update(delta)
	this:Move(inputDir * delta * 50);
end
