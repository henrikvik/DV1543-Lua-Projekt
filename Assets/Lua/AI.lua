dofile("Assets/Lua/Blob.lua")

this = Blob:New()

function update(delta)
	
	this.radius = this.radius + delta;
	this:Move(delta, 0);
end

function onCollision(otherRadius, distance)
	print("SCHREEE");

	if (otherRadius > this.radius) then
		local difference = (otherRadius + this.radius) - distance;
		this.radius = this.radius - difference;
	end
end