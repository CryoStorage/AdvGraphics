Shader "Custom/Specularity"
{
    Properties
    {
        _Color ("Color", Color) = (1,1,1,1)
        _MainTex ("Albedo (RGB)", 2D) = "white" {}
        _Glossiness ("Smoothness", Range(0,1)) = 0.5
        _Metallic ("Metallic", 2D) = "white" {}
        _LightPos ("Light Position", Vector) = (0, 3, 0)
        _Shininess ("Shininess", Range(0, 1)) = 0.5
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 200

        CGPROGRAM
        // Physically based Standard lighting model, and enable shadows on all light types
        #pragma surface surf Standard fullforwardshadows

        // Use shader model 3.0 target, to get nicer looking lighting
        #pragma target 3.0

        sampler2D _MainTex;

        struct Input
        {
            float2 uv_MainTex;
            float3 WorldPos;
            float3 _LightPos;
        };

        half _Glossiness;
        float2 _Metallic;
        fixed4 _Color;
        float3 _LightPos;
        float _Shininess;

        // Add instancing support for this shader. You need to check 'Enable Instancing' on materials that use the shader.
        // See https://docs.unity3d.com/Manual/GPUInstancing.html for more information about instancing.
        // #pragma instancing_options assumeuniformscaling
        UNITY_INSTANCING_BUFFER_START(Props)
            // put more per-instance properties here
        UNITY_INSTANCING_BUFFER_END(Props)

        void surf (Input IN, inout SurfaceOutputStandard o)
        {
            normalize(_WorldSpaceCameraPos - IN.WorldPos);
            half halfDir = normalize(_LightPos - IN.WorldPos + _WorldSpaceCameraPos - IN.WorldPos);
            float abs = max(0, dot(o.Normal, halfDir));
            // Albedo comes from a texture tinted by color
            fixed4 c = tex2D (_MainTex, IN.uv_MainTex) * _Color;
            float _SpecularFactor = pow(abs, _Shininess);
            o.Albedo = c.rgb;
            // Metallic and smoothness come from slider variables
            o.Metallic = _Metallic;
            o.Smoothness = _Glossiness;
            o.Alpha = c.a;
            // o.Emission = _Shininess * abs * tex2D(_Metallic, IN.uv_MainTex).rgb); 
            
        }
        ENDCG
    }
    FallBack "Diffuse"
}
