dofile("Assets/Blob.lua")

me = Blob:New()
enemies = {}
foods = {}

function update(delta)
--[[
	for k,v in ipairs(foods) do
	end

	for k,v in ipairs(enemies) do
	end
]]--

	print("update");
--[[
	local dir = enemies[1].position - this.position;
	dir:Normalize();

	position = position + dir * delta
]]--
end