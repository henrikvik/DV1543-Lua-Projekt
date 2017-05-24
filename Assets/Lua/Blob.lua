dofile("Assets/Lua/Vector.lua");
dofile("Assets/Lua/Color.lua");

Blob = { 
	lifespan = 0,
	growthrate = 0,
	movespeed = 0,
	radius = 0, 
	color = Color:New(),
	position = Vector:New(), 
	name = "UNKNOWN"
};

--## Constructor ##--

function Blob:New(blob)
	blob = blob or {};
	self.__index = self;
	setmetatable(blob, self);
	return blob;
end

--## Member Function ##--

function Blob:Move(x, y)
	self.position.x = self.position.x + x;
	self.position.y = self.position.y + y;
end