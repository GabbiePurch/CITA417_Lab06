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


# Lab 07 - Event-Driven Interaction Extension

## Overview

For Lab 07, I extended the reusable C++ interaction system developed in Lab 06. The goal was to introduce a second interaction method, improve communication between gameplay objects, and support multiple configurable targets.

The original pressure plate system remains functional, while the new interaction switch allows the player to activate multiple objects by pressing E.

## Second Interaction Method

I created a new C++ Actor called `InteractionSwitch`.

Unlike the original pressure plate, which activates automatically when the player enters its collision area, the switch requires the player to be within range and press E.

The switch uses a Box Collision component to detect nearby players. The E key is configured through Unreal Engine's Enhanced Input system using `IA_Interact` and `IMC_Default`.

The `Interact()` function validates that the player is within range before allowing activation.

## Event-Driven Communication

I implemented a C++ multicast delegate called `OnSwitchActivated`.

When the switch is activated, it broadcasts an event that other systems can listen to.

I demonstrated this using a Blueprint event listener that displays "Switch Event Received!" when the switch activates.

This allows additional gameplay behaviors to respond to the switch without requiring every behavior to be directly implemented inside the switch.

## Interface-Based Communication

I created an Unreal C++ interface called `InteractableTarget`.

The interface declares a reusable function:

`ActivateTarget()`

The existing `InteractiveDoor` class implements this interface using `ActivateTarget_Implementation()`.

When activated through the interface, the door calls its existing `OpenDoor()` function.

The switch uses `IInteractableTarget::Execute_ActivateTarget()` rather than directly calling door-specific functions.

This reduces coupling because the switch can communicate with any compatible Actor that implements the interface.

## Object Filtering

I implemented Actor Tag filtering to restrict which Actors can activate the switch.

The player character has the `Player` tag.

The switch checks for this tag during overlap events and ignores Actors that do not have it.

I verified the filtering by removing the tag, testing that the switch rejected interaction, and restoring the tag to confirm the interaction worked again.

## Multiple Target Support

The switch contains a configurable array named `TargetActors`.

This array allows a single interaction source to activate multiple Actors without hard-coded calls for each target.

For the demonstration, I configured two sliding doors that move away from each other when the player presses E.

The same switch can be configured with different targets through the Unreal Editor.

## Independent Architecture Improvement

My independent architecture improvement is the reusable target collection combined with interface-based communication.

Instead of storing only door-specific references, the switch now stores Actor references and validates whether each Actor implements the interaction interface.

This makes the system easier to extend, maintain, and reuse with additional gameplay objects.

## Error Handling and Validation

I tested the following behaviors:

- Original Lab 06 pressure plates still activate their assigned doors.
- The new interaction switch responds to the E key when the player is within range.
- Pressing E outside the interaction range is rejected.
- Both sliding doors open from one switch activation.
- The C++ delegate broadcasts an activation event.
- A Blueprint listener receives the activation event.
- Removing the Player tag prevents switch activation.
- Restoring the Player tag allows interaction again.
- Missing target references generate warnings without crashing.
- The switch successfully calls the interface function on both doors.

## Architecture Comparison

**Lab 06:** The pressure plate directly referenced an `InteractiveDoor` Actor and called its public `OpenDoor()` and `CloseDoor()` functions.

**Lab 07:** The new switch uses an interface-based API to activate multiple configurable Actors and broadcasts an event for additional listeners.

The Lab 07 approach improves flexibility and reduces direct dependencies between interaction sources and targets.

One trade-off is increased architectural complexity, since the system now includes an interface, delegate, and target collection that must be configured and validated.

## Conclusion

Lab 07 demonstrates how an existing Unreal Engine C++ interaction system can be extended through additional input methods, event-driven communication, object filtering, reusable interfaces, and configurable target collections.

The system preserves the original Lab 06 functionality while providing a more flexible foundation for future gameplay interactions.
