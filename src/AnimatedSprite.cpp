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

	m_shader = new Shader();
	m_shader->fromString(default_vert, default_frag);
	m_shader->compile();
	m_shader->addCommonUniforms();
	m_shader->addUniform("image");
	m_shader->addUniform("cliprect");
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

	if (m_shader != nullptr)
	{
		m_shader->use();
		m_shader->setInt("image", 0);
		m_shader->setVec4("cliprect", tr.x, tr.y, tr.z, tr.w);
		m_shader->setMatrix("model", getTransform()->getTransformation());
		m_shader->setMatrix("proj", GameWindow::Projection);
	}

	m_sheet->getShape()->draw(GL_TRIANGLE_STRIP);

	glUseProgram(0);
}
