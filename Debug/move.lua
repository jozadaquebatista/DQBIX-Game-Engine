require "Keys"

local intens = 0.0

function on_update(own, d)
	local comps = own:getcomponents() -- Get all Components attached to Own (self)
	local lgt = comps["Light_comp2"] -- Get the light component

	-- Move the light with the mouse =)
	local mpos = Input.getMousePosition()
	own.transform:setposition(Vector3(mpos.x, mpos.y, 35.0))
	
	-- Light intensity controls
	if Input.getKey(Keys.K_w) then
		if intens < 500.0 then
			intens = intens + 0.5
		end
	elseif Input.getKey(Keys.K_s) then
		if intens >= 0.0 then
			intens = intens - 0.5
		end
	end

	-- Set the light intensity
	lgt.intensity = intens
end