dofile("Assets/Lua/Vector.lua");

Blob = { radius = 0, position = Vector:New() }

--## Constructor ##--

function Blob:New(a)
	a = a or {}
	self.__index = self;
	setmetatable(a, self);
	return a;
end

--## Member Function ##--

function Blob:Move(v)
	self.position.x = self.position.x + v.x;
	self.position.y = self.position.y + v.y;
end