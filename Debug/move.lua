require "Keys"

local r = 0.0
function on_update(own, d)
	r = r + d * 5
	if Input.getKey(Keys.K_SPACE) then
		own.transform:move(1.0, 0.0, 0.0)
	end
end