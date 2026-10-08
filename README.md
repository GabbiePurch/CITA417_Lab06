# CITA417_Lab06

# Lab 06 - Reusable Interaction System

## Overview

For this lab, I created a reusable C++ interaction system in Unreal Engine 5 using pressure plates and interactive doors. The goal was to demonstrate composition, object communication, and separation of responsibilities between C++ and Blueprints.

The system allows a player to activate a pressure plate that controls a door. Different pressure plates and doors can be configured in the Unreal Editor without modifying the underlying C++ code.

## C++ Classes

### PressurePlate

The `PressurePlate` class is a reusable C++ Actor that owns a Box Collision component.

It uses overlap events to detect when a Pawn enters or leaves the pressure plate.

The pressure plate is responsible for:
- Detecting overlap events.
- Tracking whether a player is standing on the plate.
- Managing the activation timer.
- Communicating with its assigned door.
- Logging activation, deactivation, and configuration errors.

### InteractiveDoor

The `InteractiveDoor` class is a separate reusable C++ Actor responsible for opening and closing a door.

It contains two public functions:
- `OpenDoor()` — Opens the door.
- `CloseDoor()` — Closes the door.

The door uses `FMath::VInterpConstantTo()` to move smoothly between its closed and open positions.

## Reusable Configurations

I created two different pressure plate and door setups using the same C++ classes.

**Setup 1 — Vertical Door**
- Opens upward.
- Opening offset: Z = 350.
- Movement speed: 150.
- Activation delay: 0 seconds.

**Setup 2 — Horizontal Door**
- Opens sideways.
- Opening offset: X = 250.
- Movement speed: 100.
- Activation delay: 3 seconds.

Both setups use the same underlying C++ system, demonstrating reusability through Editor configuration.

## Independent Extension — Activation Delay

I added a configurable activation delay to the pressure plate system.

The `ActivationDelay` variable allows designers to specify how long a player must remain on a pressure plate before its assigned door opens.

If the player leaves before the timer finishes, activation is canceled and the timer resets.

If the player leaves after the door opens, the pressure plate calls `CloseDoor()`.

This feature makes the interaction system more flexible without requiring separate pressure plate classes.

## C++ and Blueprint Responsibilities

**C++ handles:**
- Collision detection.
- Overlap event processing.
- Activation timing.
- Door movement.
- Communication between objects.
- State tracking and error logging.

**Blueprints and the Unreal Editor handle:**
- Mesh selection and visual appearance.
- Level layout.
- Collision-volume configuration.
- Door movement distance and speed.
- Activation delay settings.
- Assigning each pressure plate to its target door.

## Architecture and Communication

The system uses composition because the `PressurePlate` Actor owns a Box Collision component, while the `InteractiveDoor` Actor owns a Static Mesh component.

The pressure plate communicates with its target door through the public `OpenDoor()` and `CloseDoor()` functions.

The pressure plate does not directly modify the door's internal movement variables. Instead, the door manages its own behavior.

This separation makes the system easier to reuse, configure, and maintain.

## Testing and Validation

The following tests were completed successfully:

- Pressure plate detects player overlap.
- Door opens when its pressure plate activates.
- Door closes when the player leaves.
- Two
