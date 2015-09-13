#include "../include/AnimatedSprite.h"
#include "../include/GameWindow.h"

AnimatedSprite::AnimatedSprite(Texture* sheet, int rows, int cols) : Sprite(sheet)
{
    setMaterial(new Material(sheet));

	m_cols = cols;
	m_rows = rows;
	m_index = 0;
	m_clock.Start();

}

AnimatedSprite::AnimatedSprite(Texture *sheet, Texture *sheet_norm, int rows, int cols) : Sprite(sheet, sheet_norm)
{
    setMaterial(new Material(sheet, sheet_norm));

    m_cols = cols;
    m_rows = rows;
    m_index = 0;
    m_clock.Start();

}

void AnimatedSprite::step()
{
    if (m_currentAnim == NULL) return;
	if (m_index < 0) m_index = 0;
    if (getMaterial() == NULL) return;
	if (m_cols <= 0 || m_rows <= 0) return;

	int fc = m_rows * m_cols;
    int sz = m_currentAnim->m_frames.size();
    if (m_clock.ElapsedMillis() >= (int)(1000.0f * m_currentAnim->m_speed))
	{
		m_clock.Restart();
        if (sz <= 0)
        {
            if (m_index++ >= fc - 1)
            {
                if (m_currentAnim->m_loop)
                    m_index = 0;
                else
                    m_index = fc - 1;
            }
        }
        else
        {
            if (m_index++ >= sz - 1)
            {
                if (m_currentAnim->m_loop)
                    m_index = 0;
                else
                    m_index = sz - 1;
            }
        }
	}
	int i = 0;
    if (m_currentAnim->m_frames.size() <= 0)
    {
        i = m_index;
    }
    else
    {
        i = m_currentAnim->m_frames[m_index];
    }

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

void AnimatedSprite::addAnimation(Animation* anim)
{
    m_animations[anim->m_name] = anim;
}

bool AnimatedSprite::removeAnimation(std::string name)
{
    map<string, Animation*>::const_iterator pos = m_animations.find(name);
    if (pos != m_animations.end())
    {
        m_animations.erase(pos);
        return true;
    }
    return false;
}

void AnimatedSprite::setCurrentAnimation(std::string name)
{
    map<std::string, Animation*>::const_iterator pos = m_animations.find(name);
    if (pos != m_animations.end())
    {
        m_index = 0;
        m_currentAnim = pos->second;
    }
}

void AnimatedSprite::RegisterObject(lua_State* L)
{
	using namespace luabridge;

	getGlobalNamespace(L)
        .deriveClass<AnimatedSprite, Node>("AnimatedSprite")
        .addConstructor<void(*)(Texture*, int, int)>()
        .addConstructor<void(*)(Texture*, Texture*, int, int)>()
        .addFunction("setcurrentanimation", &AnimatedSprite::setCurrentAnimation)
		.addProperty("rows", &AnimatedSprite::getRows, &AnimatedSprite::setRows)
        .addProperty("columns", &AnimatedSprite::getCols, &AnimatedSprite::setCols)
		.addProperty("index", &AnimatedSprite::getIndex)
		.addFunction("step", &AnimatedSprite::step)
		.endClass();
}
