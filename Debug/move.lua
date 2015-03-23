require "Keys"

function on_update(own, d)
	if Input.getKey(Keys.K_SPACE) then
		own.transform:move(1.0, 0.0, 0.0)
	end
end