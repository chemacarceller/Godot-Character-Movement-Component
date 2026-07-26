#ifndef CHARACTER_MOVEMENT_COMPONENT_H
#define CHARACTER_MOVEMENT_COMPONENT_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/kinematic_collision3d.hpp>
#include <godot_cpp/classes/rigid_body3d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/vector3.hpp>

// Using the godot namespace to avoid prefixing all Godot classes with 'godot::'
using namespace godot;

// We indicate that the struct CharacterMovementData is defined after
class CharacterMovementData;

// Basic Character Movement Component
//
// That is a Movement Component to be attached as a child to a Pawn, Character built as a CharacterBody3D
//
// The parent object (Character, Pawn) must have mandatory an Node3D Armature (MeshInstance3D, Skeleton3D) to be rotated
// and a Node3D (mostly a CameraController but not mandatory) that indicates the Character Forward Vector
// and should have a mass needed for the pushing action
//
// The Movement Component receives the left, right, front, rear, jump InputAction as String
// In an advanced version this could change
//
// This Basic component is based in three states idle, walk, and run with fixed exported speed constant
// The transitions between this states are blended with help of accelerationSpeed and decelerationSpeed (is in reality a time indicator)
// The transitions between walk and run are made by activating the flag _isRuning using the set_isRuning() method
//
// The armature rotates blended with help of trasitionSpeed ( is also a time indicator)
//
// It can also jump with a fixed constant exported value speed
//
// Gravity is also taken into account
//

class CharacterMovementComponent : public Node {

    GDCLASS(CharacterMovementComponent, Node);

public:

    enum EVENT_TYPE {
        MOVEMENT_STATE_CHANGED,
        DIRECTION_MODE_CHANGED
    };

    // --- CHARACTERMOVEMENTCOMPONENTS ENUMS ---

    // Movement state's options
    enum MOVEMENT_STATE {
        MS_NOTDEFINED,
        IDLE,
        WALKING,
        RUNING,
        JUMPING,
        FALLING
    };

    // Different movement modes
    // ONESPEED -> the character moves only with a speed it is the MAX_SPEER that correspon with RUN_SPEED
    // The increase and decrease in speed is managed via the acceleration and deceleration, the acceleration should not be high, the deceleration can be high
    // The animation should be done bia a blending Locomotion
    // TWOSPEEDS -> there is a walk and run speed and can changed from one to another
    // There is also the acceleration and deceleration parameter to be configured
    enum MOVEMENT_MODE {
        ONESPEED,
        TWOSPEEDS
    };

    // Indicates how the change in the direction is done:
    //  CONTINUOUS : The speed is kept
    //  FIFTY : Only the fifty percent os the speed is kept
    //  RESET : The speed is reset to ZERO
    // TRANSITIONED : The speed and direction of previous speed is not modified
    enum CHANGEDIRECTION_MODE {
        CONTINOUS,
        FIFTY,
        RESET,
        TRANSITIONED
    };

    // Indicates the direction the character is moving can be used for animations
    // None means it is not moving
    enum DIRECTION_MODE {
        DM_NOTDEFINED,
        NONE,
        STRAIFLEFT,
        LEFTFOR,
        LEFTBACK,
        STRAIFRIGHT,
        RIGHTFOR,
        RIGHTBACK,
        FORWARD,
        BACKWARD
    };

private:

    //################################################################################################
    //#                               E X P O R T E D   V A R I A B L E S                            #
    //################################################################################################

    // The underscore indicates that the variable is exported

    // Property to activate or deactivate the movement
    /// Property to activate or deactivate the movement
    bool _isEnabled = true;

    // Movement mode
    /// Movement mode
    MOVEMENT_MODE _movementMode = MOVEMENT_MODE::TWOSPEEDS;
    
    // Character settings
    // Specifies the character mass for calculating the impulse force
    /// Specifies the character mass for calculating the impulse force
    float _characterMass = 75.0f;

    // Specifies the characterForceFactor for calculating the impulse force, how strong is the character
    /// Specifies the characterForceFactor for calculating the impulse force, how strong is the character
    float _characterForceFactor = 1.0f;

    // Components and properties

    // Armature is used to rotate the character but not the camera
    /// A Node3D that represents ths mesh to be rotated by this movement component
    Node3D *_armature = nullptr;

    // DirectionalObject is to set the Forward Direction
    /// A Node3D that indicates que forward vector for the movement component
    Node3D *_directionalObject = nullptr;

    // The list of collisionHulls of the character so that they are also rotated when the armature is totated.
    /// The list of collisionHulls of the character so that they are also rotated when the armature is totated.
    TypedArray<CollisionShape3D> _collisionHullsArray;

    //Indicates if the character should rotate or not, used if you want to provide with directional animations
    ///Indicates if the character should rotate or not, used if you want to provide with directional animations
    bool _characterRotation = true;

    // Input actions setting

    // Left movement input action
    /// Left movement input action
    String _leftInput = "";

    // Indicates when the pawn turns left if it should rotate
    /// Indicates when the pawn turns left if it should rotate
    bool _leftRotationEnabled = true;

    // Right movement input action
    /// Right movement input action
    String _rightInput = "";

    // Indicates when the pawn turns right if it should rotate
    /// Indicates when the pawn turns right if it should rotate
    bool _rightRotationEnabled = true ;

    // Front movement input action
    /// Front movement input action
    String _frontInput = "";

    // Indicates when the pawn turns front if it should rotate
    /// Indicates when the pawn turns front if it should rotate
    bool _frontRotationEnabled = true;

    // Rear movement input action
    /// Rear movement input action
    String _rearInput = "";

    // Indicates when the pawn turns rear if it should rotate
    /// Indicates when the pawn turns rear if it should rotate
    bool _rearRotationEnabled = true;

    // Jump input action
    /// Jump input action
    String _jumpInput = "";


    // Transition's settings
    
    // How fast the character increases speed in m/seg
    /// How fast the character increases speed in m/seg
    float _accelerationSpeed = 15.0f;
    
    // How fast the character reduces speed in m/seg
    // How fast the character reduces speed in m/seg
    float _decelerationSpeed = 15.0f;

    // How fast the character changes direction in seg
    /// How fast the character changes direction in seg
    float _transitionTime = 0.25f;

    // Change Direction mode
    /// Change Direction mode
    CHANGEDIRECTION_MODE _changeDirectionMode = CHANGEDIRECTION_MODE::FIFTY;



    // Speed settings

    // WALK SPEED
    /// WALK SPEED
    float _WALK_SPEED = 3.0f;

    // RUN SPEED
    /// RUN SPEED
    float _RUN_SPEED = 6.0f;

    // MAX SPEED used in mode ONESPEED
    /// MAX SPEED used in mode ONESPEED
    float _MAX_SPEED = 10.0f;

    // JUMP SPEED
    /// JUMP SPEED
    float _JUMP_VELOCITY = 4.2f;

    // Speed is reducing by jumping, the speed during jumping is multiply by this factor
    /// Speed is reducing by jumping, the speed during jumping is multiply by this factor
    float _SPEED_KEPT_BY_JUMPING = 0.4f;

    // Speed is reducing by falling, the speed during falling is multiply by this factor
    /// Speed is reducing by falling, the speed during falling is multiply by this factor
    float _SPEED_KEPT_BY_FALLING = 0.4f;




    // Pushing settings

    // The lowest value calculated for the massRatio between character and pushing object
    /// The lowest value calculated for the massRatio between character and pushing object
    float _minMassRatioAllowed = 0.5f;

    // The highest value calculated for the massRatio between character and pushing object
    /// The highest value calculated for the massRatio between character and pushing object
    float _maxMassRatioAllowed = 30.0f;






    // --- INTERNAL / PRIVATE VARIABLES ---

    // myCharacter without access outside because is the ParentActor
    CharacterBody3D *myCharacter = nullptr;


    // State of the Character's movement used typically in animation tree
    MOVEMENT_STATE movementState = MOVEMENT_STATE::IDLE;
    MOVEMENT_STATE movementStatePrev = MOVEMENT_STATE::MS_NOTDEFINED;


    // State of the Character's direction movement used typically in animation tree
    DIRECTION_MODE directionMode = DIRECTION_MODE::NONE;
    DIRECTION_MODE directionModePrev = DIRECTION_MODE::DM_NOTDEFINED;


    // speed accesible from outside get and set method
    // oldSpeed is the speed before a speed change, it is used to know the difference in a speed change for the right transition time
    float oldSpeed = 0.0f;
    float speed = isRuning ? _RUN_SPEED : _WALK_SPEED;


    // This variable indicates if we are in front of a direction change and the speed should be mantained
    // Detected comparing previos direction with actual direction
    // The changeDirection is disable when the character stops, in this case the speed should be increased or reduced by the accelerationSpeed decelerationSpeed
    bool changedDirection = false;


    // Flags indicating different states of the movementcomponent
    // _isRuning indicates if the character is running or not at this momment
    // _isWalking indicates if the character is walking or not at this momment
    // isRunOrWalk indicates the state of avancing state true is Run, false is Walk

    bool isRunOrWalk = false;
    bool isRuning = false;
    bool isWalking = false;

    //Indicates if the character is moving, the opposite of idle
    bool isMoving = false;

    // isPushing indicates it is pushing something not used as a movement state jet
    bool isPushing = false;

    // isJumping indicates it is in the jumping process, in this case it is moving
    bool isJumping = false;

    // Jumpkeypressed indicates that the jump key is pressed while on floor
    bool JumpKeyPressed = false;

    // _isFalling indicates it is in the falling process, in this case it is moving
    bool isFalling = false;

    // isDoingRotation indicates it is doing the rotation
    bool isDoingRotation = false;

    // inputDir : Vector generated from the inputs needed to character change
    // and the previous input, used to detect a direction change
    Vector2 inputDir = Vector2(0.0f, 0.0f);
    Vector3 prevDirection = Vector3(0.0f, 0.0f, 0.0f);

    // Stores the actual direction
    Vector3 direction = Vector3(0.0f, 0.0f, 0.0f);
  
    // Flags indicating if the input actions exist
    bool existFrontInput = false;
    bool existRearInput = false;
    bool existLeftInput = false;
    bool existRightInput = false;
    bool existJumpInput = false;

    // Control to simulate the "await" coroutine in C++
    Node3D *armatureComponentTarget = nullptr;
    float rotOldAngle = 0.0f;
    float rotNewAngle = 0.0f;
    float rotStep = 0.0f;

    // Internal variable storing the offsets of each collision shape relative to the armature, calculated in _ready()
    TypedArray<float> collisionHullsArrayOffset = godot::TypedArray<float>();

    float accelerationTime = _WALK_SPEED / _accelerationSpeed;
    float decelerationTime = _WALK_SPEED / _decelerationSpeed; 

    // --- INTERNAL METHODS ---

    void pushAwwayRigidbody();
    void rotateArmature(Node3D *p_armature, float p_current_rot, float p_target_rot, double p_delta);
    void process_armature_rotation(double p_delta);

protected:
    static void _bind_methods();
    void _validate_property(PropertyInfo &p_property) const;

public:
    CharacterMovementComponent();
    ~CharacterMovementComponent();

    // Godot lifecycle
    void _notification(int p_what);
    void _ready() override;
    void _physics_process(double delta) override;

    // --- GETTERS & SETTERS (EXPORTED PROPERTIES) ---

    void set_enabled(const bool value) { _isEnabled = value; }
    bool is_enabled() const { return _isEnabled; }
    void set_movementMode(const MOVEMENT_MODE value) { _movementMode = value; notify_property_list_changed(); }
    MOVEMENT_MODE get_movementMode() const { return _movementMode; }


    void set_characterMass(const float value) { _characterMass = value; }
    float get_characterMass() const { return _characterMass; }
    void set_characterForceFactor(const float value) { _characterForceFactor = value; }
    float get_characterForceFactor() const { return _characterForceFactor; }


    void set_armature(Node3D *value) { _armature = value; }
    Node3D *get_armature() const { return _armature; }
    void set_directionalObject(Node3D *value) { _directionalObject = value; }
    Node3D *get_directionalObject() const { return _directionalObject; }
    void set_collisionHullsArray(const TypedArray<CollisionShape3D> value) { _collisionHullsArray = value; }
    TypedArray<CollisionShape3D> get_collisionHullsArray() const { return _collisionHullsArray; }
    void set_characterRotation(const bool value) { _characterRotation = value; }
    bool get_characterRotation() const { return _characterRotation; }


    void set_leftInput(const String value) { _leftInput = value; }
    String get_leftInput() const { return _leftInput; }
    void set_leftRotationEnabled(const bool value) { _leftRotationEnabled = value; }
    bool get_leftRotationEnabled() const { return _leftRotationEnabled; }
    void set_rightInput(const String value) { _rightInput = value; }
    String get_rightInput() const { return _rightInput; }
    void set_rightRotationEnabled(const bool value) { _rightRotationEnabled = value; }
    bool get_rightRotationEnabled() const { return _rightRotationEnabled; }
    void set_frontInput(const String value) { _frontInput = value; }
    String get_frontInput() const { return _frontInput; }
    void set_frontRotationEnabled(const bool value) { _frontRotationEnabled = value; }
    bool get_frontRotationEnabled() const { return _frontRotationEnabled; }
    void set_rearInput(const String value) { _rearInput = value; }
    String get_rearInput() const { return _rearInput; }
    void set_rearRotationEnabled(const bool value) { _rearRotationEnabled = value; }
    bool get_rearRotationEnabled() const { return _rearRotationEnabled; }
    void set_jumpInput(const String value) { _jumpInput = value; }
    String get_jumpInput() const { return _jumpInput; }


    void set_accelerationSpeed(const float value) { _accelerationSpeed = value; accelerationTime = (get_isRuning() ? _RUN_SPEED : _WALK_SPEED) / _accelerationSpeed; }
    float get_accelerationSpeed() const { return _accelerationSpeed; }
    void set_decelerationSpeed(const float value) { _decelerationSpeed = value; decelerationTime = (get_isRuning() ? _RUN_SPEED : _WALK_SPEED) / _decelerationSpeed; }
    float get_decelerationSpeed() const { return _decelerationSpeed; }
    void set_transitionTime(const float value) { _transitionTime = value; }
    float get_transitionTime() const { return _transitionTime; }
    void set_changeDirectionMode(const CHANGEDIRECTION_MODE value) { _changeDirectionMode = value; notify_property_list_changed(); }
    CHANGEDIRECTION_MODE get_changeDirectionMode() const { return _changeDirectionMode; }


    void set_walk_speed(const float value) { _WALK_SPEED = value; }
    float get_walk_speed() const { return _WALK_SPEED; }
    void set_run_speed(const float value) { _RUN_SPEED = value; }
    float get_run_speed() const { return _RUN_SPEED; }
    void set_max_speed(const float value) { _MAX_SPEED = value; _RUN_SPEED = _MAX_SPEED; set_isRunOrWalk(true); }
    float get_max_speed() const { return _MAX_SPEED; }
    void set_jump_velocity(const float value) { _JUMP_VELOCITY = value; }
    float get_jump_velocity() const { return _JUMP_VELOCITY; }
    void set_speed_kept_by_jumping(const float value) { _SPEED_KEPT_BY_JUMPING = value; }
    float get_speed_kept_by_jumping() const { return _SPEED_KEPT_BY_JUMPING; }
    void set_speed_kept_by_falling(const float value) { _SPEED_KEPT_BY_FALLING = value; }
    float get_speed_kept_by_falling() const { return _SPEED_KEPT_BY_FALLING; }


    void set_minMassRatioAllowed(const float value) { _minMassRatioAllowed = value; }
    float get_minMassRatioAllowed() const { return _minMassRatioAllowed; }
    void set_maxMassRatioAllowed(const float value) { _maxMassRatioAllowed = value; }
    float get_maxMassRatioAllowed() const { return _maxMassRatioAllowed; }




    // --- PUBLIC API (TRADITIONAL GETTERS/SETTERS) ---

    MOVEMENT_STATE get_movementState() const { return movementState; }
    void set_movementState(const MOVEMENT_STATE value) { movementState = value; }
    DIRECTION_MODE get_directionMode() const { return directionMode; }
    void set_directionMode(const DIRECTION_MODE value) { directionMode = value; }

    float get_speed() const { return speed; }
    void set_speed(float value) { speed = value; }

    bool get_isRunOrWalk() const { return isRunOrWalk; }
    void set_isRunOrWalk(bool value) {
        isRuning = false;
        isWalking = false;
        isRunOrWalk = value;
        
        // if the mode is ONESPEED pnly Run is possible
        if (_movementMode == MOVEMENT_MODE::ONESPEED) isRunOrWalk = true;

        // Setting the state of isRuning isWalking isJumping and isFalling depending on isRunOrWalk
        if (isRunOrWalk && isMoving == true ) set_isRuning(true);
        if (! isRunOrWalk && isMoving == true ) set_isWalking(true);
    }

    bool get_isRuning() const { return isRuning; }
    void set_isRuning(bool value) {
        isRuning = value;
        isRunOrWalk = value;
        if (value == true) {
            isMoving = true;
            isWalking = false;
            set_accelerationSpeed(get_accelerationSpeed());
            set_decelerationSpeed(get_decelerationSpeed());
        } else { }
    }
    bool get_isWalking() const { return isWalking; }
    void set_isWalking(bool value) {
        isWalking = value;
        isRunOrWalk = ! value;
        if (value == true) {
            isMoving = true;
            isRuning = false; 
            set_accelerationSpeed(get_accelerationSpeed());
            set_decelerationSpeed(get_decelerationSpeed());
            if (_movementMode == MOVEMENT_MODE::ONESPEED) {
                isWalking = false; 
                isRuning = true; 
                isRunOrWalk = true;
            }
        } else {   }
    }
    bool get_isMoving() const { return isMoving; }
    void set_isMoving(bool value) { 
        isMoving = value; 
        if (value == false) {
            isWalking = false;
            isRuning = false;
        } else {  
            if (isRunOrWalk) set_isRuning(true);
            else set_isWalking(true);
        }
    }
    bool get_isPushing() const { return isPushing; }
    void set_isPushing(bool value) { isPushing = value; }
    bool get_isFalling() const { return isFalling; }
    void set_isFalling(bool value) { 
        isFalling = value; 
        if (value == true) {
            isJumping = false;
            isMoving = false;
        } else {  }
    }
    bool get_isJumping() const { return isJumping; }
    void set_isJumping(bool value) { 
        isJumping = value; 
        if (value == true) {
            isFalling = false;
            isMoving = false;
        } else {     }
    }
    bool get_isDoingRotation() const { return isDoingRotation; }
    void set_isDoingRotation(bool value) { isDoingRotation = value; }

    Vector2 get_inputDir() const { return inputDir; }
    void set_inputDir(Vector2 value) { inputDir = value; }

    Vector3 get_direction() const { return direction; }
    void set_direction(Vector3 value) { direction = value; }

    // --- CONTEXT MANAGEMENT ---
    Ref<CharacterMovementData> get_context();
    void set_context(const Ref<CharacterMovementData> &p_context);

    // Additional public methods
    void stop_movement();
    void start_movement();
};


VARIANT_ENUM_CAST(CharacterMovementComponent::MOVEMENT_STATE);
VARIANT_ENUM_CAST(CharacterMovementComponent::MOVEMENT_MODE);
VARIANT_ENUM_CAST(CharacterMovementComponent::CHANGEDIRECTION_MODE);
VARIANT_ENUM_CAST(CharacterMovementComponent::DIRECTION_MODE);
VARIANT_ENUM_CAST(CharacterMovementComponent::EVENT_TYPE);




// Definition of the CharacterMovementData structure, which creates a context for this movement component so it can be transferred between characters.
class CharacterMovementData : public RefCounted {

    GDCLASS(CharacterMovementData, RefCounted);

    protected:
    
        static void _bind_methods();

    public :

        CharacterMovementData();
        ~CharacterMovementData();

        CharacterMovementComponent::MOVEMENT_STATE movementState = CharacterMovementComponent::MOVEMENT_STATE::IDLE;
        CharacterMovementComponent::DIRECTION_MODE directionMode = CharacterMovementComponent::DIRECTION_MODE::NONE;
        CharacterMovementComponent::CHANGEDIRECTION_MODE changeDirectionMode = CharacterMovementComponent::CHANGEDIRECTION_MODE::FIFTY;
    
        bool isRuning = false;
        bool isMoving = false;
        bool isPushing = false;
        bool isJumping = false;
        bool isWalking = false;
        bool JumpKeyPressed = false;
        bool isFalling = false;
        bool isDoingRotation = false;
    
        Vector2 inputDir = Vector2(0.0f, 0.0f);
        Vector3 prevDirection = Vector3(0.0f, 0.0f, 0.0f);
        Vector3 direction = Vector3(0.0f, 0.0f, 0.0f);
};


#endif