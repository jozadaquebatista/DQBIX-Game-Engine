#include "../include/AnimatedSprite.h"
#include "../include/GameWindow.h"

AnimatedSprite::AnimatedSprite(Texture* sheet, int rows, int cols, float speed, bool loop)
{
	m_sheet = sheet;
	m_loop = loop;
	m_cols = cols;
	m_rows = rows;
	m_speed = speed;
	m_index = 0;
	m_clock.Start();

#ifdef MODERN_OPENGL
	m_shader = new Shader();
	m_shader->fromString(default_vert, default_frag);
	m_shader->compile();
	m_shader->addCommonUniforms();
	m_shader->addUniform("image");
	m_shader->addUniform("cliprect");
#endif
}


AnimatedSprite::~AnimatedSprite()
{
	SAFE_DELETE(m_sheet);
	SAFE_DELETE(m_shader);
}

void AnimatedSprite::step()
{
	if (m_index < 0) m_index = 0;
	if (m_sheet == NULL) return;
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

	int w = m_sheet->getResource()->getWidth() / m_cols;
	int h = m_sheet->getResource()->getHeight() / m_rows;

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
	m_sheet->setCliprect(clip);
}

void AnimatedSprite::draw()
{
	if (!m_sheet) return;

	vec4 tr = m_sheet->getTransformedClipRect();

	m_sheet->bind();

#ifdef MODERN_OPENGL
    if (m_shader != NULL)
	{
		m_shader->use();
		m_shader->setInt("image", 0);
		m_shader->setVec4("cliprect", tr.x, tr.y, tr.z, tr.w);
		m_shader->setMatrix("model", getTransform()->getTransformation());
		m_shader->setMatrix("proj", GameWindow::Projection);
	}

	m_sheet->getShape()->draw(GL_TRIANGLE_STRIP);

	glUseProgram(0);
#else
    float w2 = (float)m_sheet->getResource()->getWidth() / 2.0f;
    float h2 = (float)m_sheet->getResource()->getHeight() / 2.0f;

    float crx = tr.x / m_sheet->getCliprect().cols;
    float cry = tr.y / m_sheet->getCliprect().rows;
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

void AnimatedSprite::update(float delta)
{
	Node::update(delta);
	step();
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
