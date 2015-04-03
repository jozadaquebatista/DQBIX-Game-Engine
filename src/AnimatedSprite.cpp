#include "../include/AnimatedSprite.h"
#include "../include/GameWindow.h"

AnimatedSprite::AnimatedSprite(Texture* sheet, int rows, int cols, float speed, bool loop)
    : Sprite(sheet)
{
    setMaterial(new Material(sheet));

	m_loop = loop;
	m_cols = cols;
	m_rows = rows;
	m_speed = speed;
	m_index = 0;
	m_clock.Start();

}

AnimatedSprite::AnimatedSprite(Texture *sheet, Texture *sheet_norm, int rows, int cols, float speed, bool loop)
    : Sprite(sheet, sheet_norm)
{
    setMaterial(new Material(sheet, sheet_norm));

    m_loop = loop;
    m_cols = cols;
    m_rows = rows;
    m_speed = speed;
    m_index = 0;
    m_clock.Start();

}

void AnimatedSprite::step()
{
	if (m_index < 0) m_index = 0;
    if (getMaterial() == NULL) return;
	if (m_cols <= 0 || m_rows <= 0) return;

	int fc = m_rows * m_cols;
	if (m_clock.ElapsedMillis() >= (int)(1000.0f * m_speed))
	{
		m_clock.Restart();
		if (m_index++ >= fc - 1)
		{
			if (m_loop)
				m_index = 0;
			else
				m_index = fc - 1;
		}
	}
	int i = 0;
	i = m_index;

    int w = getMaterial()->getDiffuseTexture()->getResource()->getWidth() / m_cols;
    int h = getMaterial()->getDiffuseTexture()->getResource()->getHeight() / m_rows;

	int ax = i % m_cols * w;
	int ay = (int)(i / m_cols) * h;

	rect clip;
	clip.x = ax;
	clip.y = ay;
	clip.w = w;
	clip.h = h;
	clip.frame = i;
	clip.cols = m_cols;
	clip.rows = m_rows;
    getMaterial()->getDiffuseTexture()->setCliprect(clip);
    if (getMaterial()->getNormalTexture())
        getMaterial()->getNormalTexture()->setCliprect(clip);
}

void AnimatedSprite::draw(SceneTree* tree)
{
    Sprite::draw(tree);
}

void AnimatedSprite::update(float delta)
{
	Node::update(delta);
    step();
}

bool AnimatedSprite::hovered(point mousepos)
{
    return Sprite::hovered(mousepos);
}

void AnimatedSprite::RegisterObject(lua_State* L)
{
	using namespace luabridge;

	getGlobalNamespace(L)
		.beginClass<AnimatedSprite>("AnimatedSprite")
		.addConstructor<void(*)(Texture*, int, int, float, bool)>()
		.addProperty("rows", &AnimatedSprite::getRows, &AnimatedSprite::setRows)
		.addProperty("columns", &AnimatedSprite::getCols, &AnimatedSprite::setCols)
		.addProperty("speed", &AnimatedSprite::getSpeed, &AnimatedSprite::setSpeed)
		.addProperty("loop", &AnimatedSprite::getLoop, &AnimatedSprite::setLoop)
		.addProperty("index", &AnimatedSprite::getIndex)
		.addFunction("step", &AnimatedSprite::step)
		.endClass();
}
