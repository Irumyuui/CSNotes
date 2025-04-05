using UnityEngine;

public class InputManager : MonoBehaviour
{
    private PlayerInput _playerInput;
    private PlayerInput.OnFootActions _onFoot;
    
    private PlayerMotor _motor;
    private PlayerLook _look;
    
    public PlayerInput.OnFootActions     OnFoot => _onFoot;
    
    // Start is called before the first frame update
    void Awake()
    {
        _playerInput = new PlayerInput();
        _onFoot = _playerInput.OnFoot;

        _motor = GetComponent<PlayerMotor>();
        _look = GetComponent<PlayerLook>();
        
        _onFoot.Jump.performed += _ => _motor.Jump();
    }

    private void FixedUpdate()
    {
        _motor.ProcessMove(_onFoot.Move.ReadValue<Vector2>());    
    }

    private void LateUpdate()
    {
        _look.ProcessLook(_onFoot.Look.ReadValue<Vector2>());
    }

    private void OnEnable()
    {
        _onFoot.Enable();
    }

    private void OnDisable()
    {
        _onFoot.Disable();
    }
}
