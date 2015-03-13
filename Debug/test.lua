screen(320, 240, 32, "Test")
lighting(false)

local key = 0
local tset_img = image("data/tile1.png")
local tset = tileset(tset_img, 4, 4, "abcdefghijklmnop")

player = {
	pos = point(0.0, 0.0),
	walk = animation(image("data/player.png"), 1, 4, 0.4, true),
	stand = image("data/stand.png"),
}
walk = animation(image("data/player.png"), 1, 4, 0.4, true)

map = {
	{"g","g","g","g","g","g","g","g"},
	{"g","g","g","g","g","g","g","g"},
	{"g","g","g","g","g","g","g","g"},
	{"g","g","g","g","g","g","g","g"},
	{"g","g","g","g","g","g","g","g"},
	{"g","g","g","g","g","g","g","g"}
}

while key ~= 27 do
	poll()
	cls()
	key = getkey()
	
	-- for i = 1, #map do
		-- for j = 1, #map[1] do
			-- blits(tset:tile(map[i][j]), (j-1)*48, (i-1)*48, 3.0, 3.0)
		-- end
	-- end
	
	blits(walk:step(), 20, 20, 3.0, 3.0)
		
	flip()
end
quit()