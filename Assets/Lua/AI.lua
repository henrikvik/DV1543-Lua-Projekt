dofile("Assets/Lua/Blob.lua")

this = Blob:New()

function update(delta)
	local dangerX, dangerY, dangerD = getClosestDanger()
	local foodX, foodY, foodD = getClosestFood()

	if (dangerD > foodD) then
		moveAway(dangerX, dangerY, delta)
	else
		moveTo(foodX, foodY, delta)
	end

	
end

function onCollision(otherRadius, distance)
	if (otherRadius > this.radius) then
		local difference = (otherRadius + this.radius) - distance;
		this.radius = this.radius - difference;
	end
end

function moveTo(x, y, delta)	
	local newPos = Vector(x, y)

	dir = Normalize(newPos - this.position)

	this.Move(
	dir.x * delta,
	dir.y * delta
	);	

end

function moveAway(x, y, delta)
	local danger *= Vector(x, y)
	dir = Normalize(this.position - danger)

	this.Move(
		dir.x * delta,
		dir.y * delta
	);
end
