<script lang="ts">
  import Keyboard from "$lib/components/Keyboard.svelte";
  import startStop from "$lib/frontendMQTT/startStop";
  import CustomFunctions from "$lib/components/CustomFunctions.svelte";
  import Statistics from "$lib/components/Statistics.svelte";
  import ControllerSettings from "$lib/components/ControllerSettings.svelte";
  import Joystick from "$lib/components/Joystick.svelte";

  $: joystick = false;
  $: statistics = true;
  $: functions = true;

  const setSettings = (setting: string, value: boolean) => {
    if (setting === "joystick") {
      joystick = value;
      console.log("Joystick is now", value ? "enabled" : "disabled");
    } else if (setting === "statistics") {
      statistics = value;
      console.log("Statistics is now", value ? "enabled" : "disabled");
    } else if (setting === "functions") {
      console.log("Functions is now", value ? "enabled" : "disabled");
      functions = value;
    }
  };
</script>

<div class="wrapper">
  <!-- <a class="esc" href="/"><div></div></a> -->
  {#if joystick}
    <Joystick />
  {:else}
    <Keyboard />
  {/if}
  <div class="card-column">
    <ControllerSettings {setSettings} />
    {#if statistics}
      <Statistics />
    {/if}
    {#if functions}
      <CustomFunctions />
    {/if}
  </div>
</div>

<style>
  .wrapper {
    display: flex;
    justify-content: center;
    align-items: center;
    flex-direction: column;
  }

  .esc {
    position: absolute;
    right: 24px;
    top: 24px;
    border: 2px solid #fff;
    border-radius: 50%;
    padding: 20px;
    width: 20px;
    height: 20px;
    display: flex;
    align-items: center;
    justify-content: center;
  }

  .esc::before,
  .esc::after {
    content: "";
    position: absolute;
    height: 1.5px;
    width: 40%;
    background-color: #fff;
  }

  .esc::before {
    transform: rotate(45deg);
  }

  .esc::after {
    transform: rotate(-45deg);
  }

  .card-column {
    display: flex;
    flex-direction: column;
    position: absolute;
    align-items: center;
    justify-content: flex-start;
    top: 8px;
    right: 40px;
    width: 200px;
    height: 90%;
  }
</style>
