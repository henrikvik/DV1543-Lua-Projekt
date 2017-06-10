dofile("Assets/Lua/Blob.lua");

this = Blob:New();

function update(delta)
	local x, y, r = getClosestBlob();
	
	if (r > this.radius) then
		--print("ohgod");
		moveAway(x, y, delta);
	else
		--print("isfine");
		--moveTo(x, y, delta);
	end	
end

function onCollision(otherRadius, distance)
	if (otherRadius > this.radius) then
		local difference = (otherRadius + this.radius) - distance;
		this.radius = this.radius - difference;
		print("help");
		if (this.radius < 0) then
			addBlob(
				{ r = 0, g = 255, b = 0}, 
				{ x = 100.0, y = 20.0}, 
				65.0,
				"Assets/Lua/AI.lua"
			);
		end
	end
end

function moveTo(x, y, delta)	
	local newPos = Vector:New({x = x, y = y});
	local dir = newPos - this.position;
	dir:Normalize();

	this:Move(dir.x * delta, dir.y * delta);
end

function moveAway(x, y, delta)
	print("moveAway");
	local danger = Vector:New({x = x, y = y});
	local dir = this.position - danger;
	dir:Normalize();

	this:Move(dir.x * delta, dir.y * delta);
end
