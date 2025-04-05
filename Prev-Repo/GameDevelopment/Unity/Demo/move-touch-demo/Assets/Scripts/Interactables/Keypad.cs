using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Keypad : Interactable
{
    private static readonly int IsOpen = Animator.StringToHash("IsOpen");

    [SerializeField]
    private GameObject door;    
    private bool _doorOpen = false;
    
    protected override void Interact()
    {
        Debug.Log($"Interacting with {gameObject.name}");
        _doorOpen = !_doorOpen;
        door.GetComponent<Animator>().SetBool(IsOpen, _doorOpen);
    }
}
