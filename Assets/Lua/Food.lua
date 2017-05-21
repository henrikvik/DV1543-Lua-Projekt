dofile("Assets/Lua/Blob.lua");

this = Blob:New();

function update(delta)
	

end

function onCollision(otherRadius, distance)
	if (otherRadius > this.radius) then
		local difference = (otherRadius + this.radius) - distance;
		this.radius = this.radius - difference;
	end
end