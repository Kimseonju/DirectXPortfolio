#pragma once

#include "../Ref.h"

struct TextureResourceInfo
{
    //DirectXTex 클래스 이미지 픽셀정보 저장
    ScratchImage* Image;
    //이미지 쉐이더에 넘기는 용도
    ID3D11ShaderResourceView* SRV;
    unsigned int    Width;
    unsigned int    Height;
    TCHAR* FileName;
    char* PathName;
    TCHAR* FullPath;
    TextureResourceInfo() :
        Image(nullptr),
        SRV(nullptr),
        FileName(nullptr),
        PathName(nullptr),
        FullPath(nullptr),
        Width(0),
        Height(0)
    {
    }
};

//이미지의 픽셀정보와 쉐이더를 가지고있음
class CTexture :
    public CRef
{
    friend class CResourceManager;
    friend class CSceneResource;
    friend class CMaterial;

protected:
    CTexture();
    virtual ~CTexture();

protected:
    class CScene* m_pScene;
    std::vector<TextureResourceInfo*>   m_vecResourceInfo;
    Image_Type                  m_ImageType;
    ID3D11ShaderResourceView*   m_ArraySRV;

public:
    ID3D11ShaderResourceView* GetResource(int Index = 0) const
    {
        return m_vecResourceInfo[Index]->SRV;
    }

    TextureResourceInfo* GetResourceInfo(int index=0) const
    {
        return m_vecResourceInfo[index];
    }



    Image_Type GetImageType()   const
    {
        return m_ImageType;
    }

    unsigned int GetWidth(int Index = 0)    const
    {
        return m_vecResourceInfo[Index]->Width;
    }

    unsigned int GetHeight(int Index = 0)    const
    {
        return m_vecResourceInfo[Index]->Height;
    }

    size_t GetImageCount()  const
    {
        return m_vecResourceInfo.size();
    }

public:
    bool LoadTexture(const std::string& Name, const TCHAR* FileName,
        const std::string& PathName = TEXTURE_PATH);
    bool LoadTextureFullPath(const std::string& Name, const TCHAR* FullPath);
    bool LoadTexture(const std::string& Name, const std::vector<const TCHAR*>& vecFileName, 
        const std::string& PathName = TEXTURE_PATH);
    bool LoadTextureFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath);
    bool LoadTextureArray(const std::string& Name, const std::vector<const TCHAR*>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    bool LoadTextureArrayFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath);

protected:
    //쉐이더 리소스 뷰 생성
    bool CreateResource(int Index);
    bool CreateResourceArray();

public:
    virtual void SetShader(int Register, int ShaderType, int Index = 0);
    virtual void ResetShader(int Register, int ShaderType, int Index = 0);
    virtual void Save(FILE* pFile);
};
