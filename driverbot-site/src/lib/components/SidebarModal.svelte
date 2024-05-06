<script lang="ts">
  import Slider from "$lib/components/Slider.svelte";
  export let setSettings: Function;
  export let slidersEnabled: boolean = false;
  export let checkedSliders: boolean[];
  export let sliderSettings: string[];
  export let header: string;
  export let labels: string[];
  export let values: string[];
</script>

<div class="settings">
  <div class="setting">
    <h1 class="main-label custom-shadow">{header}</h1>
    {#each labels as label, i}
      <div class="label custom-shadow">{label}</div>

      {#if slidersEnabled}
        <div class="slider-wrapper">
          <Slider
            setting={sliderSettings[i]}
            checked={checkedSliders[i]}
            {setSettings}
          />
        </div>
      {/if}
    {/each}
  </div>
</div>

<style>
.settings {
  margin-bottom: 32px;
  position: relative;
  display: flex;
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
  flex-direction: column;
  align-items: center;
  justify-content: center;
  margin: 32px;
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
    margin: 16px;
  }

  .main-label {
    margin: 12px 0 20px 0;
    color: #fff;
  }

  .custom-shadow {
    text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.2);
  }
</style>
