#ifndef OFFSETS_H
#define OFFSETS_H

// PlayerController
#define MOVEMENT_CONTROLLER 0x98
#define PLAYER_HIT_CONTROLLER 0xA8
#define PLAYER_MATERIAL 0xB0
#define PLAYER_OCCLUSION 0xB8
#define CAMERA 0xE8
#define PHOTON_PLAYER 0x160
#define AIM_CONTROLLER 0x80
#define WEAPON 0x88

// MovementController
#define TRANSFORM 0x70

// Transform (Unity)
#define POSITION 0x24

// PlayerHitController
#define HEALTH 0x20

// PhotonPlayer
#define TEAM 0x70

// AimController
#define VIEW_DIRECTION 0x224

// Camera
#define CAMERA_POSITION 0x18
#define FOV 0x30

// Player size
#define PLAYER_SIZE 0x100

// Wallhack
#define IS_VISIBLE 0x18

// Local player
#define LOCAL_PLAYER 0x70

// Player list
#define PLAYER_LIST 0x28

// ViewMatrix chain
#define VIEW_MATRIX_A 0xE8
#define VIEW_MATRIX_B 0x28
#define VIEW_MATRIX_C 0x38

// Recoil (проверять по очереди)
#define RECOIL_1 0x18
#define RECOIL_2 0x1C
#define RECOIL_3 0x20
#define RECOIL_4 0x24
#define RECOIL_5 0x28
#define RECOIL_6 0x2C

// World
#define FOG_COLOR 0x60
#define SKYBOX_OVERRIDE 0x70

#endif
