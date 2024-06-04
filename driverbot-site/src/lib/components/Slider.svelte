<script lang="ts">
  // Props
  export let setSettings: Function;
  export let setting: string;
  export let checked = false;
</script>

<!-- Basic slider -->
<label class="switch">
  <input
    type="checkbox"
    {checked}
    on:change={(e) => {
      if (e.target) {
        // @ts-ignore
        setSettings(setting, e.target.checked);
      }
    }}
  />
  <span class="slider round"></span>
</label>

<style>
  /* The switch - the box around the slider */
  .switch {
    position: relative;
    display: inline-block;
    width: 52px;
    height: 24px;
    margin: 8px;
  }

  /* Hide default HTML checkbox */
  .switch input {
    opacity: 0;
    width: 0;
    height: 0;
  }

  /* The slider */
  .slider {
    position: absolute;
    cursor: pointer;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    background-color: #111;
    -webkit-transition: 0.4s;
    transition: 0.4s;
  }

  .slider:before {
    position: absolute;
    content: "";
    height: 17px;
    width: 17px;
    left: 4px;
    bottom: 4px;
    background-color: white;
    -webkit-transition: 0.4s;
    transition: 0.4s;
  }

  input:checked + .slider {
    background-color: #7289d9;
  }

  input:focus + .slider {
    box-shadow: 0 0 1px #7289d9;
  }

  input:checked + .slider:before {
    -webkit-transform: translateX(26px);
    -ms-transform: translateX(26px);
    transform: translateX(26px);
  }

  /* Rounded sliders */
  .slider.round {
    border-radius: 34px;
  }

  .slider.round:before {
    border-radius: 50%;
  }
</style>
