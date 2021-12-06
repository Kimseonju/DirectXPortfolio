#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include <UI/ProgressBar.h>
#include "RestaurantButton.h"
#include <UI/Text.h>
struct RestaurantInfo
{
    CRestaurantButton* RestaurantButton;
    CText* FoodName;
    CText* FoodPrice;
    void Enable(bool bEnable)
    {
        RestaurantButton->Enable(bEnable);
        FoodName->Enable(bEnable);
        FoodPrice->Enable(bEnable);

    }
    void Active(bool bActive)
    {
        RestaurantButton->Active(bActive);
        FoodName->Active(bActive);
        FoodPrice->Active(bActive);
    }
};
class CRestaurantUI :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CSharedPtr<CImage>    m_BackGround;
    CSharedPtr<CImage>    m_Base;
    CSharedPtr<CImage>    m_Label;
    CSharedPtr<CImage>    m_RestaurantTable;
    CSharedPtr<CImage>    m_SatietyBase;
    CSharedPtr<CImage>    m_SatietyIcon;
    CSharedPtr<CText>    m_SatietyLeft;
    CSharedPtr<CText>    m_SatietyMiddle;
    CSharedPtr<CText>    m_SatietyRight;
    CSharedPtr<CProgressBar>    m_SatietyBar;


    CSharedPtr<CImage>    m_BaseTable;
    CSharedPtr<CImage>    m_FoodSelectBase;
    CSharedPtr<CImage>    m_GoldIcon;
    CSharedPtr<CText>    m_GoldText;

    CSharedPtr<CImage>    m_GoldBase;
    std::vector<RestaurantInfo> m_RestaurantInfo;

    std::unordered_map<FoodType, CSharedPtr<CImage>> m_mapFoodImage;


    CImage* m_SelectFoodImage;
    CImage* m_EatFoodImage;
    bool m_Eat;
    bool m_EatStart;
    float m_EatFoodImageAlpha;
protected:
    CRestaurantUI();
    virtual ~CRestaurantUI();
public:
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CRestaurantUI* Clone();
public:
    void MosueOnCallback();
    void ClickCallback();
    
};

