require "Keys"

function on_create(own)
	print("Created: "..own.name)
end

function on_update(own, d)
	if Input.getKey(Keys.K_SPACE) then
		own.transform:move(0.3, 0.0, 0.0)
	end
end