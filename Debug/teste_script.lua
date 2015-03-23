require "Keys"

local r = 0.0
local s = 1.0

function on_create(own)
	print("Created "..own:getname())
	local par = own:getparent()
	print(own:getname().."'s parent is "..par:getname())
end

function on_update(own, d)
	r = r + d * 2
	s = s + d * 6
	local ob_scale = math.abs(math.sin(s))
	own.transform:setscale(Vector3(ob_scale, 1.0, 1.0))
	own.transform:setrotation(r, Vector3(0.0, 0.0, 1.0))
end