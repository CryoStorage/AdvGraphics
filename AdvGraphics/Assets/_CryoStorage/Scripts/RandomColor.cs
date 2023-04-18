using System.Collections;
using System.Collections.Generic;
using JetBrains.Annotations;
using UnityEngine;

public class RandomColor : MonoBehaviour
{
    
    [SerializeField] private float _time;
    
    private Renderer _rend;
    private Color _color;   
    // Start is called before the first frame update
    private void Start()
    {
        Prepare();
        StartCoroutine(Randomize());
    }

    private IEnumerator Randomize()
    {
        while (true)
        {
            
            _color = Random.ColorHSV();
            _rend.material.color = _color;
            yield return new WaitForSeconds(_time);
        }
    }

    private void Prepare()
    {
        _rend = GetComponent<Renderer>();
    }
}
