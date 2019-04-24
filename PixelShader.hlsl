struct DirectionalLight
{
	float4 AmbientColor;
	float4 DiffuseColor;
	float3 Direction;
};

cbuffer externalData : register(b0)
{
	DirectionalLight light;
	DirectionalLight light_two;
	float3 CameraPosition;
};

Texture2D DiffuseTexture : register(t0);
Texture2D NormalTexture : register(t1);
SamplerState BasicSampler : register(s0);

// Struct representing the data we expect to receive from earlier pipeline stages
// - Should match the output of our corresponding vertex shader
// - The name of the struct itself is unimportant
// - The variable names don't have to match other shaders (just the semantics)
// - Each variable must have a semantic, which defines its usage
struct VertexToPixel
{
	// Data type
	//  |
	//  |   Name          Semantic
	//  |    |                |
	//  v    v                v
	float4 position		 : SV_POSITION;
	float2 uv			 : TEXCOORD;
	float3 normal		 : NORMAL;
	float3 tangent		 : TANGENT;
	float3 worldPosition : POSITION;
};



float4 calculateLight(float3 t_normal, DirectionalLight t_light)
{
	float3 lightNormDir = normalize(-t_light.Direction);
	float NdotL = saturate(dot(t_normal, lightNormDir));
	return t_light.AmbientColor + t_light.DiffuseColor * NdotL;
}


// --------------------------------------------------------
// The entry point (main method) for our pixel shader
// 
// - Input is the data coming down the pipeline (defined by the struct)
// - Output is a single color (float4)
// - Has a special semantic (SV_TARGET), which means 
//    "put the output of this into the current render target"
// - Named "main" because that's the default the shader compiler looks for
// --------------------------------------------------------
float4 main(VertexToPixel input) : SV_TARGET
{
	input.normal = normalize(input.normal);
	input.tangent = normalize(input.tangent);
	float3 normalFromMap = NormalTexture.Sample(BasicSampler, input.uv).rgb*2 - 1;

	// Convert from Tangent space to World Space
	float3 N = input.normal;
	// ensure tangent is 90 degrees from normal
	float3 T = normalize(input.tangent - N * dot(input.tangent, N));
	float3 B = cross(T, N);
	float3x3 TBN = float3x3(T, B, N);

	input.normal = normalize(mul(normalFromMap, TBN));
	float4 lightColor = calculateLight(input.normal, light) + calculateLight(input.normal, light_two);
	float4 textureColor = DiffuseTexture.Sample(BasicSampler, input.uv);
	// Just return the input color
	// - This color (like most values passing through the rasterizer) is 
	//   interpolated for each pixel between the corresponding vertices 
	//   of the triangle we're rendering
	return float4(lightColor* textureColor.rgb, 1);
}