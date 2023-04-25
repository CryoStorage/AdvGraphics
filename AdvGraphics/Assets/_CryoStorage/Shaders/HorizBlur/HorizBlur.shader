Shader "Unlit/VertiBlur"
{
    Properties
    {
        _MainTex ("Texture", 2D) = "white" {}
        _KernelSize ("Kernel Size", Range(1, 30)) = 1
        _TextureWidth ("Texture Width", Range(0, 2048)) = 512
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 100

        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            // make fog work
            #pragma multi_compile_fog

            #include "UnityCG.cginc"

            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct v2f
            {
                float2 uv : TEXCOORD0;
                UNITY_FOG_COORDS(1)
                float4 vertex : SV_POSITION;
            };

            sampler2D _MainTex;
            float _KernelSize;
            float _TextureWidth;
            float4 _MainTex_ST;

            v2f vert (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = TRANSFORM_TEX(v.uv, _MainTex);
                UNITY_TRANSFER_FOG(o,o.vertex);
                return o;
            }

            fixed4 frag (v2f i) : SV_Target
            {
                float texelSize = 1.0 / _TextureWidth;
                fixed4 result = fixed4(0.0, 0.0, 0.0, 0.0);
                for (int j = - _KernelSize; j < _KernelSize; ++j)
                {
                    float weight = float(j);
                    fixed4 sample = tex2D(_MainTex, i.uv + fixed2(weight * texelSize, 0.0));
                    result += sample;
                }
                result /= _KernelSize * 2 + 1;
                return result;
            }
            ENDCG
        }
    }
}
