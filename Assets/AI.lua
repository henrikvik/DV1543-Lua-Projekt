dofile("Blob.lua")

this = Blob:New()
enemies = {}
foods = {}

function update(delta)
--[[
	for k,v in ipairs(foods) do
	end

	for k,v in ipairs(enemies) do
	end
]]--

	local dir = enemies[1].position - this.position;
	dir:Normalize();

	position = position + dir * delta
end