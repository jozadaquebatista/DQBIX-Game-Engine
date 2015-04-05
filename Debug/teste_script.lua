require "Keys"

function on_create(own)
	print("Created "..own:getname())
end

function on_update(own, d)
	local x = own:gettransform():getposition()
	print(x.x)
end