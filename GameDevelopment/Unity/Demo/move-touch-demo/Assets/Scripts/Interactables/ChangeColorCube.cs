using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChangeColorCube : Interactable
{
    private MeshRenderer _mesh;
    public Color[] colors;
    private int _colorIndex;

    private void Start()
    {
        _mesh = GetComponent<MeshRenderer>();
        _mesh.material.color = Color.red;
    }

    protected override void Interact()
    {
        _colorIndex++;
        if (_colorIndex >= colors.Length)
            _colorIndex = 0;
        _mesh.material.color = colors[_colorIndex];
    }
}