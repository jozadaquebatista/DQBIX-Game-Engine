#include "../include/Sprite.h"
#include "../include/GameWindow.h"

Sprite::Sprite(std::string filename)
{
    m_material = new Material(new Texture(filename));

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
    m_shader->addUniform("u_lightFalloff");
#endif
}

Sprite::Sprite(std::string filename, std::string normal_filename)
{
    m_material = new Material(new Texture(filename), new Texture(normal_filename));

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
    m_shader->addUniform("u_lightFalloff");
#endif
}


Sprite::~Sprite()
{
	SAFE_DELETE(m_shader);
    SAFE_DELETE(m_material);
}

void Sprite::draw(SceneTree* tree)
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
                    m_shader->setVec3("u_lightFalloff", l->getConstant(), l->getLinear(), l->getQuadratic());

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
    if (!m_material->getDiffuseTexture()) return false;

    Vector3 pos = getTransform()->getTranslation();
    float w = (float)m_material->getDiffuseTexture()->getWidth();
    float h = (float)m_material->getDiffuseTexture()->getHeight();
    float sradius = w < h ? w / 2.0f : h / 2.0f;

    return (collisiondetection::circle(mousepos.x, mousepos.y, 2, pos.x, pos.y, sradius));
}

void Sprite::RegisterObject(lua_State* L)
{
	using namespace luabridge;
	getGlobalNamespace(L)
		.beginClass<Sprite>("Sprite")
        .addConstructor<void(*)(std::string)>()
        .addConstructor<void(*)(std::string, std::string)>()
		.endClass();
}
Material *Sprite::getMaterial() const
{
    return m_material;
}

void Sprite::setMaterial(Material *material)
{
    m_material = material;
}

