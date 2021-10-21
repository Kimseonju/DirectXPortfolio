#include "IMGUIImageButton.h"
#include "Resource/Texture.h"
#include "Resource/ResourceManager.h"
CIMGUIImageButton::CIMGUIImageButton() :
    m_Click(false),
    m_Size(16.f, 16.f),
    m_SelectImageIdx(-1.f, -1.f)
{
}

CIMGUIImageButton::~CIMGUIImageButton()
{
}

bool CIMGUIImageButton::Init()
{
	return true;
}

void CIMGUIImageButton::Render()
{
	if (m_Font)
		ImGui::PushFont(m_Font);
    float m_tex_w= (float)m_Image->GetWidth();
    float m_tex_h = (float)m_Image->GetHeight();
    int IdxX = (int)(m_tex_w / m_Size.x);
    int IdxY = (int)(m_tex_h / m_Size.y);

    //ID넘기기 SRV로 넘길수있다고 함
    ImTextureID my_tex_id = m_Image->GetResourceInfo()->SRV;
    ImVec2 uv = ImVec2(16.f  / m_tex_w, 16.f / m_tex_h);

    for (int y = 1; y <= IdxY; ++y)
    {
        for (int x = 1; x <= IdxX; x++)
        {
            ImGui::PushID(y*IdxX+x);
            int frame_padding = 1;
            ImVec2 size = ImVec2(32.f, 32.f);
            ImVec2 uv0 = ImVec2(16.f * x / m_tex_w, 16.f * y / m_tex_h);
            uv0.x -= uv.x;
            uv0.y -= uv.y;
            ImVec2 uv1 = ImVec2(16.f * x / m_tex_w, 16.f * y / m_tex_h);


            ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
            ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            if (m_SelectImageIdx.x == x && m_SelectImageIdx.y == y)
            {
                bg_col = ImVec4(1.f, 0.0f, 0.0f, 1.0f);
                tint_col = ImVec4(1.f, 0.f, 0.f, 1.f);
            }
            if (ImGui::ImageButton(my_tex_id, size, uv0, uv1, frame_padding, bg_col, tint_col))
            {
                m_SelectImageIdx.x = (float)x;
                m_SelectImageIdx.y = (float)y;
            }
            if(x!=IdxX)
                ImGui::SameLine();
            ImGui::PopID();
        }
    }
    

	if (m_Font)
		ImGui::PopFont();

	if (m_Click && m_ClickCallback)
		m_ClickCallback();
}
