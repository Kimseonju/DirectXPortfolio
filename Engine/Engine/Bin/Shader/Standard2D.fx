

#include "share.fx"

/*

*/
struct VS_INPUT_COLOR
{
	// ��ȣ�� �Ⱥ��̸� 0�� ��������
	float3  Pos : POSITION;
	float4  Color : COLOR;
};

struct VS_OUTPUT_COLOR
{
	// SV�� System Value
	// Shader�ڵ忡�� ���Ͽ����θ� ����� �ǰ� ��������� ����� �Ұ���
	//����ڰ� ���⿡ �־������ ���� �����ġ�� ����Ѵ�.
	//SV_POSITION�� ������¿��� ������ �־������ �˾Ƽ� �ٲ۴�.
	//������������ ��ȯ�� ������ SV_POSITION�������Ϳ� �־������ PixelShader�� ���۵Ǳ� ����
	//ȭ����������� ��ȯ�� �Ͼ��
	float4  Pos : SV_POSITION;
	float4  Color : COLOR;
	float2	UV	: TEXCOORD;
};

// output.Pos �� x, y, z ���� input.Pos�� x, y, z �� ���� w���� 1.f �� ���� �ȴ�.

	//����ȭ�� ���� ����� ���Ѱ��� �ƿ� �Ѱ��������
	//���⼭ ������ �Ͼ�ԵǸ� ��������ŭ �Ͼ��.
	//�װ��� �����ϱ����ؼ� �̸� ���ؼ� �ѱ��
	//mul ��Ŀ���

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

    // output.Pos �� x, y, z ���� input.Pos�� x, y, z �� ���� w���� 1.f �� ���� �ȴ�.
	float4	Color = input.Color * g_vMtrlBaseColor + g_vMtrlEmissiveColor;

	output.Color = Color;

    return output;
}


//VS�ε� �ص��ȴ�
//VS������ Color�� �־ �ȴ�
//��������ŭ �����Ѵ�.
//���� �簢���϶� 132 123������ �簢�� �ϴµ�
//�ε����� 6������ ������ 4���̹Ƿ� 4�� �����Ѵ�.
PS_OUTPUT_SINGLE Standard2DColorPS(VS_OUTPUT_COLOR input)
{
	PS_OUTPUT_SINGLE    output = (PS_OUTPUT_SINGLE)0;
							//�� ����				�� �߻�
	output.Color = input.Color* g_vMtrlBaseColor + g_vMtrlEmissiveColor;

	return output;
}


struct VS_INPUT_UV
{
	float3  Pos : POSITION;
	float2  UV : TEXCOORD;
};

//UV�� ��ǥ �ؼ���ǥ��
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

	//UV�� ��ǥ���ִ� �÷�����������
	//UV�⺻���� 0~1
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