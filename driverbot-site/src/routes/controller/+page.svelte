<script lang="ts">
  import Keyboard from "$lib/components/Keyboard.svelte";
  import RecordInput from "$lib/components/RecordInput.svelte";
  import ControllerSettings from "$lib/components/ControllerSettings.svelte";
  import CarSettings from "$lib/components/CarSettings.svelte";
  import Joystick from "$lib/components/Joystick.svelte";

  $: joystick = false;
  $: functions = true;
  $: carSettings = true;

  // Function to change the sidebar settings visibility
  const setSettings = (setting: string, value: boolean) => {
    if (setting === "joystick") {
      joystick = value;
    } else if (setting === "functions") {
      functions = value;
    } else if (setting === "car") {
      carSettings = value;
    }
  };
</script>

<div class="wrapper">
  {#if joystick}
    <Joystick />
  {:else}
    <Keyboard />
  {/if}
  <!-- Dynamic settings sidebar -->
  <div class="card-column">
    <ControllerSettings {setSettings} />
    {#if functions}
      <RecordInput />
    {/if}
    {#if carSettings}
      <CarSettings />
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
