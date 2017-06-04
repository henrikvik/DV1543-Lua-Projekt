dofile("Assets/Lua/Blob.lua");

this = Blob:New();

function update(delta)
	this.lifeSpan = this.lifeSpan - delta;

	local x, y = getInputDirection();

	this:Move(
		x * this.moveSpeed * delta,
		y * this.moveSpeed * delta
	);


end

function onCollision(otherRadius, distance)
	if (otherRadius > this.radius) then
		local difference = (otherRadius + this.radius) - distance;
		this.radius = this.radius - difference;

		if (this.radius <= 0.0) then
			quitGame();
		end
	end
end

function split()
	local newRadius = this.radius * 0.5;
	local newPosition = Vector:New({
		x = this.position.x + newRadius,
		y = this.position.y
	});
	
	this.radius = newRadius;
	this:Move(-newRadius, 0);

	addBlob(this.color, newPosition, newRadius, "Assets/Lua/AI.lua");	
end