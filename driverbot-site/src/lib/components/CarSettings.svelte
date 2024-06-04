<script lang="ts">
  import { FontAwesomeIcon } from "@fortawesome/svelte-fontawesome";
  import { faArrowLeft, faArrowRight } from "@fortawesome/free-solid-svg-icons";
  import publishCarSettings from "$lib/MQTT/publishCarSettings";
  import { scale } from "svelte/transition";

  let motorSpeed = 255;
  let servoAngle = 90;

  // Functions to increase or decrease the motor speed
  const increaseMotorSpeed = () => {
    if (motorSpeed < 1024) {
      motorSpeed += 5;
      publishCarSettings("motorSpeed", motorSpeed);
    }
  };

  const decreaseMotorSpeed = () => {
    if (motorSpeed > 0) {
      motorSpeed -= 5;
      publishCarSettings("motorSpeed", motorSpeed);
    }
  };

  // Functions to increase or decrease the servo angle
  const increaseServoAngle = () => {
    if (servoAngle < 110) {
      servoAngle += 5;
      publishCarSettings("servoAngle", servoAngle);
    }
  };

  const decreaseServoAngle = () => {
    if (servoAngle > 0) {
      servoAngle -= 5;
      publishCarSettings("servoAngle", servoAngle);
    }
  };
</script>

<div class="settings" transition:scale>
  <h1 class="main-label custom-shadow">Car Settings</h1>
  <div class="setting">
    <div class="label custom-shadow">Motor Speed</div>
    <div class="input-wrapper">
      <button class="arrow-left" on:click={decreaseMotorSpeed}
        ><FontAwesomeIcon icon={faArrowLeft} /></button
      >
      <div>{motorSpeed}</div>
      <button class="arrow-right" on:click={increaseMotorSpeed}
        ><FontAwesomeIcon icon={faArrowRight} /></button
      >
    </div>
  </div>
  <div class="setting bottom">
    <div class="label custom-shadow">Servo angle</div>
    <div class="input-wrapper">
      <button class="arrow-left" on:click={decreaseServoAngle}
        ><FontAwesomeIcon icon={faArrowLeft} /></button
      >
      <div>{servoAngle}</div>
      <button class="arrow-right" on:click={increaseServoAngle}
        ><FontAwesomeIcon icon={faArrowRight} /></button
      >
    </div>
  </div>
</div>

<style>
  .settings {
    margin-bottom: 32px;
    position: relative;
    display: flex;
    align-items: center;
    justify-content: center;
    flex-direction: column;
    padding: 0 24px 0 24px;
    left: 16px;
    top: 16px;
    border-radius: 8px;
    background: #2f3136;
    box-shadow: 6px 8px 5px rgba(0, 0, 0, 0.2);
    width: 192px;
    transition: all 1000ms ease;
  }

  .input-wrapper {
    position: absolute;
    right: 4px;
    display: flex;
    align-items: center;
    justify-content: center;
    margin: 16px;
    color: #fff;
  }

  .setting {
    display: flex;
    align-items: center;
    justify-content: center;
    margin: 16px;
  }

  .arrow-left,
  .arrow-right {
    background-color: inherit;
    border: none;
    color: #fff;
  }

  .label {
    font-size: 18px;
    position: absolute;
    left: 12px;
    color: #fff;
  }

  .main-label {
    font-size: 26px;
    margin: 12px 0 20px 0;
    color: #fff;
  }

  .custom-shadow {
    text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.2);
  }

  .bottom {
    margin-bottom: 24px;
  }
</style>
