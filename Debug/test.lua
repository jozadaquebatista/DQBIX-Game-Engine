screen(320, 240, 32, "Test")
lighting(true)

local key = 0
local tset_img = image("tiles.png")
local tset = tileset(tset_img, 3, 6, "abcdefghijklmnopqr")

local l5 = light(160, 120, 1.0, 1.0, 1.0)
local ocs = {
	boxoccluder(50, 50, 120, 12),
	boxoccluder(50, 100, 15, 20),
	boxoccluder(70, 100, 15, 20),
	boxoccluder(100, 100, 15, 20),
	boxoccluder(130, 100, 15, 20),
	boxoccluder(160, 100, 15, 20)
}

l5.intensity = 1.0
l5.radius = 50.0

addlight("l5", l5)

for i = 1, #ocs do
	addoccluder("oc"..i, ocs[i])
end

map = {
	{"p","g","g","g","g","o"},
	{"q","d","c","d","d","r"},
	{"q","d","d","d","d","r"}
}

while key ~= 27 do
	poll()
	cls()
	key = getkey()
	
	for i = 1, #map do
		for j = 1, #map[1] do
			blit(tset:tile(map[i][j]), (j-1)*64, (i-1)*64)
		end
	end
	
	l5.x = mousex()
	l5.y = mousey()
	
	flip()
end
quit()