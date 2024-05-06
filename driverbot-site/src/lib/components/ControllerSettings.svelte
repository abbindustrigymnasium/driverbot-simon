<script lang="ts">
  import Slider from "$lib/components/Slider.svelte";
  export let setSettings: Function;
</script>

<div class="settings">
  <h1 class="main-label custom-shadow">Settings</h1>
  <div class="setting">
    <div class="label custom-shadow">Joystick</div>
    <div class="slider-wrapper">
      <Slider setting="joystick" {setSettings} />
    </div>
  </div>
  <div class="setting">
    <div class="label custom-shadow">Statistics</div>
    <div class="slider-wrapper">
      <Slider setting="statistics" checked {setSettings} />
    </div>
  </div>
  <div class="setting bottom">
    <div class="label custom-shadow">Functions</div>
    <div class="slider-wrapper">
      <Slider setting="functions" checked {setSettings} />
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

  .setting {
    display: flex;
    align-items: center;
    justify-content: center;
    margin: 16px;
  }

  .slider-wrapper {
    position: absolute;
    right: 4px;
  }

  .label {
    font-size: 18px;
    position: absolute;
    left: 12px;
    color: #fff;
  }

  .main-label {
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
