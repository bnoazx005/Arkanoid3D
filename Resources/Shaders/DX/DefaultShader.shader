#define VERTEX_ENTRY mainVS
#define PIXEL_ENTRY mainPS


#include <TDEngine2Globals.inc>


struct VertexOut
{
	float4 mPos              : SV_POSITION;
	float4 mLightPos         : POSITION1;
	float4 mWorldPos         : POSITION2;
	float4 mColor            : COLOR;
	float2 mUV               : TEXCOORD;
	float4 mNormal           : NORMAL;
	float3x3 mTangentToWorld : TEXCOORD1;
	float4 mTangentViewDir   : TEXCOORD4;
};


#program vertex

struct VertexIn
{
	float4 mPos     : POSITION0;
	float4 mColor   : COLOR0;
	float2 mUV      : TEXCOORD;
	float4 mNormal  : NORMAL;
	float4 mTangent : TANGENT;
};


VertexOut mainVS(in VertexIn input)
{
	VertexOut output;

	output.mPos      = mul(mul(ProjMat, mul(ViewMat, ModelMat)), input.mPos);
	output.mLightPos = mul(mul(SunLightMat, ModelMat), input.mPos);
	output.mWorldPos = mul(ModelMat, input.mPos);
	output.mNormal   = normalize(mul(transpose(InvModelMat), input.mNormal));
	output.mUV       = input.mUV;
	output.mColor    = input.mColor;

	float3 tangent  = normalize(mul(transpose(InvModelMat), input.mTangent));
	float3 binormal = normalize(cross(output.mNormal, tangent));

	output.mTangentToWorld = transpose(float3x3(tangent, binormal, output.mNormal.xyz));

	float3 view = CameraPosition.xyz - output.mWorldPos.xyz;
	output.mTangentViewDir = float4(dot(tangent, view), dot(view, binormal), dot(output.mNormal.xyz, view), 0.0);

	return output;
}

#endprogram

#program pixel

#include <TDEngine2ShadowMappingUtils.inc>


DECLARE_TEX2D_EX(AlbedoMap, 1);

float4 mainPS(VertexOut input): SV_TARGET0
{
	return input.mColor;
}

#endprogram
