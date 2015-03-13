screen(320, 240, 32, "Test")
lighting(true)

local key = 0
local tset_img = image("data/tile1.png")
local tset = tileset(tset_img, 3, 6, "abcdefghijklmnopqr")

map = {
	{"p","g","g","g","g","o"},
	{"q","d","c","d","d","r"},
	{"q","d","d","d","d","r"},
	{"q","d","d","d","d","r"}
}

while key ~= 27 do
	poll()
	cls()
	key = getkey()
	
	for i = 1, #map do
		for j = 1, #map[1] do
			blit(tset:tile(map[i][j]), (j-1)*16, (i-1)*16)
		end
	end
	
	for i = 1, #ocs do
		rect(ocs[i].x, ocs[i].y, ocs[i].width, ocs[i].height, true)
	end
	
	l5.x = mousex()
	l5.y = mousey()
	
	flip()
end
quit()