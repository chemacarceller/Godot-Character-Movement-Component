#include "CharacterMovementComponent.h"

// Using the godot namespace to avoid prefixing all Godot classes with 'godot::'
using namespace godot;

// The _bind_methods method is required even if it is empty

void CharacterMovementData::_bind_methods() {}

void CharacterMovementComponent::_bind_methods() {

    // Record of methods for Godot to see
    ClassDB::bind_method(D_METHOD("set_enabled", "value"), &CharacterMovementComponent::set_enabled);
    ClassDB::bind_method(D_METHOD("is_enabled"), &CharacterMovementComponent::is_enabled);

    ClassDB::bind_method(D_METHOD("set_movementMode", "value"), &CharacterMovementComponent::set_movementMode);
    ClassDB::bind_method(D_METHOD("get_movementMode"), &CharacterMovementComponent::get_movementMode);

    ClassDB::bind_method(D_METHOD("set_characterMass", "value"), &CharacterMovementComponent::set_characterMass);
    ClassDB::bind_method(D_METHOD("get_characterMass"), &CharacterMovementComponent::get_characterMass);
    ClassDB::bind_method(D_METHOD("set_characterForceFactor", "value"), &CharacterMovementComponent::set_characterForceFactor);
    ClassDB::bind_method(D_METHOD("get_characterForceFactor"), &CharacterMovementComponent::get_characterForceFactor);

    ClassDB::bind_method(D_METHOD("set_armature", "value"), &CharacterMovementComponent::set_armature);
    ClassDB::bind_method(D_METHOD("get_armature"), &CharacterMovementComponent::get_armature);
    ClassDB::bind_method(D_METHOD("set_directionalObject", "value"), &CharacterMovementComponent::set_directionalObject);
    ClassDB::bind_method(D_METHOD("get_directionalObject"), &CharacterMovementComponent::get_directionalObject);
    ClassDB::bind_method(D_METHOD("set_collisionHullsArray", "value"), &CharacterMovementComponent::set_collisionHullsArray);
    ClassDB::bind_method(D_METHOD("get_collisionHullsArray"), &CharacterMovementComponent::get_collisionHullsArray);
    ClassDB::bind_method(D_METHOD("set_characterRotation", "value"), &CharacterMovementComponent::set_characterRotation);
    ClassDB::bind_method(D_METHOD("get_characterRotation"), &CharacterMovementComponent::get_characterRotation);

    ClassDB::bind_method(D_METHOD("set_leftInput", "value"), &CharacterMovementComponent::set_leftInput);
    ClassDB::bind_method(D_METHOD("get_leftInput"), &CharacterMovementComponent::get_leftInput);
    ClassDB::bind_method(D_METHOD("set_leftRotationEnabled", "value"), &CharacterMovementComponent::set_leftRotationEnabled);
    ClassDB::bind_method(D_METHOD("get_leftRotationEnabled"), &CharacterMovementComponent::get_leftRotationEnabled);
    ClassDB::bind_method(D_METHOD("set_rightInput", "value"), &CharacterMovementComponent::set_rightInput);
    ClassDB::bind_method(D_METHOD("get_rightInput"), &CharacterMovementComponent::get_rightInput);
    ClassDB::bind_method(D_METHOD("set_rightRotationEnabled", "value"), &CharacterMovementComponent::set_rightRotationEnabled);
    ClassDB::bind_method(D_METHOD("get_rightRotationEnabled"), &CharacterMovementComponent::get_rightRotationEnabled);
    ClassDB::bind_method(D_METHOD("set_frontInput", "value"), &CharacterMovementComponent::set_frontInput);
    ClassDB::bind_method(D_METHOD("get_frontInput"), &CharacterMovementComponent::get_frontInput);
    ClassDB::bind_method(D_METHOD("set_frontRotationEnabled", "value"), &CharacterMovementComponent::set_frontRotationEnabled);
    ClassDB::bind_method(D_METHOD("get_frontRotationEnabled"), &CharacterMovementComponent::get_frontRotationEnabled);
    ClassDB::bind_method(D_METHOD("set_rearInput", "value"), &CharacterMovementComponent::set_rearInput);
    ClassDB::bind_method(D_METHOD("get_rearInput"), &CharacterMovementComponent::get_rearInput);
    ClassDB::bind_method(D_METHOD("set_rearRotationEnabled", "value"), &CharacterMovementComponent::set_rearRotationEnabled);
    ClassDB::bind_method(D_METHOD("get_rearRotationEnabled"), &CharacterMovementComponent::get_rearRotationEnabled);
    ClassDB::bind_method(D_METHOD("set_jumpInput", "value"), &CharacterMovementComponent::set_jumpInput);
    ClassDB::bind_method(D_METHOD("get_jumpInput"), &CharacterMovementComponent::get_jumpInput);

    ClassDB::bind_method(D_METHOD("set_accelerationSpeed", "value"), &CharacterMovementComponent::set_accelerationSpeed);
    ClassDB::bind_method(D_METHOD("get_accelerationSpeed"), &CharacterMovementComponent::get_accelerationSpeed);
    ClassDB::bind_method(D_METHOD("set_decelerationSpeed", "value"), &CharacterMovementComponent::set_decelerationSpeed);
    ClassDB::bind_method(D_METHOD("get_decelerationSpeed"), &CharacterMovementComponent::get_decelerationSpeed);
    ClassDB::bind_method(D_METHOD("set_transitionTime", "value"), &CharacterMovementComponent::set_transitionTime);
    ClassDB::bind_method(D_METHOD("get_transitionTime"), &CharacterMovementComponent::get_transitionTime);
    ClassDB::bind_method(D_METHOD("set_changeDirectionMode", "value"), &CharacterMovementComponent::set_changeDirectionMode);
    ClassDB::bind_method(D_METHOD("get_changeDirectionMode"), &CharacterMovementComponent::get_changeDirectionMode);

    ClassDB::bind_method(D_METHOD("set_walk_speed", "value"), &CharacterMovementComponent::set_walk_speed);
    ClassDB::bind_method(D_METHOD("get_walk_speed"), &CharacterMovementComponent::get_walk_speed);
    ClassDB::bind_method(D_METHOD("set_run_speed", "value"), &CharacterMovementComponent::set_run_speed);
    ClassDB::bind_method(D_METHOD("get_run_speed"), &CharacterMovementComponent::get_run_speed);
    ClassDB::bind_method(D_METHOD("set_max_speed", "value"), &CharacterMovementComponent::set_max_speed);
    ClassDB::bind_method(D_METHOD("get_max_speed"), &CharacterMovementComponent::get_max_speed);
    ClassDB::bind_method(D_METHOD("set_jump_velocity", "value"), &CharacterMovementComponent::set_jump_velocity);
    ClassDB::bind_method(D_METHOD("get_jump_velocity"), &CharacterMovementComponent::get_jump_velocity);
    ClassDB::bind_method(D_METHOD("set_speed_kept_by_jumping", "value"), &CharacterMovementComponent::set_speed_kept_by_jumping);
    ClassDB::bind_method(D_METHOD("get_speed_kept_by_jumping"), &CharacterMovementComponent::get_speed_kept_by_jumping);
    ClassDB::bind_method(D_METHOD("set_speed_kept_by_falling", "value"), &CharacterMovementComponent::set_speed_kept_by_falling);
    ClassDB::bind_method(D_METHOD("get_speed_kept_by_falling"), &CharacterMovementComponent::get_speed_kept_by_falling);

    ClassDB::bind_method(D_METHOD("set_minMassRatioAllowed", "value"), &CharacterMovementComponent::set_minMassRatioAllowed);
    ClassDB::bind_method(D_METHOD("get_minMassRatioAllowed"), &CharacterMovementComponent::get_minMassRatioAllowed);
    ClassDB::bind_method(D_METHOD("set_maxMassRatioAllowed", "value"), &CharacterMovementComponent::set_maxMassRatioAllowed);
    ClassDB::bind_method(D_METHOD("get_maxMassRatioAllowed"), &CharacterMovementComponent::get_maxMassRatioAllowed);



    ClassDB::bind_method(D_METHOD("set_movementState", "value"), &CharacterMovementComponent::set_movementState);
    ClassDB::bind_method(D_METHOD("get_movementState"), &CharacterMovementComponent::get_movementState);
    ClassDB::bind_method(D_METHOD("set_directionMode", "value"), &CharacterMovementComponent::set_directionMode);
    ClassDB::bind_method(D_METHOD("get_directionMode"), &CharacterMovementComponent::get_directionMode);

    ClassDB::bind_method(D_METHOD("get_speed"), &CharacterMovementComponent::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "value"), &CharacterMovementComponent::set_speed);

    ClassDB::bind_method(D_METHOD("get_isRunOrWalk"), &CharacterMovementComponent::get_isRunOrWalk);
    ClassDB::bind_method(D_METHOD("set_isRunOrWalk", "value"), &CharacterMovementComponent::set_isRunOrWalk);
    ClassDB::bind_method(D_METHOD("get_isRuning"), &CharacterMovementComponent::get_isRuning);
    ClassDB::bind_method(D_METHOD("set_isRuning", "value"), &CharacterMovementComponent::set_isRuning);
    ClassDB::bind_method(D_METHOD("get_isWalking"), &CharacterMovementComponent::get_isWalking);
    ClassDB::bind_method(D_METHOD("set_isWalking", "value"), &CharacterMovementComponent::set_isWalking);
    ClassDB::bind_method(D_METHOD("get_isMoving"), &CharacterMovementComponent::get_isMoving);
    ClassDB::bind_method(D_METHOD("set_isMoving", "value"), &CharacterMovementComponent::set_isMoving);
    ClassDB::bind_method(D_METHOD("get_isPushing"), &CharacterMovementComponent::get_isPushing);
    ClassDB::bind_method(D_METHOD("set_isPushing", "value"), &CharacterMovementComponent::set_isPushing);
    ClassDB::bind_method(D_METHOD("get_isFalling"), &CharacterMovementComponent::get_isFalling);
    ClassDB::bind_method(D_METHOD("set_isFalling", "value"), &CharacterMovementComponent::set_isFalling);
    ClassDB::bind_method(D_METHOD("get_isJumping"), &CharacterMovementComponent::get_isJumping);
    ClassDB::bind_method(D_METHOD("set_isJumping", "value"), &CharacterMovementComponent::set_isJumping);
    ClassDB::bind_method(D_METHOD("get_isDoingRotation"), &CharacterMovementComponent::get_isDoingRotation);
    ClassDB::bind_method(D_METHOD("set_isDoingRotation", "value"), &CharacterMovementComponent::set_isDoingRotation);

    ClassDB::bind_method(D_METHOD("get_inputDir"), &CharacterMovementComponent::get_inputDir);
    ClassDB::bind_method(D_METHOD("set_inputDir", "value"), &CharacterMovementComponent::set_inputDir);

    ClassDB::bind_method(D_METHOD("get_direction"), &CharacterMovementComponent::get_direction);
    ClassDB::bind_method(D_METHOD("set_direction", "value"), &CharacterMovementComponent::set_direction);


    ClassDB::bind_method(D_METHOD("get_context"), &CharacterMovementComponent::get_context);
    ClassDB::bind_method(D_METHOD("set_context", "context"), &CharacterMovementComponent::set_context);


    ClassDB::bind_method(D_METHOD("stop_movement"), &CharacterMovementComponent::stop_movement);
    ClassDB::bind_method(D_METHOD("start_movement"), &CharacterMovementComponent::start_movement);


    // Exporting properties (equivalent to @export)
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "_isEnabled"), "set_enabled", "is_enabled");

    ADD_PROPERTY(PropertyInfo(Variant::INT, "_movementMode", PROPERTY_HINT_ENUM, "ONESPEED,TWOSPEEDS"), "set_movementMode", "get_movementMode");

    ADD_GROUP("Character settings", "character");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "_characterMass", PROPERTY_HINT_RANGE, "25,150"), "set_characterMass", "get_characterMass");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "_characterForceFactor", PROPERTY_HINT_RANGE, "0.1,10"), "set_characterForceFactor", "get_characterForceFactor");

    ADD_GROUP("Components and properties", "");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "_armature", PROPERTY_HINT_NODE_TYPE, "Node3D"), "set_armature", "get_armature");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "_directionalObject", PROPERTY_HINT_NODE_TYPE, "Node3D"), "set_directionalObject", "get_directionalObject");
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "_collisionHullsArray", PROPERTY_HINT_TYPE_STRING, "24/34:CollisionShape3D"), "set_collisionHullsArray", "get_collisionHullsArray");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "_characterRotation"), "set_characterRotation", "get_characterRotation");

    ADD_GROUP("Input actions setting", "");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "_leftInput"), "set_leftInput", "get_leftInput");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "_leftRotationEnabled"), "set_leftRotationEnabled", "get_leftRotationEnabled");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "_rightInput"), "set_rightInput", "get_rightInput");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "_rightRotationEnabled"), "set_rightRotationEnabled", "get_rightRotationEnabled");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "_frontInput"), "set_frontInput", "get_frontInput");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "_frontRotationEnabled"), "set_frontRotationEnabled", "get_frontRotationEnabled");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "_rearInput"), "set_rearInput", "get_rearInput");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "_rearRotationEnabled"), "set_rearRotationEnabled", "get_rearRotationEnabled");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "_jumpInput"), "set_jumpInput", "get_jumpInput");

    ADD_GROUP("Transition's settings", "");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "_accelerationSpeed", PROPERTY_HINT_RANGE, "0.1,30"), "set_accelerationSpeed", "get_accelerationSpeed");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "_decelerationSpeed", PROPERTY_HINT_RANGE, "0.1,30"), "set_decelerationSpeed", "get_decelerationSpeed");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "_transitionTime", PROPERTY_HINT_RANGE, "0.01,1"), "set_transitionTime", "get_transitionTime");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "_changeDirectionMode", PROPERTY_HINT_ENUM, "CONTINOUS,FIFTY,RESET,TRANSITIONED"), "set_changeDirectionMode", "get_changeDirectionMode");

    ADD_GROUP("Speed settings", "");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "_WALK_SPEED", PROPERTY_HINT_RANGE, "1,4"), "set_walk_speed", "get_walk_speed");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "_RUN_SPEED", PROPERTY_HINT_RANGE, "1,15"), "set_run_speed", "get_run_speed");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "_MAX_SPEED", PROPERTY_HINT_RANGE, "1,15"), "set_max_speed", "get_max_speed");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "_JUMP_VELOCITY", PROPERTY_HINT_RANGE, "1,6"), "set_jump_velocity", "get_jump_velocity");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "_SPEED_KEPT_BY_JUMPING", PROPERTY_HINT_RANGE, "0,1"), "set_speed_kept_by_jumping", "get_speed_kept_by_jumping");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "_SPEED_KEPT_BY_FALLING", PROPERTY_HINT_RANGE, "0,1"), "set_speed_kept_by_falling", "get_speed_kept_by_falling");

    ADD_GROUP("Pushing settings", "");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "_minMassRatioAllowed", PROPERTY_HINT_RANGE, "0.1,1"), "set_minMassRatioAllowed", "get_minMassRatioAllowed");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "_maxMassRatioAllowed", PROPERTY_HINT_RANGE, "1,100"), "set_maxMassRatioAllowed", "get_maxMassRatioAllowed");

    BIND_ENUM_CONSTANT(IDLE);
    BIND_ENUM_CONSTANT(WALKING);
    BIND_ENUM_CONSTANT(RUNING);
    BIND_ENUM_CONSTANT(JUMPING);
    BIND_ENUM_CONSTANT(FALLING);
    BIND_ENUM_CONSTANT(ONESPEED);
    BIND_ENUM_CONSTANT(TWOSPEEDS);
    BIND_ENUM_CONSTANT(CONTINOUS);
    BIND_ENUM_CONSTANT(FIFTY);
    BIND_ENUM_CONSTANT(RESET);
    BIND_ENUM_CONSTANT(TRANSITIONED);
    BIND_ENUM_CONSTANT(NONE);
    BIND_ENUM_CONSTANT(STRAIFLEFT);
    BIND_ENUM_CONSTANT(LEFTFOR);
    BIND_ENUM_CONSTANT(LEFTBACK);
    BIND_ENUM_CONSTANT(STRAIFRIGHT);
    BIND_ENUM_CONSTANT(RIGHTFOR);
    BIND_ENUM_CONSTANT(RIGHTBACK);
    BIND_ENUM_CONSTANT(FORWARD);
    BIND_ENUM_CONSTANT(BACKWARD);

    ADD_SIGNAL(MethodInfo("MOVEMENT_STATE_CHANGED", 
        PropertyInfo(Variant::INT, "data")
    ));
    ADD_SIGNAL(MethodInfo("DIRECTION_MODE_CHANGED", 
        PropertyInfo(Variant::INT, "data")
    ));
}


// Constructor and Destructor

// The constructor and destructor are required even if they are empty

CharacterMovementData::CharacterMovementData() {}

CharacterMovementData::~CharacterMovementData() {}

CharacterMovementComponent::CharacterMovementComponent() {}

CharacterMovementComponent::~CharacterMovementComponent() {}



void CharacterMovementComponent::_ready() {

    if (Engine::get_singleton()->is_editor_hint()) return;

    myCharacter = Object::cast_to<CharacterBody3D>(get_parent());

    if (_armature == nullptr && myCharacter != nullptr) {
        UtilityFunctions::print("CharacterMovementComponent : The Parent class " + myCharacter->get_name() + " doesn't have specified the armature component");
    }
    if (_directionalObject == nullptr && myCharacter != nullptr) {
        UtilityFunctions::print("CharacterMovementComponent : The Parent class " + myCharacter->get_name() + " doesn't have specified the directionalObject component");
    }

    InputMap *input_map = InputMap::get_singleton();
    TypedArray<StringName> actions = input_map->get_actions();
    for (int i = 0; i < actions.size(); i++) {
        String action_name = actions[i];
        if (_frontInput == action_name) existFrontInput = true;
        if (_rearInput == action_name)  existRearInput = true;
        if (_leftInput == action_name)  existLeftInput = true;
        if (_rightInput == action_name) existRightInput = true;
        if (_jumpInput == action_name)  existJumpInput = true;
    }

    if (_armature != nullptr) {
        for (int i = 0; i < _collisionHullsArray.size(); i++) {
            CollisionShape3D *collisionHull = Object::cast_to<CollisionShape3D>(_collisionHullsArray[i]);
            if (collisionHull) {
                Vector3 diff = Vector3(collisionHull->get_position().x - _armature->get_position().x, 0.0f, collisionHull->get_position().z - _armature->get_position().z);
                collisionHullsArrayOffset.append(Math::abs(diff.length()));
            }
        }
    }

    set_accelerationSpeed(get_accelerationSpeed());
    set_decelerationSpeed(get_decelerationSpeed());
    if (_movementMode == MOVEMENT_MODE::ONESPEED) set_max_speed(get_max_speed());
}

void CharacterMovementComponent::_physics_process(double delta) {
    if (Engine::get_singleton()->is_editor_hint()) return;

    float _rotationAngle = 0.0f;
    Input *input = Input::get_singleton();

     if (_isEnabled && myCharacter != nullptr) {

        if (existJumpInput) {

            // && myCharacter->is_on_floor()
            if (input->is_action_just_pressed(_jumpInput)) {
                set_isJumping(true);
                JumpKeyPressed = true;
                Vector3 velocity = myCharacter->get_velocity();
                velocity.y = _JUMP_VELOCITY;
                myCharacter->set_velocity(velocity);
            } else {
                JumpKeyPressed = false;
                if (myCharacter->is_on_floor()) { 
                    set_isJumping(false);
                    if (isMoving) {
                        if (isRunOrWalk) set_isRuning(true); 
                        else set_isWalking(true); 
                    }
                } 
            }
        } 
  
        if (! myCharacter->is_on_floor()) {
            if (! JumpKeyPressed) {
                Vector3 velocity = myCharacter->get_velocity();
                velocity += myCharacter->get_gravity() * (float)delta;
                myCharacter->set_velocity(velocity);
                if (! isJumping) set_isFalling(true);
            }
        } else {
            set_isFalling(false);
            if (isMoving) {
                if (isRunOrWalk) set_isRuning(true); 
                else set_isWalking(true); 
            }
        }

        if (! isJumping && ! isFalling) {
             if (! existLeftInput || ! existRightInput) {
                if (existFrontInput && existRearInput) {
                    set_inputDir(Vector2(0.0f, 1.0f) * (input->get_action_strength(_rearInput) - input->get_action_strength(_frontInput)));
                } else {
                    if (existFrontInput) {
                        set_inputDir(Vector2(0.0f, -1.0f) * input->get_action_strength(_frontInput));
                    } else {
                        set_inputDir(Vector2(0.0f, 0.0f));
                    }
                }
            } else if (! existFrontInput || ! existRearInput) {
                set_inputDir(Vector2(1.0f, 0.0f) * (input->get_action_strength(_rightInput) - input->get_action_strength(_leftInput)));                
            } else {
                set_inputDir(input->get_vector(_leftInput, _rightInput, _frontInput, _rearInput));
            }

            if (inputDir == Vector2(1.0f, 0.0f)){ 
                directionMode = DIRECTION_MODE::STRAIFRIGHT;
                if (directionMode != directionModePrev) {
                    directionModePrev = directionMode;
                    emit_signal("DIRECTION_MODE_CHANGED", directionMode);
                }
            }
            else if (inputDir == Vector2(-1.0f, 0.0f)) { 
                directionMode = DIRECTION_MODE::STRAIFLEFT;
                if (directionMode != directionModePrev) {
                    directionModePrev = directionMode;
                    emit_signal("DIRECTION_MODE_CHANGED", directionMode);
                }
            }
            else if (inputDir == Vector2(0.0f, 1.0f))  { 
                directionMode = DIRECTION_MODE::BACKWARD;
                if (directionMode != directionModePrev) {
                    directionModePrev = directionMode;
                    emit_signal("DIRECTION_MODE_CHANGED", directionMode);
                }
            }
            else if (inputDir == Vector2(0.0f, -1.0f)) {
                directionMode = DIRECTION_MODE::FORWARD;
                if (directionMode != directionModePrev) {
                    directionModePrev = directionMode;
                    emit_signal("DIRECTION_MODE_CHANGED", directionMode);
                }
            }

            if (inputDir.is_equal_approx(Vector2(1.0f, 1.0f).normalized())) {
                directionMode = DIRECTION_MODE::RIGHTBACK;
                if (directionMode != directionModePrev) {
                    directionModePrev = directionMode;
                    emit_signal("DIRECTION_MODE_CHANGED", directionMode);
                }
            }
            else if (inputDir.is_equal_approx(Vector2(1.0f, -1.0f).normalized())) { 
                directionMode = DIRECTION_MODE::RIGHTFOR;
                if (directionMode != directionModePrev) {
                    directionModePrev = directionMode;
                    emit_signal("DIRECTION_MODE_CHANGED", directionMode);
                }
            }
            else if (inputDir.is_equal_approx(Vector2(-1.0f, 1.0f).normalized()))  { 
                directionMode = DIRECTION_MODE::LEFTBACK;
                if (directionMode != directionModePrev) {
                    directionModePrev = directionMode;
                    emit_signal("DIRECTION_MODE_CHANGED", directionMode);
                }
            }
            else if (inputDir.is_equal_approx(Vector2(-1.0f, -1.0f).normalized())) { 
                directionMode = DIRECTION_MODE::LEFTFOR;
                if (directionMode != directionModePrev) {
                    directionModePrev = directionMode;
                    emit_signal("DIRECTION_MODE_CHANGED", directionMode);
                }
            }

            Vector3 target_vector = Vector3(inputDir.x, 0.0f, inputDir.y).normalized();
            if (_directionalObject != nullptr) {
                set_direction(_directionalObject->get_transform().basis.xform(target_vector));
            } else {
                set_direction(myCharacter->get_transform().basis.xform(target_vector));
            }
        }

        if (direction != prevDirection) {
            changedDirection = true;
            prevDirection = direction;
        }

        if (direction != Vector3(0.0f, 0.0f, 0.0f)) {
            set_isMoving(true);
            _rotationAngle = Math::atan2(direction.z, direction.x) + (Math_PI / 2.0f);
            float current_y_rot = (_armature != nullptr) ? _armature->get_rotation().y : 0.0f;
            float _offset = current_y_rot + _rotationAngle;
            if (_offset >= (2.0f * Math_PI)) {
                _offset -= (2.0f * Math_PI);
            }

            if (! isDoingRotation && Math::abs(_offset) > (Math_PI / 18000.0f) && _armature != nullptr) {
                if ((inputDir.is_equal_approx(Vector2(-1.0f, 0.0f)) && _leftRotationEnabled) ||
                    (inputDir.is_equal_approx(Vector2(1.0f, 0.0f)) && _rightRotationEnabled) ||
                    (inputDir.is_equal_approx(Vector2(0.0f, -1.0f)) && _frontRotationEnabled) ||
                    (inputDir.is_equal_approx(Vector2(0.0f, 1.0f)) && _rearRotationEnabled)) {
                    rotateArmature(_armature, -_armature->get_rotation().y, _rotationAngle, delta);
                }
            }

            if ((speed != _RUN_SPEED) &&  isRuning) {
                oldSpeed = speed; speed = _RUN_SPEED;
            } else if ((speed != _WALK_SPEED) && ! isRuning) {
                oldSpeed = speed; speed = _WALK_SPEED;
            }

            if ( isFalling) {
                if ( isRuning && speed != _RUN_SPEED * _SPEED_KEPT_BY_FALLING) { oldSpeed = speed; speed = _RUN_SPEED * _SPEED_KEPT_BY_FALLING; }
                else if (! isRuning && speed != _WALK_SPEED * _SPEED_KEPT_BY_FALLING) { oldSpeed = speed; speed = _WALK_SPEED * _SPEED_KEPT_BY_FALLING; }
            } else if ( JumpKeyPressed) {
                if ( isRuning && speed != _RUN_SPEED * _SPEED_KEPT_BY_JUMPING) { oldSpeed = speed; speed = _RUN_SPEED * _SPEED_KEPT_BY_JUMPING; }
                else if (! isRuning && speed != _WALK_SPEED * _SPEED_KEPT_BY_JUMPING) { oldSpeed = speed; speed = _WALK_SPEED * _SPEED_KEPT_BY_JUMPING; }
            }

            Vector3 _finalSpeed = direction * speed;
            Vector3 current_velocity = myCharacter->get_velocity();

            if (current_velocity != _finalSpeed) {
                if (changedDirection && ! isJumping && ! isFalling) {
                    if (_changeDirectionMode == CHANGEDIRECTION_MODE::CONTINOUS)      current_velocity = _finalSpeed;
                    else if (_changeDirectionMode == CHANGEDIRECTION_MODE::FIFTY)     current_velocity = _finalSpeed * 0.5f;
                    else if (_changeDirectionMode == CHANGEDIRECTION_MODE::RESET)     current_velocity = _finalSpeed * 0.0f;
                    changedDirection = false;
                }
                float accel_factor = (float)delta * Math::abs(speed - oldSpeed) / accelerationTime;
                current_velocity.x = Math::move_toward(current_velocity.x, _finalSpeed.x, accel_factor);
                current_velocity.z = Math::move_toward(current_velocity.z, _finalSpeed.z, accel_factor);
                myCharacter->set_velocity(current_velocity);
            } 
        } else {
            if (speed != 0.0f) { oldSpeed = speed; speed = 0.0f; }
            Vector3 current_velocity = myCharacter->get_velocity();
            if (current_velocity.x != 0.0f || current_velocity.z != 0.0f) {
                float decel_factor = (float)delta * Math::abs(speed - oldSpeed) / decelerationTime;
                current_velocity.x = Math::move_toward(current_velocity.x, 0.0f, decel_factor);
                current_velocity.z = Math::move_toward(current_velocity.z, 0.0f, decel_factor);
                myCharacter->set_velocity(current_velocity);
            } else {
                if (! isFalling) {
                    changedDirection = false;
                    set_isMoving(false);
                    directionMode = DIRECTION_MODE::NONE;
                    if (directionMode != directionModePrev) {
                        directionModePrev = directionMode;
                        emit_signal("DIRECTION_MODE_CHANGED", directionMode);
                    }
                }
            }
        }

        if ( isJumping ||  isFalling || myCharacter->get_floor_angle() > 0.0f) {
            myCharacter->set_axis_lock(PhysicsServer3D::BODY_AXIS_LINEAR_Y, false);
        } else {
            myCharacter->set_axis_lock(PhysicsServer3D::BODY_AXIS_LINEAR_Y, true);
        }

        if (myCharacter->move_and_slide()) {
            pushAwwayRigidbody();
        }

        if (isFalling) { 
            movementState = MOVEMENT_STATE::FALLING;
            if (movementState != movementStatePrev) {
                movementStatePrev = movementState;
                emit_signal("MOVEMENT_STATE_CHANGED", movementState);
            }
        }
        else if (isJumping) { 
            movementState = MOVEMENT_STATE::JUMPING;
            if (movementState != movementStatePrev) {
                movementStatePrev = movementState;
                emit_signal("MOVEMENT_STATE_CHANGED", movementState);
            }
        }
        else if (isRuning) { 
            movementState = MOVEMENT_STATE::RUNING;
            if (movementState != movementStatePrev) {
                movementStatePrev = movementState;
                emit_signal("MOVEMENT_STATE_CHANGED", movementState);
            }
        }
        else if (isWalking) { 
            movementState = MOVEMENT_STATE::WALKING;
            if (movementState != movementStatePrev) {
                movementStatePrev = movementState;
                emit_signal("MOVEMENT_STATE_CHANGED", movementState);
            }
        }
        else if ( ! isMoving) { 
            movementState = MOVEMENT_STATE::IDLE;
            if (movementState != movementStatePrev) {
                movementStatePrev = movementState;
                emit_signal("MOVEMENT_STATE_CHANGED", movementState);
            }
        }
    }

    if ( isDoingRotation) {
        process_armature_rotation(delta);
    }
}

void CharacterMovementComponent::rotateArmature(Node3D *armatureComponent, float oldRotationAngle, float newRotationAngle, double delta) {
    if (!_characterRotation || armatureComponent == nullptr) return;

    armatureComponentTarget = armatureComponent;
    rotStep = (float)delta / _transitionTime;
    set_isDoingRotation(true);


    if (oldRotationAngle > Math_PI)  oldRotationAngle -= (2.0f * Math_PI);
    if (oldRotationAngle < -Math_PI) oldRotationAngle += (2.0f * Math_PI);
    if (newRotationAngle > Math_PI)  newRotationAngle -= (2.0f * Math_PI);
    if (newRotationAngle < -Math_PI) newRotationAngle += (2.0f * Math_PI);

    if (Math::abs(newRotationAngle - oldRotationAngle) > Math_PI) {
        if (oldRotationAngle > 0.0f) oldRotationAngle -= (2.0f * Math_PI);
        else                         oldRotationAngle += (2.0f * Math_PI);
    }

    rotOldAngle = oldRotationAngle;
    rotNewAngle = newRotationAngle;
}

void CharacterMovementComponent::process_armature_rotation(double delta) {
    if (!is_inside_tree() || armatureComponentTarget == nullptr) {
        set_isDoingRotation(false);
        return;
    }

    if (rotStep < 1.0f) {
        float x = Math::lerp(rotOldAngle, rotNewAngle, rotStep);
        armatureComponentTarget->set_rotation(Vector3(0.0f, -x, 0.0f));

        for (int i = 0; i < _collisionHullsArray.size(); i++) {
            CollisionShape3D *collisionHull = Object::cast_to<CollisionShape3D>(_collisionHullsArray[i]);
            if (collisionHull) {
                Vector3 current_pos = collisionHull->get_position();
                Vector3 new_pos = -armatureComponentTarget->get_transform().basis.get_column(2).normalized() * (float)collisionHullsArrayOffset[i];
                collisionHull->set_position(Vector3(new_pos.x, current_pos.y, new_pos.z));
                collisionHull->set_rotation(Vector3(0.0f, -x, 0.0f));
            }
        }
        rotStep += (float)delta / _transitionTime;
    } else {
        set_isDoingRotation(false);
    }
}

void CharacterMovementComponent::pushAwwayRigidbody() {
    set_isPushing(false);
    for (int i = 0; i < myCharacter->get_slide_collision_count(); i++) {
        Ref<KinematicCollision3D> collision = myCharacter->get_slide_collision(i);
        if (collision.is_valid()) {
            RigidBody3D *rb = Object::cast_to<RigidBody3D>(collision->get_collider());
            if (rb != nullptr) {
                Vector3 pushDir = -collision->get_normal();
                float massRatio = Math::max(_minMassRatioAllowed, _characterMass / rb->get_mass());
                massRatio = Math::min(massRatio, _maxMassRatioAllowed);

                float pushForce = massRatio * _characterForceFactor * speed;
                rb->apply_impulse(pushDir.normalized() * pushForce, collision->get_position() - rb->get_global_position());
                set_isPushing(true);
            }
        }
    }
}


void CharacterMovementComponent::stop_movement() { set_isMoving(false); }
void CharacterMovementComponent::start_movement() { set_isMoving(true); }


Ref<CharacterMovementData> CharacterMovementComponent::get_context() {
    Ref<CharacterMovementData> context; 
    context.instantiate();
    context->movementState = movementState;
    context->directionMode = directionMode;
    context->changeDirectionMode = _changeDirectionMode;
    context->isRuning = get_isRuning();
    context->isMoving = get_isMoving();
    context->isPushing = get_isPushing();
    context->isJumping = get_isJumping();
    context->isWalking = get_isWalking();
    context->JumpKeyPressed = JumpKeyPressed;
    context->isFalling = get_isFalling();
    context->isDoingRotation = get_isDoingRotation();
    context->inputDir = get_inputDir();
    context->prevDirection = prevDirection;
    context->direction = get_direction();
    return context;
}

void CharacterMovementComponent::set_context(const Ref<CharacterMovementData> &context) {
    if (context.is_null()) return;
    movementState = (MOVEMENT_STATE)context->movementState;
    directionMode = (DIRECTION_MODE)context->directionMode;
    _changeDirectionMode = context->changeDirectionMode;
    set_isRuning(context->isRuning);
    set_isMoving(context->isMoving);
    set_isPushing(context->isPushing);
    set_isJumping(context->isJumping);
    set_isWalking(context->isWalking);
    JumpKeyPressed = context->JumpKeyPressed;
    set_isFalling(context->isFalling);
    set_isDoingRotation(context->isDoingRotation);
    set_inputDir(context->inputDir);
    prevDirection = context->prevDirection;
    set_direction(context->direction);
}


void CharacterMovementComponent::_validate_property(PropertyInfo &p_property) const {
    if (p_property.name == StringName("_WALK_SPEED") && _movementMode != MOVEMENT_MODE::TWOSPEEDS) {
        p_property.usage = PROPERTY_USAGE_NO_EDITOR;
    }
    if (p_property.name == StringName("_RUN_SPEED") && _movementMode != MOVEMENT_MODE::TWOSPEEDS) {
        p_property.usage = PROPERTY_USAGE_NO_EDITOR;
    }
    if (p_property.name == StringName("_MAX_SPEED") && _movementMode != MOVEMENT_MODE::ONESPEED) {
        p_property.usage = PROPERTY_USAGE_NO_EDITOR;
    }
}


void CharacterMovementComponent::_notification(int p_what) {
    if (p_what == NOTIFICATION_WM_CLOSE_REQUEST) {
        queue_free();
    }
}