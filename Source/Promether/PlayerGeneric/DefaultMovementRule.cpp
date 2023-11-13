// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultMovementRule.h"

UDefaultMovementRule::UDefaultMovementRule()
{
	GroundFriction = 1000;
	MaxWalkSpeed = 400;
	MaxAcceleration = 2147483647;
	bOrientRotationToMovement = true;
	RotationRate = FRotator(0, 720, 0);
}
