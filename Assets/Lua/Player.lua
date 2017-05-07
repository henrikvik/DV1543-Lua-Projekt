dofile("Assets/Lua/Blob.lua");

this = Blob:New();
moveSpeed = 10;

function update(delta)
	
	local x, y = getInputDirection();

	this:Move(
		x * moveSpeed * delta,
		y * moveSpeed * delta
	);

end

function onCollision(otherRadius, distance)
	if (otherRadius > this.radius) then
		local difference = (otherRadius + this.radius) - distance;
		this.radius = this.radius - difference;
	end
end