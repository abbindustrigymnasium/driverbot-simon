<script lang="ts">
  // Import necessary components and functions
  import { get } from "svelte/store";
  import {
    recordInputStore,
    setIsRecording,
  } from "$lib/stores/recordInputStore";
  import publishDirection from "$lib/MQTT/publishDirection";
  import { FontAwesomeIcon } from "@fortawesome/svelte-fontawesome";
  import {
    faRepeat,
    faTrash,
    faVideo,
    faVideoSlash,
    faLocationDot,
  } from "@fortawesome/free-solid-svg-icons";
  import { scale, blur } from "svelte/transition";

  $: isRecording = false;

  // Function to delay execution
  const delay = (ms: number) =>
    new Promise((resolve) => setTimeout(resolve, ms));

  // Function to repeat recorded inputs
  const repeatInput = async () => {
    console.log("Repeat Input");

    const records = get(recordInputStore);
    if (records.length === 0) return;

    let previousTime = records[0].time;

    console.log(records);

    // Loop through records and publish directions with delay
    for (const record of records) {
      const delayTime = record.time.getTime() - previousTime.getTime();

      await delay(delayTime);
      publishDirection(record.key);

      previousTime = record.time;
    }
  };

  // Function to delete all records
  const deleteRecords = () => {
    recordInputStore.set([]);
  };

  // Function to toggle recording state
  const recordInput = () => {
    isRecording = !isRecording;
    setIsRecording(isRecording);
    console.log("Record Input", isRecording);
  };

  let hoveredButton = "";

  // Function to handle mouse enter event
  const handleMouseEnter = (buttonName: any) => {
    hoveredButton = buttonName;
  };

  // Function to handle mouse leave event
  const handleMouseLeave = () => {
    hoveredButton = "";
  };
</script>

<!-- UI for function settings -->
<div class="settings" transition:scale>
  <h1 class="main-label custom-shadow">Functions</h1>
  <div class="row1">
    <!-- Button to repeat input -->
    <button
      class="button"
      on:click={repeatInput}
      on:mouseenter={() => handleMouseEnter("repeat")}
      on:mouseleave={handleMouseLeave}
    >
      {#if hoveredButton === "repeat"}
        <span transition:scale={{ duration: 700 }} class="button-inner">
          Repeat Input
        </span>
      {:else}
        <span transition:scale={{ duration: 700 }} class="button-inner icon"
          ><FontAwesomeIcon icon={faRepeat} /></span
        >
      {/if}
    </button>
    <!-- Button to delete records -->
    <button
      class="button"
      on:click={deleteRecords}
      on:mouseenter={() => handleMouseEnter("delete")}
      on:mouseleave={handleMouseLeave}
    >
      {#if hoveredButton === "delete"}
        <span transition:scale={{ duration: 700 }} class="button-inner"
          >Delete Records</span
        >
      {:else}
        <span transition:scale={{ duration: 700 }} class="button-inner icon"
          ><FontAwesomeIcon icon={faTrash} /></span
        >
      {/if}
    </button>
  </div>
  <div class="row2">
    <!-- Button to record input -->
    <button
      class="button"
      on:click={recordInput}
      on:mouseenter={() => handleMouseEnter("record")}
      on:mouseleave={handleMouseLeave}
    >
      {#if hoveredButton === "record"}
        <span transition:scale={{ duration: 700 }} class="button-inner"
          >{isRecording ? "Stop Recording" : "Start Recording"}</span
        >
      {:else}
        <span transition:scale={{ duration: 700 }} class="button-inner icon">
          <FontAwesomeIcon icon={isRecording ? faVideoSlash : faVideo} /></span
        >
      {/if}
    </button>
    <!-- Button to view map -->
    <a href="/map">
      <button
        class="button"
        on:mouseenter={() => handleMouseEnter("map")}
        on:mouseleave={handleMouseLeave}
      >
        {#if hoveredButton === "map"}
          <span transition:scale={{ duration: 700 }} class="button-inner"
            >View Map</span
          >
        {:else}
          <span transition:scale={{ duration: 700 }} class="button-inner icon">
            <FontAwesomeIcon icon={faLocationDot} /></span
          >
        {/if}
      </button>
    </a>
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

  .button-inner {
    position: absolute;
    left: 50%;
    top: 50%;
    transform: translate(-50%, -50%);
    color: #fff;
    font-size: 12px;
  }

  .icon {
    font-size: 24px;
  }

  .row1,
  .row2 {
    display: flex;
    align-items: center;
    justify-content: center;
  }

  .button {
    width: 64px;
    height: 64px;
    position: relative;
    background-color: #7289d9;
    border-radius: 12px;
    border: none;
    margin: 8px;
  }

  .button:active {
    transform: translateY(2px);
  }

  .main-label {
    margin: 12px 0 20px 0;
    color: #fff;
  }

  .custom-shadow {
    text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.2);
  }
</style>
