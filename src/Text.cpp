#include "../include/Text.h"
#include "../include/GameWindow.h"

void Text::draw(SceneTree* tree)
{
    if (!m_font) return;

    m_font->use();
    glActiveTexture(GL_TEXTURE0);

	if (m_shader != nullptr)
	{
		m_shader->use();
        m_shader->setInt("image", 0);
		m_shader->setVec4("color", m_color.r, m_color.g, m_color.b, m_color.a);
		m_shader->setMatrix("model", getTransform()->getTransformation());
		m_shader->setMatrix("proj", GameWindow::Projection);
	}

    m_font->draw(m_text);

	glUseProgram(0);

}

Text::~Text()
{
    SAFE_DELETE(m_font);
    SAFE_DELETE(m_shader);
}
Font *Text::getFont() const
{
    return m_font;
}

void Text::setFont(Font *font)
{
    m_font = font;
}


Text::Text(std::string fontfile /*= ""*/, int sz/*=18*/)
{
    m_font = new Font(fontfile, sz);

    m_shader = new Shader();
    m_shader->fromString(text_vert, text_frag);

    m_shader->compile();
    m_shader->addCommonUniforms();
    m_shader->addUniform("image");
    m_shader->addUniform("color");
}

Text::Text(Font *f)
{
    m_font = f;
    if (!m_font) return;

    m_shader = new Shader();
    m_shader->fromString(text_vert, text_frag);

    m_shader->compile();
    m_shader->addCommonUniforms();
    m_shader->addUniform("image");
    m_shader->addUniform("color");
}
