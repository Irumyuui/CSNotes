using UnityEngine;
using UnityEngine.Serialization;

public class PlayerInteract : MonoBehaviour
{
    private Camera _cam;
    
    [SerializeField]
    private float interactDistance = 3f;
    
    [SerializeField]
    private LayerMask layerMask;
    
    private PlayrUI _playrUI;
    
    private InputManager _inputManager;
    
    private void Start()
    {
        _cam = GetComponent<PlayerLook>().cam;
        _playrUI = GetComponent<PlayrUI>();
        _inputManager = GetComponent<InputManager>();
    }

    private void Update()
    {
        // 射线
        var ray = new Ray(_cam.transform.position, _cam.transform.forward);
        Debug.DrawRay(ray.origin, ray.direction * interactDistance, Color.red);

        // 检测射线命中
        if (Physics.Raycast(ray, out var hitInfo, interactDistance, layerMask))
        {
            var interactable = hitInfo.collider.gameObject.GetComponent<Interactable>();
            if (interactable is not null)
            {
                // Debug.Log(interactable.name);

                _playrUI.UpdateText(interactable.promptMessage);
                if (_inputManager.OnFoot.Interact.triggered)
                {
                    interactable.BaseInteract();
                }
            }
        }
        else
        {
            _playrUI.UpdateText(string.Empty);
        }
    }
}
