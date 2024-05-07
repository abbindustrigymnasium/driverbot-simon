<script lang="ts">
  import publishDirection from "$lib/frontendMQTT/publishDirection";
  import { onMount } from "svelte";

  let nipplejs;
  let lastDirection = "";

  // Load nipple.js when the component mounts
  onMount(async () => {
    nipplejs = (await import("nipplejs")).default;

    const joystickElement = document.querySelector(".joystick");

    // Options for nipple.js
    const options = {
      zone: joystickElement,
      color: "white",
      size: 100,
      threshold: 0.1,
      fadeTime: 250,
      multitouch: false,
      maxNumberOfNipples: 1,
      dataOnly: false,
      position: { left: "50%", top: "50%" },
      mode: "static",
      restJoystick: true,
      restOpacity: 0.5,
      lockX: false,
      lockY: false,
      catchDistance: 200,
      shape: "circle",
      dynamicPage: false,
      follow: false,
    };

    // Create the joystick
    const manager = nipplejs.create(options as any);

    // Listen to the 'move' event
    manager.on("move", (evt, data) => {
      // Calculate the direction based on the angle
      const angle = data.angle.degree;
      let direction;

      if (angle >= 22.5 && angle < 67.5) {
        direction = "NE";
      } else if (angle >= 67.5 && angle < 112.5) {
        direction = "N";
      } else if (angle >= 112.5 && angle < 157.5) {
        direction = "NW";
      } else if (angle >= 157.5 && angle < 202.5) {
        direction = "W";
      } else if (angle >= 202.5 && angle < 247.5) {
        direction = "SW";
      } else if (angle >= 247.5 && angle < 292.5) {
        direction = "S";
      } else if (angle >= 292.5 && angle < 337.5) {
        direction = "SW";
      } else {
        direction = "E";
      }

      // Publish the direction if it has changed
      if (lastDirection !== direction) {
        lastDirection = direction;
        publishDirection(direction.toLocaleLowerCase());
        console.log(`Joystick is pointing: ${direction}`);
      }
    });

    // Publish stop when the joystick is released
    manager.on("end", () => {
      // Publish "stop" when the user lets go of the joystick
      publishDirection("stop");
      console.log(`Joystick is pointing: stop`);
    });
  });
</script>

<div class="joystick"></div>

<style>
  .joystick {
    margin: 80px auto;
    position: relative;
    border-radius: 32px;
    background: #2f3136;
    box-shadow: 6px 8px 5px rgba(0, 0, 0, 0.2);
  }
</style>