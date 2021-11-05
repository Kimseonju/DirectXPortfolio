#include "IMGUIImageButton.h"
#include "Resource/Texture.h"
#include "Resource/ResourceManager.h"
CIMGUIImageButton::CIMGUIImageButton() :
    m_Size(16.f, 16.f),
    m_SelectImageFrame(-1.f, -1.f),
    m_TileImageSize(-1.f, -1.f),
    m_FrameMaxX(-1),
    m_FrameMaxY(-1)

{
}

CIMGUIImageButton::~CIMGUIImageButton()
{
}

void CIMGUIImageButton::SetFrameMax(int x, int y)
{
    m_TileImageSize.x = (float)m_Texture->GetWidth();
    m_TileImageSize.y = (float)m_Texture->GetHeight();

    m_FrameMaxX = x;
    m_FrameMaxY = y;

    m_Size.x = m_TileImageSize.x / m_FrameMaxX;
    m_Size.y = m_TileImageSize.y / m_FrameMaxY;
}

void CIMGUIImageButton::SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
    CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName);

    m_Texture = CResourceManager::GetInst()->FindTexture(Name);
}

void CIMGUIImageButton::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
    CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath);

    m_Texture = CResourceManager::GetInst()->FindTexture(Name);
}

void CIMGUIImageButton::SetTexture(CTexture* Texture)
{
    m_Texture = Texture;
}

bool CIMGUIImageButton::Init()
{
    m_UVStart = ImVec2(0.f, 0.f);
    m_UVEnd = ImVec2(1.f, 1.f);
    
    m_Tint = ImVec4(1.f, 1.f, 1.f, 1.f);
    m_BorderColor = ImVec4(0.f, 0.f, 0.f, 0.f);
	return true;
}

void CIMGUIImageButton::Render()
{
	if (m_Font)
		ImGui::PushFont(m_Font);
    float m_tex_w= (float)m_Texture->GetWidth();
    float m_tex_h = (float)m_Texture->GetHeight();
    int IdxX = (int)(m_tex_w / m_Size.x);
    int IdxY = (int)(m_tex_h / m_Size.y);
    //타일1개 사이즈 16
    //32로 조금 키웠음

    //ID넘기기 SRV로 넘길수있다고 함
    ImTextureID my_tex_id = m_Texture->GetResourceInfo()->SRV;
    ImVec2 uv = ImVec2(m_Size.x / m_tex_w, m_Size.y / m_tex_h);
    bool Click = false;
    for (int y = 0; y < IdxY; ++y)
    {
        for (int x = 0; x < IdxX; ++x)
        {
            ImGui::PushID((y+1)*IdxX+(x+1));
            int frame_padding = 1;
            ImVec2 size = ImVec2(32.f, 32.f);
            ImVec2 uv0 = ImVec2(m_Size.x * x / m_tex_w, m_Size.y * y / m_tex_h);
            ImVec2 uv1 = ImVec2(m_Size.x * (x+1) / m_tex_w, m_Size.y * (y+1) / m_tex_h);


            ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
            ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            if (m_SelectImageFrame.x == x && m_SelectImageFrame.y == y)
            {
                bg_col = ImVec4(1.f, 0.0f, 0.0f, 1.0f);
                tint_col = ImVec4(1.f, 0.f, 0.f, 1.f);
                m_UVStart = uv0;
                m_UVEnd = uv1;

            }
            if (ImGui::ImageButton(my_tex_id, size, uv0, uv1, frame_padding, bg_col, tint_col))
            {
                Click = true;
                m_SelectImageFrame.x = (float)x;
                m_SelectImageFrame.y = (float)y;
            }
            if(x!=IdxX-1)
                ImGui::SameLine();
            ImGui::PopID();
        }
    }
    

	if (m_Font)
		ImGui::PopFont();

	if (Click && m_ClickCallback)
		m_ClickCallback();
}
