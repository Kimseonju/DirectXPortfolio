
#include "Share.fx"

cbuffer MiniMapCBuffer : register(b10)
{
	float2	g_Size;
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
	float   Empty;
};

StructuredBuffer<MiniMapInfo>		g_MiniMapArrayInput	: register(t31);

VS_OUTPUT_MINIMAP TileMapVS(VS_INPUT_MINIMAP input)
{
	VS_OUTPUT_MINIMAP	output = (VS_OUTPUT_MINIMAP)0;

	output.ProjPos = mul(float4(input.Pos, 1.f), g_MiniMapArrayInput[input.InstanceID].matWVP);
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

	float4  BaseColor = g_BaseTexture.Sample(g_AnisotropicSmp, input.UV);
	float4	EmissiveColor = g_EmissiveTexture.Sample(g_AnisotropicSmp, input.UV);

	float4	result = (float4)0.f;

	result.rgb = BaseColor.rgb * input.Color.rgb * input.Color.a + EmissiveColor.rgb * input.EmvColor.rgb;
	result.a = BaseColor.a * input.Opacity;

	result = PaperBurn2D(result, input.UV);

	result = Distortion(result, input.UV, input.ProjPos);

	output.Color = result;

	return output;
}
