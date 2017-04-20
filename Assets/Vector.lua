Vector = { x = 0, y = 0 }

--## Constructor ##--

function Vector:New(a)
	a = a or {}
	self.__index = self
	setmetatable(a, self)
	return a;
end

--## Memeber Functions ##--

function Vector:Distance(other)
	return math.sqrt((self.x - other.x) ^ 2 + (self.y - other.y) ^ 2)
end

function Vector:Length()
	return math.sqrt(self.x ^ 2 + self.y ^ 2)
end

function Vector:Normalize()
	local length = self:Length()
	self.x = self.x / length
	self.y = self.y / length
end

--## Meta Functions ##--

function Vector.__sub(a, b)
	if (getmetatable(a) == Vector) then
		if (getmetatable(b) == Vector) then
			return Vector:New({ 
				x = a.x - b.x,
				y = a.y - b.y
			})
		end
	else
		error("behaviour not defined Vector.__sub")
	end
end

function Vector.__mul(a, b)
	if (getmetatable(a) == Vector) then
		if (type(b) == "number") then
			return Vector:New({ 
				x = a.x * b,
				y = a.y * b
			})
		end
	elseif (type(a) == "number") then
		if (getmetatable(b) == Vector) then
			return Vector:New({ 
				x = a * b.x,
				y = a * b.y
			})
		end
	else
		error("behaviour not defined Vector.__mul")
	end
end