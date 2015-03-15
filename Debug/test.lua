screen(320, 240, 32, "Test")
backcolor(0.2, 0.5, 0.9, 1.0)

-- Resources
local key = 0
local tset_img = image("data/tile1.png")
local tset = tileset(tset_img, 4, 4, "abcdefghijklmnop")
local walkimg = image("data/player.png")

-- Objects
player = {
	pos = point(160.0, 32.0),
	vel = point(0.0, 0.0),
	dir = 1,
	walk = animation(walkimg, 1, 4, 0.2, true),
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

-- Engine
local gravity = 8.0
local canjump = true

while key ~= 27 do
	poll()
	cls()
	key = getkey()
	
	color(0.0, 0.0, 0.0, 0.5)
	blits(player.walk:step(), player.pos.x-8, player.pos.y+8, 3.0*player.dir, 3.0)
	color(1.0, 1.0, 1.0, 1.0)
	blits(player.walk:step(), player.pos.x, player.pos.y, 3.0*player.dir, 3.0)

	for i = 1, #map do
		for j = 1, #map[1] do
			if map[i][j] ~= 0 then
				blits(tset:tile(map[i][j]), (j-1)*48, (i-1)*48, 3.0, 3.0)
			end
		end
	end
	
	-- Player movement
	if keystatus(32) then -- space
		if canjump then
			player.vel.y = -400
			canjump = false
		end
	else
		canjump = true
	end
	if keystatus(275) then -- right
		player.dir = 1
		player.vel.x = 1.5
	elseif keystatus(276) then -- left
		player.dir = -1
		player.vel.x = -1.5
	else
		player.vel.x = 0
	end
	player.pos.x = player.pos.x + player.vel.x
	
	-- Update player
	player.vel.y = player.vel.y + gravity
	player.vel.y = player.vel.y * 0.9		
	
	if player.pos.y > 96.0 then
		player.vel.y = 0
	end
	if player.pos.x <= 16.0 or player.pos.x >= 304.0 then
		player.vel.x = 0.0
	end
	
	player.pos.y = player.pos.y + player.vel.y
	
	flip()
end
quit()