#include "../include/Sprite.h"
#include "../include/GameWindow.h"

Sprite::Sprite(std::string filename)
{
	m_texture = filename != "" ? new Texture(filename) : NULL;
#ifdef MODERN_OPENGL
	m_shader = new Shader();
	m_shader->fromString(default_vert, default_frag);

	m_shader->compile();
	m_shader->addCommonUniforms();
	m_shader->addUniform("image");
	m_shader->addUniform("cliprect");
#endif
}


Sprite::~Sprite()
{
	SAFE_DELETE(m_texture);
	SAFE_DELETE(m_shader);
}

void Sprite::draw()
{
	if (!m_texture) return;

	vec4 tr = m_texture->getTransformedClipRect();

	m_texture->bind();

#ifdef MODERN_OPENGL
	if (m_shader != nullptr)
	{
		m_shader->use();
		m_shader->setInt("image", 0);
		m_shader->setVec4("cliprect", tr.x, tr.y, tr.z, tr.w);
		m_shader->setMatrix("model", getTransform()->getTransformation());
		m_shader->setMatrix("proj", GameWindow::Projection);
	}
    m_texture->getShape()->draw(GL_TRIANGLE_STRIP);

    glUseProgram(0);
#else
    float w2 = (float)m_texture->getWidth() / 2.0f;
    float h2 = (float)m_texture->getHeight() / 2.0f;

    float crx = tr.x / m_texture->getCliprect().cols;
    float cry = tr.y / m_texture->getCliprect().rows;
    float crw = tr.z;
    float crh = tr.w;

    glPushMatrix();

    glMultMatrixf(value_ptr(getTransform()->getTransformation()));

    glBegin(GL_QUADS);

    glTexCoord2f(crx,         cry); glVertex2f(-1.0f*w2, -1.0f*h2);
    glTexCoord2f(crx+crw,     cry); glVertex2f( 1.0f*w2, -1.0f*h2);
    glTexCoord2f(crx+crw, cry+crh); glVertex2f( 1.0f*w2,  1.0f*h2);
    glTexCoord2f(crx,     cry+crh); glVertex2f(-1.0f*w2,  1.0f*h2);

    glEnd();

    glPopMatrix();
#endif
}

// This is a bad thing, but it's okay for now.
bool Sprite::hovered(point mousepos)
{
    if (!getTexture()) return false;

    Vector3 pos = getTransform()->getTranslation();
    float w = (float)getTexture()->getWidth();
    float h = (float)getTexture()->getHeight();
    float sradius = w < h ? w / 2.0f : h / 2.0f;

    return (collisiondetection::circle(mousepos.x, mousepos.y, 2, pos.x, pos.y, sradius));
}

void Sprite::RegisterObject(lua_State* L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginClass<Sprite>("Sprite")
		.addConstructor<void(*)(std::string)>()
		.addProperty("texture", &Sprite::getTexture, &Sprite::setTexture)
		.endClass();
}
