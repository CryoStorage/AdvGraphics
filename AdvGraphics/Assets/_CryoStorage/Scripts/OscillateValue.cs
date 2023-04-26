using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OscillateValue : MonoBehaviour
{
    private Renderer _rend;
    private Material _mat;
    // Start is called before the first frame update
    void Start()
    {
        Prepare();
    }

    // Update is called once per frame
    void Update()
    {
        float blendValue = Mathf.Sin(Time.time) * .5f + .5f;
        _mat.SetFloat("_blendValue", blendValue);
    }
    
    private void Prepare()
    {
        _rend = GetComponent<Renderer>();
        _mat = _rend.material;

    }
}
