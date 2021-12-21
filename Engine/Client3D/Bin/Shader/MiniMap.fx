
#include "UI.fx"

cbuffer MiniMapCBuffer : register(b13)
{
	float2	g_Size;
	float2	g_Empty;
};

struct VS_INPUT_MINIMAP
{
	float3	Pos : POSITION;
	uint	InstanceID : SV_InstanceID;
};

struct VS_OUTPUT_MINIMAP
{
	float4	Pos : SV_POSITION;
	float4	ProjPos : POSITION;
	float4	Color : COLOR;
	float4	EmvColor : COLOR1;
	float	Opacity : TEXCOORD1;
	float2	Position : TEXCOORD2;
};

struct MiniMapInfo
{
	matrix	matWVP;
	float4	Color;
	float4	EmvColor;
	float	Opacity;
	float2	Pos;
	float   Enable;
};

StructuredBuffer<MiniMapInfo>		g_MiniMapArrayInput	: register(t31);

VS_OUTPUT_MINIMAP  MiniMapVS(VS_INPUT_MINIMAP input)
{
	VS_OUTPUT_MINIMAP	output = (VS_OUTPUT_MINIMAP)0;

	//output.ProjPos = mul(g_MiniMapArrayInput[input.InstanceID].matWVP,float4(input.Pos, 1.f));
	output.ProjPos = mul(g_MiniMapArrayInput[input.InstanceID].matWVP,float4(input.Pos, 1.f));
	output.Pos = output.ProjPos;
	output.Color = g_MiniMapArrayInput[input.InstanceID].Color;
	output.EmvColor = g_MiniMapArrayInput[input.InstanceID].EmvColor;
	output.Opacity = g_MiniMapArrayInput[input.InstanceID].Opacity;
	output.Position = g_MiniMapArrayInput[input.InstanceID].Pos;

	return output;
}

PS_OUTPUT_SINGLE MiniMapPS(VS_OUTPUT_MINIMAP input)
{
	PS_OUTPUT_SINGLE    output = (PS_OUTPUT_SINGLE)0;

	float4  BaseColor = input.Color;

	output.Color = BaseColor;

	return output;
}
