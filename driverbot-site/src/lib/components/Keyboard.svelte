<script lang="ts">
  import publishDirection from "$lib/MQTT/publishDirection";
  import { addRecord } from "$lib/stores/recordInputStore";

  const allKeys: string[] = ["W", "A", "S", "D"];
  let pressedKeys: Set<string> = new Set(); // Set to store the pressed keys
  let lastDirection = "";

  // Function to animate a key when pressed
  const pressKey = () => {
    for (const key of pressedKeys.values()) {
      const elem: HTMLButtonElement | any = document.querySelector(
        `.key-${key.toLowerCase()}`
      );

      if (elem) {
        elem.style.transform = "scale(0.9)";
      }
    }

    for (const key of allKeys) {
      if (!pressedKeys.has(key)) {
        const elem: HTMLButtonElement | any = document.querySelector(
          `.key-${key.toLowerCase()}`
        );
        if (elem) {
          elem.style.transform = "scale(1)";
        }
      }
    }
  };

  // Function to handle key down event
  const onKeyDown = (event: any) => {
    const key = event.key.toUpperCase();
    if (allKeys.includes(key)) {
      pressedKeys.add(key);
      pressKey();
      updateDirection();
    }
  };

  // Function to handle key up event
  const onKeyUp = (event: any) => {
    const key = event.key.toUpperCase();
    if (allKeys.includes(key)) {
      pressedKeys.delete(key);
      pressKey();
      updateDirection();
    }
  };

  // Determine the direction and publish it to the MQTT broker
  const updateDirection = () => {
    let direction = "stop";

    if (pressedKeys.has("W") && pressedKeys.has("A")) direction = "nw";
    else if (pressedKeys.has("W") && pressedKeys.has("D")) direction = "ne";
    else if (pressedKeys.has("W")) direction = "n";
    else if (pressedKeys.has("S") && pressedKeys.has("A")) direction = "sw";
    else if (pressedKeys.has("S") && pressedKeys.has("D")) direction = "se";
    else if (pressedKeys.has("S")) direction = "s";
    else if (pressedKeys.has("A")) direction = "w";
    else if (pressedKeys.has("D")) direction = "e";

    if (direction !== lastDirection) {
      publishDirection(direction);
      addRecord(direction);
      lastDirection = direction;
    }
  };
</script>

<div class="keyboard">
  <div class="row-1">
    <!-- W key is on another row -->
    <button
      class="key key-w"
      id="key-w"
      
      on:mousedown={() => {
        onKeyDown({ key: "W" });
      }}
      on:mouseup={() => {
        onKeyUp({ key: "W" });
      }}
    >
      <div class="key-inner">
        <span>W</span>
      </div>
    </button>
  </div>
  <div class="row-2">
    <!-- Loop through the keys to display them dynamically -->
    {#each allKeys as key (key)}
      {#if key !== "W"}
        <button
          id="key-{key}"
          class="key key-{key.toLocaleLowerCase()}"
          on:mousedown={() => {
            onKeyDown({ key });
          }}
          on:mouseup={() => {
            onKeyUp({ key });
          }}
        >
          <div class="key-inner">
            <span>{key}</span>
          </div>
        </button>
      {/if}
    {/each}
  </div>
</div>

<!-- Event handler for handling wasd presses -->
<svelte:window on:keydown|preventDefault={onKeyDown} on:keyup={onKeyUp} />

<style>
  .key {
    width: 64px;
    height: 64px;
    background-color: black;
    border-radius: 5px;
    display: inline-block;
    margin: 8px;
    margin-left: -4px;
    padding: 0;
    transition: all 150ms ease;
  }

  .key-w {
    margin-bottom: 0;
  }

  #key-w {
    top: 0;
  }

  #key-a {
    top: 50px;
    left: 0;
  }

  #key-s {
    top: 50px;
  }

  .key:hover {
    cursor: grab;
  }

  .key-inner {
    width: 47px;
    height: 51.5px;
    background-color: #333;
    color: white;
    position: relative;
    top: 1px;
    left: 9px;
    border-radius: 3px;
    text-align: center;
    margin: 0;
    padding: 0;
    transition: all 100ms ease;
    display: flex;
    align-items: center;
    justify-content: center;
  }

  span {
    transition: all 100ms ease;
  }

  .key:active,
  .active {
    transform: scale(0.9);
  }

  .keyboard {
    display: flex;
    align-items: center;
    justify-content: center;
    margin-top: 100px;
    position: relative;
    flex-direction: column;
    height: 160px;
    width: 240px;
  }

  .row-1,
  .row-2 {
    display: flex;
    transform: translateX(6px);
  }

  button {
    background: none;
    color: inherit;
    border: none;
    padding: 0;
    font: inherit;
    cursor: pointer;
    outline: inherit;
  }
</style>
