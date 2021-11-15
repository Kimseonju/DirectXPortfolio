

#include "share.fx"

/*

*/
struct VS_INPUT_COLOR
{
	// 번호를 안붙이면 0번 레지스터
	float3  Pos : POSITION;
	float4  Color : COLOR;
};

struct VS_OUTPUT_COLOR
{
	// SV는 System Value
	// Shader코드에서 리턴용으로만 사용이 되고 연산용으로 사용이 불가능
	//사용자가 여기에 넣어놓으면 최종 출력위치로 사용한다.
	//SV_POSITION는 최종출력용임 정보를 넣어놓으면 알아서 바꾼다.
	//투영공간으로 변환된 정점을 SV_POSITION레지스터에 넣어놓으면 PixelShader가 동작되기 전에
	//화면공간으로의 변환이 일어난다
	float4  Pos : SV_POSITION;
	float4  Color : COLOR;
	float2	UV	: TEXCOORD;
};

// output.Pos 의 x, y, z 에는 input.Pos의 x, y, z 가 들어가고 w에는 1.f 이 들어가게 된다.

	//최적화를 위해 월드뷰 곱한것을 아예 넘겨줘버리기
	//여기서 연산이 일어나게되면 정점수만큼 일어난다.
	//그것을 방지하기위해서 미리 곱해서 넘긴다
	//mul 행렬연산

float2 ComputeAnimation2DUV(float2 UV)
{
	if (g_Animation2DEnable == 0)
		return UV;

	if (g_Animation2DType == Animation2DFrame ||
		g_Animation2DType == Animation2DArray)
		return UV;

	float2	ResultUV;

	if (UV.x <= 0.f)
		ResultUV.x = g_vAnimation2DStartUV.x;

	else
		ResultUV.x = g_vAnimation2DEndUV.x;

	if (UV.y <= 0.f)
		ResultUV.y = g_vAnimation2DStartUV.y;

	else
		ResultUV.y = g_vAnimation2DEndUV.y;

	return ResultUV;
}

VS_OUTPUT_COLOR Standard2DColorVS(VS_INPUT_COLOR input)
{
    VS_OUTPUT_COLOR output = (VS_OUTPUT_COLOR)0;

    float3  Pos = input.Pos - g_vPivot * g_vMeshSize;

    // output.Pos 의 x, y, z 에는 input.Pos의 x, y, z 가 들어가고 w에는 1.f 이 들어가게 된다.
	float4	Color = input.Color * g_vMtrlBaseColor + g_vMtrlEmissiveColor;

	output.Color = Color;

    return output;
}


//VS로도 해도된다
//VS에서도 Color가 있어서 된다
//정점수만큼 동작한다.
//만약 사각형일때 132 123등으로 사각형 하는데
//인덱스는 6개지만 정점은 4개이므로 4번 동작한다.
PS_OUTPUT_SINGLE Standard2DColorPS(VS_OUTPUT_COLOR input)
{
	PS_OUTPUT_SINGLE    output = (PS_OUTPUT_SINGLE)0;
							//색 변경				색 발산
	output.Color = input.Color* g_vMtrlBaseColor + g_vMtrlEmissiveColor;

	return output;
}


struct VS_INPUT_UV
{
	float3  Pos : POSITION;
	float2  UV : TEXCOORD;
};

//UV는 좌표 텍셀좌표계
struct VS_OUTPUT_UV
{
	float4  Pos : SV_POSITION;
	float2  UV : TEXCOORD;
	float4	ProjPos : POSITION;
};

VS_OUTPUT_UV Standard2DTextureVS(VS_INPUT_UV input)
{
	VS_OUTPUT_UV output = (VS_OUTPUT_UV)0;

	float3  Pos = input.Pos - g_vPivot * g_vMeshSize;


	output.ProjPos = mul(float4(Pos, 1.f), g_matWVP);
	output.Pos = output.ProjPos;
	output.UV = ComputeAnimation2DUV(input.UV);
	if (g_HorizontalReverse2DEnable==1)
	{
		output.UV.x = 1 - output.UV.x;
	}

	if (g_VerticalReverse2DEnable == 1)
	{
		output.UV.y = 1 - output.UV.y;
	}
	return output;
}


PS_OUTPUT_SINGLE Standard2DTexturePS(VS_OUTPUT_UV input)
{
	PS_OUTPUT_SINGLE    output = (PS_OUTPUT_SINGLE)0;

	//UV쪽 좌표에있는 컬러값가져오기
	//UV기본값은 0~1
	float4  BaseColor = g_BaseTexture.Sample(g_AnisotropicSmp, input.UV);
	float4	EmissiveColor = g_EmissiveTexture.Sample(g_AnisotropicSmp, input.UV);

	float4	result = (float4)0.f;

	result.rgb = BaseColor.rgb * g_vMtrlBaseColor.rgb + EmissiveColor.rgb * g_vMtrlEmissiveColor.rgb;
	result.a = BaseColor.a * g_MtrlOpacity* g_vMtrlBaseColor.a;

	result = PaperBurn2D(result, input.UV);

	result = Distortion(result, input.UV, input.ProjPos);

	output.Color = result;

	return output;
}