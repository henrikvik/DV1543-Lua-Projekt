dofile("Assets/Lua/Blob.lua")

this = Blob:New()

function update(delta)
	
	local x, y, radius = getClosestBlob();

	local dir = Vector:New({
		x = x - this.position.x,
		y = y - this.position.y
	});

	dir:Normalize();

	if (radius > this.radius) then
		dir = -dir;
	end
	
	this.radius = this.radius + delta;
	this:Move(
		dir.x * delta,
		dir.y * delta
	);
end

function onCollision(otherRadius, distance)
	if (otherRadius > this.radius) then
		local difference = (otherRadius + this.radius) - distance;
		this.radius = this.radius - difference;
	end
end