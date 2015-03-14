screen(320, 240, 32, "Test")
backcolor(0.2, 0.5, 0.9, 1.0)

local key = 0
local tset_img = image("data/tile1.png")
local tset = tileset(tset_img, 4, 4, "abcdefghijklmnop")

local walkimg = image("data/player.png")

player = {
	pos = point(160.0, 96.0),
	walk = animation(walkimg, 1, 4, 0.4, true),
	stand = image("data/stand.png")
}

map = {
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{"a","a","a","a","a","a","a","a"},
	{"e","e","e","e","e","e","e","e"},
	{"e","e","e","e","e","e","e","e"}
}

while key ~= 27 do
	poll()
	cls()
	key = getkey()
	
	color(0.0, 0.0, 0.0, 0.5)
	blits(player.walk:step(), player.pos.x-8, player.pos.y+8, 3.0, 3.0)
	color(1.0, 1.0, 1.0, 1.0)
	blits(player.walk:step(), player.pos.x, player.pos.y, 3.0, 3.0)

	for i = 1, #map do
		for j = 1, #map[1] do
			if map[i][j] ~= 0 then
				blits(tset:tile(map[i][j]), (j-1)*48, (i-1)*48, 3.0, 3.0)
			end
		end
	end
	
	flip()
end
quit()