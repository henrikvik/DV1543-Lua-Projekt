dofile("Vector.lua");

Blob = { radius = 0, position = Vector:New() }

--## Constructor ##--

function Blob:New(a)
	a = a or {}
	self.__index = self;
	setmetatable(a, self);
	return a;
end

--## Member Function ##--

function Blob:Move(x, y)
	self.position.x += x;
	self.position.y += y;
end