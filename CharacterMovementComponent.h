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

    // --- CHARACTERMOVEMENTCOMPONENTS ENUMS ---

    // Movement state's options
    enum MOVEMENT_STATE {
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
    bool _isEnabled;

    // Movement mode
    /// Movement mode
    MOVEMENT_MODE _movementMode;
    
    // Character settings
    // Specifies the character mass for calculating the impulse force
    /// Specifies the character mass for calculating the impulse force
    float _characterMass;

    // Specifies the characterForceFactor for calculating the impulse force, how strong is the character
    /// Specifies the characterForceFactor for calculating the impulse force, how strong is the character
    float _characterForceFactor;

    // Components and properties

    // Armature is used to rotate the character but not the camera
    /// A Node3D that represents ths mesh to be rotated by this movement component
    Node3D *_armature;

    // DirectionalObject is to set the Forward Direction
    /// A Node3D that indicates que forward vector for the movement component
    Node3D *_directionalObject;

    // The list of collisionHulls of the character so that they are also rotated when the armature is totated.
    /// The list of collisionHulls of the character so that they are also rotated when the armature is totated.
    TypedArray<CollisionShape3D> _collisionHullsArray;

    //Indicates if the character should rotate or not, used if you want to provide with directional animations
    ///Indicates if the character should rotate or not, used if you want to provide with directional animations
    bool _characterRotation;

    // Input actions setting

    // Left movement input action
    /// Left movement input action
    String _leftInput;

    // Indicates when the pawn turns left if it should rotate
    /// Indicates when the pawn turns left if it should rotate
    bool _leftRotationEnabled;

    // Right movement input action
    /// Right movement input action
    String _rightInput;

    // Indicates when the pawn turns right if it should rotate
    /// Indicates when the pawn turns right if it should rotate
    bool _rightRotationEnabled;

    // Front movement input action
    /// Front movement input action
    String _frontInput;

    // Indicates when the pawn turns front if it should rotate
    /// Indicates when the pawn turns front if it should rotate
    bool _frontRotationEnabled;

    // Rear movement input action
    /// Rear movement input action
    String _rearInput;

    // Indicates when the pawn turns rear if it should rotate
    /// Indicates when the pawn turns rear if it should rotate
    bool _rearRotationEnabled;

    // Jump input action
    /// Jump input action
    String _jumpInput;


    // Transition's settings
    
    // How fast the character increases speed in m/seg
    /// How fast the character increases speed in m/seg
    float _accelerationSpeed;
    
    // How fast the character reduces speed in m/seg
    // How fast the character reduces speed in m/seg
    float _decelerationSpeed;

    // How fast the character changes direction in seg
    /// How fast the character changes direction in seg
    float _transitionTime;

    // Change Direction mode
    /// Change Direction mode
    CHANGEDIRECTION_MODE _changeDirectionMode;



    // Speed settings

    // WALK SPEED
    /// WALK SPEED
    float _WALK_SPEED;

    // RUN SPEED
    /// RUN SPEED
    float _RUN_SPEED;

    // MAX SPEED used in mode ONESPEED
    /// MAX SPEED used in mode ONESPEED
    float _MAX_SPEED;

    // JUMP SPEED
    /// JUMP SPEED
    float _JUMP_VELOCITY;

    // Speed is reducing by jumping, the speed during jumping is multiply by this factor
    /// Speed is reducing by jumping, the speed during jumping is multiply by this factor
    float _SPEED_KEPT_BY_JUMPING;

    // Speed is reducing by falling, the speed during falling is multiply by this factor
    /// Speed is reducing by falling, the speed during falling is multiply by this factor
    float _SPEED_KEPT_BY_FALLING;




    // Pushing settings

    // The lowest value calculated for the massRatio between character and pushing object
    /// The lowest value calculated for the massRatio between character and pushing object
    float _minMassRatioAllowed;

    // The highest value calculated for the massRatio between character and pushing object
    /// The highest value calculated for the massRatio between character and pushing object
    float _maxMassRatioAllowed;






    // --- INTERNAL / PRIVATE VARIABLES ---

    // myCharacter without access outside because is the ParentActor
    CharacterBody3D *myCharacter;


    // State of the Character's movement used typically in animation tree
    MOVEMENT_STATE movementState;


    // State of the Character's direction movement used typically in animation tree
    DIRECTION_MODE directionMode;


    // speed accesible from outside get and set method
    // oldSpeed is the speed before a speed change, it is used to know the difference in a speed change for the right transition time
    float oldSpeed;
    float speed;


    // This variable indicates if we are in front of a direction change and the speed should be mantained
    // Detected comparing previos direction with actual direction
    // The changeDirection is disable when the character stops, in this case the speed should be increased or reduced by the accelerationSpeed decelerationSpeed
    bool changedDirection;


    // Flags indicating different states of the movementcomponent
    // _isRuning indicates if the character is running or not
    // Two possibilities Runing or Walking. They are always opposites; it indicates whether, in case of movement, it would move by walking or running.
    bool isRuning;
    bool isWalking;

    //Indicates if the character is moving or idle
    bool isMoving;

    // isPushing indicates it is pushing something not used as a movement state jet
    bool isPushing;

    
    // isJumping indicates it is in the jumping process
    bool isJumping;

    // Jumpkeypressed indicates that the jump key is pressed while on floor
    bool JumpKeyPressed;

    // _isFalling indicates it is in the falling process
    bool isFalling;

    // isDoingRotation indicates it is doing the rotation
    bool isDoingRotation;

    // inputDir : Vector generated from the inputs needed to character change
    // and the previous input, used to detect a direction change
    Vector2 inputDir;
    Vector3 prevDirection;

    // Stores the actual direction
    Vector3 direction;
  
    // Flags indicating if the input actions exist
    bool existFrontInput;
    bool existRearInput;
    bool existLeftInput;
    bool existRightInput;
    bool existJumpInput;

    // Control to simulate the "await" coroutine in C++
    Node3D *armatureComponentTarget;
    float rotOldAngle;
    float rotNewAngle;
    float rotStep;

    // Internal variable storing the offsets of each collision shape relative to the armature, calculated in _ready()
    TypedArray<float> collisionHullsArrayOffset; 

    float accelerationTime; 
    float decelerationTime; 

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

    // Ciclo de vida de Godot
    void _notification(int p_what);
    void _ready() override;
    void _physics_process(double delta) override;

    // --- GETTERS & SETTERS (EXPORTED PROPERTIES) ---

    void set_enabled(const bool value);
    bool is_enabled() const;

    void set_movementMode(const MOVEMENT_MODE value);
    MOVEMENT_MODE get_movementMode() const;



    void set_characterMass(const float value);
    float get_characterMass() const;

    void set_characterForceFactor(const float value);
    float get_characterForceFactor() const;



    void set_armature(Node3D *value);
    Node3D *get_armature() const;

    void set_directionalObject(Node3D *value);
    Node3D *get_directionalObject() const;

    void set_collisionHullsArray(const TypedArray<CollisionShape3D> value);
    TypedArray<CollisionShape3D> get_collisionHullsArray() const;

    void set_characterRotation(const bool value);
    bool get_characterRotation() const;



    void set_leftInput(const String value);
    String get_leftInput() const;

    void set_leftRotationEnabled(const bool value);
    bool get_leftRotationEnabled() const;

    void set_rightInput(const String value);
    String get_rightInput() const;

    void set_rightRotationEnabled(const bool value);
    bool get_rightRotationEnabled() const;

    void set_frontInput(const String value);
    String get_frontInput() const;

    void set_frontRotationEnabled(const bool value);
    bool get_frontRotationEnabled() const;

    void set_rearInput(const String value);
    String get_rearInput() const;

    void set_rearRotationEnabled(const bool value);
    bool get_rearRotationEnabled() const;

    void set_jumpInput(const String value);
    String get_jumpInput() const;



    void set_accelerationSpeed(const float value);
    float get_accelerationSpeed() const;

    void set_decelerationSpeed(const float value);
    float get_decelerationSpeed() const;

    void set_transitionTime(const float value);
    float get_transitionTime() const;

    void set_changeDirectionMode(const CHANGEDIRECTION_MODE value);
    CHANGEDIRECTION_MODE get_changeDirectionMode() const;




    void set_walk_speed(const float value);
    float get_walk_speed() const;

    void set_run_speed(const float value);
    float get_run_speed() const;

    void set_max_speed(const float value);
    float get_max_speed() const;

    void set_jump_velocity(const float value);
    float get_jump_velocity() const;

    void set_speed_kept_by_jumping(const float value);
    float get_speed_kept_by_jumping() const;

    void set_speed_kept_by_falling(const float value);
    float get_speed_kept_by_falling() const;




    void set_minMassRatioAllowed(const float value);
    float get_minMassRatioAllowed() const;

    void set_maxMassRatioAllowed(const float value);
    float get_maxMassRatioAllowed() const;






    // --- PUBLIC API (TRADITIONAL GETTERS/SETTERS) ---

    MOVEMENT_STATE get_movementState() const;
    DIRECTION_MODE get_directionMode() const;

    float get_speed() const;
    void set_speed(float value);


    bool get_isRuning() const;
    void set_isRuning(bool value);

    bool get_isWalking() const;
    void set_isWalking(bool value);
    
    bool get_isMoving() const;
    void set_isMoving(bool value);
    
    bool get_isPushing() const;
    void set_isPushing(bool value);
    
    bool get_isFalling() const;
    void set_isFalling(bool value);
    
    bool get_isJumping() const;
    void set_isJumping(bool value);
    
    bool get_isDoingRotation() const;
    void set_isDoingRotation(bool value);

    Vector2 get_inputDir() const;
    void set_inputDir(Vector2 value);

    Vector3 get_direction() const;
    void set_direction(Vector3 value);

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
