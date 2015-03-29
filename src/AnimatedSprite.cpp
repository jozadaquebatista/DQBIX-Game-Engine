#include "../include/AnimatedSprite.h"
#include "../include/GameWindow.h"

AnimatedSprite::AnimatedSprite(Texture* sheet, int rows, int cols, float speed, bool loop)
{
    m_material = new Material(sheet);
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
    m_shader->addUniform("diffuse");
    if (m_material->getNormalTexture() != NULL)
        m_shader->addUniform("normal");
    m_shader->addUniform("cliprect");
    m_shader->addUniform("u_lightPos");
    m_shader->addUniform("u_lightColor");
    m_shader->addUniform("u_lightIntens");
    m_shader->addUniform("u_ambientColor");
    m_shader->addUniform("m_specularPower");
    m_shader->addUniform("m_normalPower");
    m_shader->addUniform("m_diffuseColor");
    m_shader->addUniform("m_specularColor");
#endif
}

AnimatedSprite::AnimatedSprite(Texture *sheet, Texture *sheet_norm, int rows, int cols, float speed, bool loop)
{
    m_material = new Material(sheet, sheet_norm);
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
    m_shader->addUniform("diffuse");
    if (m_material->getNormalTexture() != NULL)
        m_shader->addUniform("normal");
    m_shader->addUniform("cliprect");
    m_shader->addUniform("u_lightPos");
    m_shader->addUniform("u_lightColor");
    m_shader->addUniform("u_lightIntens");
    m_shader->addUniform("u_ambientColor");
    m_shader->addUniform("m_specularPower");
    m_shader->addUniform("m_normalPower");
    m_shader->addUniform("m_diffuseColor");
    m_shader->addUniform("m_specularColor");
#endif
}


AnimatedSprite::~AnimatedSprite()
{
    SAFE_DELETE(m_material);
	SAFE_DELETE(m_shader);
}

void AnimatedSprite::step()
{
	if (m_index < 0) m_index = 0;
    if (m_material == NULL) return;
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

    int w = m_material->getDiffuseTexture()->getResource()->getWidth() / m_cols;
    int h = m_material->getDiffuseTexture()->getResource()->getHeight() / m_rows;

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
    m_material->getDiffuseTexture()->setCliprect(clip);
    if (m_material->getNormalTexture() != NULL)
        m_material->getNormalTexture()->setCliprect(clip);
}

void AnimatedSprite::draw(SceneTree* tree)
{
    if (!m_material) return;

    m_material->getDiffuseTexture()->use(0);
    if (m_material->getNormalTexture() != NULL)
        m_material->getNormalTexture()->use(1);

    vec4 tr = m_material->getDiffuseTexture()->getTransformedClipRect();

#ifdef MODERN_OPENGL
    std::vector<Light*> lights = tree->getLights();
    if (m_shader != nullptr)
    {
        m_shader->use();
        m_shader->setInt("diffuse", 0);
        m_shader->setVec4("cliprect", tr.x, tr.y, tr.z, tr.w);
        m_shader->setMatrix("model", getTransform()->getTransformation());
        m_shader->setMatrix("proj", GameWindow::Projection);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        if (m_material->getIsSshadeless())
        {
            m_shader->setVec4("u_ambientColor", 1.0f, 1.0f, 1.0f, 1.0f);
            m_material->getDiffuseTexture()->getShape()->draw(GL_TRIANGLE_STRIP);
        }
        else
        {
            if (m_material->getNormalTexture() != NULL)
                m_shader->setInt("normal", 1);

            m_shader->setFloat("m_specularPower", m_material->getSpecularPower());
            m_shader->setFloat("m_normalPower", m_material->getNormalPower());
            m_shader->setVec4("m_diffuseColor", m_material->dR,
                                                m_material->dG,
                                                m_material->dB,
                                                m_material->dA);
            m_shader->setVec4("m_specularColor", m_material->sR,
                                                 m_material->sG,
                                                 m_material->sB,
                                                 m_material->sA);
            Color ambient = tree->getEngine()->getAmbient();
            m_shader->setVec4("u_ambientColor", ambient.r, ambient.g, ambient.b, ambient.a);

            if (lights.size() > 0)
            {

                glBlendFunc(GL_ONE, GL_ONE);
                glBlendEquation(GL_FUNC_ADD);

                for (Light*& l : lights)
                {
                    Vector3 lpos = l->getTransform()->getTranslation();
                    Color lcol = l->getColor();
                    m_shader->setVec3("u_lightPos", lpos.x, lpos.y, lpos.z);
                    m_shader->setVec4("u_lightColor", lcol.r, lcol.g, lcol.b, lcol.a);
                    m_shader->setFloat("u_lightIntens", l->getIntensity());

                    m_material->getDiffuseTexture()->getShape()->draw(GL_TRIANGLE_STRIP);
                }
            }
            else
            {
                m_material->getDiffuseTexture()->getShape()->draw(GL_TRIANGLE_STRIP);
            }
        }
        glDisable(GL_BLEND);
    }

    glUseProgram(0);
#endif
}

void AnimatedSprite::update(float delta)
{
	Node::update(delta);
    step();
}

bool AnimatedSprite::hovered(point mousepos)
{
    if (!m_material) return false;

    Vector3 pos = getTransform()->getTranslation();
    float w = (float)m_material->getDiffuseTexture()->getWidth();
    float h = (float)m_material->getDiffuseTexture()->getHeight();
    float sradius = w < h ? w / 2.0f : h / 2.0f;

    return (collisiondetection::circle(mousepos.x, mousepos.y, 2, pos.x, pos.y, sradius));
}

Material *AnimatedSprite::getMaterial() const
{
    return m_material;
}

void AnimatedSprite::setMaterial(Material *material)
{
    m_material = material;
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
