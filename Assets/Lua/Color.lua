Color = { r = 0, g = 0, b = 0 };

-- # Constructor # --

function Color:New(color)
	color = color or {};
	self.__index = self;
	setmetatable(color, self);
	return color;
end
